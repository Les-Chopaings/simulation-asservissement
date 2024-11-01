#include "statusTextView.h"


statusTextView::statusTextView(GtkWidget * view,std::atomic<bool>* stop_thread){
    mBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(view), GTK_WRAP_WORD);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(view), FALSE);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
    mStop_thread = stop_thread;
    mThreadStatusTextView = g_thread_new("update_thread", thread_func, this);
}

GThread* statusTextView::getThread(){
    return mThreadStatusTextView;
}

gpointer statusTextView::thread_func(gpointer data) {
    statusTextView* stv = (statusTextView*)data;
    std::atomic<bool>* stop_thread = stv->mStop_thread;
    while (1) {
        g_usleep(7000);

        {
            std::lock_guard<std::mutex> lock(stv->mTextMutex);
            stv->mText = generateText();
        }

        // Utiliser g_idle_add pour exécuter update_text dans le thread principal GTK
        g_idle_add(update_text, data);
    }
    return NULL;
}

gboolean statusTextView::update_text(gpointer data) {
    statusTextView* stv = (statusTextView*)data;
    gtk_text_buffer_set_text(stv->mBuffer, stv->mText.c_str(), -1);
    return FALSE;       // Retourner FALSE pour ne pas être appelé à nouveau
}

std::string statusTextView::generateText(void){
    std::string text;
    int16_t x;
    int16_t y;
    int16_t theta;
    commandsAsserv.get_coordinates(x,y,theta);
    text += "x: " + std::to_string(x) + '\n';
    text += "y: " + std::to_string(y) + '\n';
    text += "theta: " + std::to_string(theta) + '\n';
    return text;
}