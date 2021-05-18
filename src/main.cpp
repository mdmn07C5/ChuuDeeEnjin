#include "Game.h"
#include "SDL.h"
#include "Globals.h"

Game *game{nullptr};

int main(int argc, char *argv[])
{

    uint32_t frameStart{0};
    int frameTime{0};

    game = new Game();
    game->Init("Maek Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
               globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, false);

    while (game->Running())
    {
        frameStart = SDL_GetTicks();

        game->HandleEvents();
        game->Update();
        game->Render();

        frameTime = SDL_GetTicks() - frameStart;
        if (globals::FRAME_DELAY > frameTime)
        {
            SDL_Delay(globals::FRAME_DELAY - frameTime);
        }
    }

    game->Clean();
    return 0;
}