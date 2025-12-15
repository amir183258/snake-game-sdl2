#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <string>
#include <SDL2/SDL.h>
#include "./game_state.hpp"
#include "./playground.hpp"
#include "./snake.hpp"
#include "./apple.hpp"
#include "./monitor.hpp"

class PlayState: public GameState {
private:
	Playground* playground;
	Snake* snake;
	Apple* apple;
	Monitor* score_monitor;
	Monitor* time_monitor;
	
	// for handling time
	Uint32 previous_time;

	// private functions
	void update_time_monitor();

public:
	// these two variables manage time between pause and play states
	static Uint32 state_time;
	static Uint32 pause_duration;

	PlayState();

	void handle_input(SDL_Keycode key) override;
	void draw(SDL_Renderer* renderer) override;
	void update() override;

	~PlayState();
};

#endif
