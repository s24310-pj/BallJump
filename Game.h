#include "SDL.h"
#include "SDL_image.h"
#include "iostream"
#ifndef GAME_GAME_H
#define GAME_GAME_H


class Game {

public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() {return isRunning;}

    static SDL_Renderer *renderer;

private:
    int counter = 0;
    bool isRunning{};
    SDL_Window *window{};

};


#endif //GAME_GAME_H
