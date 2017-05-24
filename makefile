games: main.o kgame.o tictactoe.o
	gcc -o games main.o kgame.o k.o tictactoe.o
main.o: main.c
	gcc -c main.c
kgame.o: kgame.c k.c k.h
	gcc -c kgame.c k.c
tictactoe.o: tictactoe.c
	gcc -c tictactoe.c