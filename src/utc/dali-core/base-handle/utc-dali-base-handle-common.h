#ifndef _UTC_DALI_BASE_HANDLE_COMMON_H_
#define _UTC_DALI_BASE_HANDLE_COMMON_H_

#include <exception>

#include "dali-common.h"

using namespace Dali;

#define RENDER_FRAME_INTERVAL_H  16                      //Duration of each frame in ms. (at approx 60FPS)
#define DEFAULT_WAIT_PERIOD  100                         //Default waiting period for check.

#define SUITE_NAME  "BASE_HANDLE_UTC"


enum BasehandleRegisterPropertyOption
{
  REGISTERPROPERTY_WITH_ACCESSMODE,
  REGISTERPROPERTY_WITHOUT_ACCESSMODE
};

enum BasehandleSetGetPropertyOption
{
  SETGETPROPERTY_RETURN_PROPERTYVALUE,
  SETGETPROPERTY_RETURN_TYPEVALUE
};

//Check whether stage and Actor can be initialized
bool basehandleInit(Stage &stage, Actor &actor,Vector3 *vec3SetPosition);

#endif  //_UTC_DALI_BASE_HANDLE_COMMON_H_
