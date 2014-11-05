#include "Engine.h"

void Engine::Init()
{
	done = false;
	
	al_init(); //Initialises the allegro library
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    
    display = al_create_display(WIDTH, HEIGHT);
	al_set_window_title(display, "Double Pendulum Simulation");
    
	al_install_keyboard(); //Installs keyboard driver
    
    eventQueue = al_create_event_queue();
    redrawQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());

    timer = al_create_timer(1.0f / FPS);
    al_register_event_source(redrawQueue, al_get_timer_event_source(timer));
    al_start_timer(timer);

	doublePendulum = new DoublePendulum();
    
}

void Engine::Update()
{
	doublePendulum->Update();
}

void Engine::Render()
{
	doublePendulum->Render(); //????
}

void Engine::Destroy()
{
	delete doublePendulum;

	al_destroy_display(display);
	al_destroy_event_queue(eventQueue);
	al_destroy_event_queue(redrawQueue);
	al_destroy_timer(timer);
	al_destroy_font(font18);
}

bool Engine::Done() const
{
	return done;
}
