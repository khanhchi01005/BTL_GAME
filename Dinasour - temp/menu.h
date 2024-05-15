#ifndef MENU_H
#define MENU_H
#include "defs.h"
#include "graphics.h"


void drawBoundingBox(SDL_Renderer* renderer, const SDL_Rect& rect) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set the color to red
    SDL_RenderDrawRect(renderer, &rect); // Draw the rectangle
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void loadMenu(Graphics graphics){
    Graphics graphics;
    graphics.init();
    bool isPlaying = false;
    bool quit = false;
    SDL_Event e;



    SDL_Texture* Menu = graphics.loadTexture("images/try.jpg");
    graphics.prepareScene(Menu);

    TTF_Font* font = graphics.loadFont("fonts/purisa.ttf", 35);
    SDL_Color color = {0, 0, 0, 255};

// Welcome to my game
    SDL_Texture* WELCOME = graphics.renderText("WELCOME TO MY T-REX GAME", font, color);
    graphics.renderTexture(WELCOME, 80, 150);

// New Game
    SDL_Texture* newGame = graphics.renderText("New Game", font, color);
    graphics.renderTexture(newGame, 270, 250);
    SDL_Rect newGameBox = {250, 250, 250, 50};
    drawBoundingBox(graphics.getRenderer(), newGameBox);

// Exit
    SDL_Texture* Exit = graphics.renderText("Exit", font, color);
    graphics.renderTexture(Exit, 330, 330);
    SDL_Rect exitBox = {250, 330, 250, 50};
    drawBoundingBox(graphics.getRenderer(), exitBox);

// Instruction
    SDL_Texture* Help = graphics.renderText("Help", font, color);
    graphics.renderTexture(Help, 330, 410);
    SDL_Rect helpBox = {250, 410, 250, 50};
    drawBoundingBox(graphics.getRenderer(), helpBox);

    graphics.presentScene();

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
// Vao choi game
                if (mouseX >= newGameBox.x && mouseX < newGameBox.x + newGameBox.w &&
                    mouseY >= newGameBox.y && mouseY < newGameBox.y + newGameBox.h) {
                    isPlaying = true;
                    quit=true;
                }
//Thoat game ra
                if (mouseX >= exitBox.x && mouseX < exitBox.x + exitBox.w &&
                    mouseY >= exitBox.y && mouseY < exitBox.y + exitBox.h) {

                    quit=true;
                }


            }
        }
    }
}
#endif
