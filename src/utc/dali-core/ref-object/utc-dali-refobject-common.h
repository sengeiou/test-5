#ifndef _UTC_DALI_REFOBJECT_COMMON_H_
#define _UTC_DALI_REFOBJECT_COMMON_H_

#include <dali.h>
#include "dali-common.h"
#include <exception>
#include <dali-toolkit/public-api/controls/control.h>
#include <dali/dali.h>
#include <dali-toolkit/dali-toolkit.h>

using namespace std;
using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME  "REFOBJ_UTC"

//Check whether stage and Actor can be initialized
bool RefObjInit(Stage &stage, Actor &actor,Vector3 *vec3SetPosition);

#endif  //_UTC_DALI_REFOBJECT_COMMON_H_
