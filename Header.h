#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <math.h>
#include <time.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <functional> 

class Game;
enum ITYPE {EMPTY, STICK, RPIPE, CPIPE, CWIRE, HOODIE, SWEATP, JEANS, TSHIRT, WIFEB};
extern const Uint8* keys;
struct Entity {
	float x;
	float y;
	int w;
	int h;
	int health;
	int level;
	float atkdmg;
	std::vector<ITYPE> inventory;
	//index 0 is hands, index 1 is shoes, index 2 is pants, index 3 is shirt, index 4 is back, index 5 is hands, index 6 is head
	ITYPE equipped;
	int type;
	int index;
	int xp;
	float strength;
	float agility;
	float intelligence;
	int skillpoints;
	SDL_Texture* sprite;
};
struct FLText {
	int x;
	int y;
	int w;
	int h;
	std::string text;
	double timer;
	int type;
	SDL_Color color;
};
class Button {
public:
	int x;
	int y;
	int w;
	int h;
	std::string text;
	void (*click)(Entity*, Entity*);
};
struct ESpawner {
public:
	int maxlvl;
	int minlvl;
	std::vector<int> spawnchances;
	std::vector<int> etypes;
};
struct TexListMem {
	SDL_Texture* current;
	TexListMem *next;
	std::string name;
};
typedef TexListMem* texp;


class Game {
private:
	Uint64 LAST = 0;
	Uint64 NOW = SDL_GetPerformanceCounter();

public:
	double getDelta() {
		double delta = 0;
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		delta = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
		delta = delta * 0.001;
		return delta;
	}
	//Button functions
	void attackButton(Entity* e, Entity* e2, SDL_Texture* player4tex, Mix_Chunk* buttonsound);

	//Enemy spawn functions
	void spawnE1(std::vector<Entity>& enemies, float *sx, float *sy, SDL_Texture* enemtex);
	void spawnE2(std::vector<Entity>& enemies, float *sx, float *sy, SDL_Texture* enemtex);
	void spawnE3(std::vector<Entity>& enemies, float *sx, float *sy, SDL_Texture* enemtex);
	void spawnE4(std::vector<Entity>& enemies, float *sx, float *sy, SDL_Texture* enemtex);
	void spawnE5(std::vector<Entity>& enemies, float *sx, float *sy, SDL_Texture* enemtex);
	
	//Saving
	void saveGame(Entity* player, int *crack, int *xpreq);
	void loadGame(Entity* player, int* crack, int *xpreq);

	//Texture linked list
	void insertTex(TexListMem* &tex,  SDL_Texture* current, std::string name);
	SDL_Texture* findTex(texp head, std::string name);

	//Text functions
	void drawText(SDL_Renderer* rend, texp head, std::string text, int x, int y, int w, int h);
	void CreateText(SDL_Renderer* rend, TTF_Font* font, std::string text, SDL_Color color, TexListMem*& head);
	void createDynamicText(SDL_Renderer* rend, TTF_Font* font, SDL_Color color, TexListMem*& head, texp& end);
	void editText(SDL_Renderer* rend, TTF_Font* font, std::string text, SDL_Color color, texp& head);
	void drawTempText(SDL_Renderer* rend, TTF_Font* font, std::string text, SDL_Color color, int x, int y, int w, int h);

	//Utility
	void createCombatButtons(std::vector<Button>& buttons, TexListMem*& head, SDL_Renderer* rend, TTF_Font* font, SDL_Color yellow);
	void createMenuButtons(std::vector<Button>& buttons, TexListMem*& head, SDL_Renderer* rend, TTF_Font* font, SDL_Color yellow);
	void createUpgradeButtons(std::vector<Button>& buttons, TexListMem*& head, SDL_Renderer* rend, TTF_Font* font, SDL_Color yellow);
	void createSpawners(std::vector<ESpawner>& espawners);
	void createEnemyInstance(std::vector<Entity>& enemies, std::vector<ESpawner>& espawners, Entity* p, texp head);

	//Update functions
	void updateEnemies(std::vector<FLText>& explosions, std::vector<Entity>& enemies, std::vector<FLText>& damagetext, int* crack, bool playerturn, Entity* player, SDL_Renderer* rend, SDL_Texture* healtex, Mix_Chunk* edeath);
	void updateExplosions(std::vector<FLText>& explosions, double delta, texp head, SDL_Renderer* rend);
	void updateDamage(std::vector<FLText>& damagetext, double delta, SDL_Renderer* rend, TTF_Font* font, texp head);
	void updatemButtons(std::vector<Button>& buttons, bool* combat, bool* exitf, double* bcool, SDL_Renderer* rend, texp font, Entity* player);
	void updateupButtons(std::vector<Button>& buttons, SDL_Renderer* rend, texp font, double* bcool, Entity* player, bool* levelm, bool* change);
	void updateButtons(std::vector<Button>& buttons, std::vector<FLText>& damagetext, Entity* player, Entity* targenemy, SDL_Renderer* rend, texp font, int esize, double* bcool, int* crack, bool* playerturn, bool* levelm, texp head, Mix_Chunk* buttonsound, Mix_Chunk* cracksound);
};
