#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Board.h"

#ifndef GAME_H
#define GAME_H

namespace engine
{
class Game
{
    public:
        static Game& getInstance();
        static void cleanup();

        void run();

    private:
        static Game* instance;

        sf::RenderWindow* window;
        Ball ball;
        Board leftBoard, rightBoard;

        Game();
        ~Game();
        Game(const Game& other) = delete;
        Game& operator=(const Game& other) = delete;
};
} // namespace engine

#endif // GAME_H