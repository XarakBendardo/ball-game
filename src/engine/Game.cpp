#include <random>
#include "../include/Game.h"
#include "../include/paths.h"
#include "../include/gameconfig.h"
#include "../include/SoundManager.h"

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
    this->window = new sf::RenderWindow{
        {sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height},
        "Ball Game",
        sf::Style::Fullscreen};
    // this->window->setFramerateLimit(config::FPSLimit);
    this->currentState = new GameStateMenu(*this->window);
    this->stateStack.push(this->currentState);
}

Game::~Game()
{
    delete this->window;
    while(!this->stateStack.empty())
    {
        delete this->stateStack.top();
        this->stateStack.pop();
    }
}

void Game::init()
{
    std::srand(std::time(0));
    config::FPSLimit = 60u;
    config::FONT.loadFromFile(paths::FONTS_DIR + "/Pacifico.ttf");
    SoundManager::init();
}

void Game::run()
{
    while (this->window->isOpen() && this->currentState != nullptr)
    {
        for (auto event = sf::Event{}; this->window->pollEvent(event);)
        {
            this->currentState->reactToEvent(event);
        }
        
        this->currentState->update();
        this->window->clear();
        this->currentState->draw();
        this->window->display();

        if(this->currentState->wantsToChange())
            this->changeState(this->currentState->getNextState());
    }

    this->window->close();
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
    {
        if(this->stateStack.empty())
            this->currentState = nullptr;
        else
        {
            this->currentState = this->stateStack.top();
            this->currentState->resume();
        }
    }
}

} // namespace engine