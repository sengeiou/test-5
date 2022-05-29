#ifndef _UTC_DALI_CONSTRAINT_COMMON_H_
#define _UTC_DALI_CONSTRAINT_COMMON_H_

#include "dali-common.h"


using namespace Dali;

#define SUITE_NAME "CONSTRAINT_UTC"

/** Global variable declarations **/
const float CONSTRAINT_EPSILON = 0.0001f;
const int   CONSTRAINT_INVALID_STRING_LENGTH = 0;
const bool  CONSTRAINT_BOOL_START(true), CONSTRAINT_BOOL_TARGET(false);
const int   CONSTRAINT_INT_START(1), CONSTRAINT_INT_TARGET(2);
const float CONSTRAINT_FLOAT_START(1.0f), CONSTRAINT_FLOAT_TARGET(2.0f);
const Vector2 CONSTRAINT_VEC2_START(6.0f, 6.0f), CONSTRAINT_VEC2_TARGET(100.0f, 100.0f);
const Vector3 CONSTRAINT_VEC3_START(2.0f, 2.0f, 2.0f), CONSTRAINT_VEC3_TARGET(6.0f, 6.0f, 6.0f);
const Vector4 CONSTRAINT_VEC4_START(2.0f, 2.0f, 2.0f, 2.0f), CONSTRAINT_VEC4_TARGET(3.0f, 3.0f, 3.0f, 3.0f);
const Quaternion CONSTRAINT_QT_START(Radian(1.0f), Vector3::YAXIS);
const Quaternion CONSTRAINT_QT_TARGET(Radian(2.0f), Vector3::YAXIS);

/**
 * @function         ConstraintTypeEquals
 * @description      A helper for fuzzy-comparing different property type values
 * @param[in]        tValue1 the first property type value
 * @param[in]        tValue2 the second property type value
 * @param[in]        fEpsilon difference threshold[not effective
 * @param[out]       NA
 * @return           true if difference is smaller than fEpsilon threshold, false otherwise
 */
template<typename type>
inline bool ConstraintTypeEquals(type tValue1, type tValue2, float fEpsilon);

/**
 * @function         ConstraintTypeEquals<bool>
 * @description      A helper for fuzzy-comparing boolean values
 * @param[in]        bValue1 the first boolean value
 * @param[in]        bValue2 the second boolean value
 * @param[in]        fEpsilon difference threshold[not effective
 * @param[out]       NA
 * @return           true if there is no difference, false otherwise
 */
  template<>
inline bool ConstraintTypeEquals<bool>(bool bValue1, bool bValue2, float fEpsilon)
{
  return bValue1 == bValue2;
}

/**
 * @function         ConstraintTypeEquals<int>
 * @description      A helper for fuzzy-comparing integer values
 * @param[in]        nValue1 the first integer value
 * @param[in]        nValue2 the second integer value
 * @param[in]        fEpsilon difference threshold
 * @param[out]       NA
 * @return           true if difference is smaller than fEpsilon threshold, false otherwise
 */
  template<>
inline bool ConstraintTypeEquals<int>(int nValue1, int nValue2, float fEpsilon)
{
  return fabsf(nValue1 - nValue2) < fEpsilon;
}

/**
 * @function         ConstraintTypeEquals<unsigned int>
 * @description      A helper for fuzzy-comparing unsigned integer values
 * @param[in]        uValue1 the first unsigned integer value
 * @param[in]        uValue2 the second unsigned integer value
 * @param[in]        fEpsilon difference threshold
 * @param[out]       NA
 * @return           true if difference is smaller than fEpsilon threshold, false otherwise
 */
  template<>
inline bool ConstraintTypeEquals<unsigned int>(unsigned int uValue1, unsigned int uValue2, float fEpsilon)
{
  return fabsf(uValue1 - uValue2) < fEpsilon;
}

/**
 * @function         ConstraintTypeEquals<float>
 * @description      A helper for fuzzy-comparing float values
 * @param[in]        fValue1 the first float value
 * @param[in]        fValue2 the second float value
 * @param[in]        fEpsilon difference threshold
 * @param[out]       NA
 * @return           true if difference is smaller than fEpsilon threshold, false otherwise
 */
  template<>
inline bool ConstraintTypeEquals<float>(float fValue1, float fValue2, float fEpsilon)
{
  return fabsf(fValue1 - fValue2) < fEpsilon;
}

/**
 * @function         ConstraintTypeEquals<Vector2>
 * @description      A helper for fuzzy-comparing Vector2 objects
 * @param[in]        vector1 the first vector2 object
 * @param[in]        vector2 the second vector2 object
 * @param[in]        fEpsilon difference threshold
 * @param[out]       NA
 * @return           true if difference is smaller than fEpsilon threshold, false otherwise
 */
  template<>
inline bool ConstraintTypeEquals<Vector2>(Vector2 vector1, Vector2 vector2, float fEpsilon)
{
  return fabsf(vector1.x - vector2.x) < fEpsilon && fabsf(vector1.y - vector2.y) < fEpsilon;
}

/**
 * @function         ConstraintTypeEquals<Vector3>
 * @description      A helper for fuzzy-comparing vector3 objects
 * @param[in]        vector1 the first vector3 object
 * @param[in]        vector2 the second vector3 object
 * @param[in]        fEpsilon difference threshold
 * @param[out]       NA
 * @return           true if difference is smaller than fEpsilon threshold, false otherwise
 */
  template<>
inline bool ConstraintTypeEquals<Vector3>(Vector3 vector1, Vector3 vector2, float fEpsilon)
{
  return fabsf(vector1.x - vector2.x) < fEpsilon &&
    fabsf(vector1.y - vector2.y) < fEpsilon &&
    fabsf(vector1.z - vector2.z) < fEpsilon;
}

/**
 * @function         ConstraintTypeEquals<Vector4>
 * @description      A helper for fuzzy-comparing vector4 objects
 * @param[in]        vector1 the first vector4 object
 * @param[in]        vector2 the second vector4 object
 * @param[in]        fEpsilon difference threshold
 * @param[out]       NA
 * @return           true if difference is smaller than fEpsilon threshold, false otherwise
 */
  template<>
inline bool ConstraintTypeEquals<Vector4>(Vector4 vector1, Vector4 vector2, float fEpsilon)
{
  return fabsf(vector1.x - vector2.x) < fEpsilon &&
    fabsf(vector1.y - vector2.y) < fEpsilon &&
    fabsf(vector1.z - vector2.z) < fEpsilon &&
    fabsf(vector1.w - vector2.w) < fEpsilon;
}

/**
 * @function         ConstraintTypeEquals<Matrix>
 * @description      A helper for fuzzy-comparing matrix objects
 * @param[in]        matrix1 the first matrix object
 * @param[in]        matrix2 the second matrix object
 * @param[in]        fEpsilon difference threshold
 * @param[out]       NA
 * @return           true if there is no difference, false otherwise
 */
  template<>
inline bool ConstraintTypeEquals<Matrix>(Matrix matrix1, Matrix matrix2, float fEpsilon)
{
  return matrix1 == matrix2;
}

/**
 * @function         ConstraintTypeEquals<Matrix3>
 * @description      A helper for fuzzy-comparing matrix3 objects
 * @param[in]        matrix1 the first matrix3 object
 * @param[in]        matrix2 the second matrix3 object
 * @param[in]        fEpsilon difference threshold
 * @param[out]       NA
 * @return           true if there is no difference, false otherwise
 */
  template<>
inline bool ConstraintTypeEquals<Matrix3>(Matrix3 matrix1, Matrix3 matrix2, float fEpsilon)
{
  return matrix1 == matrix2;
}

/**
 * @function         ConstraintTypeEquals<Quaternion>
 * @description      A helper for fuzzy-comparing quaternion objects
 * @param[in]        quaternion1 the first quaternion object
 * @param[in]        quaternion2 the second quaternion object
 * @param[in]        fEpsilon difference threshold
 * @param[out]       NA
 * @return           true if difference is smaller than fEpsilon threshold, false otherwise
 */
  template<>
inline bool ConstraintTypeEquals<Quaternion>(Quaternion quaternion1, Quaternion quaternion2, float fEpsilon)
{
  Quaternion q2N = -quaternion2;
  return ConstraintTypeEquals<Vector4>(quaternion1.mVector, quaternion2.mVector, fEpsilon) || ConstraintTypeEquals<Vector4>(quaternion1.mVector, q2N.mVector, fEpsilon);
}


/** Helper to create handle object **/
bool ConstraintCreateHandle(Actor&, bool);

/** Template structure for different type value **/
template<class type>
struct STConstraintTypeValue
{
  STConstraintTypeValue() : tValue()
  {
  }

  STConstraintTypeValue(type tValue) : tValue(tValue)
  {
  }

  //@NOTE: new operators overloaded added since dali 1.0.41
  void operator()(int &tCurrent, const PropertyInputContainer& container)
  {
    if(container.Size() > 0)
    {
      tCurrent = container[0]->GetInteger();
    }
    else
    {
      tCurrent = tValue;
    }
  }

  void operator()(bool &tCurrent, const PropertyInputContainer& container)
  {
    if(container.Size() > 0)
    {
      tCurrent = container[0]->GetBoolean();
    }
    else
    {
      tCurrent = tValue;
    }
  }

  void operator()(float &tCurrent, const PropertyInputContainer& container)
  {
    if(container.Size() > 0)
    {
      tCurrent = container[0]->GetFloat();
    }
    else
    {
      tCurrent = tValue;
    }
  }

  void operator()(Vector2 &tCurrent, const PropertyInputContainer& container)
  {
    if(container.Size() > 0)
    {
      tCurrent = container[0]->GetVector2();
    }
    else
    {
      tCurrent = tValue;
    }
  }

  void operator()(Vector3 &tCurrent, const PropertyInputContainer& container)
  {
    if(container.Size() > 0)
    {
      tCurrent = container[0]->GetVector3();
    }
    else
    {
      tCurrent = tValue;
    }
  }

  void operator()(Vector4 &tCurrent, const PropertyInputContainer& container)
  {
    if(container.Size() > 0)
    {
      tCurrent = container[0]->GetVector4();
    }
    else
    {
      tCurrent = tValue;
    }
  }

  void operator()(Matrix &tCurrent, const PropertyInputContainer& container)
  {
    if(container.Size() > 0)
    {
      tCurrent = container[0]->GetMatrix();
    }
    else
    {
      tCurrent = tValue;
    }
  }

  void operator()(Matrix3 &tCurrent, const PropertyInputContainer& container)
  {
    if(container.Size() > 0)
    {
      tCurrent = container[0]->GetMatrix3();
    }
    else
    {
      tCurrent = tValue;
    }
  }

  void operator()(Quaternion &tCurrent, const PropertyInputContainer& container)
  {
    if(container.Size() > 0)
    {
      tCurrent = container[0]->GetQuaternion();
    }
    else
    {
      tCurrent = tValue;
    }
  }

  type tValue;
};


#endif  //_UTC_DALI_CONSTRAINT_COMMON_H_
