#include <SDL.h>
#include "Game.h"

Game *game = nullptr;

int main(int argc, char *args[]) {

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();

    game->init("BallJump", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

    while (game->running()) {

        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }

    }

    game->clean();

    return 0;



    //    //Start SDL
//    SDL_Init( SDL_INIT_EVERYTHING );
//    auto window = SDL_CreateWindow( "Gierka", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN );
//    SDL_Delay(5000);
//    SDL_DestroyWindow( window );
//    //Quit SDL
//    SDL_Quit();
//    return 0;
}