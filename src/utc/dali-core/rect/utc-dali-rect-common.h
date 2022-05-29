#ifndef _UTC_DALI_RECT_COMMON_H_
#define _UTC_DALI_RECT_COMMON_H_

#include "dali-common.h"
#include <sstream>

using namespace Dali;

#define SUITE_NAME  "RECT_UTC"

enum ERectDirection
{
  RECT_BOTTOM,
  RECT_TOP,
  RECT_LEFT,
  RECT_RIGHT
};

//Helper function for Rect Bottom / Left / Right / Top
bool RectBottomLeftRightTop(enum ERectDirection eRectDirection);

#endif  //_UTC_DALI_RECT_COMMON_H_
