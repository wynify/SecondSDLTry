//FILE FOR PRINT TEXT IN NATIVE FORM

#include "InitializeText.h"
#include <stdio.h>

TTF_Font *font = NULL;

int InitializeTTF(const char *font_path, int font_size){
    if(TTF_Init() == -1){
        printf("Can't initialize TTF: %s\n", SDL_GetError());
        return -1;
    }

    font = TTF_OpenFont(font_path, font_size);
    if(!font){
        printf("Error loading font: %s\n", SDL_GetError());
        return -1;
    }

    return 0; //Success
}

void CloseTTF(){
    if(font){
        TTF_CloseFont(font);
        font = NULL;
    }
    TTF_Quit();
}

void RenderText(SDL_Renderer *renderer, TTF_Font* font, const char *text, int x, int y, SDL_Color color){
    if (text == NULL || strlen(text) == 0) {
        return;  // Don't render empty text
    }
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    if(!surface){
        printf("Error creating font surface: %s\n", TTF_GetError());
        exit(-1);
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(!texture){
        printf("Error creating text texture: %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_Rect Dst_Rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &Dst_Rect);

    SDL_DestroyTexture(texture);
}
