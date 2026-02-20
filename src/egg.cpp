#include "egg.hpp"

Egg::Egg(sf::Vector2f position)
    : speed(0.03f)
{
    shape.setRadius(5);
    shape.setScale(sf::Vector2f(2, 2.3f)); // Oval shape (narrow width, taller height)
    shape.setOrigin(4, 6);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::White);
}

void Egg::move()
{
    shape.move(0, speed);
}
