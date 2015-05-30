#include "Riverside.h"
#include <gl/glut.h>

Riverside::Riverside() {}

Riverside::~Riverside() {}

void Riverside::draw() {
	glPushMatrix();
	glColor3f(0.119608, 0.756863, 0.137255);
	GLfloat riversideamb[] = { 0.11f, 0.75f, 0.13f, 1.0f };
	GLfloat riversidediff[] = { 0.56f, 0.71f, 0.61f, 1.0f };
	GLfloat riversidespec[] = { 0.42f, 0.75f, 0.58f, 1.0f };
	GLfloat riversideshine = 128;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, riversideamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, riversidediff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, riversidespec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, riversideshine);
	for (double y = 12.0; y < 14.0; y += 0.5) {
		for (double x = 0.0; x < 21.0; x += 0.5) {
			glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(x, y, 0.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x + 0.5, y, 0.0);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(x + 0.5, y + 0.5, 0.0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(x, y + 0.5, 0.0);
			glEnd();
		}
	}
	glPopMatrix();
}