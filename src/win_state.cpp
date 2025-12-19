#include <SDL2/SDL.h>
#include "./win_state.hpp"
#include "./game.hpp"
#include "./state_manager.hpp"
#include "./play_state.hpp"

WinState::WinState() {
	// import win text texture
	win_text = load_texture("./assets/win_state/win_text.png");


	SDL_QueryTexture(win_text, nullptr, nullptr, &w, &h);

	SDL_GetWindowSize(Game::instance().get_window(), &window_w, &window_h);

	x = (window_w - w) / 2;
	y = (window_w - h) / 2;
}

void WinState::handle_input(SDL_Keycode key) {
	switch (key) {
	case SDLK_ESCAPE:
	case SDLK_RETURN:
		PlayState::pause_duration = SDL_GetTicks();
		StateManager::instance().remove_first_game_state();
		StateManager::instance().add_game_state(new PlayState {});
		StateManager::instance().remove_first_game_state();
	}
}

void WinState::draw(SDL_Renderer* renderer) {
	SDL_Rect window_rect;
	window_rect.x = 0;
	window_rect.y = 0;
	window_rect.w = window_w;
	window_rect.h = window_h;

	SDL_SetRenderDrawColor(renderer, 100, 150, 100, 75);
	SDL_RenderFillRect(renderer, &window_rect);

	SDL_Rect dest_rect;
	dest_rect.x = x;
	dest_rect.y = y;
	dest_rect.w = w;
	dest_rect.h = h;

	SDL_RenderCopy(renderer, win_text, nullptr, &dest_rect);
}

void WinState::update() {

}

WinState::~WinState() {
	SDL_DestroyTexture(win_text);
	SDL_Log("destroying win state textures...");
}
