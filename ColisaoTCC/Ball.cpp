#include "Ball.h"

Ball::Ball()
{

}

void Ball::Destroy()
{
	GameObject::Destroy();
}

void Ball::Init(ALLEGRO_BITMAP *image, ALLEGRO_COLOR *color)
{
	_position position = {200,200};
	
	_velocity velocity = {1,2.5};
	_direction direction = {0,0};
	_bound bound = {30,30};

	GameObject::Init(position,velocity,direction,bound);

	setID(_BALL);
	setAlive(true);

	maxFrame = 3;
	currFrame = 0;
	frameWidth = 30;
	frameHeight = 30;
	animationColumns = 0;
	animationDirection = 0;

	radius = 30;

	if(image != NULL)
		Ball::image = image;
	if(color != NULL)
		Ball::color = *color;
	else
		Ball::color = al_map_rgb(255,255,255);
}

void Ball::Update()
{
	GameObject::Update();

	/*if(x < 0 - boundX)
		x = 0 - boundX;
	else if(x > SCREEN_W + boundX)
		x = SCREEN_W + boundX;

	if(y < 0 + boundY)
		y = 0 + boundY;
	else if(y > SCREEN_H - boundY)
		y = SCREEN_H - boundY;*/

	if(x < 0 + boundX)
	{
		x = 0 + boundX;
		dirX *= -1;
	}
	else if(x > SCREEN_W - boundX)
	{
		x = SCREEN_W - boundX;
		dirX *= -1;
	}

	if(y < 0 + boundY)
	{
		y = 0 + boundY;
		dirY *= -1;
	}
	else if(y > SCREEN_H - boundY)
	{
		y = SCREEN_H - boundY;
		dirY *= -1;
	}
	
	//Stop();
}

void Ball::Render()
{
	GameObject::Render();

	int fx = (currFrame & animationColumns) * frameWidth;
	int fy = 0;
	if(image)
		//al_draw_bitmap_region(image,fx,fy, frameWidth,frameHeight,
		//x - frameWidth / 2, y - frameHeight / 2, 0);
			al_draw_scaled_bitmap(image,0,0,240,240,x-frameWidth/2,y-frameHeight/2,80,80,0);
	else
	{
		al_draw_filled_rectangle(x-boundX,y-boundY,x+boundX, y+boundY,color);

		/*al_draw_filled_circle(x,y,radius,Ball::color);
		al_draw_circle(x,y,radius,al_map_rgb(0,0,0),3);
		if(font)
			al_draw_textf(font,al_map_rgb(0,0,0),x,y,0,"B %i",index);*/
	}
}

void Ball::MoveUp()
{
	dirY = _DIRECTION_UP;
}
void Ball::MoveDown()
{
	dirY = _DIRECTION_DOWN;
}
void Ball::MoveLeft()
{
	dirX = _DIRECTION_LEFT;
}
void Ball::MoveRight()
{
	dirX = _DIRECTION_RIGHT;
}

void Ball::Stop()
{
	dirX = _DIRECTION_NONE;
	dirY = _DIRECTION_NONE;
}
void Ball::Collided(GameObject *collidedObject)
{
	GameObject::Collided(collidedObject->getID());

	if(collidedObject->getID() == _OBSTACLE)	
		;//DO SOMETHING obstacle == border limit
	if(collidedObject->getID() == _BALL)
	{

		color = al_map_rgb(100,0,250);//DO SOMETHING == other balls in the simulation

		double vX,vY,vX_Object,vY_Object,vRx,vRy,vRx_Object,vRy_Object,mod,mod_Object,modR,modR_Object;
		double mass_object = dynamic_cast<Ball *>(collidedObject)->getMass();
		double theta,theta_Object;
		
		vX = velX;
		vY = velY;

		/*vX_Object = collidedObject->getVelocity().x + collidedObject->getX();
		vY_Object = collidedObject->getVelocity().y + collidedObject->getY();*/
		vX_Object = collidedObject->getVelocity().x;
		vY_Object = collidedObject->getVelocity().y;

		mod = sqrt(pow(vX,2)+pow(vY,2));

		theta = vX/vY;
		theta = pow(tan(theta),-1);

		mod_Object = sqrt(pow(vX_Object,2)+pow(vY_Object,2));

		theta_Object = vX_Object/vY_Object;
		theta_Object = pow(tan(theta_Object),-1);

		modR = (mass - mass_object)/(mass+mass_object);
		modR = modR * mod;
		modR = modR + (((2*mass_object)/(mass+mass_object))*mod_Object);

		modR_Object = ((2*mass_object)/(mass + mass_object)) * mod;
		modR_Object = ((mass_object - mass)/(mass + mass_object))*mod_Object;


		vX = modR * cos(theta);
		vY = modR * sin(theta);

		vX_Object = modR_Object * cos(theta_Object);
		vY_Object = modR_Object * sin(theta_Object);


		_velocity vR_object = {vX_Object,vY_Object};
		//collidedObject->setVelocity(vR_object);

		velX = vX;
		velY = vY;

		float obj_y = collidedObject->getY();
		float obj_x = collidedObject->getX();

		float obj_bound_x = collidedObject->getBoundX();
		float obj_bound_y = collidedObject->getBoundY();

		if(y+boundY > obj_y - obj_bound_y)
			y += (obj_y - obj_bound_y) - (y+boundY);
		if(y-boundY < obj_y + obj_bound_y)
			y = (obj_y + obj_bound_y) -sdfgdsdfgdsfg;

		if(x+boundX > obj_x - obj_bound_x)
			x = obj_x - obj_bound_x - 1;
		if(x-boundX < obj_bound_x + obj_bound_x)
			x = obj_x + obj_bound_x + 1;
		
		/*float obj_x = collidedObject->getX();
		float obj_y = collidedObject->getY();

		float r = 0;

		float obj_bound_x = collidedObject->getBoundX();
		float obj_bound_y = collidedObject->getBoundY();


		float a1,a2,a3,a4;
		float b1,b2,b3,b4;

		a1 = (x-boundX) + (y-boundY);
		a2 = (x-boundX) + (y+boundY);
		a3 = (x+boundX) + (y+boundY);
		a4 = (x+boundX) + (y-boundY);

		b1 = (obj_x-obj_bound_x) + (obj_y-obj_bound_y);
		b2 = (obj_x-obj_bound_x) + (obj_y+obj_bound_y);
		b3 = (obj_x+obj_bound_x) + (obj_y+obj_bound_y);
		b4 = (obj_x+obj_bound_x) + (obj_y-obj_bound_y);


		if(a3 > b1 || a3 > b2 || a3 > b3 || a3 > b4 
		 ||a4 > b1 || a4 > b2 || a4 > b3 || a4 > b4){
			x += (obj_x - obj_bound_x) - (x + boundX);
		}*/
		



	/*	_velocity velRes_Object = collidedObject->getVelocity();

		velRes_Object.x *-1;
		velRes_Object.y *-1;


		collidedObject->setVelocity(velRes_Object);*/
	}
}

