#ifndef _UTC_DALI_RADIAN_COMMON_H_
#define _UTC_DALI_RADIAN_COMMON_H_

#include "dali-common.h"
#include <dali/dali.h>
#include <dali-toolkit/dali-toolkit.h>
#include <exception>

using namespace std;
using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME  "RADIAN_UTC"

extern bool gRadianInit;

/**
 * @brief Clamp a value.
 *
 * @param[in] value The value to clamp.
 * @param[in] min The minimum allowed value.
 * @param[in] max The maximum allowed value.
 * @return T the clamped value
 */
  template< typename T >
inline const T& ClampAngle( const T& value, const T& min, const T& max )
{
  const T& constrainedUpper = value < max ? value : max;
  const T& constrainedUpperAndLower = constrainedUpper > min ? constrainedUpper : min;
  return  constrainedUpperAndLower;
}

#endif  //_UTC_DALI_RADIAN_COMMON_H_
