#ifndef ENEMY_H
#define ENEMY_H

#include "constants.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


struct Enemy
{
    sf::RectangleShape mainRect; // тело врага
    sf::RectangleShape hp_bar_green; // часть
    sf::RectangleShape hp_bar_red; // полная

    int hp, max_hp; // очки здоровья
    double speed; // пикселей/сек
    double path_completed = 0.0; // на сколько путь завершен [0; 1)

    Enemy(int hp, double speed)
    {
        this->hp = this->max_hp = hp;
        this->speed = speed;

        mainRect.setFillColor(COLOR_BLUE);
        hp_bar_green.setFillColor(COLOR_GREEN);
        hp_bar_red.setFillColor(COLOR_RED);

        mainRect.setSize({ENEMY_SIZE, ENEMY_SIZE});
        hp_bar_green.setSize({ENEMY_SIZE, HP_BAR_THICKNESS});
        hp_bar_red.setSize({ENEMY_SIZE, HP_BAR_THICKNESS});
    }

    // center берём из Path::getPositionForRatio
    void updateRects(sf::Vector2f center)
    {
        const sf::Vector2f rectPos = center - sf::Vector2f(ENEMY_SIZE/2, ENEMY_SIZE/2);
        mainRect.setPosition(rectPos);
        
        const sf::Vector2f barPos = rectPos - sf::Vector2f(0, HP_BAR_OFFSETY);
        hp_bar_green.setPosition(barPos);
        hp_bar_red.setPosition(barPos);

        const sf::Vector2f greenSize(ENEMY_SIZE*(((double)hp)/max_hp), HP_BAR_THICKNESS);

        hp_bar_green.setSize(greenSize);
    }

    void decreaseHP(int amount)
    {
        this->hp -= amount;
        sf::Vector2f newSize(ENEMY_SIZE * ((double)this->hp / this->max_hp), HP_BAR_THICKNESS);
        if (this->hp <= 0) newSize.x = 0;
        
        hp_bar_green.setSize(newSize);
    }

    void draw(sf::RenderWindow& w)
    {
        w.draw(mainRect);
        w.draw(hp_bar_red);
        w.draw(hp_bar_green);
    }

    sf::Vector2f getPos() const
    {
        return mainRect.getPosition() + sf::Vector2f(ENEMY_SIZE/2, ENEMY_SIZE/2);
    }
};

#endif // ENEMY_H
