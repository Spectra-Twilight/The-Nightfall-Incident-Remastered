#include <Spybot/DataLoader.hpp>

#include <stdexcept>

#include <Log.hpp>

using namespace std;
using namespace Spybot;

//=========================================================================================================================================

void DataLoader::getDataSubstring(const string& source, string& destination, char start, char finish)
{
    int begin, end;

    for (begin = 1; source[begin - 1] != start; begin++);

    end = begin;
    for (bool escape = false; source[end] != finish || escape; end++)
    {
        if (source[end] == '\\' && !escape)
            escape = true;
        else
            escape = false;
    }

    destination.resize(end - begin);

    for (int i = begin; i < end; i++)
        destination[i - begin] = source[i];
}

//=========================================================================================================================================

bool DataLoader::isValidData(const string& line)
{
    bool escape = false;
    int c;

    // First character MUST be left bracket (not including whitespace).
    for (c = 0; c < line.length(); c++)
    {
        if (line[c] == '[')
            break;
        else if (line[c] != '\t' && line[c] != ' ')
        {
            LOG(Log::Level::ERROR) << "\t\tError: Received unexpected token '" << line[c] << "' when expecting token '['";
            return false;
        }
    }

    // Attribute name can be anything, but must end with a non-escaped right bracket.
    for (c++; c < line.length(); c++)
    {
        if (line[c] == ']' && !escape)
            break;
        else if (line[c] == '\\' && !escape)
            escape = true;
        else
            escape = false;
    }
    escape = false;

    // Next character (not including whitespace) MUST be a colon.
    for (c++; c < line.length(); c++)
    {
        if (line[c] == ':')
            break;
        else if (line[c] != '\t' && line[c] != ' ')
            return false;
    }

    // Next character (not including whitespace) MUST be a quotation mark.
    for (c++; c < line.length(); c++)
    {
        if (line[c] == '"')
            break;
        else if (line[c] != '\t' && line[c] != ' ')
        {
            LOG(Log::Level::ERROR) << "\t\tError: Received unexpected token '" << line[c] << "' when expecting token '\"'";
            return false;
        }
    }

    // Attribute value can be anything, but must end with an un-escaped quotation mark.
    for (c++; c < line.length(); c++)
    {
        if (line[c] == '"' && !escape)
            break;
        else if (line[c] == '\\' && !escape)
            escape = true;
        else
            escape = false;
    }

    return (c < line.length());
}

//=========================================================================================================================================

void DataLoader::seekCharacter(char desiredChar)
{
    char c;
    for (c = dataFile.get(); dataFile.good() && c != desiredChar; c = dataFile.get())
    {
        switch(c)
        {
            //-----------------------------------------------------------------------------------------------------------------------------
            case '#': // Comments
                dataFile.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore to end of line.
            break;
            //-----------------------------------------------------------------------------------------------------------------------------
            case ' ': case '\n': case '\t': // Whitespace
            break; // Do nothing.
            //-----------------------------------------------------------------------------------------------------------------------------
            default: // Report invalid characters, but otherwise ignore them.
                LOG(Log::Level::ERROR) << "Unexpected character in data file: " << c << ", ignoring...";
            break;
            //-----------------------------------------------------------------------------------------------------------------------------
        }
    }
}

//=========================================================================================================================================

DataLoader::DataLoader(const string& filepath): error("")
{
    open(filepath);
}

//=========================================================================================================================================

void DataLoader::open(const string& filepath)
{
    dataFile.open(filepath);
    if (!dataFile.is_open())
    {
        LOG(Log::Level::ERROR) << "Failed to open program data file at '" << filepath << "'.";
        throw runtime_error("Failed to open program data file at '" + filepath + "'.");
    }
}

//=========================================================================================================================================

void DataLoader::close()
{
    dataFile.close();
}

//=========================================================================================================================================

const string& DataLoader::getAttributeValue(const string& attribute) const
{
    list<Data>::const_iterator iter = currentData.begin();

    while (iter->attribute != attribute && iter != currentData.end())
        iter++;

    if (iter->attribute == attribute)
        return iter->value;
    else
        return error;
}

//=========================================================================================================================================

bool DataLoader::loadNext()
{
    LOG(Log::Level::DEBUG) << "Attempting to load next element...";

    // Parse data file for the start of an element ID.
    seekCharacter('"');

    if (!dataFile.good())
    {
        LOG(Log::Level::DEBUG) << "End of data file.";
        return false;
    }

    // Get ID.
    getline(dataFile, ID, '"');
    LOG(Log::Level::DEBUG) << "ID: " << ID;
    currentData.clear();

    if (!dataFile.good())
    {
        LOG(Log::Level::ERROR) << "Error: Unexpected EOF encountered.";
        return false;
    }

    // Seek the start of the element's definition.
    seekCharacter('{');

    if (!dataFile.good())
    {
        LOG(Log::Level::ERROR) << "Error: Unexpected EOF encountered.";
        return false;
    }

    // Find the first attribute.
    for (char c = dataFile.peek(); dataFile.good() && (c == ' ' || c == '\t' || c == '\n'); c = dataFile.peek())
        dataFile.ignore(1);

    if (!dataFile.good())
    {
        LOG(Log::Level::ERROR) << "Error: Unexpected EOF encountered.";
        return false;
    }
    
    string currentLine;
    for (getline(dataFile, currentLine); currentLine != "}" && dataFile.good(); getline(dataFile, currentLine))
    {
        if (isValidData(currentLine))
        {
            Data newData;
            currentData.push_back(newData);
            getDataSubstring(currentLine, currentData.back().attribute, '[', ']');
            getDataSubstring(currentLine, currentData.back().value, '"', '"');
            LOG(Log::Level::DEBUG) << "\t[" << currentData.back().attribute << "]: \"" << currentData.back().value << "\"";
        }
        else
            LOG(Log::Level::ERROR) << "\tDiscarding invalid attribute line '" << currentLine << "'.";
    }

    return true;
}

//=========================================================================================================================================