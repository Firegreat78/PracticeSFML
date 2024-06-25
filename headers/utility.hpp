#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>

#include <iostream>

namespace util
{

enum PathDirection // направление
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

void printColor(const sf::Color color)
{
    std::cout << "Color<" << (int)color.r << ',' << (int)color.g << ',' << (int)color.b << ',' << (int)color.a << '>';
}

template <class T>
void printVector(const sf::Vector2<T> v)
{
    std::cout << "Vec2<" << v.x << ',' << v.y << '>';
}

void printRectangleInfo(const sf::RectangleShape& rect)
{
    std::cout << "Rectangle<";
    printVector(rect.getPosition());
    printColor(rect.getFillColor());
    std::cout << '>';
}

inline sf::Vector2i getDelta(const PathDirection dir)
{
    switch (dir)
    {
        case PathDirection::UP: return sf::Vector2i(0, -1);
        case PathDirection::DOWN: return sf::Vector2i(0, 1);
        case PathDirection::LEFT: return sf::Vector2i(-1, 0);
        case PathDirection::RIGHT: return sf::Vector2i(1, 0);
    }
}

inline PathDirection getDir(const sf::Vector2i delta)
{
    if (delta.x == 1) return PathDirection::RIGHT;
    if (delta.x == -1) return PathDirection::LEFT;
    if (delta.y == -1) return PathDirection::UP;
    if (delta.y == 1) return PathDirection::DOWN;
}

inline sf::Vector2i getTilePos(const int mouseX, const int mouseY)
{
    const int tileX = mouseX / TILESIDELEN;
    const int tileY = mouseY / TILESIDELEN;
    return sf::Vector2i(tileX, tileY);
}










} // namespace util

#endif // UTILITY_H
