#ifndef _BUTTON_H_
#define _BUTTON_H_
#include </usr/include/gtkmm-3.0/gtkmm/window.h>
#include </usr/include/gtkmm-3.0/gtkmm/button.h>
#include </usr/include/gtkmm-3.0/gtkmm/stock.h>
#include </usr/include/gtkmm-3.0/gtkmm/buttonbox.h>
#include </usr/include/gtkmm-3.0/gtkmm/listbox.h>
#include </usr/include/gtkmm-3.0/gtkmm/filechooserdialog.h>
#include </usr/include/gtkmm-3.0/gtkmm/filefilter.h>
#include </usr/include/gtkmm-3.0/gtkmm/textview.h>
#include </usr/include/gtkmm-3.0/gtkmm/entry.h>
#include </usr/include/gtkmm-3.0/gtkmm/label.h>
#include </usr/include/gtkmm-3.0/gtkmm/comboboxtext.h>
#include </usr/include/gtkmm-3.0/gtkmm/progressbar.h>
#include </usr/include/glibmm-2.4/glibmm/refptr.h>
#include <iostream>
#include "play.h"
#include <algorithm>
#include <cstdio>
#include <vector>
#include <string>
#include <thread>

#define Info printf("\n%s:%d",__FUNCTION__, __LINE__);

using namespace std;
//using namespace Gtk;

class Button: public Gtk::Window
{
	public:
		Button();
		virtual ~Button();
	protected:
		bool on_delete_event(GdkEventAny* event);
		bool on_button_release_event_m(GdkEventButton* release_event);
		void pauseResume_button_clicked();
		void on_button_folder_clicked();
		void on_button_file_clicked();
		void Next_button_clicked();
		void Previous_button_clicked();
		bool label_selected(GdkEventButton* event);
		void playSong(int songIndex);
	    bool FindSongInMap(string SongName, int& songIndex);
//		void playSong(std::string uri);

	protected:
		Gtk::Button mBtn, mBtnFolder, mBtnFile, mBtnNext, mBtnPrevious;
		Gtk::ButtonBox mBtnBox;
		Gtk::ListBox listbox;
		Gtk::TextView tv;
		Gtk::Entry en;
		Gtk::Label lb, lb1;
		Gtk::ProgressBar mProgressBar;
//		std::vector<Gtk::Label> vLabel;
		Gtk::Label vLabel[25];
		int labelIndex;
		Gtk::ComboBoxText cb;
		playAudio* playaudio;
		static bool isPause;
		std::vector<std::string> mSelectedFileNames;
		thread testThread;
		std::map<int, std::string>mSongList;
		int mCurrentIndex;
};
#endif
