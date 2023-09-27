#include "parser.hpp"

#include <ostream>
#include <iostream>

turkin::MakeCMD::MakeCMD():
  main_list_(),
  sub_list_()
{}

turkin::CommandsList & turkin::MakeCMD::get_main()
{
  return main_list_;
}

turkin::SubCommandsList & turkin::MakeCMD::get_sub()
{
  return sub_list_;
}
