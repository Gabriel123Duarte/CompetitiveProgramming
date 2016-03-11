/*
	Trie
	Author: Gabriel Duarte

	Complexity: O(n)

*/

#include <bits/stdc++.h>

using namespace std;


#define ALPHABET_SIZE 26 // Maybe you have to change this value

struct Node
{
	Node* children[ALPHABET_SIZE];
	int prefix; 
	bool isEnd;
};

class Trie
{
	private:
		Node *root;
		int toNum(char c) { return c - 'a'; } // Convert a char to num
		int dfs(Node *node)
		{
			int ans = 1;
			for(int i = 0; i < ALPHABET_SIZE; i++)
				if(node->children[i])
					ans += dfs(node->children[i]);	
			return ans;	
		}
	public:
		Trie()
		{
			root = newNode();
			root->isEnd = false;
		}
		Node *newNode()
		{
			Node *node = new Node();
			node->prefix = 0;
		
			for(int i = 0; i < ALPHABET_SIZE; i++)
				node->children[i] = NULL;
			
			return node;
		}
		void insert(string s)
		{
			Node *aux = root;		
			aux->prefix++;
			for(int i = 0; i < s.size(); i++)
			{
				if(!aux->children[toNum(s[i])])
					aux->children[toNum(s[i])] = newNode();
				aux->children[toNum(s[i])]->prefix++;
				aux = aux->children[toNum(s[i])];
			}
			aux->isEnd = true;
		}
		bool find(string s)
		{
			Node *aux = root;
			for(int i = 0; i < s.size(); i++)
			{
				if(!aux->children[toNum(s[i])])
					return false;
				aux = aux->children[toNum(s[i])];
			}
			return aux->isEnd;
		}
		int wordPrefix(string prefix) // Return total of word with this prefix
		{
			Node *aux = root;
			for(int i = 0; i < prefix.size(); i++)
			{
				if(!aux->children[toNum(prefix[i])])
					return 0;
				aux = aux->children[toNum(prefix[i])];
			}
			return aux->prefix;
		}
		int getPrefix()
		{
			return dfs(root) - 1;
		}
};

int main()
{
	Trie t = Trie();

	t.insert("gabriel");
	t.insert("goat");
	printf("Find %d\n", t.find("goat"));
	printf("Find %d\n", t.find("goats"));
	printf("How many words ? %d\n", t.wordPrefix("g"));
	printf("How many words ? %d\n", t.wordPrefix("ga"));
	printf("Total prefix %d\n", t.getPrefix());
	

	return 0;
}