#include "huffman-code.hpp"
#include "comporator.hpp"
#include <numeric>

turkin::encoding_t turkin::encode(const phrase_t & phrase, const encoding_map_t & map)
{
  encoding_t result;
  std::accumulate(phrase.begin(), phrase.end(), result, CopyCode(map));
  return result;
}
