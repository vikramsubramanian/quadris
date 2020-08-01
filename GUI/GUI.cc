/*
 * Displays an image in a window. 
 */

#include <gtkmm.h> 
#include <cairomm/cairomm.h> 
#include "helloworld.h"
#include <iostream>

// Creates a new button with the label "Hello World".
HelloWorld::HelloWorld(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder) : Gtk::Window(cobject), _builder(builder)
{

  _builder->get_widget("Main_box", Main_box);
  _builder->get_widget("level", level);
  _builder->get_widget("HS", HS);
  _builder->get_widget("Label", Label);
  _builder->get_widget_derived("game_grid", game_grid);
  _builder->get_widget_derived("img1x1", first_image);
  // first_image = Gdk::Pixbuf::create_from_file("O.png");
}

HelloWorld::~HelloWorld() {}
