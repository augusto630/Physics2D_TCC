#include "GradeUniforme.h"

#include <iostream>
#include <sstream>

GradeUniforme::GradeUniforme(float _x, float _y, float _width, float _height, int _column, int _row) :
	x		(_x),
	y		(_y),
	width	(_width),
	height	(_height),
	column  (_column),
	row     (_row)
	
{
}

	
GradeUniforme::GradeUniforme()
{
}

void GradeUniforme::AddObject(GameObject *object) {

	int objX = floor(object->getX()/(SCREEN_W / columnGU));
	int objY = floor(object->getY()/(SCREEN_H / rowGU));
	grid[objY][objX].lista.push_back(object);

}

std::list<GameObject*> GradeUniforme::GetObjectsAt(float _x, float _y) {
	int objX = floor(_x/(SCREEN_W / columnGU));
	int objY = floor(_y/(SCREEN_H / rowGU));

	return grid[objY][objX].lista;
}

void GradeUniforme::Clear() {	
	for(int i=0; i<rowGU;i++)
	{
		for(int j=0;j<columnGU;j++)
		{
			grid[i][j].lista.clear();
		}
	}
}
