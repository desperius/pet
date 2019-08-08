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
    
    bool Init();
    bool Update(std::list<std::string> paths);
    
    std::list<std::string> GetPaths() { return mPaths; }
    
private:
    static constexpr LPCSTR VAL_NAME = TEXT("Path");
    HKEY mOpenKey;
    std::list<std::string> mPaths;
};

} /* namespace pet */

#endif /* _PET_MODEL_H_ */