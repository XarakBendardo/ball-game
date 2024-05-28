#include <SFML/Graphics.hpp>
#include "include/Board.h"
#include "include/Ball.h"


int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);
    
    engine::Board left, right(window.getSize().x - engine::Board::WIDTH);
    engine::Ball ball(window.getSize().x / 2 - engine::Ball::RADIUS, window.getSize().y / 2 - engine::Ball::RADIUS);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(left);
        window.draw(right);
        window.draw(ball);
        window.display();
    }
}