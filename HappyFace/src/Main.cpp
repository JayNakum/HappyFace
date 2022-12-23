
#include "HappyFace/Engine.h"


int main()
{
	Engine* engine = new Engine();

	engine->go();

	delete engine;
}