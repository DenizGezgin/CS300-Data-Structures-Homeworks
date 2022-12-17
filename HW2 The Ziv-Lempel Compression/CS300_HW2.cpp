#include <iostream>
#include "CodedString.h"
#include "HashTable.h";
#include <fstream>
#include <sstream>

//REHASH-  HASH_FUNCTION-  SIZE

using namespace std;

const CodedString ITEM_NOT_FOUND; //defalt item to printed if find fails

//Initilze dict with 256 ascii charahcters 
void initializeDict(HashTable<CodedString> &myTable)
{
    
    for (int i = 0; i < 256; i++)
    {
        string s(1, (unsigned char)i);  //create a string of given char 
        CodedString temp(i,s); //create a dict. element with asci code and string version of char
        myTable.insert(temp); //add to table
    }
}




int main()
{
    HashTable<CodedString> hashTable(ITEM_NOT_FOUND, 8209); //create hash table

    initializeDict(hashTable); //put single char ascii items to table

    CodedString FIND(-1, "A"), temp; //coded string that will be used on find calls
    temp = hashTable.find(FIND);
    string line;

    ifstream compin; //file to get input to be compressed
    compin.open("compin.txt");
    ofstream compout; //file to put output intagers
    compout.open("compout.txt");


    int code = 255; //first code will be 256
    char ch;
    string fileContents = "";
    while (!compin.eof()) //reads char bt char into file contents string
    {
        compin.get(ch);
        fileContents += ch;
    }
    fileContents.pop_back(); //remove repated item in the end

    bool matched = false;
    string searchedPrefix;
    int maxSize = 1; //max possible size to search the string prefixes
    while (!(fileContents.size() == 0)) //when there are still items to encode
    {
        matched = false;
        if (maxSize > fileContents.size()) //if max size overflows fix to string size
            maxSize = fileContents.size();

        for (int i = maxSize; !matched; i--) //check first maxsize elements 
        {
            searchedPrefix = fileContents.substr(0, i); //get prefix of sepecifed size
            FIND.setString(searchedPrefix);
            temp = hashTable.find(FIND); //search for find
            if (temp != ITEM_NOT_FOUND) //if found
            {
                matched = true;
                compout << temp.getCode() << " ";
                //remove the encoded part from file
                fileContents = fileContents.substr(searchedPrefix.length()); //remove the found string from start
                //if string is not empty append next char to found string AND we havent made max insertions
                if (fileContents.size() != 0 && hashTable.getSize() < 4095)
                {
                    searchedPrefix += fileContents[0];
                    code++; //incremnt code for next instertion
                    CodedString newDict(code, searchedPrefix);
                    hashTable.insert(newDict);
                    if (searchedPrefix.size() > maxSize)
                        maxSize = searchedPrefix.size();
                }
            }
        }
    }
   
    compin.close();
    compout.close();
}