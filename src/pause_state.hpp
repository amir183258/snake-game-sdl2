#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "./game_state.hpp"

class PauseState: public GameState {
private:
	int button_width;
	int button_height;

	int space_between_buttons;

	int current_button;

	SDL_Texture* button_resume;
	SDL_Texture* button_restart;
	SDL_Texture* button_quit;

	std::vector<SDL_Texture*> buttons;

	// draw position
	int draw_pos_x;
	int draw_pos_y;

	// sound
	Mix_Chunk *navigate_sound;
	Mix_Chunk *confirm_sound;

public:
	PauseState();

	void handle_input(SDL_Keycode key) override;
	void draw(SDL_Renderer* renderer) override;
	void update() override;

	~PauseState();
};

#endif
