#include "utc-dali-base-handle-common.h"

/**
 * @function       RefObjInit
 * @description    Check Whether Stage and Actor can be initialized
 * @param[in]      stage[Handle of Stage]
 * @param[in]      actor[Handle of Actor]
 * @param[in]      vec3SetPosition[A Vactor3 variable]
 * @param[out]     NA
 *
 * @return         NA
 */
bool basehandleInit(Stage &stage, Actor &actor, Vector3 *vec3SetPosition)
{
  stage= Stage::GetCurrent();
  DALI_CHECK_FALSE(!stage , " stage is not created");

  actor = Actor::New();
  DALI_CHECK_FALSE(!actor, " Actor::New() is failed ");

  stage.Add(actor);
  actor.SetPosition (*vec3SetPosition);
  DALI_CHECK_FALSE(!actor.OnStage(), " actor is not in OnStage");

  return true;
}

