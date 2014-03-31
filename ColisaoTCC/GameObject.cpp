#include "GameObject.h"
#include "Core.h"

GameObject::GameObject()
{
	x = 0;
	y = 0;

	velX = 0;
	velY = 0;

	dirX = 0;
	dirY = 0;

	gravity = 0;

	boundX = 0;
	boundY = 0;

	maxFrame = 0;
	currFrame = 0;
	frameCount = 0;
	frameDelay = 0;
	frameWidth = 0;
	frameHeight = 0;
	animationColumns = 0;
	animationDirection = 0;

	image = NULL;

	alive = true;
	collidable = true;
}

void GameObject::Destroy()
{
	if(image != NULL)
		al_destroy_bitmap(image);
}

void GameObject::Init(_position position, _velocity velocity, _direction direction, _bound bound, float gravity)//Position: X, Y | Velocity: X, Y | Direction: X, Y | Bound: X, Y
{
	GameObject::x = position.x;
	GameObject::y = position.y;

	GameObject::velX = velocity.x;
	GameObject::velY = velocity.y;

	GameObject::dirX = direction.x;
	GameObject::dirY = direction.y;

	GameObject::boundX = bound.x;
	GameObject::boundY = bound.y;

	if(gravity != 0)
		GameObject::gravity = gravity;
}

void GameObject::Update()
{
	x += velX*dirX;//if 0 not move
	y += velY*dirY + gravity;
}

void GameObject::Render()
{}

bool GameObject:: CheckCollisions(GameObject *otherObject)
{
	float obj_x = otherObject->getX();
	float obj_y = otherObject->getY();

	float obj_bound_x = otherObject->getBoundX();
	float obj_bound_y = otherObject->getBoundY();

	if((x + boundX > obj_x - obj_bound_x &&
	   x - boundX < obj_x + obj_bound_x &&
	   y + boundY > obj_y - obj_bound_y &&
	   y - boundY < obj_y + obj_bound_y
	   )
	   )
	   return true;
	else 
		return false;	 
}

void GameObject::Collided(int objectID)
{}

bool GameObject::isCollidable()
{
	return alive && collidable;
}



