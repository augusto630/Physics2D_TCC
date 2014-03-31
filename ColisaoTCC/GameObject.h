#pragma once

#include <iostream>
#include <allegro5\allegro5.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include "Globals.h"

class GameObject
{
private:	
	int ID;
	bool alive;
	bool collidable;

protected:
	float x;
	float y;

	float velX;
	float velY;

	float gravity;

	int dirX;// Right = +1| Left = -1 | None = 0
	int dirY;// Up = -1 | Down = +1 | None = 0

	int boundX;
	int boundY;

#pragma region
	int maxFrame;
	int currFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationDirection;

	ALLEGRO_BITMAP *image;
#pragma endregion Animation

public:
	GameObject();
	void virtual Destroy();

	void Init(_position position, _velocity velocity, _direction direction, _bound bound, float gravity = 0);
	void virtual Update();
	void virtual Render();

	float getX(){return x;}
	float getY(){return y;}

	void setX(float x){GameObject::x = x;}
	void setY(float y){GameObject::y = y;}

	void setVelocity(_velocity velocity){GameObject::velX = velocity.x; GameObject::velY = velocity.y;}
	_velocity getVelocity()
	{
		_velocity velocity = {GameObject::velX,GameObject::velY};
		return velocity;
	}

	void setGravity(float gravity){GameObject::gravity = gravity;}
	void setDirection(_direction direction){GameObject::dirX = direction.x; GameObject::dirY = direction.y;}

	_direction getDirection(void)
	{
		_direction direction = {GameObject::dirX,GameObject::dirY};
		return direction;
	}

	int getBoundX(){return boundX;}
	int getBoundY(){return boundY;}

	int getID(){return ID;}
	void setID(int ID){GameObject::ID = ID;}

	bool getAlive(){return alive;}
	void setAlive(bool alive){GameObject::alive = alive;}

	bool getCollidable(){return collidable;}
	void setCollidable(bool collidable){GameObject::collidable = collidable;}

	bool CheckCollisions(GameObject *otherObject);
	void virtual Collided(int objectID);
	bool isCollidable();//is alive and is collidable
};
