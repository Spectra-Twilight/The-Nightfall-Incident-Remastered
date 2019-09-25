#ifndef SPYBOT_GAME_DATA_READER_HPP
#define SPYBOT_GAME_DATA_READER_HPP

#include <cstdint>
#include <fstream>
#include <string>

#include <Spybot/GameData/Interface.hpp>

namespace Spybot
{
    namespace GameData
    {
        template <typename T>
        class Reader: public virtual Spybot::GameData::Interface
        {   //============================================================================================================================================
            protected:

            std::ifstream file;

            uint32_t numDataElements; // Total number of data elements in the file.
            uint32_t currDataElement; // Current data element number being pointed to.

            //============================================================================================================================================
            public:
            /*--------------------------------------------------------------------------------------------------------------------------------------------
                Default constructor.
            */
            inline Reader();

            /*--------------------------------------------------------------------------------------------------------------------------------------------
                Destructor.
            */
            inline virtual ~Reader() { close(); }

            /*--------------------------------------------------------------------------------------------------------------------------------------------
                Inherited from Spybot::GameData::Interface.
            */
            inline void close();

            /*--------------------------------------------------------------------------------------------------------------------------------------------
                Returns the number of data elements within the currently associated data.

                If the currently associated data is not open at the time of the call to this function, 
                then this function returns 0.

                Returns: The number of data elements.
            */
            inline uint32_t count() const;

            /*--------------------------------------------------------------------------------------------------------------------------------------------
                Searches the associated data file for an element with an ID matching the requested 
                ID argument. If an element with a matching ID is found, the stream pointer is 
                set to that element and the function returns true.

                If no element with a matching ID is found, then the stream's position is restored to 
                the position it was at when the function was called and the function returns false.

                Additionally, this function returns false if the file is not currently open.

                Parameter:
                *   requestedID: ID to search the associated data file for.
                
                Returns: True if an element with a matching ID is located, or false otherwise.
            */
            bool find(const std::string& requestedID);

            /*--------------------------------------------------------------------------------------------------------------------------------------------
                Populates the argument string with the current element's ID, and the appropriate 
                argument data variable's attributes with the current element's attributes, then 
                returns true.

                If the file is not open or not pointing to any data element (such as when the data 
                file is empty) at the time of the call to this function, the function returns false 
                and neither argument variable is modified.

                Parameters:
                *   idDest: Destination for the ID of the current data.
                *   dataDest: Destination for the current data.
                
                Returns: True if the current data was successfully written into the arguments, or false otherwise.
            */
            virtual bool get(std::string& idDest, T& dataDest) = 0;

            /*--------------------------------------------------------------------------------------------------------------------------------------------
                Retrieves the ID of the data element currently pointed to by the stream and stores it 
                in the provided argument string, then returns true. If the stream is either currently 
                closed or not pointing to any data, then the function returns false and the argument 
                string is left unchanged.

                Parameter:
                *   dest: String in which to store the retrieved ID within.
                
                Returns: True if the ID was successfully retrieved, or false otherwise.
            */
            bool getID(std::string& dest);

            /*--------------------------------------------------------------------------------------------------------------------------------------------
                Returns true if the associated data is open and is pointing at a data element.
                If the stream is either closed or has no data element to point at (such as when 
                the associated data file is empty), then this function returns false.

                Returns: True if there is data available to get, or false otherwise.
            */
            inline bool has();

            /*--------------------------------------------------------------------------------------------------------------------------------------------
                Moves the internal stream pointer to the next data element, if it exists, and 
                then returns true. 

                If there are no more data elements are the current one, or the stream is currently closed, 
                then this function returns false and the internal stream pointer is not moved.

                Returns: True if there is another element after the current one, or false otherwise.
            */
            bool next();

            /*--------------------------------------------------------------------------------------------------------------------------------------------
                Inherited from Spybot::GameData::Interface.
            */
            bool open();

        };  //============================================================================================================================================
    }
}

#include <Spybot/GameData/Reader.tpp> // Implementation.

#endif // SPYBOT_GAME_DATA_READER_HPP