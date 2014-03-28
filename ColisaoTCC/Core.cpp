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

	title = "";
	done = true;
	render = false;
	isDrawFPS = false;
	gameTime = 0;
	frames = 0;
	gameFPS = 60;
	soundSamples = 1;
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
			s_mouse[_MOUSE_UP] = true;

			p_mouse[_MOUSE_UP].x = event.mouse.x;
			p_mouse[_MOUSE_UP].y = event.mouse.y;

			s_mouse[_MOUSE_DOWN] = false;
			p_mouse[_MOUSE_DOWN].x = -1;
			p_mouse[_MOUSE_DOWN].y = -1;

		}
		if(event.type == ALLEGRO_EVENT_MOUSE_AXES && s_mouse[_MOUSE_DOWN])
		{
			p_mouse[_MOUSE_DOWN].x = event.mouse.x;
			p_mouse[_MOUSE_DOWN].y = event.mouse.y;
		}


		#pragma endregion MouseUp

		#pragma region 
		if(event.type == ALLEGRO_EVENT_TIMER){

			Tick();

			if(s_mouse[_MOUSE_DOWN])
			{
				MouseDown();
			}
			if(s_mouse[_MOUSE_UP])
			{
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

			for(std::list<GameObject *>::iterator iter = objects.begin(); iter != objects.end(); ++iter)
				if(*iter)
					(*iter)->Update();

			redraw = true;
		}
		#pragma endregion Timer/Draw

	}
}


void Core::Tick(){};

void Core::MouseDown(void){};
void Core::MouseUp(void){};

void Core::KeyUp(void){};
void Core::KeyDown(void){};
void Core::KeyLeft(void){};
void Core::KeyRight(void){};
void Core::KeySpace(void){};//Add more action Keys if nedded

