#include "../include/GameState.h"

namespace engine
{

GameStateAbstract::GameStateAbstract(sf::RenderWindow& renderWindow) : window(renderWindow) {}

GameStateRunning::GameStateRunning(sf::RenderWindow& renderWindow) : GameStateAbstract(renderWindow) {}

void GameStateRunning::reactToEvent(const sf::Event& event)
{
    if (event.type == sf::Event::Closed)
        this->window.close();
    else if(event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Escape:
            this->window.close();
            break;

        case sf::Keyboard::Up:
            this->currentMovement = BoardsMovement::up;
            break;

        case sf::Keyboard::Down:
            this->currentMovement = BoardsMovement::down;
            break;
        
        default:
            break;
        }
    }
    else if(event.type == sf::Event::KeyReleased)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Up:
        case sf::Keyboard::Down:
            this->currentMovement = BoardsMovement::none;
            break;
        
        default:
            break;
        }
    }
}

void GameStateRunning::moveBoards(const float diff)
{
    this->leftBoard.move(diff);
    this->rightBoard.move(diff);
}

void GameStateRunning::update()
{
    this->dt = this->clock.restart().asSeconds();
    float newPos;
    switch (this->currentMovement)
    {
    case BoardsMovement::up:
        newPos = this->leftBoard.getPosition().y - Board::boardVelocity * this->dt;
        if(newPos >= 0.f)
            this->moveBoards(-Board::boardVelocity * this->dt);
        break;
        
    case BoardsMovement::down:
        newPos = this->leftBoard.getPosition().y + Board::boardVelocity * this->dt;
        if(newPos <= this->window.getSize().y - Board::HEIGHT)
            this->moveBoards(Board::boardVelocity * this->dt);
        break;
    
    default:
        break;
    }
}

void GameStateRunning::draw() const
{
    this->window.draw(this->leftBoard);
    this->window.draw(this->rightBoard);
    this->window.draw(this->ball);
}

} // namespace engine
