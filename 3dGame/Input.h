#pragma once
#include <SDL3/SDL.h>
#include "object.h"
#include "Cube.h"


class Input
{

public:
	static void processInput(SDL_Event e, Cube& c,float dt);
	static float getFrameDeltaTime(Uint64& last);
	
	static void processScrollWheelInput(SDL_Event e, Cube& c);

};

