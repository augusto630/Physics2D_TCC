#include "Core.h"

Core::Core()
{
	fullscreen = false;
	keys[_KEY_UP] = false;
	keys[_KEY_DOWN] = false;
	keys[_KEY_LEFT] = false;
	keys[_KEY_RIGHT] = false;
	keys[_KEY_SPACE] = false;

	s_mouse[_MOUSE_DOWN] = false;
	s_mouse[_MOUSE_UP] = false;

	p_mouse[_MOUSE_DOWN].x = -1;
	p_mouse[_MOUSE_DOWN].y = -1;

	p_mouse[_MOUSE_UP].x = -1;
	p_mouse[_MOUSE_UP].y = -1;

	p_mouse[_MOUSE_MOVE].x = -1;
	p_mouse[_MOUSE_MOVE].y = -1;

	b_mouse = _MOUSE_BUTTON_NONE_OTHER;

	title = "";
	done = true;
	render = false;
	isDrawFPS = false;
	gameTime = 0;
	frames = 0;
	gameFPS = 60;
	soundSamples = 1;
	maxFPS = 0;
	minFPS = 9999;
	loopCount = 0;




	 fps1 = 0;
	 frames_done = 0;
	 old_time = 0;
 
	 frame_index = 0;//used to store the index of the last updated value in the array
	for(int ii = 0; ii < 10; ii++)
		frames_array[ii] = 0;//initialize the array to 0



	qTree = Quadtree( 0.0f, 0.0f, SCREEN_W, SCREEN_H, 1, nivelMaximo,NULL);


}

void Core::Start(void)
{
	GameLoop();
}

void Core::Stop(void)
{
	Destr();
}

int Core::Init()
{
	if(Allegro_Init() == -1)
	{
		al_rest(5);
		return -1;
	}
	done = false;

	return 0;
}

int Core::Allegro_Init()
{
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if(!al_install_mouse()) {
		fprintf(stderr, "failed to initialize the mouse!\n");
		return -1;
	}

	if(!al_install_keyboard())
	{
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}

	if(!al_init_primitives_addon())
	{
		fprintf(stderr, "failed to init primitive addon!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / gameFPS);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display = createDisplay();
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	buffer = al_create_bitmap(SCREEN_W,SCREEN_H);
	if(!buffer) {
		fprintf(stderr, "failed to create buffer bitmap!\n");
		return -1;
	}

	event_queue = al_create_event_queue();
	if(!event_queue)
	{
		fprintf(stderr, "failed to create event queue!\n");
		return -1;
	}

	al_init_font_addon();
	al_init_ttf_addon();

	font = al_load_ttf_font("DefaultFont.ttf",12,0);
	if(!font)
	{
		fprintf(stderr, al_path_cstr(resourcePath, '/'));
		return -1;
	}

	if(!al_install_audio()){
		fprintf(stderr, "failed to initialize audio!\n");
		return -1;
	}

	if(!al_init_acodec_addon()){
		fprintf(stderr, "failed to initialize audio codecs!\n");
		return -1;
	}

	if (!al_reserve_samples(soundSamples)){
		fprintf(stderr, "failed to reserve samples!\n");
		return -1;
	}
	al_init_image_addon();

	background = al_load_bitmap("C:/bg.jpg");

	if(!background)
	{
		fprintf(stderr,"Carregar Imagens falhou");
		return -1;
	}


	return 0;
}

void Core::Destr()
{
	al_destroy_font(font);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_destroy_timer(timer);
	for(std::list<GameObject *>::iterator iter = objects.begin(); iter != objects.end();)
	{
		(*iter)->Destroy();
		delete (*iter);
		iter = objects.erase(iter);

	}
}

void Core::GameLoop()
{
	
	ALLEGRO_KEYBOARD_STATE key_state;
	bool redraw = false;
	GradeUniforme grade(0,0,SCREEN_W,SCREEN_H,50,50);

	al_get_keyboard_state(&key_state);
	al_register_event_source(event_queue,al_get_mouse_event_source());//Register Mouse queue
	al_register_event_source(event_queue,al_get_keyboard_event_source());//Register Keyboard queue
	al_register_event_source(event_queue,al_get_timer_event_source(timer));//Register Timer queue
	al_register_event_source(event_queue,al_get_display_event_source(display));//Register Display queue
	al_flip_display();
	al_start_timer(timer);

	while(!done){


		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue,&event);		
		if(UpdateDisplay(event,redraw) == -1) done = true;

		#pragma region
		if(event.type == ALLEGRO_EVENT_KEY_DOWN){
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[_KEY_UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[_KEY_DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[_KEY_LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[_KEY_RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[_KEY_SPACE] = true;
				break;
			default:
				break;
			}		

		}
		#pragma endregion KeyDown

		#pragma region 
		else if(event.type == ALLEGRO_EVENT_KEY_UP){
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[_KEY_UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[_KEY_DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[_KEY_LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[_KEY_RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[_KEY_SPACE] = true;
				break;
			default:
				break;
			}
		}
		#pragma endregion KeyUp

		#pragma region

		if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{

			switch (event.mouse.button)
			{
			case 1:
				b_mouse = _MOUSE_LEFT;
				break;
			case 2:
				b_mouse = _MOUSE_RIGHT;
				break;
			default:
				b_mouse = _MOUSE_BUTTON_NONE_OTHER;
				break;
			}

			s_mouse[_MOUSE_DOWN] = true;

			p_mouse[_MOUSE_DOWN].x = event.mouse.x;
			p_mouse[_MOUSE_DOWN].y = event.mouse.y;

			s_mouse[_MOUSE_UP] = false;
			p_mouse[_MOUSE_UP].x = -1;
			p_mouse[_MOUSE_UP].y = -1;
		}
		

		#pragma endregion MouseDown
		
		#pragma region

		else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			switch (event.mouse.button)
			{
			case 1:
				b_mouse = _MOUSE_LEFT;
				break;
			case 2:
				b_mouse = _MOUSE_RIGHT;
				break;
			default:
				b_mouse = _MOUSE_BUTTON_NONE_OTHER;
				break;
			}

			s_mouse[_MOUSE_UP] = true;

			p_mouse[_MOUSE_UP].x = event.mouse.x;
			p_mouse[_MOUSE_UP].y = event.mouse.y;

			s_mouse[_MOUSE_DOWN] = false;
			p_mouse[_MOUSE_DOWN].x = -1;
			p_mouse[_MOUSE_DOWN].y = -1;

		}

		#pragma endregion MouseUp

		#pragma region

		if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			p_mouse[_MOUSE_MOVE].x = event.mouse.x;
			p_mouse[_MOUSE_MOVE].y = event.mouse.y;

			if(s_mouse[_MOUSE_DOWN])				
				p_mouse[_MOUSE_DOWN] = p_mouse[_MOUSE_MOVE];
			if(s_mouse[_MOUSE_UP])
				p_mouse[_MOUSE_UP] = p_mouse[_MOUSE_MOVE];
		}

		#pragma endregion MouseMove

		#pragma region 
		if(event.type == ALLEGRO_EVENT_TIMER){

			Tick();

			if(s_mouse[_MOUSE_DOWN])
			{
				if(!isInsertMultiple)
					s_mouse[_MOUSE_DOWN] = false;
				MouseDown();
			}
			if(s_mouse[_MOUSE_UP])
			{
				s_mouse[_MOUSE_UP] = false;
				MouseUp();
			}

			if(keys[_KEY_UP]){
				KeyUp();
			}
			else if(keys[_KEY_DOWN])
				KeyDown();
			if(keys[_KEY_LEFT])
				KeyLeft();
			else if(keys[_KEY_RIGHT])
			{
				KeyRight();
			}
			if(keys[_KEY_SPACE]){
				KeySpace();
			}



			#pragma region ForcaBruta
			if(isForcaBruta)
			{
				for(std::list<GameObject *>::iterator iter = objects.begin(); iter != objects.end(); ++iter)
				if(*iter){
					(*iter)->Update();
					for(std::list<GameObject *>::iterator it2 = iter; it2 != objects.end(); ++it2)
				{
					if(*iter != *it2){
						(*iter)->CheckCollisions(*it2);
					}
					loopCount++;
				}
				}
			}
			#pragma endregion ForcaBruta
			#pragma region QuadTree
			else if(isQuadTree){
				for(std::list<GameObject *>::iterator iter = objects.begin(); iter != objects.end(); ++iter){
					if(*iter){
						(*iter)->Update();


						qTree.AddObject(*iter);
						loopCount++;
						std::list<GameObject *> objlist = qTree.GetObjectsAt((*iter)->getX(),(*iter)->getY());

						for(std::list<GameObject *>::iterator it2 = objlist.begin(); it2 != objlist.end(); ++it2)
						{
							if(*iter != *it2){
								(*iter)->CheckCollisions(*it2);
							}
							loopCount++;
						}
					}
				}
				if(debug)
					qTree.draw();
				qTree.Clear();
			}
			#pragma endregion QuadTree	
			#pragma region GUniforme
			else if(isGUniforme)
			{
				for(std::list<GameObject *>::iterator iter = objects.begin(); iter != objects.end(); ++iter){
					if(*iter){
						(*iter)->Update();


						grade.AddObject(*iter);
						loopCount++;
						std::list<GameObject *> objlist = grade.GetObjectsAt((*iter)->getX(),(*iter)->getY());

						for(std::list<GameObject *>::iterator it2 = objlist.begin(); it2 != objlist.end(); ++it2)
						{
							if(*iter != *it2){
								(*iter)->CheckCollisions(*it2);
							}
							loopCount++;
						}
					}
					
				}
				if(debug)
						grade.draw();
				grade.Clear();
			}
			#pragma endregion GUniforme
			#pragma region Sem Física
			else{
				for(std::list<GameObject *>::iterator iter = objects.begin(); iter != objects.end(); ++iter){
					if(*iter)
						(*iter)->Update();
					loopCount++;
				}
			}
			#pragma endregion Sem Física

			redraw = true;
		}
		#pragma endregion Timer/Draw

	}
}


void Core::Tick(){};

void Core::MouseDown(void){};
void Core::MouseUp(void){};
void Core::MouseMove(void){};

void Core::KeyUp(void){};
void Core::KeyDown(void){};
void Core::KeyLeft(void){};
void Core::KeyRight(void){};
void Core::KeySpace(void){};//Add more action Keys if nedded

