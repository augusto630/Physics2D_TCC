#include "GameObject.h"
#include "Core.h"

GameObject::GameObject()
{
	x = 0;
	y = 0;

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

void GameObject::Init(_position position, Vector velocity,Vector acceleration, _bound bound, QuadTreeOccupant *ocp)
{
	const_atrict = 0;
	GameObject::x = position.x;
	GameObject::y = position.y;

	GameObject::velocity = velocity;
	GameObject::acceleration = acceleration;

	GameObject::boundX = bound.x;
	GameObject::boundY = bound.y;

	GameObject::ocp = *ocp;

}

Vector GameObject::getVelocityR()
{
	Vector vR;
	//vR += staticForce;
	vR += velocity;
	//vR += dynamicForce;

	return vR;
}

float modulo(float valor)
{
	if(valor < 0)
		return valor * -1;
	else
		return valor;
}

void GameObject::Update()
{
	float vX;
	float vY;

	Vector vR;

	float sec = (float)1/gFPS;

	if(velocity.y != 0){
		if(velocity.y > 0)velocity.y -= const_atrict;
		if(velocity.y < 0)velocity.y += const_atrict;

		if(velocity.y > const_atrict && velocity.y < const_atrict)
			velocity.y = 0;
	}

	if(velocity.x != 0){
		if(velocity.x > 0)velocity.x -= const_atrict;
		if(velocity.x < 0)velocity.x += const_atrict;

		if(velocity.x > const_atrict && velocity.x < const_atrict)
			velocity.x = 0;
	}



	velocity += acceleration;
	velocity += staticForce*sec;
	velocity += dynamicForce*sec;

	//vR += staticForce;
	vR += velocity;
	vR += dynamicForce;

	//RETIRAR

	//RETIRAR;

	velocity = vR;
	
	if(dynamicForce.x != 0){
		if(dynamicForce.x > 0 )
			dynamicForce.x -= sec;
		if(dynamicForce.x < 0)
			dynamicForce.x += sec;
	}

	if(dynamicForce.y != 0){
		if(dynamicForce.y > 0 )
			dynamicForce.y -= sec;
		if(dynamicForce.y < 0)
			dynamicForce.y += sec;
	}

	if(dynamicForce.x <= sec && dynamicForce.x >= -sec)
		dynamicForce.x = 0;

	if(dynamicForce.y <= sec && dynamicForce.y >= -sec)
		dynamicForce.y = 0;

	if(modulo(vR.x) < 0.1) vR.x = 0;
	if(modulo(vR.y) < 0.1) vR.y = 0;

	x += vR.x;
	y += vR.y;

	ocp.aabb.lowerBound = Vec2f(x - boundX, y + boundY);
	ocp.aabb.upperBound = Vec2f(x + boundX, y - boundY);
	ocp.UpdateTreeStatus();
}


void GameObject::Render()
{
}

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
	   ){
		   bool xNull = velocity.x == 0;
		   bool yNull = velocity.y == 0;
		   bool xBNull = otherObject->getVelocityR().x == 0;
		   bool yBNull =  otherObject->getVelocityR().y == 0;


		double vX,vY,vX_Object,vY_Object,vRx,vRy,vRx_Object,vRy_Object,mod,mod_Object,modR,modR_Object;
		double mB = otherObject->getMass();
		double mA = mass;
		double theta,theta_Object;

		float Al,Ar,Au,Ad;
		float Bl,Br,Bu,Bd;


		float boundAx = boundX;
		float boundAy = boundY;
		float boundBx = otherObject->getBoundX();
		float boundBy = otherObject->getBoundY();

		Al = x - boundX;
		Ar = x + boundX;
		Au = y + boundY;
		Ad = y - boundY;

		Bl = otherObject->getX() - otherObject->getBoundX();
		Br = otherObject->getX() + otherObject->getBoundX();
		Bu = otherObject->getY() + otherObject->getBoundY();
		Bd = otherObject->getY() - otherObject->getBoundY();

		float pAx = (Al - Br) > 0? (Al - Br)/2: (Ar - Bl)/2 ; 
		float pAy = (Ad - Bu) > 0? (Ad - Bu)/2: (Au - Bd)/2 ;

		pAx -= boundX;
		pAy -= boundY;

		float pBx = (Bl - Ar) > 0? (Bl - Ar)/2: (Br - Al)/2 ;
		float pBy = (Bd - Au) > 0? (Bd - Bu)/2: (Bu - Bd)/2 ;

		pBx -= otherObject->getBoundX();
		pBy -= otherObject->getBoundY();

		Vector vA = getVelocityR();
		Vector vB = otherObject->getVelocityR();

		Vector n(vB.x - vA.x,vB.y-vA.y);


		Vector un;
		un = n/Magnitude(n);

		Vector ut(-un.y,un.x);

		float vAn = Dot(un,vA);
		float vAt = Dot(ut,vA);

		float vBn = Dot(un,vB);
		float vBt = Dot(ut,vB);

		float vlAt = vAt;
		float vlBt = vBt;

		float vlAn = ( vAn*(mA - mB) + (2*mB*vBn) ) / ( mA + mB );
		float vlBn = ( vBn*(mB - mA) + (2*mA*vAn) ) / ( mA + mB );

		Vector lAn = un*vlAn;
		Vector lAt = ut*vlAt;
		
		Vector lBn = un*vlBn;
		Vector lBt = ut*vlBt;

		Vector lA = lAn + lAt;
		Vector lB = lBn + lBt;		

		//while((x + boundX > obj_x - obj_bound_x &&
	 //  x - boundX < obj_x + obj_bound_x &&
	 //  y + boundY > obj_y - obj_bound_y &&
	 //  y - boundY < obj_y + obj_bound_y
	 //  )
	 //  )
		//{
		//	//lA.x += 0.01;
		//	//lB.x -= 0.01;
		//	y += 0.01;
		//	floor'
		//	//Update();
		//	
		//}


		if(xNull && yNull)
		{
			lA = Vector(0,0);
		}


		if(xBNull && yBNull)
		{
			lB	= Vector(0,0);
		}


		
			velocity = lA;
			otherObject->setVelocity(lB);


			if((x + boundX > obj_x - obj_bound_x &&
				x - boundX < obj_x + obj_bound_x &&
				y + boundY > obj_y - obj_bound_y &&
				y - boundY < obj_y + obj_bound_y
				))
			{
				float tX = (x + boundX) - (obj_x + obj_bound_x);
				float tY = (y + boundY) - (obj_y + obj_bound_y);

				if(tX < 0) tX *= -1;
				if(tY < 0) tY *= -1;

					/*if((x+boundX) > (obj_bound_x + obj_x))
						x += tX/(gFPS/2);
					else
						x -= tX/(gFPS/2);

					if((y+boundY) > (obj_bound_y + obj_y))
						y += tY/(gFPS/2);
					else
						y -= tY/(gFPS/2);

						
*/
				int fator = 10;
					if((x+boundX) > (obj_bound_x + obj_x))
						x += tX/(gFPS/fator);
					else
						x -= tX/(gFPS/fator);

					if((y+boundY) > (obj_bound_y + obj_y))
						y += tY/(gFPS/fator);
					else
						y -= tY/(gFPS/fator);

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
			}


		/*if(xNull && yNull && xBNull && yBNull)
		{
			x += boundAx;
			y += boundAy;
		}*/



		

		/*x += pAx/2;
		y += pAy/2;

*/

	   return true;
	}else 
		return false;	 
}

void GameObject::Collided(int objectID)
{}

bool GameObject::isCollidable()
{
	return alive && collidable;
}



