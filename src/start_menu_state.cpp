#include <SDL2/SDL.h>
#include "./start_menu_state.hpp"
#include "./game.hpp"
#include "./state_manager.hpp"
#include "./play_state.hpp"

StartMenuState::StartMenuState() {
	// import button textures, they are same size
	button_start = load_texture("./assets/start_menu_state/button_start.png");
	button_help = load_texture("./assets/start_menu_state/button_help.png");
	button_exit = load_texture("./assets/start_menu_state/button_exit.png");

	// vertical space between buttons
	space_between_buttons = 30;

	// button width and height
	SDL_QueryTexture(button_start, nullptr, nullptr, &button_width, &button_height);
	button_width /= 2;

	// append buttons to buttons list
	buttons.push_back(button_start);
	buttons.push_back(button_help);
	buttons.push_back(button_exit);

	// set current button to the first button
	current_button = 0;

	// compute draw position
	int total_bbox_w = button_width;
	int total_bbox_h = button_height * buttons.size() + space_between_buttons * (buttons.size() - 1);

	int window_w;
	int window_h;
	SDL_GetWindowSize(Game::instance().get_window(), &window_w, &window_h);

	draw_pos_x = (window_w - total_bbox_w) / 2;
	draw_pos_y = (window_h - total_bbox_h) / 2;
}

void StartMenuState::handle_input(SDL_Keycode key) {
	switch (key) {
	case SDLK_w:
		--current_button;
		if (current_button < 0)
			current_button = buttons.size() - 1;
		break;
	case SDLK_s:
		++current_button;
		if (current_button >= buttons.size())
			current_button = 0;
		break;
	case SDLK_ESCAPE: // exit
		Game::instance().set_running(false);
		break;
	case SDLK_RETURN:
		switch (current_button) {
		case 0: // start button
			PlayState::pause_duration = SDL_GetTicks();
			StateManager::instance().add_game_state(new PlayState {});
			StateManager::instance().remove_first_game_state();
			break;
		case 1: // help button
			// TODO
			break;
		case 2: // exit button
			Game::instance().set_running(false);
		}
	}
}

void StartMenuState::draw(SDL_Renderer* renderer) {
	// TODO add a big game logo
	// drawing a big rectangle
	int window_w;
	int window_h;
	SDL_GetWindowSize(Game::instance().get_window(), &window_w, &window_h);

	SDL_Rect window_rect;
	window_rect.x = 0;
	window_rect.y = 0;
	window_rect.w = window_w;
	window_rect.h = window_h;

	SDL_SetRenderDrawColor(renderer, 182, 208, 226, 100);
	SDL_RenderFillRect(renderer, &window_rect);

	// draw buttons
	SDL_Rect source_rect;
	source_rect.x = 0;
	source_rect.y = 0;
	source_rect.w = button_width;
	source_rect.h = button_height;

	SDL_Rect dest_rect;
	dest_rect.x = draw_pos_x;
	dest_rect.y = draw_pos_y;
	dest_rect.w = button_width;
	dest_rect.h = button_height;

	for (int i = 0; i < buttons.size(); ++i) {
		if (i == current_button) {
			source_rect.x += source_rect.w;
			SDL_RenderCopy(renderer, buttons[i], &source_rect, &dest_rect);
			source_rect.x -= source_rect.w;
		}
		else
			SDL_RenderCopy(renderer, buttons[i], &source_rect, &dest_rect);

		dest_rect.y += dest_rect.h + space_between_buttons;
	}
}

void StartMenuState::update() {

}

StartMenuState::~StartMenuState() {
	for (int i = 0; i < buttons.size(); ++i)
		SDL_DestroyTexture(buttons[i]);

	SDL_Log("destroying start menu state textures...");
}
