#ifndef MY_WINDOW_GUARD
#define MY_WINDOW_GUARD 1

#include "GUI.h"
#include "Graph.h"
#include <vector>
#include "Flight.h"

using namespace Graph_lib;

struct MyWindow : Window {
    MyWindow(Point xy, int w, int h, const string& title);

    bool wait_for_button(); // simple event loop

private:
    Button sorting_button;     // the "next" button
    bool button_pushed;     // implementation detail

    static void cb_sorting(Address, Address); // callback for sort_button
    void sorting();            // action to be done when next_button is pressed

};

#endif // MY_WINDOW_GUARD
