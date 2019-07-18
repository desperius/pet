#include "petModel.h"

#include <regex>
#include <windows.h>
#include <QDebug>

namespace pet
{

std::string trim(const std::string& str, const std::string& whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    
    if (std::string::npos == strBegin)
    {
        return std::string();
    }
    
    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;
    
    return str.substr(strBegin, strRange);
}

petModel::petModel()
{
    // Get a value of the environment variable
    HKEY key = HKEY_LOCAL_MACHINE;
    LPCSTR subKey = TEXT("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment");
    DWORD options = 0;
    REGSAM samDesired = KEY_ALL_ACCESS;
    
    HKEY openResult;
    LPCSTR valueName = "Fake";
    DWORD flags = RRF_RT_ANY;
    
    DWORD dataType;
    CHAR value[1024];
    DWORD valSize = sizeof(value);
    
    LONG err = RegOpenKeyExA(key, subKey, options, samDesired, &openResult);
    
    if (err != ERROR_SUCCESS)
    {
        return;
    }
    
    err = RegGetValueA(openResult, nullptr, valueName, flags, &dataType, static_cast<PVOID>(value), &valSize);
    
    if (err != ERROR_SUCCESS)
    {
        return;
    }
    
    switch (dataType)
    {
        case REG_SZ:
        {
            qDebug() << &value[0];
            break;
        }
        
        default:
        {
            qDebug() << "Something went wrong";
            break;
        }
    }
    
    RegCloseKey(openResult);
    
    // Parese a value of the environment variable
    std::string env(value);
    qDebug() << "len: " << env.length();
    qDebug() << "val: " << env.c_str();
    
    if (!env.empty())
    {
        qDebug() << "divide: ";
        std::regex rex("[^\\;;]+");
        std::regex_iterator<std::string::iterator> rit(env.begin(), env.end(), rex);
        std::regex_iterator<std::string::iterator> rend;
        
        while (rit != rend)
        {
            mPaths.push_back(trim(rit->str()).c_str());
            qDebug() << mPaths.back().c_str();
            ++rit;
        }
    }
}

} /* namespace pet */