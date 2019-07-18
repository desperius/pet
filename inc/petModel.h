#ifndef _PET_MODEL_H_
#define _PET_MODEL_H_

#include <list>
#include <string>
#include <memory>

namespace pet
{

class petModel
{
public:
    petModel();
    
    std::list<std::string> GetPaths() { return mPaths; }
    
private:
    std::list<std::string> mPaths;
};

} /* namespace pet */

#endif /* _PET_MODEL_H_ */