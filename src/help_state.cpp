#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "./help_state.hpp"
#include "./game.hpp"
#include "./state_manager.hpp"
#include "./start_menu_state.hpp"

Mix_Chunk *HelpState::confirm_sound = nullptr;

HelpState::HelpState() {
	// import help texture
	help_texture = load_texture("./assets/help_state/help.png");

	SDL_QueryTexture(help_texture, nullptr, nullptr, &w, &h);

	// load sound
	confirm_sound = Mix_LoadWAV("./assets/sound/confirm.wav");
	Mix_VolumeChunk(confirm_sound, MIX_MAX_VOLUME);
}

void HelpState::handle_input(SDL_Keycode key) {
	switch (key) {
	case SDLK_ESCAPE:
	case SDLK_RETURN:
		Mix_PlayChannel(-1, confirm_sound, 0);
		StateManager::instance().remove_last_game_state();
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
