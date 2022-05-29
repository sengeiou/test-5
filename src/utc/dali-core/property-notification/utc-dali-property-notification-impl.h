#include "utc-dali-property-notification-common.h"

int gRenderCountPropertyNotification;
TestClass* gTestClass;
Actor gActorPN;
PropertyNotification::NotifyMode gNotifyMode;
PropertyNotification::NotifyMode gNotifyModeCheck;
PropertyNotification gPropertyNotification;
float gMinXaxisPN= 0.0f, gMinYaxisPN = 0.0f, gMinZaxisPN = 0.0f, gMaxXaxisPN = 200.0f;

void PropertyNotificationSetGetNotifyModeONChangedP()
{
  float fGreaterVal = 100.0f;
  gCallBackCalled = false;
  gNotifyMode = PropertyNotification::NotifyOnChanged;
  gNotifyModeCheck = PropertyNotification::NotifyOnTrue;

  gActorPN = Actor::New();
  DALI_CHECK_FAIL(!gActorPN, "actor is not created " );

  Stage::GetCurrent().Add(gActorPN);
  gPropertyNotification = gActorPN.AddPropertyNotification(Actor::Property::POSITION_X, GreaterThanCondition(fGreaterVal));

  bool bRet = false;
  bRet = PropertyNotificationSetGetNotifyMode( gPropertyNotification, gNotifyModeCheck, gNotifyMode);
  DALI_CHECK_FAIL(!bRet, "Notification check has failed." );
}

void VTPropertyNotificationSetGetNotifyModeONChanged001()
{
  gActorPN.SetPosition(Vector3(gMaxXaxisPN,gMinYaxisPN,gMinZaxisPN));
}

void VTPropertyNotificationSetGetNotifyModeONChanged002()
{
  gActorPN.SetPosition(Vector3(gMinXaxisPN, gMinYaxisPN, gMinZaxisPN));
}

void VTPropertyNotificationSetGetNotifyModeONChanged003()
{
  DALI_CHECK_FAIL( !gCallBackCalled , "Notification is not Triggered");
  Stage::GetCurrent().Remove(gActorPN);
  DaliLog::PrintPass();
}

void PropertyNotificationSetGetNotifyModeONTrueP()
{
  float fGreaterVal = 100.0f;
  gCallBackCalled = false;
  gNotifyMode = PropertyNotification::NotifyOnFalse;
  gNotifyModeCheck = PropertyNotification::NotifyOnTrue;

  gActorPN = Actor::New();
  DALI_CHECK_FAIL(!gActorPN, "actor is not created" );

  Stage::GetCurrent().Add(gActorPN);
  gPropertyNotification= gActorPN.AddPropertyNotification(Actor::Property::POSITION_X, GreaterThanCondition(fGreaterVal));

  bool bRet = false;
  bRet = PropertyNotificationSetGetNotifyMode( gPropertyNotification, gNotifyModeCheck, gNotifyMode);
  DALI_CHECK_FAIL(!bRet, "Notification check is failed." );
}

void VTPropertyNotificationSetGetNotifyModeONTrue001()
{
  gActorPN.SetPosition(Vector3(gMinXaxisPN, gMinYaxisPN, gMinZaxisPN));
}

void VTPropertyNotificationSetGetNotifyModeONTrue002()
{
  gActorPN.SetPosition(Vector3(gMaxXaxisPN, gMinYaxisPN, gMinZaxisPN));
}

void VTPropertyNotificationSetGetNotifyModeONTrue003()
{
  DALI_CHECK_FAIL( !gCallBackCalled , "Notification is not Triggered");
  Stage::GetCurrent().Remove(gActorPN);
  DaliLog::PrintPass();
}

void PropertyNotificationSetGetNotifyModeONFalseP()
{
  float fGreaterVal = 100.0f;
  gCallBackCalled = false;
  gNotifyMode =  PropertyNotification::NotifyOnFalse;
  gNotifyModeCheck = PropertyNotification::NotifyOnTrue;

  gActorPN= Actor::New();
  DALI_CHECK_FAIL(!gActorPN, " actor is not created" );

  Stage::GetCurrent().Add(gActorPN);
  gPropertyNotification = gActorPN.AddPropertyNotification(Actor::Property::POSITION_X, GreaterThanCondition(fGreaterVal));

  bool bRet = false;
  bRet = PropertyNotificationSetGetNotifyMode( gPropertyNotification, gNotifyModeCheck, gNotifyMode);
  DALI_CHECK_FAIL(!bRet, "Notification check is failed." );
}

void VTPropertyNotificationSetGetNotifyModeONFalse001()
{
  gActorPN.SetPosition(Vector3(gMaxXaxisPN,gMinYaxisPN, gMinZaxisPN));
}

void VTPropertyNotificationSetGetNotifyModeONFalse002()
{
  gActorPN.SetPosition(Vector3(gMinXaxisPN, gMinYaxisPN, gMinZaxisPN));
}

void VTPropertyNotificationSetGetNotifyModeONFalse003()
{
  DALI_CHECK_FAIL( !gCallBackCalled , "Notification is not Triggered");
  Stage::GetCurrent().Remove(gActorPN);
  DaliLog::PrintPass();
}

void PropertyNotificationSetGetNotifyModeDisabledP()
{
  float fGreaterVal = 100.0f;
  gCallBackCalled = false;
  gNotifyMode = PropertyNotification::Disabled;
  gNotifyModeCheck = PropertyNotification::NotifyOnTrue;

  gActorPN = Actor::New();
  DALI_CHECK_FAIL(!gActorPN, "actor is not created " );

  Stage::GetCurrent().Add(gActorPN);
  gPropertyNotification= gActorPN.AddPropertyNotification(Actor::Property::POSITION_X, GreaterThanCondition(fGreaterVal));

  bool bRet = false;
  bRet = PropertyNotificationSetGetNotifyMode( gPropertyNotification, gNotifyModeCheck, gNotifyMode);
  DALI_CHECK_FAIL(!bRet, "Notification check is failed." );
}
void VTPropertyNotificationSetGetNotifyModeDisabled001()
{
  gActorPN.SetPosition(Vector3(gMaxXaxisPN, gMinYaxisPN, gMinZaxisPN));
}
void VTPropertyNotificationSetGetNotifyModeDisabled002()
{
  gActorPN.SetPosition(Vector3(gMinXaxisPN,gMinYaxisPN, gMinZaxisPN ));
}
void VTPropertyNotificationSetGetNotifyModeDisabled003()
{
  if(!gCallBackCalled) gCallBackCalled = !gCallBackCalled;
  DALI_CHECK_FAIL( !gCallBackCalled , "Notification is not disabled.");
  Stage::GetCurrent().Remove(gActorPN);
  DaliLog::PrintPass();
}

void PropertyNotificationGetConditionP()
{
  Actor actor;
  Stage stage;
  float fGreaterVal = 100.0f;
  PropertyNotification notification;
  PropertyCondition condition;
  PropertyCondition condition2;

  stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created" );

  actor = Actor::New();
  DALI_CHECK_FAIL(!actor, " actor is not created" );

  stage.Add(actor);

  condition = GreaterThanCondition(fGreaterVal);
  notification = actor.AddPropertyNotification(Actor::Property::POSITION_X,condition);

  condition2 = notification.GetCondition();

  DALI_CHECK_FAIL( condition2 != condition , " PropertyNotification Condition missmatched to the set condition" );

  stage.Remove(actor);

  DaliLog::PrintPass();
}

void PropertyNotificationGetConditionConstP()
{
  Actor actor;
  Stage stage;
  float fGreaterVal = 100.0f;
  PropertyNotification notification;
  PropertyCondition condition;

  stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created" );
  actor = Actor::New();
  DALI_CHECK_FAIL(!actor, " actor is not created" );
  stage.Add(actor);

  condition = GreaterThanCondition(fGreaterVal);
  notification = actor.AddPropertyNotification(Actor::Property::POSITION_X,condition);
  PropertyNotificationConstWrapper notificationConst(notification);

  const PropertyCondition& conditionReference1 = notificationConst.GetCondition();

  DALI_CHECK_FAIL(conditionReference1 != condition , "conditionReference1 != condition" );

  stage.Remove(actor);

  DaliLog::PrintPass();
}

void PropertyNotificationGetTargetP()
{
  float fGreaterVal = 100.0f;
  Handle handleobject;
  Handle handleobject2;
  PropertyNotification notification;
  PropertyCondition condition;

  handleobject = Actor::New();
  DALI_CHECK_FAIL(!handleobject, "handleobject is not created " );

  condition = GreaterThanCondition(fGreaterVal);
  notification = handleobject.AddPropertyNotification(Actor::Property::POSITION_X,condition);

  handleobject2 = notification.GetTarget();

  DALI_CHECK_FAIL( !handleobject2 , "Not a valid handleobject" );
  DALI_CHECK_FAIL( handleobject2 != handleobject , "Getting Target failed" );

  DaliLog::PrintPass();
}

void PropertyNotificationGetTargetPropertyP()
{
  float fGreaterVal = 100.0f;
  Handle handleobject;
  Handle handleobject2;
  PropertyNotification notification;
  PropertyCondition condition;

  Property::Index indexSetValue;
  Property::Index indexGetValue;

  handleobject = Actor::New();
  DALI_CHECK_FAIL(!handleobject, "handleobject is not created" );
  condition = GreaterThanCondition(fGreaterVal);

  indexSetValue = Actor::Property::POSITION_X;
  notification = handleobject.AddPropertyNotification(indexSetValue,condition);
  indexGetValue = notification.GetTargetProperty();
  DALI_CHECK_FAIL( indexGetValue != indexSetValue , "Getting Target failed for position X" );

  indexSetValue = Actor::Property::POSITION_Y;
  notification = handleobject.AddPropertyNotification(indexSetValue,condition);
  indexGetValue = notification.GetTargetProperty();
  DALI_CHECK_FAIL( indexGetValue != indexSetValue , "Getting Target failed  for position Y" );

  DaliLog::PrintPass();
}

void PropertyNotificationGetNotifyResultP()
{
  PropertyNotification::NotifyMode notifyModeCheck = PropertyNotification::NotifyOnChanged;

  bool bInitialize = false;
  Vector3 vecSetVal(0.0f, 0.0f, 0.0f), vecSetVal2(200.0f, 0.0f, 0.0f);

  gTestClass = new TestClass();

  bInitialize = gTestClass->Initialize();
  DALI_CHECK_FAIL(!bInitialize, "Object has not been initialized" );

  gTestClass->mNotification.SetNotifyMode(notifyModeCheck);

  gTestClass->mActor.SetPosition(vecSetVal);

  gCallBackCalled = false;
  gTestClass->mActor.SetPosition(vecSetVal2);
}
void VTPropertyNotificationGetNotifyResult001()
{
  bool bResult= false;
  DALI_CHECK_FAIL( !gCallBackCalled , "Notification not Triggered" );

  bResult= gTestClass->mNotification.GetNotifyResult();
  DALI_CHECK_FAIL( !bResult , "GetNotifyResult Invalid" );

  DaliLog::PrintPass();
}

void PropertyNotificationDownCastP()
{
  float fCondition = 100.0f;
  /**Actor handle construction is required for constructing property notification**/
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor handle is empty");

  /**PropertyCondition handle construction is required for constructing property notification**/
  PropertyCondition condition = GreaterThanCondition(fCondition);
  DALI_CHECK_FAIL(!condition, "PropertyCondition handle is empty");

  /**An property index is required for constructing property notification**/
  Property::Index index = Actor::Property::POSITION_X;

  PropertyNotification notification = actor.AddPropertyNotification(index, condition);
  DALI_CHECK_FAIL(!notification, "PropertyNotification instance is not created.");

  BaseHandle baseHandle = notification;
  PropertyNotification notificationDownCasted = PropertyNotification::DownCast( baseHandle );
  DALI_CHECK_FAIL(!notificationDownCasted, "PropertyNotification instance is empty after downcast.");

  Handle handleTarget = notificationDownCasted.GetTarget();
  Property::Index indexTarget = notificationDownCasted.GetTargetProperty();
  PropertyCondition conditionGet  = notificationDownCasted.GetCondition();

  DALI_CHECK_FAIL( (handleTarget != actor) || (indexTarget != index) || ( conditionGet != condition ), "PropertyNotification::DownCast has failed with expected target, property and condition" );

  DaliLog::PrintPass();
}


void PropertyNotificationDownCastN()
{
  float fCondition = 100.0f;
  Actor somethingElse = Actor::New();
  DALI_CHECK_FAIL(!somethingElse, "Actor handle is empty");

  /**Actor handle construction is required for constructing property notification**/
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor handle is empty");

  /**PropertyCondition handle construction is required for constructing property notification**/
  PropertyCondition condition = GreaterThanCondition(fCondition);
  DALI_CHECK_FAIL(!condition, "PropertyCondition handle is empty");

  /**An property index is required for constructing property notification**/
  Property::Index index = Actor::Property::POSITION_X;

  PropertyNotification notification = actor.AddPropertyNotification(index, condition);
  DALI_CHECK_FAIL(!notification, "PropertyNotification instance is not created.");

  BaseHandle baseHandle = somethingElse;
  DALI_CHECK_FAIL(!baseHandle, "BaseHandle is empty");

  PropertyNotification notificationDownCasted = PropertyNotification::DownCast( baseHandle );
  DALI_CHECK_FAIL( notificationDownCasted, "PropertyNotification::DownCast is failed with expected PropertyNotification" );

  DaliLog::PrintPass();
}

void PropertyNotificationConstructorP()
{
  float fCondition = 100.0f;
  Actor somethingElse = Actor::New();
  DALI_CHECK_FAIL(!somethingElse, "Actor handle is empty");

  /**Actor handle construction is required for constructing property notification**/
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor handle is empty");

  /**PropertyCondition handle construction is required for constructing property notification**/
  PropertyCondition condition = GreaterThanCondition(fCondition);
  DALI_CHECK_FAIL(!condition, "PropertyCondition handle is empty");

  /**An property index is required for constructing property notification**/
  Property::Index index = Actor::Property::POSITION_X;

  PropertyNotification notification = actor.AddPropertyNotification(index, condition);
  DALI_CHECK_FAIL(!notification, "PropertyNotification instance is not created.");

  DaliLog::PrintPass();
}

void PropertyNotificationCopyConstructorP()
{
  float fCondition = 100.0f;
  Actor somethingElse = Actor::New();
  DALI_CHECK_FAIL(!somethingElse, "Actor handle is empty");

  /**Actor handle construction is required for constructing property notification**/
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor handle is empty");

  /**PropertyCondition handle construction is required for constructing property notification**/
  PropertyCondition condition = GreaterThanCondition(fCondition);
  DALI_CHECK_FAIL(!condition, "PropertyCondition handle is empty");

  /**An property index is required for constructing property notification**/
  Property::Index index = Actor::Property::POSITION_X;

  PropertyNotification notification = actor.AddPropertyNotification(index, condition);
  DALI_CHECK_FAIL(!notification, "PropertyNotification instance is not created.");

  PropertyNotification notification2 = notification;
  DALI_CHECK_FAIL(!notification2, "PropertyNotification instance is not created.");

  DALI_CHECK_FAIL( (notification2 != notification), "PropertyNotification instance is not created.");

  DaliLog::PrintPass();
}

void PropertyNotificationOperatorAssignmentP()
{
  float fCondition = 100.0f;
  Actor somethingElse = Actor::New();
  DALI_CHECK_FAIL(!somethingElse, "Actor handle is empty");

  /**Actor handle construction is required for constructing property notification**/
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor handle is empty");

  /**PropertyCondition handle construction is required for constructing property notification**/
  PropertyCondition condition = GreaterThanCondition(fCondition);
  DALI_CHECK_FAIL(!condition, "PropertyCondition handle is empty");

  /**An property index is required for constructing property notification**/
  Property::Index index = Actor::Property::POSITION_X;

  PropertyNotification notification = actor.AddPropertyNotification(index, condition);
  DALI_CHECK_FAIL(!notification, "PropertyNotification instance is not created.");

  PropertyNotification notification2;
  notification2 = notification;
  DALI_CHECK_FAIL(!notification2, "PropertyNotification instance is not created.");

  DALI_CHECK_FAIL( (notification2 != notification), "PropertyNotification instance is not created.");

  DaliLog::PrintPass();
}

