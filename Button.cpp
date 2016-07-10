#include "Button.h"
#include </usr/include/gtkmm-3.0/gtkmm/listboxrow.h>

bool Button::isPause = false;
bool isPlaying = false;

std::string getlastWord(std::string str)
{
	int pos = str.find_last_of("/");
	int len = str.length();
	std::string out = str.substr(pos+1);
	return out;
}

bool Button::FindSongInMap(string SongName, int& songIndex)
{
	Info
	bool status = false;
	std::map<int, string>::iterator itr;
	itr = mSongList.begin();
	while(itr != mSongList.end())
	{
		if(itr->second == SongName)
		{
			songIndex = itr->first;
			status = true;
			break;
		}
		itr++;
	}
	return status;
}

void Button::playSong(int songIndex)
{
	Info
	// trying to highlight row of listbox. currently it's not working
	Gtk::ListBoxRow* row = listbox.get_row_at_index(songIndex);
	listbox.drag_highlight_row(*row);
	mCurrentIndex = songIndex;
	string uri("file:");
	std::map<int, string>::iterator itr;
	if(!isPlaying)
	{
		playaudio->stop();
		isPlaying = true;
		itr = mSongList.find(songIndex);
		uri.append(itr->second);
		printf("\nuri is %s and isPlaying is %d", uri.c_str(), isPlaying);
		playaudio->play_uri(uri.c_str());
	}
	else
	{
		playaudio->stop();
		isPlaying = false;
		itr = mSongList.find(songIndex);
		uri.append(itr->second);
		printf("\nuri is %s and isPlaying is %d", uri.c_str(), isPlaying);
		playaudio->play_uri(uri.c_str());
	}
}

Button::Button():labelIndex(0)
{
	Info
	//windows in GTKmm open in the centre of the screen
	set_position(Gtk::WIN_POS_CENTER);
	set_default_size(900,400);
	set_resizable(true);
	set_opacity(1);
	playaudio = new playAudio();
//	std::cout<<"Button creation in constructor\n";
	set_title("Button Api");
	add(mBtnBox);
	mBtnBox.pack_start(listbox);
	mBtnBox.pack_start(mBtnFile);
	mBtnFile.set_label("Select");
	mBtnFile.set_alignment(1, 2);
	mBtnFile.signal_clicked().connect( sigc::mem_fun(*this, &Button::on_button_file_clicked) );
	mBtnBox.pack_start(mBtn);
	mBtn.set_label("Pause/Resume");
	mBtn.set_alignment(10, 12);
	mBtn.signal_clicked().connect(sigc::mem_fun(*this, &Button::pauseResume_button_clicked));
	mBtnBox.pack_start(mBtnNext);
	mBtnNext.set_label("Next");
	mBtnNext.signal_clicked().connect(sigc::mem_fun(*this, &Button::Next_button_clicked));
	mBtnBox.pack_start(mBtnPrevious);
	mBtnPrevious.set_label("Previous");
	mBtnPrevious.signal_clicked().connect(sigc::mem_fun(*this, &Button::Previous_button_clicked));
	mBtnBox.pack_start(mProgressBar);
	mProgressBar.set_text("time");
	listbox.signal_button_release_event().connect(sigc::mem_fun(*this, &Button::on_button_release_event_m));
	show_all_children();
	
}

bool Button::label_selected(GdkEventButton* event)
{
	Info
}

//function called when x button is clicked in window.
//if you want to change functionality of x button then overwrite on_delete_event()
bool Button::on_delete_event(GdkEventAny* event)
{
	Info
	this->hide();
	playaudio->stop();
	if(playaudio)
	{
		delete playaudio;
//        	std::cout << "playaudio object deleted\n";
	}
	exit(EXIT_SUCCESS);
}

//function inherited from Gtk::widget 
bool Button::on_button_release_event_m(GdkEventButton* release_event)
{
	Info
	Gtk::ListBoxRow* row = listbox.get_selected_row();
	Gtk::Label* l = dynamic_cast<Gtk::Label*>(row->get_child());
	std::cout << "\nSelected label Name is " << l->get_label() << endl;//row->get_index() << std::endl;
	//testThread.
//	terminate();
	playaudio->stop();
	std::string uri("file:");
	uri.append(l->get_label());
	int songIndex = -1;
	FindSongInMap(l->get_label(), songIndex);
	playSong(songIndex);
}

void Button::pauseResume_button_clicked()
{
	Info
	std::cout<<"\nPause Button clicked";
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

void Button::Next_button_clicked()
{
	Info
	if(++mCurrentIndex == mSongList.size())
		mCurrentIndex = 0;
	playSong(mCurrentIndex);
}

void Button::Previous_button_clicked()
{
	Info
	if(mCurrentIndex == 0)
		mCurrentIndex = mSongList.size() ;
	playSong(--mCurrentIndex);
}

void Button::on_button_file_clicked()
{
	Info
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
//			std::vector<std::string> selectedFileNames;
			/*std::string*/ 
			mSelectedFileNames = dialog.get_filenames();
			int i =0;
			for(auto itr = mSelectedFileNames.begin(); itr != mSelectedFileNames.end(); itr++)
			{
				mSongList[i] = *itr;
				cout << endl;
				std::cout <<mSongList[i] ;
				i++;
//				std::cout << "last word is" << getlastWord(*itr) << std::endl;
				//vLabel[i].set_label(getlastWord(*itr));
				vLabel[labelIndex].set_label(*itr);
				listbox.add(vLabel[labelIndex]);
				labelIndex++;
			}
			show_all_children();
			
			std::string uri("file:");
			uri.append(dialog.get_filename());
			printf("\nfilename = %s and mapSize = %d",(dialog.get_filename()).c_str(), mSongList.size());
			int songNameIndex = -1;
			FindSongInMap(dialog.get_filename(), songNameIndex);
			printf("\nsongNameIndex =%d", songNameIndex);
			testThread= thread(&Button::playSong, this, songNameIndex);
			testThread.detach();
//			playSong(uri);
		}
	}
}

Button::~Button()
{
	Info
//	std::cout<<"\nDestructor";
	if(playaudio)
	{
		delete playaudio;
//		std::cout << "playaudio object deleted\n";
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
