#ifndef __GAME_H__
#define __GAME_H__

#include <string>
#include <SDL2/SDL.h>

class PlayState;

class Game {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool game_running;

	PlayState* state;

	Game() {}
	
public:
	bool init(std::string title, int xpos, int ypos, bool fullscreen);

	void render();
	void update();
	void handle_events();
	void clean();

	static Game& instance() {
		static Game game_instance;
		return game_instance;
	}

	bool get_running() { return game_running; }
	void set_running(bool run) { game_running = run; }

	SDL_Renderer* get_renderer() const { return renderer; }

	SDL_Window* get_window() { return window; }

	~Game() { clean(); }
};

// helper functions
SDL_Texture* load_texture(std::string path, SDL_Renderer* renderer);

#endif
