#ifndef GRID_H
#define GRID_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "constants.hpp"
#include "tile.hpp"
#include "path.hpp"
#include "utility.hpp"


class Grid // singleton class, описание игрового мира
{
    Tile tiles[TILES_PER_X][TILES_PER_Y];
    std::vector<Path> pathlist;
    sf::Vector2i hovered = VEC2_NULL;
public:

    inline Tile& getTile(const sf::Vector2i tilePos)
    {
        return tiles[tilePos.x][tilePos.y];
    }

    inline Tile& getTile(const int tilePosX, const int tilePosY)
    {
        return tiles[tilePosX][tilePosY];
    }

    inline const Tile& getTile(const sf::Vector2i tilePos) const
    {
        return tiles[tilePos.x][tilePos.y];
    }

    inline const Tile& getTile(const int tilePosX, const int tilePosY) const
    {
        return tiles[tilePosX][tilePosY];
    }

    inline void setTileColor(const sf::Vector2i tilePos, const sf::Color color)
    {
        Tile& tile = getTile(tilePos);
        tile.changeColor(color);
    }

    inline void changeTileBrightness(const sf::Vector2i tilePos, const int delta)
    {
        Tile& tile = getTile(tilePos);
        tile.changeColor(delta);
    }

    inline bool isMouseInside(const int mouseX, const int mouseY) const
    {
        constexpr int sizeX = TILESIDELEN*TILES_PER_X;
        constexpr int sizeY = TILESIDELEN*TILES_PER_Y;
        return mouseX < sizeX && mouseY < sizeY;
    }
    
    Grid()
    {
        for (int i = 0; i < TILES_PER_X; i++)
        {
            for (int j = 0; j < TILES_PER_Y; j++)
            {
                Tile tile(Tile::TileType::EMPTY, {i, j});
                tiles[i][j] = tile;
            }
        }
    }

    void updateBrightness(int mouseX, int mouseY) // при смене координаты мыши
    {
        if (!isMouseInside(mouseX, mouseY)) return; // вне сетки

        const sf::Vector2i tilePos = util::getTilePos(mouseX, mouseY);
        if (tilePos == Tile::hovered) return; // внутри той же ячейки

        changeTileBrightness(tilePos, HOVER_RGB_INCREMENT);
        if (Tile::hovered != VEC2_NULL) changeTileBrightness(Tile::hovered, -HOVER_RGB_INCREMENT);
        Tile::hovered = tilePos;
    }

    void draw(sf::RenderWindow& window) const
    {
        for (int i = 0; i < TILES_PER_X; i++)
        {
            for (int j = 0; j < TILES_PER_Y; j++)
            {
                const Tile& tile = getTile(i, j);
                window.draw(tile.rect);
            }
        }
    }

    void appendPath(const Path& path) // новый объект
    {
        const auto& v = path.getDirectionVector();
        const size_t vec_size = v.size();
        if (vec_size == 0) return;

        sf::Vector2i pos = path.begin();
        Tile* currentTile = &getTile(pos);
        currentTile->changeType(Tile::TileType::PATH_BEGIN);
        pos += util::getDelta(v[0]);

        for (size_t i = 1; i < vec_size; i++)
        {
            currentTile = &getTile(pos);
            currentTile->changeType(Tile::TileType::PATH);
            pos += util::getDelta(v[i]);
        }
        
        currentTile = &getTile(pos);
        currentTile->changeType(Tile::TileType::PATH_END);
    }

    const std::vector<Path>& getPathList() const
    {
        return this->pathlist;
    }

    void spawnEnemy(const int pathIndex)
    {
        
    }
};

#endif // GRID_H