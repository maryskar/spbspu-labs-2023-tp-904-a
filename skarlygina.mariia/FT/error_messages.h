#ifndef ERROR_MESSAGES_H
#define ERROR_MESSAGES_H
#include <ios>
namespace skarlygina
{
	std::ostream& errorOpenFileMessage(std::ostream&);
  std::ostream& errorEmptyMessage(std::ostream&);
  std::ostream& errorInvalidArgsMessage(std::ostream&);
  std::ostream& errorInvalidCommandMessage(std::ostream&);
}
#endif
