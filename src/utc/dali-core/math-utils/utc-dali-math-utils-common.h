#ifndef _UTC_DALI_MATH_UTILS_COMMON_H_
#define _UTC_DALI_MATH_UTILS_COMMON_H_

#include "dali-common.h"

using namespace Dali;

#define SUITE_NAME  "MATH_UTILS_UTC"

template <class T> bool MathUtilsCommonClamp( T tValue, T tMinValue, T tMaxValue )
{
  T tClamp = Clamp( tValue, tMinValue, tMaxValue );
  T tClampResult = max( min( tValue, tMaxValue ), tMinValue );

  DALI_CHECK_FALSE( tClamp != tClampResult, "Clamp is failed to clamp the value between minimum and maximum values." );

  return true;
}

template <typename T> bool MathUtilsCommonClampInPlace( T tValue, T tMinValue, T tMaxValue )
{
  ClampInPlace(tValue, tMinValue, tMaxValue);
  T tClampResult = std::max( std::min( tValue, tMaxValue ), tMinValue );

  DALI_CHECK_FALSE( tValue != tClampResult, "ClampInPlace is failed to clamp the value directly between minimum and maximum values." );

  return true;
}

#endif  //_UTC_DALI_MATH_UTILS_COMMON_H_
