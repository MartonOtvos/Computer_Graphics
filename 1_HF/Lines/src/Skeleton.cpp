//=============================================================================================
// Mintaprogram: Zöld háromszög. Ervenyes 2019. osztol.
//
// A beadott program csak ebben a fajlban lehet, a fajl 1 byte-os ASCII karaktereket tartalmazhat, BOM kihuzando.
// Tilos:
// - mast "beincludolni", illetve mas konyvtarat hasznalni
// - faljmuveleteket vegezni a printf-et kiveve
// - Mashonnan atvett programresszleteket forrasmegjeloles nelkul felhasznalni es
// - felesleges programsorokat a beadott programban hagyni!!!!!!! 
// - felesleges kommenteket a beadott programba irni a forrasmegjelolest kommentjeit kiveve
// ---------------------------------------------------------------------------------------------
// A feladatot ANSI C++ nyelvu forditoprogrammal ellenorizzuk, a Visual Studio-hoz kepesti elteresekrol
// es a leggyakoribb hibakrol (pl. ideiglenes objektumot nem lehet referencia tipusnak ertekul adni)
// a hazibeado portal ad egy osszefoglalot.
// ---------------------------------------------------------------------------------------------
// A feladatmegoldasokban csak olyan OpenGL fuggvenyek hasznalhatok, amelyek az oran a feladatkiadasig elhangzottak 
// A keretben nem szereplo GLUT fuggvenyek tiltottak.
//
// NYILATKOZAT
// ---------------------------------------------------------------------------------------------
// Nev    : Otvos Marton Almos
// Neptun : EZG1LF
// ---------------------------------------------------------------------------------------------
// ezennel kijelentem, hogy a feladatot magam keszitettem, es ha barmilyen segitseget igenybe vettem vagy
// mas szellemi termeket felhasznaltam, akkor a forrast es az atvett reszt kommentekben egyertelmuen jeloltem.
// A forrasmegjeloles kotelme vonatkozik az eloadas foliakat es a targy oktatoi, illetve a
// grafhazi doktor tanacsait kiveve barmilyen csatornan (szoban, irasban, Interneten, stb.) erkezo minden egyeb
// informaciora (keplet, program, algoritmus, stb.). Kijelentem, hogy a forrasmegjelolessel atvett reszeket is ertem,
// azok helyessegere matematikai bizonyitast tudok adni. Tisztaban vagyok azzal, hogy az atvett reszek nem szamitanak
// a sajat kontribucioba, igy a feladat elfogadasarol a tobbi resz mennyisege es minosege alapjan szuletik dontes.
// Tudomasul veszem, hogy a forrasmegjeloles kotelmenek megsertese eseten a hazifeladatra adhato pontokat
// negativ elojellel szamoljak el es ezzel parhuzamosan eljaras is indul velem szemben.
//=============================================================================================
#include "framework.h"
#include "Skeleton.h"


    // vertex shader in GLSL: It is a Raw string (C++11) since it contains new line characters
    const char * const vertexSource = R"(
        #version 330

    )";

    // fragment shader in GLSL
    const char * const fragmentSource = R"(

    )";

    Skeleton::Skeleton() : vertexShader(vertexSource), fragmentShader(fragmentSource) {}

    // Initialization, create an OpenGL context
    void Skeleton::onInitialization() {
        glViewport(0, 0, windowWidth, windowHeight);


    }

    // Window has become invalid: Redraw
    void Skeleton::onDisplay() {

    }

    // Key of ASCII code pressed
    void Skeleton::onKeyboard(unsigned char key, int pX, int pY) {
        if (key == 'd') glutPostRedisplay();         // if d, invalidate display, i.e. redraw
    }

    // Key of ASCII code released
    void Skeleton::onKeyboardUp(unsigned char key, int pX, int pY) {
    }

    // Move mouse with key pressed
    void Skeleton::onMouseMotion(int pX, int pY) {	// pX, pY are the pixel coordinates of the cursor in the coordinate system of the operation system
        // Convert to normalized device space
        float cX = 2.0f * pX / windowWidth - 1;	// flip y axis
        float cY = 1.0f - 2.0f * pY / windowHeight;
        printf("Mouse moved to (%3.2f, %3.2f)\n", cX, cY);
    }

    // Mouse click event
    void Skeleton::onMouse(int button, int state, int pX, int pY) { // pX, pY are the pixel coordinates of the cursor in the coordinate system of the operation system
        // Convert to normalized device space
        float cX = 2.0f * pX / windowWidth - 1;	// flip y axis
        float cY = 1.0f - 2.0f * pY / windowHeight;

        char * buttonStat;
        switch (state) {
            case GLUT_DOWN: buttonStat = "pressed"; break;
            case GLUT_UP:   buttonStat = "released"; break;
        }

        switch (button) {
            case GLUT_LEFT_BUTTON:   printf("Left button %s at (%3.2f, %3.2f)\n", buttonStat, cX, cY);   break;
            case GLUT_MIDDLE_BUTTON: printf("Middle button %s at (%3.2f, %3.2f)\n", buttonStat, cX, cY); break;
            case GLUT_RIGHT_BUTTON:  printf("Right button %s at (%3.2f, %3.2f)\n", buttonStat, cX, cY);  break;
        }
    }

    // Idle event indicating that some time elapsed: do animation here
    void Skeleton::onIdle() {
        long time = glutGet(GLUT_ELAPSED_TIME); // elapsed time since the start of the program
    }





