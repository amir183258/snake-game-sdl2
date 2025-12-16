#ifndef LOSS_STATE_H
#define LOSS_STATE_H

#include <SDL2/SDL.h>
#include "./game_state.hpp"

class LossState: public GameState {
private:
	SDL_Texture* loss_text;

	// draw position
	int w;
	int h;
	int x;
	int y;

	// window size
	int window_w;
	int window_h;

public:
	LossState();

	void handle_input(SDL_Keycode key) override;
	void draw(SDL_Renderer* renderer) override;
	void update() override;

	~LossState();
};

#endif
