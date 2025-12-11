#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <string>
#include <SDL2/SDL.h>
#include "./monitor.hpp"

class MenuButton {
private:
	Monitor* text_monitor;
	SDL_Rect bbox;

	bool selected;

public:
	MenuButton(std::string text);

	void set_y(int y);

	void set_selected(bool s) { selected = s; }

	void draw(SDL_Renderer* renderer);

	~MenuButton();
};

#endif
