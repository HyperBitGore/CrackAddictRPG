#include "Header.h"



void Game::spawnE1(std::vector<Entity>& enemies, float *sx, float *sy, SDL_Texture* enemtex) {
	Entity e;
	e.atkdmg = 10;
	e.level = 1;
	e.type = 0;
	e.sprite = enemtex;
	e.equipped = STICK;
	e.x = (*sx);
	e.y = (*sy);
	e.w = 50;
	e.h = 100;
	e.health = 50;
	enemies.push_back(e);
	(*sx) += 50;
	(*sy) += 50;
}
void Game::spawnE2(std::vector<Entity>& enemies, float *sx, float *sy, SDL_Texture* enemtex) {
	Entity e;
	e.atkdmg = 25;
	e.level = 2;
	e.type = 1;
	e.equipped = STICK;
	e.x = (*sx);
	e.y = (*sy);
	e.w = 50;
	e.h = 100;
	e.sprite = enemtex;
	e.health = 800;
	enemies.push_back(e);
	(*sx) += 50.0f;
	(*sy) += 50.0f;
}
void Game::spawnE3(std::vector<Entity>& enemies, float *sx, float *sy, SDL_Texture* enemtex) {
	Entity e;
	e.atkdmg = 150;
	e.level = 8;
	e.type = 2;
	e.sprite = enemtex;
	e.equipped = STICK;
	e.x = (*sx);
	e.y = (*sy);
	e.w = 50;
	e.h = 100;
	e.health = 2000;
	enemies.push_back(e);
	(*sx) += 50.0f;
	(*sy) += 50.0f;
}
void Game::spawnE4(std::vector<Entity>& enemies, float *sx, float *sy, SDL_Texture* enemtex) {
	Entity e;
	e.atkdmg = 550;
	e.level = 30;
	e.type = 3;
	e.sprite = enemtex;
	e.equipped = STICK;
	e.x = *sx;
	e.y = *sy;
	e.w = 50;
	e.h = 100;
	e.health = 5000;
	enemies.push_back(e);
	*sx += 50.0f;
	*sy += 50.0f;
}
void Game::spawnE5(std::vector<Entity>& enemies, float *sx, float *sy, SDL_Texture* enemtex) {
	Entity e;
	e.atkdmg = 1500;
	e.level = 50;
	e.type = 4;
	e.sprite = enemtex;
	e.equipped = STICK;
	e.x = *sx;
	e.y = *sy;
	e.w = 50;
	e.h = 100;
	e.health = 10000;
	enemies.push_back(e);
	*sx += 50.0f;
	*sy += 50.0f;
}