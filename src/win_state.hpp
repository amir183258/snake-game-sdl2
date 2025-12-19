#ifndef WIN_STATE_H
#define WIN_STATE_H

#include <SDL2/SDL.h>
#include "./game_state.hpp"

class WinState: public GameState {
private:
	SDL_Texture* win_text;

	// draw position
	int w;
	int h;
	int x;
	int y;

	// window size
	int window_w;
	int window_h;

public:
	WinState();

	void handle_input(SDL_Keycode key) override;
	void draw(SDL_Renderer* renderer) override;
	void update() override;

	~WinState();
};

#endif
