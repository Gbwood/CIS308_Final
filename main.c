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
        //this will fill a 9 x 9 table with 81 buttons
        for (i = 0; i < 9 ; i++) {
                for (j = 0; j< 9; j++) {

                        sprintf(name[count], "%d%d",i,j);
                        button = gtk_toggle_button_new_with_label(name[count]);

			//would it be possible to make a struct for all the button that contain a variable that changes based on whose turn it is?
                        g_signal_connect (button, "clicked",G_CALLBACK (callback), (gpointer) name[count]);

			//updates the board, in terms of scoring
			g_signal_connect (button, "clicked", G_CALLBACK(update), (gpointer) name[count]);

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


/*        //creating the Restart Button
        button = gtk_button_new_with_label("Restart Game");
        g_signal_connect (button, "clicked", G_CALLBACK (Restart), "Restart");
        gtk_box_pack_start (GTK_BOX (box), button, TRUE, FALSE, 0);
        gtk_widget_show(button);
*/
	return box;
}

GtkWidget* CreatePlayerBox() {
	GtkWidget * box  = gtk_vbox_new (FALSE, 10);
	GtkWidget *box2 = gtk_hbox_new(FALSE,0);
	GtkWidget *name;


	name = gtk_label_new(player_1_Name  );
	gtk_box_pack_start(GTK_BOX (box2),name, TRUE, FALSE,0);
 	gtk_widget_show(name);

    	char buffer [33];
    
    
    	sprintf(buffer, "%d", p1_Score);

	
	Player_1_Score = gtk_label_new(buffer);
	gtk_box_pack_start (GTK_BOX (box2), Player_1_Score, TRUE, FALSE, 0);
	gtk_widget_show(Player_1_Score);

	gtk_box_pack_start(GTK_BOX (box), box2, TRUE, FALSE, 0);
	gtk_widget_show(box2);


	box2 = gtk_hbox_new(FALSE,0);
	name = gtk_label_new(player_2_Name);
	gtk_box_pack_start(GTK_BOX (box2), name, TRUE, FALSE, 0);
	gtk_widget_show(name);

	sprintf(buffer, "%d", p2_Score);

	Player_2_Score = gtk_label_new(buffer);
	gtk_box_pack_start (GTK_BOX (box2), Player_2_Score, TRUE, FALSE, 0);
	gtk_widget_show(Player_2_Score);

	gtk_box_pack_start(GTK_BOX (box), box2,TRUE, FALSE, 0);
	gtk_widget_show(box2);







 


	Turn = gtk_label_new(" Player 1's Turn");
	gtk_box_pack_start (GTK_BOX (box), Turn, TRUE, FALSE, 0);
	gtk_widget_show(Turn);

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





	//Add a box with labels to display the score for each player as well as to display whose turn it is
	box2 = CreatePlayerBox();
	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 50);
	gtk_widget_show(box2);






	gtk_container_add (GTK_CONTAINER (window), box1);

        //now that the table is done we can show it
        gtk_widget_show (box1);
	gtk_widget_show (window);


	turn = PLAYER1;


	return window;


}

void GetPlayerNames() {
   	GtkWidget *button;
    	GtkWidget *table;
        GtkWidget *box2;
	GtkWidget *box1;
	GtkWidget *label;
	GtkWidget *entry;
	GtkWidget *window2;

	/* Create a new window */
    	window2 = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    	/* Set the window title */
    	gtk_window_set_title (GTK_WINDOW (window2), "Setup");


	/* Sets the border width of the window. */
        gtk_container_set_border_width (GTK_CONTAINER (window2), 40);


	//we are going to create a vertical box to pack the horizontal boxes into
	box1 = gtk_vbox_new( FALSE, 0);
	box2 = gtk_hbox_new (FALSE, 0);
       	//gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);

	//name 1
	label = gtk_label_new("Enter Player 1's Name: ");
	gtk_box_pack_start (GTK_BOX (box2), label, FALSE, FALSE, 0);
	entry = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY (entry), 15);
	 g_signal_connect (entry, "changed",
		      G_CALLBACK (enter_callback),
		      entry);
	gtk_box_pack_start(GTK_BOX (box2), entry, FALSE, FALSE, 10);
	gtk_widget_show(label);
	gtk_widget_show(entry);

	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 10);
	gtk_widget_show (box2);

	//name 2
	box2 = gtk_hbox_new(FALSE, 0);
	label = gtk_label_new("Enter Player 2's Name: ");
	gtk_box_pack_start(GTK_BOX (box2), label, FALSE, FALSE, 0);
	entry = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY (entry), 15);
	 g_signal_connect (entry, "changed",
		      G_CALLBACK (enter2_callback),
		      entry);
	gtk_box_pack_start(GTK_BOX (box2), entry, FALSE, FALSE, 10);
	gtk_widget_show(label);
	gtk_widget_show(entry);

	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 10);
	gtk_widget_show(box2);


	//enter button
	box2 = gtk_hbox_new(FALSE, 0);

	button = gtk_button_new_with_label("Enter");
	g_signal_connect (button, "clicked", G_CALLBACK (delete_event), "Quit");
	gtk_box_pack_start(GTK_BOX (box2), button, FALSE, FALSE, 0);
	gtk_widget_show(button);

	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 10);
	gtk_widget_show(box2);






	gtk_container_add (GTK_CONTAINER (window2), box1);
	 //now that the table is done we can show it

        gtk_widget_show (box1);	
	gtk_widget_show (window2);

	gtk_main();
	gtk_window_close(window2);
	name_1 = player_1_Name;
}


int main( int   argc, char *argv[] ) {
	gtk_init (&argc, &argv);

	GetPlayerNames();
    	/* Create a new window */
    	MakeUI(window);
	//runs the programs and waits for input from the user
	gtk_main ();

	return 0;
}


