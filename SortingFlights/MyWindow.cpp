#include "MyWindow.h"

//------------------------------------------------------------------------------

MyWindow::MyWindow(Point xy, int w, int h, const string& title) :
    Window(xy, w, h, title),
    sorting_button(Point(x_max() - 100, 0), 100, 40, "<<< SORT >>>", cb_sorting),
    button_pushed(false)
{
    attach(sorting_button);
}

//------------------------------------------------------------------------------

bool MyWindow::wait_for_button()
// modified event loop:
// handle all events (as per default), quit when button_pushed becomes true
// this allows graphics without control inversion
{
    show();
    button_pushed = false;
#if 1
    // Simpler handler
    while (!button_pushed) Fl::wait();
    Fl::redraw();
#else
    // To handle the case where the user presses the X button in the window frame
    // to kill the application, change the condition to 0 to enable this branch.
    Fl::run();
#endif
    return button_pushed;
}

//------------------------------------------------------------------------------

void MyWindow::cb_sorting(Address, Address pw)
// call MyWindow::sorting() for the window located at pw
{
    reference_to<MyWindow>(pw).sorting();
}

//------------------------------------------------------------------------------

void MyWindow::sorting()
{
    button_pushed = true;
    hide();
}

//------------------------------------------------------------------------------
