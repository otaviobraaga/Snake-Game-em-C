#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

typedef struct
{
	char **matriz;
	int width, height;
	void *clear;
}Screen;

typedef struct
{
	char **matriz;
	int width, height;
}Entity;

void screen_draw_image(Screen *tela, int h, int w, int x, int y, char image[h][w]);
void screen_draw_pixel(Screen *tela, int x, int y, char character);
void screen_present(Screen *tela);
Screen* screen_new(int height, int width);
void screen_clear(Screen *tela, char character);

#endif // SCREEN_H_INCLUDED
