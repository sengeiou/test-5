#ifndef _UTC_DALI_MATRIX_COMMON_H_
#define _UTC_DALI_MATRIX_COMMON_H_

#include <sstream>
#include "dali-common.h"
#include <dali/dali.h>
#include <dali-toolkit/dali-toolkit.h>

using namespace std;
using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME   "MATRIX_UTC"

const int DIMENSION_OF_MATRIX = 16;
const float MATRIX_EPSILON = 0.01f;
enum EAxisSet { AXIS_X = 1, AXIS_Y = 2, AXIS_Z = 3 };

//Helper function for Matrix set/ get Axis
bool MatrixSetGetAxis(int nAxisSet);

//Helper function to check two matrices are eual
bool MatrixCheckEquals(const Matrix& matrix1, const Matrix& matrix2, float epsilon);

#endif  //_UTC_DALI_MATRIX_COMMON_H_
