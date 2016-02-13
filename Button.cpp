#include "Button.h"
#include </usr/include/gtkmm-3.0/gtkmm/listboxrow.h>

bool Button::isPause = false;
bool isPlaying = false;

void Button::playSong(std::string uri)
{
//			playAudio* playaudio = new playAudio;
			if(!isPlaying)
			{
				playaudio->stop();
				isPlaying = true;
				playaudio->play_uri(uri.c_str());
			}
			else
			{
				playaudio->stop();
				isPlaying = false;
				playaudio->play_uri(uri.c_str());
			}
}

Button::Button()
{
//	cb.append("combo");
//	cb.append("box");
//	cb.append("text");
//	cb.set_active(1);
//	cb.set_size_request(10,10);
//	add(cb);
	playaudio = new playAudio();
	std::cout<<"Button creation in constructor\n";
//	mBtnBox.add_pixlabel("53236364.jpg", "testButton");
	set_title("Button Api");
//	set_default_size(100,100);
	add(mBtnBox);
//	add(listbox);
//	add(mBtn);
//	set_border_width(10);
//	mBtnBox.set_size_request(5,5);
//	mBtnBox.set_margin_right(0);
//	mBtnBox.set_margin_left(0);
//	mBtnBox.set_margin_top(0);
//	mBtnBox.set_margin_bottom(0);
	mBtnBox.pack_start(listbox);
	mBtnBox.pack_start(mBtnFile);
	mBtnFile.set_label("Select");
	mBtnFile.signal_clicked().connect( sigc::mem_fun(*this, &Button::on_button_file_clicked) );
	mBtnBox.pack_start(mBtn);
	mBtn.set_label("Pause/Resume");
	mBtn.signal_clicked().connect(sigc::mem_fun(*this, &Button::pauseResume_button_clicked));
//	mBtnBox.pack_start(mBtnFolder);
//	mBtnFolder.signal_clicked().connect( sigc::mem_fun(*this, &Button::on_button_folder_clicked) );

//			lb.set_label("vidhuA");
//			lb1.set_label("AvidhuA");
//			listbox.add(lb);
//			listbox.add(lb1);
	listbox.signal_button_release_event().connect(sigc::mem_fun(*this, &Button::on_button_release_event_m));
//	lb1.signal_button_release_event().connect(sigc::mem_fun(*this, &Button::label_selected));
	show_all_children();
	
}

bool Button::label_selected(GdkEventButton* event)
{
	std::cout << "hi it worked !!" << std::endl;
}

//function called when x button is clicked in window.
//if you want to change functionality of x button then overwrite on_delete_event()
bool Button::on_delete_event(GdkEventAny* event)
{
	//Gtk::Window::on_delete_event(event);
	this->hide();
	//close();
	playaudio->stop();
	if(playaudio)
	{
		delete playaudio;
        	std::cout << "playaudio object deleted\n";
	}
	exit(EXIT_SUCCESS);
}

//function inherited from Gtk::widget 
bool Button::on_button_release_event_m(GdkEventButton* release_event)
{
//	std::cout << "hi !" << get_focus_child()->get_name() <<  std::endl;
	Gtk::ListBoxRow* row = listbox.get_selected_row();
	Gtk::Label* l = dynamic_cast<Gtk::Label*>(row->get_child());
	std::cout << "Selected label Name is " << l->get_label() << endl;//row->get_index() << std::endl;
	//testThread.
	terminate();
	playSong(l->get_label());

//	vector<Gtk::Widget*> childs = listbox.get_children();
//	std::cout << childs[row->get_index()]->get_name() ;
}

void Button::pauseResume_button_clicked()
{
	std::cout<<"Pause Button clicked\n";
	if(!isPause)
	{
		mBtn.set_label("Resume");
		playaudio->pause();
		isPause = true;
	}
	else
	{
		mBtn.set_label("Pause");
		playaudio->resume();
		isPause = false;
	}
	
}

void Button::on_button_file_clicked()
{
	Gtk::FileChooserDialog dialog("Choose file", Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_select_multiple();
	dialog.set_transient_for(*this);
	dialog.add_button("Select", Gtk::RESPONSE_OK);
	dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);

	auto filter_mp3 = Gtk::FileFilter::create();
	filter_mp3->set_name(".mp3");
	filter_mp3->add_mime_type("audio/mp3");
	dialog.add_filter(filter_mp3);
	int res = dialog.run();
	dialog.hide();
	switch(res)
	{
		case(Gtk::RESPONSE_OK):
		{
			std::vector<std::string> selectedFileNames;
			/*std::string*/ mSelectedFileNames = dialog.get_filenames();
			std::cout << mSelectedFileNames.size();
//			std::vector<Gtk::Label> vLabel;
//			Gtk::Label vLabel[25];
//			vLabel.resize(mSelectedFileNames.size());
			int i =0;
			for(auto itr = mSelectedFileNames.begin(); itr != mSelectedFileNames.end(); itr++)
			{
				std::cout << *itr << std::endl;
				vLabel[i].set_label(*itr);
				listbox.add(vLabel[i]);
				i++;
			}
			show_all_children();
			//this->hide();
//			std::cout << "working fine\n" << "filename is :" << dialog.get_filename() << std::endl;
			
			std::string uri("file:");
			uri.append(dialog.get_filename());
			testThread= thread(&Button::playSong, this,uri);
			testThread.detach();
//			playSong(uri);
		}
	}
}

Button::~Button()
{
	std::cout<<"Destructor\n";
	if(playaudio)
	{
		delete playaudio;
		std::cout << "playaudio object deleted\n";
	}
}


//void Button::on_button_folder_clicked()
//{
//	Gtk::FileChooserDialog dialog("Choose folder", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
//	dialog.set_transient_for(*this);
//	dialog.add_button("Select", Gtk::RESPONSE_OK);
//	dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
//
//	int res = dialog.run();
//	switch(res)
//	{
//		case(Gtk::RESPONSE_OK):
//		{
//			std::cout << "working fine\n" << "folder is : " << dialog.get_filename();
//			std::string uri("file:");
//			uri.append(dialog.get_filename());
//			std::cout << "uri is " << uri << std::endl;
//			break;
//		}
//		case(Gtk::RESPONSE_CANCEL):
//		{
//			std::cout << "cancel operation\n";
//			break;
//		}
//	}
//}
