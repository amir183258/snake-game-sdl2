#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <SDL2/SDL.h>
#include "./play_state.hpp"
#include "./game.hpp"
#include "./playground.hpp"
#include "./snake.hpp"
#include "./apple.hpp"
#include "./monitor.hpp"

PlayState::PlayState() {
	// setting up the renderer
	GameState::renderer = Game::instance().get_renderer();

	// setting up playground
	playground = &Playground::instance();

	// setting up the snake
	snake = &Snake::instance();
	snake->collision_call_back = [this]() {
		SDL_Log("Hi, I ate myself!");
	};
	snake->eat_apple_call_back = [this](int score) {
		std::stringstream ss;
		ss << std::setw(4) << std::setfill('0') << score;
		score_monitor->update("SCORE: " + ss.str());
	};

	// setting up apple
	apple = &Apple::instance();

	// score monitor
	SDL_Rect playground_bbox = playground->get_bbox();
	score_monitor = new Monitor {playground_bbox.x, 0, "SCORE: 0000"};
	score_monitor->set_y(playground_bbox.y - score_monitor->get_height());

	// time monitor
	time_monitor = new Monitor {0 , 0, "00:00"};
	time_monitor->set_y(playground_bbox.y - score_monitor->get_height());

	int xpos = playground_bbox.x + playground_bbox.w - time_monitor->get_width();
	time_monitor->set_x(xpos);
}

void PlayState::draw() {
	playground->draw(renderer);
	snake->draw(renderer);
	apple->draw(renderer);
	score_monitor->draw(renderer);
	time_monitor->draw(renderer);
}

void PlayState::update() {
	snake->update();
}

PlayState::~PlayState() {
	delete score_monitor;
	SDL_Log("destorying score monitor...");

}
