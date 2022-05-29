#ifndef _UTC_DALI_PROPERTY_COMMON_H_
#define _UTC_DALI_PROPERTY_COMMON_H_

#include "dali-common.h"
#include <dali/dali.h>
#include <dali-toolkit/dali-toolkit.h>

using namespace std;
using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME  "PROPERTY_UTC"

#define PROPERTY_NAME  "position"
#define PROPERTY_COMPONENT_INDEX  0
#define PROPERTY_ANIMATION_TIME   0.3f

const float gTarget(100.0f);

const unsigned int PROPERTY_TIME_BEYOND_ANIM = static_cast< unsigned int >( 1000.0f*PROPERTY_ANIMATION_TIME ) + 2u;

//Helper for property animation for position X component
bool PropertyAnimationForPositionComponentX(Actor actor, Property property );


#endif  //_UTC_DALI_PROPERTY_COMMON_H_
