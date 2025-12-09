#include <SDL2/SDL.h>
#include "./input_handler.hpp"
#include "./game.hpp"
#include "./snake.hpp"
#include "./state_manager.hpp"

void InputHandler::update() {
	SDL_Event event;
	key_state = SDL_GetKeyboardState(0);

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			Game::instance().set_running(false);

		if (event.type == SDL_KEYDOWN) {
			SDL_Keycode key = event.key.keysym.sym;

			StateManager::instance().handle_input(key);
		}
	}
}

void InputHandler::clean() {

}

