#include "commands.h"
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include "error_messages.h"

namespace skarlygina
{
	void analyze(std::string str, Dicts_t& dicts)
	{
		std::string dictname = skarlygina::getWordFromString(str);
		std::string filename = skarlygina::getWordFromString(str);
		std::ifstream file(filename);
		if (!file)
		{
			skarlygina::errorOpenFileMessage(std::cerr);
			std::cout << "\n";
			return;
		}

		skarlygina::Dict_t dict;
		size_t str_number = 1;
		std::string string = "";
		while (!file.eof())
		{
			std::getline(file, string);
			if (string.empty())
			{
				continue;
			}
			skarlygina::makeDictStr(string, str_number++, dict);
		}
		dicts.emplace(dictname, dict);
		file.close();
	}

	void rename(std::string str, Dicts_t& dicts)
	{
		std::string old_name = skarlygina::getWordFromString(str);
		std::string new_name = skarlygina::getWordFromString(str);
		if (dicts.find(old_name) == dicts.end())
		{
			skarlygina::errorInvalidArgsMessage(std::cerr);
			std::cout << "\n";
			return;
		}
		auto temp = dicts.find(old_name)->second;
		dicts.erase(old_name);
		dicts.emplace(new_name, temp);
	}

	void deleteWord(std::string str, Dicts_t& dicts)
	{
		std::string dict_name = skarlygina::getWordFromString(str);
		std::string word = skarlygina::getWordFromString(str);
		if (dicts.find(dict_name) == dicts.end() || dicts.find(dict_name)->second.empty())
		{
			skarlygina::errorInvalidCommandMessage(std::cerr);
			std::cout << "\n";
			return;
		}
		(dicts.find(dict_name))->second.erase(word);
	}

	void printWord(std::string str, const Dicts_t& dicts)
	{
		std::string dict_name = skarlygina::getWordFromString(str);
		std::string word = skarlygina::getWordFromString(str);
		bool isFound = false;
		if ((dicts.find(dict_name) == dicts.end()) || ((*dicts.find(dict_name)).second.empty()))
		{
			skarlygina::errorInvalidCommandMessage(std::cerr);
			std::cout << "\n";
			return;
		}
		using ostreamIterator_t = typename std::ostream_iterator< size_t >;
		for (auto i = (dicts.find(dict_name))->second.cbegin(); i != (dicts.find(dict_name))->second.cend(); i++)
		{
			if (i->first == word)
			{
				std::cout << i->first << " ";
				std::copy(i->second.cbegin(), i->second.cend(), ostreamIterator_t(std::cout, " "));
				std::cout << "\n";
				isFound = true;
			}
		}
		if (!isFound)
		{
			std::cerr << "The word is not in this dictionary\n";
		}
	}

	void merge(std::string str, Dicts_t& dicts)
	{
		std::vector<std::string> dicts_names;
		std::string dict_name = skarlygina::getWordFromString(str);
		while (!dict_name.empty())
		{
			dicts_names.push_back(dict_name);
			dict_name = skarlygina::getWordFromString(str);
		}
		if ((dicts.find(dicts_names[0]) == dicts.cend()))
		{
			skarlygina::errorInvalidArgsMessage(std::cerr);
			std::cout << "\n";
			return;
		}
		auto iterator = dicts.find(dicts_names[0]);
		Dict_t result = iterator->second;
		for (size_t i = 1; i < dicts_names.size(); i++)
		{
			auto iterator = dicts.find(dicts_names[i]);
			if (iterator == dicts.cend())
			{
				skarlygina::errorInvalidCommandMessage(std::cerr);
				std::cout << "\n";
				return;
			}
			for (auto j = iterator->second.cbegin(); j != iterator->second.cend(); j++)
			{
				if (result.find(j->first) == result.cend())
				{
					result.emplace(j->first, j->second);
				}
			}
		}
		dicts.erase(dicts.find(dicts_names[0]));
		dicts.emplace(dicts_names[0], result);
	}
}
