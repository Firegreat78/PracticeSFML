#ifndef CONSTANTS_H
#define CONSTANTS_H

#define FPS 75 // кадров в секунду

#define TILESIDELEN 40 // сторона квадрата клетки поля (пикселей) - чётное целое
#define TILES_PER_X 40 // количество клеток по горизонтали -> (вправо)
#define TILES_PER_Y 16 // количество клеток по вертикали V (вниз)

#define TILE_BORDER_THICKNESS 1 // толщина границы клеток поля
#define HOVER_RGB_INCREMENT 15 // повышение RGB при наводе мышкой на клетку поля
#define SELECT_RGB_INCREMENT 20 // повышение RGB при нажатии ЛКМ по клетке поля


#define RIGHT_PANEL_SIZE 0
#define BOTTOM_PANEL_SIZE 250

#define WIN_WIDTH TILESIDELEN*TILES_PER_X + RIGHT_PANEL_SIZE // размер окна (X)
#define WIN_HEIGHT TILESIDELEN*TILES_PER_Y + BOTTOM_PANEL_SIZE // размер окна (Y)

#define VEC2_NULL sf::Vector2i(-1, -1) // null-vector 

#define PATHVEC_CAPACITY 100

#define ENEMY_SIZE (TILESIDELEN / 2) // размер ректа врага + длина хп бара
#define HP_BAR_THICKNESS 7 // пикселей
#define HP_BAR_OFFSETY (0 + HP_BAR_THICKNESS) // пикселей

#define START_LIVES 100

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
#define PATH_TILE_COLOR sf::Color(158, 200, 70)
#define PATHBEGIN_TILE_COLOR sf::Color(11, 220, 81)
#define PATHEND_TILE_COLOR sf::Color(220, 43, 80)
#define OBSTACLE_TILE_COLOR sf::Color(220, 165, 5)
#define ARCHER_TOWER_TILE_COLOR sf::Color(20, 195, 81)
#define BOMB_TOWER_TILE_COLOR sf::Color(220, 201, 175)

#endif // CONSTANTS_H