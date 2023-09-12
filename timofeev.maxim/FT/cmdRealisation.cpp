#include "cmdRealisation.h"
namespace timofeev
{
  void printHelp(std::istream& in, std::ostream& out, dictsOfDicts &)
  {
    out << "Select which command you need:" << "\n";
    out << "Write down \"All\" to get full info:" << "\n";
    out << "Write down \"List\" to get list of command:" << "\n";
    std::string tmp = "";
    in >> tmp;
    if (tmp == "All")
    {
      out << "AddWord Rus - let you add word in Russian with English translation (rus + eng)\n";
      out << "AddWord Eng - let you add word in English with Russian translation (eng + rus)\n";
      out << "Exist - a command that will help you find out if a word is in a any dictionary ";
      out << "and in which one it is\n";
      out << "Delete All - delete all dictionaries\n";
      out << "Delete Eng - delete English dictionary\n";
      out << "Delete Rus - delete Russian dictionary\n";
      out << "DeleteW Rus - delete word in Russian dictionary and it English translation\n";
      out << "DeleteW Eng - delete word in English dictionary and it Russian translation\n";
      out << "Print All - print all dictionaries\n";
      out << "Print Eng - print English dictionary\n";
      out << "Print Rus - print Russian dictionary\n";
      out << "Translate Eng - show you translation of English word in Russian\n";
      out << "Translate Rus - show you translation of Russian word in English\n";
    }
    else if (tmp == "List")
    {
      out << "AddWord Rus " << "AddWord Eng " << "Exist " << "Delete All " << "\n";
      out << "Delete Eng " << "Delete Rus " << "DeleteW Rus " << "DeleteW Eng " << "\n";
      out << "Print All " << "Print Eng " << "Print Rus " << "\n";
      out << "Translate Rus " << "Translate Eng" << "\n";
    }
    else
    {
      throw std::logic_error("Wrong Command");
    }
  }

  void AddWord(std::istream& in, std::ostream&, dictsOfDicts & dicts)
  {
    std::string secPart = "";
    in >> secPart;
    if (secPart == "Rus")
    {

    }
    else if (secPart == "Eng")
    {

    }
    else
    {
      throw std::logic_error("Wrong Command");
    }
  }
}