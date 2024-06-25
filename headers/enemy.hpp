#ifndef ENEMY_H
#define ENEMY_H

#include "constants.hpp"
#include "path.hpp"
#include "grid.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


class Enemy
{
    public:
    static std::vector<Enemy> enemies;
    private:
    const Path* path = nullptr; // указатель на путь, по которому движется враг
    sf::RectangleShape hp_bar;

    int hp, max_hp; // очки здоровья
    float speed; // пикселей/сек
    int lives_drain; // сколько жизней уйдёт если враг дойдёт до конца пути
    int path_index; // индекс пути в векторе путей
    int tile = 0; // клетка пути по счёту
    float tile_percentage = 0.0f; // на сколько % текущая клетка завершена

    public:
    static void moveAll() // вызывается каждый кадр
    {
        for (auto& enemy : enemies) enemy.move();
    }

    Enemy(int path_index, int hp, float speed, int lives_drain)
    {
        enemies.push_back(*this);

        this->hp = this->max_hp = hp;
        this->speed = speed;
        this->lives_drain = lives_drain;
        this->path_index = path_index;
    }
    private:
    void move() // вызывается каждый кадр
    {

    }
};

std::vector<Enemy> Enemy::enemies = std::vector<Enemy>();

#endif // ENEMY_H
