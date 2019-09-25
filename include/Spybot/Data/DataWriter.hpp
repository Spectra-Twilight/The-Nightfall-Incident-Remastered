#ifndef SPYBOT_DATA_WRITER_HPP
#define SPYBOT_DATA_WRITER_HPP

#include <fstream>

#include <Spybot/Data/DataInterface.hpp>

namespace Spybot
{
    template <typename T>
    class DataWriter: public virtual Spybot::DataInterface
    {   //====================================================================================================================================
        protected:

        std::ofstream file;

        //====================================================================================================================================
        public:

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Closes the stream that the DataWriter is writing to.

            Inherited from DataInterface.
        */
        inline void close() { file.close(); }

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Opens the stream associated with this DataWriter, and returns true.
            If the stream fails to open for any reason, then this function returns false.

            WARNING: Note that all data stored in the file associated with this DataWriter 
            at the time of the call to this function will be lost upon opening the stream.
            If you wish to update or append to the associated data, load it into memory first 
            using a DataReader, make the desired changes, and then use a DataWriter to overwrite 
            the original file.

            Inherited from DataInterface.

            Returns: True if the stream is opened, or false otherwise.
        */
        inline bool open() { file.open(filepath, std::ios_base::binary); return file.is_open(); }

        /*------------------------------------------------------------------------------------------------------------------------------------
            Writes srcData to the stream under the ID provided by srcID, then returns true.

            If the stream is not currently open at the time of the call to this function, then 
            this function returns false and does nothing else.

            Parameters:
            *   srcID: The ID under which to identify the data being stored.
            *   srcData: The data to store.
            
            Returns: True if the data was written to the stream, or false otherwise.
        */
        virtual bool put(const std::string& srcID, const T& srcData) = 0;

    };  //====================================================================================================================================
}

#endif // SPYBOT_DATA_WRITER_HPP