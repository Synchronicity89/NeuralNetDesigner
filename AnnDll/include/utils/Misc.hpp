#ifndef _MISC_HPP_
#define _MISC_HPP_

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <filesystem>

using namespace std;
 
namespace utils
{
  class __declspec(dllexport) Misc
  {
  public:
    static vector< vector<double> > fetchData(string path);
    static void writeData(string path, vector< vector<double> > data);
  };
}

#endif
