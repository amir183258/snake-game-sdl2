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

	// setting up apple
	apple = &Apple::instance();

	// score monitor
	SDL_Rect playground_bbox = playground->get_bbox();
	score_monitor = new Monitor {playground_bbox.x, playground_bbox.y, "SCORE 000"};
}

void PlayState::draw() {
	playground->draw(renderer);
	snake->draw(renderer);
	apple->draw(renderer);
	score_monitor->draw(renderer);
}

void PlayState::update() {
	snake->update(score_monitor);
}

PlayState::~PlayState() {
	delete score_monitor;
	SDL_Log("destorying score monitor...");

}
