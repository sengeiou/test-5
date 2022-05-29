#include "utc-dali-connection-tracker-common.h"

ConnectionTrackerSlotObserver* gConnectionTrackerSlotObserver;
CallbackFunction* gConnectionTrackerCallBack;

void ConnectionTrackerReset()
{
  if(gConnectionTrackerSlotObserver)
    {
      delete gConnectionTrackerSlotObserver;
      gConnectionTrackerSlotObserver = NULL;
    }

  if(gConnectionTrackerCallBack)
    {
      delete gConnectionTrackerCallBack;
      gConnectionTrackerCallBack = NULL;
    }
}
