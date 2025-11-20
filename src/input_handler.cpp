#include <SDL2/SDL.h>
#include "./input_handler.hpp"
#include "./game.hpp"
#include "./snake.hpp"

void InputHandler::update() {
	SDL_Event event;
	key_state = SDL_GetKeyboardState(0);

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			Game::instance().set_running(false);

		if (event.type == SDL_KEYDOWN) {
			SDL_Keycode key = event.key.keysym.sym;

			switch (key) {
			case SDLK_w:
				Snake::instance().set_direction(direction::UP);
				break;
			case SDLK_d:
				Snake::instance().set_direction(direction::RIGHT);
				break;
			case SDLK_s:
				Snake::instance().set_direction(direction::DOWN);
				break;
			case SDLK_a:
				Snake::instance().set_direction(direction::LEFT);
			}

		}
	}
}

void InputHandler::clean() {

}

