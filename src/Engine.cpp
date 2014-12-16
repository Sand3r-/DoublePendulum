#include "Engine.h"

Engine::Engine(int w, int h, int fps):WIDTH(w), HEIGHT(h), FPS(fps) {};

void Engine::Init()
{
	done = false;
	
	al_init(); //Initialises the allegro library
    al_init_image_addon();
	al_init_primitives_addon();
    
    display = al_create_display(WIDTH, HEIGHT);
	al_set_window_title(display, "Double Pendulum Simulation");
    
	al_install_keyboard(); //Installs keyboard driver
    al_install_mouse(); //installs mouse driver

    eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_mouse_event_source());

    timer = al_create_timer(1.0f / FPS);
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_start_timer(timer);

	doublePendulum = new DoublePendulum();
	doublePendulum->Init(150, 150, 4, 4, 0.5, 0.5, 400, 200);
    
}

void Engine::InputHandler()
{
	if(event.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		switch(event.keyboard.keycode)
		{
		case ALLEGRO_KEY_ESCAPE:
			done = true;
			break;
		case ALLEGRO_KEY_DOWN:
			doublePendulum->IncreaseRodLength(2, -5.0);
			break;
		case ALLEGRO_KEY_UP:
			doublePendulum->IncreaseRodLength(2, 5.0);
			break;
		case ALLEGRO_KEY_W:
			doublePendulum->IncreaseRodLength(1, 5.0);
			break;
		case ALLEGRO_KEY_S:
			doublePendulum->IncreaseRodLength(1, -5.0);
			break;
		case ALLEGRO_KEY_LEFT:
			doublePendulum->IncreaseParticleMass(2, -1.0);
			break;
		case ALLEGRO_KEY_RIGHT:
			doublePendulum->IncreaseParticleMass(2, 1.0);
			break;
		case ALLEGRO_KEY_A:
			doublePendulum->IncreaseParticleMass(1, -1.0);
			break;
		case ALLEGRO_KEY_D:
			doublePendulum->IncreaseParticleMass(1, 2.0);
			break;
		}
	}
	else if(event.type == ALLEGRO_EVENT_KEY_UP)
	{
		switch(event.keyboard.keycode)
		{
		case ALLEGRO_KEY_ESCAPE:
			done = true;
			break;
		}
	}
	else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		done = true;
	else if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		int z = event.mouse.z;
		if (z > prev_z)
		{
			doublePendulum->IncreaseAngle(1, 0.1);
			doublePendulum->IncreaseAngle(2, 0.1);
		}
		else if (z < prev_z)
		{
			doublePendulum->IncreaseAngle(1, -0.1);
			doublePendulum->IncreaseAngle(2, -0.1);
		}
		prev_z = z;
	}
}

void Engine::Update()
{
	if(event.type == ALLEGRO_EVENT_TIMER)
	{
		render = true;
		for(int i = 0; i < 150; i++) doublePendulum->Update();
	}
}

void Engine::Render()
{
	if(render && al_is_event_queue_empty(eventQueue))
	{
		render = false;
		
		doublePendulum->Render();

		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
	}
}

void Engine::Destroy()
{
	delete doublePendulum;

	al_destroy_display(display);
	al_destroy_event_queue(eventQueue);
	al_destroy_timer(timer);
}

bool Engine::Done() const
{
	return !done;
}
