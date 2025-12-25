#ifndef HELP_STATE_H
#define HELP_STATE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "./game_state.hpp"

class HelpState: public GameState {
private:
	SDL_Texture* help_texture;

	// help state dimensions
	int w;
	int h;

	// sound
	static Mix_Chunk *confirm_sound;

public:
	HelpState();

	void handle_input(SDL_Keycode key) override;
	void draw(SDL_Renderer* renderer) override;
	void update() override;

	~HelpState();
};

#endif
