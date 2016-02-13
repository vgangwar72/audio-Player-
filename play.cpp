#include "play.h"

GMainLoop* playAudio::loop = NULL;
GstElement* playAudio::pipeline = NULL;

gboolean playAudio::bus_call(GstBus *bus, GstMessage *msg, void *user_data)
{
	switch (GST_MESSAGE_TYPE(msg)) {
	case GST_MESSAGE_EOS: {
		g_message("End-of-stream");
		g_main_loop_quit(loop);
		break;
	}
	case GST_MESSAGE_ERROR: {
		GError *err;
		gst_message_parse_error(msg, &err, NULL);
		g_error("%s", err->message);
		g_error_free(err);

		g_main_loop_quit(loop);
		break;
	}
	default:
		break;
	}

	return true;
}

void playAudio::play_uri(const char *uri)
{
//	std::cout << "playAudio::play_uri => uri is " << uri ;//<< std::endl;
//	std::string finalUri(uri);
//	finalUri.erase(std::remove(finalUri.begin(), finalUri.end(), '\n'), finalUri.end());
//	uri = finalUri.c_str();
	GstBus *bus;

	loop = g_main_loop_new(NULL, FALSE);
	pipeline = gst_element_factory_make("playbin", "player");

//	std::cout << "playAudio::play_uri => uri is " << uri ;//<< std::endl;
	if (uri)
	{
//		std::cout << "\nuri is fine ";// << uri; 
		g_object_set(G_OBJECT(pipeline), "uri", uri, NULL);
	}
//	else
//		std::cout << "uri is null";
	bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
	gst_bus_add_watch(bus, bus_call, NULL);
	gst_object_unref(bus);

	gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PLAYING);

	g_main_loop_run(loop);

	//pause audio	
	//gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PAUSED);	

	gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_NULL);
	gst_object_unref(GST_OBJECT(pipeline));
}

void playAudio::pause()
{
	gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PAUSED);
}

void playAudio::stop()
{
	//g_main_loop_quit(loop);
	gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_NULL);
//	gst_object_unref(GST_OBJECT(pipeline));
}

void playAudio::resume()
{
	gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PLAYING);
}
