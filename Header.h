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
//Small city map with some multi level buildings, based on tilemap !
//able to rip copper wire and piping out of walls $
//real time top down movement !
//turn based jrpg combat %
//can get high on shit %
// small skill tree so you can spec into speed, strength, or buffs from crack
//addicted to crack, but can become addicted to other drugs %
//rob dealers and gas stations, add banks if time %
//can ride shopping cart around(if time) %
//NPC list
//Static npcs: drug dealers, gas station attendants, mcdonalds cashiers, and bank tellers %
//Only static until attacked and then enter into battle with player %
//If time add this
//Non-static npcs: crack addicts, meth addicts, gang members, police %
//follow set routines unless provoked or spot player in which case they attack them %

enum ITYPE {EMPTY, STICK, RPIPE, CPIPE, CWIRE, HOODIE, SWEATP, JEANS, TSHIRT, WIFEB};
extern const Uint8* keys;
struct Entity {
	float x;
	float y;
	int w;
	int h;
	int health;
	int level;
	int atkdmg;
	std::vector<ITYPE> inventory;
	//index 0 is hands, index 1 is shoes, index 2 is pants, index 3 is shirt, index 4 is back, index 5 is hands, index 6 is head
	ITYPE equipped;
	int type;
	int index;
	int xp;
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
};
class Button {
public:
	int x;
	int y;
	int w;
	int h;
	std::string text;
	void (*click)(Entity*, Entity*);
	//std::function<void(Entity*, Entity*)> click;
};


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
	void drawText(SDL_Renderer* rend, TTF_Font* font, std::string text, SDL_Color color, int x, int y, int w, int h);
	void generateMap(std::vector<Entity>& tiles, Entity* p);
	void playerUpdate(Entity* p, float delta, std::vector<Entity>& tiles);
	void createEnemyInstance(std::vector<Entity>& enemies, Entity* p);
};
