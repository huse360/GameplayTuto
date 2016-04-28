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

#ifndef HelloTriangleScene_H_
#define HelloTriangleScene_H_

#include "gameplay.h"

using namespace gameplay;

class HelloTriangleScene: public Game
{

public:

    HelloTriangleScene();
    void keyEvent(Keyboard::KeyEvent evt, int key);

protected:

    void initialize();
    void finalize();
    void update(float elapsedTime);
    void render(float elapsedTime);
    void resizeEvent(unsigned int width, unsigned int height);
    void touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);

    bool drawScene(Node* node);

private:

    Model* model;
    Matrix wvpMatrix;
    float spinDirection;
    
    Scene* scene;


};

#endif
