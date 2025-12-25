#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "./pause_state.hpp"
#include "./game.hpp"
#include "./state_manager.hpp"
#include "./play_state.hpp"

Mix_Chunk *PauseState::navigate_sound = nullptr;
Mix_Chunk *PauseState::confirm_sound = nullptr;

PauseState::PauseState() {
	// import button textures, they are same size
	button_resume = load_texture("./assets/pause_state/button_resume.png");
	button_restart = load_texture("./assets/pause_state/button_restart.png");
	button_quit = load_texture("./assets/pause_state/button_quit.png");

	// vertical space between buttons
	space_between_buttons = 30;

	// button width and height
	SDL_QueryTexture(button_resume, nullptr, nullptr, &button_width, &button_height);
	button_width /= 2;

	// append buttons to buttons list
	buttons.push_back(button_resume);
	buttons.push_back(button_restart);
	buttons.push_back(button_quit);

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

	// load sound
	navigate_sound = Mix_LoadWAV("./assets/sound/navigate.wav");
	confirm_sound = Mix_LoadWAV("./assets/sound/confirm.wav");

	// sound volume
	Mix_VolumeChunk(navigate_sound, MIX_MAX_VOLUME);
	Mix_VolumeChunk(confirm_sound, MIX_MAX_VOLUME);
}

void PauseState::handle_input(SDL_Keycode key) {
	switch (key) {
	case SDLK_w:
		Mix_PlayChannel(-1, navigate_sound, 0);
		--current_button;
		if (current_button < 0)
			current_button = buttons.size() - 1;
		break;
	case SDLK_s:
		Mix_PlayChannel(-1, navigate_sound, 0);
		++current_button;
		if (current_button >= buttons.size())
			current_button = 0;
		break;
	case SDLK_ESCAPE:
		Mix_PlayChannel(-1, confirm_sound, 0);
		PlayState::pause_duration += SDL_GetTicks() - PlayState::state_time;
		StateManager::instance().remove_last_game_state();
		break;
	case SDLK_RETURN:
		Mix_PlayChannel(-1, confirm_sound, 0);
		switch (current_button) {
		case 0: // resume button, similar to SDLK_ESCAPE
			StateManager::instance().remove_last_game_state();
			PlayState::pause_duration += SDL_GetTicks() - PlayState::state_time;
			break;
		case 1:
			PlayState::pause_duration = SDL_GetTicks();
			StateManager::instance().remove_first_game_state();
			StateManager::instance().add_game_state(new PlayState {});
			StateManager::instance().remove_first_game_state();

			break;
		case 2: // quit button
			Game::instance().set_running(false);
		}
	}
}

void PauseState::draw(SDL_Renderer* renderer) {
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

void PauseState::update() {

}

PauseState::~PauseState() {
	// textures
	for (int i = 0; i < buttons.size(); ++i)
		SDL_DestroyTexture(buttons[i]);

	SDL_Log("destroying pause state textures and sounds...");
}
