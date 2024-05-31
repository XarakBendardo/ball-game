#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "include/Board.h"
#include "include/Ball.h"
#include "include/Game.h"
#include "include/SoundManager.h"


int main()
{
    engine::Game::init();
    // engine::SoundManager::playSound(engine::SoundManager::Sound::optionChoose);
    engine::Game::getInstance().run();
    engine::Game::cleanup();
}