/*
This is a library designed to help you write software rendered programs in C with SDL2, without actually using SDL2.
It also abstracts the main function, I may add an option to not do this.
contributions welcome.

please credit if any of this code is used
by Hasan Sabri, DO NOT REMOVE CREDIT
*/

#ifndef EASYRENDER_H
#define EASYRENDER_H
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdbool.h>

unsigned WIDTH = 960;
unsigned HEIGHT = 540;

SDL_Window* window;
SDL_Surface* surface;


uint32_t CLEAR_COLOR;
uint32_t* pixels;
bool keys[512];


#ifdef EASYRENDER
uint32_t rgb(uint8_t r, uint8_t g, uint8_t b) {
	return SDL_MapRGB(surface->format, r, g, b);
}
void pix(int x, int y, uint32_t c) {
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
	pixels[y * WIDTH + x] = c;
}
void rect(int x, int y, int w, int h, uint32_t c) {
    for (int yo = 0; yo < h; yo++) {
        for (int xo = 0; xo < w; xo++) {
            pix(x + xo, y + yo, c);
        }
    }
}
void line(int x0, int y0, int x1, int y1, uint32_t c) {
	float dx = x1 - x0;
	float dy = y1 - y0;
	
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	
	float xinc = dx / steps,
		  yinc = dy / steps;
	
	float x = x0,
		  y = y0;
	
	for (int i = 0; i <= steps; i++) {
		pix(floor(x), floor(y), c);
		x += xinc;
		y += yinc;
	}
}
void clear() {
	memset(pixels, CLEAR_COLOR, sizeof(uint32_t) * WIDTH * HEIGHT);
}
void init();
void setup();

void update(float deltaTime);
void draw();

int main() {
	init();
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(window);
	pixels = (uint32_t*)surface->pixels;
	bool quit = false;
	SDL_Event e;
	float frameTime = SDL_GetTicks();
	float lastFrameTime;
	float deltaTime;
	setup();
	while (!quit) {
		lastFrameTime = frameTime;
		frameTime = SDL_GetTicks();
		deltaTime = frameTime - lastFrameTime;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				keys[e.key.keysym.scancode] = true;
			}
			else if (e.type == SDL_KEYUP) {
				keys[e.key.keysym.scancode] = false;
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
void rect(int x, int y, int w, int h, uint32_t c);
void line(int x0, int y0, int x1, int y1, uint32_t c);
void clear(uint32_t c);
#endif

#endif
