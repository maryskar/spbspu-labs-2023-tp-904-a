#include "commands.hpp"
#include "sub-commands-list.hpp"

std::ostream & turkin::add(base_t & base, std::istream & in, std::ostream & out)
{
  std::string type = "";
  in >> type;
  if (base.empty() && type != "DICT")
  {
    throw std::runtime_error("empty source");
  }
  return sub_add_list[type](base, in, out);
}

std::ostream & turkin::remove(base_t & base, std::istream & in, std::ostream & out)
{
  if (base.empty())
  {
    throw std::runtime_error("empty source");
  }
  std::string type = "";
  in >> type;
  return sub_remove_list[type](base, in, out);
}

std::ostream & turkin::find(base_t & base, std::istream & in, std::ostream & out)
{
  if (base.empty())
  {
    throw std::runtime_error("empty source");
  }
  std::string type = "";
  in >> type;
  return sub_find_list[type](base, in, out);
}
    
std::ostream & turkin::count(base_t & base, std::istream & in, std::ostream & out)
{
  std::string type = "";
  in >> type;
  return sub_count_list[type](base, in, out);
}

std::ostream & turkin::save(base_t & base, std::istream & in, std::ostream & out)
{
  std::string type = "";
  in >> type;
  return sub_save_list[type](base, in, out);
}

std::ostream & turkin::help(base_t & base, std::istream & in, std::ostream & out)
{
  std::string type = "";
  in >> type;
  return sub_help_list[type](base, in, out);
}
