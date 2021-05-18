#ifndef _GAME_H_
#define _GAME_H_
/**
 * Game class - The engine for the game.
 * This class will handle the game loop which goes
 * Take input -> update everything based off of that input 
 * -> draw eveything on screen -> repeat
 */

#include "SDL.h"
#include <vector>

// Forward Declarations
struct SDL_Window;
struct SDL_Renderer;
class ColliderComponent;


class Game
{
    public:
        Game();
        ~Game();
        
        /**
         * Initializes window and renderer
         * @param title the window's titlle
         * @param xPos where the left most edge of the window will be 
         * @param yPos where the top most edge of the window will be 
         * @param width the window width
         * @param hegiht the window height
         * @param fullScreen if set to true, will create a fullscreen window
         */
        void Init(const char* title, int xPos, int yPos, int width, int height, bool fullScreen);

        /**
         * Handle user input events
         */
        void HandleEvents();

        /**
         * Perform necessary state updates for all game objects
         */
        void Update();

        /**
         * Draw everything on screen using **** algorithm
         */
        void Render();

        /**
         * Free up memory taken by window and renderer. Quits SDL
         */
        void Clean();

        /**
         * @return isRunning_ 
         */
        bool Running();

        static void AddTile(int srcX, int srcY, int xPos, int yPos);

        static bool isRunning_;
        static SDL_Renderer* renderer_;
        static SDL_Event event;
        static std::vector<ColliderComponent*> colliders;
        static SDL_Rect camera;
        
    private:
        
        SDL_Window* window_;
};

#endif