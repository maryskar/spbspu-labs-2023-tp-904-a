#include "CommandExecutor.h"

kumachev::CommandExecutor::CommandExecutor(std::istream &istream, kumachev::State &state):
  istream_(istream),
  state_(state)
{}

void kumachev::CommandExecutor::execute()
{
  std::istream::sentry sentry(istream_);

  if (!sentry) {
    return;
  }

  while (!istream_.eof()) {
    std::string s;
    istream_ >> s;

    if (s == "exit") {
      break;
    }

    process(std::move(s));
  }
}

void kumachev::CommandExecutor::process(std::string &&cmd)
{
  std::istream::sentry sentry(istream_);

  if (!sentry) {
    return;
  }

  // TODO: Parse all commands here
}
