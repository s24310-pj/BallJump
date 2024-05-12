#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

GameObject *player;
GameObject *rock;

Map *map;

SDL_Renderer *Game::renderer = nullptr;

Game::Game() = default;

Game::~Game() = default;

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {

    int flags = 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        }

        isRunning = true;
    }

    player = new GameObject(R"(D:\programowanie\SGD\BallJump\assets\ball.png)", 0, 0);
    rock = new GameObject(R"(D:\programowanie\SGD\BallJump\assets\rock.png)", 50, 50);
    map = new Map();
}

void Game::handleEvents() {

    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }

}

void Game::update() {

    player->Update();
    rock->Update();
}

void Game::render() {
    SDL_RenderClear(renderer);
    map->DrawMap();
    player->Render();
    rock->Render();

    SDL_RenderPresent(renderer);
}

void Game::clean() {

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "BallJump cleaned" << std::endl;

}