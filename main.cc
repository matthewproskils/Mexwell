#include "debug.hpp"
#include "std.hpp"

extern "C"
{
  void runMex(char* mexData)
  {
    Scope *global = mex_std();
    string d = mexData;
    Mex(d, global);
  }
  void runMexDebug(char* mexData)
  {
    Scope *global = mex_std();
    string d = mexData;
    MexDebug(d, global);
  }
}
