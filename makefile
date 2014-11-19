plot: multi.c function.c tools.c sy_parser.c list.c
	incrbuild build.h
	gcc -o plot tools.c multi.c function.c sy_parser.c plot_events.c list.c linenoise.c -lSDL -lSDLmain -lSDL_ttf -lm `pkg-config --cflags --libs gtk+-2.0`

clean:
	rm plot
