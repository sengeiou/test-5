#ifndef _UTC_DALI_PATH_COMMON_H_
#define _UTC_DALI_PATH_COMMON_H_

#include "dali-common.h"

using namespace Dali;

#define SUITE_NAME  "PATH_UTC"

#define F_X2(x)  x*x
#define PATH_POINT_COUNT  2
#define PATH_X_OFFSET  10.0f
#define PATH_ANIM_DUR_SEC  2.0f
#define PATH_POINT_CURVATURE  0.25f

/** Helper for path animation **/
bool PathAnimatePlay(Dali::Path path);

#endif  //_UTC_DALI_PATH_COMMON_H_
