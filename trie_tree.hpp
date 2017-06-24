#ifndef TRIE_TREE_H 
#define TRIE_TREE_H

#include <string>
#include <iterator>
#include <map>
#include <iostream>
#include "trie_node.hpp"
#include <vector>

template<typename V>
class TrieTree{
private:
	TrieNode<V> *_root;
	size_t _size;
	
public:
	

	TrieTree(): _size(0)
	{
		_root = new TrieNode<V>();

		_root->_children['~'] = new TrieNode<V>(_root,true,"~",V());

	}

	~TrieTree()
	{
		delete _root;
	}


	class Iterator : public std::iterator<std::input_iterator_tag, TrieNode<V>>
	{
		public:
			TrieNode<V> *p_it;
			TrieNode<V> *parent;
			
		public:
			explicit Iterator(TrieNode<V> *p = 0,TrieNode<V> *parent_ = 0) 
			:p_it(p), parent(parent_)
			{
			}
			
			bool operator==(const Iterator& rhs) const
			{
				return p_it == rhs.p_it && parent == rhs.parent;
			}

			bool operator!=(const Iterator& rhs) const
			{
				return !(*this==rhs);
			}


			const std::string operator*()
			{
					if( ((*this).p_it) -> _key != "~")
						return p_it->_key;
					return nullptr;

			}

			
			Iterator operator++(int) //post
			{
				Iterator temp(*this);
				++*this;
				return temp;
			}

			const Iterator& operator++()//pre
			{
				if(!p_it->_children.empty())
				{
					parent = p_it;
					p_it = ((p_it->_children).begin())->second;
					return *this;
				}
				else{
				
					char c = (p_it->_key).back();
					auto itr = (parent->_children).find(c);
					++itr;
					if(itr != (parent->_children).end())
					{	
						p_it = itr->second;
						parent = p_it->_parent;
						return *this;
					}
					else
					{
						
						do {
							p_it = parent;
							parent = p_it->_parent;
							char c = (p_it->_key).back();
							
							itr = (parent->_children).find(c);
							++itr;
						}while( itr == parent->_children.end());

						if((itr)->first =='~'){
							Iterator(parent->_children['~'],parent);
						}
						p_it = itr->second;
						parent = p_it->_parent;
						return *this;
					}
				}
			}
	};

	

	void insert(std::string key, const V &value);
	V& operator[](std::string target);
	bool remove(std::string key);
	Iterator search(std::string key);
	void traverse(void);
	std::vector<std::string> keys();
	
	Iterator begin()
	{
		return Iterator((_root->_children).begin()->second,_root);
	}
	
	Iterator end()
	{
		 return Iterator(_root->_children['~'],_root);
	}

	size_t size(){
		return _size;
	}
};


std::string trim(std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}



template<typename V>
void TrieTree<V>::insert(std::string key,const V &value)
{	
	key=trim(key);
	int n = key.length();
	++_size;
	TrieNode<V> *curr(_root);
	for(int i=0; i<n; i++)
	{
		
		if((curr->_children).find(key[i]) != (curr->_children).end())
		{
			curr = curr->_children[key[i]];
			if(i == n-1){
				curr->_isWord = true;
				curr->_value = value;
			}
		}
		else
		{
			if(i == n-1){
				curr->_children[key[i]] = new TrieNode<V>(curr,true,key.substr(0,i+1), value);
				curr = curr->_children[key[i]];
			}
			else{
				curr->_children[key[i]] = new TrieNode<V>(curr,false,key.substr(0,i+1),V());
				curr = curr->_children[key[i]];
			}
		}
	}


}

template<typename V>
typename TrieTree<V>::Iterator TrieTree<V>::search(std::string key)
{
	TrieNode<V> *curr(_root);
	for(int i=0; i<key.length(); ++i)
	{
		if((curr->_children).find(key[i]) != (curr->_children).end())
			curr = curr->_children[key[i]];
		else
		{
			return (*this).end();
		}
	}
	if(curr->_isWord)
		return Iterator(curr,curr->_parent);
	else
		return (*this).end();
}


template<typename V>
void TrieTree<V>::traverse()
{
	typename TrieTree<V>::Iterator f = (*this).begin();
	typename TrieTree<V>::Iterator l = (*this).end();
	while( f != l )
	{
		std::cout<<*f++<<"\n";
	}
}

template<typename V>
V& TrieTree<V>::operator[](std::string target){
				auto it=find( this->begin(),this->end(),target);
				if(it != this->end())
				{
					return (it.p_it)->_value;
				}
				else{
					this->insert(target,V());
					return (find( this->begin(),this->end(),target).p_it)->_value;
				}
}


template<typename V>
std::vector<std::string> TrieTree<V>::keys(){
	std::vector<std::string> v;
	typename TrieTree<V>::Iterator f = (*this).begin();
	typename TrieTree<V>::Iterator l = (*this).end();
	while( f != l )
	{
		if((f.p_it)->_isWord){
			
			v.push_back((f.p_it)->_key);
		}
		++f;
	}							
	return v;
}


template<typename V>
bool TrieTree<V>::remove(std::string key)
{
	auto it = find((*this).begin(),(*this).end(),key);
	if(it != (*this).end() && (it.p_it)->_isWord)
	{
		if(it.p_it->_children.size() > 0)
		{
			std::cout << key <<"\n";
			it.p_it->_isWord = false;
			it.p_it->_value  = -1;				
		}
		else if ( (it.p_it)->_children.size() == 0)
		 {	std::cout << key <<"\n";
			int n  = key.length();
			int i= n - 1;
			while( i > 0 && (it.parent)->_children.size() <= 1){

				auto itr=(it.parent)->_children.find( key[i] ); 
				(it.parent)->_children.erase(itr);
				it.p_it = it.parent;
				(it.parent )= (it.p_it)->_parent;
				
				i--;
			}
			auto itr=(it.parent)->_children.find( key[i] ); 
			(it.parent)->_children.erase(itr);//itr
		}
		return true;
	}
	return false;
}
#endif