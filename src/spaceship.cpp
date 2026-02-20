#include "spaceship.hpp"
#include <cmath>

Spaceship::Spaceship(sf::Vector2f pos)
    : position(pos), thrusterFlicker(0)
{
    // Main body (triangle pointing up)
    body.setPointCount(3);
    body.setPoint(0, sf::Vector2f(0, -20));   // top
    body.setPoint(1, sf::Vector2f(-15, 15));  // bottom left
    body.setPoint(2, sf::Vector2f(15, 15));   // bottom right
    body.setFillColor(sf::Color(0, 180, 0));  // Green
    body.setOrigin(0, 0);
    
    // Left wing
    leftWing.setPointCount(3);
    leftWing.setPoint(0, sf::Vector2f(-15, 0));
    leftWing.setPoint(1, sf::Vector2f(-25, 10));
    leftWing.setPoint(2, sf::Vector2f(-15, 10));
    leftWing.setFillColor(sf::Color(0, 150, 0));
    
    // Right wing
    rightWing.setPointCount(3);
    rightWing.setPoint(0, sf::Vector2f(15, 0));
    rightWing.setPoint(1, sf::Vector2f(25, 10));
    rightWing.setPoint(2, sf::Vector2f(15, 10));
    rightWing.setFillColor(sf::Color(0, 150, 0));
    
    // Cockpit
    cockpit.setRadius(5);
    cockpit.setOrigin(5, 5);
    cockpit.setFillColor(sf::Color::Cyan);
    
    // Left thruster
    leftThruster.setSize(sf::Vector2f(4, 8));
    leftThruster.setOrigin(2, 0);
    leftThruster.setFillColor(sf::Color(255, 100, 0)); // Orange
    
    // Right thruster
    rightThruster.setSize(sf::Vector2f(4, 8));
    rightThruster.setOrigin(2, 0);
    rightThruster.setFillColor(sf::Color(255, 100, 0)); // Orange
    
    setPosition(pos);
}

void Spaceship::move(float dx, float dy)
{
    position.x += dx;
    position.y += dy;
    setPosition(position);
}

void Spaceship::setPosition(sf::Vector2f pos)
{
    position = pos;
    body.setPosition(position);
    leftWing.setPosition(position);
    rightWing.setPosition(position);
    cockpit.setPosition(position + sf::Vector2f(0, -5));
    leftThruster.setPosition(position + sf::Vector2f(-8, 15));
    rightThruster.setPosition(position + sf::Vector2f(8, 15));
}

sf::Vector2f Spaceship::getPosition() const
{
    return position;
}

sf::FloatRect Spaceship::getGlobalBounds() const
{
    return body.getGlobalBounds();
}

void Spaceship::updateThrusters(bool isMoving)
{
    if (isMoving) {
        thrusterFlicker += 0.3f;
        float flicker = 1.0f + 0.3f * std::sin(thrusterFlicker);
        leftThruster.setSize(sf::Vector2f(4, 8 * flicker));
        rightThruster.setSize(sf::Vector2f(4, 8 * flicker));
        
        // Alternate colors for flame effect
        int colorPhase = static_cast<int>(thrusterFlicker * 2) % 3;
        if (colorPhase == 0) {
            leftThruster.setFillColor(sf::Color(255, 100, 0));  // Orange
            rightThruster.setFillColor(sf::Color(255, 100, 0));
        } else if (colorPhase == 1) {
            leftThruster.setFillColor(sf::Color(255, 200, 0));  // Yellow
            rightThruster.setFillColor(sf::Color(255, 200, 0));
        } else {
            leftThruster.setFillColor(sf::Color(255, 50, 0));   // Red
            rightThruster.setFillColor(sf::Color(255, 50, 0));
        }
    } else {
        leftThruster.setSize(sf::Vector2f(4, 0));  // Hide thrusters
        rightThruster.setSize(sf::Vector2f(4, 0));
    }
}

void Spaceship::draw(sf::RenderWindow& window)
{
    window.draw(leftThruster);
    window.draw(rightThruster);
    window.draw(leftWing);
    window.draw(rightWing);
    window.draw(body);
    window.draw(cockpit);
}
