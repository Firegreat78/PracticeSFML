#ifndef PATH_H
#define PATH_H

#include "constants.hpp"
#include "utility.hpp"
#include "enemy.hpp"

#include <cinttypes>
#include <vector>
#include <iostream>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>



class Path
{
private:
    std::vector<util::PathDirection> v;
    std::vector<sf::Vector2i> pathTiles;
    std::vector<Enemy> enemies;

    double getCompleted(const Enemy& enemy) const
    {
        const double pathLenPixels = (pathTiles.size() - 1) * TILESIDELEN;
        const double pixelsPerFrame = enemy.speed / FPS;
        const double increment = pixelsPerFrame / pathLenPixels;
        return enemy.path_completed + increment;
    }

public:
    Path(int beginX, int beginY)
    {
        v.reserve(PATHVEC_CAPACITY);
        pathTiles.reserve(PATHVEC_CAPACITY);

        sf::Vector2i start(beginX, beginY);
        
        pathTiles.push_back(start);
    }

    const std::vector<Enemy>& getEnemies() const noexcept
    {
        return enemies;
    }

    std::vector<Enemy>& getEnemies() noexcept
    {
        return enemies;
    }

    void append(const util::PathDirection dir)
    {
        this->v.push_back(dir);

        const sf::Vector2i last = pathTiles[pathTiles.size() - 1];
        this->pathTiles.push_back(last + util::getDelta<int>(dir));
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
    // pathCompletedRatio в полуинтервале [0; 1)
    // Возврат: центр пути (пиксели)
    sf::Vector2f getPositionForRatio(const double pathCompletedRatio) const
    {
        double halfIndexD;

        const size_t sizeTimesTwo = (this->pathTiles.size() - 1) * 2; // кол-во половинок (размер)
        const double halfsCompletedRatio = pathCompletedRatio * sizeTimesTwo; // [0; размер-1)
        double currentHalfCompletion = std::modf(halfsCompletedRatio, &halfIndexD); // на сколько завершена текущая половина [0; 1)
        size_t halfIndex = halfIndexD; // индекс клетки

        if ((halfIndex & 1) == 1) 
        {
            currentHalfCompletion += 1;
            halfIndex -= 1;
        }

        halfIndex /= 2; // порядковый номер клетки
        currentHalfCompletion /= 2; // смещение в сторону

        sf::Vector2f offset = util::getDelta<float>(v[halfIndex]);
        offset.x *= (TILESIDELEN * currentHalfCompletion);
        offset.y *= (TILESIDELEN * currentHalfCompletion);

        const sf::Vector2i tilePos = pathTiles[halfIndex];
        const float xPos = TILESIDELEN*tilePos.x + TILESIDELEN/2;
        const float yPos = TILESIDELEN*tilePos.y + TILESIDELEN/2;
        sf::Vector2f pos(xPos, yPos);
        return pos + offset;        
    }

    void spawnEnemy()
    {
        Enemy enemy(100, 100, 1);
        enemy.updateRects(getPositionForRatio(0));
        enemies.push_back(enemy);
    }

    void drawEnemies(sf::RenderWindow& w)
    {
        for (Enemy& e : enemies)
        {
            e.draw(w);
        }
    }

    void tick() // вызывается каждый кадр
    {
        std::vector<std::vector<Enemy>::iterator> toDelete;

        for (auto it = enemies.begin(); it != enemies.end(); ++it)
        {
            Enemy& enemy = *it;
            const double newCompleted = getCompleted(enemy);
            
            if (newCompleted >= 1 || enemy.hp <= 0)
            {
                toDelete.push_back(it);
                continue;
            }
            sf::Vector2f pixelPos = getPositionForRatio(newCompleted);
            
            enemy.path_completed = newCompleted;
            enemy.updateRects(pixelPos);
        }

        for (auto enemy : toDelete)
        {
            enemies.erase(enemy);
        }
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

        for (double i = 0; i < 1; i += 0.001)
        {
            //util::printVector<float>(getPositionForRatio(i)); std::cout << '\n';
        }
    }
};

#endif // PATH_H