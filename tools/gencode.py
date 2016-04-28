#The MIT License (MIT)
#Copyright (c) <2016> <Hussein Nazarala>

#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is furnished
#to do so, subject to the following conditions:

#The above copyright notice and this permission notice shall be included in
#all copies or substantial portions of the Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
#INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
#PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
#COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
#IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
#WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#!usr/bin/python
import argparse
import os
#########################################################################
#This script creates 2 files .cpp .h with Gameplay3D skeleton code

#1. Get class name and output directory (optional)
parser = argparse.ArgumentParser()
parser.add_argument("classname", metavar = 'N', help="The name of the cpp class", nargs=1)

parser.add_argument("-o", "--outdir", help="The output directory")

args = parser.parse_args()
#########################################################################

className = "Main";
parentClass = "Game"

className = args.classname[0]

#Get the current dir: #print os.path.dirname(os.path.realpath(__file__))
#If the user specifies an output directory, change to that directory
if args.outdir:
    os.chdir(args.outdir)


#########################################################################
#.h skeleton code:

hData =[

        "#ifndef " + className + "_H_",
        "#define " + className + "_H_\n",
        
        "#include \"gameplay.h\"\n",
        
        "using namespace gameplay;\n",
        
        "class " + className + ": public Game",
        "{",
        "\npublic:\n",
        
        "    "+ className + "();",
        "    void keyEvent(Keyboard::KeyEvent evt, int key);",
        
        "\nprotected:\n",
        
        "    void initialize();",
        "    void finalize();",
        "    void update(float elapsedTime);",
        "    void render(float elapsedTime);",
        "    void resizeEvent(unsigned int width, unsigned int height);",
        "    void touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);",
        
        "\nprivate:\n",
        
        "    Model* model;",
        "    Matrix wvpMatrix;",
        "    float spinDirection;",
        
        
        "\n};",
        
        "\n#endif",
]

#########################################################################
#.cpp skeleton code:

cppData =[

          "#include \"" + className + ".h\"\n",
          
          className + " game;\n",
          
          className + "::" + className + "()",
          "{",
          "}",
          
          "\nvoid " + className +  "::initialize()",
          "{",
          "}",
          
          "\nvoid " + className +  "::finalize()",
          "{",
          "}",
          
          "\nvoid " + className +  "::update(float elapsedTime)",
          "{",
          "}",
          
          "\nvoid " + className +  "::render(float elapsedTime)",
          "{",
          "    // Clear the color and depth buffers",
          "    clear(CLEAR_COLOR_DEPTH, Vector4::zero(), 1.0f, 0);\n",

          "}",
          
          "\nvoid " + className +  "::keyEvent(Keyboard::KeyEvent evt, int key)",
          "{",
          "     if (evt == Keyboard::KEY_PRESS)",
          "     {",
          "         switch (key)",
          "         {",
          "             case Keyboard::KEY_ESCAPE:",
          "                 exit();",
          "             break;",
          "         }",
          "     }",
          "}",
          
          "\nvoid " + className +  "::resizeEvent(unsigned int width, unsigned int height)",
          "{",
          "     setViewport(gameplay::Rectangle(width, height));",
          "}",
          
          "\nvoid " + className +  "::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)",
          "{",
          "     switch (evt)",
          "     {",
          "         case Touch::TOUCH_PRESS:",
          "         break;",
          "         case Touch::TOUCH_RELEASE:",
          "         break;",
          "         case Touch::TOUCH_MOVE:",
          "         break;",
          "     };",
          "}",
          

          


]


#os.chdir("/Users/huse/Documents/2016/XCodeProjects/PythonProjects/template/Sources")

#########################################################################

# Close opend file
fo = open(className + ".h", "wb")

for line in hData:
    fo.write (line + "\n");

fo.close()

#########################################################################


fo = open(className + ".cpp", "wb")

for line in cppData:
    fo.write (line + "\n");

fo.close()

#########################################################################


print "Done."