#include "comporator.hpp"

bool turkin::SortByFreq::operator()(const std::pair< char, t_node > & lhs, const std::pair< char, t_node > rhs)
{
  return lhs.second->data.second < rhs.second->data.second;
}
