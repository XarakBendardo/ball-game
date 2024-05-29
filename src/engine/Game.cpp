#include "../include/Game.h"

namespace engine
{

Game* Game::instance = nullptr;
float Game::boardVelocity = 500.f;
unsigned int Game::FPSLimit = 60u;

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
    this->window = new sf::RenderWindow{
        {sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height},
        "Ball Game",
        sf::Style::Fullscreen};
    this->window->setFramerateLimit(Game::FPSLimit);
    this->currentState = new GameStateRunning(*this->window);
}

Game::~Game()
{
    delete this->window;
    delete this->currentState;
}

void Game::run()
{
    while (this->window->isOpen())
    {
        for (auto event = sf::Event{}; this->window->pollEvent(event);)
        {
            this->currentState->reactToEvent(event);
        }
        this->currentState->update();
        this->window->clear();
        this->currentState->draw();
        this->window->display();
    }
}

} // namespace engine