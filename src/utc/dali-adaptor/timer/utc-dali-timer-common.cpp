#include "utc-dali-timer-common.h"

Timer TimerInit()
{
  Timer timer = Timer::New(PERIODIC_TICK_INTERVAL);
  return timer;
}
