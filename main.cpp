#include <iostream>

#include <SDL/SDL.h>

#include "game.h"
#include "engine.h"

using namespace std;
using namespace gs;

int main(int argc, char* argv[])
{
	Engine* engine = new Engine();
	engine->start();
	delete engine;

	return 0;
}
