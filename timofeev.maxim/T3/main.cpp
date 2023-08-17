#include <iostream>
#include <fstream>
#include "helpFunctions.h"
int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Error\n";
    return 1;
  }
  std::ifstream inFile;
  if (argc == 2)
  {
    inFile.open(argv[1]);
    if (!inFile.is_open())
    {
      std::cerr << "File error" << "\n";
      return 1;
    }
  }

  try
  {

  }
  catch (std::logic_error &e)
  {
    timofeev::printError(std::cout);
  }

}