#ifndef DATASTRUCTUR_HPP
#define DATASTRUCTUR_HPP
#include"OtherStructur.hpp"

namespace kazakov
{
    struct DataStructur 
    {
        ExpectedLongLong key1;
        ExpectedChar key2;
        ExpectedString  key3;
    };
    std::ostream& operator << (std::ostream& out, const DataStructur& p);
    std::istream& operator >> (std::istream& in, DataStructur& p);
    bool comparator(const DataStructur& p1, const DataStructur& p2);
}
#endif 
