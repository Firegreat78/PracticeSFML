#ifndef CONSTANTS_H
#define CONSTANTS_H

#define FPS 75 // кадров в секунду

#define TILESIDELEN 32 // сторона квадрата клетки поля (пикселей)
#define TILES_PER_X 40 // количество клеток по горизонтали -> (вправо)
#define TILES_PER_Y 16 // количество клеток по вертикали V (вниз)

#define TILE_BORDER_THICKNESS 1 // толщина границы клеток поля
#define HOVER_RGB_INCREMENT 20 // повышение RGB при наводе мышкой на клетку поля

#define RIGHT_PANEL_SIZE 0
#define BOTTOM_PANEL_SIZE 50

#define WIN_WIDTH TILESIDELEN*TILES_PER_X + RIGHT_PANEL_SIZE // размер окна (X)
#define WIN_HEIGHT TILESIDELEN*TILES_PER_Y + BOTTOM_PANEL_SIZE // размер окна (Y)

#define VEC2_NULL sf::Vector2i(-1, -1) // null-vector для текущей наведённой клетки

#define PATHVEC_CAPACITY 100 // 

// некоторые цвета
#define COLOR_RED sf::Color(255, 0, 0)
#define COLOR_BLUE sf::Color(0, 0, 255)
#define COLOR_GREEN sf::Color(0, 255, 0)
#define COLOR_BLACK sf::Color(0, 0, 0)
#define COLOR_GRAY sf::Color(200, 200, 200)
#define COLOR_LIGHTGRAY sf::Color(227, 227, 227)
#define COLOR_WHITE sf::Color(255, 255, 255)

// цвета клеток поля
#define EMPTY_TILE_COLOR sf::Color(180, 180, 180)
#define PATH_TILE_COLOR sf::Color(178, 234, 93)
#define PATHBEGIN_TILE_COLOR sf::Color(11, 218, 81)
#define PATHEND_TILE_COLOR sf::Color(229, 43, 80)
#define OBSTACLE_TILE_COLOR sf::Color(230, 165, 5)
#define ARCHER_TOWER_TILE_COLOR sf::Color(11, 218, 81)
#define BOMB_TOWER_TILE_COLOR sf::Color(76, 47, 39)

#endif // CONSTANTS_H