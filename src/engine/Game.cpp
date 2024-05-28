#include "../include/Game.h"

namespace engine
{

Game* Game::instance = nullptr;

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

Game::Game()
{
    this->window = new sf::RenderWindow{ { 1920u, 1080u }, "Ball Game" };
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
            if (event.type == sf::Event::Closed)
            {
                this->window->close();
            }
        }

        this->window->clear();
        this->window->draw(this->leftBoard);
        this->window->draw(this->rightBoard);
        this->window->draw(this->ball);
        this->window->display();
    }
}

} // namespace engine