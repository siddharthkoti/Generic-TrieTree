#include <iostream>
#include <algorithm>
#include "trie_tree.hpp"
using namespace std;

int main()
{
	TrieTree<int> t;
	t.insert("zebra",5);
	t.insert("boomerang",6);
	t.insert("apple",1);
	t.insert("sample",8);

	TrieTree<string> t1;
	t1.insert("dameit","zebra");
	t1.insert("batman","comeon");

	cout<<t1["batman"]<<"\n";
	t1["batman"] = "gotit";
	cout<<t1["batman"]<<"\n";
	t1["dhoni"] = "msd";
	cout<<t1["dhoni"]<<"\n";
	
	return 0;
}
