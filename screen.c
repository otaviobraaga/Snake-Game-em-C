#include "screen.h"

void screen_draw_image(Screen *tela, int h, int w, int x, int y, char image[h][w])
{
	int i, j;

	if(x+w >= tela->width+1 || y+h >= tela->height+1)
		return;

	for(i = 0; i < h; i++)
		for(j = 0; j < w; j++)
			tela->matriz[y+i][x+j] = image[i][j];
}

void screen_draw_pixel(Screen *tela, int x, int y, char character)
{
	if(x >= tela->width+1 || y >= tela->height+1)
		return;

	tela->matriz[y][x] = character;
}

void screen_present(Screen *tela)
{
	int i, size = 0;
	char *buffer = (char*) malloc(tela->width*tela->height+tela->height*20);
	
	for(i = 0; i < tela->height; i++)
	{//memset(tela->matriz[i], 'x', tela->width);
        size = (tela->width+1)*i;
		snprintf(buffer+size, tela->width, "%s", tela->matriz[i]);
        buffer[tela->width*(i+1)+i] = '\n';
	}

	printf("%s", buffer);

	free((void*)buffer);
}

Screen* screen_new(int height, int width)
{
	int i;
	Screen *tela = (Screen*) malloc(sizeof(Screen));
	
	tela->matriz = (char**) malloc(height * sizeof(char*));
	tela->width = width;
	tela->height = height;
	tela->clear = screen_clear;
	
	for(i = 0; i < height; i++)
		tela->matriz[i] = (char*) malloc(width * sizeof(char));
	
	return tela;
}

//funçoes de Screen
void screen_clear(Screen *tela, char character)
{
	int i, j;
	
	for(i = 0; i < tela->height; i++)
		//memset(tela->matriz[i], ' ', tela.width);
		for(j = 0; j < tela->width; j++)
			tela->matriz[i][j] = character;
		
	system("cls");
}