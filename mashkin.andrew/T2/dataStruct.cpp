#include "dataStruct.h"
#include <bitset>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>

namespace mashkin
{
  std::string getDoubleString(const mashkin::DataStruct& data)
  {
    std::string varString = std::to_string(data.key1);
    size_t varPow = varString.find_first_not_of("0.");
    double dblWithMantissa = 0.0;
    std::string result;
    if (varPow > 1)
    {
      dblWithMantissa = data.key1 * pow(10, varPow - 1);
      result = std::to_string(dblWithMantissa) + "e-" + std::to_string(varPow - 1);
    }
    else
    {
      varPow = varString.find_first_of(".");
      dblWithMantissa = data.key1 / pow(10, (varPow - 1));
      result = std::to_string(dblWithMantissa) + "e+" + std::to_string(varPow - 1);
    }
    while (result.find_last_of('e') - 1 == result.find_last_of('0') &&
           result.find_last_of('0') != std::to_string(dblWithMantissa).find_last_not_of('0') + 1)
    {
      result.erase(std::begin(result) + result.find_last_of('0'));
    }
    {
      return result;
    }
  }

  std::string getUllBinStr(const mashkin::DataStruct& data)
  {
    unsigned long long varUll = data.key2;
    std::string result = "";
    while (varUll)
    {
      result = std::to_string(varUll % 2) + result;
      varUll /= 2;
    }
    result = "0b0" + result;
    return result;
  }

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  /*void getKey1(std::istream& inp, std::string& var, mashkin::DataStruct& varData)
  {
    inp >> var;
    std::string dblSCI;
    std::copy(std::begin(var), std::begin(var) + var.find_last_of(':'), std::back_inserter(dblSCI));
    var.erase(std::begin(var), std::begin(var) + var.find_last_of(':') + 1);
    if (dblSCI.find_first_of("eE") != std::string::npos && dblSCI.find_first_of('.') == 1 && *dblSCI.begin() != '0')
    {
      varData.key1 = std::stod(dblSCI);
    }
    else
    {
      inp.setstate(std::ios::failbit);
    }
  }*/

  std::istream& operator>>(std::istream& in, DoubleIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
  }

  /*void getKey2(std::istream& inp, std::string& var, mashkin::DataStruct& varData)
  {
    inp >> var;
    if (var.find_first_of("Bb") != 1)
    {
      inp.setstate(std::ios::failbit);
      return;
    }
    else
    {
      std::string binaryUll;
      var.erase(std::begin(var), std::begin(var) + 2);
      std::copy(std::begin(var), std::begin(var) + var.find_last_of(':'), std::back_inserter(binaryUll));
      varData.key2 = std::bitset< 64 >(binaryUll).to_ullong();
      var.erase(std::begin(var), std::begin(var) + var.find_last_of(':') + 1);
    }
  }*/

  std::istream& operator>>(std::istream& in, UllIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string var;
    std::getline(in, var, ':');
    if (var.substr(0, 2) != "0b")
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    dest.ref = std::bitset< 64 >(var.substr(2)).to_ullong();
    return in;
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    std::getline(in, data, 'y');
    data += 'y';
    if (data[0] == ':')
    {
      data.erase(std::begin(data));
    }
    if (data != dest.exp)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    {
      using sep = DelimiterIO;
      using label = LabelIO;
      using dbl = DoubleIO;
      using str = StringIO;
      in >> sep{'('} >> sep{':'};
      for (size_t i = 0; i < 3; ++i)
      {
        size_t keyNum;
        in >> label{"key"} >> keyNum;
        if (keyNum == 1)
        {
          in >> dbl{input.key1};
        }
        else if (keyNum == 2)
        {
          in >> UllIO{input.key2};
        }
        else if (keyNum == 3)
        {
          in >> str{input.key3};
        }
        else
        {
          in.setstate(std::ios::failbit);
        }
      }
      in >> sep{':'} >> sep{')'};
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(:key1 " << getDoubleString(src);
    out << ":key2 " << getUllBinStr(src);
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
  }

  iofmtguard::iofmtguard(std::basic_ios< char >& s):
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {
  }

  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }

  bool Comparator::operator()(const DataStruct& first, const DataStruct& second)
  {
    if (first.key1 == second.key1)
    {
      if (first.key2 == second.key2)
      {
        return first.key3.length() < second.key3.length();
      }
      return first.key2 < second.key2;
    }
    else
    {
      return first.key1 < second.key1;
    }
  }
}

/*void getKey1(std::istream& inp, std::string& var, mashkin::DataStruct& varData);
void getKey2(std::istream& inp, std::string& var, mashkin::DataStruct& varData);
void getKey3(std::istream& inp, std::string& var, mashkin::DataStruct& varData);

std::string getDoubleString(const mashkin::DataStruct& data)
{
  std::string varString = std::to_string(data.key1);
  size_t varPow = varString.find_first_not_of("0.");
  double dblWithMantissa = 0.0;
  std::string result;
  if (varPow > 1)
  {
    dblWithMantissa = data.key1 * pow(10, varPow - 1);
    result = std::to_string(dblWithMantissa) + "e-" + std::to_string(varPow - 1);
  }
  else
  {
    varPow = varString.find_first_of(".");
    dblWithMantissa = data.key1 / pow(10, (varPow - 1));
    result = std::to_string(dblWithMantissa) + "e+" + std::to_string(varPow - 1);
  }
  while (result.find_last_of('e') - 1 == result.find_last_of('0') &&
         result.find_last_of('0') != std::to_string(dblWithMantissa).find_last_not_of('0') + 1)
  {
    result.erase(std::begin(result) + result.find_last_of('0'));
  }
  {
    return result;
  }
}

std::string getUllBinStr(const mashkin::DataStruct& data)
{
  unsigned long long varUll = data.key2;
  std::string result = "";
  while (varUll)
  {
    result = std::to_string(varUll % 2) + result;
    varUll /= 2;
  }
  result = "0b0" + result;
  return result;
}

void getKey1(std::istream& inp, std::string& var, mashkin::DataStruct& varData)
{
  inp >> var;
  std::string dblSCI;
  std::copy(std::begin(var), std::begin(var) + var.find_last_of(':'), std::back_inserter(dblSCI));
  var.erase(std::begin(var), std::begin(var) + var.find_last_of(':') + 1);
  if (dblSCI.find_first_of("eE") != std::string::npos && dblSCI.find_first_of('.') == 1 && *dblSCI.begin() != '0')
  {
    varData.key1 = std::stod(dblSCI);
  }
  else
  {
    inp.setstate(std::ios::failbit);
  }
}

void getKey2(std::istream& inp, std::string& var, mashkin::DataStruct& varData)
{
  inp >> var;
  if (var.find_first_of("Bb") != 1)
  {
    inp.setstate(std::ios::failbit);
    return;
  }
  else
  {
    std::string binaryUll;
    var.erase(std::begin(var), std::begin(var) + 2);
    std::copy(std::begin(var), std::begin(var) + var.find_last_of(':'), std::back_inserter(binaryUll));
    varData.key2 = std::bitset< 64 >(binaryUll).to_ullong();
    var.erase(std::begin(var), std::begin(var) + var.find_last_of(':') + 1);
  }
}

void getKey3(std::istream& inp, std::string& var, mashkin::DataStruct& varData)
{
  inp >> var;
  if (var.find_first_of('\"') == std::string::npos)
  {
    inp.setstate(std::ios::failbit);
    return;
  }
  std::string::iterator beginIt = std::begin(var) + var.find_first_of('\"');
  std::string::iterator endIt = std::begin(var) + var.find_last_of('\"');
  while (beginIt == endIt)
  {
    std::string varString;
    inp >> varString;
    var += " " + varString;
    endIt = std::begin(var) + var.find_last_of('\"');
  }
  beginIt++;
  std::copy(beginIt, endIt, std::back_inserter(varData.key3));
  var.erase(std::begin(var), endIt + 2);
}

namespace mashkin
{
  std::istream& operator>>(std::istream& inp, DataStruct& data)
  {
    std::istream::sentry sen(inp);
    if (!sen)
    {
      return inp;
    }
    std::string var;
    DataStruct varData{0.0, 0, ""};
    inp >> var;
    if (*std::begin(var) != '(' || *(std::begin(var) + 1) != ':')
    {
      inp.setstate(std::ios::failbit);
      return inp;
    }
    var.erase(std::begin(var), std::begin(var) + 2);
    for (size_t i = 0; i < 3; ++i)
    {
      if (var == "key1")
      {
        getKey1(inp, var, varData);
      }
      else if (var == "key2")
      {
        getKey2(inp, var, varData);
      }
      else if (var == "key3")
      {
        getKey3(inp, var, varData);
      }
      else
      {
        inp.setstate(std::ios::failbit);
        return inp;
      }
    }
    if (inp.fail())
    {
      return inp;
    }
    data = varData;
    return inp;
  }



  std::ostream& operator<<(std::ostream& out, const DataStruct& data)
  {
    std::ostream::sentry sen(out);
    if (!sen)
    {
      return out;
    }
    out << "(:key1 " << getDoubleString(data);
    out << ":key2 " << getUllBinStr(data);
    out << ":key3 \"" << data.key3 << "\":)";
    return out;
  }
}*/
