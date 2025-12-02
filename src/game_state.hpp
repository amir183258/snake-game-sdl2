#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SDL2/SDL.h>
#include "./game.hpp"

class GameState {
private:

public:
	SDL_Renderer* renderer;

	virtual void draw() = 0;
	virtual void update() = 0;

	virtual ~GameState() {}
};

#endif
