#ifndef FT_COMMANDS_H
#define FT_COMMANDS_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <functional>
#include <map>
#include <message.h>
#include <read_trash.h>
#include "funcs_map_commands.h"

namespace tarasenko
{
  template< typename Key, typename Value, typename Compare >
  class Commands
  {
   using dict_type = std::map< Key, Value, Compare >;
   using dict_of_dict_t = std::map< std::string, dict_type, std::greater<> >;
  public:
   Commands():
     type_1(),
     type_2()
   {
     type_1.insert({"complement", &complementCommand< Key, Value, Compare >});
     type_1.insert({"intersect", &intersectCommand< Key, Value, Compare >});
     type_1.insert({"union", &unionCommand< Key, Value, Compare >});
     type_1.insert({"merge", &mergeCommand< Key, Value, Compare >});
     type_1.insert({"add", &addCommand< Key, Value, Compare >});
     type_1.insert({"delete", &deleteCommand< Key, Value, Compare >});
     type_1.insert({"resort", &resortCommand< Key, Value, Compare >});
     type_1.insert({"put", &putCommand< Key, Value, Compare >});
     type_1.insert({"copy", &copyCommand< Key, Value, Compare >});
     type_1.insert({"random_dict", &randomCommand< Key, Value, Compare >});
     type_1.insert({"swap", &swapCommand< Key, Value, Compare >});
     type_1.insert({"update", &updateCommand< Key, Value, Compare >});

     type_2.insert({"write", &writeCommand< Key, Value, Compare >});
     type_2.insert({"print", &printCommand< Key, Value, Compare >});
     type_2.insert({"print_if", &printIfCommand< Key, Value, Compare >});
     type_2.insert({"subset", &subsetCommand< Key, Value, Compare >});
   }

   void call(const std::string& name_of_command, dict_of_dict_t& dict_of_dict,
             std::istream& input, std::ostream& output)
   {
     try
     {
       if (findInType1(name_of_command))
       {
         type_1.at(name_of_command)(input, dict_of_dict);
       }
       else if (findInType2(name_of_command))
       {
         type_2.at(name_of_command)(output, input, dict_of_dict);
       }
       else
       {
         throw std::out_of_range("Invalid command");
       }
     }
     catch (const std::invalid_argument& e)
     {
       output << outMessageEmpty << "\n";
       readTrash(input);
     }
     catch (const std::exception& e)
     {
       output << outMessageInvalidCommand << "\n";
       readTrash(input);
     }
   }

  private:
   using command1_t = std::function< std::istream&(std::istream&, dict_of_dict_t&) >;
   using command2_t = std::function< std::ostream&(std::ostream&, std::istream&, const dict_of_dict_t&) >;
   std::map< std::string, command1_t, Compare > type_1;
   std::map< std::string, command2_t, Compare > type_2;
   bool findInType1(const std::string& key) const;
   bool findInType2(const std::string& key) const;
  };

  template< typename Key, typename Value, typename Compare >
  bool Commands< Key, Value, Compare >::findInType1(const std::string& key) const
  {
    return type_1.find(key) != type_1.cend();
  }

  template< typename Key, typename Value, typename Compare >
  bool Commands< Key, Value, Compare >::findInType2(const std::string& key) const
  {
    return type_2.find(key) != type_2.cend();
  }
}
#endif
