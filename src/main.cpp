#include <stdlib.h>
#include <gl/glut.h>
#include <iostream>
#include "GameManager.h"

GameManager g;

void keyboard (unsigned char key, int xmouse, int ymouse) {	
	g.keyPressed(key, xmouse, ymouse);
}

void keyUp(unsigned char key, int xmouse, int ymouse) {
	g.keyUp(key, xmouse, ymouse);
}
 
void display(void) {
	g.display();
}

 
void reshape(GLsizei w, GLsizei h) {
	g.reshape(w, h);
}

void timer(int n) {
	int t = rand() % 400 + 100;
	g.onTimer();
	glutTimerFunc(t, timer, 0);
}

void idle() {
	g.idle();
}

void specialkeys(int key, int x, int y) {
	g.specialKeys(key, x, y);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (860, 555); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Frogger - grupo 19");
	g.init();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(specialkeys);
	glutTimerFunc(0, timer, 0);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}