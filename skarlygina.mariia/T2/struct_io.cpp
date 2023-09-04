#include "struct_io.h"
#include "iofmt_guard.h"

#include <iostream>

std::istream& operator>>(std::istream&, delimiter_sep&& dest);
std::istream& operator>>(std::istream&, delimiter_IO&& dest);
std::istream& operator>>(std::istream&, string_IO&& dest);
std::istream& operator>>(std::istream&, DBL_sciIO&& dest);
std::istream& operator>>(std::istream&, ULL_hexIO&& dest);

std::ostream& operator<<(std::ostream& out, const DBL_sciIO& dest);
