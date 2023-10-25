#ifndef READ_AND_DO_COMM_H
#define READ_AND_DO_COMM_H
#include <vector>
#include <map>
#include "dictionary.h"

namespace kryuchkova
{
  class CommandDict
  {
    using comm_t_input_t = void(*)(std::istream & in, std::map< std::string, ErDictionary > & dicts);
    using comm_inout_t = void(*)(std::istream & in, std::ostream & out, std::map< std::string, ErDictionary > & dicts);
    using comm_cinout_t = void(*)(std::istream & in, std::ostream & out, const std::map< std::string, ErDictionary > & dicts);
    using comm_ct_input_t = void(*)(std::istream & in, const std::map< std::string, ErDictionary > & dicts);
  public:
    CommandDict();
    void handleCommand(std::string comm, std::istream & in, std::ostream & out, std::map< std::string, ErDictionary > & dicts);
  private:
    std::map< std::string, comm_t_input_t > input_comm_;
    std::map< std::string, comm_inout_t > inout_comm_;
    std::map< std::string, comm_cinout_t > cinout_comm_;
    std::map< std::string, comm_ct_input_t > cinput_comm_;

    std::map< std::string, comm_t_input_t > initInputComm();
    std::map< std::string, comm_inout_t > initInputOutComm();
    std::map< std::string, comm_ct_input_t > initCInputComm();
    std::map< std::string, comm_cinout_t > initCInputOutComm();
  };
}

#endif
