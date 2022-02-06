#include "debug.hpp"

int main(int argc, char const *argv[])
{
  const char* filename = "main.mx";
  MexFile(filename);
  return 0;
}

void runMex(string mexData)
{
  Mex(mexData);
}