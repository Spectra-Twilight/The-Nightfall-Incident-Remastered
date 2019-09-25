#ifndef TRIE_NODE_HPP
#define TRIE_NODE_HPP

#include "trie.hpp"

template <typename T>
class trie<T>::trie_node
{
    private:
    char key;
    T data;
    bool valid;
    std::unique_ptr<trie_node> next;
    std::unique_ptr<trie_node> child;

    public:
    /*==================
    |   Constructors   |
    ==================*/
    inline trie_node(char initKey = '\0'): key(initKey), valid(false) {}

    /*====================
    |   Getter Methods   |
    ====================*/
    inline char getKey() const { return key; }
    inline T getData() { return data; }
    inline bool hasData() const { return valid; }
    inline bool hasNext() const { return next != nullptr; }
    inline std::unique_ptr<trie_node>& getNext() { return next; }
    inline bool hasChild() const { return child != nullptr; }
    inline std::unique_ptr<trie_node>& getChild() { return child; }

    /*====================
    |   Setter Methods   |
    ====================*/
    inline void setKey(char newKey) { key = newKey; }
    inline void setData(T newData) { data = newData; valid = true; }
    inline void clearData() { valid = false; }
    inline void setNext(trie_node* newNext) { next.reset(newNext); }
    inline void setChild(trie_node* newChild) { child.reset(newChild); }
};

#endif // TRIE_NODE_HPP
