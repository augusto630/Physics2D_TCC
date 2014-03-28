#include "Scene.h"

int Scene::Init()
{
	Core::Init();
	Scene::ballCount = 0;
	srand(time(NULL));

	return 0;
}


void Scene::Tick(void)
{
	//al_draw_scaled_bitmap(fundo,0,0,902,674,0,0,SCREEN_W,SCREEN_H,0);
	al_draw_filled_rectangle(0,0,SCREEN_W,SCREEN_H,al_map_rgb(200,200,200));


	checkCollisions();

}

void Scene::MouseDown(void)
{

	if(ballCount >= 100)
	{
		Scene::popObject();
		ballCount --;
	}

	if(rand() % 20 == 0){
		Ball *ball = new Ball();
		ball->Init();
		ball->setX(Scene::getMouseDown_position().x);
		ball->setY(Scene::getMouseDown_position().y);
		ball->setColor(getRandomColor());
		ball->setDirection(getRandomDirection());
		ball->setVelocity(getRandomVelocity());

		ballCount ++;

		addObject(ball);
	}

}

void Scene::MouseUp(void)
{
	
	
}


void Scene::KeyUp(void)
{

}

void Scene::KeyDown(void)
{
	std::list<GameObject *> *obj = getObjects();
	for(std::list<GameObject *>::iterator it = obj->begin(); it != obj->end(); ++it)
	{
		//if((*it)->getID() == _PLAYER)
		//	dynamic_cast<Player *>(*it)->MoveDown();
	}
}

void Scene::KeyLeft(void)
{
	std::list<GameObject *> *obj = getObjects();
	for(std::list<GameObject *>::iterator it = obj->begin(); it != obj->end(); ++it)
	{
		//if((*it)->getID() == _PLAYER)
		//	dynamic_cast<Player *>(*it)->MoveLeft();
	}
}

void Scene::KeyRight(void)
{
	std::list<GameObject *> *obj = getObjects();
	for(std::list<GameObject *>::iterator it = obj->begin(); it != obj->end(); ++it)
	{
		//if((*it)->getID() == _PLAYER)
		//	dynamic_cast<Player *>(*it)->MoveRight();
	}
}

void Scene::KeySpace(void)
{
}


#pragma region

ALLEGRO_COLOR *Scene::getRandomColor()
{
	char r = rand()%250;
	char g = rand()%250;
	char b = rand()%250;

	return &al_map_rgb(r,g,b);
}

_direction Scene::getRandomDirection()
{
	DIRECTION_LEFT_RIGHT dirLeftRight;
	DIRECTION_UP_DOWN dirUpDown;

	int rUD = rand() % 2;

	int rLR = rand() % 2;

	switch (rLR)
	{
		case 0: dirLeftRight = _DIRECTION_LEFT;break;
		case 1: dirLeftRight = _DIRECTION_RIGHT;break;
	}

	switch (rUD)
	{
		case 0: dirUpDown = _DIRECTION_UP;break;
		case 1: dirUpDown = _DIRECTION_DOWN;break;
	}

	_direction direction = {dirLeftRight,dirUpDown};

	return direction;

}

_velocity Scene::getRandomVelocity()
{
	int minV = 1;
	int maxV = 5;
	int vX = rand() % maxV + minV;
	int vY = rand() % maxV + minV;

	_velocity velocity = {vX,vY};

	return velocity;
}

void Scene::checkCollisions()
{
	std::list<GameObject *> *obj = getObjects(_BALL);
	if(obj->size() > 0)
	for(std::list<GameObject *>::iterator it = obj->begin(); it != obj->end(); ++it)
	{
		for(std::list<GameObject *>::iterator it2 = it; it2 != obj->end(); ++it2)
		{
			if((*it)->CheckCollisions(*it2))
			{
				_direction c_direction = (*it)->getDirection();
				c_direction.x *= -1;
				c_direction.y *= -1;
				(*it)->setDirection(c_direction);
			}
		}
	}
}



#pragma endregion Exclusive Method


