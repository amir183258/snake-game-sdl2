#include <SDL2/SDL.h>
#include "./playground.hpp"
#include "./game.hpp"

Playground::Playground() {

	// playground dimensions
	playground_bbox.w = number_of_cols * tile_dimension;
	playground_bbox.h = number_of_rows * tile_dimension;

	// window size
	int window_w, window_h;
	SDL_GetWindowSize(Game::instance().get_window(), &window_w, &window_h);

	// playground position
	playground_bbox.x = (window_w - playground_bbox.w) / 2;
	playground_bbox.y = (window_h - playground_bbox.h) / 2;

	// playground textures
	tile1 = load_texture("./assets/tile1.png", Game::instance().get_renderer());
	tile2 = load_texture("./assets/tile2.png", Game::instance().get_renderer());

	// set all board elements to fasle
	playground_board.resize(number_of_rows * number_of_cols, false);
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

	size_t idx = r * number_of_rows + c;
	playground_board[idx] = value;
}

Playground::~Playground() {
	SDL_Log("destroying playground textures...");

	SDL_DestroyTexture(tile1);
	SDL_DestroyTexture(tile2);
}
