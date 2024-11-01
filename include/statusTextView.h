#pragma once

#include <gtk/gtk.h>
#include <glib.h>
#include <thread>
#include <chrono>
#include <atomic>
#include <string>
#include <mutex>
#include "commands.h"


struct TextBufferData {
    char* text;
    GtkTextBuffer* buffer;
};


class statusTextView
{
private:
    GThread* mThreadStatusTextView = NULL;
    GtkTextBuffer* mBuffer;
    std::atomic<bool>* mStop_thread;
    std::string mText;
    std::mutex mTextMutex;
public:
    statusTextView(GtkWidget * view,std::atomic<bool>* stop_thread);
    ~statusTextView();
    GThread* getThread();
    static std::string generateText(void);
    static gpointer thread_func(gpointer data);
    static gboolean update_text(gpointer data);
};