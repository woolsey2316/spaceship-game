#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Spaceship
{
public:
    Spaceship(sf::Vector2f position);
    
    void move(float dx, float dy);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    void draw(sf::RenderWindow& window);
    void updateThrusters(bool isMoving);
    
private:
    sf::ConvexShape body;
    sf::ConvexShape leftWing;
    sf::ConvexShape rightWing;
    sf::CircleShape cockpit;
    sf::RectangleShape leftThruster;
    sf::RectangleShape rightThruster;
    sf::Vector2f position;
    float thrusterFlicker;
};

#endif
