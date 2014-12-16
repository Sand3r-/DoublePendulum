#include <iostream>
#include "Engine.h"

using namespace std;

int main()
{
	Engine *engine = new Engine(800, 600, 60);

	engine->Init();

	while(engine->Done())
	{
		engine->InputHandler();
		engine->Update();
		engine->Render();

		al_wait_for_event(engine->GetEventQueue(), engine->GetEvent());
		al_flush_event_queue(engine->GetEventQueue());
	}
	
	engine->Destroy();

	delete engine;

	return 0;
}