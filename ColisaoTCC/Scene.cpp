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


	if(l_object && Scene::getMouse_button() == _MOUSE_RIGHT)
	{
		l_object->setX(Scene::getMouse_position().x);
		l_object->setY(Scene::getMouse_position().y);		
	}

	checkCollisions();

}


void Scene::MouseDown(void)
{


}

void Scene::MouseUp(void)
{
	if(Scene::getMouse_button() == _MOUSE_LEFT){
		if(ballCount >= 100)
		{
			Scene::popObject();
			ballCount --;
		}

		if(rand() % 1 == 0){
			Ball *ball = new Ball();
			ball->Init();
			ball->setFont(Scene::getDefaultFont());
			ball->setX(Scene::getMouse_position().x);
			ball->setY(Scene::getMouse_position().y);
			ball->setColor(getRandomColor());
			ball->setDirection(getRandomDirection());
			ball->setVelocity(getRandomVelocity());
			ball->setDirection(getRandomDirection());
			ball->setMass(rand()%5);

			ballCount ++;

			addObject(ball);

			l_object = ball;
		}
	}
}

void Scene::MouseMove(void)
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

ALLEGRO_COLOR Scene::getRandomColor()
{
	char r = rand()%250;
	char g = rand()%250;
	char b = rand()%250;

	return al_map_rgb(r,g,b);
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

	_velocity velocity = {vX,0.1};
	return velocity;
}

void Scene::checkCollisions()
{
	std::list<GameObject *> *obj = getObjects(_BALL);
	ALLEGRO_COLOR corColisao = al_map_rgb(100,250,100);
	ALLEGRO_COLOR corSemColisao = al_map_rgb(0,100,250);
	if(obj->size() > 0)
		for(std::list<GameObject *>::iterator it = obj->begin(); it != obj->end(); ++it)
		{
			for(std::list<GameObject *>::iterator it2 = it; it2 != obj->end(); ++it2)
			{
				if(it != it2){
					if((*it)->CheckCollisions(*it2))
					{
						dynamic_cast<Ball *>(*it)->Collided(*it2);
						dynamic_cast<Ball *>(*it2)->Collided(*it);
					}
				}
			}
		}
}



#pragma endregion Exclusive Method


