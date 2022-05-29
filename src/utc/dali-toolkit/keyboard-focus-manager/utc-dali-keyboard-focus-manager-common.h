#ifndef _UTC_DALI_KEYBOARD_FOCUS_MANAGER_COMMON_H_
#define _UTC_DALI_KEYBOARD_FOCUS_MANAGER_COMMON_H_

#include "dali-common.h"
#include <dali-toolkit/dali-toolkit.h>

using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME             "KEYBOARD_FOCUS_MANAGER_UTC"

/**Helper function for moving focus**/
bool KeyboardFocusManagerMoveFocus( Dali::Toolkit::Control::KeyboardFocus::Direction focusDirection);

#endif //_UTC_DALI_KEYBOARD_FOCUS_MANAGER_COMMON_H_
