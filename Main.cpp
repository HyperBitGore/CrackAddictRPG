#include "Header.h"
#undef main
SDL_Renderer* rend;
bool exitf = false;
const Uint8* keys;

void atkButton(Entity* e, Entity* e2) {
	(*e2).health -= (*e).atkdmg;
}
void runButton(Entity* e, Entity* e2) {
	(*e).health += (*e).atkdmg;
}
void crackButton(Entity* e, Entity* e2) {
	
}

void createCombatButtons(std::vector<Button>& buttons) {
	Button b = { 185, 550, 100, 50 };
	b.text = "Attack";
	b.click = &atkButton;
	buttons.push_back(b);
	Button b2 = { 350, 550, 100, 50 };
	b2.text = "Block";
	b2.click = &runButton;
	buttons.push_back(b2);
	Button b3 = { 400, 650, 100, 50 };
	b3.text = "Do Crack!";
	b3.click = &crackButton;
	buttons.push_back(b3);
}

int main() {
	srand(time(NULL));
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0) {
		std::cout << "SDL Init failed: " << SDL_GetError << std::endl;
	}
	if (!TTF_Init()) {
		std::cout << "Font init failed" << TTF_GetError << std::endl;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "Error: " << Mix_GetError() << std::endl;
	}
	if (!(IMG_Init(IMG_INIT_PNG))) {
		std::cout << "Image init failed: " << IMG_GetError << std::endl;
	}
	SDL_Window* window = SDL_CreateWindow("Crack Addict RPG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
	rend = SDL_CreateRenderer(window, -1, 0);
	Mix_Music* backtrack = Mix_LoadMUS("crack.wav");
	TTF_Font* font = TTF_OpenFont("DelaGothicOne-Regular.ttf", 12);
	SDL_Surface* roadimg = IMG_Load("road1.png");
	SDL_Texture* roadtex = SDL_CreateTextureFromSurface(rend, roadimg);
	SDL_Surface* wallimg = IMG_Load("wall1.png");
	SDL_Texture* walltex = SDL_CreateTextureFromSurface(rend, wallimg);
	SDL_Surface* wallbimg = IMG_Load("wallb1.png");
	SDL_Texture* wallbtex = SDL_CreateTextureFromSurface(rend, wallbimg);
	SDL_Surface* floorimg = IMG_Load("floor1.png");
	SDL_Texture* floortex = SDL_CreateTextureFromSurface(rend, floorimg);
	SDL_Surface* playerimg = IMG_Load("player1.png");
	SDL_Texture* playertex = SDL_CreateTextureFromSurface(rend, playerimg);
	SDL_Surface* player2img = IMG_Load("bplayer1.png");
	SDL_Texture* player2tex = SDL_CreateTextureFromSurface(rend, player2img);
	SDL_Surface* player3img = IMG_Load("bplayer2.png");
	SDL_Texture* player3tex = SDL_CreateTextureFromSurface(rend, player3img);
	SDL_Surface* player4img = IMG_Load("bplayer3.png");
	SDL_Texture* player4tex = SDL_CreateTextureFromSurface(rend, player4img);
	SDL_Surface* doorimg = IMG_Load("door1.png");
	SDL_Texture* doortex = SDL_CreateTextureFromSurface(rend, doorimg);
	SDL_Surface* backimg = IMG_Load("back1.png");
	SDL_Texture* backtex = SDL_CreateTextureFromSurface(rend, backimg);
	SDL_Surface* enemimg = IMG_Load("enemy1.png");
	SDL_Texture* enemtex = SDL_CreateTextureFromSurface(rend, enemimg);
	SDL_Surface* enem2img = IMG_Load("enemy2.png");
	SDL_Texture* enem2tex = SDL_CreateTextureFromSurface(rend, enem2img);
	SDL_Surface* enem3img = IMG_Load("enemy3.png");
	SDL_Texture* enem3tex = SDL_CreateTextureFromSurface(rend, enem3img);
	SDL_Surface* enem4img = IMG_Load("enemy4.png");
	SDL_Texture* enem4tex = SDL_CreateTextureFromSurface(rend, enem4img);
	SDL_Surface* enem5img = IMG_Load("enemy5.png");
	SDL_Texture* enem5tex = SDL_CreateTextureFromSurface(rend, enem5img);
	SDL_Surface* healimg = IMG_Load("health1.png");
	SDL_Texture* healtex = SDL_CreateTextureFromSurface(rend, healimg);
	SDL_Surface* exlpo = IMG_Load("explosion.png");
	SDL_Texture* explotex = SDL_CreateTextureFromSurface(rend, exlpo);
	Mix_Chunk* edeath = Mix_LoadWAV("enemydeath.wav");
	Mix_Chunk* buttonsound = Mix_LoadWAV("button.wav");
	Mix_Chunk* cracksound = Mix_LoadWAV("cracksound.wav");
	SDL_Event e;
	Game game;
	double delta = 0;
	double pcool = 0;
	double bcool = 0;
	bool combat = true;
	bool playerturn = true;
	Entity player;
	player.sprite = player2tex;
	int targetenemy = 0;
	int xpreq = 10;
	int crack = 1;
	std::vector<Entity> tiles;
	std::vector<Entity> npcs;
	std::vector<Entity> enemies;
	std::vector<Button> buttons;
	std::vector<FLText> damagetext;
	std::vector<FLText> explosions;
	createCombatButtons(buttons);
	keys = SDL_GetKeyboardState(NULL);
	game.generateMap(tiles, &player);
	std::cout << buttons.size() << std::endl;
	SDL_Color red = { 255, 0, 50, 0 };
	SDL_Color green = { 0, 255, 50, 0 };
	Mix_VolumeMusic(30);
	Mix_PlayMusic(backtrack, -1);
	while (!exitf) {
		delta = game.getDelta();
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				exitf = true;
				break;
			}
		}
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
		SDL_RenderClear(rend);
		//write out combat system here
		if (combat) {
			//list moves under attack, and put block and run off to side as big buttons
			//limited number of moves
			SDL_PumpEvents();
			bcool += delta;
			if (keys[SDL_SCANCODE_DOWN]) {
				targetenemy++;
				if (targetenemy > enemies.size() - 1) {
					targetenemy = 0;
				}
			}
			if (player.xp >= xpreq) {
				player.level++;
				player.atkdmg += 5;
				player.xp -= xpreq;
				xpreq += 10;
			}

			SDL_Rect back = { 0,0,800,800 };
			SDL_RenderCopy(rend, backtex, NULL, &back);
			game.drawText(rend, font, "Health:", { 255, 255, 100, 0 }, 300, 20, 100, 50);
			game.drawText(rend, font, std::to_string(player.health), { 255, 255, 100, 0 }, 400, 20, 100, 50);
			game.drawText(rend, font, "Level:", {255, 255, 100, 0}, 50, 20, 100, 50);
			game.drawText(rend, font, std::to_string(player.level), { 255, 255, 100, 0 }, 150, 20, 100, 50);
			game.drawText(rend, font, "Attack Power:", { 255, 255, 100, 0 }, 50, 50, 100, 50);
			game.drawText(rend, font, std::to_string(player.atkdmg), { 255, 255, 100, 0 }, 150, 50, 100, 50);
			game.drawText(rend, font, "Crack:", { 255, 255, 100, 0 }, 50, 100, 100, 50);
			game.drawText(rend, font, std::to_string(crack), { 255, 255, 100, 0 }, 150, 100, 100, 50);
			SDL_Rect pl = { 300, 300, 50, 100 };
			SDL_RenderCopy(rend, player.sprite, NULL, &pl);
			for (int i = 0; i < damagetext.size(); i++) {
				damagetext[i].timer += delta;
				SDL_Color current;
				if (damagetext[i].type == 0) {
					current = red;
				}
				else {
					current = green;
				}
				game.drawText(rend, font, damagetext[i].text, current, damagetext[i].x, damagetext[i].y, damagetext[i].w, damagetext[i].h);
				if (damagetext[i].timer > 0.5) {
					damagetext.erase(damagetext.begin() + i);
				}
			}
			for (int i = 0; i < enemies.size(); i++) {
				SDL_Rect erect = { enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h };
				switch (enemies[i].type) {
				case 0:
					SDL_RenderCopy(rend, enemtex, NULL, &erect);
					break;
				case 1:
					SDL_RenderCopy(rend, enem2tex, NULL, &erect);
					break;
				case 2:
					SDL_RenderCopy(rend, enem3tex, NULL, &erect);
					break;
				case 3:
					SDL_RenderCopy(rend, enem4tex, NULL, &erect);
					break;
				case 4:
					SDL_RenderCopy(rend, enem5tex, NULL, &erect);
					break;
				}
				SDL_Rect ehrect = { enemies[i].x - 10,enemies[i].y - 10, enemies[i].health, 10 };
				SDL_RenderCopy(rend, healtex, NULL, &ehrect);
				if (!playerturn) {
					player.health -= enemies[i].atkdmg;
					FLText f = { rand() % 550 + player.x, rand() % 550 + player.y, 30, 12, std::to_string(enemies[i].atkdmg), 0, 0 };
					damagetext.push_back(f);
				}
				if (enemies[i].health <= 0) {
					int rollcrack = rand() % 100;
					if (rollcrack > 50) {
						switch (enemies[i].type) {
						case 0:
							crack++;
							break;
						case 1:
							crack += 2;
							break;
						case 2:
							crack += 8;
							break;
						case 3:
							crack += 30;
							break;
						case 4:
							crack += 50;
							break;

						}
					}
					FLText f = {enemies[i].x, enemies[i].y, 50, 50, "NULL", 0, 0};
					explosions.push_back(f);
					player.xp += enemies[i].level;
					Mix_PlayChannel(-1, edeath, 0);
					enemies.erase(enemies.begin() + i);
				}
			}
			if (!playerturn) {
				playerturn = true;
			}
			for (int i = 0; i < explosions.size(); i++) {
				explosions[i].timer += delta;
				SDL_Rect erect = { explosions[i].x, explosions[i].y, explosions[i].w, explosions[i].h };
				SDL_RenderCopy(rend, explotex, NULL, &erect);
				if (explosions[i].timer > 0.2) {
					explosions.erase(explosions.begin() + i);
				}
			}
			for (auto& i : buttons) {
				SDL_Rect but = { i.x, i.y, i.w, i.h };
				SDL_RenderDrawRect(rend, &but);
				game.drawText(rend, font, i.text, { 255, 255, 100, 0 }, i.x, i.y, i.w, i.h);
			}
			if (bcool >= 0.1) {
				int mx;
				int my;
				int k = 0;
				if (SDL_GetMouseState(&mx, &my) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
					for (auto& i : buttons) {
					if (mx >= i.x && mx <= i.x + i.w && my >= i.y && my <= i.y + i.h) {
						if (enemies.size() > 0) {
							i.click(&player, &enemies[targetenemy]);
							FLText f = { rand() % 550 + player.x, rand() % 550 + player.y, 30, 12, std::to_string(player.atkdmg), 0, 1 };
							damagetext.push_back(f);
							switch (k) {
							case 0:
								player.sprite = player4tex;
								Mix_PlayChannel(-1, buttonsound, 0);
								break;
							case 1:
								player.sprite = player3tex;
								Mix_PlayChannel(-1, buttonsound, 0);
								break;
							case 2:
								if (crack > 0) {
									crack--;
									player.atkdmg++;
									player.health+=60;
									player.sprite = player2tex;
									Mix_PlayChannel(-1, cracksound, 0);
								}
								break;
							}
							playerturn = false;
						}
					}
					bcool = 0;
					k++;
				}
			}
		}
			if (player.health < 0) {
				player.health = 100;
				player.atkdmg = 5;
				player.level = 1;
				player.xp = 0;
				crack = 1;
				enemies.clear();
				game.createEnemyInstance(enemies, &player);
			}
			if (enemies.size() <= 0) {
				crack++;
				game.createEnemyInstance(enemies, &player);
			}
		}
		else {
			//convert this to using texture pointer so copper wiring removal works without making walls walkable
			for (auto& i : tiles) {
				SDL_Rect rec = { i.x, i.y, i.w, i.h };
				switch (i.type) {
				case 0:
					SDL_RenderCopy(rend, roadtex, NULL, &rec);
					break;
				case 1:
					SDL_RenderCopy(rend, walltex, NULL, &rec);
					break;
				case 2:
					SDL_RenderCopy(rend, floortex, NULL, &rec);
					break;
				case 3:
					SDL_RenderCopy(rend, doortex, NULL, &rec);
					break;
				case 4:
					SDL_RenderCopy(rend, wallbtex, NULL, &rec);
					break;
				}


			}
			//add the static npc vendors
			for (auto& i : npcs) {

			}
			pcool += delta;
			if (pcool >= 0.1) {
				game.playerUpdate(&player, (float)delta, tiles);
				if (keys[SDL_SCANCODE_ESCAPE]) {
					game.createEnemyInstance(enemies, &player);
					combat = true;
				}
				pcool = 0;
			}
			SDL_Rect prec = { player.x, player.y, player.w, player.h };
			SDL_RenderCopy(rend, playertex, NULL, &prec);
		}
		SDL_RenderPresent(rend);
	}
	TTF_Quit();
	Mix_Quit();
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}