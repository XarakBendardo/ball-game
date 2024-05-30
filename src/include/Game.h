#include <SFML/Graphics.hpp>
#include <stack>
#include "../include/GameState.h"

#ifndef GAME_H
#define GAME_H

namespace engine
{
class Game
{
    public:
        static unsigned int FPSLimit;

        static Game& getInstance();
        static void cleanup();
        static void init();
        void run();
    private:
        static Game* instance;

        GameStateAbstract* currentState;
        std::stack<GameStateAbstract*> stateStack;
        sf::RenderWindow* window;

        Game();
        ~Game();
        Game(const Game& other) = delete;
        Game& operator=(const Game& other) = delete;

        void changeState(GameStateAbstract* newState);
};
} // namespace engine

#endif // GAME_H