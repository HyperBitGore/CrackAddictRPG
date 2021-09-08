#include "Header.h"


void Game::generateMap(std::vector<Entity>& tiles, Entity* p) {
	std::ifstream file;
	file.open("map.miap");
	std::string line;
	float sx = 0.0f;
	float sy = 0.0f;
	int index = 0;
	while (std::getline(file, line)) {
		for (auto& i : line) {
			Entity e;
			switch (i) {
			case '-':
				//road
				e.x = sx;
				e.y = sy;
				e.w = 20;
				e.h = 20;
				e.type = 0;
				e.index = index;
				index++;
				tiles.push_back(e);
				break;
			case '#':
				//wall
				e.x = sx;
				e.y = sy;
				e.w = 20;
				e.h = 20;
				e.type = 1;
				e.index = index;
				index++;
				tiles.push_back(e);
				break;
			case '*':
				//floor
				e.x = sx;
				e.y = sy;
				e.w = 20;
				e.h = 20;
				e.type = 2;
				e.index = index;
				index++;
				tiles.push_back(e);
				break;
			case '@':
				//player/road
				e.x = sx;
				e.y = sy;
				e.w = 20;
				e.h = 20;
				e.type = 0;
				e.index = index;
				tiles.push_back(e);
				(*p).x = sx;
				(*p).y = sy;
				(*p).w = 10;
				(*p).h = 10;
				(*p).type = 0;
				(*p).atkdmg = 5;
				(*p).level = 1;
				(*p).index = index;
				(*p).health = 100;
				(*p).xp = 0;
				index++;
				break;
			case '$':
				//door
				e.x = sx;
				e.y = sy;
				e.w = 20;
				e.h = 20;
				e.type = 3;
				e.index = index;
				index++;
				tiles.push_back(e);
				break;
			}
			sx += 20.0f;
		}
		sy += 20.0f;
		sx = 0.0f;
	}
}