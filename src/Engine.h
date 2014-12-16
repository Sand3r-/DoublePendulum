#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "DoublePendulum.h"

class Engine
{
	//const vars
	const int WIDTH;
	const int HEIGHT;
	const int FPS;

	//primitive variables
	bool done;
	bool render;

	//project variables
	DoublePendulum *doublePendulum;
	int prev_z; //for mouse wheel input

	//allegro variables
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *eventQueue;
	ALLEGRO_EVENT event;
	ALLEGRO_TIMER *timer;
	//ALLEGRO_FONT *font18;

public:
	Engine(int w, int h, int fps);
	//~Engine(void);

	void Init();
	void InputHandler();
	void Update();
	void Render();
	void Destroy();

	bool Done() const;

	ALLEGRO_EVENT_QUEUE * GetEventQueue() const { return eventQueue; }
	ALLEGRO_EVENT * GetEvent() { return &event; }


};