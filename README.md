# Garden

A true Final Fantasy VIII editor based on [Qhimm](http://www.qhimm.com)'s source.

## Qhimm's Description
Garden is indeed a true Final Fantasy VIII editor. Using my pre-alpha version,
I have been able to hack several scenes in FF8.

Examples:
![\[1\]](http://www.qhimm.com/shots/garden_game1.jpg "Go talk to a wall.")
![\[2\]](http://www.qhimm.com/shots/garden_game2.jpg "Ugh…")

After a lot of pressure (I receive 10 requests per week about this),
I've decided to release this program, however only the source code.
I hope that someone can continue my work and realize true FF8 editing.

The program currently supports decompiling the data files,
editing game text data and re-compiling the data files again.
The decompiled data files require about 1200 MB of disk space,
and you will need to have a full FF8 install (all data files on disk).

## Known Issues
- The re-compiled data files are not as effectively compressed as the original files, meaning FF8 will suffer a certain speed loss.
- *LOTS* more.

## Keyaku's notes

This is currently only a mirror. I plan to work on this when I can.
It doesn't compile without Visual Studio 6 (which I do not have).
Even with a Makefile, it won't compile without a proper code cleanup (and because
I reorganized the source files' locations).

Anyone is welcome to contribute!

## License

This project is under MIT License.
