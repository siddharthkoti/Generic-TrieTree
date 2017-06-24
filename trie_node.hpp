#ifndef TRIE_NODE_HPP
#define TRIE_NODE_HPP

#include <map>
#include <string>

template <typename V>
class TrieNode
{
	
	public:
		TrieNode<V> *_parent;
		std::map<char, TrieNode<V>* > _children; 
		bool _isWord;
		std::string _key;
		V _value;


		TrieNode():
		_parent(NULL), _children(), _isWord(false), _key(), _value()
		{
			
		}

		TrieNode(TrieNode<V> *parent, bool isLeaf, std::string key, V value):
		_children(),_isWord(isLeaf), _key(key), _value(value)
		{
			_parent = parent;
		}

		TrieNode(TrieNode<V> &other)
		:_parent(other._parent), _children(other._children), _isWord(other._isWord), _key(other._key), _value(other._value)
		{

		}

		~TrieNode()
		{
			for(auto it=_children.begin(); it!=_children.end(); ++it)
				delete it->second;
		}
	
		TrieNode<V>& operator=(const TrieNode<V>& rhs)
		{
			this->_parent = rhs._parent;
			this->_children = rhs._children;
			this->_isWord = rhs._isWord;
			this->_key = rhs._key;
			this->_value = rhs._value;

			return *this;
		}
};
#endif
