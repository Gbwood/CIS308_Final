GtkWidget * fillTable();
GtkWidget * MakeUI(GtkWidget*);



static void Restart (GtkWidget *widget, gpointer data) {
//	window.destroy();
        MakeUI(window);
        g_print ("restart\n");
}


static void forfeitTurn (GtkWidget *widget, gpointer data) {


	g_print ("player %d skipped their turn", turn);

	if (turn == 0) turn++;
	else turn = 0;

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

	switch (turn){

		case 0:
        		gtk_button_set_label (widget , NULL);
		        image = gtk_image_new_from_file("bc.png");
        		gtk_button_set_image (widget, image );
			turn = 1;
			break;
		case 1:
			g_print ("case 2\n");
                        image = gtk_image_new_from_file("wc.png");
                        gtk_button_set_image (widget, image );
			turn = 0;
			break;
	}
	
        g_print ("Hello again - %s was pressed\n", (char *) data);
}

/* This callback quits the program */
static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{

    gtk_main_quit ();
    return FALSE;
}

