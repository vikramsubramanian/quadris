/*
 * Displays an image in a window. 
 */

#ifndef GTKMM_EXAMPLE_HELLOWORLD_H
#define GTKMM_EXAMPLE_HELLOWORLD_H
#include <gtkmm.h> 
#include <cairomm/cairomm.h> 
#include <vector>




class HelloWorld : public Gtk::Window
{
public:

    virtual ~HelloWorld();
    HelloWorld(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);


    Glib::RefPtr<Gtk::Builder> _builder;
    Gtk::Box* Main_box;
    Gtk::Label * level;
    Gtk::Label * HS;
    Gtk::Label * Label;
    Gtk::Grid * game_grid;
    Gtk::Image* first_image;
}; 

#endif
