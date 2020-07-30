/*
 * Displays an image in a window. 
 */

#include "helloworld.h"
#include <iostream>

// Creates a new button with the label "Hello World".
HelloWorld::HelloWorld() 
{
  for(int i=0;i<20;i++){
    // Gtk::Image image3("O.png");
    // Gtk::Image image3 = "O.png";

    // image3 = ;
    piecesList.push_back(gtk_image_set_from_icon_set("O.png"));
  }
  // Sets the border width of the window.
  set_border_width(10);
  add(m_grid);
  for (int i = 0; i < 20; i++)
  {
    m_grid.add(*piecesList.at(i));
  }
  // This packs the image into the Window (a container).

  // m_grid.add(image);
  // m_grid.add(image2);
  // m_grid.add(image2); 
  // m_grid.attach_next_to(image3, image2, Gtk::POS_BOTTOM, 2, 1);
  // The final step is to display this newly created widget.
  show_all_children();
} // HelloWorld::HelloWorld

HelloWorld::~HelloWorld() {}
