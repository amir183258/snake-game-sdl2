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
	current_dir = direction::RIGHT;

	snake.push_front({rows_center, cols_center - 2});
	snake.push_front({rows_center, cols_center - 1});
	snake.push_front({rows_center, cols_center - 0});
}

// drawing snake
void Snake::draw_head(SDL_Renderer* renderer) {
	// destination rectangle
	SDL_Rect dest_rect;
	dest_rect.w = Playground::instance().get_tile_dimension();
	dest_rect.h = Playground::instance().get_tile_dimension();

	// set width and height of destination rectangle
	SDL_Point draw_pos = Playground::instance().get_tile_pos(snake.front().r, snake.front().c);
	dest_rect.x = draw_pos.x;
	dest_rect.y = draw_pos.y;

	// draw head
	int rotation_angle;
	switch (current_dir) {
	case direction::UP:
		rotation_angle = 0;
		break;
	case direction::RIGHT:
		rotation_angle = 90;
		break;
	case direction::DOWN:
		rotation_angle = 180;
		break;
	case direction::LEFT:
		rotation_angle = 270;
	}

	SDL_RenderCopyEx(renderer, head_texture, nullptr,
			&dest_rect, rotation_angle, nullptr, SDL_FLIP_NONE);
}

void Snake::draw_body(SDL_Renderer* renderer) {
	SDL_Rect dest_rect;
	dest_rect.w = Playground::instance().get_tile_dimension();
	dest_rect.h = Playground::instance().get_tile_dimension();

	for (size_t i = 1; i < snake.size(); ++i) {
		SDL_Point draw_pos = Playground::instance().get_tile_pos(snake[i].r, snake[i].c);
		dest_rect.x = draw_pos.x;
		dest_rect.y = draw_pos.y;

			
		SDL_RenderCopyEx(renderer, body_texture, nullptr,
				&dest_rect, 90 /* rotation angle */, nullptr, SDL_FLIP_NONE);
	}
}

void Snake::draw(SDL_Renderer* renderer) {

	draw_head(renderer);

	draw_body(renderer);
}

// update snake status
void Snake::move_snake() {
	playground_position head = snake.front();

	size_t new_row = head.r;
	size_t new_col = head.c;

	switch (current_dir) {
	case direction::UP:
		--new_row;
		break;
	case direction::RIGHT:
		++new_col;
		break;
	case direction::DOWN:
		++new_row;
		break;
	case direction::LEFT:
		--new_col;
	}

	if (new_row != snake[1].r || new_col != snake[1].c) {
		head.r = new_row;
		head.c = new_col;
	}

	snake.push_front(head);
	snake.pop_back();
}

void Snake::update() {
	++current_frame;
	if (current_frame >= move_delay) {
		move_snake();
		current_frame = 0;
	}
}

Snake::~Snake() {
	SDL_DestroyTexture(head_texture);
	SDL_DestroyTexture(body_texture);

	SDL_Log("destroying snake textures...");
}
