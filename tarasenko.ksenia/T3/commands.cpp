#include "commands.h"
#include <message.h>
#include <read_trash.h>
#include "funcs_for_map_commands.h"

namespace tarasenko
{
  namespace details
  {
    std::vector< std::string > getNames()
    {
      std::vector< std::string > name_of_cms = {"AREA", "COUNT", "INFRAME", "AREA EVEN", "AREA ODD", "AREA MEAN",
         "MAX AREA", "MIN AREA", "MAX VERTEXES", "MIN VERTEXES", "COUNT EVEN", "COUNT ODD", "RIGHTSHAPES"};
      return name_of_cms;
    }
  }
}

tarasenko::Commands::Commands():
  names(details::getNames()),
  type_1(),
  type_2()
{
  type_1.insert(std::make_pair("AREA", &getAreaWithEqualNumVertsCommand));
  type_1.insert(std::make_pair("COUNT", &getNumWithEqualNumVertsCommand));
  type_1.insert(std::make_pair("INFRAME", &isInFrameCommand));

  type_2.insert(std::make_pair("AREA EVEN", &getAreaEvenCommand));
  type_2.insert(std::make_pair("AREA ODD", &getAreaOddCommand));
  type_2.insert(std::make_pair("AREA MEAN", &getAreaMeanCommand));
  type_2.insert(std::make_pair("MAX AREA", &getMaxAreaCommand));
  type_2.insert(std::make_pair("MIN AREA", &getMinAreaCommand));
  type_2.insert(std::make_pair("MAX VERTEXES", &getMaxVertsCommand));
  type_2.insert(std::make_pair("MIN VERTEXES", &getMinVertsCommand));
  type_2.insert(std::make_pair("COUNT EVEN", &getNumEvenCommand));
  type_2.insert(std::make_pair("COUNT ODD", &getNumOddCommand));
  type_2.insert(std::make_pair("RIGHTSHAPES", &getNumRightShapesCommand));
}

void tarasenko::Commands::call(const std::string& command1, data_t& data, std::istream& in, std::ostream& out)
{
  try
  {
    char c1;
    in.get(c1);
    if (c1 != ' ')
    {
      type_2.at(command1)(data, out) << "\n";
      return;
    }
    else
    {
      char c2;
      in.get(c2);
      in.putback(c2);
      if (isdigit(c2))
      {
        type_1.at(command1)(data, in, out) << "\n";
        return;
      }
    }
    std::string command2 = " ";
    in >> command2;
    type_2.at(command1 + " " + command2)(data, out) << "\n";
  }
  catch (const std::exception&)
  {
    out << outMessageInvalidCommand << "\n";
    readTrash(in);
  }
}

bool tarasenko::Commands::find(const std::string& name)
{
  auto cond = std::bind(std::equal_to< std::string >{}, _1, name);
  return std::any_of(names.begin(), names.end(), cond);
}
