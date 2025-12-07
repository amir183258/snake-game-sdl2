#ifndef SNAKE_H
#define SNAKE_H

#include <functional>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <deque>

enum class direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Snake {
private:
	direction current_dir;
	direction previous_dir;

	struct playground_position {
		size_t r, c;
	};

	SDL_Texture* head_texture;
	SDL_Texture* body_texture;

	std::deque<playground_position> snake;

	bool eat_apple;

	// velocity handling
	size_t move_delay = 10;				// every move_delay frames snake moves
	size_t current_frame = 0;

	// snake size
	size_t snake_size = 3;

	void draw_head(SDL_Renderer* renderer);
	void draw_body(SDL_Renderer* renderer);

	bool check_self_eat();
	void update_playground_board();
	void check_apple();

	void move_snake();

	Snake();
public:
	static Snake& instance() {
		static Snake snake_instance;
		return snake_instance;
	}

	void set_direction(direction dir) { current_dir = dir; }
	void draw(SDL_Renderer* renderer);
	void update();

	size_t get_snake_size() { return snake_size; }

	// callbacks
	std::function<void()> collision_call_back;
	std::function<void(int score)> eat_apple_call_back;

	~Snake();
};

#endif
