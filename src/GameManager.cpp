#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "GameManager.h"
#include "Car.h"
#include "Frog.h"
#include "River.h"
#include "Road.h"
#include "Riverside.h"
#include "Roadside.h"
#include "TimberLog.h"
#include "OrthogonalCamera.h"
#include "PerspectiveCamera.h"
#include "PointLight.h"
#include "DirectedLight.h"
#include "BMPReader.h"

const int top = 0;
const int bot = 1;
const int right = 2;
const int left = 3;


float frogXmax;
float frogXmin;
float frogYmax;
float frogYmin;

float carXmax;
float carXmin;
float carYmax;
float carYmin;

float logXmax;
float logXmin;
float logYmax;
float logYmin;

int asd = 0;

double rotate_x = 0.0;
double rotate_y = 0.0;
double rotate_z = 0.0;


GameManager::GameManager() : _map(5, 0), _cars(15, 0), _logs(15, 0), _cameras(3, 0), _light_sources(8, 0) {
	_speedCar.set(-0.001, 0.0, 0.0);
	_speedLog.set(-0.001, 0.0, 0.0);
}

GameManager::~GameManager() {
	delete _frog;
	delete _active;
}

void GameManager::CreateMap() {
	River* river = new River();
	_map.push_back(river);
	Road* road = new Road();
	_map.push_back(road);
	Roadside* roadside = new Roadside();
	_map.push_back(roadside);
	Riverside* riverside = new Riverside();
	_map.push_back(riverside);
	_limits[right] = 21.5;
	_limits[left] = -0.5;
	_limits[top] = 14.0;
	_limits[bot] = -0.5;
	_limitsRiver[top] = 12.5;
	_limitsRiver[bot] = 7.6;
	glEnable(GL_TEXTURE_2D);
	_textures.push_back(LoadTexture("river.bmp"));
	_textures.push_back(LoadTexture("road.bmp"));
	_textures.push_back(LoadTexture("roadside.bmp"));
	_textures.push_back(LoadTexture("riverside.bmp"));
	_textures.push_back(LoadTexture("pause.bmp"));
	_textures.push_back(LoadTexture("gameover.bmp"));
	glDisable(GL_TEXTURE_2D);
}

void GameManager::DrawMap() {
	std::vector<GameObject*>::iterator map_it = _map.begin();
	int i = 0;
	for (map_it = _map.begin(); map_it != _map.end(); map_it++) {
		if ((*map_it) != NULL) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textures[i]);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			(*map_it)->draw();
			glDisable(GL_TEXTURE_2D);
			i++;
		}
	}
	
}

void GameManager::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_active->computeProjectionMatrix();
	_active->computeVisualizationMatrix();

	std::vector<GameObject*>::iterator to_draw;
	std::vector<LightSource*>::iterator light_draw;
	glTranslatef(_frog->getPosition()->getX(), _frog->getPosition()->getY(), _frog->getPosition()->getZ());
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_z, 0.0, 0.0, 1.0);
	glTranslatef(-_frog->getPosition()->getX(), -_frog->getPosition()->getY(), -_frog->getPosition()->getZ());
	Car *a;
	TimberLog *t;
	glPushMatrix();
	DrawMap();
	for (to_draw = _cars.begin(); to_draw != _cars.end(); to_draw++) {
		a = static_cast<Car*>(*to_draw);
		if (a->getToDraw()) {
			a->draw();
		}
	}
	for (to_draw = _logs.begin(); to_draw != _logs.end(); to_draw++) {
		t = static_cast<TimberLog*>(*to_draw);
		if (t->getToDraw()) {
			t->draw();
		}
	}
	_frog->draw();
	for (light_draw = _light_sources.begin(); light_draw != _light_sources.end() - 1; light_draw++) {
		if ((*light_draw) != NULL) {
			(*light_draw)->draw();
			(*light_draw)->shine();
		}
	}
	_light_sources[7]->shine();

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	_hud->computeProjectionMatrix();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	drawLives();

	if (_pause && _nlives > 0) {
		DisplayPauseMessage();
	}
	if (_pause && _nlives <= 0) {
		DisplayGameOverMessage();
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	glutSwapBuffers();
}

void GameManager::reshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
}

void GameManager::keyPressed(unsigned char key, int xmouse, int ymouse) {
	Vector3* pos = _active->getPosition();
	Vector3 inc;

	switch (tolower(key)){
		case 'q':
			_frog->setSpeed(0.0, 0.0075, 0.0);
			_frog->setDirection(0.0, 1.0, 0.0);
			break;

		case 'a':
			_frog->setSpeed(0.0, -0.0075, 0.0);
			_frog->setDirection(0.0, -1.0, 0.0);
			break;

		case 'p':
			_frog->setSpeed(0.0075, 0.0, 0.0);
			_frog->setDirection(1.0, 0.0, 0.0);
			break;

		case 'o':
			_frog->setSpeed(-0.0075, 0.0, 0.0);
			_frog->setDirection(-1.0, 0.0, 0.0);
			break;
		case 's':
			_pause = !_pause;
			break;
		case 'r':
			if (_nlives <= 0 && _pause) {
				this->restart();
			}
			break;
		case 'n':
			if (glIsEnabled(GL_LIGHT0))
				glDisable(GL_LIGHT0);
			else
				glEnable(GL_LIGHT0);
			break;
		case 'c':
			if (glIsEnabled(GL_LIGHT1))
				DisablePointLights();
			else
				EnablePointLights();
			break;
		case 'h':
			if (glIsEnabled(GL_LIGHT7))
				glDisable(GL_LIGHT7);
			else
				glEnable(GL_LIGHT7);
			break;
		case 'l':
			if (glIsEnabled(GL_LIGHTING))
				glDisable(GL_LIGHTING);
			else
				glEnable(GL_LIGHTING);
			break;
		case '1':
			_active = _cameras[0];
			break;
		case '2':
			_active = _cameras[1];
			break;
		case '3':
			_active = _cameras[2];
			break;
		default:
			break;
	}
}

void GameManager::specialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_RIGHT)
		rotate_z += 10;
	if (key == GLUT_KEY_LEFT)
		rotate_z -= 10;
	else if (key == GLUT_KEY_UP)
		rotate_x += 10;
	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 10;
}

void GameManager::keyUp(unsigned char key, int xmouse, int ymouse) {
	_frog->setSpeed(0.0, 0.0, 0.0);
}

void GameManager::onTimer() {

}

void GameManager::idle() {
	_elapsed = glutGet(GLUT_ELAPSED_TIME);
	_delta_t = _elapsed - _elap;
	_elap = _elapsed;
	int x = static_cast<int>(_elapsed);
	if (x % 10000 == 0) {
		increaseSpeed(1.5);
	}
	updateObjTimers(_delta_t);
	if (_nlives <= 0) {
		_pause = true;
	}
	if (!_pause) {
		this->update();
	}
	glutPostRedisplay();
}

void GameManager::increaseSpeed(double fraction) {
	std::vector<GameObject*>::iterator it;
	Vector3 speed;
	Car* a;
	TimberLog* b;
	for (it = _cars.begin(); it != _cars.end(); it++) {
		a = static_cast<Car*>(*it);
		speed = a->getSpeed();
		speed*fraction;
		a->setSpeed(speed);
	}
	for (it = _logs.begin(); it != _logs.end(); it++) {
		b = static_cast<TimberLog*>(*it);
		speed = b->getSpeed();
		speed*fraction;
		b->setSpeed(speed);
	}
}

void GameManager::updateObjTimers(double time) {
	std::vector<GameObject*>::iterator i;
	int timer;
	Car *a;
	TimberLog *t;
	for (i = _cars.begin(); i != _cars.end(); i++) {
		a = static_cast<Car*>(*i);
		timer = a->getTimer();
		if (timer >= 0) {
			timer -= time;
			a->setTimer(timer);
			if (timer <= 0) {
				a->setToDraw(true);
			}
		}
	}

	for (i = _logs.begin(); i != _logs.end(); i++) {
		t = static_cast<TimberLog*>(*i);
		timer = t->getTimer();
		timer -= time;
		t->setTimer(timer);
		if (timer >= 0) {
			timer -= time;
			t->setTimer(timer);
			if (timer <= 0) {
				t->setToDraw(true);
			}
		}
	}
}

void GameManager::update() {
	this->update_cars();
	this->update_frog();
	this->update_logs();
}

void GameManager::update_cars() {
	Vector3 *pos;
	std::vector<GameObject*>::iterator to_up;
	Car *a;
	for (to_up = _cars.begin(); to_up != _cars.end(); to_up++) {
		a = static_cast<Car*>(*to_up);
		if (a->getToDraw()) {
			a->update(_delta_t);
			if ((a->getPosition()->getX() <= -0.5) && (a->getDirection() == left)) {
				pos = a->getPosition();
				a->setToDraw(false);
				a->setTimer(rand() % 1000);
				float t = rand() % 7 + 1;
				a->setPosition(21.8 + t, pos->getY(), pos->getZ());
			}
			else if ((a->getPosition()->getX() >= 21.8) && (a->getDirection() == right)) {
				pos = a->getPosition();
				a->setToDraw(false);
				a->setTimer(rand() % 1000);
				double t = rand() % 7 + 1;
				a->setPosition(-0.5 - t, pos->getY(), pos->getZ());
			}
		}
	}
}

void GameManager::update_frog() {
	_frog->update(_delta_t);
	Vector3* frog_pos = _frog->getPosition();
	Vector3* direction = _frog->getDirection();
	_cameras[2]->setPosition(frog_pos->getX(), frog_pos->getY() - 5, frog_pos->getZ() + 4);
	_cameras[2]->setAt(frog_pos->getX(), frog_pos->getY() + 5, frog_pos->getZ());
	_cameras[2]->setUp(0.0, 0.0, 1.0);

	_light_sources[7]->setPosition(new Vector4(frog_pos->getX(), frog_pos->getY(), frog_pos->getZ() + 1.0, 1.0));

	if (direction->getY() == 1.0){
		_light_sources[7]->setDirection(new Vector4(0.0f, 5.0f, -1.0f, 0.0f));
	}
	else if (direction->getY() == -1.0){
		_light_sources[7]->setDirection(new Vector4(0.0f, -5.0f, -1.0f, 0.0f));
	}
	else if (direction->getX() == 1.0){
		_light_sources[7]->setDirection(new Vector4(5.0f, 0.0f, -1.0f, 0.0f));
	}
	else if (direction->getX() == -1.0){
		_light_sources[7]->setDirection(new Vector4(-5.0f, 0.0f, -1.0f, 0.0f));
	}
	
	this->testCollisionsLimits();
	if (!this->standOnLog()) {
		this->testCollisionsRiver();
		this->testCollisionsCars();
	}
}

void GameManager::testCollisionsLimits() {
	Vector3* pos = _frog->getPosition();
	if (pos->getX() + 0.75 > _limits[right]) {
		pos->set(_limits[right] - 0.75, pos->getY(), pos->getZ());
		_frog->setPosition(*pos);
		_frog->setSpeed(0.0, 0.0, 0.0);
	}
	if (pos->getX() - 0.75< _limits[left]) {
		pos->set(_limits[left] + 0.75, pos->getY(), pos->getZ());
		_frog->setPosition(*pos);
		_frog->setSpeed(0.0, 0.0, 0.0);
	}
	if (pos->getY() + 0.75> _limits[top]) {
		pos->set(pos->getX(), _limits[top] - 0.75, pos->getZ());
		_frog->setPosition(*pos);
		_frog->setSpeed(0.0, 0.0, 0.0);
	}
	if (pos->getY() - 0.75 < _limits[bot]) {
		pos->set(pos->getX(), _limits[bot] + 0.75, pos->getZ());
		_frog->setPosition(*pos);
		_frog->setSpeed(0.0, 0.0, 0.0);
	}
}

void GameManager::testCollisionsRiver() {
	Vector3* pos = _frog->getPosition();
	if ((pos->getY() - 0.75 < _limitsRiver[top]) && (pos->getY() + 0.75 > _limitsRiver[bot])) {
		pos->set(10.5, 0.5, 0.0);
		_nlives--;
		_frog->setPosition(*pos);
		_frog->setDirection(new Vector3(0.0, 1.0, 0.0));
	}
}

bool GameManager::standOnLog() {
	Vector3* pos_frog = _frog->getPosition();
	Vector3* pos_log;
	TimberLog* log;
	std::vector<GameObject*>::iterator to_up;
	for (to_up = _logs.begin(); to_up != _logs.end(); to_up++) {
		if ((*to_up) != NULL) {
			pos_log = (*to_up)->getPosition();
			log = (TimberLog*)(*to_up);

			frogXmax = pos_frog->getX() + 0.25;
			frogXmin = pos_frog->getX() - 0.25;
			frogYmax = pos_frog->getY() + 0.25;
			frogYmin = pos_frog->getY() - 0.25;

			logXmax = pos_log->getX() + 1.75;
			logXmin = pos_log->getX() - 1.75;
			logYmax = pos_log->getY() + 0.95;
			logYmin = pos_log->getY() - 0.95;
			if ((frogXmax <= logXmax) && (frogXmin >= logXmin)) {
				if ((frogYmax <= logYmax) && (frogYmin >= logYmin)) {
					_frog->setSpeed(log->getSpeed());
					return true;
				}
			}
		}
	}
	return false;
	//x+1.76
	//x-1.75
	//y+0.96
	//y-0.95
}

void GameManager::testCollisionsCars() {

	Vector3* pos_frog = _frog->getPosition();
	Vector3* pos_car;
	std::vector<GameObject*>::iterator to_up2;
	for (to_up2 = _cars.begin(); to_up2 != _cars.end(); to_up2++) {
		if ((*to_up2) != NULL) {
			pos_car = (*to_up2)->getPosition();
			frogXmax = pos_frog->getX() + 0.25;
			frogXmin = pos_frog->getX() - 0.25;
			frogYmax = pos_frog->getY() + 0.25;
			frogYmin = pos_frog->getY() - 0.25;

			carXmax = pos_car->getX() + 0.7;
			carXmin = pos_car->getX() - 0.7;
			carYmax = pos_car->getY() + 0.38;
			carYmin = pos_car->getY() - 0.38;

			if (((frogXmin >= carXmin) && (frogXmin <= carXmax) && (frogYmax >= carYmin) && (frogYmax <= carYmax)) ||
				((frogXmax >= carXmin) && (frogXmax <= carXmax) && (frogYmax >= carYmin) && (frogYmax <= carYmax)) ||
				((frogXmin >= carXmin) && (frogXmin <= carXmax) && (frogYmin >= carYmin) && (frogYmin <= carYmax)) ||
				((frogXmax >= carXmin) && (frogXmax <= carXmax) && (frogYmin >= carYmin) && (frogYmin <= carYmax)))
			{

				pos_frog->set(10.5, 0.5, 0.0);
				_nlives--;
				_frog->setPosition(*pos_frog);
				_frog->setDirection(new Vector3(0.0, 1.0, 0.0));
			}
		}
	}
}

void GameManager::update_logs() {
	std::vector<GameObject*>::iterator to_up;
	TimberLog* t;
	Vector3* pos;
	for (to_up = _logs.begin(); to_up != _logs.end(); to_up++) {
		t = static_cast<TimberLog*>(*to_up);
		if (t->getToDraw()) {
			t->update(_delta_t);
			if (t->getPosition()->getX() + 1.75 <= 0.0 && t->getDirection() == left) {
				pos = t->getPosition();
				t->setToDraw(false);
				t->setTimer(rand() % 1000);
				float post = rand() % 7 + 1;
				t->setPosition(22.3 + post, pos->getY(), pos->getZ());
			}
			else if (t->getPosition()->getX() >= 22.3 && t->getDirection() == right) {
				pos = t->getPosition();
				t->setToDraw(false);
				t->setTimer(rand() % 1000);
				float post = rand() % 7 + 1;
				t->setPosition(-1.75 - post, pos->getY(), pos->getZ());
			}
		}
	}
}

const unsigned int GameManager::LoadTexture(const std::string & textureFilename)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	BMPloader * bitmap = new BMPloader(textureFilename);
	if (bitmap->Isvalid())
	{
		glPixelStoref(GL_UNPACK_ALIGNMENT, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap->Width(), bitmap->Heigth(), 0, GL_RGB,
			GL_UNSIGNED_BYTE, bitmap->Image());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	delete bitmap;
	return textureID;
}

void GameManager::DisplayGameOverMessage() {
	glColor3f(0.0, 0.0, 0.0);
	const GLfloat grey[4] = { .3, .3, .3, 1.f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	const GLfloat white[4] = { 0.508273f, 0.508273f, 0.508273f, 1.f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.2f * 128);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, _textures[5]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(6.0, 3.25, 3.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(15.0, 3.25, 3.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(15.0, 9.75, 3.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(6.0, 9.75, 3.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void GameManager::DisplayPauseMessage() {
	glColor3f(0.0, 0.0, 0.0);
	const GLfloat grey[4] = { .3, .3, .3, 1.f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	const GLfloat white[4] = { 0.508273f, 0.508273f, 0.508273f, 1.f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.2f * 128);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, _textures[4]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(6.0, 3.25, 3.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(15.0, 3.25, 3.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(15.0, 9.75, 3.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(6.0, 9.75, 3.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void GameManager::drawLives() {
	std::vector<double> pos;
	pos.push_back(4);
	pos.push_back(12);
	pos.push_back(20);
	pos.push_back(28);
	pos.push_back(36);
	for (int i = 0; i < _nlives; i++) {
		drawHead(pos[i]);
	}
}

void GameManager::drawHead(double x) {
	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);
	glTranslatef(x, 2.0, 0.0);
	//head
	glPushMatrix();
	glTranslatef(0.0, 2.0, 0.0);
	glScalef(3.0, 2.0, 2.0);
	glColor3f(0.2, 0.5, 0.2);
	GLfloat headamb[] = { 0.2f, 0.5f, 0.2f, 1.0f };
	GLfloat headdiff[] = { 0.2f, 0.5f, 0.2f, 1.0f };
	GLfloat headspec[] = { 0.2f, 0.5f, 0.2f, 1.0f };
	GLfloat headshine = 76.8f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, headamb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, headdiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, headspec);
	glMaterialf(GL_FRONT, GL_SHININESS, headshine);
	glutSolidSphere(1.0, 8.0, 8.0);
	glPopMatrix();

	//eyeL
	glColor3f(1.0, 1.0, 1.0);
	GLfloat eyeamb[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat eyediff[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat eyespec[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat eyeshine = 76.8f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, eyeamb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, eyediff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, eyespec);
	glMaterialf(GL_FRONT, GL_SHININESS, eyeshine);
	glPushMatrix();
	glTranslatef(-2.0, 3.0, 1.0);
	glutSolidSphere(0.9, 30.0, 30.0);
	glPushMatrix();
	glTranslatef(0.0, 0.1, 0.0);
	glutSolidSphere(0.5, 30.0, 30.0);
	glPopMatrix();
	glPopMatrix();

	//eyeR
	glPushMatrix();
	glTranslatef(2.0, 3.0, 1.0);
	glutSolidSphere(0.9, 30.0, 30.0);
	glPushMatrix();
	glTranslatef(0.0, 0.1, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.5, 30.0, 30.0);
	glColor3f(0.2, 0.6, 0.2);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}


void GameManager::init() {
	Vector3 frog_pos;
	frog_pos.set(10.5, 0.5, 0.0);
	_elap = 0;
	CreateMap();
	_frog = new Frog();
	_frog->setPosition(frog_pos);
	_frog->setDirection(new Vector3(0.0, 1.0, 0.0));

	_pause = false;
	_nlives = 5;
	_hud = new OrthogonalCamera(0.0, 21.0, 0.0, 13.5, -10.0, 10.0);
	_cameras[0] = new OrthogonalCamera(0.0, 21.0, 0.0, 13.5, -10.0, 10.0);
	double aspect = 860 / 555;
	_cameras[1] = new PerspectiveCamera(45.0, aspect, 1.0, 100.0);
	_cameras[1]->setPosition(11.0, -15.0, 22.0);
	_cameras[1]->setAt(11.0, 5.0, 0.0);
	_cameras[1]->setUp(0.0, 4.0, 4.0);
	_cameras[2] = new PerspectiveCamera(70.0, aspect, 1.0, 100.0);
	_cameras[2]->setPosition(frog_pos.getX(), frog_pos.getY() - 5, frog_pos.getZ() + 4);
	_cameras[2]->setAt(frog_pos.getX() - 7, frog_pos.getY() + 5, frog_pos.getZ());
	_cameras[2]->setUp(0.0, 0.0, 1.0);
	_active = _cameras[0];
	srand(time(NULL));
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	GLfloat amb[] = { 0.0f, 0.0f, 0.0f, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	_light_sources[0] = new DirectedLight(GL_LIGHT0);
	_light_sources[0]->setAmbient(new Vector4(0.7f, 0.7f, 0.7f, 1.0f));
	_light_sources[0]->setDiffuse(new Vector4(0.3f, 0.3f, 0.3f, 1.0f));
	_light_sources[0]->setSpecular(new Vector4(0.0f, 0.0f, 0.0f, 1.0f));
	_light_sources[0]->setDirection(new Vector4(0.0f, 0.0f, -1.0f, 0.0f));

	_light_sources[1] = new PointLight(GL_LIGHT1);
	_light_sources[1]->setPosition(new Vector4(6.0f, 0.5f, 1.7f, 1.0f));

	_light_sources[2] = new PointLight(GL_LIGHT2);
	_light_sources[2]->setPosition(new Vector4(15.0f, 0.5f, 1.7f, 1.0f));

	_light_sources[3] = new PointLight(GL_LIGHT3);
	_light_sources[3]->setPosition(new Vector4(6.0f, 6.5f, 1.7f, 1.0f));

	_light_sources[4] = new PointLight(GL_LIGHT4);
	_light_sources[4]->setPosition(new Vector4(15.0f, 6.5f, 1.7f, 1.0f));

	_light_sources[5] = new PointLight(GL_LIGHT5);
	_light_sources[5]->setPosition(new Vector4(6.0f, 13.0f, 1.7f, 1.0f));

	_light_sources[6] = new PointLight(GL_LIGHT6);
	_light_sources[6]->setPosition(new Vector4(15.0f, 13.0f, 1.7f, 1.0f));

	_light_sources[7] = new PointLight(GL_LIGHT7);
	_light_sources[7]->setPosition(new Vector4(frog_pos.getX(), frog_pos.getY(), frog_pos.getZ() + 1.0, 1.0));
	_light_sources[7]->setAmbient(new Vector4(0.1f, 0.1f, 0.1f, 1.0f));
	_light_sources[7]->setDiffuse(new Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	_light_sources[7]->setSpecular(new Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	_light_sources[7]->setDirection(new Vector4(0.0f, 5.0f, -10.0f, 0.0f));
	_light_sources[7]->setCutOff(45.0);
	_light_sources[7]->setExponent(10);

	for (int i = 1; i < 7; i++) {
		_light_sources[i]->setAmbient(new Vector4(0.45f, 0.45f, 0.45f, 1.0f));
		_light_sources[i]->setDiffuse(new Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		_light_sources[i]->setSpecular(new Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		_light_sources[i]->setDirection(new Vector4(0.0f, 0.0f, -1.0f, 0.0f));
		_light_sources[i]->setCutOff(85.0);
		_light_sources[i]->setExponent(2.1);
	}

	Vector3 _speedCarInv;
	Vector3 _speedLogInv;

	_speedCar.set(-0.003, 0.0, 0.0);
	_speedCarInv.set(0.003, 0.0, 0.0);

	_speedLog.set(-0.003, 0.0, 0.0);
	_speedLogInv.set(0.003, 0.0, 0.0);
	int t = rand() % 1000 + 2000;
	double pos = rand() % 7 + 1;
	_cars[0] = new Car(21.8 + pos, 1.46, 0.0, _speedCar, left, t);
	pos = rand() % 7 + 7;
	_cars[1] = new Car(21.8 + pos, 1.46, 0.0, _speedCar, left, rand() % 1000);
	pos = rand() % 7 + 10;
	_cars[2] = new Car(21.8 + pos, 1.46, 0.0, _speedCar, left, rand() % 1000);

	pos = rand() % 8 + 1;
	_cars[3] = new Car(-0.5 - pos, 2.46, 0.0, _speedCarInv, right, t);
	pos = rand() % 8 + 7;
	_cars[4] = new Car(-0.5 - pos, 2.46, 0.0, _speedCarInv, right, rand() % 1000);
	pos = rand() % 8 + 10;
	_cars[5] = new Car(-0.5 - pos, 2.46, 0.0, _speedCarInv, right, rand() % 1000);

	pos = rand() % 6 + 1;
	_cars[6] = new Car(21.8 + pos, 3.46, 0.0, _speedCar, left, rand() % 1000);
	pos = rand() % 8 + 7;
	_cars[7] = new Car(21.8 + pos, 3.46, 0.0, _speedCar, left, rand() % 1000);
	pos = rand() % 5 + 10;
	_cars[8] = new Car(21.8 + pos, 3.46, 0.0, _speedCar, left, rand() % 1000);

	pos = rand() % 9 + 6;
	_cars[9] = new Car(-0.5 - pos, 4.46, 0.0, _speedCarInv, right, rand() % 1000);
	pos = rand() % 9 + 10;
	_cars[10] = new Car(-0.5 - pos, 4.46, 0.0, _speedCarInv, right, rand() % 1000);
	pos = rand() % 9 + 15;
	_cars[11] = new Car(-0.5 - pos, 4.46, 0.0, _speedCarInv, right, rand() % 1000);

	pos = rand() % 5 + 5;
	_cars[12] = new Car(21.8 + pos, 5.46, 0.0, _speedCar, left, rand() % 1000);
	pos = rand() % 5 + 10;
	_cars[13] = new Car(21.8 + pos, 5.46, 0.0, _speedCar, left, rand() % 1000);
	pos = rand() % 5 + 15;
	_cars[14] = new Car(21.8 + pos, 5.46, 0.0, _speedCar, left, rand() % 1000);


	pos = rand() % 5 + 5;
	_logs[0] = new TimberLog(21.8 + pos, 7.5, 0.0, _speedLog, left, rand() % 1000);
	pos = rand() % 5 + 10;
	_logs[1] = new TimberLog(21.8 + pos, 7.5, 0.0, _speedLog, left, rand() % 1000);
	pos = rand() % 5 + 15;
	_logs[2] = new TimberLog(21.8 + pos, 7.5, 0.0, _speedLog, left, rand() % 1000);


	pos = rand() % 7 + 1;
	_logs[3] = new TimberLog(0.0 - pos, 8.5, 0.0, _speedLogInv, right, rand() % 1000);
	pos = rand() % 7 + 14;
	_logs[4] = new TimberLog(0.0 - pos, 8.5, 0.0, _speedLogInv, right, rand() % 1000);
	pos = rand() % 7 + 18;
	_logs[5] = new TimberLog(0.0 - pos, 8.5, 0.0, _speedLogInv, right, rand() % 1000);


	pos = rand() % 6 + 6;
	_logs[6] = new TimberLog(21.8 + pos, 9.5, 0.0, _speedLog, left, rand() % 1000);
	pos = rand() % 6 + 10;
	_logs[7] = new TimberLog(21.8 + pos, 9.5, 0.0, _speedLog, left, rand() % 1000);
	pos = rand() % 6 + 15;
	_logs[8] = new TimberLog(21.8 + pos, 9.5, 0.0, _speedLog, left, rand() % 1000);


	pos = rand() % 4 + 1;
	_logs[9] = new TimberLog(0.0 - pos, 10.5, 0.0, _speedLogInv, right, rand() % 1000);
	pos = rand() % 7 + 5;
	_logs[10] = new TimberLog(0.0 - pos, 10.5, 0.0, _speedLogInv, right, rand() % 1000);
	pos = rand() % 7 + 10;
	_logs[11] = new TimberLog(0.0 - pos, 10.5, 0.0, _speedLogInv, right, rand() % 1000);


	pos = rand() % 5 + 2;
	_logs[12] = new TimberLog(21.8 + pos, 11.5, 0.0, _speedLog, left, rand() % 1000);
	pos = rand() % 5 + 10;
	_logs[13] = new TimberLog(21.8 + pos, 11.5, 0.0, _speedLog, left, rand() % 1000);
	pos = rand() % 7 + 9;
	_logs[14] = new TimberLog(21.8 + pos, 11.5, 0.0, _speedLog, left, rand() % 1000);
}

void GameManager::DisablePointLights() {
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);
	glDisable(GL_LIGHT5);
	glDisable(GL_LIGHT6);
}

void GameManager::EnablePointLights() {
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_LIGHT6);
}

void GameManager::restart() {
	Vector3 frog_pos;
	frog_pos.set(10.5, 0.5, 0.0);
	_frog->setPosition(frog_pos);
	_frog->setDirection(new Vector3(0.0, 1.0, 0.0));

	_active = _cameras[0];
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);
	glDisable(GL_LIGHT5);
	glDisable(GL_LIGHT6);
	glDisable(GL_LIGHT7);

	_pause = false;
	_nlives = 5;

	glClearColor(0.0, 0.0, 0.0, 0.0);

	Vector3 _speedCarInv;
	Vector3 _speedLogInv;

	_speedCar.set(-0.003, 0.0, 0.0);
	_speedCarInv.set(0.003, 0.0, 0.0);

	_speedLog.set(-0.003, 0.0, 0.0);
	_speedLogInv.set(0.003, 0.0, 0.0);

	int t = rand() % 1000 + 2000;
	double pos = rand() % 7 + 1;

	_cars[0] = new Car(21.8 + pos, 1.46, 0.0, _speedCar, left, t);
	pos = rand() % 7 + 7;
	_cars[1] = new Car(21.8 + pos, 1.46, 0.0, _speedCar, left, rand() % 1000);
	pos = rand() % 7 + 10;
	_cars[2] = new Car(21.8 + pos, 1.46, 0.0, _speedCar, left, rand() % 1000);

	pos = rand() % 8 + 1;
	_cars[3] = new Car(-0.5 - pos, 2.46, 0.0, _speedCarInv, right, t);
	pos = rand() % 8 + 7;
	_cars[4] = new Car(-0.5 - pos, 2.46, 0.0, _speedCarInv, right, rand() % 1000);
	pos = rand() % 8 + 10;
	_cars[5] = new Car(-0.5 - pos, 2.46, 0.0, _speedCarInv, right, rand() % 1000);

	pos = rand() % 6 + 1;
	_cars[6] = new Car(21.8 + pos, 3.46, 0.0, _speedCar, left, rand() % 1000);
	pos = rand() % 8 + 7;
	_cars[7] = new Car(21.8 + pos, 3.46, 0.0, _speedCar, left, rand() % 1000);
	pos = rand() % 5 + 10;
	_cars[8] = new Car(21.8 + pos, 3.46, 0.0, _speedCar, left, rand() % 1000);

	pos = rand() % 9 + 6;
	_cars[9] = new Car(-0.5 - pos, 4.46, 0.0, _speedCarInv, right, rand() % 1000);
	pos = rand() % 9 + 10;
	_cars[10] = new Car(-0.5 - pos, 4.46, 0.0, _speedCarInv, right, rand() % 1000);
	pos = rand() % 9 + 15;
	_cars[11] = new Car(-0.5 - pos, 4.46, 0.0, _speedCarInv, right, rand() % 1000);

	pos = rand() % 5 + 5;
	_cars[12] = new Car(21.8 + pos, 5.46, 0.0, _speedCar, left, rand() % 1000);
	pos = rand() % 5 + 10;
	_cars[13] = new Car(21.8 + pos, 5.46, 0.0, _speedCar, left, rand() % 1000);
	pos = rand() % 5 + 15;
	_cars[14] = new Car(21.8 + pos, 5.46, 0.0, _speedCar, left, rand() % 1000);


	pos = rand() % 5 + 5;
	_logs[0] = new TimberLog(21.8 + pos, 7.5, 0.0, _speedLog, left, rand() % 1000);
	pos = rand() % 5 + 10;
	_logs[1] = new TimberLog(21.8 + pos, 7.5, 0.0, _speedLog, left, rand() % 1000);
	pos = rand() % 5 + 15;
	_logs[2] = new TimberLog(21.8 + pos, 7.5, 0.0, _speedLog, left, rand() % 1000);


	pos = rand() % 7 + 1;
	_logs[3] = new TimberLog(0.0 - pos, 8.5, 0.0, _speedLogInv, right, rand() % 1000);
	pos = rand() % 7 + 14;
	_logs[4] = new TimberLog(0.0 - pos, 8.5, 0.0, _speedLogInv, right, rand() % 1000);
	pos = rand() % 7 + 18;
	_logs[5] = new TimberLog(0.0 - pos, 8.5, 0.0, _speedLogInv, right, rand() % 1000);


	pos = rand() % 6 + 6;
	_logs[6] = new TimberLog(21.8 + pos, 9.5, 0.0, _speedLog, left, rand() % 1000);
	pos = rand() % 6 + 10;
	_logs[7] = new TimberLog(21.8 + pos, 9.5, 0.0, _speedLog, left, rand() % 1000);
	pos = rand() % 6 + 15;
	_logs[8] = new TimberLog(21.8 + pos, 9.5, 0.0, _speedLog, left, rand() % 1000);


	pos = rand() % 4 + 1;
	_logs[9] = new TimberLog(0.0 - pos, 10.5, 0.0, _speedLogInv, right, rand() % 1000);
	pos = rand() % 7 + 5;
	_logs[10] = new TimberLog(0.0 - pos, 10.5, 0.0, _speedLogInv, right, rand() % 1000);
	pos = rand() % 7 + 10;
	_logs[11] = new TimberLog(0.0 - pos, 10.5, 0.0, _speedLogInv, right, rand() % 1000);


	pos = rand() % 5 + 2;
	_logs[12] = new TimberLog(21.8 + pos, 11.5, 0.0, _speedLog, left, rand() % 1000);
	pos = rand() % 5 + 10;
	_logs[13] = new TimberLog(21.8 + pos, 11.5, 0.0, _speedLog, left, rand() % 1000);
	pos = rand() % 7 + 9;
	_logs[14] = new TimberLog(21.8 + pos, 11.5, 0.0, _speedLog, left, rand() % 1000);
}
