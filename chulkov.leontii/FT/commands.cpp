#include "commands.h"
#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>

namespace chulkov {
  struct isName
  {
    bool operator()(const Dict& dictionary, cnstStr& name)
    {
      return dictionary.getName() == name;
    }
  };

  typedef std::map< std::string, int > WordFrequencyMap;
  std::map< std::string, WordFrequencyMap > dictionaries;
  std::vector< std::string > split(const std::string &input, char delimiter) {
    std::vector< std::string > result;
    std::istringstream stream(input);
    std::string token;
    while (std::getline(stream, token, delimiter)) {
      result.push_back(token);
    }
    return result;
  }
  auto isFound(const std::vector< Dict >& dicts, cnstStr& name)
  {
    auto check = std::bind(isName(), std::placeholders::_1, name);
    auto iter = std::find_if(dicts.begin(), dicts.end(), check);
    if (iter == dicts.end())
    {
      throw std::invalid_argument("Dictionary " + name + " wasn't found.");
    }
    return iter;
  }

  auto isFound(std::vector< Dict >& dicts, cnstStr& name)
  {
    auto check = std::bind(isName(), std::placeholders::_1, name);
    auto iter = std::find_if(dicts.begin(), dicts.end(), check);
    if (iter == dicts.end())
    {
      throw std::invalid_argument("Dictionary " + name + " wasn't found.");
    }
    return iter;
  }
  void insert(std::istream& input, std::vector< Dict >& dicts) {
    std::string datasetName, word;
    input >> datasetName >> word;
    auto it = isFound(dicts, datasetName);
    if (it != dicts.end()) {
      it->insert(word);
    }
    else {
      std::cout << "Dataset not found " << '\n';
    }
  }

  void remove(std::istream& input, std::vector< Dict >& dicts) {
    std::string dataset, word;
    input >> dataset >> word;
    auto dictIt = isFound(dicts, dataset);
    if (dictIt != dicts.end()) {
      if (dictIt->deleteWord(word)) {
        std::cout << "Word removed." << '\n';
      } else {
        std::cout << "Word not found in the dataset" << '\n';
      }
    } else {
      std::cout << "Dataset not found" << '\n';
    }
  }

  void search(std::istream& input, std::ostream& output, const std::vector< Dict >& dicts) {
    std::string name{}, word{};
    input >> name >> word;
    auto iter = isFound(dicts, name);
    output << int(iter->search(word) != iter->end());
    output << '\n';
  }

  void printMaxCountWords(std::istream& input, std::ostream& output, const std::vector< Dict >& dicts) {
    std::string dataset, word;
    input >> dataset >> word;
    auto dictIt = isFound(dicts, dataset);
    if (dictIt != dicts.end()) {
      std::_Rb_tree_const_iterator result = dictIt->search(word);
      if (result != dictIt->end()) {
        output << "Frequency of word '" << word << "': " << result->second << '\n';
      } else {
        output << "Word not found in the dataset." << '\n';
      }
    } else {
      output << "Dataset not found" << '\n';
    }
  }

  void print(std::istream& input, std::ostream& output, const std::vector< Dict >& dicts) {
    std::string dataset;
    input >> dataset;
    auto dictIt = isFound(dicts, dataset);
    if (dictIt != dicts.end()) {
      dictIt->print(output);
    } else {
      output << "not found" << '\n';
    }
  }

  void save(std::istream& input, const std::vector< Dict >& dicts) {
    std::string dataset, path;
    input >> dataset >> path;
    auto dictIt = isFound(dicts, dataset);
    if (dictIt != dicts.end()) {
      std::ofstream outFile(path);
      if (outFile.is_open()) {
        dictIt->print(outFile);
        outFile.close();
        std::cout << "Dataset saved to " << path << '\n';
      } else {
        std::cout << "Failed to open file for saving" << '\n';
      }
    } else {
      std::cout << "Dataset not found" << '\n';
    }
  }

  void loadDataset(const std::string& dataset, const std::string& path, std::vector< Dict >& dicts) {
    std::ifstream inFile(path);
    if (inFile.is_open()) {
      Dict newDict(dataset);
      std::string word;
      while (inFile >> word) {
        newDict.insert(word);
      }
      inFile.close();
      dicts.push_back(newDict);
      std::cout << "Dataset loaded from " << path << '\n';
    } else {
      std::cout << "Failed to open file for loading" << '\n';
    }
  }

  void getSize(const std::string& dataset, const std::vector<Dict>& dicts) {
    auto dictIt = isFound(dicts, dataset);
    if (dictIt != dicts.end()) {
      std::cout << "Number of words in dataset '" << dataset << "': " << dictIt->getSum() << '\n';
    } else {
      std::cout << "Dataset not found" << '\n';
    }
  }

  void count(std::istream& input, std::ostream& output, const std::vector< Dict >& dicts) {
    std::string dataset;
    int count = 0;
    input >> dataset >> count;
    auto dictIt = isFound(dicts, dataset);
    if (dictIt != dicts.end()) {
      dictIt->printMostPopular(output);
    } else {
      output << "Dataset not found" << '\n';
    }
  }

  void clear(std::istream& input, std::vector< Dict >& dicts) {
    std::string name{};
    input >> name;
    auto dict = isFound(dicts, name);
    dict->drop();
  }
  void isAvailable(const std::vector< Dict >& dicts, cnstStr& name)
  {
    auto check = std::bind(isName(), std::placeholders::_1, name);
    auto iter = std::find_if(dicts.begin(), dicts.end(), check);
    if (iter != dicts.end())
    {
      throw std::invalid_argument("Dictionary with this name already exists.");
    }
  }
  void getNamesAndDoCommand(std::istream& input, std::vector< Dict >& dicts, cnstStr& cmd)
  {
    std::string name{}, dict1{}, dict2{};
    input >> name >> dict1 >> dict2;
    char symb{};
    isAvailable(dicts, name);
    auto dictionary1 = isFound(dicts, dict1);
    auto dictionary2 = isFound(dicts, dict1);
    if (cmd == "intersect")
    {
      intersectionCommand(dicts, name, dictionary1, dictionary2, cmd, symb);
    }
  }
  void intersect(std::istream& input, std::vector< Dict >& dicts) {
    getNamesAndDoCommand(input, dicts, "intersect");
  }

  void intersectionCommand(std::vector< Dict >& dicts, cnstStr& name, std::vector< Dict >::const_iterator it1, std::vector< Dict >::const_iterator it2, cnstStr& cmd, char c)
  {
    Dict newDictionary(name);
    for (auto& i: *it1)
    {
      auto item = it2->search(i.first);
      if (item == it2->end())
      {
        continue;
      }
      if (i.second <= (*item).second)
      {
        newDictionary.insertPair(i);
      }
      else
      {
        newDictionary.insertPair(*item);
      }
    }
    dicts.push_back(newDictionary);
  }

  void unionData(const std::string& newDataset, const std::vector<std::string>& datasets, std::vector<Dict>& dicts) {
    Dict newUnionDict(newDataset);
    for (const std::string& dataset : datasets) {
      auto dictIt = isFound(dicts, dataset);
      if (dictIt != dicts.end()) {
        for (auto& pair : *dictIt) {
          newUnionDict.insertPair(pair);
        }
      } else {
        std::cout << "Dataset '" << dataset << "' not found" << '\n';
        return;
      }
    }
    dicts.emplace_back(std::move(newUnionDict));
    std::cout << "Union saved as dataset '" << newDataset << "'." << '\n';
    }
}
