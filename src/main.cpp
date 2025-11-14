#include <utility>
#include <SDL2/SDL.h>
#include "game.hpp"
#include "playground.hpp"

using namespace std;

int main() {
	Game::instance().init("Snake Game",
	SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED,
	false);

	while (Game::instance().get_running()) {
		Game::instance().render();

		Game::instance().update();
	}

	return 0;
}
