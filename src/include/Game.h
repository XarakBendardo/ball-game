#include <SFML/Graphics.hpp>
#include "../include/GameState.h"

#ifndef GAME_H
#define GAME_H

namespace engine
{
class Game
{
    public:
        static float boardVelocity;
        static unsigned int FPSLimit;

        static Game& getInstance();
        static void cleanup();

        void run();
    private:
        enum BoardsMovement {up, down, none};
    
        static Game* instance;

        GameStateAbstract* currentState;
        sf::RenderWindow* window;

        Game();
        ~Game();
        Game(const Game& other) = delete;
        Game& operator=(const Game& other) = delete;
};
} // namespace engine

#endif // GAME_H