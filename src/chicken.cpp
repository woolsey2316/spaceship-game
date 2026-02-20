#include "chicken.hpp"
#include <cstdlib>

Chicken::Chicken(sf::Vector2f position, sf::Vector2f velocity)
    : velocity(velocity), health(3)
{
    // Body (red oval)
    body.setRadius(15);
    body.setScale(1.2f, 1.0f);
    body.setOrigin(15, 15);
    body.setPosition(position);
    body.setFillColor(sf::Color::Red);
    
    // Left wing (small white circle)
    leftWing.setRadius(8);
    leftWing.setOrigin(8, 8);
    leftWing.setFillColor(sf::Color::White);
    
    // Right wing (small white circle)
    rightWing.setRadius(8);
    rightWing.setOrigin(8, 8);
    rightWing.setFillColor(sf::Color::White);
    
    // Beak (triangle)
    beak.setPointCount(3);
    beak.setPoint(0, sf::Vector2f(0, 0));
    beak.setPoint(1, sf::Vector2f(10, 5));
    beak.setPoint(2, sf::Vector2f(0, 10));
    beak.setOrigin(0, 5);
    beak.setFillColor(sf::Color::Yellow);
    
    eggTimer.restart();
}

void Chicken::takeDamage()
{
    if (health > 0) {
        health--;
    }
}

bool Chicken::isDestroyed() const
{
    return health <= 0;
}

void Chicken::move()
{
    body.move(velocity);
    leftWing.setPosition(body.getPosition() + sf::Vector2f(-12, 0));
    rightWing.setPosition(body.getPosition() + sf::Vector2f(12, 0));
    beak.setPosition(body.getPosition() + sf::Vector2f(15, 0));
}

bool Chicken::shouldLayEgg()
{
    float eggInterval = 2.0f + (std::rand() % 100) / 100.0f; // 2-3 seconds
    if (eggTimer.getElapsedTime().asSeconds() > eggInterval) {
        eggTimer.restart();
        return true;
    }
    return false;
}

void Chicken::draw(sf::RenderWindow& window)
{
    window.draw(leftWing);
    window.draw(rightWing);
    window.draw(body);
    window.draw(beak);
}

sf::FloatRect Chicken::getGlobalBounds() const
{
    return body.getGlobalBounds();
}

sf::Vector2f Chicken::getPosition() const
{
    return body.getPosition();
}
