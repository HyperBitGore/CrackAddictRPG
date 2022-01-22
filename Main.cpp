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
	int targetenemy = 0;
	int xpreq = 10;
	std::vector<Entity> tiles;
	std::vector<Entity> npcs;
	std::vector<Entity> enemies;
	std::vector<Button> buttons;
	std::vector<Button> mbuttons;
	std::vector<FLText> damagetext;
	std::vector<FLText> explosions;
	Entity* targenemy;
	game.createCombatButtons(buttons);
	keys = SDL_GetKeyboardState(NULL);
	SDL_Color red = { 255, 0, 50, 0 };
	SDL_Color green = { 0, 255, 50, 0 };
	Mix_VolumeMusic(30);
	Mix_PlayMusic(backtrack, -1);
	int crack = 1;
	std::vector<ESpawner> espawners;
	game.createSpawners(espawners);
	game.loadGame(&player, &crack, &xpreq);
	game.createMenuButtons(mbuttons);
	game.createEnemyInstance(enemies, espawners, &player,head);
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
		//write out combat system here
		if (combat) {
			SDL_PumpEvents();
			bcool += delta;
			int fps = 1 / delta;
			std::string temp = "Crack Addict RPG - FPS: " + std::to_string(fps);
			SDL_SetWindowTitle(window, temp.c_str());
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
			}

			SDL_Rect back = { 0,0,800,800 };
			SDL_RenderCopy(rend, backtex, NULL, &back);
			game.drawText(rend, font, "Health:", { 255, 255, 100, 0 }, 300, 20, 100, 50);
			game.drawText(rend, font, std::to_string(player.health), { 255, 255, 100, 0 }, 400, 20, 100, 50);
			game.drawText(rend, font, "Level:", {255, 255, 100, 0}, 50, 20, 100, 50);
			game.drawText(rend, font, std::to_string(player.level), { 255, 255, 100, 0 }, 150, 20, 50, 50);
			game.drawText(rend, font, "XP:", { 255, 255, 100, 0 }, 50, 70, 100, 50);
			game.drawText(rend, font, std::to_string(player.xp), { 255, 255, 100, 0 }, 150, 70, 50, 50);
			game.drawText(rend, font, "XP Required:", { 255, 255, 100, 0 }, 50, 120, 100, 50);
			game.drawText(rend, font, std::to_string(xpreq), { 255, 255, 100, 0 }, 150, 120, 50, 50);
			game.drawText(rend, font, "Attack Power:", { 255, 255, 100, 0 }, 50, 170, 100, 50);
			game.drawText(rend, font, std::to_string(player.atkdmg), { 255, 255, 100, 0 }, 150, 170, 50, 50);
			game.drawText(rend, font, "Crack:", { 255, 255, 100, 0 }, 50, 220, 100, 50);
			game.drawText(rend, font, std::to_string(crack), { 255, 255, 100, 0 }, 150, 220, 50, 50);
			SDL_Rect pl = { 300, 300, 50, 100 };
			SDL_RenderCopy(rend, player.sprite, NULL, &pl);
			game.updateDamage(damagetext, delta, red, green, rend, font);
			game.updateEnemies(explosions, enemies, damagetext, &crack, playerturn, &player, rend, healtex, edeath);
			if (!playerturn) {
				playerturn = true;
			}
			game.updateExplosions(explosions, delta, head, rend);
			game.updateButtons(buttons, damagetext, &player, targenemy, rend, font, enemies.size(), &bcool, &crack, &playerturn, head, buttonsound, cracksound);
			if (player.health < 0) {
				player.health = 100;
				player.atkdmg = 5;
				player.level = 1;
				player.xp = 0;
				crack = 1;
				xpreq = 10;
				enemies.clear();
				game.createEnemyInstance(enemies, espawners, &player,head);
			}
			if (enemies.size() <= 0) {
				crack++;
				game.createEnemyInstance(enemies, espawners, &player, head);
			}
		}
		else{
			bcool += delta;
			game.updatemButtons(mbuttons, &combat, &exitf, &bcool, rend, font, &player);
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