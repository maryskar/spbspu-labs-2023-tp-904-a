#include "read_and_do_comm.h"
#include "functions.h"

namespace kryuchkova
{
  CommandDict::CommandDict():
    input_comm_(initInputComm()),
    inout_comm_(initInputOutComm()),
    cinout_comm_(initCInputOutComm()),
    cinput_comm_(initCInputComm())
  {}

  void CommandDict::handleCommand(std::string comm, std::istream & in, std::ostream & out, std::map< std::string, ErDictionary > & dicts)
  {
    try
    {
      input_comm_.at(comm)(in, dicts);
      return;
    }
    catch (const std::out_of_range & e)
    {}
    inout_comm_.at(comm)(in, out, dicts);
  }

  std::map< std::string, CommandDict::comm_t_input_t > CommandDict::initInputComm()
  {
    std::map< std::string, comm_t_input_t > dict;
    dict["CREATE"] = doCreate;
    dict["INSERT"] = doInsert;
    dict["DELETE"] = doDelete;
    dict["FILL_DICTIONARY"] = fillDict;
    dict["UNITE"] = unite;
    dict["INTERSECT"] = intersect;
    dict["SYMSUBSTRACT"] = symSubtract;
    dict["SUBTRACT"] = subtract;
    return dict;
  }
  std::map< std::string, CommandDict::comm_inout_t > CommandDict::initInputOutComm()
  {
    std::map< std::string, comm_inout_t > dict;
    dict["ADDITION"] = addition;
    return dict;
  }
  std::map< std::string, CommandDict::comm_cinout_t > CommandDict::initCInputOutComm()
  {
    std::map< std::string, comm_cinout_t > dict;
    dict["SEARCH"] = doSearch;
    dict["PRINT"] = printDict;
    dict["FIND_BY_FIRST_LETTER"] = findByFirstLet;
    return dict;
  }
  std::map< std::string, CommandDict::comm_ct_input_t > CommandDict::initCInputComm()
  {
    std::map< std::string, comm_ct_input_t > dict;
    dict["EXPORT_DICTIONARY"] = exportDict;
    return dict;
  }
}
