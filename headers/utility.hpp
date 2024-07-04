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

enum AttackType // способ атаки башен
{
    FIRST, // ближайший к концу пути
    LAST, // ближайший к началу пути
    CLOSE // блишайший к башне
};

template <class T>
inline sf::Vector2<T> getDelta(const PathDirection dir)
{
    switch (dir)
    {
        case PathDirection::UP: return sf::Vector2<T>(0, -1);
        case PathDirection::DOWN: return sf::Vector2<T>(0, 1);
        case PathDirection::LEFT: return sf::Vector2<T>(-1, 0);
        case PathDirection::RIGHT: return sf::Vector2<T>(1, 0);
    }
}

inline PathDirection getDir(const sf::Vector2i delta)
{
    if (delta.x == 1) return PathDirection::RIGHT;
    if (delta.x == -1) return PathDirection::LEFT;
    if (delta.y == -1) return PathDirection::UP;
    if (delta.y == 1) return PathDirection::DOWN;
    throw std::invalid_argument("[getDir] Invalid utility function use");
}

inline sf::Vector2i getTilePos(const int mouseX, const int mouseY)
{
    const int tileX = mouseX / TILESIDELEN;
    const int tileY = mouseY / TILESIDELEN;
    return {tileX, tileY};
}

inline int convertTileInfo(const sf::Vector2i tilePos)
{
    return tilePos.y*TILES_PER_X + tilePos.x;
}

inline sf::Vector2i convertTileInfo(const int tileIndex)
{
    const int X = tileIndex % TILES_PER_X;
    const int Y = tileIndex / TILES_PER_X;
    return {X, Y};
}

inline sf::Vector2f getTileCenter(sf::Vector2i tilePos)
{
    const float x = tilePos.x * TILESIDELEN + TILESIDELEN/2;
    const float y = tilePos.y * TILESIDELEN + TILESIDELEN/2;
    return {x, y};
}

inline float distance(sf::Vector2f p1, sf::Vector2f p2)
{
    const float dx = p2.x - p1.x;
    const float dy = p2.y - p1.y;
    return std::hypotf(dx, dy);
}

} // namespace util

#endif // UTILITY_H
