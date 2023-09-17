#ifndef COMMANDS_H
#define COMMANDS_H
#include <functional>
#include <iosfwd>
#include <unordered_map>
#include "hashtable.h"
#include "dictionariesvault.h"
namespace romanovich
{
  class CommandHandler
  {
  public:
    explicit CommandHandler(std::istream &, std::ostream &);
    ~CommandHandler() = default;
    CommandHandler &operator=(CommandHandler &&) = delete;
    void operator()(const std::string &command);
  private:
    std::istream &in_;
    std::ostream &out_;
    std::unordered_map< std::string, std::function< void() > > processor_;
    std::shared_ptr< DictionariesVault::value_t > dictionaries_;
    void addWordToDict();
    void addDict();
    void addTranslation();
    void removeWord();
    void removeTranslation();
    void searchTranslations();
    void searchWords();
    void countWords();
    void countTranslations();
    void exportToFile();
    void help();
    void addMissingWords();
    void createLevelDict();
    void mergeDicts();
    void printDicts(std::ostream &out);
    romanovich::DictionariesVault::value_t::iterator findDictByName(const std::string &dictName);
  };
}
#endif
