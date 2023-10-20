#ifndef NODE_IO_H
#define NODE_IO_H

#include <cstddef>
#include <iosfwd>
#include <utility>

#include "Word.h"

namespace ganiullin {
  class MapNode {
  public:
    MapNode(const std::pair< const Word, size_t >& pair);
    friend std::ostream& operator<<(std::ostream& out, const MapNode& pair);

  private:
    const std::pair< const Word, size_t >& pair_;
  };
  std::ostream& operator<<(std::ostream& out, const MapNode& pair);

  class VecNode {
  public:
    VecNode(const std::pair< Word, size_t >& pair);
    friend std::ostream& operator<<(std::ostream& out, const VecNode& pair);

  private:
    const std::pair< Word, size_t >& pair_;
  };
  std::ostream& operator<<(std::ostream& out, const VecNode& pair);
}
#endif
