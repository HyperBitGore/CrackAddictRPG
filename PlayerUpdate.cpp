#include "Header.h"


void Game::playerUpdate(Entity* p, float delta, std::vector<Entity>& tiles) {
	SDL_PumpEvents();
	if (keys[SDL_SCANCODE_W]) {
		(*p).index -= 40;
		if (tiles[(*p).index].type == 1) {
			(*p).index += 40;
		}
	}
	else if (keys[SDL_SCANCODE_S]) {
		(*p).index += 40;
		if (tiles[(*p).index].type == 1) {
			(*p).index -= 40;
		}
	}
	else if (keys[SDL_SCANCODE_A]) {
		(*p).index--;
		if (tiles[(*p).index].type == 1) {
			(*p).index++;
		}
	}
	else if (keys[SDL_SCANCODE_D]) {
		(*p).index++;
		if (tiles[(*p).index].type == 1) {
			(*p).index--;
		}
	}
	if (keys[SDL_SCANCODE_SPACE]) {
		int indices[4] = { (*p).index - 40, (*p).index + 40, (*p).index - 1, (*p).index + 1 };
		for (int i = 0; i < 4; i++) {
			if (tiles[indices[i]].type == 1) {
				tiles[indices[i]].type = 4;
			}
		}
	}
	(*p).y = tiles[(*p).index].y + 5;
	(*p).x = tiles[(*p).index].x + 5;
}