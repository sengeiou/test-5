#include "utc-dali-refobject-common.h"

/**
 * @function       RefObjInit
 * @description    Check Whether Stage and Actor can be initialized
 * @param[in]      stage[Handle of Stage]
 * @param[in]      actor[Handle of Actor]
 * @param[in]      vec3SetPosition[A Vactor3 variable]
 * @param[in]      NA
 * @return         bool
 */
bool RefObjInit(Stage &stage, Actor &actor, Vector3 *vec3SetPosition)
{
  stage= Stage::GetCurrent();
  if(!stage )
  {
    LOG_I("stage is not created" );
    return false;
  }

  actor = Actor::New();
  if(!actor)
  {
    LOG_I("actor is not created" );
    return false;
  }

  stage.Add(actor);
  actor.SetPosition (*vec3SetPosition);
  if(!actor.OnStage())
  {
    LOG_I("actor is not in OnStage" );
    return false;
  }
  return true;
}

