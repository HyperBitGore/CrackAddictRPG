#include "Header.h"



void Game::drawText(SDL_Renderer* rend, TTF_Font* font, std::string text, SDL_Color color, int x, int y, int w, int h) {
	SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surf);
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderCopy(rend, texture, NULL, &rect);

	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);
}
//write enemy creation here
void Game::createEnemyInstance(std::vector<Entity>& enemies, Entity* p) {
	int enumb = rand() % 3 + 1;
	bool e2 = false;
	bool e3 = false;
	bool e4 = false;
	bool e5 = false;
	if ((*p).level < 5) {
		enumb = 1;
	}
	else if ((*p).level > 5 && (*p).level < 10) {
		e2 = true;
	}
	else if ((*p).level > 10 && (*p).level < 20) {
		e3 = true;
	}
	else if ((*p).level > 20 && (*p).level < 40) {
		e4 = true;
	}
	else if ((*p).level > 40 && (*p).level < 100) {
		e5 = true;
	}
	float sx = 600.0f;
	float sy = 300.0f;
	for (int i = 0; i < enumb; i++) {
		if (e2) {
			int roll = rand() % 100;
			if (roll > 52) {
				Entity e;
				e.atkdmg = 25;
				e.level = 10;
				e.type = 1;
				e.equipped = STICK;
				e.x = sx;
				e.y = sy;
				e.w = 50;
				e.h = 100;
				e.health = 800;
				enemies.push_back(e);
				sx += 50.0f;
				sy += 50.0f;
			}
			else {
				Entity e;
				e.atkdmg = 10;
				e.level = 2;
				e.type = 0;
				e.equipped = STICK;
				e.x = sx;
				e.y = sy;
				e.w = 50;
				e.h = 100;
				e.health = 50;
				enemies.push_back(e);
				sx += 50.0f;
				sy += 50.0f;
			}
		}
		else if (e3) {
			int roll = rand() % 100;
			if (roll > 52) {
				Entity e;
				e.atkdmg = 150;
				e.level = 30;
				e.type = 2;
				e.equipped = STICK;
				e.x = sx;
				e.y = sy;
				e.w = 50;
				e.h = 100;
				e.health = 2000;
				enemies.push_back(e);
				sx += 50.0f;
				sy += 50.0f;
			}
			else if (roll > 35) {
				Entity e;
				e.atkdmg = 25;
				e.level = 10;
				e.type = 1;
				e.equipped = STICK;
				e.x = sx;
				e.y = sy;
				e.w = 50;
				e.h = 100;
				e.health = 800;
				enemies.push_back(e);
				sx += 50.0f;
				sy += 50.0f;
			}
			else {
				Entity e;
				e.atkdmg = 10;
				e.level = 2;
				e.type = 0;
				e.equipped = STICK;
				e.x = sx;
				e.y = sy;
				e.w = 50;
				e.h = 100;
				e.health = 50;
				enemies.push_back(e);
				sx += 50.0f;
				sy += 50.0f;
			}
		}
		else if (e4) {
			int roll = rand() % 100;
			if (roll > 48) {
				Entity e;
				e.atkdmg = 550;
				e.level = 50;
				e.type = 3;
				e.equipped = STICK;
				e.x = sx;
				e.y = sy;
				e.w = 50;
				e.h = 100;
				e.health = 5000;
				enemies.push_back(e);
				sx += 50.0f;
				sy += 50.0f;
			}
			else if (roll > 35) {
				Entity e;
				e.atkdmg = 150;
				e.level = 30;
				e.type = 2;
				e.equipped = STICK;
				e.x = sx;
				e.y = sy;
				e.w = 50;
				e.h = 100;
				e.health = 2000;
				enemies.push_back(e);
				sx += 50.0f;
				sy += 50.0f;
			}
			else if (roll > 20) {
				Entity e;
				e.atkdmg = 25;
				e.level = 10;
				e.type = 1;
				e.equipped = STICK;
				e.x = sx;
				e.y = sy;
				e.w = 50;
				e.h = 100;
				e.health = 800;
				enemies.push_back(e);
				sx += 50.0f;
				sy += 50.0f;
			}
			else {
				Entity e;
				e.atkdmg = 10;
				e.level = 2;
				e.type = 0;
				e.equipped = STICK;
				e.x = sx;
				e.y = sy;
				e.w = 50;
				e.h = 100;
				e.health = 50;
				enemies.push_back(e);
				sx += 50.0f;
				sy += 50.0f;
			}
		}
		else if (e5) {
		int roll = rand() % 100;
		if (roll > 45) {
			Entity e;
			e.atkdmg = 1500;
			e.level = 100;
			e.type = 4;
			e.equipped = STICK;
			e.x = sx;
			e.y = sy;
			e.w = 50;
			e.h = 100;
			e.health = 10000;
			enemies.push_back(e);
			sx += 50.0f;
			sy += 50.0f;
		}
		else if (roll > 35) {
			Entity e;
			e.atkdmg = 550;
			e.level = 50;
			e.type = 3;
			e.equipped = STICK;
			e.x = sx;
			e.y = sy;
			e.w = 50;
			e.h = 100;
			e.health = 5000;
			enemies.push_back(e);
			sx += 50.0f;
			sy += 50.0f;
		}
		else if (roll > 20) {
			Entity e;
			e.atkdmg = 150;
			e.level = 30;
			e.type = 2;
			e.equipped = STICK;
			e.x = sx;
			e.y = sy;
			e.w = 50;
			e.h = 100;
			e.health = 2000;
			enemies.push_back(e);
			sx += 50.0f;
			sy += 50.0f;
		}
		else if (roll > 10) {
			Entity e;
			e.atkdmg = 25;
			e.level = 10;
			e.type = 1;
			e.equipped = STICK;
			e.x = sx;
			e.y = sy;
			e.w = 50;
			e.h = 100;
			e.health = 800;
			enemies.push_back(e);
			sx += 50.0f;
			sy += 50.0f;
		}
		else {
			Entity e;
			e.atkdmg = 10;
			e.level = 2;
			e.type = 0;
			e.equipped = STICK;
			e.x = sx;
			e.y = sy;
			e.w = 50;
			e.h = 100;
			e.health = 50;
			enemies.push_back(e);
			sx += 50.0f;
			sy += 50.0f;
		}
		}
		else {
			Entity e;
			e.atkdmg = 10;
			e.level = 2;
			e.type = 0;
			e.equipped = STICK;
			e.x = sx;
			e.y = sy;
			e.w = 50;
			e.h = 100;
			e.health = 50;
			enemies.push_back(e);
			sx += 50.0f;
			sy += 50.0f;
		}
	}
}
