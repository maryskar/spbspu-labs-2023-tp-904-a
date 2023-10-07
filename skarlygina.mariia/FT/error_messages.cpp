#include "error_messages.h"
#include <iostream>
namespace skarlygina
{
	std::ostream& errorOpenFileMessage(std::ostream& out)
	{
		out << "<ERROR INCORRECT FILE>";
		return out;
	}
}