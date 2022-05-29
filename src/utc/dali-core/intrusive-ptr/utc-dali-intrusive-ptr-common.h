#ifndef _UTC_DALI_INTRUSIVE_PTR_COMMON_H_
#define _UTC_DALI_INTRUSIVE_PTR_COMMON_H_

#include "dali-common.h"
#include <dali-toolkit/dali-toolkit.h>

using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME  "INTRUSIVE_PTR_UTC"

extern bool g_bIntrusivePtrDummyCheck;

//Class is defined to check whether IntrusivePtr can work with a user-defined class
class IntrusivePtrDummyClass : public BaseObject
{
  public:

    IntrusivePtrDummyClass()
    {
    }

    ~IntrusivePtrDummyClass()
    {
    }

    void CheckIntrusivePtrDummyCreation()
    {
      g_bIntrusivePtrDummyCheck = true;
    }
};

#endif  //_UTC_DALI_INTRUSIVE_PTR_COMMON_H_
