#ifndef DATA_SOURCE
#define DATA_SOURCE
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

class Data
{
public:
  vector<string> date;
  vector<float> open;
  vector<float> max;
  vector<float> min;
  vector<float> close;
  vector<int> volume;

  int dataLength()
  {
    return volume.size();
  }

  void readFromFile(string filename)
  {
    ifstream file;
    try
    {
      file.open(filename.c_str(), ifstream::in);
      if (!file)
        cerr << "Cannot open file " << filename << endl;
      if (file.good())
      {
        string d;
        char k;
        float o = 0.0;
        float mx = 0.0;
        float mi = 0.0;
        float c = 0.0;
        int v = 0;
        string head = "";
        cout << "Reading from file: " << filename << endl;
        getline(file, head);
        while (file.good())
        {
          getline(file, d, ',');
          file >> o >> k >> mx >> k >> mi >> k >> c >> k >> v;
          open.push_back(o);
          max.push_back(mx);
          min.push_back(mi);
          close.push_back(c);
          volume.push_back(v);
        }
      }
    }
    catch (...)
    {
      cerr << "Cannot read file: " << filename << endl;
    }
  };
};

#endif