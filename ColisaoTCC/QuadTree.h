
#include <list>
#include "GameObject.h"

class Quadtree {
public:
	Quadtree(float x, float y, float width, float height, int level, int maxLevel, Quadtree* parent);

	Quadtree();

	void					AddObject(GameObject *object);
	std::list<GameObject*>				GetObjectsAt(float x, float y);
	void					Clear();
	void draw()
	{

		if(objects.size() > 1)
		{

			al_draw_line(x - width, y - height, x - width, y + height, al_map_rgb(255,0,0), 1);
			al_draw_line(x - width, y - height, x + width, y - height, al_map_rgb(255,0,0), 1);
			al_draw_line(x + width, y + height, x + width, y - height, al_map_rgb(255,0,0), 1);
			al_draw_line(x + width, y + height, x - width, y + height, al_map_rgb(255,0,0), 1);
		}

		if(level != maxLevel){
			NW->draw();
			NE->draw();
			SW->draw();
			SE->draw();
		}

	};

private:
	float					x;
	float					y;
	float					width;
	float					height;
	int					level;
	int					maxLevel;
	std::list<GameObject*>				objects;

	Quadtree *				parent;
	Quadtree *				NW;
	Quadtree *				NE;
	Quadtree *				SW;
	Quadtree *				SE;

	bool					contains(Quadtree *child, GameObject *object);

};

