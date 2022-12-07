#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "screen.h"
#include "tileset.h"

typedef enum
{
    null,
    UP,
    DOWN,
    LEFT,
    RIGHT
}Heading;

typedef struct
{
    int length;
    Heading direcao;
    
    struct Segmento
    {
        int x, y;
        char c;
    }segmentos[32];
}Cobravia;

Cobravia* new_cobravia(int spawn_x, int spawn_y);
void draw_cobravia(Screen *tela, Cobravia *cobravia);
int get_input();

int main()
{   
    int screen_x = 48;
    int screen_y = 16;
    int speed    = 100;
    int butao    = 0;
    
	Screen   *tela     = screen_new(screen_y, screen_x);
	Cobravia *cobravia = new_cobravia(8, 8);
    
    char tiles[screen_y][screen_x];
    char props[screen_y][screen_x];
    
    for(int i = 0; i < screen_y; i++)
		for(int j = 0; j < screen_x; j++)
        {
            tiles[i][j] = '.';
            props[i][j] = EMPTY;
        }
    
    Tileset *tileset = tileset_new(screen_y, screen_x, tiles, props);
    
    tileset_rand_food(tileset, tela);
    
	while(1)
	{
        butao = get_input();
        
        if(butao >= UP && butao <= RIGHT)
            cobravia->direcao = butao;
        
		screen_clear(tela, '.');
		
        tileset_draw(tileset, tela, 0, 0);
		draw_cobravia(tela, cobravia);
		
		screen_present(tela);
        
        int  x = cobravia->segmentos[0].x;
        int  y = cobravia->segmentos[0].y;
        
        if(tileset->tiles[y][x].p == FOOD)
        {
            cobravia->length++;
            speed -= 2;
            
            tileset_rand_food(tileset, tela);
        }
        
        else if(tileset->tiles[y][x].p == SEGMENT)
        {
            break;
        }
        
        if(cobravia->direcao == UP)         y--;
        else if(cobravia->direcao == DOWN)  y++;
        else if(cobravia->direcao == LEFT)  x--;
        else if(cobravia->direcao == RIGHT) x++;
        
        if(x >= screen_x) x = 0;
        else if(x < 0)    x = screen_x-1;
        if(y >= screen_y) y = 0;
        else if(y < 0)    y = screen_y-1;
        
        for(int i = 0; i < cobravia->length; i++)
        {   
            int tx = cobravia->segmentos[i].x;
            int ty = cobravia->segmentos[i].y;
            
            if(i > 0)
                tileset->tiles[y][x].p = SEGMENT;
            tileset->tiles[ty][tx].p = EMPTY;
            
            cobravia->segmentos[i].x = x;
            cobravia->segmentos[i].y = y;
            x = tx;
            y = ty;
        }
		
		Sleep(speed);
	}

	return 0;
}

void draw_cobravia(Screen *tela, Cobravia *cobravia)
{
    for(int i = 0; i < cobravia->length; i++)
    {   
        int  x = cobravia->segmentos[i].x;
        int  y = cobravia->segmentos[i].y;
        char c = cobravia->segmentos[i].c;
        
        screen_draw_pixel(tela, x, y, c);
    }
}

Cobravia* new_cobravia(int spawn_x, int spawn_y)
{
    Cobravia *cobravia = (Cobravia*) malloc(sizeof(Cobravia));
    cobravia->length = 4;
    cobravia->direcao = LEFT;
    
    char image[] = "O===============================";
    
    for(int i = 0; i < 32; i++)
    {
        cobravia->segmentos[i].x = spawn_x + i;
        cobravia->segmentos[i].y = spawn_y;
        cobravia->segmentos[i].c = image[i];
    }
    
   // cobravia->segmentos[0].c = 'O';
    
    return cobravia;
}

int get_input()
{
	int k = 0, butao;
	
    if(kbhit())
        k = getch();
	
	if(k == 224)
	{
		k = getch();
		
		if(k == 72)
			butao = 1;
		else if(k == 80)
			butao = 2;
		else if(k == 75)
			butao = 3;
		else if(k == 77)
			butao = 4;
	}
	else if(k == 32)
		butao = 5;
	else if(k == 27)
		butao = -1;
	else butao = 0;
	
	return butao;
}
