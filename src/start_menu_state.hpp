#ifndef START_MENU_STATE_H
#define START_MENU_STATE_H

#include <vector>
#include <SDL2/SDL.h>
#include "./game_state.hpp"

class StartMenuState: public GameState {
private:
	int button_width;
	int button_height;

	int space_between_buttons;

	int current_button;

	SDL_Texture* button_start;
	SDL_Texture* button_help;
	SDL_Texture* button_exit;

	std::vector<SDL_Texture*> buttons;

	// draw position
	int draw_pos_x;
	int draw_pos_y;

public:
	StartMenuState();

	void handle_input(SDL_Keycode key) override;
	void draw(SDL_Renderer* renderer) override;
	void update() override;

	~StartMenuState();
};

#endif
