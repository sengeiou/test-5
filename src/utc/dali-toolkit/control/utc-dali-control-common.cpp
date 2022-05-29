#include "utc-dali-control-common.h"

//Add helper function definitions here


/**
 * @function                 ControlGestureInit
 * @description              Initializes Gesture events
 * @return                   bool
 */
bool ControlGestureInit(Stage &stage, Control &control)
{
  Vector3 vec3ControlSize(100.0f, 100.0f, 100.0f);

  stage = Stage::GetCurrent();
  DALI_CHECK_FALSE(!stage, "stage is not created.");

  control = Control::New();
  DALI_CHECK_FALSE(!control, "Control::New() is not created.");

  control.SetSize( vec3ControlSize );
  control.SetAnchorPoint(AnchorPoint::TOP_LEFT);
  stage.Add(control);

  return true;
}
