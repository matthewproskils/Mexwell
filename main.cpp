#include "debug.hpp"
#include "std.hpp"
int main(int argc, char const *argv[])
{
  Scope* global = mex_std();  
  MexFile("main.mx", global);
  return 0;
}