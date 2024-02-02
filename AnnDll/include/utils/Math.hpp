#ifndef _MATH_HPP_
#define _MATH_HPP_

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <assert.h>
#include "../Matrix.hpp"

using namespace std;

namespace utils
{
  class __declspec(dllexport) Math
  {
  public:
    static void multiplyMatrix(Matrix *a, Matrix *b, Matrix *c);
  };
}

#endif
