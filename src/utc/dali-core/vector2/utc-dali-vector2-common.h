#ifndef _UTC_DALI_VECTOR2_COMMON_H_
#define _UTC_DALI_VECTOR2_COMMON_H_

#include <sstream>
#include "dali-common.h"

using namespace std;
using namespace Dali;

#define SUITE_NAME  "VECTOR2_UTC"
#define  VECTOR2_MATH_EPSILON  .0001f

//Create parent and child actor set their size and add to stage.
bool Vector2CreateParentAndChildActor(Actor &actorParent, Actor &actorChild);

#endif  //_UTC_DALI_VECTOR2_COMMON_H_
