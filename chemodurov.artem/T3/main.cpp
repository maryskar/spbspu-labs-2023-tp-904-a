#include <iostream>
#include <fstream>

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Not correct number of CML args\n";
    return 1;
  }
  std::ifstream ifstream(argv[1]);
  if (!ifstream.is_open())
  {
    std::cerr << "The file doesn't open\n";
    return 1;
  }

  return 0;
}
