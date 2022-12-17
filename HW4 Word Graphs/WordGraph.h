#ifndef _WORD_GRAPH_H
#define _WORD_GRAPH_H

#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <stack>

using namespace std;


struct searchElement
{
	string vertex;
	int distance;
	string path;
};


class WordGraph
{
public:
	WordGraph(); //constractor
	void add_edge(string word1, string word2); //create edge between to vertexes, create vertices if they dont exits
	void printShortestPath(string word1, string word2); //print shortest between two words

private:
	unordered_map<string, vector<string>> myGraph;
	void add_vertex(string newWord);
	
};

#endif // !_WORD_GRAPH_H

