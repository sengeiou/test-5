#ifndef _UTC_DALI_CONTROL_COMMON_H_
#define _UTC_DALI_CONTROL_COMMON_H_

#include "dali-common.h"
#include <dali-toolkit/dali-toolkit.h>

using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME                 "CONTROL_UTC"
#define CONTROL_IMAGE_NAME         "dali_imagemodule_image.png"

// HELPER FUNCTIONS

/**Initializes control for gesture events**/
bool ControlGestureInit( Stage &stage, Control &control );

#endif //_UTC_DALI_CONTROL_COMMON_H_
