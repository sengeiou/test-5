#include "utc-dali-property-notification-common.h"

bool gCallBackCalled = false;

/**
 * @function      PropertyNotificationWait
 * @description   Set the Variable gCallBackCalled true.
 * @param[in]     PropertyNotification [Handle to the PropertyNotification]
 * @return        NA
 */
void PropertyNotificationWait(PropertyNotification& source)
{
  if(source)
  {
    LOG_I("Notification callback is called.");
    gCallBackCalled = true;
  }
}

/**
 * @function      PropertyNotificationSetGetNotifyMode
 * @description   Test for verifying the input parameter
 * @parame[out]   notification [Handle to the PropertyNotification]
 * @parame[in]    notifyModeCheck [Handle to the PropertyNotification::NotifyMode]
 * @parame[in]    notifyMode[Handle to the PropertyNotification::NotifyMode]
 * @return        result of this function
 */
bool PropertyNotificationSetGetNotifyMode(PropertyNotification &notification, PropertyNotification::NotifyMode notifyModeCheck, PropertyNotification::NotifyMode notifyMode)
{
  notification.SetNotifyMode(notifyModeCheck);
  notification.NotifySignal().Connect( &PropertyNotificationWait );
  notifyMode = notification.GetNotifyMode();
  DALI_CHECK_FALSE( notifyMode != notifyModeCheck, "Set and Get PropertyNotification mismatched");
  return true;
}