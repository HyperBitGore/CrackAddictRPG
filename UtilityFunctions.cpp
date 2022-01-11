#include "Header.h"



void Game::drawText(SDL_Renderer* rend, TTF_Font* font, std::string text, SDL_Color color, int x, int y, int w, int h) {
	SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surf);
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderCopy(rend, texture, NULL, &rect);

	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);
}
//Leftover from trying to implement std::function with std::bind to replace C function pointer
//https://stackoverflow.com/questions/11037393/c-function-pointer-to-functions-with-variable-number-of-arguments
//Might still be do able
void Game::attackButton(Entity* player, Entity* enemy, SDL_Texture* player4tex, Mix_Chunk* buttonsound) {
	(*enemy).health -= (*player).atkdmg;
	(*player).sprite = player4tex;
	Mix_PlayChannel(-1, buttonsound, 0);
}
//Button decs
void atkButton(Entity* e, Entity* e2) {
	(*e2).health -= (*e).atkdmg;
}
void runButton(Entity* e, Entity* e2) {
	(*e).health += (*e).atkdmg;
}
void crackButton(Entity* e, Entity* e2) {

}
void Game::createCombatButtons(std::vector<Button>& buttons) {
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
void Game::createSpawners(std::vector<ESpawner>& espawners) {
	ESpawner e;
	//Basic spawning
	e.maxlvl = 5;
	e.minlvl = 0;
	e.spawnchances = { 0 };
	e.etypes = { 0 };
	espawners.push_back(e);
	//Enemy 2 introduced
	e.maxlvl = 10;
	e.minlvl = 5;
	e.spawnchances = { 52, 0 };
	e.etypes = { 1, 0 };
	espawners.push_back(e);
	//Enemy 3 introduced
	e.maxlvl = 20;
	e.minlvl = 10;
	e.spawnchances = { 52, 35, 0 };
	e.etypes = { 2, 1, 0 };
	espawners.push_back(e);
	//Enemy 4 introduced
	e.maxlvl = 40;
	e.minlvl = 20;
	e.spawnchances = { 48, 35, 20, 0 };
	e.etypes = { 3, 2, 1, 0 };
	espawners.push_back(e);
	//Enemy 5 introduced
	e.maxlvl = 100;
	e.minlvl = 40;
	e.spawnchances = { 45, 35, 20, 10, 0 };
	e.etypes = { 4, 3, 2, 1, 0 };
	espawners.push_back(e);
}



void Game::createEnemyInstance(std::vector<Entity>& enemies, std::vector<ESpawner>& espawners,  Entity* p, texp head) {
	float sx = 500.0f;
	float sy = 250.0f;
	int spawnamount = rand() % 3 + 1;
	for (auto& i : espawners) {
		if ((*p).level >= i.minlvl && (*p).level < i.maxlvl) {
			for (int k = spawnamount; k > 0; k--) {
				int roll = rand() % 100;
				for (int j = 0; j < i.spawnchances.size(); j++) {
					if (roll > i.spawnchances[j]) {
						switch (i.etypes[j]) {
						case 0:
							spawnE1(enemies, &sx, &sy, findTex(head, "enemtex"));
							break;
						case 1:
							spawnE2(enemies, &sx, &sy, findTex(head, "enem2tex"));
							break;
						case 2:
							spawnE3(enemies, &sx, &sy, findTex(head, "enem3tex"));
							break;
						case 3:
							spawnE4(enemies, &sx, &sy, findTex(head, "enem4tex"));
							break;
						case 4:
							spawnE5(enemies, &sx, &sy, findTex(head, "enem5tex"));
							break;
						}
						break;
					}
				}
			}
			return;
		}
	}
}
//Make this work lmao
void Game::insertTex(texp tex, SDL_Texture* current) {
	texp t;
	t = new TexListMem;
	t->current = current;
	t->next = tex;
	std::cout << t->next << std::endl;
	tex = t;
}

SDL_Texture* Game::findTex(texp head, std::string name) {
	texp temp = head;
	while (temp != NULL) {
		if (std::strcmp(temp->name.c_str(), name.c_str()) == 0) {
			return temp->current;
		}
		temp = temp->next;
	}
	return NULL;
}