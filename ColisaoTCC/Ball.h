#pragma once

#include "GameObject.h"

class Ball: public GameObject
{
private:
	int radius;
	ALLEGRO_COLOR color;

public:
	Ball();
	void Destroy();

	void Init(ALLEGRO_BITMAP *image = NULL, ALLEGRO_COLOR *color = NULL);
	void Update();
	void Render();

	void setColor(ALLEGRO_COLOR *color){Ball::color = *color;};

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Stop();

	void Collide(int objectID);
};
