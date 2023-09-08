#include <iostream>
#include <fstream>
int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Error" << "\n";
    return 1;
  }
  std::ifstream inF;
  if (argc == 2)
  {
    inF.open(argv[1]);
    if (!inF.is_open())
    {
      std::cerr << "Error" << "\n";
      return 1;
    }
  }
}
