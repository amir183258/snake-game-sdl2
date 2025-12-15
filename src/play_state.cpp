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
#include "./pause_state.hpp"
#include "./state_manager.hpp"

Uint32 PlayState::state_time = 0;
Uint32 PlayState::pause_duration = 0;

PlayState::PlayState() {
	// setting up playground
	playground = &Playground::instance();

	// setting up the snake
	// TODO handle self eat loss
	snake = &Snake::instance();
	snake->collision_call_back = [this]() {
		SDL_Log("Hi, I ate myself!");
	};
	// TODO handle out of playground loss
	snake->eat_apple_call_back = [this](int score) {
		std::stringstream ss;
		ss << std::setw(4) << std::setfill('0') << score;
		score_monitor->update("SCORE: " + ss.str());
	};

	// setting up apple
	apple = &Apple::instance();
	apple->spawn();

	// score monitor
	SDL_Rect playground_bbox = playground->get_bbox();
	score_monitor = new Monitor {playground_bbox.x, 0, "SCORE: 0000"};
	score_monitor->set_y(playground_bbox.y - score_monitor->get_height());

	// time monitor
	time_monitor = new Monitor {0 , 0, "000:00"};
	time_monitor->set_y(playground_bbox.y - score_monitor->get_height());

	int xpos = playground_bbox.x + playground_bbox.w - time_monitor->get_width();
	time_monitor->set_x(xpos);

	previous_time = 0;
}

void PlayState::handle_input(SDL_Keycode key) {
	switch (key) {
	case SDLK_w:
		snake->set_direction(direction::UP);
		break;
	case SDLK_d:
		snake->set_direction(direction::RIGHT);
		break;
	case SDLK_s:
		snake->set_direction(direction::DOWN);
		break;
	case SDLK_a:
		snake->set_direction(direction::LEFT);
		break;
	case SDLK_ESCAPE:
		StateManager::instance().add_game_state(new PauseState {});
		state_time = SDL_GetTicks();
	}
}

void PlayState::draw(SDL_Renderer* renderer) {
	playground->draw(renderer);
	snake->draw(renderer);
	apple->draw(renderer);
	score_monitor->draw(renderer);
	time_monitor->draw(renderer);
}

void PlayState::update() {
	snake->update();

	// update time monitor
	update_time_monitor();
}

void PlayState::update_time_monitor() {
	Uint32 ms = SDL_GetTicks();

	unsigned long int total_seconds = (ms - pause_duration) / 1000;

	if (total_seconds != previous_time) {
		previous_time = total_seconds;

		int minute = total_seconds / 60;
		int seconds = total_seconds % 60;

		// create string to display
		std::ostringstream oss;
		oss << std::setw(3) << std::setfill('0') << minute << ":" <<
			std::setw(2) << std::setfill('0') << seconds;

		std::string formatted_time = oss.str();

		time_monitor->update(formatted_time);
	}
}

PlayState::~PlayState() {
	delete score_monitor;
	SDL_Log("destorying score monitor...");

}
