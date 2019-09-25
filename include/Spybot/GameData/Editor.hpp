#ifndef SPYBOT_GAME_DATA_EDITOR_HPP
#define SPYBOT_GAME_DATA_EDITOR_HPP

#include <string>

namespace Spybot
{
    namespace GameData
    {
        template <typename T>
        class Editor
        {   //======================================================================================================================================
            protected:
            struct Data
            {
                std::string id;
                T data;
            };

            std::list<Data> elements;
            typename std::list<Data>::iterator elemIter;

            //======================================================================================================================================

            public:
            inline virtual ~Editor() {}

            /*--------------------------------------------------------------------------------------------------------------------------------------
                Copies the provided ID and data arguments into loaded memory, creating 
                a new data element, adding it to the end of the data elements currently 
                loaded into this object.

                This object's internal data pointer will point to the new data element after addition.

                Parameters:
                *   srcID: ID of the new data element.
                *   srcData: Attribute data of the new data element.
            */
            void add(const std::string& srcID, const T& srcData);

            /*--------------------------------------------------------------------------------------------------------------------------------------
                Returns the number of elements currently loaded into this object.

                Returns: The number of currently loaded elements.
            */
            inline int count() const;

            /*--------------------------------------------------------------------------------------------------------------------------------------
                Queries all loaded data elements for an element with an ID matching the provided argument ID.

                If an element with a matching ID is found, this object will begin pointing to that element, 
                and the function returns true. If no matching ID can be found, then this object will return 
                to pointing to the data element that was pointed to at the start of this function, and then 
                the function returns false.

                Parameter:
                *   ID: ID to query loaded data elements for.
                
                Returns: True if a data element with the provided ID is located, or false otherwise.
            */
            bool find(const std::string& ID);

            /*--------------------------------------------------------------------------------------------------------------------------------------
                If this object is currently pointing to a data element, the argument ID and data pointers 
                will be redirected to point at the data element that this object is pointing to, allowing 
                for modification. Then function will then return true.

                If this object is not currently poining to any data elements, then the function returns 
                false and the arguments are left unmodified.

                Parameters:
                *   destID: Pointer to an ID string.
                *   destData: Pointer to data.
                
                Returns: True if the argument pointers are redirected to loaded data, or false otherwise.
            */
            bool get(std::string** destID, T** destData);

            /*--------------------------------------------------------------------------------------------------------------------------------------
                Populates the argument with constant references to the ID of every currently loaded program.

                Parameter:
                *   destList: The storage destination of ID references.
            */
            void getIDList(std::list<std::string>& destList);

            /*--------------------------------------------------------------------------------------------------------------------------------------
                Loads the associated data type in memory, and returns true.

                If the file containing the associated data type fails to open, then 
                this function does nothing and returns false.

                Returns: True if the associated data is successfully loaded, or false otherwise.
            */
            virtual bool load() = 0;

            /*--------------------------------------------------------------------------------------------------------------------------------------
                Advances this object's element pointer forward one element.

                If this object's internal pointer is pointing to the last data element at the time 
                of the call to this function, it will wrap around to the first data element.
            */
            void next();

            /*--------------------------------------------------------------------------------------------------------------------------------------
                Retracts this object's element pointer back one element.

                If this object's internal pointer is pointing to the first data element at the time 
                of the call to this function, it will wrap around to the last data element.
            */
            void prev();

            /*--------------------------------------------------------------------------------------------------------------------------------------
                Deletes the data element that this object is currently pointing at (if any), then return true. 
                This item will no longer exist to be resaved to the data files from which it was loaded.

                After deletion, this object's internal pointer will point to the data element after the deleted 
                data element. If the deleted data element was previously the last data element
                then this object's pointer will move to the first data element.

                If no data elements are loaded at the time of the call to this function, 
                then it will do nothing and return false.

                Returns: True if a data element was removed, or false otherwise.
            */
            bool remove();

            /*--------------------------------------------------------------------------------------------------------------------------------------
                Overwrites the file of the associated data with the data currently loaded into 
                the this object, then returns true.

                If the function fails to open data associated data for writing for any reason, 
                the function does nothing and returns false.

                Calling this function with no data loaded will cause the associated data file 
                to be completely erased.
            */
            virtual void save() = 0;

            /*--------------------------------------------------------------------------------------------------------------------------------------
                Clears all currently loaded data elements from memory.
            */
            inline void unload();

        };  //======================================================================================================================================

    } // namespace GameData

} // namespace Spybot

#include <Spybot/GameData/Editor.tpp> // Template implementation

#endif // SPYBOT_GAME_DATA_EDITOR_HPP