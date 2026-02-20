#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>

#include "chicken.hpp"
#include "egg.hpp"
#include "spaceship.hpp"

const float PI = 3.14159265359f;

float ComputeAngle(sf::Vector2f point1, sf::Vector2f point2)
{
    return std::atan2((point2.x - point1.x), (point2.y - point1.y)) * (180/PI);
    // std::atan2() returns RAD but you need DEG for SFML so *(180/PI) to convert it.
}


int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    sf::RenderWindow window(sf::VideoMode(800,600), "Chicken Invaders");

    Spaceship spaceship(sf::Vector2f(400, 550));

    std::vector<sf::CircleShape> bullets;
    std::vector<Chicken> chickens;
    std::vector<Egg> eggs;
    std::vector<float> angles;
    sf::Clock clock;
    sf::Clock spawnClock;
    int chickensToSpawn = 5;
    bool waveActive = false;
    bool isGameOver = false;
    
    sf::Font font;
    sf::Text gameOverText;
    sf::Text restartText;
    
    // Try to load a font (using SFML default if available)
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition(250, 250);
    
    restartText.setCharacterSize(30);
    restartText.setFillColor(sf::Color::White);
    restartText.setString("Press R to Restart");
    restartText.setPosition(270, 320);
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

      // Handle restart
      if (isGameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        isGameOver = false;
        bullets.clear();
        chickens.clear();
        eggs.clear();
        spaceship.setPosition(sf::Vector2f(400, 550));
        waveActive = false;
        chickensToSpawn = 5;
        spawnClock.restart();
      }
      
      bool isMoving = false;
      if (!isGameOver) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
          spaceship.move(0, -0.03);
          isMoving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
          spaceship.move(0, 0.03);
          isMoving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
          spaceship.move(-0.081, 0);
          isMoving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
          spaceship.move(0.081, 0);
          isMoving = true;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clock.getElapsedTime().asSeconds() > 0.235) {
          bullets.push_back(sf::CircleShape());
          bullets.back().setRadius(5);
          bullets.back().setOrigin(5,5);
          bullets.back().setPosition(spaceship.getPosition());
              clock.restart();
        }
      }
      
      spaceship.updateThrusters(isMoving);
      
      // Spawn chickens in waves
      if (!isGameOver && !waveActive && spawnClock.getElapsedTime().asSeconds() > 3.0) {
        waveActive = true;
        chickensToSpawn = 20;
        spawnClock.restart();
      }
      
      if (!isGameOver && waveActive && chickensToSpawn > 0 && spawnClock.getElapsedTime().asSeconds() > 0.3) {
        float randomX = 50 + (std::rand() % 700);
        float horizontalSpeed = -0.1f + (std::rand() % 200) / 1000.0f; // -1.0 to 1.0
        chickens.push_back(Chicken(sf::Vector2f(randomX, -30), sf::Vector2f(horizontalSpeed, .02f)));
        chickensToSpawn--;
        if (chickensToSpawn == 0) {
          waveActive = false;
        }
        spawnClock.restart();
      }
      
      // Chickens lay eggs
      if (!isGameOver) {
        for (int i = 0; i < chickens.size(); i++) {
          if (chickens[i].shouldLayEgg()) {
            eggs.push_back(Egg(chickens[i].getPosition()));
          }
        }
      }
            
      window.clear(sf::Color(0,0,173));
      
      if (!isGameOver) {
        // Collision detection: player vs chickens
        for (int i = chickens.size() - 1; i >= 0; i--)
        {
          if (spaceship.getGlobalBounds().intersects(chickens[i].getGlobalBounds()))
          {
            isGameOver = true;
            break;
          }
        }
        
        // Collision detection: player vs eggs
        for (int i = eggs.size() - 1; i >= 0; i--)
        {
          if (spaceship.getGlobalBounds().intersects(eggs[i].shape.getGlobalBounds()))
          {
            isGameOver = true;
            break;
          }
        }
      }
      
      // Collision detection: bullets vs chickens
      for (int i = bullets.size() - 1; i >= 0; i--)
      {
        bool bulletHit = false;
        for (int j = chickens.size() - 1; j >= 0; j--)
        {
          if (bullets[i].getGlobalBounds().intersects(chickens[j].getGlobalBounds()))
          {
            chickens[j].takeDamage();
            bulletHit = true;
            if (chickens[j].isDestroyed()) {
              chickens.erase(chickens.begin() + j);
            }
            break;
          }
        }
        if (bulletHit) {
          bullets.erase(bullets.begin() + i);
        }
      }
      
      // Clean up off-screen entities
      for (int i = bullets.size() - 1; i >= 0; i--)
      {
        if (bullets[i].getPosition().y < -10) {
          bullets.erase(bullets.begin() + i);
        }
      }
      
      for (int i = chickens.size() - 1; i >= 0; i--)
      {
        if (chickens[i].getPosition().y > 610) {
          chickens.erase(chickens.begin() + i);
        }
      }
      
      // Clean up off-screen eggs
      for (int i = eggs.size() - 1; i >= 0; i--)
      {
        if (eggs[i].shape.getPosition().y > 610) {
          eggs.erase(eggs.begin() + i);
        }
      }
      
      for (int i = 0; i < bullets.size(); i++)
      {
        window.draw(bullets[i]);
        bullets[i].move(0, -0.2);
      }
      
      for (int i = 0; i < chickens.size(); i++)
      {
        chickens[i].move();
        chickens[i].draw(window);
      }
      
      for (int i = 0; i < eggs.size(); i++)
      {
        eggs[i].move();
        window.draw(eggs[i].shape);
      }
      
      spaceship.draw(window);
      
      if (isGameOver) {
        window.draw(gameOverText);
        window.draw(restartText);
      }
      
      window.display();
    }

    return 0;
}

