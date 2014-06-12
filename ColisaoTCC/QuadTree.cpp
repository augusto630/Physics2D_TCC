#include "Quadtree.h"

#include <iostream>
#include <sstream>

Quadtree::Quadtree(float _x, float _y, float _width, float _height, int _level, int _maxLevel, Quadtree* _parent) :
	x		(_x),
	y		(_y),
	width	(_width),
	height	(_height),
	level	(_level),
	maxLevel(_maxLevel),
	parent  (_parent)
{
	
	if (level == maxLevel) {
		return;
	}

	NW = new Quadtree(x, y, width / 2.0f, height / 2.0f, level+1, maxLevel,this);
	NE = new Quadtree(x + width / 2.0f, y, width / 2.0f, height / 2.0f, level+1, maxLevel,this);
	SW = new Quadtree(x, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel,this);
	SE = new Quadtree(x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel,this);

	parent = _parent;
}

Quadtree::Quadtree()
{
	if (level == maxLevel)
		return;

	delete NW;
	delete NE;
	delete SW;
	delete SE;
}

void Quadtree::AddObject(GameObject *object) {
	if (level == maxLevel) {
		objects.push_back(object);
		return;
	}
	if (contains(NW, object)) {
		NW->AddObject(object); return;
	} else if (contains(NE, object)) {
		NE->AddObject(object); return;
	} else if (contains(SW, object)) {
		SW->AddObject(object); return;
	} else if (contains(SE, object)) {
		SE->AddObject(object); return;
	}
	if (contains(this, object)) {
		objects.push_back(object);
	}
}

std::list<GameObject*> Quadtree::GetObjectsAt(float _x, float _y) {
	if (level == maxLevel) {
		return objects;
	}
	
	std::list<GameObject *> returnObjects, childReturnObjects;
	if (!objects.empty()) {
		returnObjects = objects;
	}
	if (_x > x + width / 2.0f && _x < x + width) {
		if (_y > y + height / 2.0f && _y < y + height) {
			childReturnObjects = SE->GetObjectsAt(_x, _y);
			returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
			return returnObjects;
		} else if (_y > y && _y <= y + height / 2.0f) {
			childReturnObjects = NE->GetObjectsAt(_x, _y);
			returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
			return returnObjects;
		}
	} else if (_x > x && _x <= x + width / 2.0f) {
		if (_y > y + height / 2.0f && _y < y + height) {
			childReturnObjects = SW->GetObjectsAt(_x, _y);
			returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
			return returnObjects;
		} else if (_y > y && _y <= y + height / 2.0f) {
			childReturnObjects = NW->GetObjectsAt(_x, _y);
			returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
			return returnObjects;
		}
	}
	return returnObjects;
}

void Quadtree::Clear() {
	if (level == maxLevel) {
		objects.clear();
		return;
	} else {
		NW->Clear();
		NE->Clear();
		SW->Clear();
		SE->Clear();
	}
	if (!objects.empty()) {
		objects.clear();
	}
}

bool Quadtree::contains(Quadtree *child, GameObject *object) {
	return	 !(object->getX() < child->x ||
				object->getY() < child->y ||
				object->getX() > child->x + child->width  ||
				object->getY() > child->y + child->height ||
				object->getX() + object->getBoundX() < child->x ||
				object->getY() + object->getBoundY() < child->y ||
				object->getX() + object->getBoundX() > child->x + child->width ||
				object->getY() + object->getBoundY() > child->y + child->height);
}
