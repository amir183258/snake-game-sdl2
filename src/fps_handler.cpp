#include <SDL2/SDL.h>
#include "./fps_handler.hpp"

void FPSHandler::handle_fps() {
	size_t ticks_delta = SDL_GetTicks() - last_frame_tick;

	if (ticks_delta < frame_delay)
		SDL_Delay(frame_delay - ticks_delta);

	current_fps = 1000.0f / (SDL_GetTicks() - last_frame_tick);

	// SDL_Log("current_fps: %f", current_fps);			for debug

	last_frame_tick = SDL_GetTicks();
}

void FPSHandler::set_fps(size_t target) {
	target_fps = target;
	frame_delay = 1000 / target_fps;
}
