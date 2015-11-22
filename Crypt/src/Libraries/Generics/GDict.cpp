/************************************\
|*   Copyright 2015 Jacob Gonzalez  *|
|*             a1687803             *|
|* -------------------------------- *|
|*          (╯°□°）╯︵ ┻━┻           *|
\************************************/

#include "GDict.h"

 //pretty print
std::ostream& GDict::print(std::ostream& os)
{
    os << "{\n";
    size_t index = 0;

    for (std::map<std::string, Generic *>::iterator it = value.begin(); it != value.end(); ++it)
    {
        os << "\t" << it->first << ": " << it->second;

        if (index++ < value.size()-1)
        {
            os << ",\n";
        }
    }
    os << "\n}";

    return os;
}

std::istream& GDict::read(std::istream& is)
{
    // get the stream without the [
    // if [ doesn't exist then it will read for 256 characters
    std::stringstream flatStream(flattern(streamToString(is)));

    flatStream.ignore(256, '{');
    std::string s;
    getline(flatStream, s);

    // get the line without the ]
    size_t lastBreak = s.find_last_of('}');
    if (lastBreak != std::string::npos)
    {
        s.erase(lastBreak);
    }
    else
    {
        std::cerr << "GWarning: GDict missing last }" << std::endl;
        good = false;
    }

    std::vector<std::string> items = splitLine(s, good);

    for (size_t i = 0; i < items.size(); ++i)
    {
        // replace the : with a space so we can easily read it with the extraction op
        size_t pos = items[i].find_first_of(":");
        if (pos != std::string::npos)
        {
            items[i].replace(pos, 1, " ");
        }
        std::stringstream typeStream(items[i]);

        // get the key without the first "
        std::string key = "";
        typeStream >> key;

        //remove the quotes
        if (key[0] == '\"' && key[key.length()-1] == '\"')
        {
            key.erase(key.begin());
            key.erase(key.end()-1);
        }
        else
        {
            std::cerr << "GWarning: GDict key " << key << " missing \"" << std::endl;
        }

        // get the rest of the typeStream
        std::string val = "";
        getline(typeStream, val);
        // find the type of container
        size_t containerPos = val.find_first_of("{[\"");

        std::stringstream valStream(val);

        if (containerPos != std::string::npos)
        {
            if (val[containerPos] == '[')
            {
                GArray *array = Generic::make<GArray>();
                valStream >> array;
                value[key] = array;
            }
            else if (val[containerPos] == '{')
            {
                GDict *dict = Generic::make<GDict>();
                valStream >> dict;
                value[key] = dict;
            }
            else if (val[containerPos] == '\"')
            {
                // string
                GString *str = Generic::make<GString>();
                valStream >> str;
                value[key] = str;
            }
        }
        else
        {
            // number
            GNumber *num = Generic::make<GNumber>();
            valStream >> num;
            value[key] = num;
        }
    }

    return is;
}

void GDict::set(std::string key, Generic *item)
{
    value[key] = item;
}
