#ifndef TOOLS_H
#define TOOLS_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "structures.h"
#include "list.h"

int less(int a, int b);
int great(int a, int b);
int abs(int a);
double greatf(double a, double b);
window_info_t emptyWindow();
label_t emptyLabel();
label_t *label_with_id(list_t *list, int idx);
SDL_Surface *createSurface(int width, int height);
void copySurface(SDL_Surface *source, SDL_Surface *dest);
void blit(SDL_Surface *source, SDL_Surface *dest, int x, int y);
void draw_label(void *obj, void *data);
void drawLabels(label_t labels[], int labelcount, SDL_Surface *screen);
void print_debug_coords(SDL_Surface *screen, TTF_Font *font, int x, int y);
char *get_filename();

#endif