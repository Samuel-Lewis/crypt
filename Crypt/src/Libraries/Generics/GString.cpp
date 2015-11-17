#include "GString.h"

// print that string
std::ostream& GString::print(std::ostream& os)
{
    os << "\"" << value.c_str() << "\"";
    return os;
}

std::istream& GString::read(std::istream& is)
{
    // ingore the first " or 256 chars
    is.ignore(256, '\"');
    // get the line without the trailing "
    getline(is, value, '\"');
    return is;
}

size_t GString::size() const
{
    return value.size();
}
