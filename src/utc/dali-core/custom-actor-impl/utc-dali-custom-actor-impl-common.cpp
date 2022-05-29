#include "utc-dali-custom-actor-impl-common.h"

bool CustomActorImplHasMethod1(const char* pchMethodName, std::vector<std::string> vecMethods)
{
  for(unsigned i = 0; i < vecMethods.size(); i++)
  {
    if(vecMethods.at(i).find(pchMethodName) != string::npos)
    {
      return true;
    }
  }
  return false;
}
