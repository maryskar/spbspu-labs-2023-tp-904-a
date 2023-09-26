#include "encoding-struct.hpp"

#include <algorithm>
#include <iterator>
#include <iostream>

#include "comporator.hpp"
#include "data-types.hpp"

namespace
{
  std::size_t count_encoding(const turkin::phrase_t & phrase, char del)
  {
    std::size_t amount = 0;
    for (char it: phrase)
    {
      if (it == del)
      {
        amount++;
      }
    }
    return amount;
  }
}

turkin::HType::HType():
  root_(),
  list_(),
  map_()
{}

turkin::HType::HType(const phrase_t & phrase):
  root_(),
  list_(),
  map_()
{
  for (char it: phrase)
  {
    std::shared_ptr< node_t > ins = std::make_shared< node_t >(std::make_pair(it, count_encoding(phrase, it)));
    if (list_.find(it) != list_.end())
    {
      continue;
    }
    else
    {
      list_.insert({it, ins});
    }
  }

  queue_t queue;
  for (std::pair< const char, std::shared_ptr< node_t > > it: list_)
  {
    queue.push(it.second);
  }

  while (queue.size() != 1)
  {
    std::shared_ptr< node_t > left = queue.front();
    queue.pop();
    std::shared_ptr< node_t > right = queue.front();
    queue.pop();

    std::size_t sum = left->data.second + left->data.second;
    queue.push(std::make_shared< node_t >(std::make_pair('\0', sum), left, right));
  }
  root_ = queue.front();
  queue.pop();

  encode(root_, "");
}

turkin::HType::HType(const HType & htree):
  root_(copy(htree.root_)),
  list_(htree.list_),
  map_(htree.map_)
{}

turkin::HType::HType(HType && htree):
  root_(htree.root_),
  list_(htree.list_),
  map_(htree.map_)
{
  htree.root_ = nullptr;
  htree.list_.clear();
  htree.map_.clear();
}

turkin::HType & turkin::HType::operator=(const HType & htree)
{
  if (std::addressof(htree) == this)
  {
    return * this;
  }
  root_ = copy(htree.root_);
  list_ = htree.list_;
  map_ = htree.map_;
  return * this;
}

turkin::HType & turkin::HType::operator=(HType && htree)
{
  if (std::addressof(htree) == this)
  {
    return * this;
  }
  root_ = htree.root_;
  list_ = htree.list_;
  map_ = htree.map_;
  htree.root_ = nullptr;
  htree.list_.clear();
  htree.map_.clear();
  return * this;
}

const turkin::encoding_list_t & turkin::HType::get_encoding_list()
{
  return list_;
}

const turkin::encoding_map_t & turkin::HType::get_encoding_map()
{
  return map_;
}

void turkin::HType::encode(std::shared_ptr< node_t > src, encoding_t code)
{
  if (src == nullptr)
  {
    return;
  }

  if (!src->left && !src->right)
  {
    if (map_.find(src->data.first) != map_.end())
    {
      map_[src->data.first] = code;
    }
    else
    {
      map_.insert({src->data.first, code});
    }
  }

  encode(src->left, code + "0");
  encode(src->right, code + "1");
}

std::shared_ptr< turkin::node_t > turkin::HType::copy(std::shared_ptr< node_t > src)
{
  std::shared_ptr< node_t > new_root;
  if (src == nullptr)
  {
    return nullptr;
  }
  new_root = std::make_shared< node_t >(src->data);
  new_root->left = copy(src->left);
  new_root->right = copy(src->right);
  return new_root;
}

std::ostream & turkin::operator<<(std::ostream & out, const encoding_map_t & map)
{
  for (std::map< char, encoding_t >::const_iterator it = map.begin(); it != map.end(); it++)
  {
    out << "| " << it->first << " - " << it->second << " ";
  }
  out << "|";
  return out;
}
