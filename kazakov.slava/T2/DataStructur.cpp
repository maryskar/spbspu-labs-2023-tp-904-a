#include"DataStructur.hpp"

std::ostream &kazakov:: operator << (std::ostream& out, const kazakov::DataStructur& p) 
{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }
    out << "(" << ":" << "key1" << " " << p.key1 << "ll" << ":" << "key2" << " " << "'" << p.key2 << "'" << ":" << "key3" << " " << "\"" << p.key3 << "\"" << ":" << ")";
    return out;
}
std::istream &kazakov::operator >> (std::istream& in, kazakov::DataStructur& p) 
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    kazakov::DataStructur vrem;
    in >> ExpectedSymbol{ '(' } >> ExpectedSymbol{ ':' };
    std::string getin;
    for (int i = 0; i < 3; i++)
    {
        in >> getin;
        if (getin == "key1")
        {
            in >> vrem.key1;

        }
        if (getin == "key2")
        {
            in >> vrem.key2;
        }
        if (getin == "key3")
        {
            in >> vrem.key3;
        }

        in >> ExpectedSymbol{ ':' };
    }
    in >> ExpectedSymbol{ ')' };

    if (in)
    {
        p = vrem;
    }

    return in;
}
bool kazakov::comparator(const kazakov::DataStructur& p1, const kazakov::DataStructur& p2)
{
    if (p1.key1 == p2.key1 and p1.key2 == p2.key2)
    {
        return p1.key3 < p2.key3;
    }
    if (p1.key1 == p2.key1)
    {
        return p1.key2 < p2.key2;
    }
    return p1.key1 < p2.key1;
}
