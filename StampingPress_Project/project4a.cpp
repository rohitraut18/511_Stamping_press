//File : project4a.cpp
//Name : Rohit Raut

#include <iostream>
#include "fstreamwrapper.h"
#include <fstream>
#include <deque>
#include <unistd.h>

int main(int argc, char* argv[])
{
  string sr_string = argv[1];
  string rep_str = argv[2];
  string file = argv[3];
  fstreamwrapper f;
  f.file_reading(sr_string, rep_str, file);
  return 0;
}