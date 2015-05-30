#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "GameObject.h"
#include "Camera.h"
#include "LightSource.h"
#include "Frog.h"
#include "Vector3.h"
#include <gl/glut.h>
#include <vector>

class GameManager
{
public:
	GameManager();
	~GameManager();
	void display();
	void reshape(GLsizei w, GLsizei h);
	void keyPressed(unsigned char key, int xmouse, int ymouse);
	void onTimer();
	void idle();
	void update();
	void init();
	void keyUp(unsigned char key, int xmouse, int ymouse);
	void increaseSpeed(double fraction);
	void specialKeys(int key, int x, int y);
private:
	std::vector<GameObject*> _map;
	std::vector<GameObject*> _cars;
	std::vector<GameObject*> _logs;
	std::vector<unsigned int> _textures;
	Frog* _frog;
	std::vector<LightSource*> _light_sources;
	std::vector<Camera*> _cameras;
	Camera* _hud;
	Camera* _active;
	Vector3 _speedCar;
	Vector3 _speedLog;
	int _nlives;
	double _elapsed;
	double _delta_t;
	double _elap;
	double _limits[4];
	double _limitsRiver[2];
	bool _pause;
	void CreateMap();
	void DrawMap();
	void update_cars();
	void update_logs();
	void update_frog();
	void testCollisionsLimits();
	void testCollisionsCars();
	void testCollisionsRiver();
	bool standOnLog();
	int _carIndex;
	int _logIndex;
	void DisablePointLights();
	void EnablePointLights();
	void updateObjTimers(double time);
	const unsigned int GameManager::LoadTexture(const std::string & textureFilename);
	void DisplayGameOverMessage();
	void DisplayPauseMessage();
	void restart();
	void drawLives();
	void drawHead(double x);
};

#endif