#ifndef FPS_HANDLER_H
#define FPS_HANDLER_H

#include <SDL2/SDL.h>

class FPSHandler {
private:
	size_t last_frame_tick;					// mili second
	
	size_t target_fps = 60;
	size_t frame_delay = 1000 / target_fps;

	float current_fps;

	FPSHandler() {}

public:
	static FPSHandler& instance() {
		static FPSHandler fps_handler_instance;
		return fps_handler_instance;
	}

	// get current fps
	float get_fps() { return current_fps; }

	// set target fps
	void set_fps(size_t target);

	// handle fps; this function should call at last
	void handle_fps();
};

#endif
