//types.h
// Project GO
// Created by Graham, Jacob, and Chandler



#ifndef types_h
#define types_h

//typedef enum { FALSE, TRUE } bool;
typedef enum Status{ENABLED, DISABLED} Status;
typedef enum Color{ BLACK, WHITE, NONE } Color;
typedef enum State{PLAYER1, PLAYER2} State;

struct Pairs{
	int row;
	int col;
} Pairs = {99,99};

typedef struct Pairs Pair;

typedef struct Button{
	Status current_status;
	Color color;
	Pair pair;

} Button;

typedef struct PairList{
	Pair data;
	Pair last;
	struct PairList * next;
} PairList;

typedef struct Board{
	Button *buttons;
	int count;
} Board;



char name[81][10];
State turn;
GtkWidget *window;
Button board[81];
int board_count;
GtkWidget * Player_1_Score;
int p1_Score = 0;
int p2_Score = 0;
GtkWidget * Player_2_Score;
gchar* player_1_Name;
gchar* player_2_Name;
const char * name_1;
const char * name_2;

GtkWidget * Turn;
#endif /* types_h */

