#ifndef _UTC_DALI_LINEAR_CONSTRAINER_COMMON_H_
#define _UTC_DALI_LINEAR_CONSTRAINER_COMMON_H_

#include "dali-common.h"

using namespace Dali;

#define SUITE_NAME  "LINEAR_CONSTRAINER_UTC"

void LinearConstrainerSetupUniformProgress( Dali::LinearConstrainer& linearConstrainer);
void LinearConstrainerSetupNonUniformProgress( Dali::LinearConstrainer& linearConstrainer);
bool LinearConstrainerCompareType(Vector3 actorPosition, float getPosition, float epsilon);

#endif  //_UTC_DALI_LINEAR_CONSTRAINER_COMMON_H_
