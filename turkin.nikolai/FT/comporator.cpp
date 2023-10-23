#include "comporator.hpp"

bool turkin::SortByFreq::operator()(const std::pair< char, node_t * > & lhs, const std::pair< char, node_t * > rhs)
{
  return lhs.second->data.second < rhs.second->data.second;
}

turkin::StrCount::StrCount(char let):
  let_(let)
{}

bool turkin::StrCount::operator()(const char rhs)
{
  return let_ == rhs;
}

turkin::CopyCode::CopyCode(encoding_map_t map):
  map_(map)
{}

turkin::encoding_t turkin::CopyCode::operator()(encoding_t lhs, const char rhs)
{
  return lhs + map_.at(rhs);
}
