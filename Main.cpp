#include "Header.h"
#undef main
SDL_Renderer* rend;
bool exitf = false;
const Uint8* keys;




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
	Game game;
	texp head = NULL;
	SDL_Color yellow = { 255, 255, 100, 0 };
	SDL_Color red = { 255, 0, 50, 0 };
	SDL_Color green = { 0, 255, 50, 0 };

	SDL_Surface* playerimg = IMG_Load("player1.png");
	SDL_Texture* playertex = SDL_CreateTextureFromSurface(rend, playerimg);
	game.insertTex(head, playertex, "playertex");
	SDL_Surface* player2img = IMG_Load("bplayer1.png");
	SDL_Texture* player2tex = SDL_CreateTextureFromSurface(rend, player2img);
	game.insertTex(head, player2tex, "player2tex");
	SDL_Surface* player3img = IMG_Load("bplayer2.png");
	SDL_Texture* player3tex = SDL_CreateTextureFromSurface(rend, player3img);
	game.insertTex(head, player3tex, "player3tex");

	SDL_Surface* player4img = IMG_Load("bplayer3.png");
	SDL_Texture* player4tex = SDL_CreateTextureFromSurface(rend, player4img);
	game.insertTex(head, player4tex, "player4tex");


	SDL_Surface* doorimg = IMG_Load("door1.png");
	SDL_Texture* doortex = SDL_CreateTextureFromSurface(rend, doorimg);
	
	SDL_Surface* backimg = IMG_Load("back1.png");
	SDL_Texture* backtex = SDL_CreateTextureFromSurface(rend, backimg);
	
	SDL_Surface* enemimg = IMG_Load("enemy1.png");
	SDL_Texture* enemtex = SDL_CreateTextureFromSurface(rend, enemimg);
	game.insertTex(head, enemtex, "enemtex");

	SDL_Surface* enem2img = IMG_Load("enemy2.png");
	SDL_Texture* enem2tex = SDL_CreateTextureFromSurface(rend, enem2img);
	game.insertTex(head, enem2tex, "enem2tex");

	SDL_Surface* enem3img = IMG_Load("enemy3.png");
	SDL_Texture* enem3tex = SDL_CreateTextureFromSurface(rend, enem3img);
	game.insertTex(head, enem3tex, "enem3tex");

	SDL_Surface* enem4img = IMG_Load("enemy4.png");
	SDL_Texture* enem4tex = SDL_CreateTextureFromSurface(rend, enem4img);
	game.insertTex(head, enem4tex, "enem4tex");

	SDL_Surface* enem5img = IMG_Load("enemy5.png");
	SDL_Texture* enem5tex = SDL_CreateTextureFromSurface(rend, enem5img);
	game.insertTex(head, enem5tex, "enem5tex");

	SDL_Surface* healimg = IMG_Load("health1.png");
	SDL_Texture* healtex = SDL_CreateTextureFromSurface(rend, healimg);
	
	SDL_Surface* exlpo = IMG_Load("explosion.png");
	SDL_Texture* explotex = SDL_CreateTextureFromSurface(rend, exlpo);
	game.insertTex(head, explotex, "explotex");

	Mix_Chunk* edeath = Mix_LoadWAV("enemydeath.wav");
	Mix_Chunk* buttonsound = Mix_LoadWAV("button.wav");
	Mix_Chunk* cracksound = Mix_LoadWAV("cracksound.wav");

	texp texthead = NULL;
	//Text textures

	game.CreateText(rend, font, "Health:", yellow, texthead);
	game.CreateText(rend, font, "Crack:", yellow, texthead);
	game.CreateText(rend, font, "Level:", yellow, texthead);
	game.CreateText(rend, font, "XP:", yellow, texthead);
	game.CreateText(rend, font, "XP Required:", yellow, texthead);
	game.CreateText(rend, font, "Attack Power:", yellow, texthead);
	game.CreateText(rend, font, "Strength:", yellow, texthead);
	game.CreateText(rend, font, "Agility:", yellow, texthead);
	game.CreateText(rend, font, "Intelligence:", yellow, texthead);
	game.CreateText(rend, font, "Skill Points:", yellow, texthead);

	SDL_Event e;
	double delta = 0;
	double pcool = 0;
	double bcool = 0;
	bool combat = false;
	bool playerturn = true;
	Entity player = {0, 0, 50, 100, 100, 1, 5};
	player.xp = 0;
	player.sprite = player2tex;
	player.level = 1;
	player.health = 100000;
	player.atkdmg = 250;
	player.agility = 1.0;
	player.strength = 1.0;
	player.intelligence = 1.0;
	player.skillpoints = 0;
	int targetenemy = 0;
	int xpreq = 10;
	bool levelm = false;
	std::vector<Entity> tiles;
	std::vector<Entity> npcs;
	std::vector<Entity> enemies;
	std::vector<Button> buttons;
	std::vector<Button> mbuttons;
	std::vector<Button> upbuttons;
	std::vector<FLText> damagetext;
	std::vector<FLText> explosions;
	Entity* targenemy;
	game.createCombatButtons(buttons, texthead, rend, font, yellow);
	game.createMenuButtons(mbuttons, texthead, rend, font, yellow);
	game.createUpgradeButtons(upbuttons, texthead, rend, font, yellow);
	keys = SDL_GetKeyboardState(NULL);
	Mix_VolumeMusic(30);
	Mix_PlayMusic(backtrack, -1);
	int crack = 1;
	std::vector<ESpawner> espawners;
	game.createSpawners(espawners);
	game.loadGame(&player, &crack, &xpreq);
	game.createEnemyInstance(enemies, espawners, &player,head);
	texp end = nullptr;
	std::cout << end << std::endl;
	game.createDynamicText(rend, font, yellow, texthead, end);
	std::cout << end << std::endl;
	//Ints for last frame, will change text if these changed
	int lxp = -1, lxpreq = 0, lcrack = -1, lhealth = -1, llevel = 0;
	float latk = 0;
	bool change = false;
	while (!exitf) {
		delta = game.getDelta();
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				exitf = true;
				game.saveGame(&player, &crack, &xpreq);
				break;
			}
		}
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
		SDL_RenderClear(rend);
		if (combat) {
			SDL_PumpEvents();
			bcool += delta;
			int fps = 1 / delta;
			std::string temp = "Crack Addict RPG - FPS: " + std::to_string(fps);
			SDL_SetWindowTitle(window, temp.c_str());
			SDL_Rect back = { 0,0,800,800 };
			SDL_RenderCopy(rend, backtex, NULL, &back);
			if (levelm) {
				texp te = texthead;
				int j = 0;
				while (te != end) {
					switch (j) {
					case 0:
						game.editText(rend, font, std::to_string(player.strength), yellow, te);
						break;
					case 1:
						game.editText(rend, font, std::to_string(player.agility), yellow, te);
						break;
					case 2:
						game.editText(rend, font, std::to_string(player.intelligence), yellow, te);
						break;
					case 3:
						game.editText(rend, font, std::to_string(player.skillpoints), yellow, te);
						break;
					}
					j++;
					te = te->next;
				}
				game.drawText(rend, texthead, "Strength:", 100, 100, 75, 50);
				game.drawText(rend, texthead, std::to_string(player.strength), 175, 100, 75, 50);
				game.drawText(rend, texthead, "Agility:", 275, 100, 75, 50);
				game.drawText(rend, texthead, std::to_string(player.agility), 350, 100, 75, 50);
				game.drawText(rend, texthead, "Intelligence:", 475, 100, 75, 50);
				game.drawText(rend, texthead, std::to_string(player.intelligence), 550, 100, 75, 50);
				game.drawText(rend, texthead, "Skill Points:", 325, 250, 100, 50);
				game.drawText(rend, texthead, std::to_string(player.skillpoints), 425, 250, 100, 50);
				game.updateupButtons(upbuttons, rend, texthead, &bcool, &player, &levelm, &change);
			}
			else {
				if (keys[SDL_SCANCODE_DOWN]) {
					targetenemy++;
					if (targetenemy > enemies.size() - 1) {
						targetenemy = 0;
					}
				}
				if (keys[SDL_SCANCODE_ESCAPE]) {
					combat = false;
				}
				targenemy = &enemies[targetenemy];
				if (player.xp >= xpreq) {
					player.level++;
					player.atkdmg += 5;
					player.xp -= xpreq;
					xpreq += 10;
					player.skillpoints += 2;
				}
				game.drawText(rend, texthead, "Health:", 300, 20, 100, 50);
				game.drawText(rend, texthead, std::to_string(player.health), 400, 20, 100, 50);
				game.drawText(rend, texthead, "Level:", 50, 20, 100, 50);
				game.drawText(rend, texthead, std::to_string(player.level), 150, 20, 50, 50);
				game.drawText(rend, texthead, "XP:", 50, 70, 100, 50);
				game.drawText(rend, texthead, std::to_string(player.xp), 150, 70, 50, 50);
				game.drawText(rend, texthead, "XP Required:", 50, 120, 100, 50);
				game.drawText(rend, texthead, std::to_string(xpreq), 150, 120, 50, 50);
				game.drawText(rend, texthead, "Attack Power:", 50, 170, 100, 50);
				game.drawText(rend, texthead, std::to_string(player.atkdmg), 150, 170, 75, 50);
				game.drawText(rend, texthead, "Crack:", 50, 220, 100, 50);
				game.drawText(rend, texthead, std::to_string(crack), 150, 220, 50, 50);
				SDL_Rect pl = { 300, 300, 50, 100 };
				SDL_RenderCopy(rend, player.sprite, NULL, &pl);
				game.updateDamage(damagetext, delta, rend, font, head);
				game.updateEnemies(explosions, enemies, damagetext, &crack, playerturn, &player, rend, healtex, edeath);
				if (!playerturn) {
					playerturn = true;
				}
				game.updateExplosions(explosions, delta, head, rend);
				game.updateButtons(buttons, damagetext, &player, targenemy, rend, texthead, enemies.size(), &bcool, &crack, &playerturn, &levelm, head, buttonsound, cracksound);
				if (player.health < 0) {
					player.health = 100;
					player.atkdmg = 5;
					player.level = 1;
					player.xp = 0;
					crack = 1;
					xpreq = 10;
					enemies.clear();
					game.createEnemyInstance(enemies, espawners, &player, head);
				}
				if (enemies.size() <= 0) {
					crack++;
					game.createEnemyInstance(enemies, espawners, &player, head);
				}
				texp te = texthead;
				int j = 0;
				while (te != end) {
					switch (j) {
					case 0:
						if (lcrack != crack || change) {
							game.editText(rend, font, std::to_string(crack), yellow, te);
						}
						break;
					case 1:
						if (lhealth != player.health || change) {
							game.editText(rend, font, std::to_string(player.health), yellow, te);
						}
						break;
					case 2:
						if (lxp != player.xp || change) {
							game.editText(rend, font, std::to_string(player.xp), yellow, te);
						}
						break;
					case 3:
						if (llevel != player.level || change) {
							game.editText(rend, font, std::to_string(player.level), yellow, te);
						}
						break;
					case 4:
						if (latk != player.atkdmg || change) {
							game.editText(rend, font, std::to_string(player.atkdmg), yellow, te);
						}
						break;
					case 5:
						if (lxpreq != xpreq || change) {
							game.editText(rend, font, std::to_string(xpreq), yellow, te);
						}
						break;
					}
					j++;
					te = te->next;
				}
				if (change) {
					change = false;
				}
				lxp = player.xp;
				lxpreq = xpreq;
				llevel = player.level;
				lcrack = crack;
				lhealth = player.health;
				latk = player.atkdmg;
			}

		}
		else{
			bcool += delta;
			game.updatemButtons(mbuttons, &combat, &exitf, &bcool, rend, texthead, &player);
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