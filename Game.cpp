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
SDL_Rect Game::camera = {0, 0, 800, 480};


bool Game::isRunning = false;

auto &player(manager.addEntity());
auto &rock1(manager.addEntity());
auto &rock2(manager.addEntity());
auto &rock3(manager.addEntity());
auto &coin1(manager.addEntity());
auto &coin2(manager.addEntity());
auto &coin3(manager.addEntity());
auto &coin4(manager.addEntity());
auto &flag(manager.addEntity());
auto &counter(manager.addEntity());


Game::Game() = default;

Game::~Game() = default;


void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {

    int flags = 0;


    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                             "Instrukcja",
                             "Witam w grze BallJump, omijaj kamienie oraz wodę, zbieraj monety i doskocz do flagi! \n"
                             "Używaj w - aby skoczyć, a - aby poruszyć się w lewo i d - aby poruszyć się w prawo",
                             window);

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        isRunning = true;
    }

    map = new Map("../assets/tileset.png", 1, 32);

    map->LoadMap("../assets/map2.map", 40, 15);

    player.addComponent<TransformComponent>(64, 350, true);
    player.addComponent<SpriteComponent>("../assets/ball.png");
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);

    rock1.addComponent<TransformComponent>(352, 352, 32, 32, 1);
    rock1.addComponent<SpriteComponent>("../assets/rock.png");
    rock1.addComponent<ColliderComponent>("rock");
    rock1.addGroup(groupDestroyers);

    rock2.addComponent<TransformComponent>(576, 352, 32, 32, 1);
    rock2.addComponent<SpriteComponent>("../assets/rock.png");
    rock2.addComponent<ColliderComponent>("rock");
    rock2.addGroup(groupDestroyers);

    rock3.addComponent<TransformComponent>(832, 352, 32, 32, 1);
    rock3.addComponent<SpriteComponent>("../assets/rock.png");
    rock3.addComponent<ColliderComponent>("rock");
    rock3.addGroup(groupDestroyers);

    coin1.addComponent<TransformComponent>(500, 320, 32, 32, 1);
    coin1.addComponent<SpriteComponent>("../assets/coin.png", true);
    coin1.addComponent<ColliderComponent>("coin");
    coin1.addGroup(groupCoins);

    coin2.addComponent<TransformComponent>(675, 320, 32, 32, 1);
    coin2.addComponent<SpriteComponent>("../assets/coin.png", true);
    coin2.addComponent<ColliderComponent>("coin");
    coin2.addGroup(groupCoins);

    coin3.addComponent<TransformComponent>(940, 320, 32, 32, 1);
    coin3.addComponent<SpriteComponent>("../assets/coin.png", true);
    coin3.addComponent<ColliderComponent>("coin");
    coin3.addGroup(groupCoins);

    coin4.addComponent<TransformComponent>(1120, 320, 32, 32, 1);
    coin4.addComponent<SpriteComponent>("../assets/coin.png", true);
    coin4.addComponent<ColliderComponent>("coin");
    coin4.addGroup(groupCoins);

    flag.addComponent<TransformComponent>(1212, 352, 32, 32, 1);
    flag.addComponent<SpriteComponent>("../assets/flag.png", true);
    flag.addComponent<ColliderComponent>("flag");
    flag.addGroup(groupFlags);

    counter.addComponent<TransformComponent>(1212, 50, 32, 32, 1);
    counter.addComponent<SpriteComponent>("../assets/0.png");
    counter.addComponent<ColliderComponent>("counter");
    counter.addGroup(groupMap);



}

auto &tiles(manager.getGroup(Game::groupMap));
auto &players(manager.getGroup(Game::groupPlayers));
auto &colliders(manager.getGroup(Game::groupColliders));
auto &destroyers(manager.getGroup(Game::groupDestroyers));
auto &coins(manager.getGroup(Game::groupCoins));
auto &flags(manager.getGroup(Game::groupFlags));


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

    manager.refresh();
    manager.update();



    for (auto &c: colliders) {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCollider)) {
            if (player.getComponent<TransformComponent>().velocity.y > 0) {
                player.getComponent<TransformComponent>().velocity.y = 0;
                player.getComponent<TransformComponent>().position.y = cCol.y - playerCollider.h;
            }
        } else {

        }
    }

    for (auto &d: destroyers) {
        SDL_Rect dCol = d->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(dCol, playerCollider)) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                                     "Porażka",
                                     "Piłka została przebita, zacznij jeszcze raz",
                                     window);
            isRunning = false;
            player.getComponent<TransformComponent>().position.x = 64;
            player.getComponent<TransformComponent>().position.y = 350;
            isRunning = true;
        }
    }

    for (auto &money: coins) {
        SDL_Rect coinCol = money->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(coinCol, playerCollider)) {
            money->destroy();
            points++;
            switch ((points)) {
                case 0:
                    counter.getComponent<SpriteComponent>().setTex("../assets/0.png");
                    break;
                case 1:
                    counter.getComponent<SpriteComponent>().setTex("../assets/1.png");
                    break;
                case 2:
                    counter.getComponent<SpriteComponent>().setTex("../assets/2.png");
                    break;
                case 3:
                    counter.getComponent<SpriteComponent>().setTex("../assets/3.png");
                    break;
                case 4:
                    counter.getComponent<SpriteComponent>().setTex("../assets/4.png");
                    break;
            }
            std::cout << points << std::endl;
        }
    }

    for (auto &f: flags) {
        SDL_Rect fCol = f->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(fCol, playerCollider)) {
            player.getComponent<SpriteComponent>().setTex("../assets/ball_winner.png");
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                                     "Gratulacje!!!",
                                     "Doszedłeś do końca poziomu, jesteś giga koks !!!",
                                     window);
            flag.destroy();
            isRunning = false;
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

    for (auto &d: destroyers) {
        d->draw();
    }

    for (auto &coin: coins) {
        coin->draw();
    }

    for (auto &f: flags) {
        f->draw();
    }


    SDL_RenderPresent(renderer);
}

void Game::clean() {

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    TTF_Quit();
    std::cout << "BallJump closed properly" << std::endl;
}
