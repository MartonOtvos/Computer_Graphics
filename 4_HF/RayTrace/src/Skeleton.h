#ifndef GRAPHICS_SKELETON_H
#define GRAPHICS_SKELETON_H


#include "framework.h"
#include "TexturedQuad.h"

class Skeleton{
    // vertex shader in GLSL: It is a Raw string (C++11) since it contains new line characters
    const char * const vertexShader;

    // fragment shader in GLSL
    const char * const fragmentShader;

    unsigned int shaderProgram;

    void InitializeShaderProgram();

    TexturedQuad* texturedQuad;

    Scene* scene;

    vector<vec4> image;

public:

    Skeleton();
    // Initialization, create an OpenGL context
    void onInitialization();

    // Window has become invalid: Redraw
    void onDisplay();

    // Key of ASCII code pressed
    void onKeyboard(unsigned char key, int pX, int pY);

    // Key of ASCII code released
    void onKeyboardUp(unsigned char key, int pX, int pY);

    // Move mouse with key pressed
    void onMouseMotion(int pX, int pY);

    // Mouse click event
    void onMouse(int button, int state, int pX, int pY);

    // Idle event indicating that some time elapsed: do animation here
    void onIdle();


};

#endif //GRAPHICS_SKELETON_H