#include <iostream>
#include <fstream>
#include "dataStruct.h"

int main(int argc, char* argv[])
{
  using namespace potapova;
  std::ifstream input_file;
  if (argc != 2)
  {
    std::cerr << "Incorrect number of arguments\n";
    return 1;
  }
  else if (argc == 2)
  {
    input_file.open(argv[1]);
    if (!input_file.is_open())
    {
      std::cerr << "Failed to open file\n";
      return 1;
    }
  }
  else
  {
    std::cerr << "No file to open\n";
    return 1;
  }

  return 0;
}