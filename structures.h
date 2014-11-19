#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

typedef char BOOL;
#define YES 1
#define NO 0

typedef struct {
	unsigned char r, g, b;
} color_t;

typedef struct {
	double start;
	double end;
	double max;
	double min;
	double step;

	BOOL cust_bounds;

	int width;
	int height;

	char *caption;

	BOOL no_axes;
	double x_tick;
	double y_tick;
	BOOL autotick;
	BOOL aspect;

	color_t axes_col;
	color_t back_col;
	color_t hair_col;

	BOOL default_title;
	BOOL debug;
	BOOL console;
} window_info_t;

typedef struct {
	double offset;
	double x_axis;
	double y_axis;
	double x_scale;
	double y_scale;
} plot_info_t;

typedef struct {
	char *frmt;
	double *vals;

	color_t plot_col;
	color_t shade_col;

	BOOL plot_on_top;
	BOOL discreet;

	double bound_left;
	double bound_right;
	BOOL bounded;
	BOOL show_nan;
	BOOL show_hair;
	BOOL show_coords;
	BOOL use_js;
	BOOL show_tan;
	BOOL shade;
	BOOL cust_var;
	BOOL free_frmt;

	int function_id;
} function_t;

typedef struct {
	char *txt;
	
	int fontsize;
	color_t text_col;
	
	int x, y;
	int label_id;
} label_t;

typedef struct {
	plot_info_t info;
	window_info_t *winfo;
	SDL_Surface *screen;
	TTF_Font *font;
	int x;
} bundled_info_t;

#endif