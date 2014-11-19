#include "plot_events.h"

SDL_Event build_sdl_event(Uint32 type, void *data)
{
	SDL_UserEvent usr;
	usr.code = 0;
	usr.data1 = (void *)data;
	usr.type = type;
	SDL_Event evt;
	evt.type = type;
	evt.user = usr;

	return evt;
}