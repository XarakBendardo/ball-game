#include <random>
#include <iostream>
#include "../include/GameState.h"
#include "../include/gameconfig.h"
#include "../include/SoundManager.h"

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
const std::vector<std::string> GameStateMenu::mainMenuOptionsText = {"NEW GAME", "EXIT"};
const std::vector<std::string> GameStateMenu::pauseMenuOptionsText = {"RESTART", "NEW GAME", "EXIT"};
const unsigned int GameStateMenu::FONT_SIZE = 100u;
const unsigned int GameStateMenu::DELIMETER_SIZE = 100u;

GameStateMenu::GameStateMenu(sf::RenderWindow& renderWindow, const bool isMainMenu, const std::vector<std::string> initOptions) :
    GameStateAbstract(renderWindow), idx(0), mainMenu(isMainMenu), optionsText(initOptions)
{
    size_t pos = 0;
    sf::Vector2f position;
    unsigned int height = initOptions.size() * GameStateMenu::FONT_SIZE + (initOptions.size() - 1) * GameStateMenu::DELIMETER_SIZE;
    unsigned int top = (this->window.getSize().y - height) / 2;
    for (const auto& option : initOptions)
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
        SoundManager::playSound(SoundManager::Sound::optionChange);
        if(this->idx > 0)
            --this->idx;
        else
            this->idx = static_cast<unsigned short>(this->options.size() - 1);
        break;
    
    case sf::Keyboard::Down:
        SoundManager::playSound(SoundManager::Sound::optionChange);
        if(this->idx < static_cast<unsigned short>(this->options.size() - 1))
            ++this->idx;
        else
            this->idx = 0;
        break;

    case sf::Keyboard::Enter:
        SoundManager::playSound(SoundManager::Sound::optionChoose);
        this->chooseOption();
        break;
    
    default:
        break;
    }
}

void GameStateMenu::chooseOption()
{
    this->changeRequired = true;
    this->finished = true;
    if(this->optionsText[idx] == "RESTART")
    {
        
    }
    else if(this->optionsText[idx] == "NEW GAME")
        this->nextState = new GameStateRunning(this->window);
    else if(this->optionsText[idx] == "EXIT")
        this->window.close();
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
    GameStateAbstract(renderWindow),
    currentMovement(GameStateRunning::BoardsMovement::none),
    lastXCollision(GameStateRunning::XCollision::none),
    lastYCollision(GameStateRunning::YCollision::none),
    scoreCount(0),
    gameOver(false)
{
    this->ball = Ball(this->window.getSize().x / 2 - Ball::RADIUS, this->window.getSize().y / 2 - Ball::RADIUS);
    this->leftBoard = Board(0.f, (this->window.getSize().y - Board::HEIGHT) / 2);
    this->rightBoard = Board(this->window.getSize().x - Board::WIDTH, (this->window.getSize().y - Board::HEIGHT) / 2);
    this->score = {std::string("SCORE: ") + std::to_string(scoreCount), config::FONT, 40u};
    this->score.setPosition(0, 0);
    this->gameOverPromt = {std::string("GAME OVER!"), config::FONT, 120u};
    this->gameOverPromt.setPosition(
        (this->window.getSize().x - this->gameOverPromt.getGlobalBounds().width) / 2,
        (this->window.getSize().y - this->gameOverPromt.getGlobalBounds().height) / 2);
    this->gameOverPromt.setFillColor(sf::Color::Red);
}

GameStateRunning::~GameStateRunning() {}

void GameStateRunning::resume()
{
    GameStateAbstract::resume();
    this->clock.restart();
}

void GameStateRunning::reactToEvent(const sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Escape:
            this->changeRequired = true;
            this->nextState = new GameStateMenu(this->window, false, GameStateMenu::pauseMenuOptionsText);
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

void GameStateRunning::updateScore()
{
    ++this->scoreCount;
    this->score.setString(std::string("SCORE: ") + std::to_string(this->scoreCount));
    if(this->scoreCount % 10 == 0)
        this->score.setFillColor(sf::Color::Red);
    else
        this->score.setFillColor(sf::Color::White);
}

void GameStateRunning::checkCollisions()
{
    auto ballPos = this->ball.getCenterPosition();
    bool collidedWithBoard = false;
    
    //boards
    if(ballPos.x <= Ball::RADIUS + Board::WIDTH
    && this->lastXCollision != GameStateRunning::XCollision::left)
    {
        if(ballPos.y >= this->leftBoard.getPosition().y
        && ballPos.y <= this->leftBoard.getPosition().y + Board::HEIGHT)
        {
            this->ball.velocity.x = -this->ball.velocity.x;
            this->lastXCollision = GameStateRunning::XCollision::left;
            collidedWithBoard = true;
            SoundManager::playSound(SoundManager::Sound::ballRebound);
        }
    }
    else if(ballPos.x >= this->window.getSize().x - Ball::RADIUS - Board::WIDTH
    && this->lastXCollision != GameStateRunning::XCollision::right)
    {
        if(ballPos.y >= this->rightBoard.getPosition().y
        && ballPos.y <= this->rightBoard.getPosition().y + Board::HEIGHT)
        {
            this->ball.velocity.x = -this->ball.velocity.x;
            this->lastXCollision = GameStateRunning::XCollision::right;
            collidedWithBoard = true;
            SoundManager::playSound(SoundManager::Sound::ballRebound);
        }
    }

    // side walls
    if(ballPos.x <= Ball::RADIUS
    && this->lastXCollision != GameStateRunning::XCollision::left)
    {
        this->gameOver = true;
        this->ball.velocity = {0.f, 0.f};
        this->lastXCollision = GameStateRunning::XCollision::left;
        SoundManager::playSound(SoundManager::Sound::ballRebound);
    }
    else if(ballPos.x >= this->window.getSize().x - Ball::RADIUS
    && this->lastXCollision != GameStateRunning::XCollision::right)
    {
        this->gameOver = true;
        this->ball.velocity = {0.f, 0.f};
        this->lastXCollision = GameStateRunning::XCollision::right;
        SoundManager::playSound(SoundManager::Sound::ballRebound);
    }
    
    // up/down walls
    if(ballPos.y <= Ball::RADIUS
    && this->lastYCollision != GameStateRunning::YCollision::up)
    {
        this->ball.velocity.y = -this->ball.velocity.y;
        this->lastYCollision = GameStateRunning::YCollision::up;
        SoundManager::playSound(SoundManager::Sound::ballRebound);
    }
    else if(ballPos.y >= this->window.getSize().y - Ball::RADIUS
    && this->lastYCollision != GameStateRunning::YCollision::down)
    {
        this->ball.velocity.y = -this->ball.velocity.y;
        this->lastYCollision = GameStateRunning::YCollision::down;
        SoundManager::playSound(SoundManager::Sound::ballRebound);
    }

    if(collidedWithBoard)
        this->updateScore();
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

    this->moveBall(this->ball.velocity.x * this->dt, this->ball.velocity.y * this->dt);
    this->checkCollisions();
}

void GameStateRunning::draw() const
{
    this->window.draw(this->leftBoard);
    this->window.draw(this->rightBoard);
    this->window.draw(this->ball);
    this->window.draw(this->score);
    if(this->gameOver)
        this->window.draw(this->gameOverPromt);
}

} // namespace engine
