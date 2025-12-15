#include <SDL2/SDL.h>
#include "./state_manager.hpp"
#include "./game_state.hpp"

StateManager::StateManager() {

}

void StateManager::handle_input(SDL_Keycode key) {
	current_state.back()->handle_input(key);
}

void StateManager::draw() {
	for (int i = 0; i < current_state.size(); ++i)
		current_state[i]->draw(renderer);
}

void StateManager::update() {
	current_state.back()->update();
}

void StateManager::add_game_state(GameState *state) {
	current_state.push_back(state);
}

void StateManager::change_game_state(GameState *state) {
	if (!current_state.empty())
		delete current_state.back();
	current_state.push_back(state);
}

void StateManager::remove_last_game_state() {
	delete current_state.back();
	current_state.pop_back();
}

void StateManager::remove_first_game_state() {
	delete current_state.front();
	current_state.erase(current_state.begin());
}

StateManager::~StateManager() {
	for (int i = 0; i < current_state.size(); ++i)
		delete current_state[i];
}
