#include <SFML/Graphics.hpp>
#include "include/Board.h"
#include "include/Ball.h"
#include "include/Game.h"


int main()
{
    engine::Game::init();
    engine::Game::getInstance().run();
    engine::Game::cleanup();
}