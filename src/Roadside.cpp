#include "Roadside.h"
#include <gl/glut.h>

Roadside::Roadside() {}

Roadside::~Roadside() {}

void Roadside::draw() {
	glPushMatrix();
	glColor3f(0.658824, 0.658824, 0.658824);
	GLfloat roadsideamb[] = { 0.48f, 0.48f, 0.47f, 1.0f };
	GLfloat roadsidediff[] = { 0.48f, 0.51f, 0.47f, 1.0f };
	GLfloat roadsidespec[] = { 0.51f, 0.51f, 0.51f, 1.0f };
	GLfloat roadsideshine = 128;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, roadsideamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, roadsidediff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, roadsidespec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, roadsideshine);
	for (double y = 0.0; y < 1.0; y++) {
		for (double x = 0.0; x < 21.0; x++) {
			glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(x, y, 0.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x + 1, y, 0.0);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(x + 1, y + 1, 0.0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(x, y + 1, 0.0);
			glEnd();
		}
	}
	for (double y = 6.0; y < 7.0; y++) {
		for (double x = 0.0; x < 21.0; x++) {
			glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(x, y, 0.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x + 1, y, 0.0);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(x + 1, y + 1, 0.0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(x, y + 1, 0.0);
			glEnd();
		}
	}
	glPopMatrix();
}