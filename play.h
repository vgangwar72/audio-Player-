#ifndef _PLAY_H_
#define _PLAY_H_
#include <gst/gst.h>
#include <stdbool.h>
#include <iostream>

#define Info printf("\n%s:%d",__FUNCTION__, __LINE__);

class playAudio
{
	private:
		static GMainLoop* loop;
		static GstElement *pipeline;
	public:
		playAudio()
		{
			std::cout << "\nplayAudio constructor";	
		}
		~playAudio()
		{
			std::cout << "\nplayAudio destructor";
		}
		// function for showing error message in gstreamer processing
		static gboolean bus_call(GstBus *bus, GstMessage *msg, void *msg_data);
		void play_uri(const char *uri);
		void stop();
		void pause();
		void resume();
};
#endif
