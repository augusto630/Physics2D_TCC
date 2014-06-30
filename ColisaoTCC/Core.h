#pragma once

#include <allegro5\allegro5.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

#include "GameObject.h"
#include "Globals.h"

#include "QuadTree.h"
#include "GradeUniforme.h"

#include <list>


class Core
{
private:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *buffer;
	ALLEGRO_BITMAP *background;
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

	int maxFPS;
	int minFPS;
	long loopCount;
	long loopCountC;
	long controlTimeLoopCount;
	Quadtree qTree;


	int Allegro_Init();





	int fps1;
	int frames_done;
	int old_time;
 
	int frames_array[10];//an array to store the number of frames we did during the last 10 tenths of a second
	int frame_index;//used to store the index of the last updated value in the array

	
protected:

	void GameLoop();
	void Destr();

	long getLoopCount(){return loopCountC;};

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

			for(std::list<GameObject *>::iterator it = objects.begin(); it != objects.end(); ++it)
			{
				/*for(std::list<GameObject *>::iterator it2 = it; it2 != objects.end(); ++it2)
				{
					if(it != it2){
						(*it)->CheckCollisions(*it2);
					}
				}*/


				(*it)->Render();//Renderizar todos os objetos
			}

			al_set_target_backbuffer(display);//retorna para o display os proximos draw
			al_clear_to_color(al_map_rgb(0,0,0));//limpa o display (ou o que estiver na target)		

			al_draw_bitmap(buffer,0,0,0);//desenha o buffer		

			drawFPS();

			al_flip_display();//atualiza o display
			//limparBitmap(buffer);


			frames_done++;
			if(al_get_time() - controlTimeLoopCount >= 1){
				loopCountC = loopCount;
				loopCount = 0;
				controlTimeLoopCount = al_get_time();
			}
		}


	 //   if(al_current_time() >= old_time -3)//i.e. a 0.1 second has passed since we last counted the frames
		//{
		//	fps1 -= frames_array[frame_index];//decrement the fps by the frames done a second ago
		//	frames_array[frame_index] = frames_done;//store the number of frames done this 0.1 second
		//	fps1 += frames_done;//increment the fps by the newly done frames
 
		//	frame_index = (frame_index + 1) % 3;//increment the frame index and snap it to 10
 
		//	frames_done = 0;
		//	old_time += 1;
		//}
		if(al_current_time() - old_time >= 1)//i.e. a second has passed since we last measured the frame rate
		{
			fps1 = frames_done;
			//fps now holds the the number of frames done in the last second
			//you can now output it using textout_ex et al.
 
			//reset for the next second
			frames_done = 0;
			old_time = al_current_time();
			if(fps1 < minFPS) minFPS = fps1;
			if(fps1 > maxFPS) maxFPS = fps1;
		}



		al_set_target_bitmap(buffer);


		//al_draw_textf(font,al_map_rgb(255,255,255),0,0,0,"FPS %d",fps1);

	 


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
		//double t = al_get_time();
		//double refreshRate = 60;//2 hz

		//frames++;
		//if (t - gameTime >= 1/refreshRate) {
		//	gameFPS = frames;		
		//	frames = 0;
		//	gameTime = al_current_time();

		//	if((gameFPS * refreshRate) < minFPS) minFPS = gameFPS * refreshRate;
		//	if((gameFPS * refreshRate) > maxFPS) maxFPS = gameFPS * refreshRate;

		//}
		//return gameFPS * refreshRate;




		return fps1;


	};
	void drawFPS(void)
	{

		if(Core::isDrawFPS && debug){
			//al_draw_textf(font,al_map_rgb(255,255,255),0,0,0,"FPS %d",fps1);
		    al_draw_textf(font,al_map_rgb(255,255,255),0,0,0,"FPS %d",fps1);
			al_draw_textf(font,al_map_rgb(255,255,255),0,10,0,"Min FPS %d",minFPS);
			al_draw_textf(font,al_map_rgb(255,255,255),0,20,0,"Max FPS %d",maxFPS);
			
			al_draw_textf(font,al_map_rgb(255,255,255),0,40,0,"Loop CTrl %d",loopCountC);
			
		}
		al_draw_textf(font,al_map_rgb(255,255,255),0,30,0,"Qtd Obj %d",objects.size());
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

	ALLEGRO_FONT *getDefaultFont(){return font;}
	ALLEGRO_BITMAP *getBackground(){return background;}

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
