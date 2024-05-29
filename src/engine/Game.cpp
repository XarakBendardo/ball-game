#include "../include/Game.h"

namespace engine
{

Game* Game::instance = nullptr;
float Game::boardVelocity = 500.f;

Game& Game::getInstance()
{
    if(Game::instance == nullptr)
    {
        Game::instance = new Game();
    }
    return *Game::instance;
}

void Game::cleanup()
{
    if(Game::instance != nullptr)
        delete Game::instance;
}

Game::Game() : currentMovement(BoardsMovement::none)
{
    this->window = new sf::RenderWindow{ { 1920u, 1080u }, "Ball Game" };
    this->window->setFramerateLimit(60);
    this->ball = Ball(this->window->getSize().x / 2 - Ball::RADIUS, this->window->getSize().y / 2 - Ball::RADIUS);
    this->leftBoard = Board(0.f, (this->window->getSize().y - Board::HEIGHT) / 2);
    this->rightBoard = Board(this->window->getSize().x - Board::WIDTH, (this->window->getSize().y - Board::HEIGHT) / 2);
}

Game::~Game()
{
    delete this->window;
}

void Game::run()
{
    while (this->window->isOpen())
    {
        for (auto event = sf::Event{}; this->window->pollEvent(event);)
        {
            this->reactToEvent(event);
        }
        this->update();
        this->window->clear();
        this->window->draw(this->leftBoard);
        this->window->draw(this->rightBoard);
        this->window->draw(this->ball);
        this->window->display();
    }
}

void Game::moveBoards(const float diff)
{
    this->leftBoard.move(diff);
    this->rightBoard.move(diff);
}

void Game::update()
{
    this->dt = this->clock.restart().asSeconds();
    switch (this->currentMovement)
    {
    case BoardsMovement::up:
        this->moveBoards(-Game::boardVelocity * this->dt);
        break;
        
    case BoardsMovement::down:
        this->moveBoards(Game::boardVelocity * this->dt);
        break;
    
    default:
        break;
    }
}

void Game::reactToEvent(sf::Event event)
{
    if (event.type == sf::Event::Closed)
        this->window->close();
    else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        this->window->close();
    else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
        this->currentMovement = BoardsMovement::up;
    else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
        this->currentMovement = BoardsMovement::down;
    else if(event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down))
        this->currentMovement = BoardsMovement::none;
}

} // namespace engine