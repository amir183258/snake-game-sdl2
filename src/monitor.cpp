#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "./monitor.hpp"
#include "./game.hpp"

TTF_Font* Monitor::text_font = nullptr;

Monitor::Monitor() {

}

Monitor::Monitor(int x_pos, int y_pos, std::string monitor_text) :
	bbox {x_pos, y_pos, 0, 0} {
	// load font
	if (!text_font) {
		text_font = TTF_OpenFont("./assets/arcade_font.ttf", 28);

		if (!text_font) {
			std::cerr << "error loading font: " << TTF_GetError() << std::endl;
			exit(1);
		}
	}

	text = monitor_text;

	text_color = {0, 0, 0};
	
	text_texture = create_text_texture(Game::instance().get_renderer());
}

SDL_Texture* Monitor::create_text_texture(SDL_Renderer* renderer) {
	// create surface from font
	SDL_Surface* text_surface = TTF_RenderText_Solid(text_font, text.c_str(), text_color);
	if (!text_surface) {
		std::cerr << "unable to create text surface: " << TTF_GetError() << std::endl;
		exit(1);
	}
	// updating bbox
	bbox = {0, 0, text_surface->w, text_surface->h};

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	if (!texture) {
		std::cerr << "unable to create texture from surface: " << TTF_GetError() << std::endl;
		exit(1);
	}

	// destroying temporary surface
	SDL_FreeSurface(text_surface);

	return texture;
}

void Monitor::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, text_texture, nullptr, &bbox);
}

void Monitor::update(std::string new_text) {
	// set new text
	text = new_text;

	// destory previous texture
	SDL_DestroyTexture(text_texture);

	// new texture
	text_texture = create_text_texture(Game::instance().get_renderer());
}

Monitor::~Monitor() {
	if (text_font) {
		TTF_CloseFont(text_font);
		text_font = nullptr;

		SDL_Log("destroying monitor font...");
	}

	SDL_DestroyTexture(text_texture);
	SDL_Log("destroying monitor texture...");
}
