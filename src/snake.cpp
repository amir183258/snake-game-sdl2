#include <SDL2/SDL.h>
#include "./snake.hpp"
#include "./playground.hpp"
#include "./game.hpp"
#include "./apple.hpp"

Snake::Snake() {
	// load snake textures
	head_texture = load_texture("./assets/head.png", Game::instance().get_renderer());
	body_texture = load_texture("./assets/body.png", Game::instance().get_renderer());
	
	// find the center of playground
	size_t rows_center = Playground::instance().get_rows() / 2 - 1;
	size_t cols_center = Playground::instance().get_cols() / 2 + 1;

	// snake apple flag
	eat_apple = false;

	// snake size
	snake_size = 3;

	// create 3 tiles snake and mark them on the board
	current_dir = direction::RIGHT;
	previous_dir = direction::RIGHT;

	snake.push_front({rows_center, cols_center - 2});
	Playground::instance().set_playground_board(rows_center, cols_center - 2, true);

	snake.push_front({rows_center, cols_center - 1});
	Playground::instance().set_playground_board(rows_center, cols_center - 1, true);

	snake.push_front({rows_center, cols_center - 0});
	Playground::instance().set_playground_board(rows_center, cols_center - 0, true);
}

// drawing snake
void Snake::draw_head(SDL_Renderer* renderer) {
	// destination rectangle
	SDL_Rect dest_rect;
	dest_rect.w = Playground::instance().get_tile_dimension();
	dest_rect.h = Playground::instance().get_tile_dimension();

	// set x and y of destination rectangle
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

	for (size_t i = 1; i < snake.size(); ++i) { SDL_Point draw_pos = Playground::instance().get_tile_pos(snake[i].r, snake[i].c);
		dest_rect.x = draw_pos.x;
		dest_rect.y = draw_pos.y;

			
		SDL_RenderCopyEx(renderer, body_texture, nullptr,
				&dest_rect, 0, nullptr, SDL_FLIP_NONE);
	}
}

void Snake::draw(SDL_Renderer* renderer) {

	draw_head(renderer);

	draw_body(renderer);
}

// update snake status
void Snake::move_snake() {
	playground_position head = snake.front();

	// updating playground board
	Playground::instance().set_playground_board(head.r, head.c, false);

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

	if (new_row == snake[1].r && new_col == snake[1].c) {
		current_dir = previous_dir;
		move_snake();

		return;
	}

	head.r = new_row;
	head.c = new_col;

	// updating playground board
	Playground::instance().set_playground_board(head.r, head.c, true);

	snake.push_front(head);
}

void Snake::check_apple() {
	if (snake.front().r == Apple::instance().get_apple_row() &&
			snake.front().c == Apple::instance().get_apple_col()) {
		eat_apple = true;
		++snake_size;

		Apple::instance().spawn();
	}
}

void Snake::update() {
	++current_frame;
	if (current_frame >= move_delay) {
		move_snake();

		check_apple();

		if (eat_apple)
			eat_apple = false;
		else {
			Playground::instance().set_playground_board(snake.back().r, snake.back().c, false);
			snake.pop_back();
		}

		previous_dir = current_dir;				// for checking wrong direction toward the body of snake

		current_frame = 0;
	}
}

Snake::~Snake() {
	SDL_DestroyTexture(head_texture);
	SDL_DestroyTexture(body_texture);

	SDL_Log("destroying snake textures...");
}
