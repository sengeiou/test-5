#include "utc-dali-constraint-common.h"

/**
 * @function         ConstraintCreateHandle
 * @description      A helper for creating actor handle if its requested to be on stage
 * @param[out]       actor, Actor handle instance
 * @param[in]        bIsOnStage, boolean value to request to be on stage
 * @return           if error occurs returns false else true
 */
bool ConstraintCreateHandle(Actor &actor, bool bIsOnStage)
{
  actor = Actor::New();

  DALI_CHECK_FALSE(!actor, "Actor::RegisterProperty() is failed for actor");

  if(bIsOnStage)
  {
    DALI_CHECK_FALSE(!actor.Supports(Handle::DYNAMIC_PROPERTIES), "Actor::Supports() is failed for Handle::DYNAMIC_PROPERTIES");

    Stage::GetCurrent().Add(actor);
  }

  return true;
}


