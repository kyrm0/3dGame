#include "window.h"
#include "object.h"
#include "Rectangle.h"
#include "Input.h"
#include "Cube.h"


Window::Window(const char* title, int w, int h, SDL_WindowFlags flags)
	:title(title), width(w), height(h), flags(flags)
{
	this->w = createWindow(); // Initialize to nullptr
	this->r = createRenderer(); // Initialize to nullptr
	/*this->glContext = createGLContext();*/
	SDL_SetRenderVSync(this->r, true);
}
void Window::mainLoop()
{
	Cube cube(100, this->width * 0.5, this->height * 0.5);
	SDL_Log("made cube at %f %f", (double)this->width * 0.5, (double)this->height * 0.5);
	bool isRunning = true;
	Uint64 last = SDL_GetPerformanceCounter();
	while (isRunning) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				return;
			}

		}

		
		
		float dt = Input::getFrameDeltaTime(last);
		Input::processInput(event, cube, dt);
		
		clearScreen();

		SDL_SetRenderDrawColor(this->r, 0, 0, 0, 255);
		// Render stuff here
		object::drawObjects(this->r);
		cube.draw(this->r, false);
		
		SDL_RenderPresent(this->r);
	}
}
// Replace SDL_GL_DeleteContext with SDL_GL_DestroyContext in the destructor
Window::~Window()
{
	/*if (this->glContext) SDL_GL_DestroyContext(this->glContext);*/
	if (this->r) SDL_DestroyRenderer(this->r);
	SDL_DestroyWindow(this->w);
}

SDL_Window* Window::createWindow()
{
	SDL_Log("Window created %s ", title);
	return SDL_CreateWindow(this->title, this->width, this->height, this->flags);
}

SDL_Renderer* Window::createRenderer()
{
	return SDL_CreateRenderer(this->w, nullptr);
}

SDL_GLContext Window::createGLContext()
{
	return SDL_GL_CreateContext(this->w);
}

void Window::clearScreen()
{
	SDL_SetRenderDrawColor(this->r, 255, 255, 255, 255);
	SDL_RenderClear(this->r);
}


