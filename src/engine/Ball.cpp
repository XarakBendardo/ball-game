#include "../include/Ball.h"

namespace engine
{

const float Ball::RADIUS = 40.f;

Ball::Ball(const float posX, const float posY)
{
    this->sprite = sf::CircleShape(Ball::RADIUS);
    this->sprite.setPosition(posX, posY);
}

void Ball::move(const float diffX, const float diffY)
{
    this->sprite.move(diffX, diffY);
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(this->sprite, states);
}

}