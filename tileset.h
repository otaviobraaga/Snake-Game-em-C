#ifndef TILESET_H_INCLUDED
#define TILESET_H_INCLUDED
#include "screen.h"

typedef struct
{
    int w, h;
    char padrao;
    
    struct Tile
    {
        char c;
        char p;
    }**tiles;
}Tileset;

typedef enum
{
    EMPTY,
    BLOCK,
    HEAD,
    SEGMENT,
    FOOD
}State;

void tileset_draw(Tileset *tileset, Screen *tela, int x, int y);
Tileset* tileset_new(int h, int w, const char tiles[h][w], const char props[h][w]);
void tileset_rand_food(Tileset *tileset, Screen *tela);

#endif // TILESET_H_INCLUDED
