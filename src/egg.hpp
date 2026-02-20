#ifndef EGG_HPP
#define EGG_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

class Egg
{
public:
    Egg(sf::Vector2f position);
    
    void move();
    
    sf::CircleShape shape;
    float speed;
};

#endif
