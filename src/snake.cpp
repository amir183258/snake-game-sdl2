#include <SDL2/SDL.h>
#include "./snake.hpp"
#include "./playground.hpp"
#include "./game.hpp"

Snake::Snake() {
	// load snake textures
	head_texture = load_texture("./assets/head.png", Game::instance().get_renderer());
	body_texture = load_texture("./assets/body.png", Game::instance().get_renderer());
	
	// find the center of playground
	size_t rows_center = Playground::instance().get_rows() / 2 - 1;
	size_t cols_center = Playground::instance().get_cols() / 2 + 1;

	// create 3 tiles snake
	snake.push_front({rows_center - 2, cols_center});
	snake.push_front({rows_center - 1, cols_center});
	snake.push_front({rows_center + 0, cols_center});
}

void Snake::draw(SDL_Renderer* renderer) {
	SDL_Rect dest_rect;
	dest_rect.w = Playground::instance().get_tile_dimension();
	dest_rect.h = Playground::instance().get_tile_dimension();

	for (size_t i = 0; i < snake.size(); ++i) {
		SDL_Point draw_pos = Playground::instance().get_tile_pos(snake[i].r, snake[i].c);
		dest_rect.x = draw_pos.x;
		dest_rect.y = draw_pos.y;

		SDL_RenderCopy(renderer, body_texture, nullptr, &dest_rect);

	}

}

Snake::~Snake() {
	SDL_DestroyTexture(head_texture);
	SDL_DestroyTexture(body_texture);

	SDL_Log("destroying snake textures...");
}
