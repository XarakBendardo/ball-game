#include <random>
#include "../include/GameState.h"
#include "../include/gameconfig.h"

namespace engine
{

/*---------------------------------------- ABSTRACT ----------------------------------------------*/
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
    if(!this->changeRequired)
        throw std::runtime_error("Cannot return next state if current state does not require change.");
    return this->nextState;
}

/*---------------------------------------- MENU ----------------------------------------------*/
std::vector<std::string> GameStateMenu::optionsText = {"PLAY", "EXIT"};
const unsigned int GameStateMenu::FONT_SIZE = 100u;
const unsigned int GameStateMenu::DELIMETER_SIZE = 100u;

GameStateMenu::GameStateMenu(sf::RenderWindow& renderWindow, const bool isPauseMenu) :
    GameStateAbstract(renderWindow), idx(0), pauseMenu(isPauseMenu)
{
    size_t pos = 0;
    sf::Vector2f position;
    unsigned int height = GameStateMenu::optionsText.size() * GameStateMenu::FONT_SIZE + (GameStateMenu::optionsText.size() - 1) * GameStateMenu::DELIMETER_SIZE;
    unsigned int top = (this->window.getSize().y - height) / 2;
    for (const auto& option : GameStateMenu::optionsText)
    {
        sf::Text text(option, config::FONT, GameStateMenu::FONT_SIZE);
        position = {
            static_cast<float>((this->window.getSize().x - text.getGlobalBounds().width) / 2),
            static_cast<float>(top + pos * (GameStateMenu::FONT_SIZE + GameStateMenu::DELIMETER_SIZE))
        };
        text.setPosition(position);
        this->options.push_back(text);
        ++pos;
    }
}

GameStateMenu::~GameStateMenu() {}

void GameStateMenu::reactToEvent(const sf::Event& event)
{
    if(event.type != sf::Event::KeyPressed)
        return;
    
    switch (event.key.code)
    {
    case sf::Keyboard::Escape:
        this->changeRequired = true;
        this->finished = true;
        break;

    case sf::Keyboard::Up:
        if(this->idx > 0)
            --this->idx;
        else
            this->idx = static_cast<unsigned short>(this->options.size() - 1);
        break;
    
    case sf::Keyboard::Down:
        if(this->idx < static_cast<unsigned short>(this->options.size() - 1))
            ++this->idx;
        else
            this->idx = 0;
        break;

    case sf::Keyboard::Enter:
        this->changeRequired = true;
        this->finished = true;
        if(this->optionsText[idx] == "PLAY")
        {
            if(!this->pauseMenu)
                this->nextState = new GameStateRunning(this->window);
        }
        else if(this->optionsText[idx] == "EXIT")
            this->window.close();
        break;
    
    default:
        break;
    }
}

void GameStateMenu::update()
{
    for(size_t i = 0; i < this->options.size(); ++i)
    {
        if(i == idx)
            this->options[i].setFillColor(sf::Color::Red);
        else
            this->options[i].setFillColor(sf::Color::White);
    }
}

void GameStateMenu::draw() const
{
    for(const auto& option : this->options)
    {
        this->window.draw(option);
    }
}

/*---------------------------------------- RUNNING ----------------------------------------------*/

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
            this->nextState = new GameStateMenu(this->window, true);
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

void GameStateRunning::moveBall(const float diffX, const float diffY)
{
    this->ball.move(diffX, diffY);
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
