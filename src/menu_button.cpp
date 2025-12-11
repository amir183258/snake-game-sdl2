#include <string>
#include "./menu_button.hpp"
#include "./monitor.hpp"
#include "./game.hpp"

MenuButton::MenuButton(std::string text) {
	// button dimensions
	bbox.w = 300;
	bbox.h = 50;

	// setting button x
	int window_w;
	SDL_GetWindowSize(Game::instance().get_window(), &window_w, nullptr);
	bbox.x = (window_w - bbox.w) /2;

	bbox.y = 0;			// this should be set by the state class

	// centering monitor inside the button
	text_monitor = new Monitor {100, 100, text};
	text_monitor->set_x(bbox.x + (bbox.w - text_monitor->get_width()) / 2);
	text_monitor->set_y(bbox.y + (bbox.h - text_monitor->get_height()) / 2);

	selected = false;
}

void MenuButton::set_y(int y) {
	bbox.y = y;
	text_monitor->set_y(bbox.y + (bbox.h - text_monitor->get_height()) / 2);
}

void MenuButton::draw(SDL_Renderer* renderer) {
	// render button
	if (!selected)
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	else
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	SDL_RenderFillRect(renderer, &bbox);

	// render text
	text_monitor->draw(renderer);
}

MenuButton::~MenuButton() {
	delete text_monitor;
}
