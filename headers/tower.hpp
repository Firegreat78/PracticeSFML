#ifndef TOWER_H
#define TOWER_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "constants.hpp"
#include "enemy.hpp"

struct ArcherTower
{
    float dmg;
    float fireRate; // выстрелов в секунду
    float radius; // радиус атаки в пикселях
    float cooldown = 0; // прошло секунд с выстрела
    util::AttackType type = util::AttackType::FIRST;
    sf::Vector2i tilePos;
    sf::RectangleShape beam; // при атаке появляется на 
    public:

    ArcherTower() : ArcherTower(VEC2_NULL) {}

    ArcherTower(sf::Vector2i tilePos) : ArcherTower(tilePos, 10, 2, 300) {}


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

    void setAttackType(util::AttackType type)
    {
        this->type = type;
    }

    void attack(Enemy* enemy)
    {
        std::cout << "ATK!\n";
        enemy->decreaseHP(dmg);
        cooldown = 0;
    }

    Enemy* getTarget(std::vector<Enemy*>& enemies) const
    {
        using util::AttackType;

        Enemy* first = nullptr;
        Enemy* last = nullptr;
        Enemy* close = nullptr;
        float mindist;
        for (auto enemy : enemies)
        {
            const sf::Vector2f enemyPos = enemy->getPos();

            const sf::Vector2f towerPos = util::getTileCenter(tilePos);
            const float dist = util::distance(towerPos, enemyPos);
            if (dist > radius) continue;

            if (first == nullptr)
            {
                first = last = close = enemy;
                mindist = dist;
                continue;
            }

            if (enemy->path_completed > first->path_completed) first = enemy;
            if (enemy->path_completed < last->path_completed) last = enemy;
            if (dist < mindist) 
            {
                close = enemy; 
                mindist = dist;
            }
        }

        switch (type)
        {
            case AttackType::FIRST: return first;
            case AttackType::LAST: return last;
            case AttackType::CLOSE: return close;
        }
    }
};

#endif // TOWER_H