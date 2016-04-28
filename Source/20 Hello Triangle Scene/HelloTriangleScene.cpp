/*
 The MIT License (MIT)
 Copyright (c) <2016> <Hussein Nazarala>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is furnished
 to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "HelloTriangleScene.h"

HelloTriangleScene game;

HelloTriangleScene::HelloTriangleScene()
{
}

static Mesh* CreateTriangleMesh()
{
    // Calculate the vertices of the equilateral triangle.
    float a = 0.5f;     // length of the side
    Vector2 p1(0.0f,       a / sqrtf(3.0f));
    Vector2 p2(-a / 2.0f, -a / (2.0f * sqrtf(3.0f)));
    Vector2 p3( a / 2.0f, -a / (2.0f * sqrtf(3.0f)));
    
    // Create 3 vertices. Each vertex has position
    //(x, y, z) and color (red, green, blue)
    float vertices[] =
    {
        p1.x, p1.y, 0.0f,   1.0f, 0.0f, 0.0f,
        p2.x, p2.y, 0.0f,   0.0f, 1.0f, 0.0f,
        p3.x, p3.y, 0.0f,   0.0f, 0.0f, 1.0f,
        
    };
    
    unsigned int vertexCount = 3;
    VertexFormat::Element elements[] = {
        
        VertexFormat::Element(VertexFormat::POSITION, 3),
        VertexFormat::Element(VertexFormat::COLOR, 3)
        
    };
    
    Mesh* mesh = Mesh::createMesh(VertexFormat(elements, 2), vertexCount, false);
    if (mesh == NULL)
    {
        GP_ERROR("Failed to create mesh");
        return NULL;
        
    }
    
    mesh->setPrimitiveType(Mesh::TRIANGLES);
    mesh->setVertexData(vertices, 0, vertexCount);
    return mesh;
    
}


void HelloTriangleScene::initialize()
{
    Mesh* mesh = CreateTriangleMesh();
    
    model = Model::create(mesh);
    SAFE_RELEASE(mesh);
    model->setMaterial("res/shaders/colored.vert",
                       "res/shaders/colored.frag",
                       "VERTEX_COLOR");
    
    float w = getWidth() / (float) getHeight();
    float h = 1.0f;
    Matrix::createOrthographic(w, h, -1.0f, 1.0f, &wvpMatrix);
    
    spinDirection = 1.0;
    
    
    // Bind the uniform "u_worldViewProjectionMatrix"
    //to use the WORLD_VIEW_PROJECTION_MATRIX from the scene's
    //active camera and the node that the model belongs to.
    model->getMaterial()->setParameterAutoBinding
    ("u_worldViewProjectionMatrix", "WORLD_VIEW_PROJECTION_MATRIX");
    
    //Create empty scene
    scene = Scene::create();
    
    //Create null camera and then set the projection matrix
    Camera* camera = Camera::createOrthographic(NULL, NULL, NULL, NULL, NULL);
    camera->setProjectionMatrix(wvpMatrix);
    
    
    Node* node;
    node = scene->addNode("camera");
    node->setCamera(camera);
    scene->setActiveCamera(camera);
    SAFE_RELEASE(camera);
    
    node = scene->addNode("triangle");
    node->setDrawable(model);
    
    
    node = scene->findNode("triangle")->clone();
    node->setId("triangle02");
    node->translate(0.5f, 0.0f, 0.0f);
    scene->addNode(node);
    
    node = scene->findNode("triangle")->clone();
    node->setId("triangle03");
    node->translate(-0.5f, 0.0f, 0.0f);
    scene->addNode(node);
    

}




void HelloTriangleScene::finalize()
{
    SAFE_RELEASE(model);

}

void HelloTriangleScene::update(float elapsedTime)
{
    Node* node = scene->findNode("triangle");
    
    node->rotateZ( spinDirection * MATH_PI * elapsedTime * 0.001f);

}

void HelloTriangleScene::render(float elapsedTime)
{
    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4::zero(), 1.0f, 0);
    
    scene->visit(this, &HelloTriangleScene::drawScene);
    
}

bool HelloTriangleScene::drawScene(Node* node)
{
    Drawable* drawable = node->getDrawable();
    if (drawable)
        drawable->draw();
    return true;
}

void HelloTriangleScene::keyEvent(Keyboard::KeyEvent evt, int key)
{
     if (evt == Keyboard::KEY_PRESS)
     {
         switch (key)
         {
             case Keyboard::KEY_ESCAPE:
                 exit();
             break;
         }
     }
}

void HelloTriangleScene::resizeEvent(unsigned int width, unsigned int height)
{
    setViewport(gameplay::Rectangle(width, height));
    
    float w = getWidth() / (float) getHeight();
    float h = 1.0f;
    Matrix::createOrthographic(w, h, -1.0f, 1.0f, &wvpMatrix);
    
    scene->getActiveCamera()->setProjectionMatrix(wvpMatrix);
}

void HelloTriangleScene::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
     switch (evt)
     {
         case Touch::TOUCH_PRESS:
             spinDirection *= -1.0f;

         break;
         case Touch::TOUCH_RELEASE:
         break;
         case Touch::TOUCH_MOVE:
         break;
     };
}
