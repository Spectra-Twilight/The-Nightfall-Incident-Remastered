#include "trie.hpp"
#include "trie_node.hpp"

//===================================================================================================================================================

template <typename T>
void trie<T>::findNodeAdd(const std::string& keyword, trie_node** current)
{
    if (keyword.length() > 0)
    {
        if (!root->hasChild())
            root->setChild(new trie_node(keyword[0]));
        *current = root->getChild().get();
    }
    else
        *current = nullptr;

    for (int c = 0; keyword[c]; c++)
    {
        while ((*current)->getKey() != keyword[c] && (*current)->getNext() != nullptr)
            (*current) = (*current)->getNext().get();

        if ((*current)->getKey() == keyword[c]) // Character found.
        {
            if (keyword[c + 1]) // Not end of keyword
            {
                if (!(*current)->hasChild()) // End of path.
                    (*current)->setChild(new trie_node(keyword[c + 1]));

                (*current) = (*current)->getChild().get();
            }
        }
        else // Character does not exist in this level of the trie.
        {
            // Add current character to the trie.
            (*current)->setNext(new trie_node(keyword[c]));
            if (keyword[c + 1]) // Not end of keyword
            {
                // Add the next character to the trie.
                (*current)->getNext()->setChild(new trie_node(keyword[c + 1]));
                (*current) = (*current)->getNext()->getChild().get();
            }
            else // End of keyword
                (*current) = (*current)->getNext().get();
        }
    }
}

//===================================================================================================================================================

template <typename T>
bool trie<T>::findNodeGet(const std::string& keyword, trie_node** current) const
{
    if (!root->hasChild() || keyword.length() == 0)
        return false;

    *current = root->getChild().get();

    for (int c = 0; keyword[c]; c++)
    {
        while ((*current)->getKey() != keyword[c] && (*current)->hasNext())
            (*current) = (*current)->getNext().get();

        if ((*current)->getKey() == keyword[c]) // Character found.
        {
            if (keyword[c + 1]) // Not end of keyword
            {
                if ((*current)->hasChild())
                    (*current) = (*current)->getChild().get();
                else // Keyword is not in the trie.
                    return false;
            }
        }
        else // Keyword is not in the trie.
            return false;
    }

    return (*current)->hasData();
}

//===================================================================================================================================================

template <typename T>
bool trie<T>::findNodeRemove(const std::string& keyword, trie_node** current, trie_node** parentOfRemoval, trie_node** beforeRemoval) const
{
    if (!root->hasChild() || keyword.length() == 0)
        return false;

    *current = root->getChild().get();
    *parentOfRemoval = root.get();
    trie_node* parent = *parentOfRemoval; // Parent of the current node.

    for (int c = 0; keyword[c]; c++)
    {
        if (*parentOfRemoval == parent)
            *beforeRemoval = nullptr; // Prepare to find the node before the first node to remove.

        while ((*current)->getKey() != keyword[c] && (*current)->hasNext())
        {
            if (*parentOfRemoval == parent && (*current)->getNext()->getKey() == keyword[c])
                *beforeRemoval = (*current);

            *current = (*current)->getNext().get();
        }

        if ((*current)->getKey() == keyword[c]) // Character found.
        {
            /*  A node should not be removed if:
                1.  It has data and is NOT the node being removed (keyword goes on), or
                2.  It has more than 1 child.
            */
            if (((*current)->hasData() && keyword[c + 1]) || ((*current)->hasChild() && (*current)->getChild()->hasNext()))
                *parentOfRemoval = *current;

            parent = *current;

            if (keyword[c + 1]) // Not end of keyword
            {
                if ((*current)->hasChild())
                    *current = (*current)->getChild().get();
                else // Keyword is not in the trie.
                    return false;
            }
        }
        else // Keyword is not in the trie.
            return false;
    }

    return (*current)->hasData();
} // End of findNodeRemove()

//===================================================================================================================================================

template <typename T>
trie<T>::trie()
{
    root.reset(new trie_node);
}

//===================================================================================================================================================

template <typename T>
bool trie<T>::add(const std::string& keyword, T& value, bool discard)
{
    if (keyword.length() == 0)
        return false;

    trie_node* current;
    findNodeAdd(keyword, &current);

    // Only replace existing data if explicitly told to do so.
    if (current && (!current->hasData() || discard))
    {
        current->setData(value);
        return true;
    }
    else
        return false;
}

//===================================================================================================================================================

template <typename T>
bool trie<T>::get(const std::string& keyword, T* value) const
{
    trie_node* current;
    if (findNodeGet(keyword, &current))
    {
        if (value != nullptr)
            *value = current->getData();

        return true;
    }
    else // No data under that keyword.
        return false;
}

//===================================================================================================================================================

template <typename T>
bool trie<T>::remove(const std::string& keyword, T* value)
{
    trie_node* current;
    trie_node* parentR;// Parent of the first node to be removed.
    trie_node* prevR; // The node prior of the first node to be removed.

    if (findNodeRemove(keyword, &current, &parentR, &prevR))
    {
        // Save a copy of the data (if possible) then remove it from the tree.
        if (value != nullptr)
            *value = current->getData();

        current->clearData();

        // Delete any non-vital nodes.
        if (!current->hasChild())
        {
            if (prevR)
                prevR->setNext(prevR->getNext()->getNext().release());
            else // current is first child of parentR
                parentR->setChild(parentR->getChild()->getNext().release());
        }

        return true;
    }
    else // No data under that keyword.
        return false;
} // End of remove()