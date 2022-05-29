#include "utc-dali-key-frames-common.h"

/**
 * @function     KeyFramesWithDiffPropValue
 * @description  Test for overloded Value for Add Api
 * @param[in]    keyFrames[A keyFrames  object instance ]
 * @param[in]    testValue[the value to set]
 * @param[out]   application [Application instance]
 * @param[out]   keyFrames[KeyFarmes instance]
 * @param[out]   value[Property value]
 *
 * @return       bool - true if all the conditions Executed Properly
 *                    - false if all the conditions can not execute properly
 */
bool KeyFramesWithDiffPropValue (KeyFrames& keyFrames ,Property::Value& value,float fVal)
{

  Property::Type getType;
  Property::Type setType = value.GetType();
  keyFrames.Add(fVal, value);
  getType= keyFrames.GetType();

  DALI_CHECK_FALSE(getType!=setType, "property is Not Matched With Target Type");

  return true;
}


