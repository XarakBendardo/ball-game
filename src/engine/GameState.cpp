#include "../include/GameState.h"

namespace engine
{

GameStateAbstract::GameStateAbstract(sf::RenderWindow& renderWindow) :
    window(renderWindow), changeRequired(false), finished(false), nextState(nullptr) {}

GameStateAbstract::~GameStateAbstract() {}

bool GameStateAbstract::wantsToChange() const { return this->changeRequired; }

bool GameStateAbstract::isFinished() const { return this->finished; }

void GameStateAbstract::resume()
{
    this->changeRequired = false;
    this->nextState = nullptr;
}

GameStateAbstract* GameStateAbstract::getNextState() const
{
    if(!this->finished)
        throw std::runtime_error("Cannot return next state if current state is not finished.");
    return this->nextState;
}

GameStateRunning::GameStateRunning(sf::RenderWindow& renderWindow) :
    GameStateAbstract(renderWindow), currentMovement(GameStateRunning::BoardsMovement::none)
{
    this->ball = Ball(this->window.getSize().x / 2 - Ball::RADIUS, this->window.getSize().y / 2 - Ball::RADIUS);
    this->leftBoard = Board(0.f, (this->window.getSize().y - Board::HEIGHT) / 2);
    this->rightBoard = Board(this->window.getSize().x - Board::WIDTH, (this->window.getSize().y - Board::HEIGHT) / 2);
}

GameStateRunning::~GameStateRunning() {}

void GameStateRunning::reactToEvent(const sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Escape:
            this->changeRequired = true;
            this->finished = true;
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