#include <GL/glew.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    cout << "Hello world!" << endl;
    CV_WINDOW_FULLSCREEN;
	glutInit(&argc, argv);
	glutInitWindowSize(1024, 768);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("GLUT example");
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Register callbacks:
	glutDisplayFunc(onDraw);
	glutReshapeFunc(onSizeChanged);
	glutSpecialFunc(onKeyCodePressed);
	glutIdleFunc(onUpdate);
	glutKeyboardFunc(onKeyPressed);
	glutKeyboardUpFunc(onKeyReleased);
	glutPassiveMotionFunc(onMouseMovedPassive);

	physicsWorld.setSleepLinearVelocity(2.5f);
	physicsWorld.setSleepAngularVelocity(1.0f);

	BitmapTextLoader::defaultFont = new BitmapTextLoader();

	GameStateManager::getInstance()->changeState(new MenuState(physicsWorld));

	// Turn the flow of control over to GLUT
	glutMainLoop();
    return 0;
}