#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>

typedef char BOOL;
#define YES 1
#define NO 0

typedef struct {
	unsigned char r, g, b;
} color_t;

typedef struct {
	double offset;
	double x_axis;
	double y_axis;
	double x_scale;
	double y_scale;
} plot_info_t;

typedef struct {
	double start;
	double end;
	double max;
	double min;
	double step;
	char *frmt;
	BOOL no_axes;

	int window_width;
	int window_height;

	color_t plot_col;
	color_t axes_col;
	color_t back_col;

	BOOL cust_bounds;

	double x_tick;
	double y_tick;

	BOOL autotick;
	BOOL plot_on_top;
	BOOL discreet;
	BOOL aspect;
} function_t;

function_t blank_function = {-10, 10, 0, 0, 0, NULL, NO, 600, 400, {255, 255, 255}, {255, 0 , 255}, {0, 0, 0}, NO, 0, 0, NO, NO, NO};

SDL_Surface *initSDL(char *func, int width, int height)
{
	char title[80];
	strcpy(title, "Plot: ");
	strcat(title, func);
	SDL_Init( SDL_INIT_VIDEO );
	SDL_WM_SetCaption(title, NULL);
	return SDL_SetVideoMode( width, height, 32, SDL_SWSURFACE );
}

color_t makeColor(unsigned char r, unsigned char g, unsigned char b)
{
	color_t col = {r, g, b};
	return col;
}

function_t parseArgs(int argc, char *argv[])
{
	function_t func = blank_function;
	func.frmt = argv[1];

	int i;
	for(i = 0; i < argc; i++)
	{
		char *curr = argv[i];
		char *next = i < argc - 1 ? argv[i + 1] : NULL;

		if(strcmp(curr, "--range") == 0)
			sscanf(next, "%lf,%lf", &func.start, &func.end);
		else if(strcmp(curr, "--bounds") == 0)
		{
			sscanf(next, "%lf,%lf", &func.min, &func.max);
			func.cust_bounds = YES;
		}
		else if(strcmp(curr, "--noaxes") == 0)
			func.no_axes = YES;
		else if(strcmp(curr, "--plotcolor") == 0)
		{
			sscanf(next, "%hhu,%hhu,%hhu", &func.plot_col.r, &func.plot_col.g, &func.plot_col.b);
		}
		else if(strcmp(curr, "--axescolor") == 0)
		{
			sscanf(next, "%hhu,%hhu,%hhu", &func.axes_col.r, &func.axes_col.g, &func.axes_col.b);
		}
		else if(strcmp(curr, "--backcolor") == 0)
		{
			sscanf(next, "%hhu,%hhu,%hhu", &func.back_col.r, &func.back_col.g, &func.back_col.b);
		}
		else if(strcmp(curr, "--window") == 0)
			sscanf(next, "%d,%d", &func.window_width, &func.window_height);
		else if(strcmp(curr, "--xtick") == 0)
			func.x_tick = atof(next);
		else if(strcmp(curr, "--ytick") == 0)
			func.y_tick = atof(next);
		else if(strcmp(curr, "--autotick") == 0)
			func.autotick = YES;
		else if(strcmp(curr, "--plotontop") == 0)
			func.plot_on_top = YES;
		else if(strcmp(curr, "--discreet") == 0)
			func.discreet = YES;
		else if(strcmp(curr, "--aspect") == 0)
			func.aspect = YES;
	}

	func.step = (func.end - func.start) / func.window_width;

	return func;
}

int less(int a, int b)
{
	return a < b ? a : b;
}

int great(int a, int b)
{
	return a > b ? a : b;
}

int abs(int a)
{
	return a < 0 ? a * -1 : a;
}

double greatf(double a, double b)
{
	return a > b ? a : b;
}

void drawPlot(function_t *func, plot_info_t info, double values[], SDL_Surface *screen)
{
	color_t plot = func->plot_col;
	int i;
	double orig_y_scale = ((func->max - func->min) / func->window_height);
	for(i = 0; i < func->window_width; i++)
	{
		//int ypt = func->window_height - ((values[i] / info.y_scale) + (info.offset / info.y_scale));
		int ypt = func->window_height - (values[i] / info.y_scale) - (info.offset / orig_y_scale);
		int ht = 1;

		if(!func->discreet)
		{
			//int npt = (i < func->window_width - 1 ? func->window_height - ((values[i + 1] / info.y_scale) + (info.offset / info.y_scale)) : ypt);
			int npt = (i < func->window_width - 1 ? func->window_height - ((values[i + 1] / info.y_scale)) - (info.offset / orig_y_scale): ypt);
			ht = abs(great(ypt, npt) - less(npt, ypt));
			ht = ht == 0 ? 1 : ht;

			ypt = less(npt, ypt);
		}

		SDL_Rect dest = {i, ypt, 1, ht};
		SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, plot.r, plot.g, plot.b));
		SDL_Flip(screen);
	}
}

void drawTicks(function_t *func, plot_info_t info, SDL_Surface *screen)
{
	color_t axes = func->axes_col;

	if(func->x_tick)
	{
		double step = func->x_tick / info.x_scale;
		double xt;
		for(xt = info.x_axis; xt < func->window_width; xt += step)
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

	if(func->y_tick)
	{
		double step = func->y_tick / info.y_scale;
		double yt;
		for(yt = info.y_axis; yt < func->window_height; yt += step)
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

void drawAxes(function_t *func, plot_info_t info, SDL_Surface *screen)
{
	if(func->no_axes)
		return;

	color_t axes = func->axes_col;

	SDL_Rect x_axis_rect = {info.x_axis, 0, 1, func->window_height};
	SDL_Rect y_axis_rect = {0, info.y_axis, func->window_width, 1};
	SDL_FillRect(screen, &x_axis_rect, SDL_MapRGB(screen->format, axes.r, axes.g, axes.b));
	SDL_FillRect(screen, &y_axis_rect, SDL_MapRGB(screen->format, axes.r, axes.g, axes.b));
}

void plotFunction(function_t *func, double values[], SDL_Surface *screen)
{
	plot_info_t info;
	info.offset = (func->min < 0 ? func->min * -1 : 0);
	info.x_axis = (func->start < 0 && func->end > 0 ? ((-1 * func->start) / (-1 * func->start + func->end)) * func->window_width : -1);
	info.y_axis = (func->min < 0 && func->max > 0 ? (func->max / (func->max + func->min * -1) * func->window_height) : -1);

	info.x_scale = (func->end - func->start) / func->window_width;
	info.y_scale = (func->aspect ? info.x_scale : (func->max - func->min) / func->window_height);

	/*
	if(func->aspect)
		info.offset = info.x_axis;*/

	color_t back = func->back_col;
	SDL_Rect back_rect = {0, 0, func->window_width, func->window_height};
	SDL_FillRect(screen, &back_rect, SDL_MapRGB(screen->format, back.r, back.g, back.b));

	if(func->plot_on_top)
	{
		drawTicks(func, info, screen);
		drawAxes(func, info, screen);
	}

	drawPlot(func, info, values, screen);

	if(func->plot_on_top)
		return;

	drawTicks(func, info, screen);
	drawAxes(func, info, screen);
}

int main(int argc, char *argv[])
{
	function_t func = parseArgs(argc, argv);

	putenv("SDL_VIDEO_CENTERED=1");
	SDL_Surface *screen = initSDL(argv[1], func.window_width, func.window_height);

	char call[400];
	sprintf(call, "node ~/bin/parse.js \"%s\" %lf %lf %lf %d", func.frmt, func.start, func.end, func.step, func.window_width);

	FILE *result = popen(call, "r");
	double values[func.window_width];

	int i;
	for(i = 0; i < func.window_width; i++)
	{
		fscanf(result, "%lf", &values[i]);

		if(func.cust_bounds)
			continue;

		if(values[i] > func.max)
			func.max = values[i];
		else if(values[i] < func.min)
			func.min = values[i];
	}

	pclose(result);

	if(!func.cust_bounds)
	{
		func.min -= ((func.max - func.min) / func.window_height) * 40;
		func.max += ((func.max - func.min) / func.window_height) * 40;
	}

	if(func.autotick)
	{
		int tickCount = func.window_width / 20;
		double x = (func.end - func.start) / tickCount;

		tickCount = func.window_height / 20;
		double y = (func.max - func.min) / tickCount;

		double val = greatf(x, y);
		func.x_tick = val;
		func.y_tick = val;
	}

	plotFunction(&func, values, screen);
	SDL_Flip(screen);

	SDL_Event evt;
	while(SDL_WaitEvent(&evt))
	{
		switch(evt.type)
		{
			case SDL_QUIT:
				SDL_Quit();
				return 0;
				break;
		}
	}

	SDL_FreeSurface(screen);
	SDL_Quit();
	return 0;
}
