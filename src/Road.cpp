#include "Road.h"
#include <gl/glut.h>

Road::Road() {}

Road::~Road() {}

void Road::draw() {
	glPushMatrix();
	glColor3f(0.329412, 0.329412, 0.329412);
	GLfloat roadamb[] = { 0.28f, 0.28f, 0.28f, 1.0f };
	GLfloat roaddiff[] = { 0.26f, 0.26f, 0.26f, 1.0f };
	GLfloat roadspec[] = { 0.24f, 0.24f, 0.24f, 1.0f };
	GLfloat roadshine = 128;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, roadamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, roaddiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, roadspec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, roadshine);
	for (double y = 1.0; y < 6.0; y += 0.5) {
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