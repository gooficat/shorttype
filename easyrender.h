#ifndef EASYRENDER_H
#define EASYRENDER_H
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdbool.h>

#define WIDTH 960
#define HEIGHT 480

SDL_Window* window;
SDL_Surface* surface;

uint32_t* pixels;
bool keys[512];

uint32_t rgb(uint8_t r, uint8_t g, uint8_t b);
void pix(int x, int y, uint32_t c);
void clear(uint32_t c);

#ifdef EASYRENDER_H
uint32_t rgb(uint8_t r, uint8_t g, uint8_t b) {
	return SDL_MapRGB(surface->format, r, g, b);
}
void pix(int x, int y, uint32_t c) {
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
	pixels[y * WIDTH + x] = c;
}
void clear(uint32_t c) {
	memset(pixels, c, sizeof(uint32_t));
}
void setup();

void update(float deltaTime);
void draw();

int main() {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(window);
	pixels = (uint32_t*)surface->pixels;
	setup();
	bool quit = false;
	SDL_Event e;
	float frameTime = SDL_GetTicks();
	float lastFrameTime;
	float deltaTime;
	while (!quit) {
		lastFrameTime = frameTime;
		frameTime = SDL_GetTicks();
		deltaTime = frameTime - lastFrameTime;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				keys[e.key.keysym.sym] = true;
			}
			else if (e.type == SDL_KEYUP) {
				keys[e.key.keysym.sym] = false;
			}
		}
		update(deltaTime);
		SDL_LockSurface(surface);
		
		draw();
		
		SDL_UnlockSurface(surface);
		SDL_UpdateWindowSurface(window);
	}
	
	SDL_DestroyWindow(window);
	SDL_Quit();
}
#else
uint32_t rgb(uint8_t r, uint8_t g, uint8_t b);
void pix(int x, int y, uint32_t c);
void clear(uint32_t c);
#endif

#endif
