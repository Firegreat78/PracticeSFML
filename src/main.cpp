// 1. Clone SFML template repo
// 2. Inside build dir: "cmake -G Ninja .."
// 3. Inside build dir: "ninja"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <random>
#include <cassert>
#include <limits>
#include <cstdint>
#include <map>
#include <ctime>
#include <chrono>

#include "constants.hpp"
#include "randomGenerator.hpp"
#include "path.hpp"
#include "grid.hpp"
#include "utility.hpp"
#include "enemy.hpp"

void testfunc();
void mainApp();
Path genPath();

randomGenerator<int64_t, 1 << 12> rng(0, INT64_MAX);


int main()
{
    srand(time(nullptr));
    Enemy::enemies.reserve(100);
    
    mainApp();
}

void testfunc()
{
    getchar();
    std::chrono::steady_clock a; 
}

Path genPath()
{
    Path p(0, 0);
    p.append(util::PathDirection::RIGHT, 2);
    p.append(util::PathDirection::DOWN, 3);
    p.append(util::PathDirection::RIGHT, 5);
    p.append(util::PathDirection::UP, 3);
    p.append(util::PathDirection::RIGHT, 2);
    p.append(util::PathDirection::DOWN, 7);
    p.append(util::PathDirection::LEFT, 7);
    p.append(util::PathDirection::DOWN, 3);
    p.append(util::PathDirection::RIGHT, 4);
    p.append(util::PathDirection::UP, 1);
    p.append(util::PathDirection::RIGHT, 5);
    p.append(util::PathDirection::UP, 9);
    return p;
}

void mainApp()
{
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Tower Defense", sf::Style::Close);
    Grid grid;
    grid.appendPath(genPath(grid));
    window.setFramerateLimit(FPS);
    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                window.close();
                break;

                case sf::Event::MouseMoved:
                grid.updateBrightness(event.mouseMove.x, event.mouseMove.y);
                break;

                case sf::Event::MouseButtonPressed:
                break;

                case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                    using sf::Keyboard;

                    case Keyboard::Num1:
                    std::cout << 'F' << '!' << '\n';
                    break;
                    case Keyboard::Num2:

                    break;

                    case Keyboard::Num3:

                    break;
                    default:
                    break;
                }

                break;
    
                default: 
                break;
            }
        }
        window.clear(COLOR_GRAY);
        grid.draw(window);
        window.display();
    }
}