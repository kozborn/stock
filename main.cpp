#include "Simple_window.h"
#include "Graph.h"
#include <stdexcept>

int main()
{
  try
  {
    using namespace Graph_lib;
    Point tl(100, 100);
    cout << "Test" << endl;
    Simple_window win(tl, 600, 400, "Exercise #1");

    win.wait_for_button();
  }
  catch (...)
  {
    cerr << "Something went wrong" << endl;
  }
}