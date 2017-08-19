# Generic-TrieTree
Generic Trie-Tree to work as key-value pair where the value is any generic object.

A Trie is an ordered tree data structure that is used to store a dynamic set or associative array where the keys are usually strings.
Tries are an extremely special and useful data-structure that are based on the prefix of a string. They are used to represent the 
“Retrieval” of data and thus the name Trie. Unlike a binary search tree, no node in the tree stores the key associated with that node, 
instead, its position in the tree defines the key with which it is associated. All the descendants of a node have a common prefix of the 
string associated with that node, and the root is associated with the empty string. Values are not necessarily associated with every node. 
Rather, values tend only to be associated with leaves, and with some inner nodes that correspond to keys of interest.

Key features:

  * The Trie Tree is implemented in C++, concntrating highly on use of templates.
  
  * The Trie tree can hold any Generic object as a value and can be accessed by the its key which is a string.
  
  * Basic functions like insert, search, remove, traverse, keys are implemented.
  
  * Operator '[]' is overloaded to insert a key-value pair to the trie-tree if it does not exist and also retrive value for the given key.
  
  * An Iterator is implemeted that extends std::input_iterator_tag so as to work with few STL algorithms like find, find_if, for_each,
  count, count_if, copy, copy_if, lexicographical_compare, begin(), end().
