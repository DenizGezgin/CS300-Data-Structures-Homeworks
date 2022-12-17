// Deniz Can Gezgin 27792 created 17.12.2021 
//

#include <iostream>
#include "WordGraph.h"
#include <fstream>
#include <sstream>

using namespace std;

//Check if word2 is reachable by single insertions/deletions/substitutions
bool isDirectlyConnected(string word1, string word2)
{
    if (word1.size() == word2.size()) //check one letter substitutions
    {
        int mistakes = 0;
        for (int i = 0; i < word1.size(); i++)
        {
            if (word1.at(i) != word2.at(i)) //when char mismatch increment mistake by one
                mistakes++;

            if (mistakes > 1) //if more then one mistake no one letter substitutions
                return false;
        }
        return true;
    }
    else if (word1.size() + 1 == word2.size()) //check for deletions
    {
        int mistakes = 0;
        for (int i = 0; i < word1.size(); i++)
        {
            if (mistakes == 0) //try to find first deletation place
            {
                if (word1.at(i) != word2.at(i))
                {
                    mistakes++;
                    i--;
                }
            }         
            else if (mistakes == 1) //after first mistake is found check the second word with on ofset to balance
            {
                if (word1.at(i) != word2.at(i + 1))
                {
                    return false;
                }
            }     
        }
        return true;
    }
    else if (word1.size() - 1 == word2.size()) //check for insertions logilacy like delete with word1 andd word2 interchanged
    {
        int mistakes = 0;
        for (int i = 0; i < word2.size(); i++)
        {
            if (mistakes == 0)
            {
                if (word2.at(i) != word1.at(i))
                {
                    mistakes++;
                    i--;
                }
            }
            else if (mistakes == 1)
            {
                if (word2.at(i) != word1.at(i + 1))
                {
                    return false;
                }
            }       
        }
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    WordGraph graph;


    ifstream words; 
    words.open("words.txt");
    string currentWord;
    unordered_map<string, string> allWordsMap;
    vector<string> allWords;
    //put words from file to a vector
    while (getline(words, currentWord))
    {
        if (allWordsMap.find(currentWord) == allWordsMap.end()) //add to map if not a repeat so we can assume no repates
        {
            allWordsMap[currentWord] = currentWord;
            allWords.push_back(currentWord);
        }
    }

    for (int i = 0; i < allWords.size(); i++)
    {
        currentWord = allWords[i];
        //Compare each word with all the words after it to find direct connections
        for (int j = i + 1; j < allWords.size(); j++)
        {
            if (isDirectlyConnected(currentWord, allWords[j]))
            {
                graph.add_edge(currentWord, allWords[j]); //add to graph
            }
        }
    }

    string word1, word2;
    while (true)
    {
        cin >> word1 >> word2;
        if (word1.at(0) == '*')
            break;
        //check if both words are int the given text
        if (allWordsMap.find(word1) == allWordsMap.end() || allWordsMap.find(word2) == allWordsMap.end())
        {
            cout << "One of the words is not in the list" << endl;
        }
        else
        {
            graph.printShortestPath(word1, word2);
        }

    }

}
