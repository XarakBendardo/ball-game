#include "../include/Board.h"

namespace engine
{

const float Board::WIDTH = 20.f;
const float Board::HEIGHT = 200.f;
float Board::boardVelocity = 1000.f;

Board::Board(const float posX, const float posY)
{
    this->sprite = sf::RectangleShape(sf::Vector2f(Board::WIDTH, Board::HEIGHT));
    this->sprite.setPosition(posX, posY);
}

void Board::move(const float diff)
{
    this->sprite.move(0.f, diff);
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(this->sprite, states);
}

sf::Vector2f Board::getPosition() const
{
    return this->sprite.getPosition();
}

} //namespace engine