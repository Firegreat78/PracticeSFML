#ifndef TOWER_H
#define TOWER_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "constants.hpp"
#include "enemy.hpp"

struct ArcherTower
{
    float dmg; // урон
    float fireRate; // выстрелов в секунду
    float radius; // радиус атаки в пикселях
    float cooldown = 0; // прошло секунд с выстрела
    sf::Vector2i tilePos;

    ArcherTower() : ArcherTower(VEC2_NULL) {}

    ArcherTower(sf::Vector2i tilePos) : ArcherTower(tilePos, 15, 3, 400) {}


    ArcherTower(sf::Vector2i tilePos, float dmg, float fireRate, float radius)
    {
        this->tilePos = tilePos;
        this->dmg = dmg;
        this->fireRate = fireRate;
        this->radius = radius;
    }
    
    void tick()
    {
        if (!canAttack()) cooldown += (1.0 / FPS);
    }

    bool canAttack()
    {
        return cooldown >= (1/fireRate);
    }

    void attack(Enemy* enemy)
    {
        enemy->decreaseHP(dmg);
        cooldown = 0;
    }

    Enemy* getTarget(std::vector<Enemy*>& enemies) const
    {
        Enemy* first = nullptr;
        float mindist;
        const sf::Vector2f towerPos = util::getTileCenter(tilePos);
        for (auto enemy : enemies)
        {
            const sf::Vector2f enemyPos = enemy->getPos();

            const float dist = util::distance(towerPos, enemyPos);
            if (dist > radius) continue;

            if (first == nullptr)
            {
                first = enemy;
                mindist = dist;
                continue;
            }

            if (enemy->path_completed > first->path_completed) first = enemy;
        }
        return first;
    }
};

#endif // TOWER_H