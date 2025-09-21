#include "Input.h"

void Input::processInput(SDL_Event e, float deltaTT)
{
	const bool* ks = SDL_GetKeyboardState(nullptr);

	int ax = 0, ay = 0;
	if (ks[SDL_SCANCODE_A]) ax -= 1;
	if (ks[SDL_SCANCODE_D]) ax += 1;
	if (ks[SDL_SCANCODE_W]) ay -= 1;
	if (ks[SDL_SCANCODE_S]) ay += 1;

	// normalize so diagonal speed == straight speed
	float vx = (float)ax, vy = (float)ay;
	float len = std::sqrt(vx * vx + vy * vy);
	if (len > 0.0f) { vx /= len; vy /= len; }

	float speed = 200.0f;   // pixels per second
	float dt = deltaTT; // compute from timing
	auto* obj = object::getObjectById(ID_RECT1);
	if (obj) obj->setPos(obj->getX() + vx * speed * dt, obj->getY() + vy * speed * dt);
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
