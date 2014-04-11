#pragma once

#include "Globals.h"

#include "Core.h"

#include "Ball.h"

class Scene: public Core
{
public:
	int Init(void);
private:
	long ballCount;

	ALLEGRO_BITMAP *ballBitmap;
	GameObject *l_object;

	void Tick(void);

	void MouseDown(void);
	void MouseUp(void);
	void MouseMove(void);

	void KeyUp(void);
	void KeyDown(void);
	void KeyLeft(void);
	void KeyRight(void);
	void KeySpace(void);

	ALLEGRO_COLOR getRandomColor(void);
	_direction getRandomDirection(void);
	_velocity getRandomVelocity(void);
	void checkCollisions(void);

};