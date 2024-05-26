#ifndef GRAPHICS_SKELETON_H
#define GRAPHICS_SKELETON_H



class Skeleton{
    // vertex shader in GLSL: It is a Raw string (C++11) since it contains new line characters
    const char * const vertexShader;

    // fragment shader in GLSL
    const char * const fragmentShader;



public:

    Skeleton();
    // Initialization, create an OpenGL context
    void onInitialization();

    // Window has become invalid: Redraw
    static void onDisplay();

    // Key of ASCII code pressed
    static void onKeyboard(unsigned char key, int pX, int pY);

    // Key of ASCII code released
    static void onKeyboardUp(unsigned char key, int pX, int pY);

    // Move mouse with key pressed
    static void onMouseMotion(int pX, int pY);

    // Mouse click event
    static void onMouse(int button, int state, int pX, int pY);

    // Idle event indicating that some time elapsed: do animation here
    static void onIdle();
};

#endif //GRAPHICS_SKELETON_H