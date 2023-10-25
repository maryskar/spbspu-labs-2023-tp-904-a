#ifndef DICT_H
#define DICT_H
#include <string>
#include <iosfwd>
#include <iterator>
#include <map>
namespace chulkov
{
  using pairSS = std::pair< std::string, std::size_t >;
  using mapIter = std::map< std::string, std::size_t >::iterator;
  using mapCosntIter = std::map< std::string, std::size_t >::const_iterator;
  class Dict
  {
  public:
    Dict() = default;
    Dict(const Dict& other) = default;
    Dict(const std::string& name);
    ~Dict() = default;
    bool operator==(const Dict& dict) const;

    std::string getName() const;
    std::size_t getSum() const;
    bool empty() const;
    void rename(const std::string& name);
    void print(std::ostream& stream) const;
    void printPair(std::ostream& stream, const pairSS& pair) const;
    void printMostPopular(std::ostream& stream) const;


    void insert(const std::string& word);
    void insertPair(const pairSS pair);
    mapCosntIter search(const std::string& word) const;
    mapIter search(const std::string& word);
    bool deleteWord(const std::string& word);
    void drop();

    mapCosntIter begin() const;
    mapCosntIter end() const;
    mapIter begin();
    mapIter end();
  private:
    std::string name_;
    std::map< std::string, std::size_t > Dict_;
  };
}

#endif
