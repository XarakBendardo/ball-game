#include <SFML/Graphics.hpp>

#ifndef GAMESTATE_H
#define GAMESTATE_H

namespace engine
{
class GameStateAbstract
{
    public:
        GameStateAbstract(sf::RenderWindow& renderWindow);
        virtual void reactToEvent(const sf::Event& event) = 0;
        virtual void update() = 0;
        virtual void draw() const = 0;

    protected:
        sf::RenderWindow& window;
};

class GameStateRunning : public GameStateAbstract
{
    public:
        GameStateRunning(sf::RenderWindow& renderWindow);
        virtual void reactToEvent(const sf::Event& event) override;
        virtual void update() override;
        virtual void draw() const override;

    private:
        sf::Clock clock;
        float dt;
};

} // namespace engine


#endif // GAMESTATE_H