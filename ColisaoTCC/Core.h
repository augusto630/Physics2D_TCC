#pragma once

#include "GameObject.h"
#include "Globals.h"

#include <allegro5\allegro5.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

#include <list>


class Core
{
private:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *buffer;
	ALLEGRO_TIMER *timer;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_FONT *font;
	ALLEGRO_PATH *resourcePath;

	std::list<GameObject *> objects;
	
	bool fullscreen;
	bool keys[5];//Folow Keys Struct Layout

	bool s_mouse[2];//0-MouseDown || 1 - MouseUp	
	_position p_mouse[3];//0-Position MouseDown || 1 - Position MouseUp || 2 -Position MouseMove
	MOUSE_BUTTON b_mouse;

	std::string title;
	bool done;
	bool render;
	bool isDrawFPS;
	float gameTime;
	int frames;
	int gameFPS;
	int soundSamples;

	int Allegro_Init();

	
protected:

	void GameLoop();
	void Destr();
	int UpdateDisplay(ALLEGRO_EVENT event, bool redraw)
	{
		/*bool redraw = false;
		if(event.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
		}*/
		if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			return -1;
		}

		if(redraw && al_event_queue_is_empty(event_queue)) {
		//if(redraw){

			

			redraw = false;
			int ob = 0;

			for(std::list<GameObject *>::iterator iter = objects.begin(); iter != objects.end(); ++iter)
				(*iter)->Render();//Renderizar todos os objetos

			al_set_target_backbuffer(display);//retorna para o display os proximos draw
			al_clear_to_color(al_map_rgb(0,0,0));//limpa o display (ou o que estiver na target)		

			al_draw_bitmap(buffer,0,0,0);//desenha o buffer		

			drawFPS();

			al_flip_display();//atualiza o display
			//limparBitmap(buffer);

		}

		al_set_target_bitmap(buffer);

		return 0;
	};
	void limparBitmap(ALLEGRO_BITMAP *bitmap)
	{
		ALLEGRO_BITMAP *btmAtual = al_get_target_bitmap();
		al_set_target_bitmap(bitmap);
		al_clear_to_color(al_map_rgb(0,0,0));
		if(btmAtual) al_set_target_bitmap(btmAtual);
		else al_set_target_backbuffer(display);
	};
	int getFPS()
	{
		double t = al_get_time();
		double refreshRate = 10;//2 hz

		frames++;
		if (t - gameTime >= 1/refreshRate) {
			gameFPS = frames;		
			frames = 0;
			gameTime = al_current_time();
		}
		return gameFPS * refreshRate;
	};
	void drawFPS(void)
	{
		if(Core::isDrawFPS)
			al_draw_textf(font,al_map_rgb(255,255,255),0,0,0,"FPS %d",Core::getFPS());
	};
	ALLEGRO_DISPLAY *createDisplay(void)
{
	al_set_new_display_option(ALLEGRO_COLOR_SIZE,32,ALLEGRO_DONTCARE);
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
	if(Core::fullscreen == true)
		al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	else
		al_set_new_display_flags(ALLEGRO_WINDOWED);

	return al_create_display(SCREEN_W,SCREEN_H);	
};

public:
	Core();
	int Init(void);
	void Start(void);
	void Stop(void);
	void addObject(GameObject *object){Core::objects.push_back(object);};
	void popObject(void){Core::objects.pop_front();};
	std::list<GameObject *> *getObjects(){return &objects;};
	std::list<GameObject *> *getObjects(ID id)
	{
		std::list<GameObject *> *returnList = new std::list<GameObject *>();
		for(std::list<GameObject *>::iterator it = objects.begin(); it != objects.end(); ++it)
		{
			if((*it)->getID() == id)			
				returnList->push_back(*it);
			
		}
		return returnList;
	};

	void setTitle(std::string value){Core::title = value;};
	void setFullScreen(bool value){Core::fullscreen = value;};
	void setSoundSamples(int value){Core::soundSamples = value;};
	void setMaxFPS(int value){Core::gameFPS = value;};
	void setDrawFPS(bool value){Core::isDrawFPS = value;};

	_position getMouseDown_position(void){return p_mouse[_MOUSE_DOWN];}
	_position getMouseUp_position(void){return p_mouse[_MOUSE_UP];}
	_position getMouse_position(void){return p_mouse[_MOUSE_MOVE];}
	MOUSE_BUTTON getMouse_button(void){return b_mouse;}
	ALLEGRO_FONT *getDefaultFont(void){return font;}


	virtual void Tick(void);

	virtual void MouseDown(void);
	virtual void MouseUp(void);
	virtual void MouseMove(void);

	virtual void KeyUp(void);
	virtual void KeyDown(void);
	virtual void KeyLeft(void);
	virtual void KeyRight(void);
	virtual void KeySpace(void);//Add more action Keys if nedded



};
