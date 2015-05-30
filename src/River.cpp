#include "River.h"
#include <gl/glut.h>

River::River() {}

River::~River() {}

void River::draw() {
	glPushMatrix();
	glColor3f(0.254902, 0.411765, 1.0);
	GLfloat riveramb[] = { 0.31f, 0.49f, 0.79f, 1.0f };
	GLfloat riverdiff[] = { 0.62f, 0.62f, 0.61f, 1.0f };
	GLfloat riverspec[] = { 0.66f, 0.68f, 0.66f, 1.0f };
	GLfloat rivershine = 128;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, riveramb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, riverdiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, riverspec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, rivershine);
	for (double y = 7.0; y < 12.0; y += 0.25) {
		for (double x = 0.0; x < 21.0; x += 0.25) {
			glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(x, y, 0.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x+0.25, y, 0.0);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(x+0.25, y+0.25, 0.0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(x, y+0.25, 0.0);
			glEnd();
		}
	}
	glPopMatrix();
}

