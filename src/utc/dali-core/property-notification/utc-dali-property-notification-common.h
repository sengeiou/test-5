#ifndef _UTC_DALI_PROPERTYNOTIFICATION_COMMON_H_
#define _UTC_DALI_PROPERTYNOTIFICATION_COMMON_H_

#include "dali-common.h"

using namespace std;
using namespace Dali;

#define SUITE_NAME  "PROPERTY_NOTIFICATION_UTC"

extern bool gCallBackCalled;

/**Set the Variable gCallBackCalled true*/
void PropertyNotificationTestCallback(PropertyNotification& source);

/**Test for varrying the input parameter*/
bool PropertyNotificationSetGetNotifyMode(PropertyNotification &notification, PropertyNotification::NotifyMode notifyModeCheck, PropertyNotification::NotifyMode notifyMode);

/**========================================*/
/** Custom connection tracker class */
/**========================================*/
//Class which  inherit connectiontracker
class TestClass : public ConnectionTracker
{
  public:

    TestClass()
    : mGreaterThan(100.0f)
    {
    }

    ~TestClass()
    {
    }

    bool Initialize()
    {
      mGreaterThan = 100.0f;
      mActor = Actor::New();
      DALI_CHECK_FALSE(!mActor, "actor is not created" );

      Stage::GetCurrent().Add( mActor );
      mNotification = mActor.AddPropertyNotification( Actor::Property::POSITION_X, GreaterThanCondition(mGreaterThan));
      mNotification.NotifySignal().Connect( this, &TestClass::OnPropertyNotify );
      return true;
    }

    void RemovePropertyNotification()
    {
      mActor.RemovePropertyNotification( mNotification );
    }

    void RemovePropertyNotifications()
    {
      mActor.RemovePropertyNotifications();
    }

    void Terminate()
    {
      Stage::GetCurrent().Remove( mActor );
      mActor.Reset();
      mNotification.Reset();
    }

    void OnPropertyNotify( PropertyNotification& source )
    {
      gCallBackCalled = true;
    }

    Actor mActor;
    PropertyNotification mNotification;
    float mGreaterThan;
};

//Class for propertynotification
class PropertyNotificationConstWrapper
{
  public:

    PropertyNotificationConstWrapper(PropertyNotification propertyNotification):mPropertyNotification(propertyNotification)
  {

  }

    /**
     * Returns const reference to property notification.
     * @return const reference.
     */
    const PropertyCondition& GetCondition() const
    {
      return mPropertyNotification.GetCondition();
    }

  private:
    PropertyNotification mPropertyNotification;
};

#endif  //_UTC_DALI_PROPERTYNOTIFICATION_COMMON_H_
