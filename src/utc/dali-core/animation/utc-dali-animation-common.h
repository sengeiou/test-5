#ifndef _UTC_DALI_ANIMATION_COMMON_H_
#define _UTC_DALI_ANIMATION_COMMON_H_

#include "dali-common.h"

using namespace Dali;

#define SUITE_NAME  "ANIMATION_UTC"
#define ROTATION_EPSILON  0.0001f
#define ALPHA_FUNCTION  AlphaFunction::LINEAR
#define ALPHA_FUNCTION_EASEIN  AlphaFunction::EASE_IN
#define RENDER_DELAY_TIME  1000u

/**Global variables declaration for more than one file*/
extern float gFloatAnimationSetDuration;
extern float gFloatTwentyFivepercent;
extern float gFloatAlphaFuncCheck;
extern float gFloatAnimationDelay;
extern const float ANIMATION_EPSILON;
extern const Vector4 ANIM_INIT_COLOR;
extern const Vector4 ANIM_TARGET_COLOR;
extern bool gBoolSignalReceived;

/**Callback for anination finished signal*/
void CbAnimationFinishCheck(Animation& animation);

/**animation actor and stage init */
bool  AnimationActorInit(Actor& actor,Animation& animation ,Stage& stage);

/**animation and zero color actor init */
bool  AnimationZeroColorActorInit(Actor& actor,Animation& animation);

/** initial color check and set keyframe */
bool AnimationInitColorCheckSetKeyFrame( Actor& actor,KeyFrames& keyFrames );

/** Final Color Check */
bool AnimationFinalColorCheck( Actor& actor );

/**
 * @function         AnimationTemplateCheck
 * @description      A helper for fuzzy-comparing different property type values
 * @param[in]        tValue1 the first property type value
 * @param[in]        tValue2 the second property type value
 * @param[in]        fEpsilon difference threshold
 * @param[out]       NA
 *
 * @return           true if difference is smaller than fEpsilon threshold, false otherwise
 */
template<typename type>
inline bool AnimationTemplateCheck(type tValue1, type tValue2, float fEpsilon);

/**
 * @function         AnimationTemplateCheck<bool>
 * @description      A helper for fuzzy-comparing boolean values
 * @param[in]        bValue1 the first boolean value
 * @param[in]        bValue2 the second boolean value
 * @param[in]        fEpsilon difference threshold[not effective
 * @param[out]       NA
 *
 * @return           true if there is no difference, false otherwise
 */
  template<>
inline bool AnimationTemplateCheck<bool>(bool bValue1, bool bValue2, float fEpsilon)
{
  return bValue1 == bValue2;
}

/**
 * @function         AnimationTemplateCheck<int>
 * @description      A helper for fuzzy-comparing integer values
 * @param[in]        nValue1 the first integer value
 * @param[in]        nValue2 the second integer value
 * @param[in]        fEpsilon difference threshold
 * @param[out]       NA
 *
 * @return           true if difference is smaller than fEpsilon threshold, false otherwise
 */
  template<>
inline bool AnimationTemplateCheck<int>(int nValue1, int nValue2, float fEpsilon)
{
  return fabsf(nValue1 - nValue2) < fEpsilon;
}

/**
 * @function         AnimationTemplateCheck<float>
 * @description      A helper for fuzzy-comparing float values
 * @param[in]        fValue1 the first float value
 * @param[in]        fValue2 the second float value
 * @param[in]        fEpsilon difference threshold
 * @param[out]       NA
 *
 * @return           true if difference is smaller than fEpsilon threshold, false otherwise
 */
  template<>
inline bool AnimationTemplateCheck<float>(float fValue1, float fValue2, float fEpsilon)
{
  return fabsf(fValue1 - fValue2) < fEpsilon;
}


/**
 * @function         AnimationTemplateCheck<Vector2>
 * @description      A helper for fuzzy-comparing Vector2 objects
 * @param[in]        vector1 the first vector2 object
 * @param[in]        vector2 the second vector2 object
 * @param[in]        fEpsilon difference threshold
 * @param[out]       NA
 *
 * @return           true if difference is smaller than fEpsilon threshold, false otherwise
 */
  template<>
inline bool AnimationTemplateCheck<Vector2>(Vector2 vector1, Vector2 vector2, float fEpsilon)
{
  return fabsf(vector1.x - vector2.x) < fEpsilon && fabsf(vector1.y - vector2.y) < fEpsilon;
}

/**
 * @function         AnimationTemplateCheck<Vector3>
 * @description      A helper for fuzzy-comparing vector3 objects
 * @param[in]        vector1 the first vector3 object
 * @param[in]        vector2 the second vector3 object
 * @param[in]        fEpsilon difference threshold
 * @param[out]       NA
 *
 * @return           true if difference is smaller than fEpsilon threshold, false otherwise
 */
  template<>
inline bool AnimationTemplateCheck<Vector3>(Vector3 vector1, Vector3 vector2, float fEpsilon)
{
  return fabsf(vector1.x - vector2.x) < fEpsilon &&
    fabsf(vector1.y - vector2.y) < fEpsilon &&
    fabsf(vector1.z - vector2.z) < fEpsilon;
}

/**
 * @function         AnimationTemplateCheck<Vector4>
 * @description      A helper for fuzzy-comparing vector4 objects
 * @param[in]        vector1 the first vector4 object
 * @param[in]        vector2 the second vector4 object
 * @param[in]        fEpsilon difference threshold
 * @param[out]       NA
 *
 * @return           true if difference is smaller than fEpsilon threshold, false otherwise
 */
  template<>
inline bool AnimationTemplateCheck<Vector4>(Vector4 vector1, Vector4 vector2, float fEpsilon)
{
  return fabsf(vector1.x - vector2.x) < fEpsilon &&
    fabsf(vector1.y - vector2.y) < fEpsilon &&
    fabsf(vector1.z - vector2.z) < fEpsilon &&
    fabsf(vector1.w - vector2.w) < fEpsilon;
}

/**
 * @function         AnimationTemplateCheck
 * @description      A helper for fuzzy-comparing quaternion objects
 * @param[in]        quaternion1 the first quaternion object
 * @param[in]        quaternion2 the second quaternion object
 * @param[in]        fEpsilon difference threshold
 * @param[out]       NA
 *
 * @return           true if difference is smaller than fEpsilon threshold, false otherwise
 */
  template<>
inline bool AnimationTemplateCheck<Quaternion>(Quaternion quaternion1, Quaternion quaternion2, float fEpsilon)
{
  Quaternion q2N = -quaternion2;
  return AnimationTemplateCheck<Vector4>(quaternion1.mVector, quaternion2.mVector, fEpsilon) || AnimationTemplateCheck<Vector4>(quaternion1.mVector, q2N.mVector, fEpsilon);
}

//common function for AnimateBy Api with Different template Type
/**
 * @function          AnimationAnimateByTemplate
 * @description       Test for overloded Value for AnimateBy Api
 * @param[out]        actor[A actor  object instance ]
 * @param[out]        animation[A animation  object instance ]
 * @param[in]         testValue[the value to set]
 * @param[in]         propertyIndex [the index of target property]
 *
 * @return            true if all the conditions Executed Properly
 */
template <class type> bool AnimationAnimateByTemplate (Actor& actor , Animation& animation,type testValue,Property::Index propertyIndex)
{
  gFloatAnimationSetDuration = 0.3f;
  gBoolSignalReceived = false;
  Stage::GetCurrent().Add(actor);
  animation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FALSE(!animation, "Animation::New is failed.");

  animation.FinishedSignal().Connect(&CbAnimationFinishCheck);
  animation.AnimateBy(Property(actor, propertyIndex), testValue);
  animation.Play();
  return true;
}
/**
 * @function          AnimationAnimateByTemplateCheck
 * @description       Check animationby is over with target value
 * @param[out]        actor[A actor  object instance ]
 * @param[out]        animation[A animation  object instance ]
 * @param[in]         testFinalValue[the final value to get expected]
 * @param[in]         propertyIndex [the index of target property]
 *
 * @return            true if all the conditions Executed Properly
 */
template <class type> bool AnimationAnimateByTemplateCheck (Actor& actor , Animation& animation, type testFinalValue,Property::Index propertyIndex)
{
  DALI_CHECK_FALSE(!gBoolSignalReceived, "Animation is not finished");
  DALI_CHECK_FALSE(!AnimationTemplateCheck<type>(actor.GetProperty<type>(propertyIndex), testFinalValue, ANIMATION_EPSILON),
      "Current property is Not Matched With target property.");
  animation.Clear();
  Stage::GetCurrent().Remove(actor);
  return true;
}

//common function for AnimateBy Api with Different template Type for TimePeriod
/**
 * @function          AnimationAnimateByTimePeriod
 * @description       Test for overloded Value for AnimateBy Api
 * @param[out]        actor[A actor  object instance ]
 * @param[out]        animation[A animation  object instance ]
 * @param[in]         testValue[the value to set]
 * @param[in]         propertyIndex [the index of target property]
 *
 * @return            true if all the conditions Executed Properly
 */
template <class type> bool AnimationAnimateByTimePeriod (Actor& actor, Animation& animation,type testValue,Property::Index propertyIndex)
{
  gFloatAnimationSetDuration = 0.5f;
  gBoolSignalReceived = false;
  TimePeriod timePeriod(gFloatAnimationDelay, gFloatAnimationSetDuration - gFloatAnimationDelay);

  Stage::GetCurrent().Add(actor);
  animation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FALSE(!animation, "Animation::New is failed.");

  animation.FinishedSignal().Connect(&CbAnimationFinishCheck);
  animation.AnimateBy(Property(actor, propertyIndex), testValue,timePeriod);
  animation.Play();
  return true;
}

//common function for Animation Actor and propertyIndex Init
/**
 * @function           ActorAnimatePropInit
 * @description        common function for Animation Actor and propertyIndex Init
 * @param[in]          testValue[ the different type property value ]
 * @param[out]         actor[A actor  object instance ]
 * @param[out]         propertyIndex [the index of target property]
 *
 * @return             true if all the conditions Executed Properly
 */
template <class type> bool ActorAnimatePropInit ( Actor& actor ,type testValue,Property::Index &propertyIndex )
{
  const string strPROPERTYNAME = "New-property" ;
  actor = Actor::New();
  DALI_CHECK_FALSE(!actor, " Actor::New is failed.");
  propertyIndex = actor.RegisterProperty( strPROPERTYNAME , testValue );
  DALI_CHECK_FALSE(actor.GetProperty<type>(propertyIndex)!=testValue, " Actor property registration failed.");
  return true ;
}


//common function for AnimateTo Api with Different template Type for TimePeriod and Alpha Function
/**
 * @function           AnimationAnimateToTimePeriodAlphaFunction
 * @description        Test for overloded Value for AnimateBy Api
 * @param[out]         actor[A actor  object instance ]
 * @param[out]         animation[A animation  object instance ]
 * @param[in]          targetValue[the value to set]
 * @param[in]          propertyIndex [the index of target property]
 *
 * @return             true if all the conditions Executed Properly
 */
template <class type> bool AnimationAnimateToTimePeriodAlphaFunction (Actor& actor, Animation& animation,type targetValue,Property::Index propertyIndex)
{
  gFloatAnimationSetDuration = 0.5f;
  gBoolSignalReceived = false;
  TimePeriod timePeriod(gFloatAnimationDelay, gFloatAnimationSetDuration - gFloatAnimationDelay);

  Stage::GetCurrent().Add(actor);
  animation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FALSE(!animation, "Animation::New is failed.");

  animation.FinishedSignal().Connect(&CbAnimationFinishCheck);
  animation.AnimateTo(Property (actor, propertyIndex), targetValue, ALPHA_FUNCTION, timePeriod);
  animation.Play();
  return true;
}

//common function for AnimateTo Api with Different template Type for TimePeriod
/**
 * @function           AnimationAnimateToTimePeriod
 * @description        Test for overloded Value for AnimateTo Api for TimePeriod
 * @param[out]         animation[Instance of animation]
 * @param[out]         actor[A actor  object instance ]
 * @param[in]          targetValue[ the value of final  property    ]
 * @param[in]          propertyIndex [the index of target property]
 *
 * @return             true if all the conditions Executed Properly
 */
template <class type> bool AnimationAnimateToTimePeriod (Actor& actor, Animation& animation,type targetValue,Property::Index propertyIndex)
{
  gFloatAnimationSetDuration = 0.5f;
  gBoolSignalReceived = false;
  TimePeriod timePeriod(gFloatAnimationDelay, gFloatAnimationSetDuration - gFloatAnimationDelay);

  Stage::GetCurrent().Add(actor);
  animation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FALSE(!animation, "Animation::New is failed.");

  animation.FinishedSignal().Connect(&CbAnimationFinishCheck);
  animation.AnimateTo(Property (actor, propertyIndex), targetValue, timePeriod);
  animation.Play();
  return true;
}

//common function for AnimateTo Api with Different template Type
/**
 * @function             AnimationAnimateToDiffProperty
 * @description          Test for overloded Value for AnimateTo Api
 * @param[out]           actor[A actor  object instance ]
 * @param[out]           animation[A animation  object instance ]
 * @param[in]            targetValue[the value to set as target]
 * @param[in]            propertyIndex [the index of target property]
 *
 * @return               true if all the conditions Executed Properly
 */
template <class type> bool AnimationAnimateToDiffProperty (Actor& actor, Animation& animation,type targetValue,Property::Index propertyIndex)
{
  gFloatAnimationSetDuration = 0.3f;
  gBoolSignalReceived = false;

  Stage::GetCurrent().Add(actor);
  animation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FALSE(!animation, "Animation::New is failed.");

  animation.FinishedSignal().Connect(&CbAnimationFinishCheck);
  animation.AnimateTo(Property(actor, propertyIndex), targetValue);
  animation.Play();
  return true;
}


#endif  //_UTC_DALI_ANIMATION_COMMON_H_
