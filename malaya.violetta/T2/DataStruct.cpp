#include<iostream>
#include<string>
#include<iomanip>
#include"DataStruct.hpp"
#include"IOStructs.hpp"
#include"IOStreamsGuard.hpp"
std::istream & malaya::operator>>(std::istream & in, DataStruct & dest)
{
  std::istream::sentry istreamChecker(in);
  if (!istreamChecker)
  {
    in.clear();
    in.ignore();
    return in;
  }
  DataStruct data;
  in >> DelimiterIO{"{"};
  if (!in)
  {
    in.clear();
    in.ignore();
    return in; //проверить так ли надо
  }
  // цикл для чтения трех ключей
  for (int i = 0; i < 3; i++)
  {
    int keyNumber = 0;
    in >> LabelIO{"key"} >> keyNumber >> DelimiterIO{":"};
    if (!in)
    {
      in.clear(); // ????
      in.ignore();
      return in;
    }
    switch (keyNumber)
    {
      case 1:
        in >> data.key1;
        break;
      case 2:
        in >> data.key2;
        break;
      case 3:
        in >> data.key3;
        break;
      default:
        in.clear(); // так ли это делать?
        in.ignore();
        return in;
    }
  }
  in >> DelimiterIO{"}"}; //???????????????????????
}

std::ostream& malaya::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry ostreamChecker(out);
  if (!ostreamChecker)
  {
    out.clear();
    return out;
  }
  IOStreamsGuard guard(out);
  out << "{ " << "\"key1\": " << std::fixed << std::setprecision(1) << data.key1 << "d, "; //проверить
  out << "\"key2\": " << std::setprecision(3) << data.key2;
  out << "\"key3\": " << data.key3 << " }";
  return out;
}
