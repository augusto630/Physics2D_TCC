#pragma once

#include <iostream>
#include <allegro5\allegro5.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include "Globals.h"
#include "QuadTreeOccupant.h"

class GameObject
{
private:	
	int ID;
	bool alive;
	bool collidable;

protected:
	float x;
	float y;
	float mass;

	Vector acceleration;
	Vector velocity;
	Vector velocityI;
	Vector staticForce;
	Vector dynamicForce;
	Vector momentum;

	bool correcao;
	Vector vCorrecao;

	float const_atrict;

	int boundX;
	int boundY;
	QuadTreeOccupant ocp;

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

	void Init(_position position, Vector velocity,Vector acceleration, _bound bound,QuadTreeOccupant* ocp);
	void virtual Update();
	void virtual Render();
 
	float getX(){return x;}
	float getY(){return y;}

	void setMass(float mass){GameObject::mass = mass;};
	float getMass(){return GameObject::mass;};

	void setX(float x){GameObject::x = x;}
	void setY(float y){GameObject::y = y;}

	void setCorrecao(bool valor){ GameObject::correcao = valor;}
	bool getCorrecao(){ return GameObject::correcao;}

	void setVCorrecao(Vector valor){ GameObject::vCorrecao = valor;}
	Vector getVCorrecao(){ return GameObject::vCorrecao;}

	void setVelocity(Vector velocity){GameObject::velocity = velocity; GameObject::velocityI = velocity;}
	Vector *getVelocity(){return  &velocity;}

	Vector getVelocityR();

	void addForce(Vector force){GameObject::dynamicForce += force;}
	void setForce(Vector force){GameObject::dynamicForce = force;}

	void addStaticForce(Vector force){GameObject::staticForce += force;}

	void setAtrict(float atrict){const_atrict = atrict;}
	float getAtrict(){return const_atrict;}

	Vector *getDynamicForce(){return &dynamicForce;}
	Vector *getStaticForce(){return &staticForce;}

	void resetForces(){velocity = velocityI;dynamicForce.Set(0,0);}

	int getBoundX(){return boundX;}
	int getBoundY(){return boundY;}

	QuadTreeOccupant *getQuadTreeOccupant(){return &ocp;}
	void setQuadTreeOccupant(QuadTreeOccupant* ocp){ GameObject::ocp = *ocp;}

	int getID(){return ID;}
	void setID(int ID){GameObject::ID = ID;}

	bool getAlive(){return alive;}
	void setAlive(bool alive){GameObject::alive = alive;}

	bool getCollidable(){return collidable;}
	void setCollidable(bool collidable){GameObject::collidable = collidable;}

	bool virtual CheckCollisions(GameObject *otherObject);
	void virtual Collided(int objectID);
	bool isCollidable();//is alive and is collidable
};
