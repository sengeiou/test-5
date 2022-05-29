#include "utc-dali-matrix3-common.h"

float Matrix3GetMagnitude(float rgfMatrix3[])
{
  float fAverage = 0.0f;
  for(int i = 0; i < ELEMENTS_COUNT; i++)
  {
    fAverage += fabsf(rgfMatrix3[i]);
  }
  return fAverage/ ELEMENTS_COUNT;
}


/**
 * @function         Matrix3CheckEquals
 * @description         Check two 3x3 matrices are eual
 * @param    [in]    matrix1 [const Matrix3]
 * @param    [in]    matrix2 [const Matrix3]
 * @return           bool - true, if two matrices are eual; false, otherwise
 */

bool Matrix3CheckEquals(const Matrix3& matrix1, const Matrix3& matrix2)
{
  const float* fM1 = matrix1.AsFloat();
  const float* fM2 = matrix2.AsFloat();
  bool bValueCheck = true;

  for ( int i = 0; i < ELEMENTS_COUNT; ++i )
  {
    bValueCheck &= (fabsf(fM1[i] - fM2[i]) < GetRangedEpsilon( fM1[i], fM2[i] ) );
  }

  return bValueCheck;
}
