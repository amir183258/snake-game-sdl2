#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <string>
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

public:
	PlayState();

	void draw() override;
	void update() override;

	~PlayState();
};

#endif
