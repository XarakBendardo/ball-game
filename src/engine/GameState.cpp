#include "../include/GameState.h"

namespace engine
{

GameStateAbstract::GameStateAbstract(sf::RenderWindow& renderWindow) : window(renderWindow) {}

GameStateRunning::GameStateRunning(sf::RenderWindow& renderWindow) : GameStateAbstract(renderWindow) {}

void GameStateRunning::reactToEvent(const sf::Event& event)
{
    (void) event;
}

void GameStateRunning::update()
{
    
}

void GameStateRunning::draw() const
{
    
}

} // namespace engine
