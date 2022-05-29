#ifndef _UTC_DALI_DEGREE_COMMON_H_
#define _UTC_DALI_DEGREE_COMMON_H_

#include "dali-common.h"

using namespace std;
using namespace Dali;

#define SUITE_NAME  "DEGREE_UTC"

namespace
{
  const float ONE80_OVER_PI = 180.0f/ Dali::Math::PI;
  const float PI_OVER_180 = Dali::Math::PI/ 180.0f;

  const float ANGLE_ONE80 = 180.0f;
  const float ANGLE_RHS = 90.0f, ANGLE_LHS = 90.0f;

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
}
/*******************************************************HELPER FUNCTIONS**************************************************/

#endif  //_UTC_DALI_DEGREE_COMMON_H_
