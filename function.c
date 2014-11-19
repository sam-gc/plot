#include <stdlib.h>
#include "function.h"
#include "structures.h"
#include "tools.h"
#include "sy_parser.h"
#include "list.h"

int function_id = 0;
function_t emptyFunction()
{
	function_t func = {NULL, NULL, {255, 255, 255}, {230, 230, 230}, NO, NO, 0, 0, NO, NO, YES, YES, NO, NO, NO, NO, NO, function_id++};
	return func;
}

function_t *function_with_id(list_t *funclist, int id)
{
	node_t *node;
	for(node = funclist->head; node; node = node->right)
	{
		function_t *func = (function_t *)node->obj;
		if(func->function_id == id)
			return func;
	}

	return NULL;
}

void rescale_winfo(void *obj, void *data)
{
	function_t *func = (function_t *)obj;
	window_info_t *winfo = (window_info_t *)data;

	if(winfo->cust_bounds)
		return;

	int i;
	for(i = 0; i < winfo->width; i++)
	{
		if(func->vals[i] > winfo->max)
			winfo->max = func->vals[i];
		if(func->vals[i] < winfo->min)
			winfo->min = func->vals[i];
	}
}

void calc_val(void *obj, void *data)
{
	calc_val_bool(obj, data);
}

BOOL calc_val_bool(void *obj, void *data)
{
	function_t *func = (function_t *)obj;
	window_info_t *winfo = (window_info_t *)data;

	double step = (winfo->end - winfo->start) / winfo->width;

	func->vals = malloc(sizeof(double) * winfo->width);

	sy_error_t error;
	sy_node_t *tree = sy_parse_string(func->frmt, &error);
	if(!tree)
	{
		printf("\n%s\n", func->frmt);
		int i;
		for(i = 0; i < error.location; i++)
			printf(" ");
		printf("^ ~%s\n", error.message);
		return NO;
	}

	int i;
	for(i = 0; i < winfo->width; i++)
	{
		double x = step * i + winfo->start;
		func->vals[i] = sy_evaluate(tree, x);

		//printf("%lf\t%lf\t%lf\n", x, eval(tree, x), step);

		if(winfo->cust_bounds)
			continue;

		if(func->vals[i] > winfo->max)
			winfo->max = func->vals[i];
		if(func->vals[i] < winfo->min)
			winfo->min = func->vals[i];
	}

	sy_free(tree);
	return YES;
}

void cleanUp(function_t *func)
{
	free(func->vals);
	if(func->free_frmt)
		free(func->frmt);
}

void shadeWith(int ypt, int xpt, int xaxis, SDL_Surface *screen, color_t col)
{
	char target = xpt % 2;

	BOOL below = ypt < xaxis;

	int y;
	for(y = xaxis; (below && y > ypt) || (!below && y < ypt); y += below ? -1 : 1)
	{
		if(y % 2 == target)
		{
			SDL_Rect dest = {xpt, y, 1, 1};
			SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, col.r, col.g, col.b));
		}
	}
}

void draw_plot(void *obj, void *data)
{
	function_t *func = (function_t *)obj;
	bundled_info_t *bi = (bundled_info_t *)data;

	plot_info_t info = bi->info;
	window_info_t *winfo = bi->winfo;
	SDL_Surface *screen = bi->screen;

	color_t plot = func->plot_col;

	double orig_y_scale = ((winfo->max - winfo->min) / winfo->height);

	int i;
	for(i = 0; i < winfo->width; i++)
	{
		double x_val = i * info.x_scale - info.x_axis * info.x_scale;
		if(func->bounded)
		{
			if(x_val < func->bound_left || x_val > func->bound_right)
				continue;
		}

		if(!func->show_nan && (func->vals[i] != func->vals[i] || (i < winfo->width - 1 && func->vals[i + 1] != func->vals[i + 1])))
			continue;

		int ypt = winfo->height - (func->vals[i] / info.y_scale) - (info.offset / orig_y_scale);

		int ht = 1;

		if(!func->discreet)
		{
			int npt = (i < winfo->width - 1 ? winfo->height - ((func->vals[i + 1] / info.y_scale)) - (info.offset / orig_y_scale): ypt);
			ht = abs(great(ypt, npt) - less(npt, ypt));
			ht = ht == 0 ? 1 : ht;

			if(ht > winfo->height)
				continue;

			ypt = less(npt, ypt);
		}

		if(func->shade)
			shadeWith(ypt, i, info.y_axis, screen, func->shade_col);

		SDL_Rect dest = {i, ypt, 1, ht};
		SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, plot.r, plot.g, plot.b));
	}
}

void drawTicks(plot_info_t info, window_info_t *winfo, SDL_Surface *screen)
{
	color_t axes = winfo->axes_col;

	if(winfo->x_tick)
	{
		double step = winfo->x_tick / info.x_scale;
		double xt;
		for(xt = info.x_axis; xt < winfo->width; xt += step)
		{
			SDL_Rect dest = {xt, info.y_axis - 2, 1, 5};
			SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, axes.r, axes.g, axes.b));
		}
		for(xt = info.x_axis; xt >= 0; xt -= step)
		{
			SDL_Rect dest = {xt, info.y_axis - 2, 1, 5};
			SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, axes.r, axes.g, axes.b));
		}
	}

	if(winfo->y_tick)
	{
		double step = winfo->y_tick / info.y_scale;
		double yt;
		for(yt = info.y_axis; yt < winfo->height; yt += step)
		{
			SDL_Rect dest = {info.x_axis - 2, yt, 5, 1};
			SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, axes.r, axes.g, axes.b));
		}
		for(yt = info.y_axis; yt > 0; yt -= step)
		{
			SDL_Rect dest = {info.x_axis - 2, yt, 5, 1};
			SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, axes.r, axes.g, axes.b));
		}
	}
}

void drawAxes(plot_info_t info, window_info_t *winfo, SDL_Surface *screen)
{
	if(winfo->no_axes)
		return;

	color_t axes = winfo->axes_col;

	SDL_Rect x_axis_rect = {info.x_axis, 0, 1, winfo->height};
	SDL_Rect y_axis_rect = {0, info.y_axis, winfo->width, 1};
	SDL_FillRect(screen, &x_axis_rect, SDL_MapRGB(screen->format, axes.r, axes.g, axes.b));
	SDL_FillRect(screen, &y_axis_rect, SDL_MapRGB(screen->format, axes.r, axes.g, axes.b));
}

void draw_tangent(void *obj, void *data)
{
	function_t *func = (function_t *)obj;
	bundled_info_t *bit = (bundled_info_t *)data;
	window_info_t *winfo = bit->winfo;
	int loc = bit->x;
	SDL_Surface *screen = bit->screen;
	plot_info_t info = bit->info;

	if(loc == winfo->width - 1 || loc == 0)
		return;

	if(!func->show_tan)
		return;

	function_t tangent = emptyFunction();
	tangent.plot_col = func->plot_col;

	double vals[winfo->width];

	double slope_right = (func->vals[loc + 1] - func->vals[loc]);
	double slope_left = (func->vals[loc] - func->vals[loc - 1]);

	double slope = (slope_right + slope_left) / 2;

	tangent.vals = vals;
	tangent.vals[loc] = func->vals[loc];

	int i;
	for(i = loc; i < winfo->width - 1; i++)
		tangent.vals[i + 1] = tangent.vals[i] + slope;
	for(i = loc; i > 0; i--)
		tangent.vals[i - 1] = tangent.vals[i] - slope;

	draw_plot((voidptr)&tangent, data);
}

void draw_crosshair(void *obj, void *data)
{
	function_t *func = (function_t *)obj;
	bundled_info_t *bit = (bundled_info_t *)data;
	window_info_t *winfo = bit->winfo;
	int loc = bit->x;
	SDL_Surface *screen = bit->screen;
	plot_info_t info = bit->info;

	double orig_y_scale = ((winfo->max - winfo->min) / winfo->height);
	color_t hair_col = winfo->hair_col;

	if(!func->show_hair)
		return;

	if(func->vals[loc] != func->vals[loc] || (func->discreet && loc < winfo->width - 1 && func->vals[loc + 1] != func->vals[loc + 1]))
		return;

	int ypt = winfo->height - (func->vals[loc] / info.y_scale) - (info.offset / orig_y_scale);
	int ht = 1;

	if(!func->discreet)
	{
		int npt = (loc < winfo->width - 1 ? winfo->height - ((func->vals[loc + 1] / info.y_scale)) - (info.offset / orig_y_scale): ypt);
		ht = abs(great(ypt, npt) - less(npt, ypt));
		ht = ht == 0 ? 1 : ht;

		ypt = (npt + ypt) / 2;
	}

	SDL_Rect top = {loc, ypt - 4, 1, 4};
	SDL_Rect right = {loc + 1, ypt, 4, 1};
	SDL_Rect bottom = {loc, ypt + 1, 1, 4};
	SDL_Rect left = {loc - 4, ypt, 4, 1};

	SDL_FillRect(screen, &top, SDL_MapRGB(screen->format, hair_col.r, hair_col.g, hair_col.b));
	SDL_FillRect(screen, &right, SDL_MapRGB(screen->format, hair_col.r, hair_col.g, hair_col.b));
	SDL_FillRect(screen, &bottom, SDL_MapRGB(screen->format, hair_col.r, hair_col.g, hair_col.b));
	SDL_FillRect(screen, &left, SDL_MapRGB(screen->format, hair_col.r, hair_col.g, hair_col.b));
}

void print_vals(list_t *funclist, bundled_info_t *bit)
{
	int funccount = list_count(funclist);
	window_info_t *winfo = bit->winfo;
	SDL_Surface *screen = bit->screen;
	TTF_Font *font = bit->font;
	int loc = bit->x;

	SDL_Surface *faces[funccount];

	double step = (winfo->end - winfo->start) / winfo->width;

	node_t *node = funclist->head;
	int i;
	for(i = 0, node; node; node = node->right, i++)
	{
		function_t *func = (function_t *)node->obj;

		if(!func->show_coords ||(func->vals[loc] != func->vals[loc] && !func->show_nan))
		{
			faces[i] = NULL;
			continue;
		}

		char t[80];

		double x = loc * step + winfo->start;

		sprintf(t, "(%lf,%lf)", x, func->vals[loc]);

		SDL_Color col = {func->plot_col.r, func->plot_col.g, func->plot_col.b};
		faces[i] = TTF_RenderText_Solid(font, t, col);
	}

	int x = winfo->width - 10;
	for(i = funccount - 1; i >= 0; i--)
	{
		SDL_Surface *surf = faces[i];

		if(!surf)
			continue;

		x -= surf->w;
		blit(surf, screen, x, winfo->height - surf->h - 5);
		x -= 10;
		SDL_FreeSurface(surf);
	}
}