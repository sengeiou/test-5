#include "utc-dali-quaternion-common.h"

bool QuaternionCompare(Quaternion q1, Quaternion q2, float epsilon)
{
  Quaternion q2N = -q2; // These quaternions represent the same rotation

  Vector4 vector1 = q1.mVector, vector2 = q2.mVector;

  bool bCheckOne = fabsf(vector1.x - vector2.x)<epsilon &&
    fabsf(vector1.y - vector2.y)<epsilon &&
    fabsf(vector1.z - vector2.z)<epsilon &&
    fabsf(vector1.w - vector2.w)<epsilon;

  vector2 = q2N.mVector;

  bool bCheckTwo = fabsf(vector1.x - vector2.x)<epsilon &&
    fabsf(vector1.y - vector2.y)<epsilon &&
    fabsf(vector1.z - vector2.z)<epsilon &&
    fabsf(vector1.w - vector2.w)<epsilon;

  return bCheckOne || bCheckTwo;

}


/**
 * @function        QuaternionCompareVector3
 * @description     Helper for comparing two Vector3
 * @param[int]      vector1 [Vector3 instance]
 * @param[int]      vector2 [Vector3 instance]
 * @param[int]      epsilon[float tolerance]
 * @param[out]      NA
 * @return          bool - true, if two Vector3 instances are equal; false - otherwise
 */
bool QuaternionCompareVector3(Vector3 vector1, Vector3 vector2, float epsilon)
{
  return fabsf(vector1.x - vector2.x)<epsilon &&
    fabsf(vector1.y - vector2.y)<epsilon &&
    fabsf(vector1.z - vector2.z)<epsilon;
}
