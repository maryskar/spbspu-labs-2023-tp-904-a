#ifndef FT_COMMANDS_H
#define FT_COMMANDS_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <functional>
#include <map>
#include <message.h>
#include "funcs_commands.h"

namespace tarasenko
{
  std::istream& readTrash(std::istream& input)
  {
    input.clear();
    std::string trash = " ";
    getline(input, trash);
    return input;
  }

  template< typename Key, typename Value, typename Compare >
  class Commands
  {
   using dict_type = std::map< Key, Value, Compare >;
   using dict_of_dict_t = std::map< std::string, dict_type, std::greater<> >;
  public:
   Commands():
     type_1(),
     type_2(),
     type_3(),
     type_4(),
     type_5()
   {
     type_1.insert({"complement", &complement< Key, Value, Compare >});
     type_1.insert({"intersect", &intersect< Key, Value, Compare >});
     type_1.insert({"union", &unionWith< Key, Value, Compare >});
     type_1.insert({"merge", &merge< Key, Value, Compare >});

     type_2.insert({"print", &print< Key, Value, Compare >});
     type_2.insert({"print_if", &printIf< Key, Value, Compare >});

     type_3.insert({"add", &add< std::string, dict_type, std::greater<> >});
     type_3.insert({"delete", &deleteDicts< Key, Value, Compare >});
     type_3.insert({"write", &writeDicts< Key, Value, Compare >});
     type_3.insert({"resort", &resort< Key, Value, Compare >});
     type_3.insert({"put", &put< Key, Value, Compare >});
     type_3.insert({"copy", &copy< Key, Value, Compare >});
     type_3.insert({"random_dict", &addRandomDict< Key, Value, Compare >});

     type_4.insert({"swap", &swap< Key, Value, Compare >});
     type_4.insert({"update", &update< Key, Value, Compare >});

     type_5.insert({"subset", &isSubset< Key, Value, Compare >});
   }

   void call(const std::string& name_of_command,
      std::map< std::string, dict_type, std::greater<> >& dict_of_dict,
      std::istream& input, std::ostream& output)
   {
     try
     {
       if (findInType1(name_of_command))
       {
         callType1(name_of_command, dict_of_dict, input);
       }
       else if (findInType2(name_of_command))
       {
         callType2(name_of_command, dict_of_dict, input, output);
       }
       else if (findInType3(name_of_command))
       {
         callType3(name_of_command, dict_of_dict, input);
       }
       else if (findInType4(name_of_command) || findInType5(name_of_command))
       {
         callType45(name_of_command, dict_of_dict, input, output);
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
   std::map< std::string, std::function< dict_type(const dict_type&, const dict_type&) >, Compare > type_1;
   std::map< std::string,
      std::function< std::ostream&(std::ostream&, const std::string&, const dict_of_dict_t&) >, Compare > type_2;
   std::map< std::string, std::function< void(std::istream&, dict_of_dict_t&) >, Compare > type_3;
   std::map< std::string, std::function< void(dict_type&, dict_type&) >, Compare > type_4;
   std::map< std::string, std::function< bool(const dict_type&, const dict_type&) >, Compare > type_5;

   bool findInType1(const std::string& key) const;
   bool findInType2(const std::string& key) const;
   bool findInType3(const std::string& key) const;
   bool findInType4(const std::string& key) const;
   bool findInType5(const std::string& key) const;
   void callType1(const std::string& name_of_command, dict_of_dict_t& dict_of_dict, std::istream& input);
   void callType2(const std::string& name_of_command, dict_of_dict_t& dict_of_dict,
      std::istream& input, std::ostream& output);
   void callType3(const std::string& name_of_command, dict_of_dict_t& dict_of_dict, std::istream& input);
   void callType45(const std::string& name_of_command, dict_of_dict_t& dict_of_dict,
      std::istream& input, std::ostream& output);
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

  template< typename Key, typename Value, typename Compare >
  bool Commands< Key, Value, Compare >::findInType3(const std::string& key) const
  {
    return type_3.find(key) != type_3.cend();
  }

  template< typename Key, typename Value, typename Compare >
  bool Commands< Key, Value, Compare >::findInType4(const std::string& key) const
  {
    return type_4.find(key) != type_4.cend();
  }

  template< typename Key, typename Value, typename Compare >
  bool Commands< Key, Value, Compare >::findInType5(const std::string& key) const
  {
    return type_5.find(key) != type_5.cend();
  }

  template< typename Key, typename Value, typename Compare >
  void Commands< Key, Value, Compare >::callType1(const std::string& name_of_command,
     dict_of_dict_t& dict_of_dict, std::istream& input)
  {
    std::string name_new_dict = " ";
    std::string name_dict1 = " ";
    std::string name_dict2 = " ";
    input >> name_new_dict >> name_dict1 >> name_dict2;
    dict_type dict1 = dict_of_dict.at(name_dict1);
    dict_type dict2 = dict_of_dict.at(name_dict2);
    auto new_dict = type_1.at(name_of_command)(dict1, dict2);
    dict_of_dict[name_new_dict] = new_dict;
  }

  template< typename Key, typename Value, typename Compare >
  void Commands< Key, Value, Compare >::callType2(const std::string& name_of_command,
     dict_of_dict_t& dict_of_dict, std::istream& input, std::ostream& output)
  {
    std::string key = " ";
    input >> key;
    type_2.at(name_of_command)(output, key, dict_of_dict);
  }

  template< typename Key, typename Value, typename Compare >
  void Commands< Key, Value, Compare >::callType3(const std::string& name_of_command,
     dict_of_dict_t& dict_of_dict, std::istream& input)
  {
    type_3.at(name_of_command)(input, dict_of_dict);
  }

  template< typename Key, typename Value, typename Compare >
  void Commands< Key, Value, Compare >::callType45(const std::string& name_of_command,
     dict_of_dict_t& dict_of_dict, std::istream& input, std::ostream& output)
  {
    std::string name_dict1 = " ";
    std::string name_dict2 = " ";
    input >> name_dict1 >> name_dict2;

    dict_type dict1 = dict_of_dict.at(name_dict1);
    dict_type dict2 = dict_of_dict.at(name_dict2);
    if (findInType4(name_of_command))
    {
      type_4.at(name_of_command)(dict1, dict2);
      dict_of_dict[name_dict1] = dict1;
      dict_of_dict[name_dict2] = dict2;
    }
    else
    {
      output << std::boolalpha << type_5.at(name_of_command)(dict1, dict2) << "\n";
    }
  }
}
#endif
