#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <gtk/gtk.h>

#include "build.h"
#include "structures.h"
#include "tools.h"
#include "function.h"
#include "plot_events.h"
#include "list.h"
#include "linenoise.h"

void print_usage(char *command);

typedef enum prs {FUNCTION, LABEL} PARSE_TYPE;

SDL_Surface *initSDL(window_info_t *winfo)
{
	SDL_Init( SDL_INIT_VIDEO );
	TTF_Init();

	SDL_WM_SetCaption(winfo->caption, NULL);
	return SDL_SetVideoMode( winfo->width, winfo->height, 32, SDL_SWSURFACE );
}

void parseWinfoArg(char *curr, char *next, window_info_t *winfo)
{
	if(strcmp(curr, "--xrange") == 0)
		sscanf(next, "%lf,%lf", &winfo->start, &winfo->end);
	else if(strcmp(curr, "--yrange") == 0)
	{
		sscanf(next, "%lf,%lf", &winfo->min, &winfo->max);
		winfo->cust_bounds = YES;
	}
	else if(strcmp(curr, "--noaxes") == 0)
		winfo->no_axes = !winfo->no_axes;
	else if(strcmp(curr, "--axescolor") == 0)
		sscanf(next, "%hhu,%hhu,%hhu", &winfo->axes_col.r, &winfo->axes_col.g, &winfo->axes_col.b);
	else if(strcmp(curr, "--backcolor") == 0)
		sscanf(next, "%hhu,%hhu,%hhu", &winfo->back_col.r, &winfo->back_col.g, &winfo->back_col.b);
	else if(strcmp(curr, "--haircolor") == 0)
		sscanf(next, "%hhu,%hhu,%hhu", &winfo->hair_col.r, &winfo->hair_col.g, &winfo->hair_col.b);
	else if(strcmp(curr, "--window") == 0)
		sscanf(next, "%d,%d", &winfo->width, &winfo->height);
	else if(strcmp(curr, "--xtick") == 0)
		winfo->x_tick = atof(next);
	else if(strcmp(curr, "--ytick") == 0)
		winfo->y_tick = atof(next);
	else if(strcmp(curr, "--autotick") == 0)
	{
		if(winfo->autotick)
		{
			winfo->x_tick = 0;
			winfo->y_tick = 0;
		}
		winfo->autotick = !winfo->autotick;
	}
	else if(strcmp(curr, "--aspect") == 0)
		winfo->aspect = !winfo->aspect;
	else if(strcmp(curr, "--title") == 0)
		winfo->caption = next;
	else if(strcmp(curr, "--debug") == 0)
		winfo->debug = !winfo->debug;
	else if(strcmp(curr, "--console") == 0)
		winfo->console = YES;
}

void parseLabelArg(int argc, char *argv[], label_t *label, window_info_t *winfo, int idx)
{
	char *curr = argv[idx];
	char *next = idx < argc - 1 ? argv[idx + 1] : NULL;
	
	parseWinfoArg(curr, next, winfo);
	
	if(strcmp(curr, "--color") == 0)
		sscanf(next, "%hhu,%hhu,%hhu", &label->text_col.r, &label->text_col.g, &label->text_col.b);
	if(strcmp(curr, "--loc") == 0)
		sscanf(next, "%d,%d", &label->x, &label->y);
	if(strcmp(curr, "--size") == 0)
		label->fontsize = atoi(next);
}

void parseFunctionArg(int argc, char *argv[], function_t *func, window_info_t *winfo, int idx)
{
	char *curr = argv[idx];
	char *next = idx < argc - 1 ? argv[idx + 1] : NULL;
	
	parseWinfoArg(curr, next, winfo);
	
	if(strcmp(curr, "--plotcolor") == 0)
		sscanf(next, "%hhu,%hhu,%hhu", &func->plot_col.r, &func->plot_col.g, &func->plot_col.b);
	else if(strcmp(curr, "--shadecolor") == 0)
		sscanf(next, "%hhu,%hhu,%hhu", &func->shade_col.r, &func->shade_col.g, &func->shade_col.b);
	else if(strcmp(curr, "--shownan") == 0)
		func->show_nan = YES;
	else if(strcmp(curr, "--bounds") == 0)
	{
		sscanf(next, "%lf,%lf", &func->bound_left, &func->bound_right);
		func->bounded = YES;
	}
	else if(strcmp(curr, "--nocoords") == 0)
		func->show_coords = NO;
	else if(strcmp(curr, "--nohair") == 0)
		func->show_hair = NO;
	else if(strcmp(curr, "--tangent") == 0)
		func->show_tan = YES;
	else if(strcmp(curr, "--plotontop") == 0)
		func->plot_on_top = YES;
	else if(strcmp(curr, "--discreet") == 0)
		func->discreet = YES;
	else if(strcmp(curr, "--static") == 0)
	{
		func->show_coords = NO;
		func->show_hair = NO;
	}
	else if(strcmp(curr, "-v") == 0)
	{
		char var = next[0];
		int j;
		for(j = 0; j < strlen(func->frmt); j++)
		{
			if(func->frmt[j] == var)
				func->frmt[j] = '$';
		}

		func->cust_var = YES;
	}
	else if(strcmp(curr, "-js") == 0)
		func->use_js = YES;
	else if(strcmp(curr, "--shade") == 0)
		func->shade = YES;
}

int listen(void *data)
{
	window_info_t *winfo = (window_info_t *)data;

	char *line;
	//strcpy(text, "heyo");

	while((line = linenoise("> ")))
	{
		if(line[0] != '\0' && line[0] != '/')
			linenoiseHistoryAdd(line);

		char text[1000];
		strcpy(text, line);
		free(line);

		//int i;
		//for(i = 0; text[i] != '\n' && text[i] != '\0' && i < 100; i++);
		//text[i] = '\0';

		char *pch;

		pch = strtok(text, " ");

		if(strcmp(pch, "f") == 0)
		{
			function_t func = emptyFunction();
			printf("[%d]\n", func.function_id);

			char *nxt = strtok(NULL, " ");
			char *frmt = malloc(strlen(nxt) + 1);
			strcpy(frmt, nxt);

			func.frmt = frmt;
			func.free_frmt = YES;

			pch = strtok(NULL, " ");

			while(pch)
			{
				char *argv[2];
				argv[0] = pch;
				argv[1] = pch = strtok(NULL, " ");
				parseFunctionArg(2, argv, &func, NULL, 0);
			}
			function_t *funcmem = malloc(sizeof(function_t));
			memcpy(funcmem, &func, sizeof(function_t));
			SDL_Event evt = build_sdl_event(CMD_FUNCEVENT, (voidptr)funcmem);
			SDL_PushEvent(&evt);
		}
		else if(strcmp(pch, "l") == 0)
		{
			label_t lab = emptyLabel();
			printf("(%d)\n", lab.label_id);

			char *nxt = strtok(NULL, "\"");
			char *txt = malloc(strlen(nxt) + 1);
			strcpy(txt, nxt);

			lab.txt = txt;

			pch = strtok(NULL, " ");

			while(pch)
			{
				char *argv[2];
				argv[0] = pch;
				argv[1] = pch = strtok(NULL, " ");
				parseLabelArg(2, argv, &lab, NULL, 0);
			}
			label_t *labmem = malloc(sizeof(label_t));
			memcpy(labmem, &lab, sizeof(label_t));
			SDL_Event evt = build_sdl_event(CMD_LABEVENT, (voidptr)labmem);
			SDL_PushEvent(&evt);
		}
		else if(strcmp(pch, "rmf") == 0)
		{
			pch = strtok(NULL, " ");
			if(!pch)
				printf("Usage: rmf <function id>\n");
			else
			{
				int *idx = malloc(sizeof(int));
				*idx = atoi(pch);

				SDL_Event evt = build_sdl_event(CMD_RMFUNCEVENT, (voidptr)idx);
				SDL_PushEvent(&evt);
			}
		}
		else if(strcmp(pch, "rml") == 0)
		{
			pch = strtok(NULL, " ");
			if(!pch)
				printf("Usage: rml <label id>\n");
			else
			{
				int *idx = malloc(sizeof(int));
				*idx = atoi(pch);

				SDL_Event evt = build_sdl_event(CMD_RMLABEVENT, (voidptr)idx);
				SDL_PushEvent(&evt);
			}
		}
		else if(strcmp(pch, "w") == 0)
		{
			while(pch)
			{
				char *next = strtok(NULL, " ");
				parseWinfoArg(pch, next, winfo);
				pch = next;
			}

			SDL_Event evt = build_sdl_event(CMD_WINDOWEVENT, NULL);
			SDL_PushEvent(&evt);
		}

		printf("\n");
	}

	SDL_Event evt;
	evt.type = SDL_QUIT;
	SDL_PushEvent(&evt);
}

int findFor(char *str, int argc, char *argv[])
{
	int count = 0;
	
	int i;
	for(i = 0; i < argc; i++)
	{
		if(strcmp(argv[i], str) == 0)
			count++;
	}
	
	return count;
}

int countFunctions(int argc, char *argv[])
{
	return findFor("-f", argc, argv) + 1;
}

int countLabels(int argc, char *argv[])
{
	return findFor("-l", argc, argv);
}

void generateTitle(char *frmts[], int funccount, window_info_t *winfo)
{
	if(winfo->caption)
		return;

	winfo->default_title = YES;

	char *title = malloc(400);
	strcpy(title, "Plot: ");

	int i;
	for(i = 0; i < funccount; i++)
	{
		strcat(title, frmts[i]);
		strcat(title, "; ");
	}

	winfo->caption = title;
}

void replace_var(function_t *func)
{
	if(!func->cust_var)
	{
		int j;
		for(j = 0; j < strlen(func->frmt); j++)
		{
			if(func->frmt[j] == 'x')
				func->frmt[j] = '$';
		}
	}
}

void setup_window(list_t *funclist, bundled_info_t *bit)
{
	window_info_t *winfo = bit->winfo;

	if(!winfo->cust_bounds)
	{
		winfo->min -= ((winfo->max - winfo->min) / winfo->height) * 40;
		winfo->max += ((winfo->max - winfo->min) / winfo->height) * 40;
	}

	if(winfo->autotick)
	{
		int tickCount = winfo->width / 20;
		double x = (winfo->end - winfo->start) / tickCount;

		tickCount = winfo->height / 20;
		double y = (winfo->max - winfo->min) / tickCount;

		double val = greatf(x, y);
		winfo->x_tick = val;
		winfo->y_tick = val;
	}

	plot_info_t info;
	info.offset = winfo->min * -1;
	info.x_axis = (winfo->start < 0 && winfo->end > 0 ? ((-1 * winfo->start) / (-1 * winfo->start + winfo->end)) * winfo->width : -3);
	info.y_axis = (winfo->min < 0 && winfo->max > 0 ? (winfo->max / (winfo->max + winfo->min * -1) * winfo->height) : -3);

	info.x_scale = (winfo->end - winfo->start) / winfo->width;
	info.y_scale = (winfo->aspect ? info.x_scale : (winfo->max - winfo->min) / winfo->height);

	bit->info = info;
}

void draw(list_t *funclist, list_t *labllist, bundled_info_t *bit)
{
	SDL_Surface *screen = bit->screen;

	color_t back = bit->winfo->back_col;
	SDL_Rect back_rect = {0, 0, bit->winfo->width, bit->winfo->height};
	SDL_FillRect(screen, &back_rect, SDL_MapRGB(screen->format, back.r, back.g, back.b));

	list_for_each(funclist, draw_plot, (voidptr)bit);

	drawAxes(bit->info, bit->winfo, screen);
	drawTicks(bit->info, bit->winfo, screen);

	list_for_each(labllist, draw_label, (voidptr)screen);
}

void remove_broken(void *data)
{
	cleanUp((function_t *)data);
}

int main(int argc, char *argv[])
{
	if(argc == 2)
	{
		if(strcmp(argv[1], "--usage") == 0)
		{
			print_usage(argv[0]);
			return 0;
		}
		else if(strcmp(argv[1], "--version") == 0)
		{
			printf("Version 3.2, build %X\nCreated 2013, Sam Olsen\n", BUILDNUMBER);
			return 0;
		}
	}

	gtk_init(&argc, &argv);
	window_info_t winfo = emptyWindow();

	int funccount = countFunctions(argc, argv);

	list_t funclist = list_list();
	list_t labllist = list_list();
	
	char *frmts[funccount];
	
	PARSE_TYPE currType = FUNCTION;
	function_t currFunc = emptyFunction();
	label_t currLab = emptyLabel();
	int currFuncIdx = 0, currLabIdx = 0;
	
	int i;
	for(i = 0; i < argc; i++)
	{
		char *curr = argv[i];
		
		if(strcmp(curr, "-f") == 0 || (i == 0 && argc > 1))
		{
			if(currType == FUNCTION && i != 0)
			{
				replace_var(&currFunc);
				function_t *func = malloc(sizeof(function_t));
				memcpy(func, &currFunc, sizeof(function_t));
				list_add(&funclist, func);
				currFuncIdx++;
				//funcs[currFuncIdx++] = currFunc;
			}
			else if(currType == LABEL)
			{
				label_t *lab = malloc(sizeof(label_t));
				memcpy(lab, &currLab, sizeof(label_t));
				list_add(&labllist, lab);
				//labels[currLabIdx++] = currLab;
			}
				
			currType = FUNCTION;
			currFunc = emptyFunction();
			currFunc.frmt = argv[++i];
			frmts[currFuncIdx] = argv[i];
			
			continue;
		}
		else if(strcmp(curr, "-l") == 0)
		{
			if(currType == FUNCTION)
			{
				replace_var(&currFunc);
				function_t *func = malloc(sizeof(function_t));
				memcpy(func, &currFunc, sizeof(function_t));
				list_add(&funclist, func);
				//funcs[currFuncIdx++] = currFunc;
			}
			else if(currType == LABEL)
			{
				label_t *lab = malloc(sizeof(label_t));
				memcpy(lab, &currLab, sizeof(label_t));
				list_add(&labllist, lab);
				//labels[currLabIdx++] = currLab;
			}
			
			currType = LABEL;
			currLab = emptyLabel();
			currLab.txt = argv[++i];
			
			continue;
		}
		
		if(currType == FUNCTION)
		{
			parseFunctionArg(argc, argv, &currFunc, &winfo, i);
		}
		else if(currType == LABEL)
		{
			parseLabelArg(argc, argv, &currLab, &winfo, i);
		}
	}
	
	if(argc > 1)
	{
		if(currType == FUNCTION)
		{
			replace_var(&currFunc);
			function_t *func = malloc(sizeof(function_t));
			memcpy(func, &currFunc, sizeof(function_t));
			list_add(&funclist, func);
			//funcs[currFuncIdx++] = currFunc;
		}
		else if(currType == LABEL)
		{
			label_t *lab = malloc(sizeof(label_t));
			memcpy(lab, &currLab, sizeof(label_t));
			list_add(&labllist, lab);
			//labels[currLabIdx++] = currLab;
		}
	}

	generateTitle(frmts, funccount, &winfo);

	winfo.step = (winfo.end - winfo.start) / winfo.width;

	//calcVals(funccount, funcs, &winfo);

	putenv("SDL_VIDEO_CENTERED=1");
	SDL_Surface *screen = initSDL(&winfo);

	bundled_info_t setupbit;
	setupbit.winfo = &winfo;
	setupbit.screen = screen;

	list_for_each_bool(&funclist, calc_val_bool, (voidptr)&winfo, remove_broken);

	setup_window(&funclist, &setupbit);

	draw(&funclist, &labllist, &setupbit);

	SDL_Flip(screen);

	SDL_Surface *graph = createSurface(winfo.width, winfo.height);
	copySurface(screen, graph);

	TTF_Font *font = TTF_OpenFont("AnonPro.ttf", 11);

	BOOL finished = NO;

	SDL_Thread *listenThread = NULL;
	if(winfo.console || argc == 1)
		SDL_CreateThread(listen, &winfo);

	SDL_Event evt;
	while(SDL_WaitEvent(&evt))
	{
		switch(evt.type)
		{
			case SDL_QUIT:
				finished = YES;
			break;
			case SDL_MOUSEMOTION:
			{
				copySurface(graph, screen);
				int x = evt.motion.x;
				int y = evt.motion.y;
				setupbit.font = font;
				setupbit.x = x;
				list_for_each(&funclist, draw_tangent, (voidptr)&setupbit);
				list_for_each(&funclist, draw_crosshair, (voidptr)&setupbit);
				print_vals(&funclist, &setupbit);

				if(winfo.debug)
					print_debug_coords(screen, font, x, y);
				SDL_Flip(screen);
			}
			break;
			case SDL_ACTIVEEVENT:
				copySurface(graph, screen);
				SDL_Flip(screen);
			break;
			case SDL_KEYDOWN:
				if(evt.key.keysym.sym == SDLK_q)
					finished = YES;
				else if(evt.key.keysym.sym == SDLK_s)
				{
					char *filename = get_filename();
					if(filename)
					{
						SDL_SaveBMP(screen, filename);
						free(filename);
					}
				}
				//else
					//printf("%d\n", evt.key.keysym.sym);
			break;
			case CMD_FUNCEVENT:
			{
				winfo.max = 0;
				winfo.min = 0;
				function_t *func = (function_t *)evt.user.data1;
				replace_var(func);
				list_add(&funclist, (voidptr)func);
				calc_val((voidptr)func, (voidptr)&winfo);
				list_for_each(&funclist, rescale_winfo, (voidptr)&winfo);
				setup_window(&funclist, &setupbit);

				draw(&funclist, &labllist, &setupbit);

				SDL_Flip(screen);

				copySurface(screen, graph);

				//SDL_WM_SetCaption((char *)evt.user.data1, NULL);
			}
			break;
			case CMD_LABEVENT:
				list_add(&labllist, evt.user.data1);
				draw(&funclist, &labllist, &setupbit);
				SDL_Flip(screen);
				copySurface(screen, graph);
			break;
			case CMD_RMFUNCEVENT:
			{
				int idx = *((int *)evt.user.data1);
				free(evt.user.data1);

				winfo.max = 0;
				winfo.min = 0;

				function_t *ftorm = function_with_id(&funclist, idx);
				if(!ftorm)
					break;

				list_remove_obj(&funclist, ftorm);
				cleanUp(ftorm);
				free(ftorm);
				list_for_each(&funclist, rescale_winfo, (voidptr)&winfo);
				setup_window(&funclist, &setupbit);

				draw(&funclist, &labllist, &setupbit);

				SDL_Flip(screen);
				copySurface(screen, graph);
			}
			break;
			case CMD_RMLABEVENT:
			{
				int idx = *((int *)evt.user.data1);
				free(evt.user.data1);

				label_t *ltorm = label_with_id(&labllist, idx);
				if(!ltorm)
					break;

				list_remove_obj(&labllist, ltorm);
				draw(&funclist, &labllist, &setupbit);

				SDL_Flip(screen);
				copySurface(screen, graph);
			}
			break;
			case CMD_WINDOWEVENT:
			{
				node_t *node = funclist.head;

				for(node; node; node = node->right)
					free(((function_t *)node->obj)->vals);

				if(!winfo.cust_bounds)
				{
					winfo.max = 0;
					winfo.min = 0;
				}
				list_for_each(&funclist, calc_val, (voidptr)&winfo);
				setup_window(&funclist, &setupbit);

				draw(&funclist, &labllist, &setupbit);

				SDL_Flip(screen);
				copySurface(screen, graph);
			}
			break;
		}



		if(finished)
			break;
	}
	
	TTF_CloseFont(font);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(graph);

	if(listenThread)
		SDL_KillThread(listenThread);

	TTF_Quit();
	SDL_Quit();


	node_t *node = funclist.head;

	for(node; node; node = node->right)
		cleanUp((function_t *)node->obj);

	list_free(&funclist);
	list_free(&labllist);


	if(winfo.default_title)
		free(winfo.caption);

	return 0;
}

void print_usage(char *command)
{
	printf("Usage: %s <function> [args] [-f] <another function> [args] [-l] <label text> [args]\n"
"\n"
"<mandatory>\n"
"[optional]\n"
"\n"
"Window flags:\n"
"(to be used anywhere)\n"
"--xrange <min,max>   where min and max represent the bounds on the xrange\n"
"--yrange <min,max>   to set bounds on the yrange\n"
"--noaxes             hides the axes\n"
"--axescolor <r,g,b>  sets the color of the axes\n"
"--backcolor <r,g,b>  sets the background color\n"
"--haircolor <r,g,b>  sets the crosshair color\n"
"--window <w,h>       sets the width and heigt of the window\n"
"--xtick <i>          sets the interval of ticks on the x-axis\n"
"--ytick <i>          \"                               \" y-axis\n"
"--autotick           selects a size for axes ticks, consistent for both axes\n"
"--aspect             makes the plot aspect (x & y scale are the same)\n"
"--title <text>       sets the window title\n"
"--debug              shows the screen coordinates in the top left corner\n"
"\n"
"Function flags:\n"
"(following intial call or after -f)\n"
"--plotcolor <r,g,b>  sets the color of the function plot\n"
"--shadecolor <r,g,b> sets the color of the shading\n"
"--shownan            shows nan (not a number) values (i.e. 1/0)\n"
"--bounds <min,max>   puts bounds on the function\n"
"--nocoords           don't show coordinates in bottom left\n"
"--nohair             don't show the crosshair\n"
"--tangent            draw a tangent line at the cursor\n"
"--discreet           don't connect the dots\n"
"--static             don't show the crosshair or the coordinates\n"
"-v <character>       makes the given character the variable (default x)\n"
"-js                  use node.js to parse the function\n"
"--shade              shades under the curve\n"
"\n"
"Label flags:\n"
"(following -l)\n"
"--color <r,g,b>      sets the color of the text\n"
"--loc <x,y>          sets the location in the window of the text\n"
"--size <i>           sets the size of the text\n", command);

}
