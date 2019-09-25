#ifndef TRIE_HPP
#define TRIE_HPP

#include <memory>
#include <string>

template <typename T>
class trie
{
  private:
    class trie_node; // Defintion in trie_node.hpp

    std::unique_ptr<trie_node> root;

    void findNodeAdd(const std::string& keyword, trie_node** current);
    bool findNodeGet(const std::string& keyword, trie_node** current) const;
    bool findNodeRemove(const std::string& keyword, trie_node** current, trie_node** parentOfRemoval, trie_node** beforeRemoval) const;

  public:
    trie();

    bool add(const std::string& keyword, T& value, bool discard = false);
    bool get(const std::string& keyword, T* value = nullptr) const;
    bool remove(const std::string& keyword, T* value = nullptr);
};

#include "trie.tpp"

#endif // TRIE_HPP
