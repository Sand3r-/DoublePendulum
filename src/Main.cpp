#include <iostream>
#include "Engine.h"

using namespace std;

int main()
{
	Engine *engine = new Engine();

	engine->Init();

	while(engine->Done())
	{
		engine->Update();
		engine->Render();

		al_wait_for_event(engine->GetRedrawQueue(), NULL);
		al_flush_event_queue(engine->GetRedrawQueue());
	}
	
	engine->Destroy();

	delete engine;

	return 0;
}