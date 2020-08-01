#include "helloworld.h"
#include <gtkmm.h>
#include <cairomm/cairomm.h>
#include <gtkmm/application.h>

int main(int argc, char *argv[])
{
    Gtk::Main app(argc, argv);
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("sample.glade");

    HelloWorld *helloworld = nullptr;
    builder->get_widget_derived("Main_window", helloworld)
	Gtk::Main::run(*helloworld); 
	delete helloworld; 
	return 0; 
}