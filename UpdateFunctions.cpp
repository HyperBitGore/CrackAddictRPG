#include "Header.h"



void Game::updateEnemies(std::vector<FLText>& explosions, std::vector<Entity>& enemies, std::vector<FLText>& damagetext, int *crack, bool playerturn, Entity *player, SDL_Renderer* rend, SDL_Texture* healtex, Mix_Chunk* edeath) {
	for (int i = 0; i < enemies.size(); i++) {
		SDL_Rect erect = { enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h };
		SDL_RenderCopy(rend, enemies[i].sprite, NULL, &erect);
		SDL_Rect ehrect = { enemies[i].x - 10,enemies[i].y - 10, enemies[i].health, 10 };
		SDL_RenderCopy(rend, healtex, NULL, &ehrect);
		if (!playerturn) {
			(*player).health -= enemies[i].atkdmg;
			FLText f = { rand() % 550 + (*player).x, rand() % 550 + (*player).y, 30, 12, std::to_string(enemies[i].atkdmg), 0, 0 };
			damagetext.push_back(f);
		}
		if (enemies[i].health <= 0) {
			int rollcrack = rand() % 100;
			if (rollcrack > 50) {
				switch (enemies[i].type) {
				case 0:
					(*crack)++;
					break;
				case 1:
					(*crack) += 2;
					break;
				case 2:
					(*crack) += 8;
					break;
				case 3:
					(*crack) += 30;
					break;
				case 4:
					(*crack) += 50;
					break;

				}
			}
			FLText f = { enemies[i].x, enemies[i].y, 50, 50, "NULL", 0, 0 };
			explosions.push_back(f);
			(*player).xp += enemies[i].level;
			Mix_PlayChannel(-1, edeath, 0);
			enemies.erase(enemies.begin() + i);
		}
	}
}
void Game::updateExplosions(std::vector<FLText>& explosions, double delta, SDL_Texture* explotex, SDL_Renderer* rend) {
	for (int i = 0; i < explosions.size(); i++) {
		explosions[i].timer += delta;
		SDL_Rect erect = { explosions[i].x, explosions[i].y, explosions[i].w, explosions[i].h };
		SDL_RenderCopy(rend, explotex, NULL, &erect);
		if (explosions[i].timer > 0.2) {
			explosions.erase(explosions.begin() + i);
		}
	}
}

void Game::updateButtons(std::vector<Button>& buttons, std::vector<Entity>& enemies, std::vector<FLText>& damagetext, Entity* player, SDL_Renderer* rend, TTF_Font* font, double *bcool, int targetenemy, int *crack, bool *playerturn, SDL_Texture* player4tex, SDL_Texture* player3tex, SDL_Texture* player2tex, Mix_Chunk* buttonsound, Mix_Chunk* cracksound) {
	for (auto& i : buttons) {
		SDL_Rect but = { i.x, i.y, i.w, i.h };
		SDL_RenderDrawRect(rend, &but);
		drawText(rend, font, i.text, { 255, 255, 100, 0 }, i.x, i.y, i.w, i.h);
	}
	if ((*bcool) >= 0.1) {
		int mx;
		int my;
		int k = 0;
		if (SDL_GetMouseState(&mx, &my) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			for (auto& i : buttons) {
				if (mx >= i.x && mx <= i.x + i.w && my >= i.y && my <= i.y + i.h) {
					if (enemies.size() > 0) {
						i.click(player, &enemies[targetenemy]);
						FLText f = { rand() % 550 + (*player).x, rand() % 550 + (*player).y, 30, 12, std::to_string((*player).atkdmg), 0, 1 };
						damagetext.push_back(f);
						switch (k) {
						case 0:
							(*player).sprite = player4tex;
							Mix_PlayChannel(-1, buttonsound, 0);
							break;
						case 1:
							(*player).sprite = player3tex;
							Mix_PlayChannel(-1, buttonsound, 0);
							break;
						case 2:
							if ((*crack) > 0) {
								(*crack)--;
								(*player).atkdmg++;
								(*player).health += 60;
								(*player).sprite = player2tex;
								Mix_PlayChannel(-1, cracksound, 0);
							}
							break;
						}
						(*playerturn) = false;
					}
				}
				(*bcool) = 0;
				k++;
			}
		}
	}
}
void Game::updateDamage(std::vector<FLText>& damagetext, double delta, SDL_Color red, SDL_Color green, SDL_Renderer* rend, TTF_Font* font) {
	for (int i = 0; i < damagetext.size(); i++) {
		damagetext[i].timer += delta;
		SDL_Color current;
		if (damagetext[i].type == 0) {
			current = red;
		}
		else {
			current = green;
		}
		drawText(rend, font, damagetext[i].text, current, damagetext[i].x, damagetext[i].y, damagetext[i].w, damagetext[i].h);
		if (damagetext[i].timer > 0.5) {
			damagetext.erase(damagetext.begin() + i);
		}
	}
}