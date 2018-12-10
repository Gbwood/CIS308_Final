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
static void enter_callback( GtkWidget *widget,
                            GtkWidget *entry )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
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
	Pair neighbors[8];
	int r = start.row;
	int c = start.col;
	int co = 0;
	for (int i = 0; i < board_count+1; i++)
	{
		if ((board[i].pair.row != r || board[i].pair.col != c) && board[i].color == color)
		{
			g_print("der\n");
			if ((board[i].pair.row == r || board[i].pair.row == r-1 || board[i].pair.row == r+1) && (board[i].pair.col == c || board[i].pair.col == c-1 || board[i].pair.col == c+1))
			{
				neighbors[i].row = board[i].pair.row;
				neighbors[i].col = board[i].pair.col;
				co++;
			}
		}
	}
	g_print("%d\n", co);
	if (color == BLACK) g_print("BLACK\n");
	if (color == WHITE) g_print("WHITE\n");
	if (color == NONE) g_print("NONE\n");
	*count = co;
	Pair * neighborss = neighbors;
	return neighborss;
}

/*function called to determine whether an area is closed by pieces, and which pieces create the enclosure.*/
static int closedArea(Color color, PairList * pairs, int count, Pair last)
{
	Pair start = pairs->data;
	Pair next;
	PairList nextlist;
	int co;
	Pair * neighbors = findNeighbors(color, start, &co);
	if (co == 0)
	{
		return 0;
	}
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
			pairs->next->data = *(neighbors+i);
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
                        pairs->next->data = *(neighbors+i);
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
                        pairs->next->data = *(neighbors+i);
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
                        pairs->next->data = *(neighbors+i);
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
        }	for (int i = 0; neighbors+i < neighbors+co; i++)
                {
                        pairs->next->data = *(neighbors+i);
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
	pairs->next->data = next;
	if (closedArea(color, ((*pairs).next), count+1, start))
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
	PairList pairs;
	pairs.data = current.pair;
	Pair last;
	if (closedArea(current.color, &pairs, 0, last))
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

