#include "NodeIO.h"

#include <iostream>

ganiullin::MapNode::MapNode(const std::pair< const Word, size_t >& pair)
    : pair_(pair)
{
}
std::ostream& ganiullin::operator<<(std::ostream& out, const MapNode& node)
{
  return out << node.pair_.first << ' ' << node.pair_.second;
}
ganiullin::VecNode::VecNode(const std::pair< Word, size_t >& pair)
    : pair_(pair)
{
}
std::ostream& ganiullin::operator<<(std::ostream& out, const VecNode& node)
{
  return out << node.pair_.first << ' ' << node.pair_.second;
}
