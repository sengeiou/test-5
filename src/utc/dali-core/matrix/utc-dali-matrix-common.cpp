#include "utc-dali-matrix-common.h"

bool MatrixSetGetAxis(int nAxisSet)
{
  Matrix matrix(true);
  const Vector3 VEC3_AXIS_SET(2.0f, 3.0f, 4.0f);
  const float ARRAY[] = { 0.0f, 0.0f, 0.0f };
  Vector3 vector3get;

  switch(nAxisSet)
  {
    case AXIS_X:
      matrix.SetXAxis(VEC3_AXIS_SET);
      break;
    case AXIS_Y:
      matrix.SetYAxis(VEC3_AXIS_SET);
      break;
    case AXIS_Z:
      matrix.SetZAxis(VEC3_AXIS_SET);
  }

  switch(nAxisSet)
  {
    case AXIS_X:
      vector3get = matrix.GetXAxis();
      break;
    case AXIS_Y:
      vector3get = matrix.GetYAxis();
      break;
    case AXIS_Z:
      vector3get = matrix.GetZAxis();
      break;
    default:
      vector3get = ARRAY;
  }

  if(vector3get == VEC3_AXIS_SET)
  {
    return true;
  }
  else
  {
    switch(nAxisSet)
    {
      case AXIS_X:
        LOG_E( "Dali::Matrix::SetXAxis and Dali::Matrix::GetXAxis is mismatched" );
        break;
      case AXIS_Y:
        LOG_E( "Dali::Matrix::SetYAxis and Dali::Matrix::GetYAxis is mismatched" );
        break;
      case AXIS_Z:
        LOG_E( "Dali::Matrix::SetZAxis and Dali::Matrix::GetZAxis is mismatched" );
        break;
      default:
        LOG_E( "unknown axis set request." );
    }
  }

  return false;
}

/**
 * @function            MatrixCheckEquals
 * @description         Check two matrices are eual
 * @param    [in]       matrix1 [const Matrix]
 * @param    [in]       matrix2 [const Matrix]
 * @param    [in]       fEpsilon [tolerance for fractional mismatches]
 * @return              bool - true, if two matrices are eual; false, otherwise
 */

bool MatrixCheckEquals(const Matrix& matrix1, const Matrix& matrix2, float fEpsilon)
{
  const float* fM1 = matrix1.AsFloat();
  const float* fM2 = matrix2.AsFloat();
  bool bValueCheck = true;

  for ( int i = 0; i < DIMENSION_OF_MATRIX; ++i )
  {
    bValueCheck &= (fabsf(fM1[i] - fM2[i])<fEpsilon);
  }

  return bValueCheck;
}
