//=============================================================================================
// Collection of classes from lecture slides.
// Framework for assignments. Valid from 2019.
// Do not change it if you want to submit a homework.
//=============================================================================================
#include "Skeleton.h"


Skeleton* skeleton = new Skeleton();

// Entry point of the application
int main(int argc, char * argv[]) {
	// Initialize GLUT, Glew and OpenGL 
	glutInit(&argc, argv);

	// OpenGL major and minor versions
	int majorVersion = 3, minorVersion = 3;
#if !defined(__APPLE__)
	glutInitContextVersion(majorVersion, minorVersion);
#endif
	glutInitWindowSize(windowWidth, windowHeight);				// Application window is initially of resolution 800x800
	glutInitWindowPosition(400, 100);							// Relative location of the application window
#if defined(__APPLE__)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);  // 8 bit R,G,B,A + double buffer + depth buffer
#else
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
#endif
	glutCreateWindow("Ray Tracing");

#if !defined(__APPLE__)
	glewExperimental = true;	// magic
	glewInit();
#endif
	printf("GL Vendor    : %s\n", glGetString(GL_VENDOR));
	printf("GL Renderer  : %s\n", glGetString(GL_RENDERER));
	printf("GL Version (string)  : %s\n", glGetString(GL_VERSION));
	glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
	printf("GL Version (integer) : %d.%d\n", majorVersion, minorVersion);
	printf("GLSL Version : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	// Initialize this program and create shaders
    skeleton->onInitialization();

    // Register onDisplay function
    glutDisplayFunc([]() { skeleton->onDisplay(); });

    // Register onMouse function
    glutMouseFunc([](int button, int state, int x, int y) { skeleton->onMouse(button, state, x, y); });

    // Register onIdle function
    glutIdleFunc([]() { skeleton->onIdle(); });

    // Register onKeyboard function
    glutKeyboardFunc([](unsigned char key, int x, int y) { skeleton->onKeyboard(key, x, y); });

    // Register onKeyboardUp function
    glutKeyboardUpFunc([](unsigned char key, int x, int y) { skeleton->onKeyboardUp(key, x, y); });

    // Register onMouseMotion function
    glutMotionFunc([](int x, int y) { skeleton->onMouseMotion(x, y); });

	glutMainLoop();
	return 1;
}
