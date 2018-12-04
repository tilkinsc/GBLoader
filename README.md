# GBLoader
A public domain simplex program that loads a GB file data into ram

No warranties neither express nor implied, even merchantability. At all. Sorry.

Just loads in a *.gb file. Nothing serious.

In a struct, you will find uncleverly named segments in which some data is copied,
the other is just pointed to from the buffer (i.e. text data like title or gb image).

Although not fully complete yet, I plan for this repository to contain its own ram layout and functions to translate memory addresses.

I might even create a sister project to recompile instructions into MIPS or ARM instructions. Who knows.
