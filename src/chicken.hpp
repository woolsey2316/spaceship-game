#ifndef CHICKEN_HPP
#define CHICKEN_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Chicken
{
public:
    Chicken(sf::Vector2f position, sf::Vector2f velocity);
    
    void takeDamage();
    bool isDestroyed() const;
    void move();
    bool shouldLayEgg();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition() const;
    
    sf::CircleShape body;
    sf::CircleShape leftWing;
    sf::CircleShape rightWing;
    sf::ConvexShape beak;
    sf::Vector2f velocity;
    int health;
    sf::Clock eggTimer;
};

#endif
