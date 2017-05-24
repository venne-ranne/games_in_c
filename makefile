games: main.o kgame.o tictactoe.o guessgame.o
	gcc -o games main.o kgame.o k.o tictactoe.o guessgame.o
main.o: main.c
	gcc -c main.c
kgame.o: kgame.c k.c k.h
	gcc -c kgame.c k.c
tictactoe.o: tictactoe.c tictactoe.h
	gcc -c tictactoe.c
guessgame.o: guessgame.c guessgame.h
	gcc -c guessgame.c 