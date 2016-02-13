#include</usr/include/gtkmm-3.0/gtkmm/application.h>
#include "Button.h"
#include "play.h"
#include </usr/include/gtk-3.0/gtk/gtk.h>

int main(int argc, char* argv[])
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc,argv);
//	Gtk::Window window;
//	window.set_default_size(1400,800);
//	window.set_title("Test");
//	Gtk::Button btn;// = new Gtk::Button("buttonTest" ,true);
//	btn.add_pixlabel("53236364.jpg", "testButton");
////	btn.set_title("Test Button");
//	btn.set_border_width(5);
//	window.add(btn);
//	window.show_all_children();	
//	return app->run(window);
	Button btn;
	gst_init(NULL, NULL);
//	g_signal_connect(app, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	return app->run(btn);
}
