#ifndef _UTC_DALI_VECTOR3_COMMON_H_
#define _UTC_DALI_VECTOR3_COMMON_H_

#include <sstream>
#include "dali-common.h"

using namespace std;
using namespace Dali;

#define SUITE_NAME  "VECTOR3_ITC"
#define  VECTOR3_MATH_EPSILON  0.00001f    //  Machine error tolerance

//Apply a vector in a Actor
bool vector3IsApplicable(Vector3 &vec3TestValue);

//Create parent and child actor set their size and add to stage
bool vector3CreateParentAndChildActor(Actor &actorParent, Actor &actorChild);

#endif  //_UTC_DALI_VECTOR3_COMMON_H_
