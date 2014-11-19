#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

#include "SDL/SDL_ttf.h"
#include "tools.h"

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

window_info_t emptyWindow()
{
	window_info_t winfo = {-10, 10, 0, 0, 0, NO, 600, 400, NULL, NO, 0, 0, NO, NO, {50, 50, 255}, {0, 0, 0}, {0, 255, 255}, NO, NO, NO};
	return winfo;
}

int label_id = 0;
label_t emptyLabel()
{
	label_t label = {NULL, 13, {255, 0, 255}, 0, 0, label_id++};
	return label;
}

label_t *label_with_id(list_t *list, int idx)
{
	node_t *node;
	for(node = list->head; node; node = node->right)
	{
		if(((label_t *)node->obj)->label_id == idx)
			return (label_t *)node->obj;
	}

	return NULL;
}

color_t makeColor(unsigned char r, unsigned char g, unsigned char b)
{
	color_t col = {r, g, b};
	return col;
}

SDL_Surface *createSurface(int width, int height)
{
	return SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
}

void copySurface(SDL_Surface *source, SDL_Surface *dest)
{
	SDL_BlitSurface(source, NULL, dest, NULL);
}

void blit(SDL_Surface *source, SDL_Surface *dest, int x, int y)
{
	SDL_Rect dstr = {x, y, 0, 0};
	SDL_BlitSurface(source, NULL, dest, &dstr);
}

void draw_label(void *obj, void *data)
{
	label_t *label = (label_t *)obj;
	SDL_Surface *screen = (SDL_Surface *)data;

	TTF_Font *font = TTF_OpenFont("AnonPro.ttf", label->fontsize);
		
	SDL_Color col = {label->text_col.r, label->text_col.g, label->text_col.b};
	SDL_Surface *surf = TTF_RenderText_Blended(font, label->txt, col);
	
	blit(surf, screen, label->x, label->y);
	
	TTF_CloseFont(font);
	SDL_FreeSurface(surf);
}

void drawLabels(label_t labels[], int labelcount, SDL_Surface *screen)
{
	int i;
	for(i = 0; i < labelcount; i++)
	{
		label_t label = labels[i];
		
		TTF_Font *font = TTF_OpenFont("AnonPro.ttf", label.fontsize);
		
		SDL_Color col = {label.text_col.r, label.text_col.g, label.text_col.b};
		SDL_Surface *surf = TTF_RenderText_Blended(font, label.txt, col);
		
		blit(surf, screen, label.x, label.y);
		
		TTF_CloseFont(font);
		SDL_FreeSurface(surf);
	}
}

void print_debug_coords(SDL_Surface *screen, TTF_Font *font, int x, int y)
{
	char frmt[20];
	sprintf(frmt, "(%d, %d)", x, y);
	
	SDL_Color col = {0, 255, 0};
	SDL_Surface *surf = TTF_RenderText_Solid(font, frmt, col);
	
	blit(surf, screen, 10, 10);
	
	SDL_FreeSurface(surf);
}

gboolean test(gpointer data)
{
	char **file = (char **)data;

	GtkWidget *dialog;
	GtkFileFilter *filter;
	
	filter = gtk_file_filter_new();
	gtk_file_filter_add_pattern(filter, "*.bmp");
	gtk_file_filter_set_name(filter, "Bitmap images");
	
	dialog = gtk_file_chooser_dialog_new("Save Snapshot", NULL, GTK_FILE_CHOOSER_ACTION_SAVE, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT, NULL);
	
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);
	gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);
	
	*file = NULL;
	char *filename = NULL;
	if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
	{
		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		
		*file = malloc(strlen(filename) + 1);
		strcpy(*file, filename);
		g_free(filename);
		
	}
	gtk_widget_destroy(dialog);
	
	gtk_main_quit();
	
	return FALSE;
}

char *get_filename()
{
	char *filename;
	
	g_timeout_add(1, test, (gpointer)&filename);
	gtk_main();
	
	return filename;
}
