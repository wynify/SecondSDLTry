#include "Game.h"
#include "InitializeText.h"

#define MAX_LINES 10
#define MAX_LINE_LENGTH 256 
#define CURSOR_BLINK_INTERVAL 500  // Cursor blink interval in milliseconds


int Initialize(int width, int height){
     if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Program",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          width,
                                          height,
                                          SDL_WINDOW_SHOWN);

    if (!window) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

//Initialize TTF
    if(InitializeTTF("./dos2000.ttf", 24) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    //Colors for text
    SDL_Color White = {255, 255, 255, 255};
    SDL_Color Red = {255, 0, 0, 255};

    // Cursor handling variables
    SDL_bool ShowCursore = SDL_TRUE;
    Uint32 LastCursoreToggle = SDL_GetTicks();

    //Input text
    SDL_StartTextInput();
    char lines[MAX_LINES][MAX_LINE_LENGTH];  // Array of strings for lines
    int line_count = 0;  // Current number of lines
    char text[MAX_LINE_LENGTH] = "";

///////////////////////////////////////////////////
//////////////////// MAIN CYCLE////////////////////
///////////////////////////////////////////////////
    SDL_bool running = SDL_TRUE;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = SDL_FALSE;
            }
            else if(event.type == SDL_TEXTINPUT){
                strcat(text, event.text.text);
            }
            else if(event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    if (strlen(text) > 0) {
                        // Remove the last character from text
                        text[strlen(text) - 1] = '\0';
                    } else if (line_count > 0) {
                        // Move the previous line's text into text and adjust line_count
                        line_count--;
                        strncat(text, lines[line_count], MAX_LINE_LENGTH - strlen(text) - 1);
                        lines[line_count][0] = '\0';  // Clear the previous line
                    }
                }
                
                else if (event.key.keysym.sym == SDLK_RETURN) {  // Handle Enter key for line break
                    if (line_count < MAX_LINES) {
                        strncpy(lines[line_count], text, MAX_LINE_LENGTH);
                        lines[line_count][MAX_LINE_LENGTH - 1] = '\0';  // Ensure null-termination
                        line_count++;
                        text[0] = '\0';  // Clear current input text
                    }
                }
            }
        }

    //Blink cursore
        if(SDL_GetTicks() - LastCursoreToggle > CURSOR_BLINK_INTERVAL){
            ShowCursore = !ShowCursore;
            LastCursoreToggle = SDL_GetTicks;
     }

    //Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

    //Render text RenderText(renderer, font, text, 50, 50, White);  

    // Render the lines to the screen
        int y = 50;  // Start position for rendering text
        for (int i = 0; i < line_count; i++) {
            RenderText(renderer, font, lines[i], 50, y, White);
            y += 30;  // Move down for the next line (adjust as needed)
        }
        
        // Render the current input text
        RenderText(renderer, font, text, 50, y, White);  // Show the current input text below the lines
          

        // Show what we've drawn
        SDL_RenderPresent(renderer);
    }
///////////////////////////////////////////////////////
/////////////////END OF MAIN CYCLE/////////////////////
//////////////////////////////////////////////////////

    SDL_StopTextInput();
    CloseTTF(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}