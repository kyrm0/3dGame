#include "Input.h"

void Input::processInput(SDL_Event e, Cube& c, float dt)
{
    SDL_PumpEvents(); // ensure keyboard state is current
    const bool* ks = SDL_GetKeyboardState(nullptr);
    double rotSpeed = 1.5;
    double dax = 0, day = 0, daz = 0;
    double moveSpeed = 50.0;
    float dx = 0, dy = 0;

    // Fix: change type from const Uint8* to const bool*
    
    if (ks[SDL_SCANCODE_A]) { day -= rotSpeed* dt; SDL_Log("A"); } // pitch up
    if (ks[SDL_SCANCODE_D]) { day += rotSpeed*dt; SDL_Log("D"); } //pitch down
    if (ks[SDL_SCANCODE_W]) { dax -= rotSpeed*dt; SDL_Log("W"); } //pitch left
    if (ks[SDL_SCANCODE_S]) { dax += rotSpeed*dt; SDL_Log("S"); } //pitch right

    if (ks[SDL_SCANCODE_Q]) { daz -= rotSpeed * dt; SDL_Log("Q"); }
    if (ks[SDL_SCANCODE_E]) { daz += rotSpeed * dt; SDL_Log("E"); }

    
    if (ks[SDL_SCANCODE_LEFT])  dx -= moveSpeed * dt;
    if (ks[SDL_SCANCODE_RIGHT]) dx += moveSpeed * dt;
    if (ks[SDL_SCANCODE_UP])    dy -= moveSpeed * dt;
    if (ks[SDL_SCANCODE_DOWN])  dy += moveSpeed * dt;
    
    c.update(dax, day, daz);

    if (auto* obj = object::getObjectById(ID_RECT1)) {
        obj->moveBy(dx, dy);
    }

}

float Input::getFrameDeltaTime(Uint64& last)
{
	Uint64 now = SDL_GetPerformanceCounter();
	if (last == 0) { last = now; return 0.0f; }   // first frame
	Uint64 freq = SDL_GetPerformanceFrequency();
	float dt = float(now - last) / float(freq);   // seconds
	last = now;
	return dt;
}
