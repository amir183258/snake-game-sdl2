#include <SDL2/SDL.h>
#include "./pause_state.hpp"
#include "./game.hpp"

PauseState::PauseState() {
	// import button textures, they are same size
	button_resume = load_texture("./assets/pause_state/button_resume.png");
	button_quit = load_texture("./assets/pause_state/button_quit.png");

	// vertical space between buttons
	space_between_buttons = 30;

	// button width and height
	SDL_QueryTexture(button_resume, nullptr, nullptr, &button_width, &button_height);
	button_width /= 2;

	// append buttons to buttons list
	buttons.push_back(button_resume);
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
}

void PauseState::handle_input(SDL_Keycode key) {

}

void PauseState::draw(SDL_Renderer* renderer) {
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

}
