#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include "object.h"
class Window
{
public:
	Window(const char* title, int w, int h, SDL_WindowFlags flags);
	inline SDL_Renderer* getRenderer() { return r; }
	inline SDL_Window* getWindow() { return w; }
	void mainLoop();
	~Window();

private:
	SDL_Window* createWindow();
	SDL_Renderer* createRenderer();
	SDL_GLContext createGLContext();
	SDL_GLContext glContext;
	SDL_Window* w;
	SDL_Renderer* r;
	const char* title = "";
	int width;
	int height;
	object* o;
	SDL_WindowFlags flags;
	void clearScreen();
	void makeObjects2d(object* o);
};

