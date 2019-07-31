#ifndef SPYBOT_DATA_LOADER_HPP
#define SPYBOT_DATA_LOADER_HPP

#include <fstream>
#include <list>
#include <string>

namespace Spybot
{
    class DataLoader
    {   //=========================================================================================================================================
        private:
        struct Data
        {
            std::string attribute;
            std::string value;
        };

        const std::string error;

        std::ifstream dataFile;

        std::string ID; // ID of the current object being parsed.
        std::list<Data> currentData;

        // Helper methods.
        void getDataSubstring(const std::string& source, std::string& destination, char start, char end);
        bool isValidData(const std::string& line);
        void seekCharacter(char desiredChar);

        //=========================================================================================================================================
        public:
        DataLoader(): error("") {}
        /*------------------------------------------------------------------------------------------------------------------------------------
            Creates a DataLoader object that reads from the file at the location specified by the provided filepath.

            Parameter:
            *   filepath: The directory to the data file from which to load Program_Factories.
        */
        DataLoader(const std::string& filepath);

        void open(const std::string& filepath);
        void close();

        const std::string& getAttributeValue(const std::string& attribute) const;

        inline const std::string& getID() const { return ID; }

        /*------------------------------------------------------------------------------------------------------------------------------------
            If another element exists in the loaded data file, this function discards the attribute data of the 
            current element and loads in the attributes of the next element, then returns true. If there are no 
            more elements in the loaded data file, then this function makes no changes to its currently stored 
            attribute data and returns false.

            Returns: True if another element exists in the loaded data file to proceed to, or false otherwise.
        */
        bool loadNext();


    };  //=========================================================================================================================================
}

#endif // SPYBOT_DATA_LOADER_HPP