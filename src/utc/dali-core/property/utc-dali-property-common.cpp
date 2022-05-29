#include "utc-dali-property-common.h"

/**
 * @function     PropertyAnimationForPositionComponentX
 * @description  Helper for property animation for position X component
 * @param[in]    actor[actor instance]
 * @param[in]    property[Property instance]
 * @param[out]   application[TestApplication]
 * @return       bool    true: if property is properly animated using object-property pair; false: otherwise.
 */
bool PropertyAnimationForPositionComponentX( Actor actor, Property property )
{
  Stage::GetCurrent().Add( actor );

  Animation animation = Animation::New( PROPERTY_ANIMATION_TIME );
  DALI_CHECK_FALSE(!animation, "Animation::New is failed .");

  float fProgressInit = 0.0f, fProgressTarget = 1.0f;
  float fInit = 0.0f;

  KeyFrames keyframes = KeyFrames::New();
  DALI_CHECK_FALSE(!keyframes, "KeyFrames::New is failed .");
  keyframes.Add( fProgressInit, fInit);
  keyframes.Add( fProgressTarget, gTarget );

  animation.AnimateBetween( property, keyframes, AlphaFunction::LINEAR);
  animation.Play();

  return true;
}
