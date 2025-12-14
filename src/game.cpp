#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "./game.hpp"
#include "./input_handler.hpp"
#include "./playground.hpp"
#include "./snake.hpp"
#include "./apple.hpp"
#include "./fps_handler.hpp"
#include "./monitor.hpp"
#include "./play_state.hpp"
#include "./state_manager.hpp"

bool Game::init(std::string title, int xpos, int ypos, bool fullscreen) {

	int flags {0};
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		SDL_Log("SDL init success");

		if (TTF_Init() == -1) {
			SDL_Log("error initializing SDL_ttf: %s\n", TTF_GetError());
			exit(1);
		}

		SDL_DisplayMode DM;
		int width = 600;									// default value
		int height = 600;									// default value

		window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);
		if (window != nullptr) {
			SDL_Log("window creation success");

			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer != nullptr)
				SDL_Log("renderer creation success");
			else {
				SDL_Log("renderer init fail");
				return false;
			}
		}
		else {
			SDL_Log("window init fail");
			return false;
		}
	}
	else {
		SDL_Log("SDL init fail");
		return false;
	}

	StateManager::instance().set_renderer(renderer);

	SDL_Log("game running success");
	game_running = true;

	return true;
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 182, 208, 226, 255);
	SDL_RenderClear(renderer);

	StateManager::instance().draw();

	SDL_RenderPresent(renderer);

	// handle fps
	FPSHandler::instance().handle_fps();
}

void Game::update() {
	InputHandler::instance().update();
	StateManager::instance().update();
}

void Game::clean() {
	SDL_Log("cleaning game");
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	game_running = false;

	SDL_Quit();
}

// helper functions
SDL_Texture* load_texture(std::string path, SDL_Renderer* renderer) {
	SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
	if (!texture)
		SDL_Log("failed to load texture: %s, SDL_image Error: %s", path.c_str(), IMG_GetError());
	return texture;
}

// TODO use this function in all other classes
SDL_Texture* load_texture(std::string path) {
	SDL_Renderer* renderer = Game::instance().get_renderer();
	SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
	if (!texture)
		SDL_Log("failed to load texture: %s, SDL_image Error: %s", path.c_str(), IMG_GetError());
	return texture;
}
