#ifndef MONITOR_H
#define MONITOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// this file is monitor class to show scores or anything (like time)
class Monitor {
private:
	SDL_Rect bbox;

	static TTF_Font* text_font;
	SDL_Color text_color;

	SDL_Texture* text_texture;				// this is the final output of using fonts
	
	SDL_Texture* create_text_texture(SDL_Renderer* renderer);

public:
	Monitor();
	Monitor(int x_pos, int y_pos, int width, int height);

	void draw(SDL_Renderer* renderer);
	void update();

	~Monitor();
};
#endif
