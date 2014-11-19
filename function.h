#ifndef FUNCTION_H
#define FUNCTION_H

#include "structures.h"
#include "list.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

function_t emptyFunction();
function_t *function_with_id(list_t *funclist, int id);
BOOL calc_val_bool(void *obj, void *data);
void calc_val(void *obj, void *data);
void calcVals(int funccount, function_t func[], window_info_t *winfo);
void cleanUp(function_t *func);
void draw_plot(void *obj, void *data);
void drawTicks(plot_info_t info, window_info_t *winfo, SDL_Surface *screen);
void drawAxes(plot_info_t info, window_info_t *winfo, SDL_Surface *screen);
void draw_tangent(void *obj, void *data);
void draw_crosshair(void *obj, void *data);
void rescale_winfo(void *obj, void *data);
void print_vals(list_t *funclist, bundled_info_t *bit);

#endif