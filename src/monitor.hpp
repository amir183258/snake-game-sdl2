#ifndef MONITOR_H
#define MONITOR_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// this file is monitor class to show scores or anything (like time)
class Monitor {
private:
	SDL_Rect bbox;

	std::string text = "test";

	static TTF_Font* text_font;
	SDL_Color text_color;

	SDL_Texture* text_texture;				// this is the final output of using fonts
	
	SDL_Texture* create_text_texture(SDL_Renderer* renderer);

public:
	Monitor();
	Monitor(int x_pos, int y_pos, std::string monitor_text);

	void draw(SDL_Renderer* renderer);
	void update();

	~Monitor();
};
#endif
