# Plot

## Disclaimer
Alright, admittedly this is a bit of a messy repository. Nonetheless the code works (and works quite well).

## Dependencies
Plot currently requires SDL-1.2 and gtk-2. Gtk is only used for the save-file dialog when saving bitmaps.
This bit could safely be removed to create a build free of the Gtk dependency.

## Building
Running `make` will suffice. A `make clean` is also provided

## Example Usage
Help can be found by typing `./plot --usage`.

A pretty plot:   
`./plot 1 --plotcolor 70,70,70 --static -f "-1" --plotcolor 70,70,70 --static -f  "Sin[x]" --tangent --aspect --plotcolor 255,0,0 --axescolor 255,255,255 --xtick 0.78539816 --ytick 0.5 --window 1500,400 -f "Cos[x]" --tangent --plotcolor 255,255,0`

In theory if you just run `plot` with no arguments, it should give you an interactive terminal with syntax similar
to that of the static version. This is _extremely_ buggy, however.

## Credit
I use the [linenoise](https://github.com/antirez/linenoise) library to have a (somewhat) interactive experience.
I also use the Anonymous Pro font, provided under a very liberal license by the folks over at the [Open Font Library](http://openfontlibrary.org/en/font/anonymous-pro).

