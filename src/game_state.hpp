#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SDL2/SDL.h>
#include "./game.hpp"

class GameState {
private:

public:
	virtual void handle_input(SDL_Keycode key) = 0;
	virtual void draw(SDL_Renderer* renderer) = 0;
	virtual void update() = 0;

	virtual ~GameState() {}
};

#endif
