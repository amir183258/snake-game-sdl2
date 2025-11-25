#include <SDL2/SDL.h>
#include "./apple.hpp"
#include "./game.hpp"
#include "./playground.hpp"
#include "./snake.hpp"

Apple::Apple() {
	// loading apple texture
	apple_texture = load_texture("./assets/apple.png", Game::instance().get_renderer());

	// spawn an apple
	spawn();
}

void Apple::spawn() {
	SDL_Point spawn_position = Playground::instance().get_free_playground_position();

	r = spawn_position.x;
	c = spawn_position.y;
}

void Apple::draw(SDL_Renderer* renderer) {
	// destination rectangle
	SDL_Rect dest_rect;
	dest_rect.w = Playground::instance().get_tile_dimension();
	dest_rect.h = Playground::instance().get_tile_dimension();

	// set x and y of destination rectangle
	SDL_Point draw_pos = Playground::instance().get_tile_pos(r, c);
	dest_rect.x = draw_pos.x;
	dest_rect.y = draw_pos.y;

	SDL_RenderCopy(renderer, apple_texture, nullptr, &dest_rect);
}

Apple::~Apple() {
	SDL_Log("destroying apple texture...");

	SDL_DestroyTexture(apple_texture);
}
