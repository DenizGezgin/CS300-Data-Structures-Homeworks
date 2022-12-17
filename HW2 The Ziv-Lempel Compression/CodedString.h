//Deniz Can Gezgin made on 13.11.2021
//Basic class to store string and a code associted with that string
//Overloads the == and != operators to use with hash table class
#ifndef _CODED_STRING
#define _CODED_STRING

#include <string>

class CodedString
{
public:
    CodedString(const int e = -1, std::string element = "ITEM_NOT_FOUND");

    std::string getString() const; //returns string
    int getCode() const; //returns code of codded string
    void setString(std::string newStr); //changes the string
    

    bool operator==(const CodedString& rhs) const; 
    bool operator!=(const CodedString& rhs) const;
private:  
    int code;
    std::string element;

};
#endif // !_CODED_STRING


