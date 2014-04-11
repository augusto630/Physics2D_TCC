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
	
	Vector velocity(0,0);
	Vector acceleration(0,0);
	_bound bound = {30,30};

	GameObject::Init(position,velocity,acceleration,bound);

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
		velocity.x *= -1;
	}
	else if(x > SCREEN_W - boundX)
	{
		x = SCREEN_W - boundX;
		velocity.x *= -1;
	}

	if(y < 0 + boundY)
	{
		y = 0 + boundY;
		velocity.y *= -1;
	}
	else if(y > SCREEN_H - boundY)
	{
		y = SCREEN_H - boundY;
		velocity.y *= -1;
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

	/*	al_draw_filled_circle(x,y,radius,Ball::color);
		al_draw_circle(x,y,radius,al_map_rgb(0,0,0),3);
		if(font)
			al_draw_textf(font,al_map_rgb(0,0,0),x,y,0,"B %i",index);*/
	}
}

void Ball::MoveUp()
{
	if(velocity.y > 0)
		velocity.y *= -1;
	//velocity = _DIRECTION_UP;
}
void Ball::MoveDown()
{
	if(velocity.y < 0)
		velocity.y *= -1;
	/*dirY = _DIRECTION_DOWN;*/
}
void Ball::MoveLeft()
{
	if(velocity.x > 0) 
		velocity.x *= -1;

	//dirX = _DIRECTION_LEFT;
}
void Ball::MoveRight()
{
	if(velocity.x < 0) 
		velocity.x *= -1;
	//dirX = _DIRECTION_RIGHT;
}

void Ball::Stop()
{
	//dirX = _DIRECTION_NONE;
	//dirY = _DIRECTION_NONE;
}

bool Ball:: CheckCollisions(Ball *otherObject)
{
	if(GameObject::CheckCollisions(otherObject))
	{
		Collided(otherObject);
		return true;
	}
	return false;
}


void Ball::Collided(GameObject *collidedObject)
{
	GameObject::Collided(collidedObject->getID());

	if(collidedObject->getID() == _OBSTACLE)	
		;//DO SOMETHING obstacle == border limit
	if(collidedObject->getID() == _BALL)
	{

		//color = al_map_rgb(100,0,250);//DO SOMETHING == other balls in the simulation

		//double vX,vY,vX_Object,vY_Object,vRx,vRy,vRx_Object,vRy_Object,mod,mod_Object,modR,modR_Object;
		//double mB = dynamic_cast<Ball *>(collidedObject)->getMass();
		//double mA = mass;
		//double theta,theta_Object;

		//float Al,Ar,Au,Ad;
		//float Bl,Br,Bu,Bd;

		//Al = x - boundX;
		//Ar = x + boundX;
		//Au = y + boundY;
		//Ad = y - boundY;

		//Bl = collidedObject->getX() - collidedObject->getBoundX();
		//Br = collidedObject->getX() + collidedObject->getBoundX();
		//Bu = collidedObject->getY() + collidedObject->getBoundY();
		//Bd = collidedObject->getY() - collidedObject->getBoundY();

		//float pAx = (Al - Br) > 0? (Al - Br)/2: (Ar - Bl)/2 ; 
		//float pAy = (Ad - Bu) > 0? (Ad - Bu)/2: (Au - Bd)/2 ;

		//pAx -= boundX;
		//pAy -= boundY;

		//float pBx = (Bl - Ar) > 0? (Bl - Ar)/2: (Br - Al)/2 ;
		//float pBy = (Bd - Au) > 0? (Bd - Bu)/2: (Bu - Bd)/2 ;

		//pBx -= collidedObject->getBoundX();
		//pBy -= collidedObject->getBoundY();

		//Vector vA = getVelocityR();
		//Vector vB = collidedObject->getVelocityR();

		//Vector n(vB.x - vA.x,vB.y-vA.y);


		//Vector un;
		//un = n/Magnitude(n);

		//Vector ut(-un.y,un.x);

		//float vAn = Dot(un,vA);
		//float vAt = Dot(ut,vA);

		//float vBn = Dot(un,vB);
		//float vBt = Dot(ut,vB);

		//float vlAt = vAt;
		//float vlBt = vBt;

		//float vlAn = ( vAn*(mA - mB) + (2*mB*vBn) ) / ( mA + mB );
		//float vlBn = ( vBn*(mB - mA) + (2*mA*vAn) ) / ( mA + mB );

		//Vector lAn = un*vlAn;
		//Vector lAt = ut*vlAt;
		//
		//Vector lBn = un*vlBn;
		//Vector lBt = ut*vlBt;

		//Vector lA = lAn + lAt;
		//Vector lB = lBn + lBt;		

		//velocity = lA;
		//collidedObject->setVelocity(lB);

		//x += pAx;
		//y += pAy;

		//collidedObject->setX(collidedObject->getX() + pBx);
		//collidedObject->setY(collidedObject->getY() + pBy);
	/*	x += lA.x;
		y += lA.y;

		collidedObject->setX(collidedObject->getX() + lB.x);
		collidedObject->setY(collidedObject->getY() + lB.y);*/

		/*normal.Normalize();

		float velAlongNorm = Dot(ab,normal);


		if(velAlongNorm <= 0)
		{

			float e = 0;

			float j = (1 + e) * velAlongNorm;
			j /= 1 / mass + 1 / mass_object;

			Vector impulse = j * normal;

			vA -= 1 / mass * impulse;
			vB += 1 / mass_object * impulse;

			velocity = vA;

			collidedObject->setVelocity(vB);

		}



		
		//vX = velX;
		//vY = velY;

		///*vX_Object = collidedObject->getVelocity().x + collidedObject->getX();
		//vY_Object = collidedObject->getVelocity().y + collidedObject->getY();*/
		//vX_Object = collidedObject->getVelocity().x;
		//vY_Object = collidedObject->getVelocity().y;

		//mod = sqrt(pow(vX,2)+pow(vY,2));

		//theta = vX/vY;
		//theta = pow(tan(theta),-1);

		//mod_Object = sqrt(pow(vX_Object,2)+pow(vY_Object,2));

		//theta_Object = vX_Object/vY_Object;
		//theta_Object = pow(tan(theta_Object),-1);

		//modR = (mass - mass_object)/(mass+mass_object);
		//modR = modR * mod;
		//modR = modR + (((2*mass_object)/(mass+mass_object))*mod_Object);

		//modR_Object = ((2*mass_object)/(mass + mass_object)) * mod;
		//modR_Object = ((mass_object - mass)/(mass + mass_object))*mod_Object;


		//vX = modR * cos(theta);
		//vY = modR * sin(theta);

		//vX_Object = modR_Object * cos(theta_Object);
		//vY_Object = modR_Object * sin(theta_Object);


		//_velocity vR_object = {vX_Object,vY_Object};
		////collidedObject->setVelocity(vR_object);

		//velX = vX;
		//velY = vY;

	}
}

