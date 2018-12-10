GtkWidget * fillTable();
GtkWidget * MakeUI(GtkWidget*);



static void Restart (GtkWidget *widget, gpointer data) {
//	window.destroy();
        MakeUI(window);
        g_print ("restart\n");
}


static void forfeitTurn (GtkWidget *widget, gpointer data) {


	g_print ("player %d skipped their turn", turn);

	if (turn == PLAYER1) PLAYER2;
	else turn = PLAYER1;

        g_print ("it is now player %d's turn.\n", turn);

}

static void forfeitGame (GtkWidget *widget, gpointer data) {

        g_print ("Game Forfeited by %d\n", turn);

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
			break;
	}
	
        g_print ("Hello again - button%d-%d was pressed\n", r,c);
	board[board_count] = b;
	board_count += 1;
}

//function that, given a pair and a color, determines all valid neighbors of that color
static Pair * findNeighbors(Color color, Pair start, int * count)
{
	Pair  * neighbors;
	int r = start.row;
	int c = start.col;
	int co = 0;
	for (int i = 0; i < board_count; i++)
	{
		if ((board[i].pair.row != r || board[i].pair.col != c) && board[i].color == color)
		{
			if ((board[i].pair.row == r || board[i].pair.row == r-1 || board[i].pair.row == r+1) && (board[i].pair.col == c || board[i].pair.col == c-1 || board[i].pair.col == c+1))
			{
				*(neighbors+co) = board[i].pair;
				co++;
			}
		}
	}
	count = &co;
	return neighbors;
}

/*function called to determine whether an area is closed by pieces, and which pieces create the enclosure.*/
static int closedArea(Color color, Pair ** pairs, int count)
{
	Pair start = **(pairs+count);
	Pair last;
	if (count != 0)
	{
		last = **(pairs+count-1);
	}
	Pair next;
	int co;
	Pair * neighbors = findNeighbors(color, start, co);
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
			**(pairs+count+1) = *(neighbors+i);
			if ((neighbors+i)->row != last.row || (neighbors+i)->col != last.col || last.row == 99)
			{
				if ((neighbors+i)->row == pairs[0]->row && (neighbors+i)->col == pairs[0]->col)
				{
					return 1;
				}else
				{
					if (closedArea(color, &pairs, count+1))
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
                        **(pairs+count+1) = *(neighbors+i);
                        if ((neighbors+i)->row != last.row || (neighbors+i)->col != last.col || last.row == 99)
                        {
                                if ((neighbors+i)->row == pairs[0]->row && (neighbors+i)->col == pairs[0]->col)
                                {
                                        return 1;
                                }else
                                {
                                        if (closedArea(color, &pairs, count+1))
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
                        **(pairs+count+1) = *(neighbors+i);
                        if ((neighbors+i)->row != last.row || (neighbors+i)->col != last.col || last.row == 99)
                        {
                                if ((neighbors+i)->row == pairs[0]->row && (neighbors+i)->col == pairs[0]->col)
                                {
                                        return 1;
                                }else
                                {
                                        if (closedArea(color, &pairs, count+1))
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
                        **(pairs+count+1) = *(neighbors+i);
                        if ((neighbors+i)->row != last.row || (neighbors+i)->col != last.col || last.row == 99)
                        {
                                if ((neighbors+i)->row == pairs[0]->row && (neighbors+i)->col == pairs[0]->col)
                                {
                                        return 1;
                                }else
                                {
                                        if (closedArea(color, &pairs, count+1))
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
	for (int i = 0; neighbors+i != NULL; i++)
	{
		**(pairs+count+1) = *(neighbors+i);
		if ((neighbors+i)->row != last.row || (neighbors+i)->col != last.col || last.row == 99)
		{
			if ((neighbors+i)->row == pairs[0]->row && (neighbors+i)->col == pairs[0]->col)
			{
				return 1;
			}else
			{
				if (closedArea(color, &pairs, count+1))
					return 1;
			}
		}
	}
	**(pairs+count+1) = next;
	if (closedArea(color, &pairs, count+1))
		return 1;
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
	Pair * pairs = malloc(sizeof *pairs);
	*pairs = current.pair;
	if (closedArea(current.color, &pairs, 0))
	{
		//PUT SCORE FUNCTION ONE HERE
		g_print("Closed Area Found!\n");
	}
	free(pairs);

}

/* This callback quits the program */
static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{

    gtk_main_quit ();
    return FALSE;
}

