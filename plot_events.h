#ifndef PLOT_EVENTS_H
#define PLOT_EVENTS_H

#include <SDL/SDL.h>

#define CMD_FUNCEVENT SDL_USEREVENT
#define CMD_LABEVENT (SDL_USEREVENT + 1)
#define CMD_TITLEEVENT (SDL_USEREVENT + 2)
#define CMD_RMFUNCEVENT (SDL_USEREVENT + 3)
#define CMD_WINDOWEVENT (SDL_USEREVENT + 4)
#define CMD_RMLABEVENT (SDL_USEREVENT + 5)

SDL_Event build_sdl_event(Uint32 type, void *data);

#endif