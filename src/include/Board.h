#include <SFML/Graphics.hpp>

#ifndef BOARD_H
#define BOARD_H

namespace engine
{
class Board : public sf::Drawable
{
    /*
    Class for boards on each side of the screen.
    */
    public:
        static const float WIDTH;
        static const float HEIGHT;
        static float boardVelocity;

        Board(const float posX = 0.f, const float posY = 0.f);
        Board(const Board& other) = default;
        Board& operator=(const Board& other) = default;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::Vector2f getPosition() const;
        void move(const float diff);
    
    private:
        sf::RectangleShape sprite;
};
} // namespace engine

#endif //BOARD_H