//types.h
// Project GO
// Created by Graham, Jacob, and Chandler



#ifndef types_h
#define types_h

//typedef enum { FALSE, TRUE } bool;
typedef enum Status{ENABLED, DISABLED} Status;
typedef enum Color{ BLACK, WHITE, NONE } Color;
typedef enum State{PLAYER1, PLAYER2} State;
typedef struct Pair{
	int row;
	int col;
} Pair;
typedef struct Button{
	Status current_status;
	Color color;
	Pair pair;

} Button;
char name[81][10];
int turn;
GtkWidget *window;


#endif /* types_h */

