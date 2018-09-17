#include "Simple_window.h"
#include "Graph.h"
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include "FL/Fl_Box.H"
#include "FL/Fl_Scroll.H"
#include "Data.h"

const int xmax = 1800;
const int ymax = 700;

const int xoffset = 20;
const int yoffset = 20;

const int xspace = xoffset;
const int yspace = yoffset;

const int xlength = xmax - xoffset - xspace;
const int ylength = ymax - yoffset - yspace;

const int base_open = 0;
const int base_end = 3;

template <typename T>
vector<T> slice(vector<T> &v, int m, int n)
{
  vector<T> vec;
  copy(v.begin() + m, v.begin() + n, back_inserter(vec));
  return vec;
}

template <typename T>
void print(vector<T> &v)
{
  for (auto i : v)
  {
    cout << i << '\t';
  }
  cout << endl;
}

template <typename T>
T getMin(vector<T> &v)
{
  return *std::min_element(v.begin(), v.end());
}

template <typename T>
T getMax(vector<T> &v)
{
  return *std::max_element(v.begin(), v.end());
}

class Scale
{
  int cbase;
  int vbase;
  double scale;

public:
  Scale(int b, int vb, double s) : cbase(b), vbase(vb), scale(s) {}
  int operator()(float v) const { return cbase + (v - vbase) * scale; }
};

void preparePolyline(Open_polyline &poly, vector<float> &data, int min, int max)
{
  const double xscale = double(xlength) / (data.size());
  const double yscale = double(ylength) / (max - min);

  Scale xs(xoffset, 0, xscale);
  Scale ys(ymax - yoffset, min, -yscale);

  const int yStartOffset = (ymax - yoffset);

  for (int i = 0; i < data.size(); ++i)
  {
    poly.add(Point(xs(i), ys(data[i])));
  }
}

int main()
{
  try
  {
    using namespace Graph_lib;
    Data procadData;
    procadData.readFromFile("./data/procad.csv");

    int start = 1550;
    int end = procadData.open.size();

    vector<float> openData = slice(procadData.open, start, end);
    vector<float> closeData = slice(procadData.close, start, end);
    vector<float> minData = slice(procadData.min, start, end);
    vector<float> maxData = slice(procadData.max, start, end);

    int openMin = floor(getMin(openData));
    int openMax = ceil(getMax(openData));

    int closeMin = floor(getMin(closeData));
    int closeMax = ceil(getMax(closeData));

    int minMin = floor(getMin(minData));
    int minMax = ceil(getMax(minData));

    int maxMin = floor(getMin(maxData));
    int maxMax = ceil(getMax(maxData));

    vector<int> mins = {openMin, closeMin, minMin, maxMin};
    vector<int> maxs = {openMax, closeMax, minMax, maxMax};

    int min = getMin(mins);
    int max = getMax(maxs);

    // DRAWING GRAPHS

    Point axisStartPoint(xoffset, ymax - yoffset);
    Simple_window *win = new Simple_window(Point(100, 100), xmax, ymax, "Analyzing procad data");

    Text t(Point(10, 20), "Stock analyze");
    win->attach(t);
    cout << "Data size " << openData.size() << endl;
    Axis xa(Axis::x, axisStartPoint, xlength, openData.size() / (xlength / openData.size()), "Date");
    win->attach(xa);

    Axis ya(Axis::y, axisStartPoint, ylength, 50, "Values");
    win->attach(ya);

    Open_polyline open_poly;
    preparePolyline(open_poly, openData, min, max);
    open_poly.set_color(Color::dark_magenta);
    win->attach(open_poly);

    Open_polyline close_poly;
    preparePolyline(close_poly, closeData, min, max);
    close_poly.set_color(Color::black);
    win->attach(close_poly);

    Open_polyline min_poly;
    preparePolyline(min_poly, minData, min, max);
    min_poly.set_color(Color::red);
    win->attach(min_poly);

    Open_polyline max_poly;
    preparePolyline(max_poly, maxData, min, max);
    max_poly.set_color(Color::dark_green);
    win->attach(max_poly);

    win->wait_for_button();
  }
  catch (...)
  {
    cerr << "Something went wrong" << endl;
  }
}