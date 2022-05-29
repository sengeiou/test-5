#ifndef _UTC_DALI_TIMEPERIOD_COMMON_H_
#define _UTC_DALI_TIMEPERIOD_COMMON_H_

#include "dali-common.h"

using namespace Dali;

#define SUITE_NAME  "TIME_PERIOD_UTC"
#define F_START  10.0f
#define F_TARGET  40.0f

extern bool gSignalAfterTime;

/**Helper for Actor, Animation creation**/
bool TimePeriodActorAnimationNew( Actor &actor, Animation& animation, float fStart, float fTime, Property::Index& index);

/**Helper for setting necessary property to actor and animation**/
void TimePeriodSetPropertyDuration( Actor &actor, Animation& animation, float fStart, float fDuration, Property::Index& index );

/**Helper for playing animation with required property and target**/
void TimePeriodAnimPlay( Actor &actor, Animation &animation, float fStart, float fTarget, Property::Index& index, TimePeriod timePeriod );

/**Functor to check whether animation is finished or not**/
void TimePeriodAnimationEnd(Animation& animation);

#endif  //_UTC_DALI_TIMEPERIOD_COMMON_H_
