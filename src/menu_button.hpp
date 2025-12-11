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

	void set_x(int x) { bbox.x = x; }
	void set_y(int y) { bbox.y = y; }
	void set_width(int width) { bbox.w = width; }
	void set_height(int height) { bbox.h = height; }

	void set_selected(bool s) { selected = s; }

	void draw(SDL_Renderer* renderer);

	~MenuButton();
};

#endif
