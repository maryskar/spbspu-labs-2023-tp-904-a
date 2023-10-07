#include "commands.h"
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
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

	}
}
