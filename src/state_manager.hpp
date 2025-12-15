#ifndef STATE_MANAGER_H
#define STATE_MANGAER_H

#include <vector>
#include "./game_state.hpp"
#include <SDL2/SDL.h>

class StateManager {
private:
	SDL_Renderer *renderer;
	std::vector<GameState*> current_state;

	StateManager();
public:
	static StateManager& instance() {
		static StateManager state_manager_instance;
		return state_manager_instance;
	}

	void draw();
	void update();

	void handle_input(SDL_Keycode key);

	// set renderer
	void set_renderer(SDL_Renderer* r) { renderer = r; }

	// stack operations
	void add_game_state(GameState* state);
	void change_game_state(GameState* state);
	void remove_last_game_state();
	void remove_first_game_state();

	~StateManager();
};

#endif
