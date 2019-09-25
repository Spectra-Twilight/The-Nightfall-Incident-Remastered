#ifndef SPYBOT_DATA_READER_HPP
#define SPYBOT_DATA_READER_HPP

#include <fstream>
#include <string>

#include <Spybot/Data/DataInterface.hpp>

namespace Spybot
{
    template <typename T>
    class DataReader: public virtual Spybot::DataInterface
    {   //============================================================================================================================================
        protected:

        std::ifstream file;

        //============================================================================================================================================
        public:

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Closes the stream that the DataReader is reading from.

            Inherited from DataInterface.
        */
        inline void close() { file.close(); }

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Returns the total number of data elements within the currently associated data.

            The file stream's pointer position is modified by this function, but returned 
            to the position at which is was at the start of the function before the function 
            returns.

            If the file is not open at the time of the call to this function, then the 
            function returns a value of 0.

            Returns: The total number of data elements.
        */
        unsigned int count()
        {
            if (!file.is_open())
                return 0;

            std::streampos original = file.tellg();
            file.seekg(0, std::ios_base::beg);

            unsigned int numElements = 0;

            if (file.peek() != EOF)
            {
                numElements++;

                while (next())
                    numElements++;
            }

            file.seekg(original, std::ios_base::beg);
            return numElements;
        }

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Searches the associated data file for an element with an ID matching the requested 
            ID argument. If an element with a matching ID is found, the stream pointer is 
            set to that element and the function returns true.

            If no element with a matching ID is found, then the stream's position is restored to 
            the way it was at the start of the function and the function returns false.

            Additionally, this function returns false if the file is not currently open.

            Parameter:
            *   requestedID: ID to search the associated data file for.
            
            Returns: True if an element with a matching ID is located, or false otherwise.
        */
        bool find(const std::string& requestedID)
        {
            if (!file.is_open())
                return false;

            std::streampos original = file.tellg();
            file.seekg(0, std::ios_base::beg);

            if (file.peek() != EOF)
            {
                std::string temp;
                do
                {
                    getID(temp);
                    if (requestedID == temp)
                        return true;
                } 
                while (next());
            }

            file.seekg(original, std::ios_base::beg);
            return false;
        }

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
        bool getID(std::string& dest)
        {
            if (!file.is_open() || file.peek() == EOF)
                return false;

            file.seekg(DataElementSizeBytes, std::ios_base::cur); // Skip over data element size counter.

            // Acquire size of ID (in chars).
            uint8_t IDCharCount;
            file.read((char*)(&IDCharCount), IDCharCountBytes);

            // Save ID in file to ID variable.
            char temp[256];
            file.read(temp, IDCharCount);
            temp[IDCharCount] = '\0';
            dest = temp;

            file.seekg(-(DataElementSizeBytes + IDCharCountBytes + IDCharCount), std::ios_base::cur); // Return to original position.
            return true;
        }

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Returns true if the data stream is open and is pointing at a data element.
            If the stream is either closed or has no data element to point at (such as when 
            the associated data file is empty), then this function returns false.

            Returns: True if there is data available to get, or false otherwise.
        */
        inline bool has() { return (file.is_open() && file.peek() != EOF); }

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Moves the internal stream pointer to the next data element, if it exists, and 
            then returns true. 

            If there are no more data elements are the current one, or the stream is currently closed, 
            then this function returns false and the internal stream pointer is not moved.

            Returns: True if there is another element after the current one, or false otherwise.
        */
        bool next()
        {
            if (!file.is_open() || file.peek() == EOF)
                return false;

            uint16_t dataElementSize;
            file.read((char*)(&dataElementSize), DataElementSizeBytes);
            file.seekg(dataElementSize - DataElementSizeBytes, std::ios_base::cur);

            if (file.peek() == EOF)
            {
                file.seekg(-dataElementSize, std::ios_base::cur); // Return to starting position.
                return false;
            }
            else
                return true;
        }

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Opens the stream associated with this DataReader, and returns true.
            If the stream fails to open for any reason, then this function returns false.

            Inherited from DataInterface.

            Returns: True if the stream is opened, or false otherwise.
        */
        inline bool open() { file.open(filepath, std::ios_base::binary); return file.is_open(); }

    };  //============================================================================================================================================
}

#endif // SPYBOT_DATA_READER_HPP