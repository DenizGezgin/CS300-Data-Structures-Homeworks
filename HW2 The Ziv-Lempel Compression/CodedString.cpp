#include "CodedString.h"

CodedString::CodedString(const int e, std::string element)
        :code(e), element(element) {}

std::string CodedString::getString() const
{
    return element;
}

int CodedString::getCode() const
{
    return code;
}

void CodedString::setString(std::string newStr)
{
    element = newStr;
}

bool CodedString::operator==(const CodedString& rhs) const
{
    return (element == rhs.element);
}

bool CodedString::operator!=(const CodedString& rhs) const
{
    return !(element == rhs.element);
}