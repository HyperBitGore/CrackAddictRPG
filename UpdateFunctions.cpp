#include "Header.h"



void Game::updateEnemies(std::vector<FLText>& explosions, std::vector<Entity>& enemies, std::vector<FLText>& damagetext, int *crack, bool playerturn, Entity *player, SDL_Renderer* rend, SDL_Texture* healtex, Mix_Chunk* edeath) {
	for (int i = 0; i < enemies.size(); i++) {
		SDL_Rect erect = { enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h };
		SDL_RenderCopy(rend, enemies[i].sprite, NULL, &erect);
		SDL_Rect ehrect = { enemies[i].x - 10,enemies[i].y - 10, enemies[i].health, 10 };
		SDL_RenderCopy(rend, healtex, NULL, &ehrect);
		if (!playerturn) {
			(*player).health -= enemies[i].atkdmg;
			FLText f = { rand() % 550 + (*player).x, rand() % 550 + (*player).y, 30, 12, std::to_string(enemies[i].atkdmg), 0, 0, { 255, 0, 50, 0 } };
			damagetext.push_back(f);
		}
		if (enemies[i].health <= 0) {
			int rollcrack = rand() % 100;
			if (rollcrack > 50) {
				(*crack) += enemies[i].level;
			}
			FLText f = { enemies[i].x, enemies[i].y, 50, 50, "NULL", 0, 0 };
			explosions.push_back(f);
			(*player).xp += enemies[i].level;
			Mix_PlayChannel(-1, edeath, 0);
			enemies.erase(enemies.begin() + i);
		}
	}
}
void Game::updateExplosions(std::vector<FLText>& explosions, double delta, texp head, SDL_Renderer* rend) {
	for (int i = 0; i < explosions.size(); i++) {
		explosions[i].timer += delta;
		SDL_Rect erect = { explosions[i].x, explosions[i].y, explosions[i].w, explosions[i].h };
		SDL_RenderCopy(rend, findTex(head, "explotex"), NULL, &erect);
		if (explosions[i].timer > 0.2) {
			explosions.erase(explosions.begin() + i);
		}
	}
}

void Game::updateButtons(std::vector<Button>& buttons, std::vector<FLText>& damagetext, Entity* player, Entity *targenemy, SDL_Renderer* rend, texp font, int esize, double *bcool, int *crack, bool *playerturn, bool *levelm, texp head, Mix_Chunk* buttonsound, Mix_Chunk* cracksound) {
	for (auto& i : buttons) {
		SDL_Rect but = { i.x, i.y, i.w, i.h };
		SDL_RenderDrawRect(rend, &but);
		drawText(rend, font, i.text, i.x, i.y, i.w, i.h);
	}
	if ((*bcool) >= 0.1) {
		int mx;
		int my;
		int k = 0;
		if (SDL_GetMouseState(&mx, &my) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			for (auto& i : buttons) {
				if (mx >= i.x && mx <= i.x + i.w && my >= i.y && my <= i.y + i.h) {
					if (esize > 0) {
						i.click(player, targenemy);
						FLText f = { rand() % 550 + (*player).x, rand() % 550 + (*player).y, 30, 12, std::to_string((*player).atkdmg), 0, 1, { 0, 255, 50, 0 } };
						damagetext.push_back(f);
						switch (k) {
						case 0:
							(*player).sprite = findTex(head, "player4tex");
							Mix_PlayChannel(-1, buttonsound, 0);
							break;
						case 1:
							(*player).sprite = findTex(head, "player3tex");
							Mix_PlayChannel(-1, buttonsound, 0);
							break;
						case 2:
							if ((*crack) > 0) {
								(*crack)--;
								(*player).atkdmg++;
								(*player).health += 60;
								(*player).sprite = findTex(head, "player2tex");
								Mix_PlayChannel(-1, cracksound, 0);
							}
							break;
						case 3:
							(*levelm) = true;
							break;
						}
						(*playerturn) = false;
					}
				}
				k++;
			}
			(*bcool) = 0;
		}
	}
}
void Game::updateDamage(std::vector<FLText>& damagetext, double delta, SDL_Renderer* rend, TTF_Font* font, texp head) {
	for (int i = 0; i < damagetext.size(); i++) {
		damagetext[i].timer += delta;
		drawTempText(rend, font, damagetext[i].text, damagetext[i].color, damagetext[i].x, damagetext[i].y, damagetext[i].w, damagetext[i].h);
		if (damagetext[i].timer > 0.5) {
			damagetext.erase(damagetext.begin() + i);
		}
	}
}

void Game::updatemButtons(std::vector<Button>& buttons, bool* combat, bool* exitf, double* bcool, SDL_Renderer* rend, texp font, Entity* player) {
	for (auto& i : buttons) {
		SDL_Rect but = { i.x, i.y, i.w, i.h };
		SDL_RenderDrawRect(rend, &but);
		drawText(rend, font, i.text, i.x, i.y, i.w, i.h);
	}
	int k = 0;
	int mx;
	int my;
	if ((*bcool) >= 0.1) {
		if (SDL_GetMouseState(&mx, &my) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			for (auto& i : buttons) {
				if (mx >= i.x && mx <= i.x + i.w && my >= i.y && my <= i.y + i.h) {
					switch (k) {
					case 0:
						(*combat) = true;
						(*player).health = -1;
						break;
					case 1:
						(*combat) = true;
						break;
					case 2:
						(*exitf) = true;
						break;
					}
				}
				k++;
			}
			(*bcool) = 0;
		}
	}
}
void Game::updateupButtons(std::vector<Button>& buttons, SDL_Renderer* rend, texp font, double* bcool, Entity *player, bool *levelm, bool* change) {
	for (auto& i : buttons) {
		SDL_Rect but = { i.x, i.y, i.w, i.h };
		SDL_RenderDrawRect(rend, &but);
		drawText(rend, font, i.text, i.x, i.y, i.w, i.h);
	}
	int k = 0;
	int mx, my;
	if ((*bcool) >= 0.1) {
		if (SDL_GetMouseState(&mx, &my) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			for (auto& i : buttons) {
				if (mx >= i.x && mx <= i.x + i.w && my >= i.y && my <= i.y + i.h) {
					switch (k) {
					case 0:
						if ((*player).skillpoints > 0) {
							(*player).strength += 0.01;
							(*player).atkdmg *= (*player).strength;
							(*player).skillpoints--;
						}
						break;
					case 1:
						if ((*player).skillpoints > 0) {
							(*player).agility += 0.01;
							(*player).atkdmg *= (*player).agility;
							(*player).skillpoints--;
						}
						break;
					case 2:
						if ((*player).skillpoints > 0) {
							(*player).intelligence += 0.01;
							(*player).atkdmg *= (*player).intelligence;
							(*player).skillpoints--;
						}
						break;
					case 3:
						(*levelm) = false;
						(*change) = true;
						break;
					}
				}
				k++;
			}
			(*bcool) = 0;
		}
	}

}