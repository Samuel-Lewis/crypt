#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <streambuf>

static inline std::vector<std::string> splitLine(std::string line, bool &good)
{
    std::vector<std::string> parts;
    std::string value = "";
    bool escaped = false;
    char escapeChar = '\0';
    int escapeDepth = 0;

    if (line == "")
    {
        return parts;
    }

    for (unsigned i = 0; i < line.length(); i++)
    {
        if (line[i] == '[')
        {
            if (escapeChar == ']' || escapeChar == '\0')
            {
                escapeChar = ']';
                escaped = true;
                escapeDepth++;
            }
            // keep the [
            value += line[i];
        }
        else if (line[i] == '{')
        {
            if (escapeChar == '}' || escapeChar == '\0')
            {
                escapeChar = '}';
                escaped = true;
                escapeDepth++;
            }
            // keep the [
            value += line[i];
        }
        else if (line[i] == escapeChar)
        {
            if (--escapeDepth == 0)
            {
                escapeChar = '\0';
                escaped = false;
            }
            // keep the ]
            value += line[i];
        }
        else if (line[i] == ',' && !escaped)
        {
            // Split by the comma (if not escaped)
            parts.push_back(value);
            value = "";
        }
        else
        {
            value += line[i];
        }
    }

    if (escaped)
    {
        std::cerr << "GWarning: Generic missing inner " << escapeChar << std::endl;
        good = false;
    }

    // Add the last value
    parts.push_back(value);
    return parts;
}

static inline std::string flattern(std::string str)
{
    std::size_t nextPos = str.find_first_of("\t\n");
    while(nextPos != std::string::npos)
    {
        str.erase(nextPos, 1);
        nextPos = str.find_first_of("\t\n");
    }
    return str;
}

static inline std::string streamToString(std::istream &stream)
{
    return std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
}

#endif // UTILS_H
