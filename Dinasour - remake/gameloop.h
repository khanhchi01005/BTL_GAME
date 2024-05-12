#ifndef _GAMELOOP__H
#define _GAMELOOP__H

#include "defs.h"
#include "graphics1.h"

// Game loop
void RunGame() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    if (!Initialize(window, renderer)) {
        return;
    }

    // Load textures
    Trex trex;
    trex.texture = LoadTexture(renderer, "images/bird.png");
    Cactus cactus;
    cactus.texture = LoadTexture(renderer, "images/cactus1.png");

    // Set initial positions
    trex.position.x = SCREEN_WIDTH / 4;
    trex.position.y = SCREEN_HEIGHT - GROUND_HEIGHT - TREX_HEIGHT;
    cactus.position.x = SCREEN_WIDTH;
    cactus.position.y = SCREEN_HEIGHT - GROUND_HEIGHT - CACTUS_HEIGHT;

    // Game variables
    bool quit = false;
    bool isGameOver = false;
    int score = 0;
    int gameSpeed = INITIAL_SPEED;

    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE && !trex.isJumping) {
                    trex.isJumping = true;
                    trex.jumpHeight = 100;
                    trex.jumpSpeed = 10;
                }
            }
        }

        if (!isGameOver) {
            if (!isGameOver) {
                // Update trex
                if (trex.isJumping) {
                    trex.position.y -= trex.jumpSpeed;
                    trex.jumpSpeed -= 1;
                    if (trex.position.y >= SCREEN_HEIGHT - GROUND_HEIGHT - TREX_HEIGHT) {
                        trex.position.y = SCREEN_HEIGHT - GROUND_HEIGHT - TREX_HEIGHT;
                        trex.isJumping = false;
                    }
                }

                // Update cactus
                cactus.position.x -= gameSpeed;

                // Check for collision
                if (CheckCollision(trex.position, cactus.position)) {
                    isGameOver = true;
                }

                // Check if cactus passed the trex
                if (cactus.position.x + CACTUS_WIDTH < trex.position.x) {
                    score++;
                    if (score % 10 == 0) {
                        gameSpeed++;
                    }
                    cactus.position.x = SCREEN_WIDTH;
                    cactus.position.y = SCREEN_HEIGHT - GROUND_HEIGHT - CACTUS_HEIGHT;
                }
            }

            // Clear the renderer
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            // Render ground
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_Rect groundRect = {0, SCREEN_HEIGHT - GROUND_HEIGHT, SCREEN_WIDTH, GROUND_HEIGHT};
            SDL_RenderFillRect(renderer, &groundRect);

            // Render trex
            RenderTexture(renderer, trex.texture, trex.position.x, trex.position.y);

            // Render cactus
            RenderTexture(renderer, cactus.texture, cactus.position.x, cactus.position.y);

            // Present the renderer
            SDL_RenderPresent(renderer);

            // Delay the game loop
            SDL_Delay(10);
        }
    }

    // Cleanup
    Cleanup(window, renderer,trex, cactus);
}
#endif
