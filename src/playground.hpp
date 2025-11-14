#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "./game.hpp"

class Playground {
private:
	SDL_Rect playground_bbox;

	size_t number_of_rows = 25;
	size_t number_of_cols = 20;

	size_t tile_dimension = 20;								// tiles are square

	// tile textures
	SDL_Texture* tile1;
	SDL_Texture* tile2;

	Playground();

public:
	static Playground& instance() {
		static Playground playground_instance;
		return playground_instance;
	}

	void draw(SDL_Renderer* renderer);

	// set playground dimensions
	void set_dimension(size_t r, size_t c);
	void set_tile_dimension(size_t s);

	// get playground bbox
	SDL_Rect get_bbox() { return playground_bbox; }

	~Playground();
};

#endif
