#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include <vector>
#include <SDL2/SDL.h>
#include "./game_state.hpp"
#include "./menu_button.hpp"
#include "./monitor.hpp"

class PauseState: public GameState {
private:
	std::vector<MenuButton> buttons;
	Monitor *test_monitor;
	MenuButton* test_button;

public:
	PauseState();

	void handle_input(SDL_Keycode key) override;
	void draw(SDL_Renderer* renderer) override;
	void update() override;

	~PauseState();

};

#endif
