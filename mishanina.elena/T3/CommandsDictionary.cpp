#include "CommandsDictionary.h"
namespace mishanina
{
  CommandDictionary::CommandDictionary()
  {
    dict_out.insert({"AREA EVEN", printAreaEven});
    dict_out.insert({"AREA ODD", printAreaOdd});
    dict_out.insert({"AREA MEAN", printAreaMean});
    dict_out.insert({"MAX AREA", printMaxArea});
    dict_out.insert({"MAX VERTEXES", printMaxVertexes});
    dict_out.insert({"MIN AREA", printMinArea});
    dict_out.insert({"MIN VERTEXES", printMinVertexes});
    dict_out.insert({"COUNT EVEN", printCountEven});
    dict_out.insert({"COUNT ODD", printCountOdd});
    dict_out.insert({"RECTS", printRects});
    dict_num.insert({"AREA NUM", printAreaNumOfVertexes});
    dict_num.insert({"COUNT NUM", printCountNumOfVertexes});
    dict_rm.insert({"RMECHO", printRmecho});
  }
  std::string CommandDictionary::readCommand(std::istream &in)
  {
    std::string cmd = " ";
    in >> cmd;
    if (!in)
    {
      throw std::runtime_error("Error : invalid read cmd");
    }
    if (cmd != "RMECHO" && cmd != "RECTS")
    {
      std::string cmd2 = " ";
      in >> cmd2;
      if (!in)
      {
        throw std::invalid_argument("Invalid parameter");
      }
      cmd += " ";
      cmd += cmd2;
    }
    return cmd;
  }
  void CommandDictionary::doCommandOut(std::string &cmd, const vect_pol &pols, std::ostream &out) const
  {
    auto func = dict_out.at(cmd);
    func(pols, out);
  }
  void CommandDictionary::doCommandNum(std::string &cmd, const vect_pol &pols, std::ostream &out, std::size_t num) const
  {
    auto func = dict_num.at(cmd);
    func(pols, out, num);
  }
  void CommandDictionary::doCommandRm(std::string &cmd, vect_pol &pols, std::ostream &out, std::istream &in) const
  {
    auto func = dict_rm.at(cmd);
    func(pols, out, in);
  }
  void CommandDictionary::doCommand(vect_pol &pols, std::string &cmd, std::istream &in, std::ostream &out)
  {
    try
    {
      doCommandOut(cmd, pols, out);
      return;
    }
    catch (const std::out_of_range &e)
    {
    }
    try
    {
      doCommandRm(cmd, pols, out, in);
      return;
    }
    catch (const std::out_of_range &e)
    {
    }
    std::size_t sep = cmd.find(' ');
    std::size_t num = std::stoull(cmd.substr(sep));
    std::string fin_cmd = cmd.substr(0, sep) + " NUM";
    doCommandNum(fin_cmd, pols, out, num);
  }
}
