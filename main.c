//sup
#include <stdlib.h>
#include <gtk/gtk.h>
#include "types.h"
#include "buttonActions.h"
#include "unused.h"


/* Create a new hbox with an image and a label packed into it
 * and return the box. */


GtkWidget * fillTable() {
	GtkWidget *button;
    	GtkWidget *table;
	GtkWidget *image;

	/* Create a 9x9 table */
        table = gtk_table_new (9, 9, TRUE);

        /* Put the table in the main window */

        int i = 0;
        int j = 0;
	int count =0;
        //this should fill a 9 x 9 table with 81 buttons
        for (i = 0; i < 9 ; i++) {
                for (j = 0; j< 9; j++) {

                        sprintf(name[count], "button%d-%d",i,j);
                        button = gtk_toggle_button_new_with_label(name[count]);

			//would it be possible to make a struct for all the button that contain a variable that changes based on whose turn it is?
                        g_signal_connect (button, "clicked",G_CALLBACK (callback), (gpointer) name[count]);

                        g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_toggle_button_set_active), button);
                        gtk_table_attach_defaults (GTK_TABLE (table), button, j, j+1, i, i + 1);

                        //set styles, images, and boarders here

		        gtk_button_set_label (button, NULL);
        		image = gtk_image_new_from_file("square.png");

        		gtk_button_set_image (button, image );


                	gtk_widget_show (button);
                	count++;
                }

        }
	gtk_widget_show (table);


	return table;
}

GtkWidget * makeGameControls() {
	//creating a box for game control buttons
	GtkWidget * box = gtk_vbox_new (FALSE, 10);
	GtkWidget * button;

        //creating the Quit Button
        button = gtk_button_new_with_label("Quit");
        g_signal_connect (button, "clicked", G_CALLBACK (delete_event), "Quit");
	//box = xpm_label_box ("info.xpm", "Quit");
        gtk_box_pack_start (GTK_BOX (box), button, TRUE, FALSE, 0);
        gtk_widget_show(button);


        //creating the Forfeit Turn Button
        button = gtk_button_new_with_label("Forfeit Turn");
        g_signal_connect (button, "clicked", G_CALLBACK (forfeitTurn), "Forfeit Turn");
        gtk_box_pack_start (GTK_BOX (box), button, TRUE, FALSE, 0);
        gtk_widget_show(button);

        //Creating the Forfeit Game Button
        button = gtk_button_new_with_label("Forfeit Game");
        g_signal_connect (button, "clicked", G_CALLBACK (forfeitGame), "Forfeit Game");
        gtk_box_pack_start (GTK_BOX (box), button, TRUE, FALSE, 0);
        gtk_widget_show(button);


        //creating the Restart Button
        button = gtk_button_new_with_label("Restart Game");
        g_signal_connect (button, "clicked", G_CALLBACK (Restart), "Restart");
        gtk_box_pack_start (GTK_BOX (box), button, TRUE, FALSE, 0);
        gtk_widget_show(button);

	return box;
}



GtkWidget* MakeUI(GtkWidget *window) {

    	GtkWidget *button;
    	GtkWidget *table;
        GtkWidget *box;
	GtkWidget *box1;
	GtkWidget *box2;
	GtkWidget *restart;


	/* Create a new window */
    	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    	/* Set the window title */
    	gtk_window_set_title (GTK_WINDOW (window), "GO");

    	/* Set a handler for delete_event that immediately
     	* exits GTK. */
    	g_signal_connect (window, "delete-event",
                      G_CALLBACK (delete_event), NULL);

	/* Sets the border width of the window. */
        gtk_container_set_border_width (GTK_CONTAINER (window), 80);


	//we are going to create a horizontal box to pack the vertical boxes into
	box1 = gtk_hbox_new( FALSE, 0);
	box2 = gtk_vbox_new (FALSE, 0);

	//pack the second box into the first box
	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);

        //creates a new blank table
        table = fillTable();

	//pack table into the box
	gtk_box_pack_start (GTK_BOX (box2), table, FALSE, FALSE, 0);

	//show table and box
	gtk_widget_show (table);
	gtk_widget_show (box2);


	//creating a box for game control buttons
	box2 = makeGameControls();

	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 50);


	//gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 9, 9, 10);
    	//gtk_widget_show (box);
	gtk_widget_show (box2);





	//don't know if this will end up going here or not
	//box2 = createPlayerBoard();


	gtk_container_add (GTK_CONTAINER (window), box1);

        //now that the table is done we can show it
        gtk_widget_show (box1);	
	gtk_widget_show (window);
	


	turn = PLAYER1;

	return window;


}




int main( int   argc, char *argv[] ) {
    	
	gtk_init (&argc, &argv);

    	/* Create a new window */
    	MakeUI(window);
	//runs the programs and waits for input from the user
	gtk_main ();

	return 0;
}


