#ifndef _UTC_DALI_ALPHA_FUNCTION_COMMON_H_
#define _UTC_DALI_ALPHA_FUNCTION_COMMON_H_

#include "dali-common.h"
#include <dali/public-api/dali-core.h>
#include <exception>


using namespace Dali;

#define SUITE_NAME  "ALPHA_FUNCTION_UTC"

#define RENDER_FRAME_INTERVAL   0
#define DEFAULT_DURATION  0.4f
#define FLOAT_VALUE_10F  10.0f
#define DEFAULT_ANGLE  70
#define DEFAULT_SQRT  1.70158f

/**Create an actor and Set actor properties */
bool AlphaFunctionsInit(Actor &actor , Animation &animation);

/**Remove actor from stage and stop animation */
void AlphaFunctionRemoveAnimationActor(Actor &actor , Animation &animation);

#endif  //_UTC_DALI_ALPHA_FUNCTION_COMMON_H_
