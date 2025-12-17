#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <vector>
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

	// playground borad; this board is used to put apples and check self eating.
	std::vector<bool> playground_board;

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

	// get playground rows, cols and tile dimension
	size_t get_rows() { return number_of_rows; }
	size_t get_cols() { return number_of_cols; }
	size_t get_tile_dimension() { return tile_dimension; }

	// get a tile position (top left corner of a tile)
	SDL_Point get_tile_pos(size_t r, size_t c);

	// set playground board elements
	void set_playground_board(size_t r, size_t c, bool value);

	// get playground board, its size and its value (status)
	std::vector<bool> get_playground_board() { return playground_board; }
	size_t get_playground_board_size() { return number_of_rows * number_of_cols; }
	bool get_playground_pos_status(size_t r, size_t c) { return playground_board[r * number_of_cols + c]; }

	// print playground
	void print_playground();

	// checks if r and c are valid
	bool is_valid_coords(int r, int c);

	// reset playground
	void reset_playground_board();

	// get a random free position (to draw apple or other staff)
	SDL_Point get_free_playground_position();

	~Playground();
};

#endif
