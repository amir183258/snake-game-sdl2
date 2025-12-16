#include <iostream>
#include <string>
#include <cstdlib>					// for making random variables
#include <ctime>					// for making random variables
#include <SDL2/SDL.h>
#include "./playground.hpp"
#include "./game.hpp"
#include "./snake.hpp"

Playground::Playground() {

	// playground dimensions
	playground_bbox.w = number_of_cols * tile_dimension;
	playground_bbox.h = number_of_rows * tile_dimension;

	// window size
	int window_w, window_h;
	SDL_GetWindowSize(Game::instance().get_window(), &window_w, &window_h);

	// playground position
	playground_bbox.x = (window_w - playground_bbox.w) / 2;
	playground_bbox.y = (window_h - playground_bbox.h) / 2 + 25;			// 25 pixels for score monitor

	// playground textures
	tile1 = load_texture("./assets/tile1.png", Game::instance().get_renderer());
	if (!tile1) {
		std::cerr << "error loading tile1 texture for playground: " << IMG_GetError() << std::endl;
		exit(1);
	}
	tile2 = load_texture("./assets/tile2.png", Game::instance().get_renderer());
	if (!tile2) {
		std::cerr << "error loading tile2 texture for playground: " << IMG_GetError() << std::endl;
		exit(1);
	}

	playground_board.resize(number_of_rows * number_of_rows, false);

	reset_playground_board();
}

void Playground::reset_playground_board() {
	// set all board elements to fasle
	std::fill(playground_board.begin(), playground_board.end(), false);
}

void Playground::draw(SDL_Renderer* renderer) {
	SDL_Rect dest_rect;
	dest_rect.x = playground_bbox.x;
	dest_rect.y = playground_bbox.y;
	dest_rect.w = tile_dimension;
	dest_rect.h = tile_dimension;

	// SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);					for debug
	for (size_t i = 0; i < number_of_rows; ++i) {
		for (size_t j = 0; j < number_of_cols; ++j) {
			// SDL_RenderDrawRect(renderer, &dest_rect);				for debug

			if ((i + j) % 2)
				SDL_RenderCopy(renderer, tile1, nullptr, &dest_rect);
			else
				SDL_RenderCopy(renderer, tile2, nullptr, &dest_rect);

			dest_rect.x += dest_rect.w;
		}
		dest_rect.x = playground_bbox.x;
		dest_rect.y += dest_rect.h;
	}

	// SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);					for debug
	// SDL_RenderDrawRect(renderer, &playground_bbox);					for debug
	print_playground();
}

void Playground::set_dimension(size_t r, size_t c) {
	if (r < 5 || c < 5) {
		SDL_Log("invalid dimensions for playground");
		return;
	}

	number_of_rows = r;
	number_of_cols = c;
}

void Playground::set_tile_dimension(size_t s) {
	tile_dimension = s;
}

SDL_Point Playground::get_tile_pos(size_t r, size_t c) {
	if (r >= number_of_rows || c >= number_of_cols ||
			r < 0 || c < 0) {
		SDL_Log("wrong row or col in get_tile_pos(...) in background");
		return {0, 0};

	}

	SDL_Point pos;

	pos.x = c * tile_dimension + playground_bbox.x; 
	pos.y = r * tile_dimension + playground_bbox.y;

	return pos;
}

void Playground::set_playground_board(size_t r, size_t c, bool value) {
	if (r < 0 || c < 0 || r >= number_of_rows || c >= number_of_cols) {
		SDL_Log("wrong row or col for playground board");
		return;
	}

	size_t idx = r * number_of_cols+ c + 1;
	playground_board[idx] = value;
}

void Playground::print_playground() {
	for (size_t i = 0; i < number_of_rows; ++i) {
		std::string line = "";
		for (size_t j = 0; j < number_of_cols; ++j)
			if (playground_board[i * number_of_cols+ j + 1])
				line += "1";
			else
				line += "0";
		SDL_Log("%s", line.c_str());
	}
}

SDL_Point Playground::get_free_playground_position() {
	// setting random stuff
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// making random pos
	size_t free_board_spaces = playground_board.size() -
		Snake::instance().get_snake_size();
	size_t free_space_position = std::rand() % free_board_spaces;

	size_t real_position = 0;
	while (free_space_position) {
		if (!playground_board[real_position])				// if there were no snake then add real position
			--free_space_position;
		++real_position;
	}

	SDL_Point result;
	result.x = real_position / number_of_cols;
	result.y = real_position % number_of_cols;

	return result;
}

Playground::~Playground() {
	SDL_Log("destroying playground textures...");

	SDL_DestroyTexture(tile1);
	SDL_DestroyTexture(tile2);
}
