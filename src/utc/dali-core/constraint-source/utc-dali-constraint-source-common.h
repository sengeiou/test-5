#ifndef _UTC_DALI_CONSTRAINTSOURCE_COMMON_H_
#define _UTC_DALI_CONSTRAINTSOURCE_COMMON_H_

#include "dali-common.h"
#include <dali/dali.h>
#include <dali-toolkit/dali-toolkit.h>

using namespace std;
using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME  "CONSTRAINT_SOURCE_UTC"

// Template structure for different type value
struct STConstraintSourceTypeValue
{
  STConstraintSourceTypeValue(bool bValue) : bValue(bValue)
  {
  }

  void operator()(bool &bCurrent, const PropertyInputContainer& container)
  {
    bCurrent = bValue;
  }
  bool bValue;
};

#endif  //_UTC_DALI_CONSTRAINTSOURCE_COMMON_H_
