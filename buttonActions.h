GtkWidget * fillTable();
GtkWidget * MakeUI(GtkWidget*);



static void Restart (GtkWidget *widget, gpointer data) {
	//gtk_window_close(window);
        MakeUI(window);
        g_print ("restart\n");
}


static void forfeitTurn (GtkWidget *widget, gpointer data) {


	g_print ("player %d skipped their turn", turn);

	if (turn == PLAYER1){ 
		turn = PLAYER2;
		gtk_label_set_text(Turn, " Player 2 Turn");
	}
	else {
		turn = PLAYER1;
		gtk_label_set_text(Turn, " Player 1 Turn");

	}
        g_print ("it is now player %d's turn.\n", turn);

}

static void forfeitGame (GtkWidget *widget, gpointer data) {

	switch (turn){
		//add get image to each case to check if peice has already been played on tile
		case PLAYER1:
        		gtk_label_set_text(Turn, "Player 1 has forfeited the game, Player 2 Wins");
			break;
		case PLAYER2:
			gtk_label_set_text(Turn, "Player 2 has forfeited the game, Player 2 Wins");
			break;
	}
        gtk_window_close(window);

}
static void enter_callback( GtkWidget *widget,
                            GtkWidget *entry )
{
  player_1_Name = gtk_entry_get_text(GTK_ENTRY (entry));
}

static void enter2_callback( GtkWidget *widget,
                            GtkWidget *entry )
{
  player_2_Name = gtk_entry_get_text (GTK_ENTRY (entry));
}

/* Our callback.
 * The data passed to this function is printed to stdout */
static void callback( GtkWidget *widget,
                      gpointer   data )
{
        GtkWidget *image;
	Button b;
	char * rc = (char *) data;
	int r = *rc - '0';
	int c = *(rc+1) - '0';
	b.pair.row = r;
	b.pair.col = c;
	switch (turn){
		//add get image to each case to check if peice has already been played on tile
		case PLAYER1:
        		gtk_button_set_label (widget , NULL);
		        image = gtk_image_new_from_file("bc.png");
			b.color = BLACK;
        		gtk_button_set_image (widget, image );
			gtk_widget_set_sensitive(widget, FALSE);
			b.current_status = DISABLED;
			gtk_label_set_text(Turn, " Player 2's Turn");
			turn = PLAYER2;
			break;
		case PLAYER2:
			g_print ("case 2\n");
                        image = gtk_image_new_from_file("wc.png");
			b.color = WHITE;
                        gtk_button_set_image (widget, image );
			gtk_widget_set_sensitive(widget, FALSE);
			b.current_status = DISABLED;
			turn = PLAYER1;
			gtk_label_set_text(Turn, " Player 1's Turn");
			break;
	}
	
        g_print ("Hello again - button%d-%d was pressed\n", r,c);
	board[board_count] = b;
	board_count += 1;
}

//function that, given a pair and a color, determines all valid neighbors of that color
static Pair * findNeighbors(Color color, Pair start, int * count)
{
	Pair neighbors[8] = {{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99},{99,99}};
	int r = start.row;
	int c = start.col;
	int co = 0;
	for (int i = 0; i < board_count+1; i++)
	{
		if ((board[i].pair.row != r || board[i].pair.col != c) && board[i].color == color)
		{
			if ((board[i].pair.row == r || board[i].pair.row == r-1 || board[i].pair.row == r+1) && (board[i].pair.col == c || board[i].pair.col == c-1 || board[i].pair.col == c+1))
			{
				g_print("BOARD: %d,%d\n", board[i].pair.row, board[i].pair.col);
				neighbors[co].row = board[i].pair.row;
				neighbors[co].col = board[i].pair.col;
				co++;
			}
		}
	}
	g_print("%d\n", co);
	*count = co;
	g_print("%d,%d\n", neighbors[0].row, neighbors[0].col);
	Pair * neighborss = neighbors;
	g_print("%d,%d\n", neighborss->row, neighborss->col);
	return neighborss;
}

/*function called to determine whether an area is closed by pieces, and which pieces create the enclosure.*/
static int closedArea(Color color, PairList * pairs, int count, Pair last, Pair first)
{
/*	Pair start = pairs->data;
	Pair next;
	g_print("START BEFORE: %d,%d\n", start.row, start.col);
	PairList *nextList;
	pairs->next = nextList;
	int co;
	Pair * neighbors = findNeighbors(color, start, &co);
	g_print("1st neighbor: %d,%d\n", neighbors->row, neighbors->col);
	g_print("last: %d,%d\n", last.row, last.col);
	if (co == 0 || (co == 1 && neighbors->row == last.row && neighbors->col == last.col))
	{
		return 0;
	}
	g_print("LASTTTTT %d,%d\n", last.row, last.col);
	if (start.row == 0)
	{
		next.row = -1;
		next.col = start.col;
	}else if (start.col == 0)
	{
		next.row = start.row;
		next.col = -1;
	}else if (start.row == 8)
	{
		next.row = 9;
                next.col = start.col;
	}else if (start.col == 8)
        {
                next.row = start.row;
                next.col = 9;
        }else if (start.row == -1)
        {
		for (int i = 0; neighbors+i != NULL; i++)
		{
			nextList->data = *(neighbors+i);
			if ((neighbors+i)->row != last.row || (neighbors+i)->col != last.col || last.row == 99)
			{
				if ((neighbors+i)->row == pairs->data.row && (neighbors+i)->col == pairs->data.col)
				{
					return 1;
				}else
				{
					if (closedArea(color, ((*pairs).next), count+1, start))
						return 1;
				}
			}
		}
		if (start.col == 9)
		{
			next.row = start.row+1;
			next.col = start.col;
		}else
		{
			next.row = start.row;
			next.col = start.col+1;
		}
        }else if (start.col == -1)
        {
		for (int i = 0; neighbors+i != NULL; i++)
                {
                        nextList->data = *(neighbors+i);
                        if ((neighbors+i)->row != last.row || (neighbors+i)->col != last.col || last.row == 99)
                        {
                                if ((neighbors+i)->row == pairs->data.row && (neighbors+i)->col == pairs->data.col)
                                {
                                        return 1;
                                }else
                                {
                                        if (closedArea(color, ((*pairs).next), count+1, start))
                                                return 1;
                                }
                        }
                }
                next.row = start.row+1;
                next.col = start.col;

        }else if (start.row == 9)
        {
		for (int i = 0; neighbors+i != NULL; i++)
                {
                        nextList->data = *(neighbors+i);
			if ((neighbors+i)->row != last.row || (neighbors+i)->col != last.col || last.row == 99)
                        {
                                if ((neighbors+i)->row == pairs->data.row && (neighbors+i)->col == pairs->data.col)
                                {
                                        return 1;
                                }else
                                {
                                        if (closedArea(color, ((*pairs).next), count+1, start))
                                                return 1;
                                }
                        }
                }
                next.row = start.row;
                next.col = start.col-1;
        }else if (start.col == 9)
        {
		for (int i = 0; neighbors+i != NULL; i++)
                {
                        nextList->data = *(neighbors+i);
                        if ((neighbors+i)->row != last.row || (neighbors+i)->col != last.col || last.row == 99)
                        {
                                if ((neighbors+i)->row == pairs->data.row && (neighbors+i)->col == pairs->data.col)
                                {
                                        return 1;
                                }else
                                {
                                        if (closedArea(color, ((*pairs).next), count+1, start))
                                                return 1;
                                }
                        }
                }
                if (start.row == 9)
                {
                        next.row = start.row;
                        next.col = start.col-1;
                }else
                {
                        next.row = start.row-1;
                        next.col = start.col;
                }
        }
	for (int i = 0; (neighbors+i) != NULL || (neighbors+i < 50); i++)
                {
                        if ((neighbors+i)->row != last.row || (neighbors+i)->col != last.col || last.row == 99)
                        {
				g_print("last %d,%d\n", last.row, last.col);
				g_print("first %d,%d\n", first.row, first.col);
                                if (((neighbors+i)->row == first.row && (neighbors+i)->col == first.col) && (first.row != last.row || first.col != last.col))
                                {
					g_print("h?\n");
                                        return 1;
                                }else
                                {
					g_print("here?\n");
					g_print("%d,%d\n", (neighbors+i)->row, (neighbors+i)->col);
					nextList->data = *(neighbors+i);
                                        if (closedArea(color, nextList, count+1, start, first))
                                                return 1;
					g_print("oh shit");
                                }
                        }
                }

	nextList->data = next;
	if (closedArea(color, nextList, count+1, start, first))
*/
	return 0;
}
/*callback that checks for scoring after a button is pressed.*/
static void update(GtkWidget *widget, gpointer data)
{
	char * rc = (char *) data;
        int r = *rc - '0';
        int c = *(rc+1) - '0';
	Button current;
	for(int i; i < board_count; i++)
	{
		if (board[i].pair.row == r && board[i].pair.col == c)
		{
			current = board[i];
		}
	}
	PairList pairs;
	pairs.data = current.pair;
	Pair last = {99,99};
	if (closedArea(current.color, &pairs, 0, last, current.pair))
	{
		//PUT SCORE FUNCTION ONE HERE
		g_print("Closed Area Found!\n");
	}

}

/* This callback quits the program */
static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{

    gtk_main_quit ();
    return FALSE;
}

