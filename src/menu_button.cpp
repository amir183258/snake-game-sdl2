#include <string>
#include "./menu_button.hpp"
#include "./monitor.hpp"

MenuButton::MenuButton(std::string text) {
	bbox.x = 0;
	bbox.y = 0;
	bbox.w = 300;
	bbox.h = 50;

	text_monitor = new Monitor {100, 100, text};

	selected = false;
}

void MenuButton::draw(SDL_Renderer* renderer) {
	// render button
	if (!selected)
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
	else
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);

	SDL_RenderFillRect(renderer, &bbox);

	// render text
	//SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	text_monitor->draw(renderer);
}

MenuButton::~MenuButton() {
	delete text_monitor;
}
