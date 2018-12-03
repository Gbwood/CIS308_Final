//sup
#include <stdlib.h>
#include <gtk/gtk.h>
#include "types.h"

/* Create a new hbox with an image and a label packed into it
 * and return the box. */

static GtkWidget *xpm_label_box( gchar     *xpm_filename,
                                 gchar     *label_text )
{
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *image;

    /* Create box for image and label */
    box = gtk_hbox_new (FALSE, 0);
   	//change number here to change size of box
	 gtk_container_set_border_width (GTK_CONTAINER (box), 10);

    /* Now on to the image stuff */
    image = gtk_image_new_from_file (xpm_filename);

    /* Create a label for the button */
    label = gtk_label_new (label_text);

    /* Pack the image and label into the box */
    gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 3);

    gtk_widget_show (image);
    gtk_widget_show (label);

    return box;
}






/* Our callback.
 * The data passed to this function is printed to stdout */
static void callback( GtkWidget *widget,
                      gpointer   data )
{
	GtkWidget *image;

	gtk_button_set_label (widget , NULL);
	image = gtk_image_new_from_file("th.jpeg");

	gtk_button_set_image (widget, image );
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

GtkWidget * fillTable(GtkWidget *window) {
//65
	GtkWidget *button;
    	GtkWidget *table;


	/* Create a 2x2 table */
        table = gtk_table_new (9, 9, TRUE);

        /* Put the table in the main window */
        



        int i = 0;
        int j = 0;
        char name[81][10];
	 int count =0;
        //this should fill a 9 x 9 table with 81 buttons
        for (i = 0; i < 9 ; i++) {
                for (j = 0; j< 9; j++) {

//88
                        sprintf(name[count], "button%d-%d",i,j);
                        button = gtk_toggle_button_new_with_label(name[count]);

                        g_signal_connect (button, "clicked",G_CALLBACK (callback), (gpointer) name[count]);

                        g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_toggle_button_set_active), button);
                        gtk_table_attach_defaults (GTK_TABLE (table), button, j, j+1, i, i + 1);

                        //set styles, images, and boarders here


//100
                        gtk_widget_show (button);
                        count++;
                }

        }
	//gtk_widget_show (table);
	//gtk_widget_show (window);

	return table;
}


GtkWidget * MakeUI(GtkWidget *window) {

    	GtkWidget *button;
    	GtkWidget *table;
        GtkWidget *box;
	GtkWidget *box1;
	GtkWidget *box2; 
    /* Create a new window */
    	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
//123
    /* Set the window title */
    	gtk_window_set_title (GTK_WINDOW (window), "GO");

    /* Set a handler for delete_event that immediately
     * exits GTK. */
    	g_signal_connect (window, "delete-event",
                      G_CALLBACK (delete_event), NULL);

    /* Sets the border width of the window. */
        gtk_container_set_border_width (GTK_CONTAINER (window), 200);


	//we are going to create a horizontal box to pack the vertical boxes into
	box1 = gtk_hbox_new( FALSE, 0);

	box2 = gtk_vbox_new (FALSE, 0);

	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);

        //creates a new blank table
        table = fillTable(window);

	gtk_box_pack_start (GTK_BOX (box2), table, FALSE, FALSE, 0);
//140	
	gtk_widget_show (table);
	gtk_widget_show (box2);

        
	//creating a quit button

	box2 = gtk_vbox_new (FALSE, 0);

        button = gtk_button_new();

        g_signal_connect (button, "clicked", G_CALLBACK (delete_event), "Quit");

        box = xpm_label_box ("info.xpm", "Quit");
//150
        gtk_container_add (GTK_CONTAINER (button), box);

	gtk_box_pack_start (GTK_BOX (box2), box, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);

        gtk_widget_show (button);


//      gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 9, 9, 10);
        gtk_widget_show (box);
	gtk_widget_show (box2);
	    gtk_container_add (GTK_CONTAINER (window), box1);

        //now that the table is done we can show it
        gtk_widget_show (box1);	
	gtk_widget_show (window);

	return window;


}

int main( int   argc,
          char *argv[] )
{
    	GtkWidget *window;
	gtk_init (&argc, &argv);

    	/* Create a new window */
    	window = MakeUI(window);
	//runs the programs and waits for input from the user
	gtk_main ();

	return 0;
}//170
