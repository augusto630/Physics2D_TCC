
#include <Box2D/Box2D.h>
#include <allegro5/allegro.h>
#include <cstdio>
#include "Globals.h"
#include <list>


//The scale. 32 is a better number than 30, because almost all screen resolution dimensions are a multiple of 32.
const int PIX_METER = 32;
const int FPS = 60;
class Box2DeX{
public:
int Box2DeX::start(int argc, char** argv)
{
  B2_NOT_USED(argc);
  B2_NOT_USED(argv);

  std::list<b2Body *> bodyes;

  b2Vec2 gravity(0.0f, 10.0f);
  bool doSleep = true;
  b2World world(gravity);

  // Define the ground body.
  b2BodyDef groundBodyDef;
  //Box2D positions are the center.
  //Put it in the middle: 10.0f, 7.5f
  groundBodyDef.position.Set((float)(SCREEN_W/2)/PIX_METER, (float)(SCREEN_H/2)/PIX_METER);

  b2Body* groundBody = world.CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;

  // The extents are the half-widths of the box.
  //I chose these numbers arbitrarily
  float g_width = 6.0f;
  float g_height = 2.4f;
  groundBox.SetAsBox(g_width/2, g_height/2);

  // Add the ground fixture to the ground body.
  groundBody->CreateFixture(&groundBox, 0.0f);

  // Define the dynamic body. We set its position and call the body factory.
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set((float)(SCREEN_W/2)/PIX_METER, 0.0f); //top of the screen
  b2Body* body = world.CreateBody(&bodyDef);
  bodyes.push_back(body);

  // Define another box shape for our dynamic body.
  b2PolygonShape dynamicBox;
  float d_width = 2.0f;
  float d_height = 2.0f;
  dynamicBox.SetAsBox(d_width/2, d_height/2);

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;
  body->CreateFixture(&fixtureDef);

  //give the body some spin and some motion to make it interesting
  body->SetAngularVelocity(0.8f);
  b2Vec2 initial_v (1.6f, 0.0f);
  body->SetLinearVelocity(initial_v);

  // Prepare for simulation. Typically we use a time step of 1/60 of a
  // second (60Hz) and 10 iterations. This provides a high quality simulation
  // in most game scenarios.
  float32 timeStep = 1.0f / FPS;
  int32 velocityIterations = 10;
  int32 positionIterations = 10;

    //prepare for drawing
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *ground = NULL;
    ALLEGRO_BITMAP *box = NULL;
    bool redraw = true;
    //ALWAYS check return values of these Allegro functions. It will save you headaches later.
    if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
    }
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
    }
    //typically, if using Box2D, you will have everything operating with Box2D coordinates throughout your game.
    //This is because Box2D methods return in Box2D coordinates.
    //Then, when drawing, convert them to "Allegro coordinates" using the scale.
    //Here, the g_ variables are in Box2D coordinates, so we convert them to Allegro coordinates to represent the box on the screen.
    ground = al_create_bitmap(g_width*PIX_METER, g_height*PIX_METER);
    if(!ground) {
      fprintf(stderr, "failed to create ground bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
    }
    box = al_create_bitmap(d_width*PIX_METER, d_height*PIX_METER);
    if(!box) {
      fprintf(stderr, "failed to create box bitmap!\n");
      al_destroy_bitmap(ground);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
    }

    al_set_target_bitmap(ground);
    al_clear_to_color(al_map_rgb(255, 0, 255));
    al_set_target_bitmap(box);
    al_clear_to_color(al_map_rgb(128, 128, 255));

    al_set_target_bitmap(al_get_backbuffer(display));

    event_queue = al_create_event_queue();
    if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(ground);
      al_destroy_bitmap(box);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
    }

	al_install_mouse();

	al_register_event_source(event_queue,al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    al_start_timer(timer);

	bool mDown = false;
	float mX = 0;
	float mY = 0;

  // This is our little game loop.
  while (1)
  {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            world.Step(timeStep, velocityIterations, positionIterations);
            world.ClearForces();
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			mDown = true;
			mX = ev.mouse.x/PIX_METER;
			mY = ev.mouse.y/PIX_METER;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			mDown = false;
			mX = ev.mouse.x/PIX_METER;
			mY = ev.mouse.y/PIX_METER;
		}


        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));

            //draw the ground
            //note that drawing is from the top-left corner,
            //and NOT the center as it is in Box2D.
            b2Vec2 g_pos = groundBody->GetPosition(); //the center
            //we need to get the top left corner from this center
            float g_x = g_pos.x - g_width/2;
            float g_y = g_pos.y - g_height/2;
            //now convert the coordinates and draw
            al_draw_bitmap(ground, g_x*PIX_METER, g_y*PIX_METER, 0);





			if(mDown)
			{


				b2BodyDef bodyDef;
				bodyDef.type = b2_dynamicBody;
				bodyDef.position.Set(mX, mY); //top of the screen
				b2Body* body = world.CreateBody(&bodyDef);
				bodyes.push_back(body);

				// Define another box shape for our dynamic body.
				b2PolygonShape dynamicBox;
				float d_width = 2.0f;
				float d_height = 2.0f;
				dynamicBox.SetAsBox(d_width/2, d_height/2);

				b2FixtureDef fixtureDef;
				fixtureDef.shape = &dynamicBox;
				fixtureDef.density = 1.0f;
				fixtureDef.friction = 0.3f;
				body->CreateFixture(&fixtureDef);

				//give the body some spin and some motion to make it interesting
				body->SetAngularVelocity(0.8f);
				b2Vec2 initial_v (1.6f, 0.0f);
				body->SetLinearVelocity(initial_v);



			}






			for(std::list<b2Body *>::iterator it = bodyes.begin(); it != bodyes.end(); ++it)
			{
				//if((*it)->getID() == _PLAYER)
				//	dynamic_cast<Player *>(*it)->MoveDown();


				//do the same for the other box
				b2Vec2 b_pos = (*it)->GetPosition();
				float32 angle = (*it)->GetAngle();
				//When using the rotated drawing function, the center is pinned to a point.
				//so essentially, we can draw from the center.
				float b_x = b_pos.x;
				float b_y = b_pos.y;

				float midx = al_get_bitmap_width(box)/2;
				float midy = al_get_bitmap_height(box)/2;

				al_draw_rotated_bitmap(box, midx, midy, b_x*PIX_METER, b_y*PIX_METER, angle, 0);
			}
            al_flip_display();
        }

  }

  // When the world destructor is called, all bodies and joints are freed. This can
  // create orphaned pointers, so be careful about your world management.

  return 0;
}
};