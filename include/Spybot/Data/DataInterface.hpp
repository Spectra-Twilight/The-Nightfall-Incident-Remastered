#ifndef SPYBOT_DATA_INTERFACE_HPP
#define SPYBOT_DATA_INTERFACE_HPP

#include <cstdint>
#include <string>

namespace Spybot
{
    class DataInterface
    {   //=================================================================================================================================================
        protected:

        constexpr static uint8_t DataElementSizeBytes = 2; // Number of bytes used to track the total size (in bytes) of a data element.
        constexpr static uint8_t IDCharCountBytes = 1; // Number of bytes used to count the number of characters in an element ID.
        const std::string filepath;

        DataInterface(const std::string& initFilepath): filepath(initFilepath) {}

        //=================================================================================================================================================
        public:
        
        virtual void close() = 0;
        virtual bool open() = 0;

    };  //=================================================================================================================================================
}

#endif // SPYBOT_DATA_INTERFACE_HPP