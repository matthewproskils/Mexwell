#include "debug.hpp"

extern "C"
{
  void runMex(char* mexData)
  {
    string d = mexData;
    Mex(d);
  }
  void runMexDebug(char* mexData)
  {
    string d = mexData;
    MexDebug(d);
  }
}
