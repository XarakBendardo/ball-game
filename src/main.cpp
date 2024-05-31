#include "include/Board.h"
#include "include/Ball.h"
#include "include/Game.h"
#include "include/SoundManager.h"


int main()
{
    engine::Game::init();
    engine::Game::getInstance().run();
    engine::Game::cleanup();
}