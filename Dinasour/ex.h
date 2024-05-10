#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 400;
const int GROUND_HEIGHT = 50;
const int TREX_WIDTH = 44;
const int TREX_HEIGHT = 47;
const int CACTUS_WIDTH = 20;
const int CACTUS_HEIGHT = 50;
const int CACTUS_GAP = 200;
const int INITIAL_SPEED = 5;
const std::string WINDOW_TITLE = "T-Rex Game";

// Game objects
struct Trex {
    SDL_Texture* texture;
    SDL_Rect position;
    bool isJumping;
    int jumpHeight;
    int jumpSpeed;

    Trex() : texture(nullptr), isJumping(false), jumpHeight(0), jumpSpeed(0) {}
};

struct Cactus {
    SDL_Texture* texture;
    SDL_Rect position;
};

// Helper functions
SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& file) {
    SDL_Surface* surface = IMG_Load(file.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void RenderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y) {
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    SDL_QueryTexture(texture, nullptr, nullptr, &destRect.w, &destRect.h);
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}

bool CheckCollision(const SDL_Rect& rect1, const SDL_Rect& rect2) {
    return rect1.x + rect1.w >= rect2.x && rect2.x + rect2.w >= rect1.x &&
           rect1.y + rect1.h >= rect2.y && rect2.y + rect2.h >= rect1.y;
}

// Game initialization
bool Initialize(SDL_Window*& window, SDL_Renderer*& renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

// Game cleanup
void Cleanup(SDL_Window* window, SDL_Renderer* renderer, Trex& trex, Cactus& cactus) {
    SDL_DestroyTexture(trex.texture);
    SDL_DestroyTexture(cactus.texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

// Game loop
void RunGame() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    if (!Initialize(window, renderer)) {
        return;
    }

    // Load textures
    Trex trex;
    trex.texture = LoadTexture(renderer, "trex.png");
    Cactus cactus;
    cactus.texture = LoadTexture(renderer, "cactus.png");

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

            // Render score
            SDL_Color textColor = {0, 0, 0, 255};
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), textColor);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_Rect textRect = {SCREEN_WIDTH - 50, 10, textSurface->w, textSurface->h};
            SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

            // Present the renderer
            SDL_RenderPresent(renderer);

            // Delay the game loop
            SDL_Delay(10);
        }
    }

    // Cleanup
    Cleanup(window, renderer, trex, cactus);
}

int main(int argc, char* argv[]) {
    RunGame();
    return 0;
}