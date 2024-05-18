#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <vector>

class ColliderComponent;

class Game {

public:
    Game();

    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();

    void update();

    void render();

    void clean();

    bool running() { return isRunning; }



    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool isRunning;
    static SDL_Rect camera;

    enum groupLabels : std::size_t {
        groupMap,
        groupPlayers,
        groupColliders,
        groupDestroyers,
        groupCoins,
        groupFlags
    };

private:
    SDL_Window *window{};
    int points = 0;

};


#endif //GAME_GAME_H
