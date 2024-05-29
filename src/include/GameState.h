#include <SFML/Graphics.hpp>
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

        void resume();

    protected:
        sf::RenderWindow& window;
        bool changeRequired, finished;
        GameStateAbstract* nextState;
};

class GameStateRunning : public GameStateAbstract
{
    public:
        enum BoardsMovement {up, down, none};

        GameStateRunning(sf::RenderWindow& renderWindow);
        virtual ~GameStateRunning();
        virtual void reactToEvent(const sf::Event& event) override;
        virtual void update() override;
        virtual void draw() const override;

    private:
        sf::Clock clock;
        float dt;
        BoardsMovement currentMovement;
        Ball ball;
        Board leftBoard, rightBoard;

        void moveBoards(const float diff);
};

} // namespace engine


#endif // GAMESTATE_H