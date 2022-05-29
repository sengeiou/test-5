#include "utc-dali-animation-common.h"

/**Global variables definitions for more than one file*/
bool gBoolSignalReceived(false);
float gFloatAnimationSetDuration (1.0f) ;
float gFloatTwentyFivepercent = 0.25f;
float gFloatAlphaFuncCheck =  0.1f;
float gFloatAnimationDelay (0.2f);
const float ANIMATION_EPSILON = 0.0001f;
const Vector4 ANIM_INIT_COLOR = Vector4::ZERO;
const Vector4 ANIM_TARGET_COLOR = Vector4::ONE;

//Add helper function definitions here

/**
 * @function      CbAnimationFinishCheck
 * @description   Callback for anination finished signal
 * @param[in]     animation[Animation instance]
 * @return        NA
 */
void CbAnimationFinishCheck(Animation& animation)
{
  if(animation)
  {
    gBoolSignalReceived = true;
  }
}

/**
 * @function      AnimationActorInit
 * @description   Initialize actor, animation, stage and add actor to stage
 * @param[out]    actor[actor object reference ]
 *       [out]    animation [animation object reference]
 *       [out]    stage    [stage object reference]
 * @return        true if all conditions passed or false if any condition fails
 */
bool  AnimationActorInit(Actor& actor,Animation& animation ,Stage& stage )
{
  actor = Actor::New();
  DALI_CHECK_FALSE(!actor, " Actor::New() is Failed.");
  stage = Stage::GetCurrent();
  DALI_CHECK_FALSE(!stage, " Stage::GetCurrent() is Failed.");
  stage.Add(actor);
  animation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FALSE(!animation, " Animation::New() is Failed.");
  return true;
}

/**
 * @function      AnimationZeroColorActorInit
 * @description   Initialize actor with zero color, animation and add actor to stage
 * @param[out]    actor[actor object reference ]
 *       [out]    animation [animation object reference]
 * @return        true if all conditions passed or false if any condition fails
 */
bool  AnimationZeroColorActorInit(Actor& actor,Animation& animation )
{
  gFloatAnimationSetDuration = 0.3f;

  animation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FALSE(!animation, " Animation::New() is Failed.");

  actor = Actor::New();
  DALI_CHECK_FALSE(!actor, " Actor::New() is Failed.");
  actor.SetColor(ANIM_INIT_COLOR);

  Stage::GetCurrent().Add(actor);
  return true;
}

/**
 * @function      AnimationInitColorCheckSetKeyFrame
 * @description   initial color check and set keyframe
 * @param[out]    actor[actor object reference ]
 *       [out]    keyFrames [KeyFrames object reference]
 * @return        true if all conditions passed or false if any condition fails
 */

bool AnimationInitColorCheckSetKeyFrame( Actor& actor,KeyFrames& keyFrames )
{
  float fStartValue = ANIM_INIT_COLOR.x;

  DALI_CHECK_FALSE(!AnimationTemplateCheck<float>(actor.GetProperty<float>(Actor::Property::COLOR_RED), fStartValue, ANIMATION_EPSILON), "Initial color setting for COLOR_RED is failed.");
  DALI_CHECK_FALSE(!AnimationTemplateCheck<float>(actor.GetProperty<float>(Actor::Property::COLOR_GREEN), fStartValue, ANIMATION_EPSILON), "Initial color setting for COLOR_GREEN is failed.");
  DALI_CHECK_FALSE(!AnimationTemplateCheck<float>(actor.GetProperty<float>(Actor::Property::COLOR_BLUE), fStartValue, ANIMATION_EPSILON), "Initial color setting for COLOR_BLUE is failed.");
  DALI_CHECK_FALSE(!AnimationTemplateCheck<float>(actor.GetProperty<float>(Actor::Property::COLOR_ALPHA), fStartValue, ANIMATION_EPSILON), "Initial color setting for COLOR_ALPHA is failed.");

  keyFrames = KeyFrames::New();
  DALI_CHECK_FALSE(!keyFrames, "Keyframes::New is failed .");

  keyFrames.Add(0.0f, Vector4(0.1f, 0.2f, 0.3f, 0.4f));
  keyFrames.Add(0.5f, Vector4(0.9f, 0.8f, 0.7f, 0.6f));
  keyFrames.Add(1.0f, ANIM_TARGET_COLOR);
  return true;
}

/**
 * @function      AnimationFinalColorCheck
 * @description   Final Color Check
 * @param[out]    actor[actor object reference ]
 * @return        true if all conditions passed or false if any condition fails
 */

bool AnimationFinalColorCheck( Actor& actor )
{
  float fTarget = ANIM_TARGET_COLOR.x;
  DALI_CHECK_FALSE(!AnimationTemplateCheck<float>(actor.GetProperty<float>(Actor::Property::COLOR_RED), fTarget, ANIMATION_EPSILON), "Actor property color  animate between failed for color red.");
  DALI_CHECK_FALSE(!AnimationTemplateCheck<float>(actor.GetProperty<float>(Actor::Property::COLOR_GREEN), fTarget, ANIMATION_EPSILON), "Actor property color animate between failed for color green .");
  DALI_CHECK_FALSE(!AnimationTemplateCheck<float>(actor.GetProperty<float>(Actor::Property::COLOR_BLUE), fTarget, ANIMATION_EPSILON), "Actor property color animate between failed  for color blue.");
  DALI_CHECK_FALSE(!AnimationTemplateCheck<float>(actor.GetProperty<float>(Actor::Property::COLOR_ALPHA), fTarget, ANIMATION_EPSILON), "Actor property color animate between failed for color alpha .");
  return true;
}


