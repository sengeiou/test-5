#ifndef _UTC_DALI_QUATERNION_COMMON_H_
#define _UTC_DALI_QUATERNION_COMMON_H_

#include "dali-common.h"
#include <dali/dali.h>
#include <dali-toolkit/dali-toolkit.h>
#include <sstream>

using namespace std;
using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME  "QUATERNION_ITC"
#define QUAT_EPSILON  0.01f

namespace
{
  const float PI_OVER_180 = Dali::Math::PI/180.0f;
  const int INTERVAL_IN_MILLISEC = 0;
  const int MAX_INFO_LEN = 2;
  const float QUATERNION_TOLERANCE = 0.001f;
}

//Helper for comparing two Quaternion
bool QuaternionCompare(Quaternion q1, Quaternion q2, float epsilon);

//Helper for comparing two Vector3
bool QuaternionCompareVector3(Vector3 vector1, Vector3 vector2, float epsilon);

#endif  //_UTC_DALI_QUATERNION_COMMON_H_
