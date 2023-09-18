#ifndef COMMANDSIMPL_H
#define COMMANDSIMPL_H
#include "commands.h"
dictOfTranslations createDictOftranslations(std::istream &in);
void createDict(std::istream &in, dictOfDicts &dict);
void outDictionaries(const dictOfDicts &dicts, std::ostream &out);
void translate(std::istream &in, dictOfDicts &dicts, std::ostream &out);
void help(std::ostream &out);
void doIntersect(std::istream &in, dictOfDicts &dicts, std::ostream &out);
void unite(std::istream &in, dictOfDicts &dicts, std::ostream &out);
void addHistory(const std::string &command);
void showHistory(std::ostream &out);
#endif