#pragma once

#include "GameObject.h"
#include <math.h>

class Ball: public GameObject
{
private:
	int radius;
	float mass;
	ALLEGRO_FONT *font;
	ALLEGRO_COLOR color;
	int index;

public:
	Ball();
	void Destroy();

	void Init(ALLEGRO_BITMAP *image = NULL, ALLEGRO_COLOR *color = NULL);
	void Update();
	void Render();

	void setColor(ALLEGRO_COLOR color){Ball::color = color;};
	void setFont(ALLEGRO_FONT *font){Ball::font = font;};

	void setMass(float mass){Ball::mass = mass;};
	float getMass(){return Ball::mass;};

	int getIndex(){return index;};
	void setIndex(int index){Ball::index = index;};

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Stop();

	void Collided(GameObject *collidedObject);
};
