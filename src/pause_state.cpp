#include <SDL2/SDL.h>
#include "./pause_state.hpp"
#include "./menu_button.hpp"
#include "./monitor.hpp"

PauseState::PauseState() {
	/*
	MenuButton test_button {"this is test"};

	test_button.set_x(0);
	test_button.set_y(0);
	test_button.set_width(300);
	test_button.set_height(100);

	buttons.push_back(test_button);
	*/
	//test_monitor = new Monitor {0, 0, "test"};	
	test_button = new MenuButton {"test"};
}

void PauseState::handle_input(SDL_Keycode key) {

}

void PauseState::draw(SDL_Renderer* renderer) {
	//buttons[0].draw(renderer);
	//test_monitor->draw(renderer);
	test_button->draw(renderer);
}

void PauseState::update() {

}

PauseState::~PauseState() {

}
