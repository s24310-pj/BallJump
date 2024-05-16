#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map *map;
Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, 840, 640};


bool Game::isRunning = false;

auto &player(manager.addEntity());


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

    map = new Map("../assets/terrain_ss.png", 1, 32);

    map->LoadMap("../assets/map.map", 25, 20);

    player.addComponent<TransformComponent>(1);
    player.addComponent<SpriteComponent>("../assets/ball.png");
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);

}

auto &tiles(manager.getGroup(Game::groupMap));
auto &players(manager.getGroup(Game::groupPlayers));
auto &colliders(manager.getGroup(Game::groupColliders));

void Game::handleEvents() {

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

    SDL_Rect playerCollider = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPosition = player.getComponent<TransformComponent>().position;

    manager.refresh();
    manager.update();

    for (auto &c: colliders) {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCollider)) {
            player.getComponent<TransformComponent>().position = playerPosition;
        }
    }


    camera.x = player.getComponent<TransformComponent>().position.x - 400;
    camera.y = player.getComponent<TransformComponent>().position.y - 320;

    if (camera.x < 0) {
        camera.x = 0;
    }
    if (camera.y < 0) {
        camera.y = 0;
    }
    if (camera.x > camera.w) {
        camera.x = camera.w;
    }
    if (camera.y > camera.h) {
        camera.y = camera.h;
    }

}


void Game::render() {
    SDL_RenderClear(renderer);

    for (auto &t: tiles) {
        t->draw();
    }

    for (auto &c: colliders) {
        c->draw();
    }

    for (auto &p: players) {
        p->draw();
    }

    SDL_RenderPresent(renderer);
}

void Game::clean() {

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "BallJump cleaned" << std::endl;
}

