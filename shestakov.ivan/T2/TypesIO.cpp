#include "TypesIO.h"

namespace shestakov
{
    std::istream& operator>>(std::istream& in, DelIO&& dest)
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

    std::istream& operator>>(std::istream& in, LabelIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        for (size_t i = 0; i < dest.str.length(); ++i) {
            in >> DelIO{ dest.str[i] };
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, CharLitIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> DelIO{ '(' } >> dest.ref >> DelIO{ ':' };
    }

    std::istream& operator>>(std::istream& in, CmpLspIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        double real_from_in = 0.0;
        double imag_from_in = 0.0;
        in >> LabelIO{ "#c(" } >> real_from_in >> imag_from_in >> DelIO{')'};
        dest.ref = std::complex< double >(real_from_in, imag_from_in);
        return in;
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest){
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelIO{ '"' }, dest.str, '"');
    }
}
