all:
	gcc -Wall -ansi src/rogue.c src/roguefunctions.c  -o bin/rogue -Iinclude -lncurses
