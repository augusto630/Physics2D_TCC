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
	frameWidth = 80;
	frameHeight = 80;
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
		al_draw_filled_circle(x,y,radius,Ball::color);
		al_draw_circle(x,y,radius,al_map_rgb(0,0,0),3);
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
void Ball::Collide(int objectID)
{
	if(objectID == _OBSTACLE)	
		;//DO SOMETHING obstacle == border limit
	if(objectID == _BALL)
		;//DO SOMETHING == other balls in the simulation
}

