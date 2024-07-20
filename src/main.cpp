#include <iostream>
#include <cmath>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>

const float PI = 3.14159265359f;

float ComputeAngle(sf::Vector2f point1, sf::Vector2f point2)
{
    return std::atan2((point2.x - point1.x), (point2.y - point1.y)) * (180/PI);
    // std::atan2() returns RAD but you need DEG for SFML so *(180/PI) to convert it.
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Chicken Invaders");

    sf::RectangleShape rect; // Your spacehip
    rect.setSize(sf::Vector2f(50,20));
    rect.setFillColor(sf::Color::Green);
    rect.setOrigin(rect.getLocalBounds().width / 2.f, rect.getLocalBounds().height / 2.f); // Its important that the origin is in the middle of the sprite
    rect.setPosition(400,550);

    std::vector<sf::CircleShape> bullets;
    std::vector<float> angles;
    sf::Clock clock;
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        float rotAngle = ComputeAngle(rect.getPosition(), static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
       // std::cout << rotAngle << std::endl;
        rect.setRotation(90-rotAngle); // "90-" Depends on how your Spaceshape is rotated by default
	//rect.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)).x, rect.getPosition().y);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		rect.setPosition(rect.getPosition().x, rect.getPosition().y - 0.5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		rect.setPosition(rect.getPosition().x, rect.getPosition().y + 0.5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		rect.setPosition(rect.getPosition().x - 0.5, rect.getPosition().y);	
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		rect.setPosition(rect.getPosition().x + 0.5, rect.getPosition().y);	
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clock.getElapsedTime().asSeconds() > 0.035) {
		bullets.push_back(sf::CircleShape());
		bullets.back().setRadius(5);
		bullets.back().setOrigin(5,5);
		bullets.back().setPosition(rect.getPosition());
		angles.push_back(
			std::atan2(sf::Mouse::getPosition(window).y - rect.getPosition().y,
				sf::Mouse::getPosition(window).x - rect.getPosition().x)
			);
		clock.restart();
	}
        
	window.clear(sf::Color(0,0,173));
	
	for (int i = 0; i < bullets.size(); i++)
	{
		window.draw(bullets[i]);
		bullets[i].move(5*cos(angles[i]), 5*sin(angles[i]));
	}


        window.draw(rect);

        window.display();

    }

    return 0;
}

