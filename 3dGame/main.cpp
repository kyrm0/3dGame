#include<SDL3/SDL.h>
#include"window.h"
#include "Rectangle.h"
#include "Input.h"
#include "Cube.h"


static bool initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	return true;
}


static int _main(void) {
	if (!initSDL()) return 1;

	const int W = 800;
	const int H = 600;

	Window* window = new Window("3D Game", W, H, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	/*object::add(std::make_unique<Rectangle>(200, 200, 150, 150, SDL_Color{ 0,255,0,255 }, ID_RECT1));*/


	window->mainLoop();

	delete window;
	SDL_Quit();
	return 0;
}


#ifdef _DEBUG

int main(void) {
	return _main();
}
#endif // DEBUG




#ifdef NDEBUG
#include <Windows.h>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	return _main();
}

#endif // NDEBUG


