#include <SDL2/SDL.h>
#include "./pause_state.hpp"
#include "./menu_button.hpp"
#include "./monitor.hpp"
#include "./game.hpp"

PauseState::PauseState() {
	number_of_buttons = 2;
	// menu bbox padding
	padding_x = 25;
	padding_y = 25;
	// menu bbox
	menu_bbox.w = 300 + 2 * padding_x;
	menu_bbox.h = 50 * number_of_buttons + padding_y * (number_of_buttons + 1);
	
	int window_w, window_h;
	SDL_GetWindowSize(Game::instance().get_window(), &window_w, &window_h);

	menu_bbox.x = (window_w - menu_bbox.w) / 2;
	menu_bbox.y = (window_h - menu_bbox.h) / 2;

	resume_button = new MenuButton {"Resume"};
	quit_button = new MenuButton {"Quit"};
}

void PauseState::handle_input(SDL_Keycode key) {

}

void PauseState::draw(SDL_Renderer* renderer) {

	// draw menu bbox
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &menu_bbox);

	// draw buttons
	int draw_height = menu_bbox.y + padding_y;

	resume_button->set_y(draw_height);
	resume_button->draw(renderer);

	draw_height += 50 + padding_y;
	quit_button->set_y(draw_height);
	quit_button->draw(renderer);
}

void PauseState::update() {

}

PauseState::~PauseState() {

}
