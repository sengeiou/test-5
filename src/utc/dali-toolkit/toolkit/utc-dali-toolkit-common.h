#ifndef _UTC_DALI_TOOLKIT_COMMON_H_
#define _UTC_DALI_TOOLKIT_COMMON_H_

#include "dali-common.h"
#include <dali-toolkit/dali-toolkit.h>

using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME             "TOOLKIT_UTC"

/**Global constant value definition **/
const Vector2 TOOLKIT_VEC2_SCROLL_POS_MAX(400.0f, 400.0f);
const Vector3 TOOLKIT_VEC3_INSIDE_BOUNDARY(Vector2(200.0f, 200.0f));
const Vector3 TOOLKIT_VEC3_OUTSIDE_BOUNDARY(Vector2(500.0f, 500.0f));
const Vector2 TOOLKIT_VEC2_CURRENT_POSITION(50.0f, 50.0f);
const Vector2 TOOLKIT_VEC2_NEW_POSITION(100.0f, 100.0f);

/**Helper to compare to Vector3 values**/
bool ToolkitVector3Compare(Vector3 vec3ValueOne, Vector3 vec3ValueTwo);

#endif  //_UTC_DALI_TOOLKIT_COMMON_H_
