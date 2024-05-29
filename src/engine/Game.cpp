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
    this->stateStack.push(this->currentState);
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
        if(this->currentState->wantsToChange())
            this->changeState(this->currentState->getNextState());
        
        if(this->currentState != nullptr)
        {
            this->currentState->update();
            this->window->clear();
            this->currentState->draw();
            this->window->display();
        }
        else
            this->window->close();
    }
}

void Game::changeState(GameStateAbstract* newState)
{
    if(this->currentState->isFinished())
    {
        delete this->currentState;
        this->stateStack.pop();
    }

    if(newState != nullptr)
    {
        this->stateStack.push(newState);
        this->currentState = newState;
    }
    else
        this->currentState = this->stateStack.empty() ? nullptr : this->stateStack.top();
}

} // namespace engine