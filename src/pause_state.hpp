#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include <SDL2/SDL.h>
#include "./game_state.hpp"
#include "./menu_button.hpp"
#include "./monitor.hpp"

class PauseState: public GameState {
private:
	int number_of_buttons;

	int padding_x;
	int padding_y;

	SDL_Rect menu_bbox;

	MenuButton* resume_button;
	MenuButton* quit_button;

public:
	PauseState();

	void handle_input(SDL_Keycode key) override;
	void draw(SDL_Renderer* renderer) override;
	void update() override;

	~PauseState();
};

#endif
