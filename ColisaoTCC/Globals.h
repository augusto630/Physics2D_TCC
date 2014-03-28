#pragma once // one instance

static int SCREEN_H = 480;//Default
static int SCREEN_W = 640;//Default



//Underline for every enum created by me
enum DIRECTION_LEFT_RIGHT{_DIRECTION_LEFT = -1, _DIRECTION_RIGHT = 1};//See GameObject.h: dirX
enum DIRECTION_NONE{_DIRECTION_NONE = 0};
enum DIRECTION_UP_DOWN{_DIRECTION_UP = -1, _DIRECTION_DOWN = 1};//See GameObject.h: dirY
enum ID{_BALL = 1,_OBSTACLE = 3,_MISC = 4}; //may add a BULLET id or INTERACTABLE
enum STATE{_TITLE,_PLAYING,_LOST};
enum KEYS{_KEY_UP,_KEY_DOWN,_KEY_LEFT,_KEY_RIGHT,_KEY_SPACE};//keyboard keys maybe add a action key as well
enum MOUSE{_MOUSE_DOWN = 0,_MOUSE_UP = 1};

struct _position
{
	float x;
	float y;
};

struct _velocity
{
	float x;
	float y;
};

struct _direction
{
	int x;
	int y;
};

struct _bound
{
	int x;
	int y;
};

struct _size
{
	float height;
	float width;
};