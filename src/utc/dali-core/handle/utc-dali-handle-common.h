#ifndef _UTC_DALI_HANDLE_COMMON_H_
#define _UTC_DALI_HANDLE_COMMON_H_

#include "dali-common.h"

using namespace std;
using namespace Dali;

#define SUITE_NAME  "HANDLE_UTC"
#define F_VAL_ZERO  0.0f
#define F_VAL_X  400.0f
#define F_VAL_Y  250.0f
#define F_VAL_Z  100.0f
#define F_CONDITION  200.0f
#define F_MIN  50.0f
#define F_MAX  150.0f

/*****Setting Constant Values to be used while applying constraint********************/
const Quaternion HANDLE_TARGET_QUATERNION = Quaternion(Radian(1.2f), Vector3::XAXIS);
const Vector3 HANDLE_TARGET_VECTOR3 = Vector3( 15.0f, 15.0f, 15.0f );
const Vector4 HANDLE_TARGET_COLOR   = Color::RED;
const float HANDLE_TARGET_FLOAT     = 123.45f;

/*** Setting values of properties***/
const float HANDLE_START_X = 1.0f, HANDLE_START_Y = 1.0f;
const float HANDLE_SET_X = 23.58f, HANDLE_SET_Y = 23.58f;
const Vector3 HANDLE_START_SCALE = Vector3(1.0f, 1.0f, 1.0f);
const Vector3 HANDLE_SET_SCALE = Vector3(2.7f, 2.7f, 2.7f);
const Vector4 HANDLE_START_COLOR = Color::WHITE, HANDLE_SET_COLOR = Color::BLUE;
const Quaternion HANDLE_QUAT_START( Radian( 0.5f ), Vector3::YAXIS), HANDLE_QUAT_SET( Radian( 0.8f ), Vector3::ZAXIS );

/*** Setting tags and check for constraint status ***/
const unsigned int HANDLE_TAG_SCALE = 21u, HANDLE_TAG_POSITION = 31u;

/*** Functor Structure to call to set the constrained property value********************************/

struct STHandleConstraintValues
{
  void operator()( Vector3& vec3Current, const PropertyInputContainer& propertyContainer )
  {
    if(propertyContainer.Size() > 0) // This will work if constraint source is added
    {
      vec3Current = propertyContainer[0]->GetVector3();
    }
    else
    {
      vec3Current = HANDLE_TARGET_VECTOR3;
    }
  }

  void operator()( float& fCurrent, const PropertyInputContainer& propertyContainer )
  {
    if(propertyContainer.Size() > 0) // This will work if constraint source is added
    {
      fCurrent = propertyContainer[0]->GetFloat();
    }
    else
    {
      fCurrent = HANDLE_TARGET_FLOAT;
    }
  }

  void operator()( Vector4& vec4Current, const PropertyInputContainer& propertyContainer )
  {
    if(propertyContainer.Size() > 0) // This will work if constraint source is added
    {
      vec4Current = propertyContainer[0]->GetVector4();
    }
    else
    {
      vec4Current = HANDLE_TARGET_COLOR;
    }
  }

  void operator()( Quaternion& quatCurrent, const PropertyInputContainer& propertyContainer )
  {
    if(propertyContainer.Size() > 0) // This will work if constraint source is added
    {
      quatCurrent = propertyContainer[0]->GetQuaternion();
    }
    else
    {
      quatCurrent = HANDLE_TARGET_QUATERNION;
    }
  }
};

/***************************End of Functor Structure Definition*********************************/



enum HandleRegisterPropertyOption
{
  REGISTERPROPERTY_WITH_ACCESSMODE,
  REGISTERPROPERTY_WITHOUT_ACCESSMODE
};

enum HandleSetGetPropertyOption
{
  SETGETPROPERTY_RETURN_PROPERTYVALUE,
  SETGETPROPERTY_RETURN_TYPEVALUE
};

/**Global variable declaration*/
extern bool gHandleException;

bool HandleAddActor(Actor& actor, Stage& stage);

/**Test for varrying the input parameter **/
bool HandleRegisterProperty(Stage stage, Actor actor, Handle handleobject, Property::Index index, string *pstrName,Property::Value value, HandleRegisterPropertyOption RegisterPropertyOption, Property::AccessMode accessMode = Property::READ_WRITE);

/**
 * @function     HandleSetGetProperty
 * @description  Test for varrying the input parameter
 * @param[in]    stage [Handle to the Stage]
 * @param[in]    actor [Handle to the Actor]
 * @param[in]    handleobject [Handle to the HandleOBJECT]
 * @param[in]    index [Handle to the  Property::Index]
 * @param[in]    type,type2  [Handle to the  Property::TYPE]
 * @param[in]    value,value1 [Handle to the Property::Value]
 * @param[in]    pstrName[string]
 * @param[in]    *GetValue, *SetValue [VariableType value]
 * @param[in]    SetGetPropertyOption [HandleSetGetPropertyOption enum ]
 * @param[in]    accessMode [Handle to Property::AccessMode]
 * @returnbool   true/false
 */
template <typename VariableType> bool HandleSetGetProperty(Stage &stage,Actor &actor,Handle handleobject, Property::Index index,Property::Type type,Property::Type type2, string *pstrName,VariableType *SetValue,VariableType *GetValue,Property::Value value,Property::Value value1, Property::AccessMode accessMode,  HandleSetGetPropertyOption SetGetPropertyOption)
{

  handleobject = actor;
  DALI_CHECK_FALSE(!handleobject, "handleobject is not created");

  index = handleobject.RegisterProperty( *pstrName, value,accessMode);
  DALI_CHECK_FALSE(!handleobject.IsPropertyWritable(index), "Property is not writable");
  DALI_CHECK_FALSE(handleobject.GetPropertyType(index) != type, "Property type did not match ");

  handleobject.SetProperty(index, value);

  if(SetGetPropertyOption == SETGETPROPERTY_RETURN_PROPERTYVALUE)
  {
    value1 = handleobject.GetProperty(index);
    if(value1.GetType() != value.GetType() )
    {
      return false;
    }
  }
  else
  {
    type2 = handleobject.GetPropertyType(index);
    DALI_CHECK_FALSE(value.GetType()!= type2 , "Property type did not match  ");

    *GetValue = handleobject.GetProperty<VariableType>(index);

    if(*GetValue != (*SetValue) )
    {
      return false;
    }
  }

  return true;
}

//Helper for checking values of actor's property due to constraint application

/**
 * @function     HandleConstraintValueCheck
 * @description  Checks values of actor's property due to constraint application
 * @parameter
 *        [IN]   actor[ Actor instance ]
 *        [IN]   tStart[ Starting property ]
 *        [IN]   tSet[ Property to set ]
 *        [IN]   indexProperty[ Property::Index instance ]
 *        [IN]   tConst[ Property set by constraint ]
 *        [OUT]  NA
 * @return       bool - false: if actor's property is matched to it's starting value or set value or not matched to the value set by constraint
 *                    - true: if actor's property is not matched to it's starting value and set value, and matched to the value set by constraint
 */

  template< class T >
bool HandleConstraintValueCheck( Actor actor, T tStart, T tSet, Property::Index indexProperty, T tConstraintValue )
{
  DALI_CHECK_FALSE( actor.GetCurrentProperty< T >( indexProperty ) == tStart , "Actor's property should not be matched to its starting value after applying constraint.");

  DALI_CHECK_FALSE( actor.GetCurrentProperty< T >( indexProperty ) == tSet , "No other value should be set after applying constraint.");

  DALI_CHECK_FALSE( actor.GetCurrentProperty< T >( indexProperty ) != tConstraintValue , "Actor's proprty is not matched to the expected value set by constraint.");
  return true;
}

/**
 * @remarks SIZE and POSITION are the only properties to return target value.
 */
  template< class T >
bool HandleConstraintValueCheckSizePosition( Actor actor, T tStart, T tSet, Property::Index indexProperty, T tConstraintValue )
{
  DALI_CHECK_FALSE( actor.GetCurrentProperty< T >( indexProperty ) == tStart , "Actor's property should not be matched to its starting value after applying constraint.");

  DALI_CHECK_FALSE( actor.GetCurrentProperty< T >( indexProperty ) == tSet , "No other value should be set after applying constraint.");

  DALI_CHECK_FALSE( actor.GetCurrentProperty< T >( indexProperty ) != tConstraintValue , "Actor's proprty is not matched to the expected value set by constraint.");
  return true;
}

#endif  //_UTC_DALI_HANDLE_COMMON_H_
