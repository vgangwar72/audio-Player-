#ifndef _PLAY_H_
#define _PLAY_H_
#include <gst/gst.h>
#include <stdbool.h>
#include <iostream>

class playAudio
{
	private:
		static GMainLoop* loop;
		static GstElement *pipeline;
	public:
		playAudio()
		{
			std::cout << "playAudio constructor\n";	
		}
		~playAudio()
		{
			std::cout << "playAudio destructor\n";
		}
		// function for showing error message in gstreamer processing
		static gboolean bus_call(GstBus *bus, GstMessage *msg, void *msg_data);
		static void play_uri(const char *uri);
		void stop();
		void pause();
		void resume();
};
#endif
