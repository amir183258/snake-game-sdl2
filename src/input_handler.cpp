#include <SDL2/SDL.h>
#include "./input_handler.hpp"
#include "./game.hpp"

void InputHandler::update() {
	SDL_Event event;
	key_state = SDL_GetKeyboardState(0);

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			Game::instance().set_running(false);

		if (event.type == SDL_KEYDOWN) {
			// TODO create class for handling keyboard.
			SDL_Log("%c", event.key.keysym.sym);
		}
	}
}

void InputHandler::clean() {

}

