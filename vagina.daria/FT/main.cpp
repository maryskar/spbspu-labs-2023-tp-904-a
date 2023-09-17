#include "commands.hpp"
#include "dictionary.hpp"
#include <iostream>



int main()
{
  dictionaryOfNames allDicts{};
  while (!std::cin.eof())
  {
    try
    {
      createSet(allDicts, std::cin);
      threeMostPopular(allDicts, std::cin, std::cout);
      findWord(allDicts, std::cin, std::cout);
      deleteWord(allDicts, std::cin, std::cout);
      //dictionary dict2;
      //createSet (dict2, std::cin);
      ////countIndentical(dict, dict2, std::cout);
      //wordsWithLetter(dict, std::cin, std::cout);
      //wordsWithLetter(dict2, std::cin, std::cout);
      /*Dictionary dict3;*/
      /*uniqueWord(dict3, dict, dict2);
      std::cout << "\n";
      printWordToSpecificLetter(dict3, std::cin, std::cout);*/
      /*threeMostPopular(dict, std::cout);
      std::cout << "\n";
      findWord(dict, std::cin, std::cout);
      std::cout << "\n";
      deleteWord(dict, std::cin, std::cout);
      std::cout << "\n";
      for (const auto& pair : dict.dict_)
      {
        std::cout << pair.first << " : " << pair.second << std::endl;
      }
      printWordToSpecificLetter(dict, std::cin, std::cout);
      std::cout << "\n";
      printDictionary(dict, std::cout);*/
      /*std::cout << "\n";
      minCountLetterDictionary(dict, std::cout);*/
    }
    catch (const std::runtime_error&)
    {
      break;
    }
  }
  return 0;
}