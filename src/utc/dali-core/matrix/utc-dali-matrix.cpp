#include "utc-dali-matrix-common.h"
#include <dlog.h>

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_Matrix_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Matrix_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_Matrix_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Matrix_cleanup(void)
{

}
void MatrixConstructor();
void MatrixConstructorP2();
void MatrixConstructorP3();
void MatrixConstructorP4();
void MatrixCopyConstructor();
void MatrixOperatorAssignment();
void MatrixGetTransformComponents();
void MatrixOrthoNormalize();
void MatrixSetTransformComponents();
void MatrixAsFloat();
void MatrixInvert();
void MatrixInvertTransform();
void MatrixOperatorNotEquals();
void MatrixOperatorEquals();
void MatrixOperatorMultiply();
void MatrixSetIdentity();
void MatrixSetIdentityAndScale();
void MatrixSetGetTranslationWithVector4();
void MatrixSetGetTranslationWithVector3();
void MatrixSetGetXAxis();
void MatrixSetGetYAxis();
void MatrixSetGetZAxis();
void MatrixTranspose();
void MatrixMultiplyTwoMatrices();
void MatrixMultiplyMatrixAndQuaternionOStream();

namespace
{
  enum TEST_CASES_LIST_MATRIX
  {
    MATRIX_CONSTRUCTOR,
    MATRIX_CONSTRUCTOR_P2,
    MATRIX_CONSTRUCTOR_P3,
    MATRIX_CONSTRUCTOR_P4,
    MATRIX_COPY_CONSTRUCTOR,
    MATRIX_OPERATOR_ASSIGNMENT,
    MATRIX_GET_TRANSFORM_COMPONENTS,
    MATRIX_ORTHO_NORMALIZE,
    MATRIX_SET_TRANSFORM_COMPONENTS,
    MATRIX_AS_FLOAT,
    MATRIX_INVERT,
    MATRIX_INVERT_TRANSFORM,
    MATRIX_OPERATOR_NOT_EQUALS,
    MATRIX_OPERATOR_EQUALS,
    MATRIX_OPERATOR_MULTIPLY,
    MATRIX_SET_IDENTITY,
    MATRIX_SET_IDENTITY_AND_SCALE,
    MATRIX_SET_GET_TRANSLATION_WITH_VECTOR4,
    MATRIX_SET_GET_TRANSLATION_WITH_VECTOR3,
    MATRIX_SET_GET_X_AXIS,
    MATRIX_SET_GET_Y_AXIS,
    MATRIX_SET_GET_Z_AXIS,
    MATRIX_TRANSPOSE,
    MATRIX_MULTIPLY_TWO_MATRICES,
    MATRIX_MULTIPLY_MATRIX_AND_QUATERNION_OSTREAM
  };

  struct Matrix_TestApp : public ConnectionTracker
  {
    Matrix_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Matrix_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Matrix_TestApp::Tick );
      mTimer.Start();
    }

    bool Tick()
    {
      mTimer.Stop();
      mApplication.Quit();
      return true;
    }

    void ExcuteTest()
    {
      switch (mTestCase)
      {
        case MATRIX_CONSTRUCTOR:
          MatrixConstructor();
          break;

        case MATRIX_CONSTRUCTOR_P2:
          MatrixConstructorP2();
          break;

        case MATRIX_CONSTRUCTOR_P3:
          MatrixConstructorP3();
          break;

        case MATRIX_CONSTRUCTOR_P4:
          MatrixConstructorP4();
          break;

        case MATRIX_COPY_CONSTRUCTOR:
          MatrixCopyConstructor();
          break;

        case MATRIX_OPERATOR_ASSIGNMENT:
          MatrixOperatorAssignment();
          break;

        case MATRIX_GET_TRANSFORM_COMPONENTS:
          MatrixGetTransformComponents();
          break;

        case MATRIX_ORTHO_NORMALIZE:
          MatrixOrthoNormalize();
          break;

        case MATRIX_SET_TRANSFORM_COMPONENTS:
          MatrixSetTransformComponents();
          break;

        case MATRIX_AS_FLOAT:
          MatrixAsFloat();
          break;

        case MATRIX_INVERT:
          MatrixInvert();
          break;

        case MATRIX_INVERT_TRANSFORM:
          MatrixInvertTransform();
          break;

        case MATRIX_OPERATOR_NOT_EQUALS:
          MatrixOperatorNotEquals();
          break;

        case MATRIX_OPERATOR_EQUALS:
          MatrixOperatorEquals();
          break;

        case MATRIX_OPERATOR_MULTIPLY:
          MatrixOperatorMultiply();
          break;

        case MATRIX_SET_IDENTITY:
          MatrixSetIdentity();
          break;

        case MATRIX_SET_IDENTITY_AND_SCALE:
          MatrixSetIdentityAndScale();
          break;

        case MATRIX_SET_GET_TRANSLATION_WITH_VECTOR4:
          MatrixSetGetTranslationWithVector4();
          break;

        case MATRIX_SET_GET_TRANSLATION_WITH_VECTOR3:
          MatrixSetGetTranslationWithVector3();
          break;

        case MATRIX_SET_GET_X_AXIS:
          MatrixSetGetXAxis();
          break;

        case MATRIX_SET_GET_Y_AXIS:
          MatrixSetGetYAxis();
          break;

        case MATRIX_SET_GET_Z_AXIS:
          MatrixSetGetZAxis();
          break;

        case MATRIX_TRANSPOSE:
          MatrixTranspose();
          break;

        case MATRIX_MULTIPLY_TWO_MATRICES:
          MatrixMultiplyTwoMatrices();
          break;

        case MATRIX_MULTIPLY_MATRIX_AND_QUATERNION_OSTREAM:
          MatrixMultiplyMatrixAndQuaternionOStream();
          break;
      }
    }
    // Data
    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };

} // unnamed namespace


/**
 * ##############################
 * TC Logic Implementation Area.
 * ##############################
 **/

void MatrixConstructor()
{

  Matrix mat;
  float* els = mat.AsFloat();
  DALI_CHECK_FAIL(*els != 0.0f, "Constructor failed");

  DaliLog::PrintPass();
}
void MatrixConstructorP2()
{

  Matrix m2(false);

  bool initialised = true;
  {
    float* els = m2.AsFloat();
    for(size_t idx=0; idx<16; ++idx, ++els)
    {
      if(*els != 0.0f)
        initialised = false;
    }
  }

  DALI_CHECK_FAIL(initialised, "Constructor failed");

  DaliLog::PrintPass();
}
void MatrixConstructorP3()
{
  float matVals[] = { -4.0f,  1.0f,  2.0f,  0.0f,
    -1.0f,  2.0f,  0.0f,  7.0f,
    -4.0f,  4.0f, 4.0f, 11.0f,
    -1.0f, -9.0f, -1.0f, 1.0f };

  Matrix mat(matVals);

  float* els = mat.AsFloat();
  DALI_CHECK_FAIL(*els != -4.0f, "Operator assignment failed");
  DaliLog::PrintPass();
}
void MatrixConstructorP4()
{
  Quaternion q(Quaternion::IDENTITY);
  Matrix m(q);

  DaliLog::PrintPass();
}
void MatrixCopyConstructor()
{
  float rgfpSetValue1[] = {    1.0f, 2.0f, 3.0f, 4.0f,
    5.0f, 6.0f, 7.0f, 8.0f,
    9.0f, 10.0f, 11.0f, 12.0f,
    13.0f, 14.0f, 15.0f, 16.0f
  };

  float *rgfpSetValue2 = NULL;
  bool bResult = false;

  Matrix m1(rgfpSetValue1);

  Matrix m2(m1);
  bResult = true;

  rgfpSetValue2 = m2.AsFloat();

  for(int i = 0; i < DIMENSION_OF_MATRIX; i++)
  {
    bResult &= (rgfpSetValue2[i] == rgfpSetValue1[i]);
  }

  DALI_CHECK_FAIL(!bResult,  "Matrix::CopyConstructor() has been failed, mismatched with matrices." );

  DaliLog::PrintPass();

}
void MatrixOperatorAssignment()
{
  float matVals[] = { -4.0f,  1.0f,  2.0f,  0.0f,
    -1.0f,  2.0f,  0.0f,  7.0f,
    -4.0f,  4.0f, 4.0f, 11.0f,
    -1.0f, -9.0f, -1.0f, 1.0f };

  Matrix m1(matVals);
  Matrix m2 = m1;

  bool bEqual = false;
  if(m1 == m2)
  {
    bEqual = true;
  }
  DALI_CHECK_FAIL(!bEqual,  "The equality operator is failed" );

  DaliLog::PrintPass();
}
void MatrixGetTransformComponents()
{
  float rgfSetVals[] = { -4.0f,  1.0f,  2.0f,  0.0f,
    -1.0f,  2.0f,  0.0f,  7.0f,
    -4.0f,  4.0f, 4.0f, 11.0f,
    -1.0f, -9.0f, -1.0f, 1.0f };
  Matrix mat(rgfSetVals);
  const Vector3 VEC3_TRANSLATION(1.0f, 2.0f, 3.0f), VEC3_SCALE(Vector3::ONE);
  const Quaternion QUAT_ROTATION(Quaternion::IDENTITY);
  Vector3 vec3CurrentScale, vec3CurrentPos;
  Quaternion quatCurrentRot;

  mat.SetTransformComponents( VEC3_SCALE, QUAT_ROTATION, VEC3_TRANSLATION );
  mat.GetTransformComponents( vec3CurrentPos, quatCurrentRot, vec3CurrentScale );
  DALI_CHECK_FAIL(vec3CurrentPos != VEC3_TRANSLATION && vec3CurrentScale != VEC3_SCALE && quatCurrentRot != QUAT_ROTATION,  "Matrix::GetTransformComponents() is failed; retrieved transform value(s) mismatched with set transform value(s)." );

  DaliLog::PrintPass();
}
void MatrixOrthoNormalize()
{
  const Vector3 VEC3_TRANSLATION(1.0f, 2.0f, 3.0f), VEC3_SCALE(Vector3::ONE);
  const Quaternion QUAT_ROTATION( Quaternion::IDENTITY );
  float rgfSetVals[] = { -4.0f,  1.0f,  2.0f,  0.0f,
    -1.0f,  2.0f,  0.0f,  7.0f,
    -4.0f,  4.0f, 4.0f, 11.0f,
    -1.0f, -9.0f, -1.0f, 1.0f };
  Matrix mat(rgfSetVals);
  Matrix matTransform(mat);

  mat.SetTransformComponents( VEC3_SCALE, QUAT_ROTATION, VEC3_TRANSLATION );
  Vector4 vec4InitX(mat.GetXAxis());
  Vector4 vec4InitY(mat.GetYAxis());
  Vector4 vec4InitZ(mat.GetZAxis());

  vec4InitX.Normalize();
  vec4InitY.Normalize();
  vec4InitZ = vec4InitX.Cross( vec4InitY );
  vec4InitY = vec4InitZ.Cross( vec4InitX );
  mat.SetXAxis(Vector3(vec4InitX.AsFloat()));
  mat.SetYAxis(Vector3(vec4InitY.AsFloat()));
  mat.SetZAxis(Vector3(vec4InitZ.AsFloat()));

  matTransform.SetTransformComponents( VEC3_SCALE, QUAT_ROTATION, VEC3_TRANSLATION );
  matTransform.OrthoNormalize();

  Vector4 vec4TargetX(matTransform.GetXAxis()), vec4TargetY(matTransform.GetYAxis()), vec4TargetZ(matTransform.GetZAxis());

  DALI_CHECK_FAIL( vec4TargetX != vec4InitX && vec4TargetY != vec4InitY && vec4TargetZ != vec4InitZ ,  "Matrix::OrthoNormalize() is failed. mismatched with axis positions." );
  DALI_CHECK_FAIL(mat != matTransform,  "Matrix::OrthoNormalize() is failed. mismatched with matrices." );

  DaliLog::PrintPass();
}
void MatrixSetTransformComponents()
{
  float rgfSetVals[] = { -4.0f,  1.0f,  2.0f,  0.0f,
    -1.0f,  2.0f,  0.0f,  7.0f,
    -4.0f,  4.0f, 4.0f, 11.0f,
    -1.0f, -9.0f, -1.0f, 1.0f };
  Matrix mat(rgfSetVals);
  Matrix matOrthoNormal(mat);
  const Vector3 VEC3_TRANSLATION(1.0f, 2.0f, 3.0f), VEC3_SCALE(Vector3::ONE);
  const Quaternion QUAT_ROTATION(Quaternion::IDENTITY);
  Vector3 vec3CurrentScale, vec3CurrentPos;
  Quaternion quatCurrentRot;

  mat.SetInverseTransformComponents( VEC3_SCALE, QUAT_ROTATION, VEC3_TRANSLATION );
  mat.GetTransformComponents( vec3CurrentPos, quatCurrentRot, vec3CurrentScale );
  DALI_CHECK_FAIL(vec3CurrentPos != VEC3_TRANSLATION && vec3CurrentScale != VEC3_SCALE && quatCurrentRot != QUAT_ROTATION,  "Matrix::SetInverseTransformComponents(Vector3, Quaternion, Vector3) is failed. mismatched with set transform value(s)." );

  vec3CurrentPos.Normalize();
  vec3CurrentScale.Normalize();
  quatCurrentRot.Normalize();

  matOrthoNormal.SetInverseTransformComponents( mat.GetXAxis(), mat.GetYAxis(), mat.GetZAxis(), VEC3_TRANSLATION );
  matOrthoNormal.GetTransformComponents( vec3CurrentPos, quatCurrentRot, vec3CurrentScale );
  DALI_CHECK_FAIL(vec3CurrentPos != VEC3_TRANSLATION && vec3CurrentScale != VEC3_SCALE && quatCurrentRot != QUAT_ROTATION,  "Matrix::SetInverseTransformComponents(Vector3,Vector3,Vector3,Vector3) is failed. mismatched with set transform value(s)." );
  DALI_CHECK_FAIL(mat != matOrthoNormal,  "Matrix::SetInverseTransformComponents() is failed. mismatched with matrices." );

  DaliLog::PrintPass();
}
void MatrixAsFloat()
{
  float rgfpSetValue1[] = {    1.0f, 2.0f, 3.0f, 4.0f,
    5.0f, 6.0f, 7.0f, 8.0f,
    9.0f, 10.0f, 11.0f, 12.0f,
    13.0f, 14.0f, 15.0f, 16.0f
  };

  float *rgfpSetValue2 = NULL;
  bool bResult = false;

  Matrix m1(rgfpSetValue1);
  bResult = true;
  rgfpSetValue2 = m1.AsFloat();
  for(int i = 0; i < DIMENSION_OF_MATRIX; i++)
  {
    bResult &= (rgfpSetValue2[i] == rgfpSetValue1[i]);
  }
  DALI_CHECK_FAIL(!bResult,  "Matrix::AsFLoat() has been failed, mismatched with matrices." );

  DaliLog::PrintPass();
}
void MatrixInvert()
{
  float rgfpSetValue1[] = { -4.0f,  1.0f,  2.0f,  0.0f,
    -1.0f,  2.0f,  0.0f,  7.0f,
    -4.0f,  4.0f, 4.0f, 11.0f,
    -1.0f, -9.0f, -1.0f, 1.0f };
  bool bResult = false;
  Matrix m1(rgfpSetValue1);

  bResult = m1.Invert();
  DALI_CHECK_FAIL(!bResult,  "Dali::Matrix::Invert is Failed" );

  DaliLog::PrintPass();
}
void MatrixInvertTransform()
{
  Vector3 vecPosition(1.0f, 2.0f, 3.0f);
  Matrix m0;
  m0.SetIdentity();
  m0.SetTransformComponents( Vector3::ONE, Quaternion::IDENTITY, vecPosition );
  bool bInverted = m0.Invert();
  DALI_CHECK_FAIL(!bInverted,  "Dali::Matrix::Invert is Failed" );

  Matrix m1;
  Matrix m3;
  m1.SetIdentity();
  m1.SetTransformComponents( Vector3::ONE, Quaternion::IDENTITY, vecPosition );
  m1.InvertTransform(m3);
  DALI_CHECK_FAIL(m0 != m3,  "Dali::Matrix::InvertTransform is Failed" );

  DaliLog::PrintPass();
}
void MatrixOperatorNotEquals()
{
  float rgfpSetValue1[] = { 5.0f,  0.0f,  0.0f,  0.0f,
    0.0f,  6.0f,  0.0f,  0.0f,
    0.0f,  0.0f,  7.0f,  0.0f,
    0.0f,  0.0f,  0.0f,  8.0f };

  Matrix m1 = Matrix::IDENTITY;
  Matrix m2(rgfpSetValue1);
  bool bNotEqual = false;
  if(m1 != m2)
  {
    bNotEqual = true;
  }
  DALI_CHECK_FAIL(!bNotEqual,  "The inequality operator is failed" );

  DaliLog::PrintPass();
}
void MatrixOperatorEquals()
{
  float rgfpSetValue1[] = { 1.0f,  0.0f,  0.0f,  0.0f,
    0.0f,  1.0f,  0.0f,  0.0f,
    0.0f,  0.0f,  1.0f, 0.0f,
    0.0f,  0.0f,  0.0f,  1.0f };

  Matrix m1 = Matrix::IDENTITY;
  Matrix m2(rgfpSetValue1);
  bool bEqual = false;
  if(m1 == m2)
  {
    bEqual = true;
  }
  DALI_CHECK_FAIL(!bEqual,  "The equality operator is failed" );

  DaliLog::PrintPass();
}
void MatrixOperatorMultiply()
{
  float rgfpSetValue1[] = { 4.0f,  0.0f,  0.0f,  0.0f,
    0.0f,  5.0f,  0.0f,  0.0f,
    0.0f,  0.0f,  10.0f, 0.0f,
    0.0f,  0.0f,  0.0f,  1.0f };

  Matrix m1(rgfpSetValue1);
  Vector4 vector4value(2.0f, 5.0f, 4.0f, 0.0f);
  Vector4 vector4Chk(8.0f, 25.0f, 40.0f, 0.0f);

  Vector4 vector4Res = m1 * vector4value;
  DALI_CHECK_FAIL(vector4Res != vector4Chk,  "The multiplication operator is Failed." );

  DaliLog::PrintPass();
}
void MatrixSetIdentity()
{
  float rgfpSetValue1[] = {    0.0f,  1.0f,  2.0f,  3.0f,
    4.0f,  5.0f,  6.0f,  7.0f,
    8.0f,  9.0f, 10.0f, 11.0f,
    12.0f, 13.0f, 14.0f, 15.0f  };

  Matrix m1(rgfpSetValue1);
  m1.SetIdentity();
  DALI_CHECK_FAIL(m1 != Matrix::IDENTITY,  "Dali::Matrix::SetIdentity is Failed." );

  DaliLog::PrintPass();
}
void MatrixSetIdentityAndScale()
{
  float rgfpSetValue1[] = {    0.0f,  1.0f,  2.0f,  3.0f,
    4.0f,  5.0f,  6.0f,  7.0f,
    8.0f,  9.0f,  10.0f, 11.0f,
    12.0f,  13.0f,  14.0f, 15.0f };

  float rgfpSetValue2[] = {    4.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 4.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 4.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f };

  const Vector3 VEC3_SCALE_VALUE(4.0f, 4.0f, 4.0f);
  Matrix m1(rgfpSetValue1);
  Matrix m2(rgfpSetValue2);

  m1.SetIdentityAndScale(VEC3_SCALE_VALUE);
  DALI_CHECK_FAIL(m1 != m2,  "Dali::Matrix::SetIdentityAndScale is Failed." );

  DaliLog::PrintPass();
}
void MatrixSetGetTranslationWithVector4()
{
  Matrix m1;
  Vector4 vector4set(2.0f, 3.0f, 4.0f, 5.0f);
  Vector4 vector4get;

  m1.SetTranslation(vector4set);
  vector4get = m1.GetTranslation();
  DALI_CHECK_FAIL(vector4get != vector4set,  "Dali::Matrix::SetTranslation and Dali::Matrix::GetTranslation is Failed." );

  DaliLog::PrintPass();
}
void MatrixSetGetTranslationWithVector3()
{
  Matrix m1;
  Vector3 vector3set(2.0f, 3.0f, 4.0f);
  Vector3 vector3get;

  m1.SetTranslation(vector3set);
  vector3get = m1.GetTranslation3();
  DALI_CHECK_FAIL(vector3get != vector3set,  "Dali::Matrix::SetTranslation and Dali::Matrix::GetTranslation3 are failed." );

  DaliLog::PrintPass();
}
void MatrixSetGetXAxis()
{
  bool bXAxis = false;

  bXAxis = MatrixSetGetAxis(AXIS_X);

  DALI_CHECK_FAIL(!bXAxis,  "UtcDaliMatrixSetGetXAxis is Failed." );
  DaliLog::PrintPass();
}
void MatrixSetGetYAxis()
{
  bool bYAxis = false;
  bYAxis = MatrixSetGetAxis(AXIS_Y);

  DALI_CHECK_FAIL(!bYAxis,  "UtcDaliMatrixSetGetYAxis is Failed." );
  DaliLog::PrintPass();
}
void MatrixSetGetZAxis()
{
  bool bZAxis = false;

  bZAxis = MatrixSetGetAxis(AXIS_Z);
  DALI_CHECK_FAIL(!bZAxis,  "UtcDaliMatrixSetGetZAxis is Failed." );

  DaliLog::PrintPass();
}
void MatrixTranspose()
{
  float rgfpSetValue1[] = {    0.0f,  1.0f,  2.0f,  3.0f,
    4.0f,  5.0f,  6.0f,  7.0f,
    8.0f,  9.0f, 10.0f, 11.0f,
    12.0f, 13.0f, 14.0f, 15.0f };

  bool bSuccess = true;
  const int ROW_COUNT = 4, COLUMN_COUNT = 4;
  Matrix m1(rgfpSetValue1);
  m1.Transpose();
  for (int x = 0; x < ROW_COUNT; ++x)
  {
    for (int y = 0; y < COLUMN_COUNT;++y)
    {
      bSuccess &= ((m1.AsFloat()[x+y*ROW_COUNT] == rgfpSetValue1[x*COLUMN_COUNT+y]));
    }
  }

  DALI_CHECK_FAIL(!bSuccess,  "Dali::Matrix::Transpose is Failed." );

  DaliLog::PrintPass();
}
void MatrixMultiplyTwoMatrices()
{
  Matrix matrixResult(false), matrixResultCalculated(false);
  float fValue0 = 0.0f, fValue1 = 0.0f,fValue2 = 0.0f, fValue3 = 0.0f;
  int nPos = 0, nPos1 = 0, nPos2 = 0, nPos3 = 0;

  int nRowCol = sqrt(DIMENSION_OF_MATRIX);
  bool bResultForMultiply = false;
  float* rgpFloatResult = matrixResultCalculated.AsFloat();
  int nIndex = 0;

  float rgFloatValuesOne[] = { 5.0f,  1.0f,  2.0f,  3.0f,
    4.0f,  5.0f,  6.0f,  7.0f,
    8.0f,  9.0f, 10.0f, 11.0f,
    12.0f, 13.0f, 14.0f, 15.0f };
  const Matrix MATRIX_ONE(rgFloatValuesOne);

  float rgFloatValuesTwo[] = { -4.0f,  1.0f,  2.0f,  0.0f,
    -1.0f,  2.0f,  0.0f,  7.0f,
    -4.0f,  4.0f, 4.0f, 11.0f,
    -1.0f, -9.0f, -1.0f, 1.0f };
  const Matrix MATRIX_TWO(rgFloatValuesTwo);

  //Calculatation of multiplication of two matrices using mathematical formula
  for( nIndex = 0; nIndex < nRowCol; nIndex++ )
  {
    nPos1 = nPos + 1;
    nPos2 = nPos + 2;
    nPos3 = nPos + 3;

    fValue0 = rgFloatValuesOne[nPos];
    fValue1 = rgFloatValuesOne[nPos1];
    fValue2 = rgFloatValuesOne[nPos2];
    fValue3 = rgFloatValuesOne[nPos3];

    rgpFloatResult[nPos]  = (fValue0 * rgFloatValuesTwo[0]) + (fValue1 * rgFloatValuesTwo[4]) + (fValue2 * rgFloatValuesTwo[8]) + (fValue3 * rgFloatValuesTwo[12]);
    rgpFloatResult[nPos1] = (fValue0 * rgFloatValuesTwo[1]) + (fValue1 * rgFloatValuesTwo[5]) + (fValue2 * rgFloatValuesTwo[9]) + (fValue3 * rgFloatValuesTwo[13]);
    rgpFloatResult[nPos2] = (fValue0 * rgFloatValuesTwo[2]) + (fValue1 * rgFloatValuesTwo[6]) + (fValue2 * rgFloatValuesTwo[10])+ (fValue3 * rgFloatValuesTwo[14]);
    rgpFloatResult[nPos3] = (fValue0 * rgFloatValuesTwo[3]) + (fValue1 * rgFloatValuesTwo[7]) + (fValue2 * rgFloatValuesTwo[11])+  (fValue3 * rgFloatValuesTwo[15]);

    nPos = nPos + nRowCol;
  }
  matrixResultCalculated = Matrix( rgpFloatResult );
  Matrix::Multiply(matrixResult, MATRIX_ONE, MATRIX_TWO);
  bResultForMultiply = MatrixCheckEquals( matrixResult, matrixResultCalculated, MATRIX_EPSILON );
  DALI_CHECK_FAIL( !bResultForMultiply, "Matrix::Multiply for two matrices is failed." );

  DaliLog::PrintPass();
}
void MatrixMultiplyMatrixAndQuaternionOStream()
{
  const Matrix MATRIX = Matrix::IDENTITY;
  Matrix matrixResult(false);
  bool bResultCheck = false;
  float fDegree = 45.0f;

  string strResultExpected = "[ 1, 0, 0, 0, 0, 0.707107, 0.707107, 0, 0, -0.707107, 0.707107, 0, 0, 0, 0, 1 ]";

  float rgResultExpected[] = { 1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.707f, 0.707f, 0.0f,
    0.0f, -0.707f,  0.707f, 0.0f,
    0.0f, 0.0f,   0.0f,  1.0f };
  Matrix matrixResultExpected = Matrix(rgResultExpected);

  const Quaternion QUATERNION(Radian(Degree(fDegree)), Vector3::XAXIS);
  Matrix matrixQuaternion( QUATERNION );

  bResultCheck = MatrixCheckEquals( matrixQuaternion, matrixResultExpected, MATRIX_EPSILON );
  DALI_CHECK_FAIL( !bResultCheck, "Matrix::Matrix(const Quaternion&) is failed." );

  Matrix::Multiply(matrixResult, MATRIX, QUATERNION);

  bResultCheck = false;
  bResultCheck = MatrixCheckEquals( matrixResult, matrixQuaternion, MATRIX_EPSILON );

  DALI_CHECK_FAIL( !bResultCheck, "Matrix::Multiply for a matrix and a quaternion is failed." );

  std::ostringstream oStringStream;

  oStringStream << matrixResult;

  DALI_CHECK_FAIL( oStringStream.str() != strResultExpected, "OStreamOperator is failed to print expected result for matrix." );

  DaliLog::PrintPass();
}
/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase            UtcDaliMatrixConstructorP
 * @since_tizen         2.4
 * @description         Gets the position, scale and rotation components from the given transform matrix.
 */
int UtcDaliMatrixConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_CONSTRUCTOR );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixConstructorP2
 * @since_tizen         2.4
 * @description         Gets the position, scale and rotation components from the given transform matrix.
 */
int UtcDaliMatrixConstructorP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_CONSTRUCTOR_P2 );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixConstructorP3
 * @since_tizen         2.4
 * @description         Gets the position, scale and rotation components from the given transform matrix.
 */
int UtcDaliMatrixConstructorP3(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_CONSTRUCTOR_P3 );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixConstructorP4
 * @since_tizen         2.4
 * @description         Gets the position, scale and rotation components from the given transform matrix.
 */
int UtcDaliMatrixConstructorP4(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_CONSTRUCTOR_P4 );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixCopyConstructorP
 * @since_tizen         2.4
 * @description         Gets the position, scale and rotation components from the given transform matrix.
 */
int UtcDaliMatrixCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_COPY_CONSTRUCTOR );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixOperatorAssignmentP
 * @since_tizen         2.4
 * @description         Gets the position, scale and rotation components from the given transform matrix.
 */
int UtcDaliMatrixOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_OPERATOR_ASSIGNMENT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixGetTransformComponentsP
 * @since_tizen         2.4
 * @description         Gets the position, scale and rotation components from the given transform matrix.
 */
int UtcDaliMatrixGetTransformComponentsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_GET_TRANSFORM_COMPONENTS);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixOrthoNormalizeP
 * @since_tizen         2.4
 * @description         Makes the axes of the matrix orthogonal to each other and of unit length.
 */
int UtcDaliMatrixOrthoNormalizeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_ORTHO_NORMALIZE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixSetTransformComponentsP
 * @since_tizen         2.4
 * @description         Sets a matrix to contain the inverse of the position, scale and rotation components or, \n
 */
int UtcDaliMatrixSetTransformComponentsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_SET_TRANSFORM_COMPONENTS);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixAsFloatP
 * @since_tizen         2.4
 * @description         Returns the contents of the matrix as an array of 16 floats.
 */
int UtcDaliMatrixAsFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_AS_FLOAT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixInvertP
 * @since_tizen         2.4
 * @description         Generic brute force Matrix Invert.
 */
int UtcDaliMatrixInvertP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_INVERT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixInvertTransformP
 * @since_tizen         2.4
 * @description         Invert a transform Matrix.
 */
int UtcDaliMatrixInvertTransformP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_INVERT_TRANSFORM);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixOperatorNotEqualsP
 * @since_tizen         2.4
 * @description         The inequality operator.
 */
int UtcDaliMatrixOperatorNotEqualsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_OPERATOR_NOT_EQUALS);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixOperatorEqualsP
 * @since_tizen         2.4
 * @description         The equality operator.
 */
int UtcDaliMatrixOperatorEqualsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_OPERATOR_EQUALS);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixOperatorMultiplyP
 * @since_tizen         2.4
 * @description         The multiplication operator.
 */
int UtcDaliMatrixOperatorMultiplyP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_OPERATOR_MULTIPLY);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixSetIdentityP
 * @since_tizen         2.4
 * @description         Sets this matrix to be an identity matrix.
 */
int UtcDaliMatrixSetIdentityP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_SET_IDENTITY);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixSetIdentityAndScaleP
 * @since_tizen         2.4
 * @description         Sets this matrix to be an identity matrix with scale.
 */
int UtcDaliMatrixSetIdentityAndScaleP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_SET_IDENTITY_AND_SCALE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixSetGetTranslationWithVector4P
 * @since_tizen         2.4
 * @description         Sets and Gets the translation.
 */
int UtcDaliMatrixSetGetTranslationWithVector4P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_SET_GET_TRANSLATION_WITH_VECTOR4);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixSetGetTranslationWithVector3P
 * @since_tizen         2.4
 * @description         Sets and Gets x,y and z components of the translation as a Vector3.
 */
int UtcDaliMatrixSetGetTranslationWithVector3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_SET_GET_TRANSLATION_WITH_VECTOR3);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixSetGetXAxisP
 * @since_tizen         2.4
 * @description         Sets the x axis.
 */
int UtcDaliMatrixSetGetXAxisP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_SET_GET_X_AXIS);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixSetGetYAxisP
 * @since_tizen         2.4
 * @description         Sets the y axis.
 */
int UtcDaliMatrixSetGetYAxisP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_SET_GET_Y_AXIS);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixSetGetZAxisP
 * @since_tizen         2.4
 * @description         Sets the z axis.
 */
int UtcDaliMatrixSetGetZAxisP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_SET_GET_Z_AXIS);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixTransposeP
 * @since_tizen         2.4
 * @description         Swaps the rows to columns.
 */
int UtcDaliMatrixTransposeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_TRANSPOSE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixMultiplyTwoMatricesP
 * @since_tizen         2.4
 * @description         Multiply two matrices and store the result onto third.
 */
int UtcDaliMatrixMultiplyTwoMatricesP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_MULTIPLY_TWO_MATRICES);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliMatrixMultiplyMatrixAndQuaternionOStreamP
 * @since_tizen         2.4
 * @description         Multiply a matrix and quaternion and store the result onto third and Print the result with OStreamOperator
 */
int UtcDaliMatrixMultiplyMatrixAndQuaternionOStreamP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix_TestApp testApp( application, MATRIX_MULTIPLY_MATRIX_AND_QUATERNION_OSTREAM);
  application.MainLoop();
  return test_return_value;
}
