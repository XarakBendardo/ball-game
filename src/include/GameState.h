#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../include/Ball.h"
#include "../include/Board.h"

#ifndef GAMESTATE_H
#define GAMESTATE_H

namespace engine
{
class GameStateAbstract
{
    public:
        GameStateAbstract(sf::RenderWindow& renderWindow);
        virtual ~GameStateAbstract();
        virtual void reactToEvent(const sf::Event& event) = 0;
        virtual void update() = 0;
        virtual void draw() const = 0;
        /*Returns true if current state has to be changed to another state.
        Otherwise returns false.*/
        bool wantsToChange() const;

        /*Returns true if the state has been finished and therefore cannot be pushed on the state stack.
        Otherwise returns false - it must be pushed on stack.*/
        bool isFinished() const;

        /*Returns the new state, if the state wants to change.
        THROWS an error, if called when wantsToChange() is false therefore should always be preceded with wantsToChange() check.*/
        GameStateAbstract* getNextState() const;

        virtual void resume();

    protected:
        sf::RenderWindow& window;
        bool changeRequired, finished;
        GameStateAbstract* nextState;
};

class GameStateMenu : public GameStateAbstract
{
    public:
        static const std::vector<std::string> optionsText;
        static const unsigned int FONT_SIZE;
        static const unsigned int DELIMETER_SIZE;

        GameStateMenu() = delete;
        GameStateMenu(const GameStateMenu& other) = default;
        GameStateMenu(sf::RenderWindow& renderWindow, const bool isPauseMenu = false);
        GameStateMenu& operator=(const GameStateMenu& other) = default;
        virtual ~GameStateMenu();
        virtual void reactToEvent(const sf::Event& event) override;
        virtual void update() override;
        virtual void draw() const override;

    private:
        std::vector<sf::Text> options;
        unsigned short idx;
        bool pauseMenu;
};

class GameStateRunning : public GameStateAbstract
{
    public:
        enum class BoardsMovement {up, down, none};
        enum class XCollision {left, right, none};
        enum class YCollision {up, down, none};

        GameStateRunning() = delete;
        GameStateRunning(const GameStateRunning& other) = default;
        GameStateRunning(sf::RenderWindow& renderWindow);
        GameStateRunning& operator=(const GameStateRunning& other) = default;
        virtual ~GameStateRunning();
        virtual void reactToEvent(const sf::Event& event) override;
        virtual void update() override;
        virtual void draw() const override;
        virtual void resume() override;

    private:
        sf::Clock clock;
        float dt;
        BoardsMovement currentMovement;
        Ball ball;
        sf::Vector2f ballVelocity;
        Board leftBoard, rightBoard;
        XCollision lastXCollision;
        YCollision lastYCollision;
        unsigned long scoreCount;
        sf::Text score;

        void moveBoards(const float diff);
        void checkCollisions();
        void moveBall(const float diffX, const float diffY);
        void updateScore();
};

} // namespace engine


#endif // GAMESTATE_H