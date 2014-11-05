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

	//allegro variables
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *eventQueue;
	ALLEGRO_EVENT_QUEUE *redrawQueue;
	ALLEGRO_EVENT event;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *font18;

public:
	Engine(void);
	~Engine(void);

	void Init();
	void Update();
	void Render();
	void Destroy();

	bool Done() const;

	ALLEGRO_EVENT_QUEUE * GetRedrawQueue() const { return redrawQueue; }
	ALLEGRO_EVENT GetEvent() const { return event; }


};