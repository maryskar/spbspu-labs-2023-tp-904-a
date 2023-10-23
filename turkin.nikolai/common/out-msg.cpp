#include <out-msg.hpp>

void turkin::outInvalidCMD(std::ostream & out)
{
  out << "<INVALID COMMAND>";
}

void turkin::outEmptyCMD(std::ostream & out)
{
  out << "<EMPTY>";
}

void turkin::outAddedCMD(std::ostream & out)
{
  out << "<ADDED>\n";
}

void turkin::outRemovedCMD(std::ostream & out)
{
  out << "<REMOVED>\n";
}

void turkin::outNotFoundedCMD(std::ostream & out)
{
  out << "<NOT FOUND>\n";
}
