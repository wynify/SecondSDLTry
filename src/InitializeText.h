#ifndef INITIALIZE_TEXT_H
#define INITIALIZE_TEXT_H

#include <SDL2/SDL_ttf.h>

//Functions for Initialie TTF
int InitializeTTF(const char *font_path, int font_size);
void CloseTTF();

//Functions for print text on screen
void RenderText(SDL_Renderer *renderer,TTF_Font* font, const char *text, int x, int y, SDL_Color color);

extern TTF_Font *font;

#endif