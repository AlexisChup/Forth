# call all programs
all:
	main

main: dictionnaire.h dictionnaire.c forth.h interface.h interface.c interprete.h interprete.c noyau.h noyau.c pile.h pile.c main.c
	gcc -o main dictionnaire.c interface.c interprete.c noyau.c pile.c main.c