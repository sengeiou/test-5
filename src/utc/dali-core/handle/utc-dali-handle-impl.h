#include "utc-dali-handle-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

Handle gHandle;                            /**Handle instance*/
Actor  gActorHandle;                       /**Actor instance*/
int gRenderCountHandle;                    /**Render count*/
bool gHandleCallBackCalled = false;        /**Status for handle callbacl called*/
PropertyNotification gHandleNotification;

/**
 * @function     HandleTestCallback
 * @description  Set the Variable gHandleCallBackCalled true.
 * @param[in]    source [Handle to the PropertyNotification]
 * @return       NA
 */

void HandleTestCallback(PropertyNotification& source)
{
  if( source )
  {
    gHandleCallBackCalled = true;
  }
}


/**
 * ##############################
 * TC Logic Implementation Area.
 * ##############################
 **/

void HandleConstructorP()
{
  Handle handle;
  DALI_CHECK_INSTANCE( !handle, "Handle::Handle() is failed." );

  DaliLog::PrintPass();
}

void HandleCopyConstructorP()
{
  Handle handle = Handle::New();
  DALI_CHECK_INSTANCE( handle, "Handle::New() is failed." );

  Handle handleWeightObject = handle;
  DALI_CHECK_INSTANCE( handleWeightObject, "Handle::Handle() is failed." );

  DaliLog::PrintPass();
}

void HandleNewP()
{
  unsigned int uHandlePropertyCount = 0u, uWeightObjectPropertyCount = 0u;
  const string STR_PROPERTY_NAME = "weight";

  Handle handle = Handle::New();
  DALI_CHECK_INSTANCE( handle, "Handle::New() is failed." );

  uHandlePropertyCount = handle.GetPropertyCount();

  Handle handleWeightObject = WeightObject::New();
  DALI_CHECK_INSTANCE( handleWeightObject, "WeightObject::New() is failed." );

  uWeightObjectPropertyCount = handleWeightObject.GetPropertyCount();

  DALI_CHECK_FAIL( uWeightObjectPropertyCount <= uHandlePropertyCount, "WeightObject does not have any property." );

  DaliLog::PrintPass();
}

void HandleGetPropertyIndicesP()
{
  Handle handle;
  Property::IndexContainer indices;
  Stage stage;
  Actor actor;

  if(!HandleAddActor(actor, stage))
  {
    test_return_value=TC_FAIL;
    return;
  }

  handle = actor;
  DALI_CHECK_FAIL(!handle, "handle instance is not created.");

  handle.GetPropertyIndices(indices);
  DALI_CHECK_FAIL(indices.Size() == 0, "No property is found, property count: ");
  DALI_CHECK_FAIL(handle.GetPropertyCount() != indices.Size(), "Property count mismatches. ");
  stage.Remove(actor);

  DaliLog::PrintPass();
}

void HandleIsPropertyAConstraintInputP()
{
  string strPropertyName;
  Handle handle;
  Property::IndexContainer indices;
  Stage stage;
  Actor actor;

  if(!HandleAddActor(actor, stage))
  {
    test_return_value=TC_FAIL;
    return;
  }

  handle = actor;
  handle.GetPropertyIndices(indices);
  DALI_CHECK_FAIL(indices.Size() == 0, "No property is found, property count: ");
  for(unsigned int i = 0u; i < handle.GetPropertyCount(); i++)
  {
    strPropertyName = handle.GetPropertyName(indices[i]);
    DALI_CHECK_FAIL(strPropertyName.empty(), " is failed to register.");
    if(handle.IsPropertyAConstraintInput(indices[i]))
    {
      LOG_I(" can BE used as in input to a constraint.");
    }
    else
    {
      LOG_I(" can NOT be used as in input to a constraint.");
    }
  }
  stage.Remove(actor);

  DaliLog::PrintPass();
}

void HandleAddRemovePropertyNotificationP()
{
  float fCondition = 100.0f;
  Handle handleobjectTwo;
  PropertyCondition condition, conditionGet;

  PropertyNotification::NotifyMode notifyMode = PropertyNotification::NotifyOnChanged;

  gActorHandle = Actor::New();
  DALI_CHECK_FAIL(!gActorHandle, "actor is not created");

  Stage::GetCurrent().Add(gActorHandle);
  condition = GreaterThanCondition(fCondition);

  gHandle = gActorHandle;
  DALI_CHECK_FAIL(!gHandle, "handle is not Initialized");

  Property::Index indexTarget = Actor::Property::SIZE_WIDTH;
  gHandleNotification = gHandle.AddPropertyNotification( indexTarget, condition );
  DALI_CHECK_FAIL(!gHandleNotification, "Property Notification is not created.");

  handleobjectTwo = gHandleNotification.GetTarget();
  conditionGet = gHandleNotification.GetCondition();
  Property::Index indexGet = gHandleNotification.GetTargetProperty();

  DALI_CHECK_FAIL( (handleobjectTwo != gHandle) || (conditionGet != condition) || (indexGet != indexTarget), "Handle::AddPropertyNotification is failed.");

  gHandleNotification.NotifySignal().Connect( &HandleTestCallback );
  gHandleNotification.SetNotifyMode(notifyMode);

  gHandleCallBackCalled = false;

  gActorHandle.SetSize(F_VAL_X, F_VAL_ZERO, F_VAL_ZERO); //Set a initial size
}
void VTHandleAddRemovePropertyNotification001()
{
  gActorHandle.SetSize(F_VAL_ZERO, F_VAL_ZERO, F_VAL_ZERO); //Set a changed size
}
void VTHandleAddRemovePropertyNotification002()
{
  DALI_CHECK_FAIL( !gHandleCallBackCalled , "Notification not Triggered after adding Property Notification");

  gHandle.RemovePropertyNotification( gHandleNotification );

  gHandleCallBackCalled = false;

  gActorHandle.SetSize(F_VAL_X, F_VAL_ZERO, F_VAL_ZERO); //again, set a initial size
}
void VTHandleAddRemovePropertyNotification003()
{
  gActorHandle.SetSize(F_VAL_ZERO, F_VAL_ZERO, F_VAL_ZERO); //again, set a changed size
}
void VTHandleAddRemovePropertyNotification004()
{
  DALI_CHECK_FAIL(gHandleCallBackCalled , "Notification  Triggered after removing Property Notification ");

  Stage::GetCurrent().Remove(gActorHandle);
  DaliLog::PrintPass();
}

void HandleGetPropertyCountAndIndexAndNameAndTypeP()
{
  int ncount=0 , ncount2=0;
  Handle handleobject;
  Property::Type type = Property::FLOAT, type1;
  Property::Index index, index2;
  float fSetValue = 123.0f;
  const Property::Value value(fSetValue);
  Property::AccessMode accessMode = Property::READ_WRITE;
  const string  strname = "test-property";
  string strName2 = "";

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created");
  stage.Add(actor);

  handleobject = actor;
  DALI_CHECK_FAIL(!handleobject, "handleobject is not created");

  index = handleobject.RegisterProperty( strname, value,accessMode);
  handleobject.SetProperty (index, value);

  ncount2 = handleobject.GetPropertyCount();
  index2 = handleobject.GetPropertyIndex(strname);

  strName2 = handleobject.GetPropertyName(index);
  type1 = handleobject.GetPropertyType(index);

  DALI_CHECK_FAIL(strName2 != strname || index2 != index ||  ncount2 == ncount ||  type1 != type, "UTcHandleGetPropertyCountAndIndexAndNameAndType is failed");
  stage.Remove(actor);
  DaliLog::PrintPass();
}

void HandleIsPropertyWritableP()
{
  Handle handleobject;
  Handle handleobject2;
  Property::Index index;
  bool bResult = false;
  float fSetValue = 123.0f, fduration = 3.0f, fXaxis = 10.0f, fYaxis = 50.0f, fZaxis = 0.0f;
  Property::Value value(fSetValue);
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::READ_WRITE;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created");
  stage.Add(actor);

  handleobject = actor;
  DALI_CHECK_FAIL(!handleobject, "handleobject is not created");

  index = handleobject.RegisterProperty( strName, value,accessMode);
  handleobject.SetProperty (index, value);

  bResult = handleobject.IsPropertyWritable(index);

  DALI_CHECK_FAIL(bResult != true , "UTcHandleIsPropertyWritable is failed");

  try
  {
    Animation mAnimation;
    mAnimation = Animation::New(fduration); // duration 3 seconds
    mAnimation.AnimateTo(Property(actor, Actor::Property::POSITION), Vector3(fXaxis, fYaxis, fZaxis));
    mAnimation.Play();
  }
  catch (Dali::DaliException& e)
  {
    LOG_E("IsPropertyAnimatable return true but Write to animation is not  done  successfully");
    test_return_value=TC_FAIL;
    return;
  }

  stage.Remove(actor);

  DaliLog::PrintPass();
}

void HandleIsPropertyAnimatableP()
{
  Handle handleobject;
  Handle handleobject2;
  Property::Index index;
  bool bResult = false,  bSetval = false;
  float  fduration = 3.0f, fXaxis = 10.0f, fYaxis = 50.0f, fZaxis = 0.0f;
  const Property::Value value(bSetval);
  string  strName = "test-property-test";
  Property::AccessMode accessMode = Property::ANIMATABLE;

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created");
  stage.Add(actor);

  handleobject = actor;
  DALI_CHECK_FAIL(!handleobject, "handleobject is not created");

  index = handleobject.RegisterProperty( strName, value,accessMode);
  handleobject.SetProperty (index, value);

  bResult = handleobject.IsPropertyAnimatable(index);
  DALI_CHECK_FAIL(bResult != true , "UTcHandleIsPropertyAnimatable is failed");

  try
  {
    Animation mAnimation;
    mAnimation = Animation::New(fduration); // duration 3 seconds
    mAnimation.AnimateTo(Property(actor, Actor::Property::POSITION), Vector3(fXaxis, fYaxis, fZaxis));
    mAnimation.Play();
  }
  catch (Dali::DaliException& e)
  {
    LOG_E("IsPropertyAnimatable return true but Animation is not  done  successfully");
    test_return_value=TC_FAIL;
    return;
  }

  stage.Remove(actor);

  DaliLog::PrintPass();
}

void HandleSupportsP()
{
  Handle handleobject;
  Handle handleobject2;
  Property::Index index;
  bool bResult = false;
  Property::Type type = Property::FLOAT;
  float fSetValue = 123.0f;
  Property::Value value(fSetValue);
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::READ_WRITE;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created");
  stage.Add(actor);

  handleobject = actor;
  DALI_CHECK_FAIL(!handleobject, "handleobject is not created");

  index = handleobject.RegisterProperty( strName, value,accessMode);
  handleobject.SetProperty (index, value);

  if(!handleobject.IsPropertyWritable(index))
  {
    LOG_E("Property is not writable");
    test_return_value=TC_FAIL;
    return;
  }
  if (handleobject.GetPropertyType(index) != type)
  {
    LOG_E("Property type did not match");
    test_return_value=TC_FAIL;
    return;
  }

  bResult = handleobject.Supports(Handle::DYNAMIC_PROPERTIES);

  DALI_CHECK_FAIL(bResult != true , "UTcHandleSupport is failed");

  stage.Remove(actor);

  DaliLog::PrintPass();
}

void HandleSetGetPropertyFloatP()
{
  Handle handleobject;
  Handle handleobject2;
  Property::Index index= 0;
  Property::Type type = Property::FLOAT;
  Property::Type type2 = Property::NONE ;
  float fSetValue = 123.0f,fGetValue = 0.0f ;
  Property::Value value(fSetValue);
  Property::Value value1;
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::READ_WRITE;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created");
  stage.Add(actor);

  if(!(HandleSetGetProperty(stage,actor,handleobject,index,type,type2,&strName,&fSetValue,&fGetValue,value,value1,accessMode,SETGETPROPERTY_RETURN_PROPERTYVALUE)))
  {
    LOG_E("Handle SetGetProeprty is Mismatched");
    stage.Remove(actor);
    test_return_value=TC_FAIL;
    return;
  }

  stage.Remove(actor);

  DaliLog::PrintPass();
}

void HandleSetGetPropertyStringP()
{
  Handle handleobject;
  Handle handleobject2;
  Property::Index index= 0;
  Property::Type type = Property::STRING;
  Property::Type type2 = Property::NONE ;
  string pszSetValue= "SetValue",pszGetValue;
  string strName = "test-property";
  Property::Value value(pszSetValue);
  Property::Value value1;

  Property::AccessMode accessMode = Property::READ_WRITE;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created");
  stage.Add(actor);

  DALI_CHECK_FAIL(!(HandleSetGetProperty(stage,actor,handleobject,index,type,type2,&strName,&pszSetValue,&pszGetValue,value,value1,accessMode,SETGETPROPERTY_RETURN_PROPERTYVALUE)), "Handle SetGetProeprty is Mismatched");

  stage.Remove(actor);

  DaliLog::PrintPass();
}

void HandleSetGetPropertyIntP()
{
  Handle handleobject;
  Handle handleobject2;
  Property::Index index= 0;
  Property::Type type = Property::INTEGER;
  Property::Type type2 = Property::NONE ;
  int nSetValue = 4, nGetValue = 0 ;
  Property::Value value(nSetValue);
  Property::Value value1;
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::READ_WRITE;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created");
  stage.Add(actor);

  DALI_CHECK_FAIL(!(HandleSetGetProperty(stage,actor,handleobject,index,type,type2,&strName,&nSetValue,&nGetValue,value,value1,accessMode,SETGETPROPERTY_RETURN_PROPERTYVALUE)), " Handle SetGetProeprty is Mismatched");

  stage.Remove(actor);

  DaliLog::PrintPass();
}

void HandleSetGetPropertyBooleanP()
{
  Handle handleobject;
  Handle handleobject2;
  Property::Index index= 0;
  Property::Type type = Property::BOOLEAN;
  Property::Type type2 = Property::NONE ;
  bool bSetValue = true,bGetValue = false ;
  Property::Value value(bSetValue);
  Property::Value value1;
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::READ_WRITE;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created");
  stage.Add(actor);

  DALI_CHECK_FAIL(!(HandleSetGetProperty(stage,actor,handleobject,index,type,type2,&strName,&bSetValue,&bGetValue,value,value1,accessMode,SETGETPROPERTY_RETURN_PROPERTYVALUE)), "Handle SetGetProeprty is Mismatched");

  stage.Remove(actor);
  DaliLog::PrintPass();
}

void HandleSetGetPropertyVector2P()
{
  Handle handleobject;
  Handle handleobject2;
  Property::Index index= 0;
  Property::Type type = Property::VECTOR2;
  Property::Type type2 = Property::NONE ;
  Vector2 vec2SetValue(0.3f,0.4f),vec2GetValue(0.0f,0.0f) ;
  Property::Value value(vec2SetValue);
  Property::Value value1;
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::READ_WRITE;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created");
  stage.Add(actor);

  DALI_CHECK_FAIL(!(HandleSetGetProperty(stage,actor,handleobject,index,type,type2,&strName,&vec2SetValue,&vec2GetValue,value,value1,accessMode,SETGETPROPERTY_RETURN_PROPERTYVALUE)), "Handle SetGetProeprty is Mismatched");
  stage.Remove(actor);

  DaliLog::PrintPass();
}

void HandleSetGetPropertyVector3P()
{
  Handle handleobject;
  Handle handleobject2;
  Property::Index index= 0;
  Property::Type type = Property::VECTOR3;
  Property::Type type2 = Property::NONE ;
  Vector3 vec3SetValue(0.3f,0.4f,0.8f),vec3GetValue(0.0f,0.0f,0.0f) ;
  Property::Value value(vec3SetValue);
  Property::Value value1;
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::READ_WRITE;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created");
  stage.Add(actor);

  DALI_CHECK_FAIL(!(HandleSetGetProperty(stage,actor,handleobject,index,type,type2,&strName,&vec3SetValue,&vec3GetValue,value,value1,accessMode,SETGETPROPERTY_RETURN_PROPERTYVALUE)), "Handle SetGetProeprty is Mismatched");

  stage.Remove(actor);

  DaliLog::PrintPass();
}

void HandleSetGetPropertyVector4P()
{
  Handle handleobject;
  Handle handleobject2;
  Property::Index index= 0;
  Property::Type type = Property::VECTOR4;
  Property::Type type2 = Property::NONE ;
  Vector4 vec4SetValue(0.1f,0.2f,0.3f,0.4f),vec4GetValue(0.0f,0.0f,0.0f,0.0f) ;
  Property::Value value(vec4SetValue);
  Property::Value value1;
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::READ_WRITE;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created");
  stage.Add(actor);

  DALI_CHECK_FAIL(!(HandleSetGetProperty(stage,actor,handleobject,index,type,type2,&strName,&vec4SetValue,&vec4GetValue,value,value1,accessMode,SETGETPROPERTY_RETURN_PROPERTYVALUE)), "Handle SetGetProeprty is Mismatched");

  stage.Remove(actor);
  DaliLog::PrintPass();
}

void HandleSetGetPropertyMatrixP()
{
  Handle handleobject;
  Handle handleobject2;
  Property::Index index= 0;
  Property::Type type = Property::MATRIX;
  Property::Type type2 = Property::NONE ;
  float rgfpSetValue[] = {   0.0f,  1.0f,  2.0f,  3.0f,
    4.0f,  5.0f,  6.0f,  7.0f,
    8.0f,  9.0f, 10.0f,  11.0f,
    12.0f, 13.0f, 14.0f,  15.0f },
        rgfpGetValue[] = {   0.0f,  0.0f,  0.0f,  0.0f,
          0.0f,  0.0f,  0.0f,  0.0f,
          0.0f,  0.0f, 0.0f,  0.0f,
          0.0f,  0.0f, 0.0f,  0.0f };

  Matrix mSetValue(rgfpSetValue);
  Matrix mGetValue(rgfpGetValue);
  Property::Value value(mSetValue);
  Property::Value value1;
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::READ_WRITE;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created");
  stage.Add(actor);

  DALI_CHECK_FAIL(!(HandleSetGetProperty(stage,actor,handleobject,index,type,type2,&strName,&mSetValue,&mGetValue,value,value1,accessMode,SETGETPROPERTY_RETURN_PROPERTYVALUE)), "Handle SetGetProeprty is Mismatched");

  stage.Remove(actor);
  DaliLog::PrintPass();
}

void HandleSetGetPropertyMatrix3P()
{
  Handle handleobject;
  Handle handleobject2;
  Property::Index index= 0;
  Property::Type type = Property::MATRIX3;
  Property::Type type2 = Property::NONE ;
  Matrix3 matrix3SetValue( 0.2f,0.3f,0.4f,0.5f,0.1f, 0.6f, 0.7f, 0.8f, 0.9f),
          matrix3GetValue(0.0f,0.0f,0.0f,0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  Property::Value value(matrix3SetValue);
  Property::Value value1;
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::READ_WRITE;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created");
  stage.Add(actor);

  DALI_CHECK_FAIL(!(HandleSetGetProperty(stage,actor,handleobject,index,type,type2,&strName,&matrix3SetValue,&matrix3GetValue,value,value1,accessMode,SETGETPROPERTY_RETURN_PROPERTYVALUE)), " Handle SetGetProeprty is Mismatched");

  stage.Remove(actor);

  DaliLog::PrintPass();
}

void HandleSetGetPropertyRectP()
{
  Handle handleobject;
  Handle handleobject2;
  Property::Index index= 0;
  Property::Type type = Property::RECTANGLE;
  Property::Type type2 = Property::NONE ;
  Rect<int> rectnSetValueue(10 ,20 , 200, 200),rectnGetValueue(0,0,0,0);
  Property::Value value(rectnSetValueue);
  Property::Value value1;
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::READ_WRITE;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created");
  stage.Add(actor);

  DALI_CHECK_FAIL(!(HandleSetGetProperty(stage,actor,handleobject,index,type,type2,&strName,&rectnSetValueue,&rectnGetValueue,value,value1,accessMode,SETGETPROPERTY_RETURN_PROPERTYVALUE)), "Handle SetGetProeprty is Mismatched");

  stage.Remove(actor);

  DaliLog::PrintPass();
}

void HandleSetGetPropertyQuaternionP()
{
  Handle handleobject;
  Handle handleobject2;
  Property::Index index= 0;
  Property::Type type = Property::ROTATION;
  Property::Type type2 = Property::NONE ;
  Quaternion qSetValue(1, 2, 3, 4), qGetValue(0,0,0,0);
  Property::Value value(qSetValue);
  Property::Value value1;
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::READ_WRITE;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created");
  stage.Add(actor);

  DALI_CHECK_FAIL(!(HandleSetGetProperty(stage,actor,handleobject,index,type,type2,&strName,&qSetValue,&qGetValue,value,value1,accessMode,SETGETPROPERTY_RETURN_PROPERTYVALUE)), "Handle SetGetProeprty is Mismatched");

  stage.Remove(actor);

  DaliLog::PrintPass();
}

void HandleSetGetPropertyArrayP()
{
  Handle handleobject;
  Handle handleobject2;
  Property::Index index= 0;
  Property::Type type = Property::ARRAY ;
  Property::Type type2 = Property::NONE ;
  Property::Value value(type);
  Property::Array* anArray = value.GetArray();
  DALI_CHECK_FAIL(!anArray, "anArray is null");

  string  strName = "test-property";
  string strName2 ="a string", strGetvalue ;
  anArray->PushBack( strName2 );
  Property::Value value1;
  Property::AccessMode accessMode = Property::READ_WRITE;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created");
  stage.Add(actor);

  DALI_CHECK_FAIL(!(HandleSetGetProperty(stage,actor,handleobject,index,type,type2,&strName,&strName2,&strGetvalue,value,value1,accessMode,SETGETPROPERTY_RETURN_PROPERTYVALUE)), "Handle SetGetProeprty is Mismatched");
  stage.Remove(actor);

  DaliLog::PrintPass();
}

void HandleSetGetPropertyMapP()
{
  Handle handleobject;
  Handle handleobject2;
  Property::Index index= 0;
  Property::Type type = Property::MAP ;
  Property::Type type2 = Property::NONE ;
  Property::Value value(type);
  Property::Map* anMap = value.GetMap();
  DALI_CHECK_FAIL(!anMap, "anMap is null");

  string  strName = "test-property";
  string  strName2 ="a string", strGetvalue ;

  anMap->Insert("key",strName2);
  Property::Value value1;
  Property::AccessMode accessMode = Property::READ_WRITE;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created");
  stage.Add(actor);

  DALI_CHECK_FAIL(!(HandleSetGetProperty(stage,actor,handleobject,index,type,type2,&strName,&strName2,&strGetvalue,value,value1,accessMode,SETGETPROPERTY_RETURN_PROPERTYVALUE)), "Handle SetGetProeprty is Mismatched ");

  stage.Remove(actor);
  DaliLog::PrintPass();
}

void HandleSetGetPropertyTypeP()
{
  Handle handleobject;
  Handle handleobject2;
  Property::Index index = 0;
  Property::Type type = Property::FLOAT;
  float fSetValue = 123.0f, fGetValue;
  Property::Value value(fSetValue);
  Property::Value value1(0.0f);
  Property::Type type2 = Property::NONE ;
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::READ_WRITE;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created");
  stage.Add(actor);

  DALI_CHECK_FAIL(!(HandleSetGetProperty(stage,actor,handleobject,index,type,type2,&strName,&fSetValue,&fGetValue,value,value1,accessMode,SETGETPROPERTY_RETURN_TYPEVALUE)), "Handle SetGetProeprty is Mismatched");

  stage.Remove(actor);
  DaliLog::PrintPass();
}

void HandleOperatorAssignmentP()
{
  Handle handleobject;
  Handle handleobject2;
  Property::Index index = 0;
  Property::Type type = Property::FLOAT;
  float fSetValue = 123.0f;
  Property::Value value(fSetValue);
  Property::Value value1;
  Property::Type type2;
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::READ_WRITE;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created");
  stage.Add(actor);

  handleobject = actor;
  DALI_CHECK_FAIL(!handleobject, " handleobject is not created");

  index = handleobject.RegisterProperty( strName, value,accessMode);
  DALI_CHECK_FAIL(!handleobject.IsPropertyWritable(index), " Property is not writable");
  DALI_CHECK_FAIL(handleobject.GetPropertyType(index) != type, " Property type did not match");

  handleobject2 = handleobject;

  type2 = handleobject2.GetPropertyType(index);
  DALI_CHECK_FAIL(type2!= type, " Equal Operator does not work");

  stage.Remove(actor);
  DaliLog::PrintPass();
}

void HandleRegisterPropertyFloatWithoutAccessModeP()
{
  int  nFlag = 0;
  Handle handleobject;
  Property::Index index =0;
  float fSetValue = 123.0f;
  Property::Value value(fSetValue);
  string  strName = "test-property";
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITHOUT_ACCESSMODE))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed");
  }

  DALI_CHECK_FAIL( gHandleException || nFlag, "UTcHandleRegisterPropertyFloatWithoutAccessMode is failed");
  gHandleException = false;

  DaliLog::PrintPass();
}

void HandleRegisterPropertyFloatWithAccessModeP()
{
  int  nFlag = 0;
  Handle handleobject;
  Property::Index index =0;
  float fSetValue = 123.0f;
  Property::Value value(fSetValue);
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::ANIMATABLE;
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITH_ACCESSMODE, accessMode))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed");
  }

  DALI_CHECK_FAIL( gHandleException || nFlag, "UTcHandleRegisterPropertyFloatWithAccessMode is failed");
  gHandleException = false;

  DaliLog::PrintPass();
}

void HandleRegisterPropertyboolWithOutAccessModeP()
{
  int nFlag = 0;
  Handle handleobject;
  Property::Index index =0;
  bool  bSetvalue = true;
  Property::Value value(bSetvalue);
  string  strName = "test-property";
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITHOUT_ACCESSMODE))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed");
  }

  DALI_CHECK_FAIL( gHandleException || nFlag, "UTcHandleRegisterPropertyboolWithOutAccessMode is failed");
  gHandleException = false;

  DaliLog::PrintPass();
}

void HandleRegisterPropertyboolWithAccessModeP()
{
  int  nFlag = 0;
  Handle handleobject;
  Property::Index index =0;
  bool  bSetvalue = true;
  Property::Value value(bSetvalue);
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::ANIMATABLE;
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITH_ACCESSMODE, accessMode))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed");
  }

  DALI_CHECK_FAIL( gHandleException || nFlag, "UTcHandleRegisterPropertyboolWithAccessMode is failed");
  gHandleException = false;
  DaliLog::PrintPass();
}

void HandleRegisterPropertyVector2WithoutAccessModeP()
{
  int  nFlag = 0;
  Handle handleobject;
  Property::Index index =0;
  Vector2 vec2GetValue(0.3f,0.4f);
  Property::Value value(vec2GetValue);
  string  strName = "test-property";
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value, REGISTERPROPERTY_WITHOUT_ACCESSMODE))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed");
  }

  DALI_CHECK_FAIL( gHandleException || nFlag, "UTcHandleRegisterPropertyVector2WithoutAccessMode is failed");
  gHandleException = false;
  DaliLog::PrintPass();
}

void HandleRegisterPropertyVector2WithAccessModeP()
{
  int nFlag = 0 ;
  Handle handleobject;
  Property::Index index =0;
  Vector2 vec2GetValue(0.3f,0.4f);
  Property::Value value(vec2GetValue);
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::ANIMATABLE;
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITH_ACCESSMODE,accessMode))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed");
  }

  DALI_CHECK_FAIL( gHandleException || nFlag , "UTcHandleRegisterPropertyVector2WithAccessMode is failed");
  gHandleException = false;
  DaliLog::PrintPass();
}

void HandleRegisterPropertyVector3WithOutAccessModeP()
{
  int nFlag = 0 ;
  Handle handleobject;
  Property::Index index =0;
  Vector3 vec3GetValue(0.1f,0.2f,0.3f);
  Property::Value value(vec3GetValue);
  string  strName = "test-property";
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITHOUT_ACCESSMODE))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed ");
  }

  DALI_CHECK_FAIL( gHandleException || nFlag , "UTcHandleRegisterPropertyVector3WithOutAccessMode is failed ");
  gHandleException = false;
  DaliLog::PrintPass();
}

void HandleRegisterPropertyVector3WithAccessModeP()
{
  int nFlag = 0;
  Handle handleobject;
  Property::Index index =0;
  Vector3 vec3GetValue(0.1f,0.2f,0.3f);
  Property::Value value(vec3GetValue);
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::ANIMATABLE;
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITH_ACCESSMODE,accessMode))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed");
  }

  DALI_CHECK_FAIL( gHandleException || nFlag , "UTcHandleRegisterPropertyVector3WithAccessMode is failed");
  gHandleException = false;
  DaliLog::PrintPass();
}

void HandleRegisterPropertyVector4WithOutAccessmodeP()
{
  int nFlag = 0;
  Handle handleobject;
  Property::Index index =0;
  Vector4 vec4GetValue(0.1f,0.2f,0.3f,0.4f);
  Property::Value value(vec4GetValue);
  string  strName = "test-property";
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITHOUT_ACCESSMODE))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed ");
  }

  DALI_CHECK_FAIL( gHandleException || nFlag , "UTcHandleRegisterPropertyVector4WithOutAccessmode is failed ");
  gHandleException = false;
  DaliLog::PrintPass();
}

void HandleRegisterPropertyVector4WithAccessmodeP()
{
  int nFlag = 0 ;
  Handle handleobject;
  Property::Index index =0;
  Vector4 vec4GetValue(0.1f,0.2f,0.3f,0.4f);
  Property::Value value(vec4GetValue);
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::ANIMATABLE;
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITH_ACCESSMODE, accessMode))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed ");
  }

  DALI_CHECK_FAIL( gHandleException || nFlag , "UTcHandleRegisterPropertyVector4WithAccessmode is failed ");
  gHandleException = false;
  DaliLog::PrintPass();
}

void HandleRegisterPropertyMatrix3WithoutAccessModeP()
{
  int  nFlag = 0 ;
  Handle handleobject;
  Property::Index index =0;
  Matrix3 matrix3GetValue( 0.2f,0.3f,0.4f,0.5f,0.1f, 0.6f, 0.7f, 0.8f, 0.9f);
  Property::Value value(matrix3GetValue);
  string  strName = "test-property";
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITHOUT_ACCESSMODE))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed");
  }

  DALI_CHECK_FAIL( gHandleException || nFlag , "UTcHandleRegisterPropertyMatrix3WithoutAccessMode is failed");
  gHandleException = false;
  DaliLog::PrintPass();
}

void HandleRegisterPropertyMatrix3WithAccessModeP()
{
  int nFlag = 0;
  Handle handleobject;
  Property::Index index =0;
  Matrix3 matrix3GetValue( 0.2f,0.3f,0.4f,0.5f,0.1f, 0.6f, 0.7f, 0.8f, 0.9f);
  Property::Value value(matrix3GetValue);
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::ANIMATABLE;
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");


  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITH_ACCESSMODE,accessMode))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed ");
  }

  DALI_CHECK_FAIL( gHandleException || nFlag ,"UTcHandleRegisterPropertyMatrix3WithAccessMode is failed ");
  gHandleException = false;

  DaliLog::PrintPass();
}

void HandleRegisterPropertyMatrixWithoutAccessModeP()
{
  int nFlag = 0;
  Handle handleobject;
  Property::Index index =0;
  float rgfpSetValue[] = {  0.0f,  1.0f,  2.0f,  3.0f,
    4.0f,  5.0f,  6.0f,  7.0f,
    8.0f,  9.0f, 10.0f,  11.0f,
    12.0f, 13.0f, 14.0f,  15.0f };

  Matrix mSetValue(rgfpSetValue);
  Property::Value value(mSetValue);
  string  strName = "test-property";
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITHOUT_ACCESSMODE))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed ");
  }

  DALI_CHECK_FAIL( gHandleException || nFlag , "UTcHandleRegisterPropertyMatrixWithoutAccessMode is failed ");
  gHandleException = false;
  DaliLog::PrintPass();
}

void HandleRegisterPropertyMatrixWithAccessModeP()
{
  int nFlag = 0;
  Handle handleobject;
  Property::Index index =0;
  float rgfpSetValue[] = {   0.0f,  1.0f,  2.0f,  3.0f,
    4.0f,  5.0f,  6.0f,  7.0f,
    8.0f,  9.0f, 10.0f,  11.0f,
    12.0f, 13.0f, 14.0f,  15.0f };

  Matrix mSetValue(rgfpSetValue);
  Property::Value value(mSetValue);
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::ANIMATABLE;
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITH_ACCESSMODE,accessMode))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed ");
  }

  DALI_CHECK_FAIL( gHandleException || nFlag , "UTcHandleRegisterPropertyMatrixWithAccessMode is failed ");

  gHandleException = false;
  DaliLog::PrintPass();
}

void HandleRegisterPropertyStringWithoutAccessModeP()
{
  int nFlag = 0;
  Handle handleobject;
  Property::Index index =0;
  char* pszSetValue= (char*)"SetValue";
  Property::Value value(pszSetValue);
  string  strName = "test-property";
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITHOUT_ACCESSMODE))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed");
  }

  DALI_CHECK_FAIL(!gHandleException || nFlag, "UTcHandleRegisterPropertyStringWithoutAccessMode is failed");
  gHandleException = false;
  DaliLog::PrintPass();
}

void HandleRegisterPropertyStringWithAccessModeP()
{
  int nFlag = 0;
  Handle handleobject;
  Property::Index index =0;
  char* pszSetValue= (char*)"SetValue";
  Property::Value value(pszSetValue);
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::ANIMATABLE;
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");


  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITH_ACCESSMODE,accessMode))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed");
  }

  DALI_CHECK_FAIL(!gHandleException || nFlag , "UTcHandleRegisterPropertyStringWithAccessMode is failed");
  gHandleException = false;

  DaliLog::PrintPass();
}

void HandleRegisterPropertyQuaternionWithoutAccessModeP()
{
  int nFlag = 0;
  Handle handleobject;
  Property::Index index =0;
  Quaternion qSetValue(1, 2, 3, 4);
  Property::Value value(qSetValue);
  string  strName = "test-property";
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITHOUT_ACCESSMODE))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed");
  }

  DALI_CHECK_FAIL( gHandleException || nFlag, "UTcHandleRegisterPropertyQuaternionWithoutAccessMode is failed");
  gHandleException = false;
  DaliLog::PrintPass();
}

void HandleRegisterPropertyQuaternionWithAccessModeP()
{
  int nFlag = 0;
  Handle handleobject;
  Property::Index index = 0;
  Quaternion qSetValue(1, 2, 3, 4);
  Property::Value value(qSetValue);
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::ANIMATABLE;
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITH_ACCESSMODE,accessMode))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed ");
  }

  DALI_CHECK_FAIL( gHandleException || nFlag , "UTcHandleRegisterPropertyQuaternionWithAccessMode is failed ");
  gHandleException = false;
  DaliLog::PrintPass();
}

void HandleRegisterPropertyRectWithoutAccessModeP()
{
  int  nFlag = 0;
  Handle handleobject;
  Property::Index index =0;
  Rect<int> rectnSetValueue(10 ,20 , 200, 200);
  Property::Value value(rectnSetValueue);
  string  strName = "test-property";
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITHOUT_ACCESSMODE))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed ");
  }

  DALI_CHECK_FAIL(!gHandleException || nFlag, "UTcHandleRegisterPropertyRectWithoutAccessMode is failed ");
  gHandleException = false;
  DaliLog::PrintPass();
}

void HandleRegisterPropertyRectWithAccessModeP()
{
  int nFlag = 0;
  Handle handleobject;
  Property::Index index =0;
  Rect<int> rectnSetValueue(10 ,20 , 200, 200);
  Property::Value value(rectnSetValueue);
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::ANIMATABLE;
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITH_ACCESSMODE,accessMode))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed ");
  }

  DALI_CHECK_FAIL(!gHandleException || nFlag , "UTcHandleRegisterPropertyRectWithAccessMode is failed ");
  gHandleException = false;
  DaliLog::PrintPass();
}

void HandleRegisterPropertyMapWithAccessModeP()
{
  int nFlag = 0;
  Handle handleobject;
  Property::Index index = 0;
  Property::Value value(Property::MAP);
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::ANIMATABLE;
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value, REGISTERPROPERTY_WITH_ACCESSMODE,accessMode))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed");
  }

  DALI_CHECK_FAIL(!gHandleException || nFlag, "UTcHandleRegisterPropertyMapWithAccessMode is failed");
  gHandleException = false;
  DaliLog::PrintPass();
}

void HandleRegisterPropertyMapWithoutAccessModeP()
{
  int nFlag = 0;
  Handle handleobject;
  Property::Index index =0;
  Property::Value value(Property::MAP);
  string  strName = "test-property";
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITHOUT_ACCESSMODE))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed ");
  }

  DALI_CHECK_FAIL(!gHandleException || nFlag, "UTcHandleRegisterPropertyMapWithoutAccessMode is failed ");
  gHandleException = false;

  DaliLog::PrintPass();
}

void HandleRegisterPropertyArrayWithoutAccessModeP()
{
  int nFlag = 0;
  Handle handleobject;
  Property::Index index =0;
  Property::Value value(Property::ARRAY);
  string  strName = "test-property";
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value,REGISTERPROPERTY_WITHOUT_ACCESSMODE))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed ");
  }

  DALI_CHECK_FAIL(!gHandleException || nFlag, "UTcHandleRegisterPropertyArrayWithoutAccessMode is failed ");
  gHandleException = false;
  DaliLog::PrintPass();
}

void HandleRegisterPropertyArrayWithAccessModeP()
{
  int nFlag = 0;
  Handle handleobject;
  Property::Index index =0;
  Property::Value value(Property::ARRAY);
  string  strName = "test-property";
  Property::AccessMode accessMode = Property::ANIMATABLE;
  Actor actor;

  Stage stage= Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created");

  if(!HandleRegisterProperty(stage, actor, handleobject, index, &strName, value, REGISTERPROPERTY_WITH_ACCESSMODE,accessMode))
  {
    nFlag = 1;
    LOG_E("HandleRegisterProperty is failed");
  }

  DALI_CHECK_FAIL(!gHandleException || nFlag, "UTcHandleRegisterPropertyArrayWithAccessMode is failed");
  gHandleException = false;
  DaliLog::PrintPass();
}

void HandleRemoveConstraintsWithAndWithoutTagP()
{
  gActorHandle = Actor::New();
  DALI_CHECK_FAIL( !gActorHandle , "Actor::New() is failed.");

  Constraint constraintScale, constraintPositionX, constraintPositionY;
  Constraint constraintOrientation, constraintColor;

  /*** Setting starting properties of actor ***/
  gActorHandle.SetScale( HANDLE_START_SCALE );
  gActorHandle.SetPosition( HANDLE_START_X, HANDLE_START_Y );
  gActorHandle.SetColor ( HANDLE_START_COLOR );
  gActorHandle.SetOrientation( HANDLE_QUAT_START );
  Stage::GetCurrent().Add(gActorHandle);

  gHandle = gActorHandle;
  DALI_CHECK_FAIL( !gHandle , "Handle instance is empty.");

  /*** Setting constraint for actor's SCALE with tag ***/
  constraintScale = Constraint::New<Vector3>( gHandle, Actor::Property::SCALE, STHandleConstraintValues() );
  DALI_CHECK_FAIL( !constraintScale , "Constraint::New() is failed for actor's SCALE.");

  constraintScale.SetTag( HANDLE_TAG_SCALE );
  DALI_CHECK_FAIL( constraintScale.GetTag() != HANDLE_TAG_SCALE , "GetTag value is not matched with SetTag value for constraintScale.");

  /*** Setting constraint for actor's  POSITION_X with tag ***/
  constraintPositionX = Constraint::New< float >( gHandle, Actor::Property::POSITION_X, STHandleConstraintValues() );
  DALI_CHECK_FAIL(!constraintPositionX, "Constraint::New() is failed for POSITION_X.");

  constraintPositionX.SetTag( HANDLE_TAG_POSITION );
  DALI_CHECK_FAIL( constraintPositionX.GetTag() != HANDLE_TAG_POSITION , "GetTag value is not matched with SetTag value for constraintPositionX.");

  /*** Setting constraint for actor's  POSITION_Y with tag; both POSITION_X and POSITION_Y have same tag ***/
  constraintPositionY = Constraint::New< float >( gHandle, Actor::Property::POSITION_Y, STHandleConstraintValues() );
  DALI_CHECK_FAIL(!constraintPositionY, "Constraint::New() is failed for POSITION_Y.");

  constraintPositionY.SetTag( HANDLE_TAG_POSITION );
  DALI_CHECK_FAIL( constraintPositionY.GetTag() != HANDLE_TAG_POSITION , "GetTag value is not matched with SetTag value for constraintPositionY.");

  /*** Setting constraint for actor's ORIENTATION (no tag) ***/
  constraintOrientation = Constraint::New< Quaternion >( gHandle, Actor::Property::ORIENTATION, STHandleConstraintValues() );
  DALI_CHECK_FAIL(!constraintOrientation, "Constraint::New() is failed for actor's ORIENTATION.");

  /*** Setting constraint for actor's COLOR (no tag) ***/
  constraintColor = Constraint::New< Vector4 >( gHandle, Actor::Property::COLOR, STHandleConstraintValues() );
  DALI_CHECK_FAIL(!constraintColor, "Constraint::New() is failed for actor's COLOR.");

  /*** Applying constraint on actor's SCALE, POSITION_X, POSITION_Y, ORIENTATION, and COLOR ***/
  constraintScale.Apply();
  constraintPositionX.Apply();
  constraintPositionY.Apply();
  constraintOrientation.Apply();
  constraintColor.Apply();
}
void VTHandleRemoveConstraintsWithAndWithoutTag001()
{
  /*** Try to set another value to actor's SCALE, POSITION_X, POSITION_Y, ORIENTATION, and COLOR ***/
  gActorHandle.SetScale( HANDLE_SET_SCALE );
  gActorHandle.SetPosition( HANDLE_SET_X, HANDLE_SET_Y );
  gActorHandle.SetOrientation( HANDLE_QUAT_SET );
  gActorHandle.SetColor( HANDLE_SET_COLOR );
}
void VTHandleRemoveConstraintsWithAndWithoutTag002()
{
  /*** Values should not be set due to constaint application ***/
  bool bApplyConstraintCheck = HandleConstraintValueCheck< Vector3 >( gActorHandle, HANDLE_START_SCALE, HANDLE_SET_SCALE, Actor::Property::SCALE, HANDLE_TARGET_VECTOR3 );
  DALI_CHECK_FAIL( !bApplyConstraintCheck , "Constraint is not applied on actor's SCALE.");

  bApplyConstraintCheck = false;
  bApplyConstraintCheck = HandleConstraintValueCheckSizePosition< float >( gActorHandle, HANDLE_START_X, HANDLE_SET_X, Actor::Property::POSITION_X, HANDLE_TARGET_FLOAT );
  DALI_CHECK_FAIL( !bApplyConstraintCheck , "Constraint is not applied on actor's POSITION_X.");

  bApplyConstraintCheck = false;
  bApplyConstraintCheck = HandleConstraintValueCheckSizePosition< float >( gActorHandle, HANDLE_START_Y, HANDLE_SET_Y, Actor::Property::POSITION_Y, HANDLE_TARGET_FLOAT );
  DALI_CHECK_FAIL( !bApplyConstraintCheck , "Constraint is not applied on actor's POSITION_Y.");

  bApplyConstraintCheck = false;
  bApplyConstraintCheck = HandleConstraintValueCheck< Quaternion >( gActorHandle, HANDLE_QUAT_START, HANDLE_QUAT_SET, Actor::Property::ORIENTATION, HANDLE_TARGET_QUATERNION );
  DALI_CHECK_FAIL( !bApplyConstraintCheck , "Constraint is not applied on actor's ORIENTATION.");

  bApplyConstraintCheck = false;
  bApplyConstraintCheck = HandleConstraintValueCheck< Vector4 >( gActorHandle, HANDLE_START_COLOR, HANDLE_SET_COLOR, Actor::Property::COLOR, HANDLE_TARGET_COLOR );
  DALI_CHECK_FAIL( !bApplyConstraintCheck , "Constraint is not applied on actor's COLOR.");

  /*** Now remove constraint from SCALE with its matching tag and another value will be set on it***/
  gHandle.RemoveConstraints( HANDLE_TAG_SCALE );

  gActorHandle.SetScale( HANDLE_SET_SCALE );
}
void VTHandleRemoveConstraintsWithAndWithoutTag003()
{
  DALI_CHECK_FAIL( gActorHandle.GetCurrentScale() != HANDLE_SET_SCALE , "Handle::RemoveConstraints(unsinged int tag) is failed to remove activeConstraint for actor's Scale with its matching tag.");

  /*** Try to set other values to POSITION_X, POSITION_Y, ORIENTATION and COLOR, constraints on them will not let new values set on them***/
  gActorHandle.SetPosition( HANDLE_SET_X, HANDLE_SET_X );
  gActorHandle.SetColor ( HANDLE_SET_COLOR );
  gActorHandle.SetOrientation( HANDLE_QUAT_SET );
}
void VTHandleRemoveConstraintsWithAndWithoutTag004()
{
  DALI_CHECK_FAIL( gActorHandle.GetCurrentPosition().x == HANDLE_SET_X , "Constraint on Actor's POSITION_X should not be removed before calling RemoveConstraints with its matching tag.");
  DALI_CHECK_FAIL( gActorHandle.GetCurrentPosition().y == HANDLE_SET_Y , "Constraint on Actor's POSITION_Y should not be removed before calling RemoveConstraints with its matching tag.");
  DALI_CHECK_FAIL( gActorHandle.GetCurrentColor() == HANDLE_SET_COLOR , "Constraint on Actor's COLOR should not be removed before calling RemoveConstraints without any tag.");
  DALI_CHECK_FAIL( gActorHandle.GetCurrentOrientation() == HANDLE_QUAT_SET , "Constraint on Actor's ORIENTATION should not be removed before calling RemoveConstraints without any tag.");

  /*** Now remove constraint from POSITION_X and POSITION_Y together with their matching tag and news values will be set on them***/
  gHandle.RemoveConstraints( HANDLE_TAG_POSITION );

  gActorHandle.SetPosition( HANDLE_SET_X, HANDLE_SET_X );
}
void VTHandleRemoveConstraintsWithAndWithoutTag005()
{
  DALI_CHECK_FAIL( gActorHandle.GetCurrentPosition().x != HANDLE_SET_X , "Handle::RemoveConstraints(unsinged int tag) is failed to remove activeConstraint on actor's POSITION_X with its matching tag.");
  DALI_CHECK_FAIL( gActorHandle.GetCurrentPosition().y != HANDLE_SET_Y , "Handle::RemoveConstraints(unsinged int tag) is failed to remove activeConstraint on actor's POSITION_Y with its matching tag.");

  /*** Again, try to set other values to ORIENTATION and COLOR, constraints on them are still applied***/
  gActorHandle.SetColor ( HANDLE_SET_COLOR );
  gActorHandle.SetOrientation( HANDLE_QUAT_SET );
}
void VTHandleRemoveConstraintsWithAndWithoutTag006()
{
  DALI_CHECK_FAIL( gActorHandle.GetCurrentColor() == HANDLE_SET_COLOR , "Constraint on Actor's COLOR should be applied untill RemoveConstraints without any tag is called.");
  DALI_CHECK_FAIL( gActorHandle.GetCurrentOrientation() == HANDLE_QUAT_SET , "Constraint on Actor's ORIENTATION should be applied untill RemoveConstraints without any tag is called.");

  /*** Now call  RemoveConstraints() without any tag, it will remove all the remaining constraints applied on actor's properties***/
  gHandle.RemoveConstraints();

  gActorHandle.SetColor ( HANDLE_SET_COLOR );
  gActorHandle.SetOrientation( HANDLE_QUAT_SET );
}
void VTHandleRemoveConstraintsWithAndWithoutTag007()
{
  DALI_CHECK_FAIL( gActorHandle.GetCurrentColor() != HANDLE_SET_COLOR , "Handle::RemoveConstraints() is failed to remove constraint from actor's COLOR.");
  DALI_CHECK_FAIL( gActorHandle.GetCurrentOrientation() != HANDLE_QUAT_SET , "Handle::RemoveConstraints() is failed to remove constraint from actor's ORIENTATION.");

  Stage::GetCurrent().Remove( gActorHandle );

  DaliLog::PrintPass();
}



void HandleNewWeightObjectDownCastP()
{
  unsigned int uHandlePropertyCount = 0u, uWeightObjectPropertyCount = 0u;
  Property::Index indexWeight = WeightObject::WEIGHT;
  const string STR_PROPERTY_NAME = "weight";

  Handle handle = Handle::New();
  DALI_CHECK_INSTANCE( handle, "Handle::New() is failed." );

  uHandlePropertyCount = handle.GetPropertyCount();

  Handle handleWeightObject = WeightObject::New();
  DALI_CHECK_INSTANCE( handleWeightObject, "WeightObject::New() is failed." );

  uWeightObjectPropertyCount = handleWeightObject.GetPropertyCount();

  DALI_CHECK_FAIL( uWeightObjectPropertyCount <= uHandlePropertyCount, "WeightObject does not have any property." );

  Property::Index indexWeightGet = handleWeightObject.GetPropertyIndex( STR_PROPERTY_NAME );
  DALI_CHECK_FAIL( (indexWeightGet ==  Property::INVALID_INDEX) || (indexWeightGet != indexWeight), "WeightObject does not have any custom property named weight." );

  BaseHandle baseHandle( handleWeightObject );
  handle = Handle::DownCast( baseHandle );

  DALI_CHECK_FAIL( handle != handleWeightObject, "Handle::DownCast is failed to downcast weight object to handle." );

  uHandlePropertyCount = handle.GetPropertyCount();
  DALI_CHECK_FAIL( uWeightObjectPropertyCount != uHandlePropertyCount, "Property count mismatches after downcast." );

  Property::Index indexDownCasted = handle.GetPropertyIndex( STR_PROPERTY_NAME );
  DALI_CHECK_FAIL( (indexDownCasted ==  Property::INVALID_INDEX) || (indexDownCasted != indexWeight), "Custom weight property is not found in handle object after downcast." );

  DaliLog::PrintPass();
}

void HandleDownCastN()
{
  // A DownCast on an empty handle will fail
  Handle empty;
  Handle customHandle2 = Handle::DownCast( empty );
  DALI_CHECK_FAIL( customHandle2 , "Handle::DownCast is failed to downcast weight object to handle." );
  DaliLog::PrintPass();
}


void HandleRemovePropertyNotificationsP()
{
  gActorHandle = Actor::New();
  DALI_CHECK_INSTANCE( gActorHandle, "Actor::New() is failed" );

  Stage::GetCurrent().Add( gActorHandle );

  gHandle = gActorHandle;
  DALI_CHECK_INSTANCE( gHandle, "Handle is not initialized" );

  /**Setting property notification for Position X and connect it to NotifySignal. **/
  PropertyCondition conditionForPosX = GreaterThanCondition( F_CONDITION );
  PropertyNotification::NotifyMode notifyModePosX  = PropertyNotification::NotifyOnTrue;
  PropertyNotification notificationPosX = gHandle.AddPropertyNotification(Actor::Property::POSITION_X, conditionForPosX);
  DALI_CHECK_FAIL(!notificationPosX, "Handle::AddPropertyNotification(index, condition) is failed for POSITION_X.");

  notificationPosX.NotifySignal().Connect( &HandleTestCallback );
  notificationPosX.SetNotifyMode( notifyModePosX );

  gActorHandle.SetX( F_VAL_ZERO );
}
void VTHandleRemovePropertyNotifications001()
{
  gHandleCallBackCalled = false;
  /**Setting Position X from zero to another value, Notification will be triggered. **/
  gActorHandle.SetX( F_VAL_X );
}
void VTHandleRemovePropertyNotifications002()
{
  DALI_CHECK_FAIL( !gHandleCallBackCalled , "Notification is not Triggered after adding Property Notification for POSITION_X");

  /**Setting property notification for Position Y and connect it to NotifySignal. **/
  PropertyCondition conditionForPosY = LessThanCondition( F_CONDITION );
  PropertyNotification::NotifyMode notifyModePosY = PropertyNotification::NotifyOnFalse;
  PropertyNotification notificationPosY = gHandle.AddPropertyNotification(Actor::Property::POSITION_Y, conditionForPosY);
  DALI_CHECK_FAIL(!notificationPosY, "Handle::AddPropertyNotification(index, condition) is failed for POSITION_Y.");

  notificationPosY.NotifySignal().Connect( &HandleTestCallback );
  notificationPosY.SetNotifyMode( notifyModePosY );
  gActorHandle.SetY( F_VAL_ZERO );
}
void VTHandleRemovePropertyNotifications003()
{
  gHandleCallBackCalled = false;
  /**Setting Position Y from zero to another value, Notification will be triggered. **/
  gActorHandle.SetY( F_VAL_Y );
}
void VTHandleRemovePropertyNotifications004()
{
  DALI_CHECK_FAIL( !gHandleCallBackCalled , "Notification is not Triggered after adding Property Notification for POSITION_Y");

  /**Setting property notification for Position Z and connect it to NotifySignal. **/
  PropertyCondition conditionForPosZ = InsideCondition( F_MIN, F_MAX );
  PropertyNotification::NotifyMode notifyModePosZ  = PropertyNotification::NotifyOnChanged;
  PropertyNotification notificationPosZ = gHandle.AddPropertyNotification(Actor::Property::POSITION_Z, conditionForPosZ);
  DALI_CHECK_FAIL(!notificationPosZ, "Handle::AddPropertyNotification(index, condition) is failed for POSITION_Z.");

  notificationPosZ.NotifySignal().Connect( &HandleTestCallback );
  notificationPosZ.SetNotifyMode( notifyModePosZ );
  gActorHandle.SetZ( F_VAL_ZERO );
}
void VTHandleRemovePropertyNotifications005()
{
  gHandleCallBackCalled = false;
  /**Setting Position Z from zero to another value, check Notification will be triggered. **/
  gActorHandle.SetZ( F_VAL_Z );

}
void VTHandleRemovePropertyNotifications006()
{
  DALI_CHECK_FAIL( !gHandleCallBackCalled , "Notification is not Triggered after adding Property Notification for POSITION_Z");

  /**Now, removing all the notifications from handle, notification will not be triggerred while setting Position X, Y, Z. **/
  gHandle.RemovePropertyNotifications();
  gActorHandle.SetX( F_VAL_ZERO );
  gActorHandle.SetY( F_VAL_ZERO );
  gActorHandle.SetZ( F_VAL_ZERO );
}
void VTHandleRemovePropertyNotifications007()
{
  gHandleCallBackCalled = false;
  /**Again, setting Position X from zero to another value, Notification will not be triggered. **/
  gActorHandle.SetX( F_VAL_X );
}
void VTHandleRemovePropertyNotifications008()
{
  DALI_CHECK_FAIL( gHandleCallBackCalled , "Notification is Triggered for POSITION_X after removing all notifications.");
  /**Again, setting Position Y from zero to another value, Notification will not be triggered. **/
  gActorHandle.SetY( F_VAL_Y );
}
void VTHandleRemovePropertyNotifications009()
{
  DALI_CHECK_FAIL( gHandleCallBackCalled , "Notification is Triggered for POSITION_Y after removing all notifications.");
  /**Again, setting Position Z from zero to another value, Notification will not be triggered. **/
  gActorHandle.SetZ( F_VAL_Z );
}
void VTHandleRemovePropertyNotifications010()
{
  DALI_CHECK_FAIL( gHandleCallBackCalled , "Notification is Triggered for POSITION_Z after removing all notifications.");
  Stage::GetCurrent().Remove( gActorHandle );
  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

