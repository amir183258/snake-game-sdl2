#ifndef APPLE_H
#define APPLE_H

#include <SDL2/SDL.h>

class Apple {
private:
	// apple texture in assets
	SDL_Texture* apple_texture;

	// apple row and column on the background
	size_t r;
	size_t c;

	// spawning apple on the playground board

	// singleton constrcutor
	Apple();

public:
	static Apple& instance() {
		static Apple apple_instance;
		return apple_instance;
	}

	void spawn();
	void draw(SDL_Renderer* renderer);

	// get apple positions
	size_t get_apple_row() { return r; }
	size_t get_apple_col() { return c; }

	~Apple();
};

#endif
