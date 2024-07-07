// 1. Clone SFML template repo
// 2. Inside build dir: "cmake -G Ninja .."
// 3. Inside build dir: "ninja"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cassert>
#include <cstdint>

#include "grid.hpp"

Path genPath();
void checkEvent(sf::RenderWindow&, sf::Event&, Grid&);

int main()
{
    sf::RenderWindow window({WIN_WIDTH, WIN_HEIGHT}, "Tower Defense Simulation", sf::Style::Close);
    Grid grid;
    grid.appendPath(genPath());
    window.setFramerateLimit(FPS);
    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);) checkEvent(window, event, grid);
        window.clear(COLOR_WHITE);
        grid.draw(window);
        grid.tick();
        window.display();
    }
}

Path genPath()
{
    Path p(0, 0);
    p.append(util::PathDirection::RIGHT, 1);
    p.append(util::PathDirection::DOWN, 2);
    p.append(util::PathDirection::RIGHT, 6);
    p.append(util::PathDirection::DOWN, 4);
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
    p.append(util::PathDirection::RIGHT, 8);
    p.append(util::PathDirection::DOWN, 2);
    p.append(util::PathDirection::LEFT, 6);
    p.append(util::PathDirection::DOWN, 10);
    p.append(util::PathDirection::LEFT, 13);
    p.append(util::PathDirection::UP, 7);
    p.append(util::PathDirection::RIGHT, 7);
    return p;
}

void checkEvent(sf::RenderWindow& w, sf::Event& e, Grid& g)
{
    switch (e.type)
    {
        case sf::Event::Closed:
        w.close();
        break;
        case sf::Event::MouseMoved:
        g.updateBrightness(e.mouseMove.x, e.mouseMove.y);
        break;
        case sf::Event::MouseButtonPressed:
        g.updateSelected(e.mouseButton.x, e.mouseButton.y);
        break;
        case sf::Event::KeyPressed:
        switch (e.key.code)
        {
            case sf::Keyboard::Q:
            g.placeTowerInSelected();
            break;
            case sf::Keyboard::E:
            g.spawnEnemy(0);
            break;
            case sf::Keyboard::Backspace:
            g.deleteTower();
            break;
            default:
            break;
        }

        break;
        default: 
        break;
    }

}