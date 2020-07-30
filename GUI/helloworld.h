/*
 * Displays an image in a window. 
 */

#ifndef GTKMM_EXAMPLE_HELLOWORLD_H
#define GTKMM_EXAMPLE_HELLOWORLD_H
#include <gtkmm.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <vector>

class HelloWorld : public Gtk::Window
{
public:
    HelloWorld();
    virtual ~HelloWorld();

protected:
    // Member widgets:
    std::vector<Gtk::Image*> piecesList;
    Gtk::Grid m_grid;
    Gtk::Image image3;
    // Gtk::Image image3;
    // Gtk::Image image;

}; // HelloWorld

#endif
