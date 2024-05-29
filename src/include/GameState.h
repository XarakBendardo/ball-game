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

    protected:
        sf::RenderWindow& window;
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