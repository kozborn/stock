#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

const int WINDOW_WIDTH = 80;
const int WINDOW_HEIGHT = 60;

const int BOX_MARGIN = 10;

int box_width = (WINDOW_WIDTH / 2) - 2 * BOX_MARGIN;
int box_height = WINDOW_HEIGHT - 2 * BOX_MARGIN;

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

struct DataRow
{
  string date;
  float opening;
  float max;
  float min;
  float closing;
  int volume;
  DataRow() : date(""), opening(0.0), max(0.0), min(0.0), closing(0.0), volume(0) {}
  DataRow(string d, float o, float max, float min, float c, int v) : date(d), opening(o), max(max), min(min), closing(c), volume(v) {}
};

struct DataTable
{
  vector<string> date;
  vector<float> open;
  vector<float> max;
  vector<float> min;
  vector<float> close;
  vector<int> volume;
};

int main()
{
  // tmp data to read from file
  string date;
  float open = 0.0;
  float max = 0.0;
  float min = 0.0;
  float close = 0.0;
  int volume = 0;
  char space = ',';
  // end of tmp data block
  DataTable data;
  cout << "Stock analyze" << endl;
  string line;
  ifstream procadFile;
  procadFile.open("procad.csv");
  procadFile >> line;
  cout << line << endl;
  while (procadFile.good())
  {
    procadFile >> date >> space >> open >> space >> max >> space >> min >> space >> close >> space >> volume;
    data.date.push_back(date);
    data.open.push_back(open);
    data.max.push_back(max);
    data.min.push_back(min);
    data.close.push_back(close);
    data.volume.push_back(volume);
  }

  procadFile.close();

  Fl_Window *window = new Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Stock analyze");
  window->end();
  window->show();
  return Fl::run();
}
