#include "utc-dali-time-period-common.h"

bool gSignalAfterTime = false;

/**
 * @function     TimePeriodAnimationEnd
 * @description  Animation finish callback
 * @param[in]    animation[ Animation instance ]
 * @param[out]   NA
 * @return       NA
 */

void TimePeriodAnimationEnd(Animation& animation)
{
  if(animation)
  {
    LOG_I("Callback for animation finished after time period is called");
    gSignalAfterTime = true;
  }
}

/**
 * @function     TimePeriodActorAnimationNew
 * @description  Create actor, animation, register property to actor and connect animation to functor
 * @param[out]   actor[ Actor instance ]
 * @param[out]   animation[ Animation instance ]
 * @param[in]    fStart[ A Start Property to Register ]
 * @param[in]    fTime[ Time for animation ]
 * @param[out]   index[ Property Index ]
 * @return       bool -false: if actor or animation instance is not created properly
 *                    -true : if property is registered to actor, actor is added to stage and animation is connected to functor
 *                            after creation
 */

bool TimePeriodActorAnimationNew( Actor &actor, Animation& animation, float fStart, float fTime, Property::Index& index)
{
  actor = Actor::New();
  DALI_CHECK_FALSE( !actor , "Actor::New() is failed");

  animation = Animation::New( fTime );
  DALI_CHECK_FALSE( !animation , "Animation::New is failed");

  Stage::GetCurrent().Add( actor );
  index = actor.RegisterProperty( "Test_Property", fStart);

  animation.FinishedSignal().Connect( &TimePeriodAnimationEnd );
  return true;
}

/**
 * @function     TimePeriodSetPropertyDuration
 * @description  Reset functor, clear animation, set property to actor, set duration to animation
 * @param[out]   actor[ Actor instance ]
 * @param[out]   animation[ Animation instance ]
 * @param[in]    fStart[ A Start Property to set ]
 * @param[in]    fDuration[ Time for animation ]
 * @param[out]   index[ Property Index ]
 * @param[out]   NA
 * @return
 */

void TimePeriodSetPropertyDuration( Actor &actor, Animation& animation, float fStart, float fDuration,
    Property::Index& index )
{
  gSignalAfterTime = false;
  /**Clearing animation to release if there is any previous animation data*/
  animation.Clear();
  actor.SetProperty( index, fStart );
  /**Clear wipes out the animatio data, so setting duration again here*/
  animation.SetDuration( fDuration );
}

/**
 * @function     TimePeriodAnimPlay
 * @description  Playing animation with required property and target
 * @param[out]   actor[ Actor instance ]
 * @param[out]   animation[ Animation instance ]
 * @param[in]    fStart[ A Start Property of actor ]
 * @param[in]    fTarget[ Target property of actor ]
 * @param[in]    index[ Property Index ]
 * @param[in]    timePeriod [ TimePeriod instance ]
 * @param[out]   NA
 * @return
 */

void TimePeriodAnimPlay( Actor &actor, Animation &animation, float fStart, float fTarget, Property::Index& index, TimePeriod timePeriod )
{
  animation.AnimateTo( Property( actor, index ), fTarget, timePeriod );
  animation.Play();
}

