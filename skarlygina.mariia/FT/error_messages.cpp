#include "error_messages.h"
#include <iostream>
namespace skarlygina
{
	std::ostream& errorOpenFileMessage(std::ostream& out)
	{
		out << "<ERROR INCORRECT FILE>";
		return out;
	}
  std::ostream& errorEmptyMessage(std::ostream& out)
  {
    out << "<EMPTY ERROR>";
    return out;
  }
  std::ostream& errorInvalidArgsMessage(std::ostream& out)
  {
    out << "<INVALID ARGUMENTS>";
    return out;
  }
  std::ostream& errorInvalidCommandMessage(std::ostream& out)
  {
    out << "<INVALID COMMAND>";
    return out;
  }
}
