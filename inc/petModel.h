/**
 * @file      petModel.h
 * @brif      Contains class for Model of data shape in MVC architecture.
 * @author    Alexander Orel (desperius@gmail.com)
 * @version   1.0
 * @date      09/08/2019
 * @copyright GNU Public License
 */
 
#ifndef _PET_MODEL_H_
#define _PET_MODEL_H_

#include <list>
#include <string>
#include <memory>

#include <windows.h>

namespace pet
{

class petModel
{
public:
    petModel() = default;
    ~petModel();
    
    petModel(const petModel& that) = delete;
    petModel(petModel&& that) = delete;
    
    petModel& operator=(const petModel& that) = delete;
    petModel& operator=(petModel&& that) = delete;
    
    /**
     * @brief Gets data from Windows registry.
     * @return Returns true if success. Returns false or may throw an exception in case of failure.
     */
    bool Init();
    
    /**
     * @brief Updates stored data.
     * @param[in] paths List of paths received from user.
     * @return Returns true if data was successfully added to Windows registry.
     */
    bool Update(std::list<std::string> paths);
    
    std::list<std::string> GetPaths() { return mPaths; }
    
private:
    static constexpr LPCSTR VAL_NAME = TEXT("Path");
    HKEY mOpenKey;
    std::list<std::string> mPaths;
};

} /* namespace pet */

#endif /* _PET_MODEL_H_ */