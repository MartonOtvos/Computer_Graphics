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

#include "Skeleton.h"

// vertex shader in GLSL: It is a Raw string (C++11) since it contains new line characters
    static const char * const vertexSource = R"(
        #version 330
        precision highp float;

        uniform mat4 MVP;
        layout(location = 0) in vec2 vp;

        void main() {
            gl_Position = vec4(vp.x, vp.y, 0, 1) * MVP;

        }
    )";

    // fragment shader in GLSL
    static const char * const fragmentSource = R"(
        #version 330
        precision highp float;

        uniform vec3 color;
        out vec4 outColor;

        void main() {
            outColor = vec4(color, 1);
        }
    )";

    Skeleton::Skeleton() : vertexShader(vertexSource), fragmentShader(fragmentSource) {}

    // Initialization, create an OpenGL context
    void Skeleton::onInitialization() {
        glViewport(0, 0, windowWidth, windowHeight);
        InitializeShaderProgram();
        Camera = new Camera2D(vec2(30,30),vec2(0,0));
        glPointSize(10);
        glLineWidth(2);

        curve = new CatmullRomSpline(shaderProgram);

    }

    void Skeleton::InitializeShaderProgram(){
        unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertShader, 1, (const GLchar**)&vertexShader, NULL);
        glCompileShader(vertShader);

        unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragShader, 1, (const GLchar**)&fragmentShader, NULL);
        glCompileShader(fragShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertShader);
        glAttachShader(shaderProgram, fragShader);

        glBindFragDataLocation(shaderProgram, 0, "outColor");

        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);
    }


    // Window has become invalid: Redraw
    void Skeleton::onDisplay() {
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);

        curve->Draw(Camera->View(),Camera->Projection());

        glutSwapBuffers();
    }

    // Key of ASCII code pressed
    void Skeleton::onKeyboard(unsigned char key, int pX, int pY) {
        switch(key){
            case 'l': delete curve; curve = new LagrangeCurve(shaderProgram); animationEnabled = false; break;

            case 'b': delete curve; curve = new BezierCurve(shaderProgram); animationEnabled = false; break;

            case 'c': delete curve; curve = new CatmullRomSpline(shaderProgram); animationEnabled = false; break;

            case 't': curve->AlterTension(-0.1); break;
            case 'T': curve->AlterTension(0.1); break;

            case 'z': Camera->Zoom(1/1.1f); break;
            case 'Z': Camera->Zoom(1.1f);break;

            case 'p': Camera->Pan(-1); break;
            case 'P': Camera->Pan(1); break;

            case 'a': animationEnabled = true; break;
            case 'A': animationEnabled = false; break;
            default: break;
        }
        glutPostRedisplay();
    }

    // Key of ASCII code released
    void Skeleton::onKeyboardUp(unsigned char key, int pX, int pY) {}

    // Move mouse with key pressed
    void Skeleton::onMouseMotion(int pX, int pY) {	// pX, pY are the pixel coordinates of the cursor in the coordinate system of the operation system
        // Convert to normalized device space
        float cX = 2.0f * pX / windowWidth - 1;	// flip y axis
        float cY = 1.0f - 2.0f * pY / windowHeight;
        vec4 c = vec4(cX,cY,0,1) * Camera->InverseProjection() * Camera->InverseView();

        if(!isnan(pickedPoint)) curve->AlterControlPoint(pickedPoint,vec2(c.x,c.y));
        glutPostRedisplay();
    }

    // Mouse click event
    void Skeleton::onMouse(int button, int state, int pX, int pY) { // pX, pY are the pixel coordinates of the cursor in the coordinate system of the operation system
        // Convert to normalized device space
        float cX = 2.0f * pX / windowWidth - 1;	// flip y axis
        float cY = 1.0f - 2.0f * pY / windowHeight;
        vec4 c = vec4(cX,cY,0,1) * Camera->InverseProjection() * Camera->InverseView();

        char * buttonStat = (char*) "placeholder";
        switch (state) {
            case GLUT_DOWN: buttonStat = (char*) "pressed"; break;
            case GLUT_UP:   buttonStat = (char*) "released"; break;
        }

        if(strcmp(buttonStat,"pressed") == 0){
            switch (button) {
                case GLUT_LEFT_BUTTON: curve->AddControlPoint(vec2(c.x,c.y));     break;
                case GLUT_MIDDLE_BUTTON:    break;
                case GLUT_RIGHT_BUTTON: pickedPoint = curve->PickControlPoint(vec2(c.x,c.y));    break;
            }
        }

        if(strcmp(buttonStat,"released") == 0){
            pickedPoint = -1;
        }
        glutPostRedisplay();
    }

    // Idle event indicating that some time elapsed: do animation here
    void Skeleton::onIdle() {
        long time = glutGet(GLUT_ELAPSED_TIME); // elapsed time since the start of the program
        float deltaTime = ((float) time - (float) previousTime) / 1000.0f;
        previousTime = time;

        // Debug prints

        if(animationEnabled){

            curve->AnimatePoint(deltaTime);
            glutPostRedisplay();
        }

    }





