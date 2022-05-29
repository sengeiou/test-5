#include "utc-dali-actor-common.h"

bool ActorGetCurrentPosition(Actor &actor,Vector3 vec3SetPosition,enum ActorPositionInputParam ePositionOption)
{
  Dali::Vector3 vec3GetPosition(0.0f, 0.0f, 0.0f);
  bool bPassed = true;
  switch(ePositionOption)
  {
    case ACTORPOSITION_DOUBLE_INPUT_PARAM:
      vec3GetPosition = Vector3::ZERO;
      vec3GetPosition = actor.GetCurrentPosition();
      if (vec3GetPosition.x != vec3SetPosition.x || vec3GetPosition.y != vec3SetPosition.y)
      {
        LOG_E("set and get value mismatched, vec3GetPosition");
        bPassed = false;
      }
      break;
    case ACTORPOSITION_MULTI_INPUT_PARAM:
      vec3GetPosition = Vector3::ZERO;

      vec3GetPosition = actor.GetCurrentPosition();
      if (vec3GetPosition.x != vec3SetPosition.x || vec3GetPosition.y != vec3SetPosition.y || vec3GetPosition.z != vec3SetPosition.z)
      {
        LOG_E("set and get value mismatched, vec3GetPosition");
        bPassed = false;
      }
      break;
    case ACTORPOSITION_VECTOR_INPUT_PARAM:
      vec3GetPosition = Vector3::ZERO;

      vec3GetPosition = actor.GetCurrentPosition();
      if (vec3GetPosition != vec3SetPosition)
      {
        LOG_E("set and get value mismatched, vec3GetPosition");
        bPassed = false;
      }
      break;
  }
  return bPassed;
}

bool ActorGetCurrentOrientation(Actor &actor,float fSetAngle,Vector3 vec3SetAxis, enum ActorOrientationInputParam OrientationOption)
{
  Dali::Quaternion quatGetOrientation = Quaternion::IDENTITY;
  Dali::Quaternion quatSetOrientation(Radian(fSetAngle), vec3SetAxis);
  Dali::Quaternion quatSetOrientationDgr(Radian(Degree(fSetAngle)), vec3SetAxis);

  bool bPassed = true;

  switch(OrientationOption)
  {
    case ACTORROTATION_DEGREE:
      quatGetOrientation = actor.GetCurrentOrientation();

      if (quatGetOrientation != quatSetOrientationDgr)
      {
        LOG_E("set and get value mismatched for rotation");
        bPassed = false;
      }
      break;
    case ACTORROTATION_RADIAN:
    case ACTORROTATION_QUATERNION:
      quatGetOrientation = actor.GetCurrentOrientation();

      if (quatGetOrientation != quatSetOrientation)
      {
        LOG_E("set and get value mismatched for rotation");
        bPassed = false;
      }
      break;
  }
  return bPassed;
}

bool ActorGetCurrentScale(Actor &actor,Vector3 vec3SetScale,enum ActorScaleInputParam ScaleOption)
{
  Dali::Vector3 vec3GetScale = Vector3::ZERO;
  bool bPassed = true;

  switch(ScaleOption)
  {
    case ACTORSCALE_SINGLE_INPUT_PARAM:

      vec3GetScale = actor.GetCurrentScale();
      //By setting scale with single param, all x, y, z terms of Vector3 scale is set with the same value
      if ((vec3GetScale.x != vec3SetScale.x) || (vec3GetScale.y != vec3SetScale.x) || (vec3GetScale.z != vec3SetScale.x))
      {
        LOG_E("set and get value mismatched for scale");
        bPassed = false;
      }
      break;
    case ACTORSCALE_MULTI_INPUT_PARAM:
      vec3GetScale = actor.GetCurrentScale();
      if ((vec3GetScale.x != vec3SetScale.x) || (vec3GetScale.y != vec3SetScale.y) || (vec3GetScale.z != vec3SetScale.z))
      {
        LOG_E("set and get value mismatched for scale");
        bPassed = false;
      }
      break;
    case ACTORSCALE_VECTOR_INPUT_PARAM:
      vec3GetScale = actor.GetCurrentScale();

      if (vec3GetScale != vec3SetScale)
      {
        LOG_E("set and get value mismatched for scale");
        bPassed = false;
      }
      break;
  }
  return bPassed;
}

bool ActorGetCurrentSize(Actor &actor,Vector3 vec3SetSize, enum ActorSizeInputParam SizeOption)
{
  bool bPassed = true;
  Dali::Vector3 vec3GetSize = Vector3::ZERO;

  switch(SizeOption)
  {
    case ACTORSIZE_DOUBLE_INPUT_PARAM:
    case ACTORSIZE_VECTOR2_INPUT_PARAM:
      vec3GetSize = actor.GetCurrentSize();
      if ((vec3GetSize.x != vec3SetSize.x) || (vec3GetSize.y != vec3SetSize.y) )
      {
        LOG_E("set and get value mismatched for Size");
        bPassed = false;
      }
      break;
    case ACTORSIZE_MULTI_INPUT_PARAM:
      vec3GetSize = Vector3::ZERO;

      vec3GetSize = actor.GetCurrentSize();
      if ((vec3GetSize.x != vec3SetSize.x) || (vec3GetSize.y != vec3SetSize.y) || (vec3GetSize.z != vec3SetSize.z))
      {
        LOG_E("set and get value mismatched for Size");
        bPassed = false;
      }
      break;
    case ACTORSIZE_VECTOR3_INPUT_PARAM:
      vec3GetSize = Vector3::ZERO;

      vec3GetSize = actor.GetCurrentSize();

      if (vec3GetSize != vec3SetSize)
      {
        LOG_E("set and get value mismatched for Size");
        bPassed = false;
      }
      break;
  }
  return bPassed;
}
