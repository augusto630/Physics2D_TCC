
#include <list>
#include "GameObject.h"


struct AABB
{
	std::list<GameObject *> lista;
};

class GradeUniforme {
public:
	GradeUniforme(float x, float y, float width, float height, int column, int row);

	GradeUniforme();

	void					AddObject(GameObject *object);
	std::list<GameObject*>				GetObjectsAt(float x, float y);
	void					Clear();
	void draw()
	{
	};

private:
	float					x;
	float					y;
	float					width;
	float					height;
	int					column;
	int					row;
	std::list<GameObject*>				objects;

	AABB grid[rowGU][columnGU];


};

