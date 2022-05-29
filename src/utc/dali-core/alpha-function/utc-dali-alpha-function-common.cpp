#include "utc-dali-alpha-function-common.h"

void AlphaFunctionRemoveAnimationActor(Actor &actor , Animation &animation)
{
  animation.Stop();
  Stage::GetCurrent().Remove(actor);
}

/**
 * @function         AlphaFunctionsInit
 * @description        Create an actor and Set actor properties
 * @param    [in]    Actor[Actor to animate]
 * @param    [in]    animation[animation state]
 * @return      true if all works properly , else false
 */
bool AlphaFunctionsInit( Actor &actor , Animation &animation)
{
  float fSetDuration(DEFAULT_DURATION);
  actor = Actor::New();
  DALI_CHECK_FALSE(!actor, " Actor::New() is Failed.");

  actor.SetAnchorPoint( AnchorPoint::CENTER );
  actor.SetParentOrigin( ParentOrigin::CENTER );
  actor.SetPosition(Vector3::ZERO);
  actor.SetSize(100,220);
  Stage::GetCurrent().Add(actor);

  animation = Animation::New(fSetDuration);
  DALI_CHECK_FALSE(!animation, " Animation::New() is Failed.");
  return true ;
}
