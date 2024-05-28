#include <SFML/Graphics.hpp>

#ifndef BALL_H
#define BALL_H

namespace engine
{
class Ball : public sf::Drawable
{
    public:
        static const float RADIUS;

        Ball(const float posX = 0.f, const float posY = 0.f);
        Ball(const Ball& other) = default;
        Ball& operator=(const Ball& other) = default;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void move(const float diffX, const float diffY);

    private:
        sf::CircleShape sprite;
};
}

#endif