#include "debug.hpp"

extern "C"
{
  void runMex(char* mexData)
  {
    string d = mexData;
    Mex(d);
  }
}
