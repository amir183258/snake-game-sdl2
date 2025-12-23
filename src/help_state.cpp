#include <SDL2/SDL.h>
#include "./help_state.hpp"
#include "./game.hpp"
#include "./state_manager.hpp"
#include "./start_menu_state.hpp"

HelpState::HelpState() {
	// import help texture
	help_texture = load_texture("./assets/help_state/help.png");


	SDL_QueryTexture(help_texture, nullptr, nullptr, &w, &h);
}

void HelpState::handle_input(SDL_Keycode key) {
	switch (key) {
	case SDLK_ESCAPE:
	case SDLK_RETURN:
		StateManager::instance().add_game_state(new StartMenuState {});
		StateManager::instance().remove_first_game_state();
	}
}

void HelpState::draw(SDL_Renderer* renderer) {
	SDL_Rect dest_rect;
	dest_rect.x = 0;
	dest_rect.y = 0;
	dest_rect.w = w;
	dest_rect.h = h;

	SDL_RenderCopy(renderer, help_texture, nullptr, &dest_rect);
}

void HelpState::update() {

}

HelpState::~HelpState() {
	SDL_DestroyTexture(help_texture);
	SDL_Log("destroying help state textures...");
}
