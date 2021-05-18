#include "Game.h"
#include "Tilemap.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include "Collision.h"
#include <iostream>

Tilemap *map;
Manager manager;

auto &newPlayer(manager.AddEntity());
auto &enemy(manager.AddEntity());

const char* mpaFile{"art/maps/terrain_ss.png"};

SDL_Event Game::event{};
SDL_Renderer *Game::renderer_{nullptr};
SDL_Rect Game::camera{0, 0, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT};
std::vector<ColliderComponent*> Game::colliders;

enum groupLabels : std::size_t
{
    groupMap,
    groupPlayer,
    groupEnemies,
    groupColliders
};


auto &tiles(manager.GetGroup(groupMap));
auto &players(manager.GetGroup(groupPlayer));
auto &enemies(manager.GetGroup(groupEnemies));

bool Game::isRunning_{false};

// temp
Game::Game()
{
    std::cout << "Make Gaem." << std::endl;
}

Game::~Game()
{
    std::cout << "DELET" << std::endl;
}

void Game::Init(const char *title, int xPos, int yPos, int width, int height, bool fullScreen)
{
    int flags = 0;
    if (fullScreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "SDL Subsystems Initialized..." << std::endl;

        window_ = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
        if (!window_)
        {
            std::cout << "Window creation failed." << SDL_GetError() << std::endl;
        }

        renderer_ = SDL_CreateRenderer(window_, -1, 0);
        if (renderer_)
        {
            SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
            std::cout << "Renderer creation success." << std::endl;
        }

        isRunning_ = true;
    }
    else
    {
        std::cout << "Window and Renderer creation failed." << std::endl;
        isRunning_ = false;
    }

    map = new Tilemap();

    Tilemap::LoadTileMap("art/maps/map.map", 25, 20);

    newPlayer.AddComponent<TransformComponent>(2);
    newPlayer.AddComponent<SpriteComponent>("art/sprites/MyChar.png", true);
    newPlayer.AddComponent<KeyboardController>();
    newPlayer.AddComponent<ColliderComponent>("player");
    newPlayer.AddGroup(groupPlayer);

    // enemy.AddComponent<TransformComponent>(368, 368, 64, 64, 2);
    // enemy.AddComponent<SpriteComponent>("art/sprites/SpookyQuote.png");
    // enemy.AddComponent<ColliderComponent>("enemy");
    // enemy.AddGroup(groupEnemies);

    std::cout << "There are " << colliders.size() << " in the colliders vector\n";
}

void Game::HandleEvents()
{

    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning_ = false;
        break;
    default:
        break;
    }
}

void Game::Update()
{
    manager.Update();
    newPlayer.Update();

#pragma region scrolling tiles while player stays in center
//     Vector2D playerVelocity = newPlayer.GetComponent<TransformComponent>().velocity_;
//     int playerSpeed = newPlayer.GetComponent<TransformComponent>().speed_;

//     for (auto t : tiles)
//     {
//         t->GetComponent<TileComponent>().destRect_.x += -(playerVelocity.x_ * playerSpeed);
//         t->GetComponent<TileComponent>().destRect_.y += -(playerVelocity.y_ * playerSpeed);
//     }
#pragma endregion

    camera.x = newPlayer.GetComponent<TransformComponent>().position_.x_ - globals::SCREEN_WIDTH/2;
    camera.y = newPlayer.GetComponent<TransformComponent>().position_.y_ - globals::SCREEN_HEIGHT/2;

    // bounds checking
    if (camera.x < 0) camera.x = 0;
    if (camera.y < 0) camera.y = 0;
    if (camera.x > camera.w) camera.x = camera.w;
    if (camera.y > camera.h) camera.y = camera.h;
}



void Game::Render()
{
    SDL_RenderClear(renderer_);
    manager.Draw();
    for (auto &t : tiles)
    {
        t->Draw();
    }

    for (auto &e : enemies)
    {
        e->Draw();
    }

    for (auto &p : players)
    {
        p->Draw();
    }
    SDL_RenderPresent(renderer_);
}

void Game::Clean()
{
    SDL_DestroyWindow(window_);
    SDL_DestroyRenderer(renderer_);
    SDL_Quit();
    std::cout << "Game Cleaned." << std::endl;
}

bool Game::Running()
{
    return isRunning_;
}

void Game::AddTile(int srcX, int srcY, int xPos, int yPos)
{
    auto& tile(manager.AddEntity());
    tile.AddComponent<TileComponent>(srcX, srcY, xPos, yPos, mpaFile);
    tile.AddGroup(groupMap);
}