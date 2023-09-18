#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <map>
#include "HuffmanCode.h"
#include "Text.h"
#include "typesIO.h"
#include "scopeGuard.h"

void printInfo()
{
  std::cout << "1. READTEXTFROMCONSOLE" << std::endl;
  std::cout << "\n";
  std::cout << "Description:" << std::endl;
  std::cout << "Read text from the console indicating its name, add it to the library." << std::endl;
  std::cout << "\n";
  std::cout << "Example:" << std::endl;
  std::cout << "READTEXTFROMCONSOLE Test text - 0" << std::endl;
  std::cout << "Hello, world!" << std::endl;
  std::cout << "^Z" << std::endl;
  std::cout << "\n\n\n";

  std::cout << "2) SAVETEXT" << std::endl;
  std::cout << "\n";
  std::cout << "Description:" << std::endl;
  std::cout << "Save the text to the specified file." << std::endl;
  std::cout << "\n";
  std::cout << "Example:" << std::endl;
  std::cout << "SAVETEXT Test text - 0" << std::endl;
  std::cout << "text 4.txt" << std::endl;
  std::cout << "\n\n\n";

  std::cout << "3) READTEXTFROMFILE" << std::endl;
  std::cout << "\n";
  std::cout << "Description:" << std::endl;
  std::cout << "Read text from a file indicating its name, add it to the library." << std::endl;
  std::cout << "\n";
  std::cout << "Example:" << std::endl;
  std::cout << "READTEXTFROMFILE Text - 1" << std::endl;
  std::cout << "text 1.txt" << std::endl;
  std::cout << "\n\n\n";

  std::cout << "4) CODEWITHREAD" << std::endl;
  std::cout << "\n";
  std::cout << "Description:" << std::endl;
  std::cout << "Encode text using an encoding derived from it." << std::endl;
  std::cout << "\n";
  std::cout << "Example:" << std::endl;
  std::cout << "CODEWITHREAD Text - 1" << std::endl;
  std::cout << "CodedText - 1" << std::endl;
  std::cout << "Code - 1" << std::endl;
  std::cout << "\n\n\n";

  std::cout << "5) CODE" << std::endl;
  std::cout << "\n";
  std::cout << "Description:" << std::endl;
  std::cout << "Encode the read text based on the existing encoding." << std::endl;
  std::cout << "\n";
  std::cout << "Example:" << std::endl;
  std::cout << "CODE Text - 2" << std::endl;
  std::cout << "Code - 1" << std::endl;
  std::cout << "CodedText - 2" << std::endl;
  std::cout << "\n\n\n";

  std::cout << "6) SAVECODEDTEXT" << std::endl;
  std::cout << "\n";
  std::cout << "Description:" << std::endl;
  std::cout << "Save the encoded text to the specified binary file." << std::endl;
  std::cout << "\n";
  std::cout << "Example:" << std::endl;
  std::cout << "SAVECODEDTEXT CodedText - 1" << std::endl;
  std::cout << "text 1.bin" << std::endl;
  std::cout << "\n\n\n";

  std::cout << "7) SAVECODE" << std::endl;
  std::cout << "\n";
  std::cout << "Description:" << std::endl;
  std::cout << "Save the encoding to the specified file." << std::endl;
  std::cout << "\n";
  std::cout << "Example:" << std::endl;
  std::cout << "SAVECODE Code - 1" << std::endl;
  std::cout << "code 1.txt" << std::endl;
  std::cout << "\n\n\n";
  std::cout << std::endl;

  std::cout << "8) READCODEDTEXTFROMFILE" << std::endl;
  std::cout << "\n";
  std::cout << "Description:" << std::endl;
  std::cout << "Read encoded text with its name from a binary file, add it to the library." << std::endl;
  std::cout << "\n";
  std::cout << "Example:" << std::endl;
  std::cout << "READCODEDTEXTFROMFILE Coded text - 2" << std::endl;
  std::cout << "text 1.bin" << std::endl;
  std::cout << "\n\n\n";
  std::cout << std::endl;

  std::cout << "9) READCODEFROMFILE" << std::endl;
  std::cout << "\n";
  std::cout << "Description:" << std::endl;
  std::cout << "Read the encoding indicating its name from the file, add it to the library." << std::endl;
  std::cout << "\n";
  std::cout << "Example:" << std::endl;
  std::cout << "READCODEFROMFILE Code - 2" << std::endl;
  std::cout << "code 1.txt" << std::endl;
  std::cout << "\n\n\n";
  std::cout << std::endl;

  std::cout << "10) DECODE" << std::endl;
  std::cout << "\n";
  std::cout << "Description:" << std::endl;
  std::cout << "Decode the read encoded text using the read encoding." << std::endl;
  std::cout << "\n";
  std::cout << "Example:" << std::endl;
  std::cout << "DECODE CodedText - 1" << std::endl;
  std::cout << "Code - 1" << std::endl;
  std::cout << "\n\n\n";

  std::cout << "11) MERGE" << std::endl;
  std::cout << "\n";
  std::cout << "Description:" << std::endl;
  std::cout << "Decode two texts, combine them and encode them again." << std::endl;
  std::cout << "\n";
  std::cout << "Example:" << std::endl;
  std::cout << "MERGE CodedText - 1" << std::endl;
  std::cout << "Code - 1" << std::endl;
  std::cout << "CodedText - 2" << std::endl;
  std::cout << "Code - 2" << std::endl;
  std::cout << "CodedText - 3" << std::endl;
  std::cout << "Code - 3" << std::endl;
  std::cout << "\n\n\n";
  std::cout << std::endl;

  std::cout << "12) PRINTCODEDTEXT" << std::endl;
  std::cout << "\n";
  std::cout << "Description:" << std::endl;
  std::cout << "Output the code that was saved to the library." << std::endl;
  std::cout << "\n";
  std::cout << "Example:" << std::endl;
  std::cout << "PRINTCODEDTEXT CodedText - 2" << std::endl;
  std::cout << "\n\n\n";

  std::cout << "13) PRINTCODE" << std::endl;
  std::cout << "\n";
  std::cout << "Description:" << std::endl;
  std::cout << "Output the encoding that was saved to the library." << std::endl;
  std::cout << "\n";
  std::cout << "Example:" << std::endl;
  std::cout << "PRINTCODE Code - 1" << std::endl;
  std::cout << "\n\n\n";

  std::cout << "14) FREQUENCY" << std::endl;
  std::cout << "\n";
  std::cout << "Description:" << std::endl;
  std::cout << "Output the frequency of characters of the text that was added to the library." << std::endl;
  std::cout << "\n";
  std::cout << "Example:" << std::endl;
  std::cout << "FREQUENCY Text - 1" << std::endl;
  std::cout << "\n\n\n";

  std::cout << "15) EFFICIENCY" << std::endl;
  std::cout << "\n";
  std::cout << "Description:" << std::endl;
  std::cout << "Output to the console the efficiency of encoding text that was added to the library: ";
  std::cout << "that is, how many times the file size has decreased." << std::endl;
  std::cout << "\n";
  std::cout << "Example:" << std::endl;
  std::cout << "EFFICIENCY Text - 1" << std::endl;
  std::cout << "\n\n\n";

  std::cout << "16) HELP" << std::endl;
  std::cout << "\n";
  std::cout << "Description:" << std::endl;
  std::cout << "Output information about the functionality of the application to the console." << std::endl;
  std::cout << "\n";
  std::cout << "Example:" << std::endl;
  std::cout << "HELP" << std::endl;
  std::cout << "\n\n\n";
}

int main()
{
  std::map< gudkov::Line, gudkov::Text > libraryText;
  std::map< gudkov::Line, gudkov::BinaryCode > libraryCodedText;
  std::map< gudkov::Line, gudkov::SymbolCodes > librarySymbolsCodes;

  gudkov::iofmtguard fmtguardIn(std::cin);
  std::cin.unsetf(std::ios_base::skipws);

  while (!std::cin.eof())
  {
    std::string command;

    std::cin >> gudkov::LabelIO{ command };

    if (command == "HELP" && std::cin >> gudkov::DelimiterExpIO{ '\n' })
    {
      printInfo();
      continue;
    }

    std::cin >> gudkov::DelimiterExpIO{ ' ' };

    if (command == "READTEXTFROMCONSOLE")
    {
      gudkov::Line textName;
      std::cin >> textName;

      gudkov::Text text;
      std::cin >> text;

      libraryText[textName] = text;

      std::cout << std::endl;
    }
    else if (command == "SAVETEXT")
    {
      gudkov::Line textName;
      std::cin >> textName;

      gudkov::Line fileName;
      std::cin >> fileName;

      std::ofstream file(fileName.toString());

      if (!file.is_open())
      {
        throw std::runtime_error("File for writing text can't be opened.\n");
      }

      file << libraryText[textName];

      std::cout << std::endl;
    }
    else if (command == "READTEXTFROMFILE")
    {
      gudkov::Line textName;
      std::cin >> textName;

      gudkov::Line fileName;
      std::cin >> fileName;

      std::ifstream file(fileName.toString());

      if (!file.is_open())
      {
        throw std::runtime_error("File with text is missing.\n");
      }

      gudkov::Text text;
      file >> text;

      libraryText[textName] = text;

      std::cout << std::endl;
    }
    else if (command == "CODEWITHREAD")
    {
      gudkov::Line textName;
      std::cin >> textName;

      gudkov::Line codedTextName;
      std::cin >> codedTextName;

      gudkov::Line codeName;
      std::cin >> codeName;

      gudkov::HuffmanCode huffmanCode(libraryText[textName]);

      libraryCodedText[codedTextName] = huffmanCode.encode(libraryText[textName]);
      librarySymbolsCodes[codeName] = huffmanCode.getCodeSymbols();;

      std::cout << std::endl;
    }
    else if (command == "CODE")
    {
      gudkov::Line textName;
      std::cin >> textName;

      gudkov::Line codeName;
      std::cin >> codeName;

      gudkov::Line codedTextName;
      std::cin >> codedTextName;

      gudkov::HuffmanCode huffmanCode(librarySymbolsCodes[codeName]);

      libraryCodedText[codedTextName] = huffmanCode.encode(libraryText[textName]);

      std::cout << std::endl;
    }
    else if (command == "SAVECODEDTEXT")
    {
      gudkov::Line textName;
      std::cin >> textName;

      gudkov::Line fileName;
      std::cin >> fileName;

      std::ofstream file(fileName.toString(), std::ios::binary);

      if (!file.is_open())
      {
        throw std::runtime_error("File for writing coded text can't be opened.\n");
      }

      libraryCodedText[textName].writeBinary(file);

      std::cout << std::endl;
    }
    else if (command == "SAVECODE")
    {
      gudkov::Line codeName;
      std::cin >> codeName;

      gudkov::Line fileName;
      std::cin >> fileName;

      std::ofstream file(fileName.toString());

      if (!file.is_open())
      {
        throw std::runtime_error("File for writing codes of symbols can't be opened.\n");
      }

      file << librarySymbolsCodes[codeName];

      std::cout << std::endl;
    }
    else if (command == "READCODEDTEXTFROMFILE")
    {
      gudkov::Line codedTextName;
      std::cin >> codedTextName;

      gudkov::Line fileName;
      std::cin >> fileName;

      std::ifstream file(fileName.toString(), std::ios_base::binary);

      if (!file.is_open())
      {
        throw std::runtime_error("File with coded text is missing.\n");
      }

      gudkov::BinaryCode binaryText;
      binaryText.readBinary(file);

      libraryCodedText[codedTextName] = binaryText;

      std::cout << std::endl;
    }
    else if (command == "READCODEFROMFILE")
    {
      gudkov::Line codeName;
      std::cin >> codeName;

      gudkov::Line fileName;
      std::cin >> fileName;

      std::ifstream file(fileName.toString());

      if (!file.is_open())
      {
        throw std::runtime_error("File with text is missing.\n");
      }

      gudkov::SymbolCodes symbols;
      file >> symbols;

      librarySymbolsCodes[codeName] = symbols;

      std::cout << std::endl;
    }
    else if (command == "DECODE")
    {
      gudkov::Line codedTextName;
      std::cin >> codedTextName;

      gudkov::Line codeName;
      std::cin >> codeName;

      gudkov::HuffmanCode huffmanCode(librarySymbolsCodes[codeName]);

      std::cout << huffmanCode.decode(libraryCodedText[codedTextName]);

      std::cout << std::endl;
      std::cout << std::endl;
    }
    else if (command == "MERGE")
    {
      gudkov::Line codedTextName1;
      std::cin >> codedTextName1;

      gudkov::Line codeName1;
      std::cin >> codeName1;

      gudkov::Line codedTextName2;
      std::cin >> codedTextName2;

      gudkov::Line codeName2;
      std::cin >> codeName2;

      gudkov::Line codedTextName3;
      std::cin >> codedTextName3;

      gudkov::Line codeName3;
      std::cin >> codeName3;

      gudkov::HuffmanCode huffmanCode1(librarySymbolsCodes[codeName1]);
      gudkov::HuffmanCode huffmanCode2(librarySymbolsCodes[codeName2]);

      gudkov::Text text3 = huffmanCode1.decode(libraryCodedText[codedTextName1]) +
        huffmanCode2.decode(libraryCodedText[codedTextName2]);

      gudkov::HuffmanCode huffmanCode3(text3);

      libraryCodedText[codedTextName3] = huffmanCode3.encode(text3);
      librarySymbolsCodes[codeName3] = huffmanCode3.getCodeSymbols();

      std::cout << std::endl;
    }
    else if (command == "PRINTCODEDTEXT")
    {
      gudkov::Line codedTextName;
      std::cin >> codedTextName;

      std::cout << libraryCodedText[codedTextName] << std::endl;

      std::cout << std::endl;
    }
    else if (command == "PRINTCODE")
    {
      gudkov::Line codeName;
      std::cin >> codeName;

      std::cout << librarySymbolsCodes[codeName] << std::endl;

      std::cout << std::endl;
    }
    else if (command == "FREQUENCY")
    {
      gudkov::Line textName;
      std::cin >> textName;

      std::cout << gudkov::CharacterFrequency(libraryText[textName]) << std::endl;

      std::cout << std::endl;
    }
    else if (command == "EFFICIENCY")
    {
      gudkov::Line textName;
      std::cin >> textName;

      size_t countBytes1 = 0;
      size_t countBytes2 = 0;

      gudkov::HuffmanCode huffman(libraryText[textName]);

      {
        std::ofstream outputFile("temp.bin", std::ios::binary);

        if (!outputFile.is_open())
        {
          throw std::runtime_error("File for writing text can't be opened.\n");
        }

        outputFile << libraryText[textName];
        outputFile.close();

        std::ifstream inputFile("temp.bin", std::ios::binary);
        inputFile.seekg(0, std::ios::end);

        countBytes1 = inputFile.tellg();

        inputFile.close();
      }

      {
        std::ofstream outputFile("temp.bin", std::ios::binary);

        if (!outputFile.is_open())
        {
          throw std::runtime_error("File for writing coded text can't be opened.\n");
        }

        huffman.encode(libraryText[textName]).writeBinary(outputFile);
        outputFile.close();

        std::ifstream inputFile("temp.bin", std::ios::binary);
        inputFile.seekg(0, std::ios::end);

        countBytes2 = inputFile.tellg();

        inputFile.close();
      }

      std::remove("temp.bin");

      std::cout << "Initial amount of memory occupied by text: " << countBytes1 << " bytes." << std::endl;
      std::cout << "The amount of memory occupied after encoding: " << countBytes2 << " bytes." << std::endl;
      std::cout << "The amount of memory occupied by the text has decreased by " <<
        static_cast< double >(countBytes1) / countBytes2 << " times." << std::endl;

      std::cout << std::endl;
    }
    else
    {
      std::cerr << "<INVALID COMMAND>" << std::endl;
      gudkov::clearStream(std::cin);

      std::cout << std::endl;
    }
  }

  return 0;
}
