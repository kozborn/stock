#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

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
  double opening;
  double max;
  double min;
  double closing;
  int volume;
  DataRow() : date(""), opening(0.0), max(0.0), min(0.0), closing(0.0), volume(0) {}
  DataRow(string d, double o, double max, double min, double c, int v) : date(d), opening(o), max(max), min(min), closing(c), volume(v) {}
};

struct DataTable
{
  vector<string> date;
  vector<double> open;
  vector<double> max;
  vector<double> min;
  vector<double> close;
  vector<int> volume;
};

int main()
{
  // tmp data to read from file
  string date;
  double open = 0.0;
  double max = 0.0;
  double min = 0.0;
  double close = 0.0;
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
    getline(procadFile, date, ',');

    procadFile >> open >> space >> max >> space >> min >> space >> close >> space >> volume;
    data.date.push_back(date);
    data.open.push_back(open);
    data.max.push_back(max);
    data.min.push_back(min);
    data.close.push_back(close);
    data.volume.push_back(volume);
  }

  double minOpen = *std::min_element(data.open.begin(), data.open.end());
  double maxOpen = *std::max_element(data.open.begin(), data.open.end());
  double minClose = *std::min_element(data.close.begin(), data.close.end());
  double maxClose = *std::max_element(data.close.begin(), data.close.end());

  cout << minOpen << " " << maxOpen << endl;
  cout << minClose << " " << maxClose << endl;

  procadFile.close();

  Fl_Window *window = new Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Stock analyze");

  std::stringstream minSS;
  minSS << "Min open: " << minOpen << " Max open: " << maxOpen;
  Fl_Box *minText = new Fl_Box(40, 20, 220, 20, minSS.str().c_str());

  std::stringstream maxSS;
  maxSS << "Min close: " << minClose << " Max close: " << maxClose;
  Fl_Box *maxText = new Fl_Box(40, 40, 220, 20, maxSS.str().c_str());

  window->end();
  window->show();
  return Fl::run();
}
