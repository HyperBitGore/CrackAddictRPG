#include "Header.h"


void Game::CreateText(SDL_Renderer* rend, TTF_Font* font, std::string text, SDL_Color color, TexListMem*& head) {
	SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	insertTex(head, texture, text);
}

void Game::drawText(SDL_Renderer* rend, texp head, std::string text, int x, int y, int w, int h) {
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderCopy(rend, findTex(head, text), NULL, &rect);
}
void Game::editText(SDL_Renderer* rend, TTF_Font* font, std::string text, SDL_Color color, texp& head) {
	//std::cout << head->current << std::endl;
	SDL_DestroyTexture(head->current);
	SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surf);
	head->current = tex;
	head->name = text;
	//std::cout << head->current << std::endl;
	SDL_FreeSurface(surf);
}

void Game::createDynamicText(SDL_Renderer* rend, TTF_Font* font, SDL_Color color, TexListMem*& head, texp& end) {
	end = head;
	CreateText(rend, font, "Health", color, head);
	CreateText(rend, font, "Crack", color, head);
	CreateText(rend, font, "xpreq", color, head);
	CreateText(rend, font, "level", color, head);
	CreateText(rend, font, "atkdmg", color, head);
	CreateText(rend, font, "xp", color, head);
}


void Game::drawTempText(SDL_Renderer* rend, TTF_Font* font, std::string text, SDL_Color color, int x, int y, int w, int h) {
	SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surf);
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderCopy(rend, texture, NULL, &rect);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);
	
}