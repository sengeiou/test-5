#ifndef _UTC_DALI_TIMER_COMMON_H_
#define _UTC_DALI_TIMER_COMMON_H_

#include "dali-common.h"
#include <exception>
#include <sstream>
#include <Ecore.h>
#include <dali/dali.h>
#include <dali-toolkit/dali-toolkit.h>

using namespace std;
using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME    "TIMER_UTC"

const unsigned int PERIODIC_TICK_INTERVAL = 50u;
const unsigned int DEFAULT_TIME_INTERVAL_IN_MILLISEC = 0u;


//initiates the timer object
Timer TimerInit();


#endif  //_UTC_DALI_TIMER_COMMON_H_
