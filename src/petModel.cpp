#include "petModel.h"

#include <regex>
#include <QDebug>

namespace pet
{

const HKEY KEY = HKEY_LOCAL_MACHINE;
LPCSTR SUB_KEY = TEXT("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment");
LPCSTR VALUE_NAME = TEXT("Fake");
    
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
    DWORD options = 0;
    REGSAM samDesired = KEY_ALL_ACCESS;
    DWORD flags = RRF_RT_ANY;
    
    DWORD dataType;
    CHAR value[4096];
    DWORD valSize = sizeof(value);
    
    LSTATUS err = RegOpenKeyExA(KEY, SUB_KEY, options, samDesired, &mOpenKey);
    
    if (err != ERROR_SUCCESS)
    {
        return;
    }
    
    err = RegGetValueA(mOpenKey, nullptr, VALUE_NAME, flags, &dataType, static_cast<PVOID>(value), &valSize);
    
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

petModel::~petModel()
{
    RegCloseKey(mOpenKey);
}

bool pet::petModel::Update(std::list<std::string> paths)
{
    mPaths = std::move(paths);
    std::string newVal;
    
    for (auto& path : mPaths)
    {
        newVal.append(path);
        newVal.append(";");
    }
    
    LSTATUS err = RegSetValueExA(mOpenKey, VALUE_NAME, 0, REG_SZ, reinterpret_cast<const BYTE*>(newVal.c_str()), newVal.length());
    
    return (ERROR_SUCCESS == err);
}

} /* namespace pet */
