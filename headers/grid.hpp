#ifndef GRID_H
#define GRID_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "constants.hpp"
#include "tile.hpp"
#include "path.hpp"
#include "tower.hpp"
#include "utility.hpp"
#include "enemy.hpp"

#include <map>


class Grid // singleton class, описание игрового мира
{
    int lives = START_LIVES;
    Tile tiles[TILES_PER_X][TILES_PER_Y];
    std::vector<Path> pathlist;
    std::map<int, ArcherTower> archerTowers;
    //std::map<int, BombTower> bombTowers;

    ArcherTower& getArcherTower(const sf::Vector2i tilePos)
    {
        const int tileIndex = util::convertTileInfo(tilePos);
        return archerTowers[tileIndex];
    }

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

    void updateSelected(int mouseX, int mouseY) // при нажатии ЛКМ
    {
        if (!isMouseInside(mouseX, mouseY)) return; // вне сетки

        const sf::Vector2i tilePos = util::getTilePos(mouseX, mouseY);
        if (tilePos == Tile::selected) return; // выбрали ту же ячейку

        changeTileBrightness(tilePos, SELECT_RGB_INCREMENT);
        if (Tile::selected != VEC2_NULL) changeTileBrightness(Tile::selected, -SELECT_RGB_INCREMENT);
        Tile::selected = tilePos;
    }

    void draw(sf::RenderWindow& window)
    {
        for (int i = 0; i < TILES_PER_X; i++)
        {
            for (int j = 0; j < TILES_PER_Y; j++)
            {
                const Tile& tile = getTile(i, j);
                window.draw(tile.rect); 
            }
        }

        for (Path& p : pathlist)
        {
            p.drawEnemies(window);
        }
    }

    void tick() // вызывается каждый кадр для логики игрового мира
    {
        for (Path& p : pathlist) p.tick(); // движутся враги
        
        towersShoot(); // стреляют башни
    }

    void appendPath(const Path& path) // новый объект
    {
        const auto& v = path.getDirectionVector();
        const size_t vec_size = v.size();
        assert(vec_size != 0);

        sf::Vector2i pos = path.begin();
        Tile* currentTile = &getTile(pos);
        currentTile->changeType(Tile::TileType::PATH_BEGIN);
        pos += util::getDelta<int>(v[0]);

        for (size_t i = 1; i < vec_size; i++)
        {
            currentTile = &getTile(pos);
            currentTile->changeType(Tile::TileType::PATH);
            pos += util::getDelta<int>(v[i]);
        }
        
        currentTile = &getTile(pos);
        currentTile->changeType(Tile::TileType::PATH_END);

        pathlist.push_back(path);
    }

    const std::vector<Path>& getPathList() const
    {
        return this->pathlist;
    }

    Path& getPath(int pathIndex)
    {
        return pathlist.at(pathIndex);
    }

    void spawnEnemy(const int pathIndex)
    {
        Path& path = pathlist.at(pathIndex);
        path.spawnEnemy();
    }


    void placeTowerInSelected(Tile::TileType towerType)
    {
        Tile& tile = getTile(Tile::selected);
        if (Tile::isPath(tile.type)) return;

        const int tileIndex = util::convertTileInfo(Tile::selected);

        tile.changeType(towerType);
        tile.changeColor(SELECT_RGB_INCREMENT);

        if (Tile::hovered == Tile::selected)
        tile.changeColor(HOVER_RGB_INCREMENT);

        if (towerType == Tile::TileType::ARCHER_TOWER) archerTowers[tileIndex] = ArcherTower(Tile::selected);
        // if (towerType == Tile::TileType::BOMB_TOWER) bombTowers[tileIndex] = BombTower(Tile::selected);
    }

    std::vector<Enemy*> getAllEnemies()
    {
        std::vector<Enemy*> enemies;

        for (auto& path : pathlist)
        {
            std::vector<Enemy>& v = path.getEnemies();
            enemies.reserve(enemies.capacity() + v.size());
            for (auto& enemy : v) enemies.push_back(&enemy);
        }
        return enemies;
    }

    void towersShoot()
    {
        std::vector<Enemy*> mapEnemies = getAllEnemies();
        for (auto& t : archerTowers)
        {
            ArcherTower& tower = t.second;
            tower.tick();
            if (!tower.canAttack()) continue;

            Enemy* target = tower.getTarget(mapEnemies);
            if (target) tower.attack(target);
        }
    }
};

#endif // GRID_H