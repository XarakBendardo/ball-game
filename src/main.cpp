#include <SFML/Graphics.hpp>
#include "include/Board.h"
#include "include/Ball.h"
#include "include/Game.h"


int main()
{
    auto& game = engine::Game::getInstance();
    game.run();
    engine::Game::cleanup();
}