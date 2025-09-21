#pragma once
#include <SDL3/SDL.h>
#include "object.h"


class Input
{

public:
	static void processInput(SDL_Event e, float deltaTT);
	static float getFrameDeltaTime(Uint64& last);

};

