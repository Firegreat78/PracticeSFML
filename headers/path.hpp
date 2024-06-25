#ifndef PATH_H
#define PATH_H

#include "constants.hpp"
#include "tile.hpp"

#include <cinttypes>
#include <vector>
#include <iostream>
#include <SFML/System/Vector2.hpp>


class Path
{
private:
    std::vector<util::PathDirection> v;
    std::vector<sf::Vector2i> pathTiles;
public:
    Path(int beginX, int beginY)
    {
        v.reserve(PATHVEC_CAPACITY);
        pathTiles.reserve(PATHVEC_CAPACITY);

        sf::Vector2i start(beginX, beginY);
        
        pathTiles.push_back(start);
    }

    void append(const util::PathDirection dir)
    {
        this->v.push_back(dir);

        const sf::Vector2i last = pathTiles[pathTiles.size() - 1];
        this->pathTiles.push_back(last + util::getDelta(dir));
    }

    void append(const util::PathDirection dir, const int times)
    {
        for (int i = 0; i < times; i++) this->append(dir);
    }

    void append(const std::vector<util::PathDirection>& sequence)
    {
        for (const auto dir : sequence) this->append(dir);
    }

    const std::vector<util::PathDirection>& getDirectionVector() const
    {
        return this->v;
    }

    sf::Vector2i begin() const
    {
        return this->pathTiles[0];
    }

    util::PathDirection getDirection(const int tileIndex)
    {
        const sf::Vector2i current = this->pathTiles.at(tileIndex);
        const sf::Vector2i next = this->pathTiles.at(tileIndex + 1);
        const sf::Vector2i delta = next - current;
        return util::getDir(delta);
    }

    void print() const
    {
        static const char* const LEFT = "Left";
        static const char* const RIGHT = "Right";
        static const char* const DOWN = "Down";
        static const char* const UP = "Up";

        const size_t size = this->v.size();
        const char* ptr = nullptr;

        for (uint64_t i = 0; i < size; i++)
        {
            switch (v[i])
            {
                case util::PathDirection::DOWN: ptr = DOWN;
                break;
                case util::PathDirection::UP: ptr = UP;
                break;
                case util::PathDirection::LEFT: ptr = LEFT;
                break;
                case util::PathDirection::RIGHT: ptr = RIGHT;
                break;
            }
            std::cout << "Direction " << i + 1 << ": " << ptr << '\n';
        }
    }
};

#endif // PATH_H