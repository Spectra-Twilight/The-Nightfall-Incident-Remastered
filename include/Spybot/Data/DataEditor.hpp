#ifndef SPYBOT_DATA_EDITOR_HPP
#define SPYBOT_DATA_EDITOR_HPP

#include <list>
#include <string>

namespace Spybot
{
    template <typename T>
    class DataEditor
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

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Copies the provided ID and data arguments into loaded memory, creating 
            a new data element, adding it to the end of the data elements currently 
            loaded into the data editor.

            The DataEditor will point to the new data element after addition.

            Parameters:
            *   srcID: ID of the new data element.
            *   srcData: Attribute data of the new data element.
        */
        void add(const std::string& srcID, const T& srcData)
        {
            elements.push_back(Data());
            elements.back().id = srcID;
            elements.back().data = srcData;
            elemIter = elements.end();
            elemIter--;
        }

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Returns the number of elements currently loaded into the DataEditor.

            Returns: The number of currently loaded elements.
        */
        inline int count() const { return elements.size(); }

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Queries all loaded data elements for an element with an ID matching the provided argument ID.

            If an element with a matching ID is found, the DataEditor will begin pointing to that element, 
            and the function returns true. If no matching ID can be found, then DataEditor will return 
            to pointing to the data element that was pointed to at the start of this function, and then 
            the function returns false.

            Parameter:
            *   ID: ID to query loaded data elements for.
            
            Returns: True if a data element with the provided ID is located, or false otherwise.
        */
        bool find(const std::string& ID)
        {
            typename std::list<Data>::iterator original = elemIter;
            
            for (elemIter = elements.begin(); elemIter != elements.end(); elemIter++)
            {
                if (elemIter->id == ID)
                    return true;
            }

            elemIter = original;
            return false;
        }

        /*--------------------------------------------------------------------------------------------------------------------------------------
            If the DataEditor is currently pointing to a data element, the argument ID and data pointers 
            will be redirected to point at the data element that the DataEditor is pointing to, allowing 
            for modification. Then function will then return true.

            If the DataEditor is not currently poining to any data elements, then the function returns 
            false and the arguments are left unmodified.

            Parameters:
            *   destID: Pointer to an ID string.
            *   destData: Pointer to data.
            
            Returns: True if the argument pointers are redirected to loaded data, or false otherwise.
        */
        bool get(std::string** destID, T** destData)
        {
            if (elements.size() == 0)
                return false;
            
            *destID = &(elemIter->id);
            *destData = &(elemIter->data);
            return true;
        }

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Populates the argument with constant references to the ID of every currently loaded program.

            Parameter:
            *   destList: The storage destination of ID references.
        */
        void getIDList(std::list<std::string>& destList)
        {
            destList.clear();
            typename std::list<Data>::const_iterator tempIter;
            for (tempIter = elements.begin(); tempIter != elements.end(); tempIter++)
                destList.push_back(tempIter->id);
        }

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Loads the associated data type in memory, and returns true.

            If the file containing the associated data type fails to open, then 
            this function does nothing and returns false.

            Returns: True if the associated data is successfully loaded, or false otherwise.
        */
        virtual bool load() = 0;

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Advances the DataEditor's element pointer forward one element.

            If the DataEditor is pointing to the last data element at the time 
            of the call to this function, it will wrap around to the first data element.
        */
        void next()
        {
            elemIter++;

            if (elemIter == elements.end())
                elemIter = elements.begin();
        }

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Retracts the DataEditor's element pointer back one element.

            If the DataEditor is pointing to the first data element at the time 
            of the call to this function, it will wrap around to the last data element.
        */
        void prev()
        {
            if (elemIter == elements.begin())
                elemIter = elements.end();

            elemIter--;
        }

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Deletes the data element that the DataEditor is currently pointing at (if any), then return true. 
            This item will no longer exist to be resaved to the data files from which it was loaded.

            After deletion, the DataEditor will point to the data element after the deleted 
            data element. If the deleted data element was previously the last data element
            then the DataEditor's pointer will move to the first data element.

            If no data elements are loaded at the time of the call to this function, 
            then it will do nothing and return false.

            Returns: True if a data element was removed, or false otherwise.
        */
        bool remove()
        {
            if (elements.size() == 0)
                return false;
            
            elemIter = elements.erase(elemIter);
            if (elemIter == elements.end())
                elemIter = elements.begin();

            return true;
        }

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Overwrites the file of the associated data with the data currently loaded into 
            the DataEditor, then returns true.

            If the function fails to open data associated data for writing for any reason, 
            the function does nothing and returns false.

            Calling this function with no data loaded will cause the associated data file 
            to be completely erased.
        */
        virtual bool save() = 0;

        /*--------------------------------------------------------------------------------------------------------------------------------------
            Clears all currently loaded data elements from memory.
        */
        inline void unload() { elements.clear(); }

    };  //======================================================================================================================================
}

#endif // SPYBOT_DATA_EDITOR_HPP