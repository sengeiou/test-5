#ifndef _UTC_DALI_MATRIX3_COMMON_H_
#define _UTC_DALI_MATRIX3_COMMON_H_

#include <sstream>
#include "dali-common.h"
#include <dali/dali.h>
#include <dali-toolkit/dali-toolkit.h>

using namespace std;
using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME    "MATRIX3_UTC"
#define MATRIX3_EPSILON  0.001f

enum EElements { s00, s01, s02, s10, s11, s12, s20, s21, s22 };
const int ELEMENTS_COUNT = 9;      // 3x3 Matrix
const float N_OF_MATRIX_SIZE_NxN = 3.0f;

//Helper to get magnitude
float Matrix3GetMagnitude(float* pMatrix3);

//Helper to check two 3x3 matrices are eual
bool Matrix3CheckEquals(const Matrix3& matrix1, const Matrix3& matrix2);

#endif  //_UTC_DALI_MATRIX3_COMMON_H_
