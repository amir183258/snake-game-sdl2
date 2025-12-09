#include <SDL2/SDL.h>
#include "./state_manager.hpp"
#include "./play_state.hpp"

StateManager::StateManager() {
	current_state = new PlayState();
}

void StateManager::handle_input(SDL_Keycode key) {
	current_state->handle_input(key);
}

void StateManager::draw() {
	current_state->draw(renderer);
}

void StateManager::update() {
	current_state->update();
}
