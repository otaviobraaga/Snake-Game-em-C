#include "tileset.h"

void tileset_draw(Tileset *tileset, Screen *tela, int x, int y)
{
	int i, j;

	if(x+tileset->w >= tela->width+1 || y+tileset->h >= tela->height+1)
		return;

	for(i = 0; i < tileset->h; i++)
		for(j = 0; j < tileset->w; j++)
			tela->matriz[y+i][x+j] = tileset->tiles[i][j].c;
}

Tileset* tileset_new(int h, int w, const char tiles[h][w], const char props[h][w])
{
	int i, j;
	Tileset *tileset = (Tileset*) malloc(sizeof(Tileset));
	
	tileset->tiles = (struct Tile**) malloc(h * sizeof(struct Tile*));
	tileset->w = w;
	tileset->h = h;
    tileset->padrao = '.';
	
	for(i = 0; i < h; i++)
    {
		tileset->tiles[i] = (struct Tile*) malloc(w * sizeof(struct Tile));
        
        for(j = 0; j < tileset->w; j++)
        {
            tileset->tiles[i][j].c = tiles[i][j];
            tileset->tiles[i][j].p = props[i][j];
        }
    }
	
	return tileset;
}

void tileset_rand_food(Tileset *tileset, Screen *tela)
{
   //posiçao aleatoria para a comida
   int x = rand() % tela->width;
   int y = rand() % tela->height;
   
   //remove comidas existentes no tileset
   for(int i = 0; i < tileset->h; i++)
		for(int j = 0; j < tileset->w; j++)
            if(tileset->tiles[i][j].p == FOOD)
            {
                tileset->tiles[i][j].c = tileset->padrao;
                tileset->tiles[i][j].p = EMPTY;
            }
   
   //add comida no tileset
   tileset->tiles[y][x].c = 'X';
   tileset->tiles[y][x].p = FOOD; 
}