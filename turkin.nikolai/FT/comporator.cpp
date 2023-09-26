#include "comporator.hpp"

bool turkin::SortByFreq::operator()(const std::pair< char, std::shared_ptr< node_t > > & lhs, const std::pair< char, std::shared_ptr< node_t > > rhs)
{
  return lhs.second->data.second < rhs.second->data.second;
}
