#ifndef TILE_H
#define TILE_H


#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "constants.hpp"
#include "utility.hpp"

#include <stdexcept>


struct Tile // клетка на поле
{
    enum TileType
    {
        UNINITIALIZED = -1, // неинициализирован
        EMPTY, // пустая клетка
        PATH_BEGIN, // клетка - часть пути (начало)
        PATH, // клетка - часть пути
        PATH_END, // клетка - часть пути (конец)
        ARCHER_TOWER, // лучники
    };

    static sf::Vector2i hovered;
    static sf::Vector2i selected;

    TileType type;
    sf::RectangleShape rect;

    static inline sf::Color getColorByType(const TileType type)
    {
        switch (type)
        {
            case Tile::TileType::UNINITIALIZED: throw std::invalid_argument("Cannot get color of an uninitialized tile");
            case Tile::TileType::EMPTY: return EMPTY_TILE_COLOR;
            case Tile::TileType::PATH_BEGIN: return PATHBEGIN_TILE_COLOR;
            case Tile::TileType::PATH: return PATH_TILE_COLOR;
            case Tile::TileType::PATH_END: return PATHEND_TILE_COLOR;
            case Tile::TileType::ARCHER_TOWER: return ARCHER_TOWER_TILE_COLOR;
        }       
    }

    static inline bool isTower(TileType type)
    {
        return 
        type == ARCHER_TOWER;
    }

    static inline bool isPath(TileType type)
    {
        return 
        type == PATH_BEGIN ||
        type == PATH ||
        type == PATH_END;
    }

    inline Tile() 
    {
        this->type = Tile::TileType::UNINITIALIZED;
    }

    Tile(const Tile::TileType type, const sf::Vector2i tilePos)
    {
        this->type = type;
        sf::RectangleShape rect(sf::Vector2f(TILESIDELEN, TILESIDELEN));

        rect.setPosition(TILESIDELEN * tilePos.x, TILESIDELEN * tilePos.y);
        rect.setFillColor(Tile::getColorByType(type));
        rect.setOutlineColor(COLOR_BLACK);
        rect.setOutlineThickness(TILE_BORDER_THICKNESS);

        this->rect = rect;
    }

    sf::Color color() const
    {
        return this->rect.getFillColor();
    }

    inline void changeColor(const sf::Color color)
    {
        this->rect.setFillColor(color);
    }

    inline void changeColor(const int delta)
    {
        const sf::Color currentColor = this->rect.getFillColor();
        const sf::Color newColor(currentColor.r + delta, currentColor.g + delta, currentColor.b + delta);
        this->changeColor(newColor);
    }

    inline void changeType(const Tile::TileType type)
    {
        this->type = type;
        changeColor(getColorByType(type));
        
    }

    bool isTower()
    {
        return Tile::isTower(this->type);
    }

    bool isPath()
    {
        return Tile::isPath(this->type);
    }
};

sf::Vector2i Tile::hovered = VEC2_NULL;
sf::Vector2i Tile::selected = VEC2_NULL;

#endif // TILE_H