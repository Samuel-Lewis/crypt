#include "GArray.h"

std::ostream& GArray::print(std::ostream& os)
{
    os << "[";
    for (size_t i = 0; i < count(); ++i)
    {
        os << value[i];

        if (i < count()-1)
        {
            os << ", ";
        }
    }
    os << "]";

    return os;
}

std::istream& GArray::read(std::istream& is)
{
    // get the stream without the [
    // if [ doesn't exist then it will read for 256 characters
    std::stringstream flatStream(flattern(streamToString(is)));

    flatStream.ignore(256, '[');
    std::string s;
    getline(flatStream, s);

    // get the line without the ]
    size_t last_break = s.find_last_of(']');
    if (last_break != std::string::npos)
    {
        s.erase(last_break);
    }
    else
    {
        std::cerr << "GWarning: GArray missing last ]" << std::endl;
        good = false;
    }

    std::vector<std::string> items = splitLine(s, good);

    for (size_t i = 0; i < items.size(); ++i)
    {
        std::stringstream typeStream(items[i]);
        // find the type of container
        size_t container_pos = items[i].find_first_of("{[\"");

        if (container_pos != std::string::npos)
        {
            if (items[i][container_pos] == '[')
            {
                GArray *array = Generic::make<GArray>();
                typeStream >> array;
                value.push_back(array);
            }
            else if (items[i][container_pos] == '{')
            {
                GDict *dict = Generic::make<GDict>();
                typeStream >> dict;
                value.push_back(dict);
            }
            else if (items[i][container_pos] == '\"')
            {
                // string
                GString *str = Generic::make<GString>();
                typeStream >> str;
                value.push_back(str);
            }
        }
        else
        {
            // number
            GNumber *num = Generic::make<GNumber>();
            typeStream >> num;
            value.push_back(num);
        }
    }

    return is;
}

size_t GArray::count() const
{
    return value.size();
}

void GArray::add(Generic *item)
{
    value.push_back(item);
}
