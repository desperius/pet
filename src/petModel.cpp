/**
 * @file      petModel.cpp
 * @brif      Contains implementation of class for Model of data shape in MVC architecture.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      09/08/2019
 * @copyright GNU Public License
 */

#include "petModel.h"

#include <regex>

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

petModel::~petModel()
{
    RegCloseKey(mOpenKey);
}

bool petModel::Init()
{
    // Get a value of the environment variable
    const HKEY key = HKEY_LOCAL_MACHINE;
    LPCSTR subKey = TEXT("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment");
    const DWORD options = 0;
    const REGSAM samDesired = KEY_ALL_ACCESS;
    const DWORD flags = RRF_RT_ANY;
    
    DWORD dataType;
    const short MAX_LENGTH_WIN_NT = 2048;
    
    // Sets twice greatest possible length of Environment Variable. Just in case :)
    CHAR value[MAX_LENGTH_WIN_NT * 2];
    DWORD valSize = sizeof(value);
    
    LSTATUS err = RegOpenKeyExA(key, subKey, options, samDesired, &mOpenKey);
    
    if (err != ERROR_SUCCESS)
    {
        return false;
    }
    
    err = RegGetValueA(mOpenKey, nullptr, VAL_NAME, flags, &dataType, static_cast<PVOID>(value), &valSize);
    
    if (err != ERROR_SUCCESS)
    {
        return false;
    }
    
    switch (dataType)
    {
        case REG_SZ:
        {
            // Parese a value of the environment variable
            std::string env(value);
            
            if (!env.empty())
            {
                std::regex rex("[^\\;;]+");
                std::regex_iterator<std::string::iterator> rit(env.begin(), env.end(), rex);
                std::regex_iterator<std::string::iterator> rend;
                
                while (rit != rend)
                {
                    mPaths.push_back(trim(rit->str()).c_str());
                    ++rit;
                }
            }
            
            break;
        }
        
        default:
        {
            throw std::runtime_error("Failed to get Environment Variable value!");
            break;
        }
    }
    
    return true;
}

bool petModel::Update(std::list<std::string> paths)
{
    mPaths = std::move(paths);
    std::string newVal;
    
    for (auto& path : mPaths)
    {
        newVal.append(path);
        newVal.append(";");
    }
    
    LSTATUS err = RegSetValueExA(mOpenKey, VAL_NAME, 0, REG_SZ, reinterpret_cast<const BYTE*>(newVal.c_str()), newVal.length());
    
    return (ERROR_SUCCESS == err);
}

} /* namespace pet */
