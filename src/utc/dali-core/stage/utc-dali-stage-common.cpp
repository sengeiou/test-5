#include "utc-dali-stage-common.h"

/**
 * @function     StageTouchCallback
 * @description  actor on stage touch callback
 * @param[in]    actor  [actor object reference]
 * @param[in]    touchEvent[touchEvent reference]
 * @return       true     if called
 */
bool StageTouchCallback( Actor actor, const TouchEvent& touchEvent )
{
  LOG_I( "StageTouchCallback CallBack is Called .");
  return true;
}

/**
 * @function     StageSetGetBackgroundColor
 * @description  Test for different background  Colors
 * @param[in]    vec4SetColor[text color]
 * @return       true     if SetBackgroundColor and GetBackgroundColor is matched for Stage or false otherwise
 */
bool StageSetGetBackgroundColor(Vector4 vec4SetColor)
{
  Vector4 vec4GetColor = Color::WHITE;

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FALSE(!stage,  "GetCurrent is Failed..");

  stage.SetBackgroundColor( vec4SetColor);

  vec4GetColor = stage.GetBackgroundColor();

  DALI_CHECK_FALSE(vec4GetColor!=vec4SetColor,  "SetBackgroundColor and GetBackgroundColor is mismatched for Stage.");
  return true;
}
