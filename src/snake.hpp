#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <deque>

class Snake {
private:
	struct playground_position {
		size_t r, c;
	};

	SDL_Texture* head_texture;
	SDL_Texture* body_texture;

	std::deque<playground_position> snake;

	Snake();
public:
	static Snake& instance() {
		static Snake snake_instance;
		return snake_instance;
	}

	void draw(SDL_Renderer* renderer);

	~Snake();
};

#endif
