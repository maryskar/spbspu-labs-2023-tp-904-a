#include <iostream>
#include <fstream>
#include <map>
int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Check arguments\n";
    return 1;
  }
  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "File not open\n";
    return 2;
  }

  return 0;
}
