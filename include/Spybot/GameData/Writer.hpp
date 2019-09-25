#ifndef SPYBOT_GAME_DATA_WRITER_HPP
#define SPYBOT_GAME_DATA_WRITER_HPP

#include <cstdint>
#include <fstream>
#include <string>

#include <Spybot/GameData/Interface.hpp>

namespace Spybot
{
    namespace GameData
    {
        template <typename T>
        class Writer: public virtual Spybot::GameData::Interface
        {   //============================================================================================================================================
            protected:

            std::ofstream file;

            uint32_t numDataElements;

            //============================================================================================================================================
            public:
            /*--------------------------------------------------------------------------------------------------------------------------------------------
                Default constructor.
            */
            inline Writer(): numDataElements(0) {}

            /*--------------------------------------------------------------------------------------------------------------------------------------------
                Destructor.
            */
            inline virtual ~Writer() { close(); }

            /*--------------------------------------------------------------------------------------------------------------------------------------------
                Inherited from Spybot::GameData::Interface.
            */
            inline void close()
            {
                if (file.is_open())
                {
                    file.seekp(0, std::ios_base::beg);
                    file.write((char*)(&numDataElements), NumElementsBytes);

                    file.close();
                    numDataElements = 0;
                }
            }

            /*--------------------------------------------------------------------------------------------------------------------------------------------
                WARNING: Note that all data stored in the file associated with this object 
                at the time of the call to this function will be lost upon opening the stream.
                If you wish to update or append to the associated data, load it into memory first 
                using a Reader, make the desired changes, and then use a Writer to overwrite 
                the original file.

                Inherited from Spybot::GameData::Interface.

                Returns: True if the associated data file is opened, or false otherwise.
            */
            inline bool open()
            {
                if (file.is_open())
                    close();
                
                file.open(filepath, std::ios_base::binary);
                if (!file.is_open())
                    return false;

                file.write((char*)(&numDataElements), NumElementsBytes); // Holds the position of this value for later writing.
                return true;
            }

            /*------------------------------------------------------------------------------------------------------------------------------------
                Writes srcData to the associated data under the ID provided by srcID, then returns true.

                If the associated data is not currently open at the time of the call to this function, then 
                this function returns false and does nothing else.

                Parameters:
                *   srcID: The ID under which to identify the data being stored.
                *   srcData: The data to store.
                
                Returns: True if the data was written to file, or false otherwise.
            */
            virtual bool put(const std::string& srcID, const T& srcData) = 0;

        };  //============================================================================================================================================
    }
}

#endif // SPYBOT_GAME_DATA_WRITER_HPP