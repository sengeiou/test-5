#include "utc-dali-quaternion-common.h"

int gRenderCountQuaternion; /** Render count **/
Actor gActorQuaternion;
bool gConstructCheck=false;
Quaternion gQuaternion1;
Quaternion gQuaternion2;
Quaternion gQuaternion3;
Quaternion gQuaternion4;
float gDistance, gReverseCount;
Vector3 gVector30;
Vector3 gVector3;
Vector4 gVector40;
Vector4 gVector4;

/**
 * ##############################
 * TC Logic Implementation Area.
 * ##############################
 **/
void QuaternionByFloat()
{
  const int ANGLE = 60.0f, ANGLE_I = 30.0f, ANGLE_J = 50.f, ANGLE_K = 20.0f;
  const float COSINE_THETA_BY_TWO = cos((ANGLE * PI_OVER_180)/2.0f);
  const float I_BY_SINE_THETA = sin(ANGLE_I * PI_OVER_180);
  const float J_BY_SINE_THETA = sin(ANGLE_J * PI_OVER_180);
  const float K_BY_SINE_THETA = sin(ANGLE_K * PI_OVER_180);

  Quaternion quaternionConstructorWithFloat(COSINE_THETA_BY_TWO , I_BY_SINE_THETA , J_BY_SINE_THETA, K_BY_SINE_THETA);

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionConstructorWithFloat);
}
void VTQuaternionByFloat001()
{
  const int ANGLE = 60.0f, ANGLE_I = 30.0f, ANGLE_J = 50.f, ANGLE_K = 20.0f;
  const float COSINE_THETA_BY_TWO = cos((ANGLE * PI_OVER_180)/2.0f);
  const float I_BY_SINE_THETA = sin(ANGLE_I * PI_OVER_180);
  const float J_BY_SINE_THETA = sin(ANGLE_J * PI_OVER_180);
  const float K_BY_SINE_THETA = sin(ANGLE_K * PI_OVER_180);

  Quaternion quaternionConstructorWithFloat(COSINE_THETA_BY_TWO , I_BY_SINE_THETA , J_BY_SINE_THETA, K_BY_SINE_THETA);
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  DALI_CHECK_FAIL(quaternionCurrentRot != quaternionConstructorWithFloat, "Quaternion::Quaternion(float,float,float,float) is failed" );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionByVector()
{
  const int X = 1.1f, Y = 1.2f, Z = 0.5f, W = 3.1f;
  const Vector4 vect4(X, Y, Z, W);
  Quaternion quaternionConstructorWithVec4(vect4);

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionConstructorWithVec4);
}
void VTQuaternionByVector001()
{
  const int X = 1.1f, Y = 1.2f, Z = 0.5f, W = 3.1f;
  const Vector4 vect4(X, Y, Z, W);
  Quaternion quaternionConstructorWithVec4(vect4);
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();

  DALI_CHECK_FAIL(quaternionCurrentRot != quaternionConstructorWithVec4, "Quaternion::Quaternion(const Vector4 &) is failed" );
  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionByAngleVector4Axis()
{
  const int X = 1.1f, Y = 1.2f, Z = 0.5f;
  const float ANGLE_ROTATION = 120.0f;
  const int SCALING_FACTOR = 10;
  Vector3 vect3(X , Y, Z);

  Quaternion quaternionConstructorByAngleVec4Axis(Radian(ANGLE_ROTATION * SCALING_FACTOR), vect3);

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionConstructorByAngleVec4Axis);
}
void VTQuaternionByAngleVector4Axis001()
{
  const int X = 1.1f, Y = 1.2f, Z = 0.5f;
  const float ANGLE_ROTATION = 120.0f;
  const int SCALING_FACTOR = 10;
  Vector3 vect3(X , Y, Z);
  Quaternion quaternionConstructorByAngleVec4Axis(Radian(ANGLE_ROTATION * SCALING_FACTOR), vect3);

  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  DALI_CHECK_FAIL(quaternionCurrentRot != quaternionConstructorByAngleVec4Axis, "Quaternion::Quaternion(float,const Vector4 &) is failed" );
  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionByEulerAngles()
{
  const float MIN_ANGLE_PITCH = 4.4f, MIN_ANGLE_YAW = 8.9f, MAX_ANGLE_ROLL = 9.8f;
  const float PITCH_SCALING_FACTOR = 1.2f;
  Radian radianPitch(MIN_ANGLE_PITCH * PITCH_SCALING_FACTOR);
  Radian radianYaw(MIN_ANGLE_YAW);
  Radian radianRoll(MAX_ANGLE_ROLL);

  Quaternion quaternionConstructorByEularAngles(radianPitch, radianYaw , radianRoll );

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionConstructorByEularAngles);
}
void VTQuaternionByEulerAngles001()
{
  const float MIN_ANGLE_PITCH = 4.4f, MIN_ANGLE_YAW = 8.9f, MAX_ANGLE_ROLL = 9.8f;
  const float PITCH_SCALING_FACTOR = 1.2f;
  Radian radianPitch(MIN_ANGLE_PITCH * PITCH_SCALING_FACTOR);
  Radian radianYaw(MIN_ANGLE_YAW);
  Radian radianRoll(MAX_ANGLE_ROLL);
  Quaternion quaternionConstructorByEularAngles(radianPitch, radianYaw , radianRoll );

  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  DALI_CHECK_FAIL(quaternionCurrentRot != quaternionConstructorByEularAngles, "Quaternion::Quaternion(radian,radian,radian) is failed" );
  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionAsVector()
{
  const float MIN_ANGLE_PITCH = 4.4f, MIN_ANGLE_YAW = 8.9f, MAX_ANGLE_ROLL = 9.8f,MAX_ANGLE_ROLL1 = 9.8f ;
  const int PITCH_SCALING_FACTOR = 1.2f;

  Quaternion testQuaternionConstructor(MIN_ANGLE_PITCH  * PITCH_SCALING_FACTOR, MIN_ANGLE_YAW , MAX_ANGLE_ROLL, MAX_ANGLE_ROLL1 );

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "Stage::GetCurrent is not created " );

  stage.Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(testQuaternionConstructor);
}
void VTQuaternionAsVector001()
{
  const float MIN_ANGLE_PITCH = 4.4f, MIN_ANGLE_YAW = 8.9f, MAX_ANGLE_ROLL = 9.8f,MAX_ANGLE_ROLL1 = 9.8f ;
  const int PITCH_SCALING_FACTOR = 1.2f;
  Quaternion testQuaternionConstructor(MIN_ANGLE_PITCH  * PITCH_SCALING_FACTOR, MIN_ANGLE_YAW , MAX_ANGLE_ROLL, MAX_ANGLE_ROLL1 );
  Vector4 valTestQuaternionVector = testQuaternionConstructor.AsVector();

  Stage stage = Stage::GetCurrent();
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  DALI_CHECK_FAIL(quaternionCurrentRot.AsVector() != valTestQuaternionVector, "Quaternion::AsVector() is failed" );

  stage.Remove(gActorQuaternion);
  DaliLog::PrintPass();
}
void QuaternionConstructorByMatrix()
{
  Matrix rotMatrix(Matrix::IDENTITY);

  Quaternion quaternionConstructorByMatrix( rotMatrix );

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed " );

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "Stage::GetCurrent is not created " );

  stage.Add(actor);
  actor.SetOrientation(quaternionConstructorByMatrix);
  Quaternion quaternionCurrentRot = actor.GetCurrentOrientation();

  DALI_CHECK_FAIL(quaternionCurrentRot != quaternionConstructorByMatrix, "Quaternion::Quaternion(const Matrix &) is failed, " );
  stage.Remove(actor);

  DaliLog::PrintPass();
}
void QuaternionConstructorByOrthonormalAxes()
{
  const float ANGLE_ROTATION = 45.0f;

  Vector3 Vec3XAxis( 1.0f, 1.0f, 0.0f );
  Vec3XAxis.Normalize();
  Vector3 Vec3YAxis( -1.0f, 1.0f, 0.0f );
  Vec3YAxis.Normalize();
  Vector3 Vec3ZAxis;
  Vec3ZAxis = Vec3XAxis.Cross(Vec3YAxis);
  Vec3ZAxis.Normalize();

  Quaternion quaternionConstructorByOrthonormalAxes( Vec3XAxis, Vec3YAxis, Vec3ZAxis );

  DALI_CHECK_FAIL(Quaternion(Radian(Degree(ANGLE_ROTATION)), Vector3::ZAXIS) != quaternionConstructorByOrthonormalAxes, " Quaternion::Quaternion(const Vector3 &, const Vector3 &, const Vector3 &) is failed" );

  DaliLog::PrintPass();
}
void QuaternionConjugate()
{
  const float ANGLE = 20.0f;
  const float COSINE_THETA_BY_TWO = cos((ANGLE * PI_OVER_180)/2.0f);
  const float MIN_X = 0.045f, MIN_Y = 0.443f, MIN_Z = 0.432f;
  const int X_SCALING = 10, Y_SCALING = 100, Z_SCALING = 100;

  Vector3 vec3Axis(MIN_X /X_SCALING, MIN_Y /Y_SCALING, MIN_Z /Z_SCALING);
  Quaternion quaternionConjugate(COSINE_THETA_BY_TWO, vec3Axis.x, vec3Axis.y, vec3Axis.z);
  Quaternion quaternionCompare(COSINE_THETA_BY_TWO, -vec3Axis.x, -vec3Axis.y, -vec3Axis.z);
  quaternionConjugate.Conjugate();

  gQuaternion1=quaternionConjugate;
  gQuaternion2=quaternionCompare;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionConjugate);
}
void VTQuaternionConjugate001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  if(quaternionCurrentRot != gQuaternion1)
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed " );
    test_return_value=1;
    return ;
  }

  DALI_CHECK_FAIL(gQuaternion2 != quaternionCurrentRot, " Quaternion::Conjugate() is failed," );
  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionEulerAngles()
{
  const float EULER_ANGLE_X = 0.795f, EULER_ANGLE_Y = 0.478f, EULER_ANGLE_Z = 0.374f,EULER_ANGLE_W = 0.374f;

  Quaternion quaternionEularAngle(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z, EULER_ANGLE_W);
  gQuaternion1=quaternionEularAngle;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed " );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionEularAngle);
}
void VTQuaternionEulerAngles001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  if(quaternionCurrentRot != gQuaternion1)
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed  " );
    test_return_value=1;
    return;
  }

  Vector4 vec4RetVal = quaternionCurrentRot.EulerAngles();
  Vector4 mVector = gQuaternion1.AsVector();

  float f_sqw = mVector.w*mVector.w;
  float f_sqx = mVector.x*mVector.x;
  float f_sqy = mVector.y*mVector.y;
  float f_sqz = mVector.z*mVector.z;

  Vector4 vec4EulerAngles;
  vec4EulerAngles.x = atan2f(2.0f * (mVector.y*mVector.z + mVector.x*mVector.w), -f_sqx - f_sqy + f_sqz + f_sqw);
  vec4EulerAngles.y = asinf(-2.0f * (mVector.x*mVector.z - mVector.y*mVector.w));
  vec4EulerAngles.z = atan2f(2.0f * (mVector.x*mVector.y + mVector.z*mVector.w), f_sqx - f_sqy - f_sqz + f_sqw);

  //@NOTE: Get EulerAngles is calculated manually and checked with set angle if difference is less than math error than pass
  DALI_CHECK_FAIL(vec4RetVal.x - vec4EulerAngles.x >= QUAT_EPSILON && vec4RetVal.y - vec4EulerAngles.y >= QUAT_EPSILON && vec4RetVal.z - vec4EulerAngles.z >= QUAT_EPSILON, "Quaternion::EulerAngles() is failed" );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionExp()
{
  const float COS_THETA_BY_TWO = 0.0f, I_BY_SINE_THETA = 1.0f, J_BY_SINE_THETA = 1.2f, K_BY_SINE_THETA = 0.0f;

  Quaternion quaternionTestObj(COS_THETA_BY_TWO, I_BY_SINE_THETA , J_BY_SINE_THETA  , K_BY_SINE_THETA);
  gQuaternion1=quaternionTestObj;

  Quaternion quaternionExp = quaternionTestObj.Exp();
  gQuaternion2=quaternionExp;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionExp);
}
void VTQuaternionExp001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();

  if(quaternionCurrentRot != gQuaternion2)
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed" );
    test_return_value=1;
    return;
  }

  Quaternion quaternionCompareObj = gQuaternion2.Log();

  Vector4 vec4Difference = quaternionCompareObj.AsVector() - gQuaternion1.AsVector();
  DALI_CHECK_FAIL(vec4Difference.x >= QUAT_EPSILON  && vec4Difference.z >= QUAT_EPSILON && vec4Difference.y >= QUAT_EPSILON, "Quaternion::Exp() is failed" );

  DaliLog::PrintPass();
}
void QuaternionLog()
{
  const float COS_THETA_BY_TWO = 0.0f, I_BY_SINE_THETA = 1.0f, J_BY_SINE_THETA = 1.2f, K_BY_SINE_THETA = 0.0f;

  Quaternion quaternionTestObj(COS_THETA_BY_TWO, I_BY_SINE_THETA , J_BY_SINE_THETA  , K_BY_SINE_THETA);
  gQuaternion1=quaternionTestObj;

  Quaternion quaternionExp = quaternionTestObj.Exp();

  Quaternion quaternionLog = quaternionExp.Log();
  gQuaternion1=quaternionLog;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed " );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionLog);
}
void VTQuaternionLog001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  if(quaternionCurrentRot != gQuaternion1)
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed " );
    test_return_value=1;
    return;
  }

  Vector4 vec4Difference = quaternionCurrentRot.AsVector() - gQuaternion1.AsVector();

  //@NOTE: If the difference of Log and Exp of both instance is less than math error than pass
  DALI_CHECK_FAIL(vec4Difference.x > QUAT_EPSILON && vec4Difference.z > QUAT_EPSILON && vec4Difference.y > QUAT_EPSILON, "Quaternion::Log() is failed" );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionInvert()
{
  const float COS_THETA_BY_TWO = 0.0f, I_BY_SINE_THETA = 1.0f, J_BY_SINE_THETA = 1.0f, K_BY_SINE_THETA = 0.0f;

  Quaternion quaternionInvertObj(COS_THETA_BY_TWO , I_BY_SINE_THETA, J_BY_SINE_THETA, K_BY_SINE_THETA);

  quaternionInvertObj.Invert();
  gQuaternion1=quaternionInvertObj;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );
  Stage::GetCurrent().Add(gActorQuaternion);

  gActorQuaternion.SetOrientation(quaternionInvertObj);
}
void VTQuaternionInvert001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  if(quaternionCurrentRot != gQuaternion1)
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed" );
    test_return_value=1;
    return;
  }

  float fXAxis = 1.0f ,fYAxis = 1.0f , fManuallyCalculatedSqrLen = 0.0f;
  float fsqrSum = fXAxis*fXAxis + fYAxis*fYAxis;
  fXAxis = fXAxis/fsqrSum;
  fYAxis = fYAxis/fsqrSum;
  fManuallyCalculatedSqrLen = fXAxis * fXAxis + fYAxis * fYAxis;

  float fretVal = quaternionCurrentRot.LengthSquared();

  //@NOTE: If the difference of Set LengthSquared and manually calculated LengthSquared less than math error than pass
  DALI_CHECK_FAIL(fabs(fretVal - fManuallyCalculatedSqrLen) > QUAT_EPSILON, "Quaternion::Invert() is failed" );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionIsIdentity()
{
  Matrix matIdentity(Matrix::IDENTITY);
  DALI_CHECK_FAIL(matIdentity != Matrix::IDENTITY, "Matrix::Matrix() is failed" );

  Quaternion quaternionIsIdentityObj(matIdentity);

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed " );

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "Stage::GetCurrent is not created" );

  stage.Add(actor);
  actor.SetOrientation(quaternionIsIdentityObj);
  Quaternion quaternionCurrentRot = actor.GetCurrentOrientation();
  if(quaternionCurrentRot != quaternionIsIdentityObj)
  {
    stage.Remove(actor);
    LOG_E("Actor::GetCurrentOrientation is failed " );
    test_return_value=1;
    return;
  }

  bool bQuaternionIsIdentity = quaternionCurrentRot.IsIdentity();

  bool bMatTypeIsIdentity = Matrix::IDENTITY == matIdentity ? true : false;
  DALI_CHECK_FAIL(bQuaternionIsIdentity != bMatTypeIsIdentity, "Quaternion::IsIdentity() is failed" );

  stage.Remove(actor);

  DaliLog::PrintPass();
}
void QuaternionLength()
{
  const float COS_THETA_BY_TWO = 0.0f, I_BY_SINE_THETA = 8.0f, J_BY_SINE_THETA = 6.0f, K_BY_SINE_THETA = 0.0f;

  Quaternion quaternionLengthObj(COS_THETA_BY_TWO , I_BY_SINE_THETA, J_BY_SINE_THETA, K_BY_SINE_THETA);
  gQuaternion1=quaternionLengthObj;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, " Actor::New() is failed " );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionLengthObj);
}
void VTQuaternionLength001()
{
  const float I_BY_SINE_THETA = 8.0f, J_BY_SINE_THETA = 6.0f, K_BY_SINE_THETA = 0.0f;
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  if(quaternionCurrentRot != gQuaternion1)
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E(" Actor::GetCurrentOrientation is failed" );
    test_return_value=1;
    return;
  }

  float f_quaternionLength = quaternionCurrentRot.Length();

  float f_manuallyCalculatedLen = sqrt((K_BY_SINE_THETA) * (K_BY_SINE_THETA ) +
      (I_BY_SINE_THETA ) * (I_BY_SINE_THETA) +
      (J_BY_SINE_THETA ) * (J_BY_SINE_THETA ));

  //@NOTE: If the difference of Set Length and manually calculated LengthSquared is same than pass
  DALI_CHECK_FAIL(f_quaternionLength != f_manuallyCalculatedLen, "Quaternion::Length() is failed" );
  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionNormalizeNormalized()
{
  const float COS_THETA_BY_TWO = 0.0f, I_BY_SINE_THETA = 8.0f, J_BY_SINE_THETA = 6.0f, K_BY_SINE_THETA = 0.0f;
  enum ETargetAPIs { QuaternionNormalized = 0, QuaternionNormalize };

  Quaternion quaternionNormalizeObj(COS_THETA_BY_TWO, I_BY_SINE_THETA , J_BY_SINE_THETA , K_BY_SINE_THETA);
  gQuaternion1=quaternionNormalizeObj;

  Quaternion quaternionNormalizedObj = quaternionNormalizeObj.Normalized();
  gQuaternion2=quaternionNormalizedObj;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed " );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionNormalizeObj);
}
void VTQuaternionNormalizeNormalized001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  if(quaternionCurrentRot != gQuaternion1)
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed " );
    test_return_value=1;
    return;
  }

  gQuaternion1.Normalize();
  DALI_CHECK_FAIL(gQuaternion2 != gQuaternion1, "Quaternion::Normalize is failed" );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionLengthSquared()
{
  const float COS_THETA_BY_TWO = 0.0f, I_BY_SINE_THETA = 8.0f, J_BY_SINE_THETA = 6.0f, K_BY_SINE_THETA = 0.0f;

  Quaternion quaternionLengthSquaredObj(COS_THETA_BY_TWO, I_BY_SINE_THETA , J_BY_SINE_THETA , K_BY_SINE_THETA);
  gQuaternion1=quaternionLengthSquaredObj;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionLengthSquaredObj);
}
void VTQuaternionLengthSquared001()
{
  const float I_BY_SINE_THETA = 8.0f, J_BY_SINE_THETA = 6.0f;
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  if(quaternionCurrentRot != gQuaternion1)
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed " );
    test_return_value=1;
    return;
  }

  float fQuaternionLengthSquared = quaternionCurrentRot.LengthSquared();

  float fManuallyCalculatedLengthSquared =   (I_BY_SINE_THETA ) * (I_BY_SINE_THETA ) +
    (J_BY_SINE_THETA ) * (J_BY_SINE_THETA );
  DALI_CHECK_FAIL(fManuallyCalculatedLengthSquared != fQuaternionLengthSquared, "Quaternion::LengthSquared() is failed" );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionOperatorInequality()
{
  const float LHS_COS_THETA_BY_TWO = 0.0f, I_BY_SINE_THETA_LHS = 1.2f, J_BY_SINE_THETA_LHS = 1.0f, K_BY_SINE_THETA_LHS = 0.0f;
  float fReverseCount = 8.0f;
  gReverseCount=fReverseCount;

  Quaternion quaternionOperatorLHSObj(LHS_COS_THETA_BY_TWO, I_BY_SINE_THETA_LHS, J_BY_SINE_THETA_LHS + fReverseCount, K_BY_SINE_THETA_LHS);
  quaternionOperatorLHSObj=gQuaternion1;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionOperatorLHSObj);
}
void VTQuaternionOperatorInequality001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  if(quaternionCurrentRot != gQuaternion1)
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed" );
    test_return_value=1;
    return;
  }

  const float RHS_COS_THETA_BY_TWO = 0.0f, I_BY_SINE_THETA_RHS = 1.0f, J_BY_SINE_THETA_RHS = 3.0f, K_BY_SINE_THETA_RHS = 0.0f;

  Quaternion quaternionOperatorRHSObj(RHS_COS_THETA_BY_TWO, I_BY_SINE_THETA_RHS + gReverseCount,  J_BY_SINE_THETA_RHS, K_BY_SINE_THETA_RHS);

  bool bRetValOperatorInequality = quaternionCurrentRot != quaternionOperatorRHSObj;

  DALI_CHECK_FAIL(!bRetValOperatorInequality, "Quaternion::operator!=() is failed" );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionOperatorEquality()
{
  const float LHS_COS_THETA_BY_TWO = 0.0f, I_BY_SINE_THETA_LHS = 1.0f, J_BY_SINE_THETA_LHS = 1.0f, K_BY_SINE_THETA_LHS = 0.0f;
  float fReverseCount = 8.0f;

  Quaternion quaternionOperatorLHSObj(LHS_COS_THETA_BY_TWO, I_BY_SINE_THETA_LHS , J_BY_SINE_THETA_LHS + fReverseCount, K_BY_SINE_THETA_LHS);

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed" );

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "Stage::GetCurrent is not created" );

  stage.Add(actor);
  actor.SetOrientation(quaternionOperatorLHSObj);

  Quaternion quaternionCurrentRot = actor.GetCurrentOrientation();

  const float RHS_COS_THETA_BY_TWO = 0.0f, I_BY_SINE_THETA_RHS = 1.0f, J_BY_SINE_THETA_RHS = 1.0f, K_BY_SINE_THETA_RHS = 0.0f;
  Quaternion quaternionOperatorRHSObj(RHS_COS_THETA_BY_TWO, I_BY_SINE_THETA_RHS ,  J_BY_SINE_THETA_RHS + fReverseCount, K_BY_SINE_THETA_RHS);

  bool bRetValOperatorEquality = (quaternionOperatorLHSObj == quaternionOperatorRHSObj);
  DALI_CHECK_FAIL(!bRetValOperatorEquality, "Quaternion::operator==() is failed" );

  stage.Remove(actor);

  DaliLog::PrintPass();
}
void QuaternionOperatorMultiplicationDivision()
{
  enum ETargetAPIs { QuaternionOperatorMultiplication = 0, QuaternionOperatorDivision };
  const float COS_THETA_BY_TWO_FIRST = 0.0f, I_BY_SINE_THETA_FIRST = 1.0f, J_BY_SINE_THETA_FIRST = 2.0f, K_BY_SINE_THETA_FIRST = 0.0f;
  const float COS_THETA_BY_TWO_SECOND = 0.0f, I_BY_SINE_THETA_SECOND = 1.0f, J_BY_SINE_THETA_SECOND = 2.0f, K_BY_SINE_THETA_SECOND = 0.0f;
  float fReverseCount = 8.0f;

  Quaternion quaternionOperatorFirstObj(COS_THETA_BY_TWO_FIRST, I_BY_SINE_THETA_FIRST , J_BY_SINE_THETA_FIRST * fReverseCount, K_BY_SINE_THETA_FIRST);
  gQuaternion1=quaternionOperatorFirstObj;
  Quaternion quaternionOperatorSecondObj(COS_THETA_BY_TWO_SECOND, I_BY_SINE_THETA_SECOND,  J_BY_SINE_THETA_SECOND * fReverseCount, K_BY_SINE_THETA_SECOND);

  Quaternion quaternionOperatorMultiplicationObj = (quaternionOperatorSecondObj * quaternionOperatorFirstObj);

  Quaternion quaternionOperatorDivisionObj = (quaternionOperatorMultiplicationObj / quaternionOperatorSecondObj);
  gQuaternion2=quaternionOperatorDivisionObj;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed " );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionOperatorDivisionObj);
}
void VTQuaternionOperatorMultiplicationDivision001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  if(quaternionCurrentRot != gQuaternion2)
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed" );
    test_return_value=1;
    return;
  }

  DALI_CHECK_FAIL(quaternionCurrentRot != gQuaternion1, "Quaternion::operator*(), Quaternion::operator/() is failed" );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionOperatorAddition()
{
  const float COS_THETA_BY_TWO_LHS = 0.0f, I_BY_SINE_THETA_LHS = 1.0f, J_BY_SINE_THETA_LHS = 1.0f, K_BY_SINE_THETA_LHS = 0.0f;
  const float COS_THETA_BY_TWO_RHS = 0.0f, I_BY_SINE_THETA_RHS = 1.0f, J_BY_SINE_THETA_RHS = 1.0f, K_BY_SINE_THETA_RHS = 0.0f;
  float fReverseCount = 8.0f;

  Quaternion quaternionOperatorAdditionLHSObj(COS_THETA_BY_TWO_LHS, I_BY_SINE_THETA_LHS, J_BY_SINE_THETA_LHS + fReverseCount, K_BY_SINE_THETA_LHS);

  Quaternion quaternionOperatorAdditionRHSObj(COS_THETA_BY_TWO_RHS, I_BY_SINE_THETA_RHS + fReverseCount, J_BY_SINE_THETA_RHS , K_BY_SINE_THETA_RHS);

  Quaternion quaternionOperatorAdditionObj = quaternionOperatorAdditionLHSObj + quaternionOperatorAdditionRHSObj;
  gQuaternion1=quaternionOperatorAdditionObj;

  Quaternion quaternionOperatorAdditionResultObj(  (COS_THETA_BY_TWO_LHS + COS_THETA_BY_TWO_RHS),
      (I_BY_SINE_THETA_LHS + I_BY_SINE_THETA_RHS) + fReverseCount,
      (J_BY_SINE_THETA_LHS + J_BY_SINE_THETA_RHS) + fReverseCount,
      (K_BY_SINE_THETA_LHS + K_BY_SINE_THETA_RHS));
  gQuaternion2=quaternionOperatorAdditionResultObj;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionOperatorAdditionResultObj);
}
void VTQuaternionOperatorAddition001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  if(quaternionCurrentRot != gQuaternion2)
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed " );
    test_return_value=1;
    return;
  }

  DALI_CHECK_FAIL(quaternionCurrentRot != gQuaternion1, "Quaternion::operator+() is failed" );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionOperatorMultiplicationScale()
{
  const float COS_THETA_BY_TWO = 0.0f, I_BY_SINE_THETA = 1.0f, J_BY_SINE_THETA = 1.0f, K_BY_SINE_THETA = 0.0f;
  float fReverseCount = 8.0f;

  Quaternion quaternionOperatorMultiScaleObj(COS_THETA_BY_TWO, I_BY_SINE_THETA, J_BY_SINE_THETA + fReverseCount, K_BY_SINE_THETA);

  Quaternion quaternionOperatorMulResult = quaternionOperatorMultiScaleObj * fReverseCount;
  gQuaternion2=quaternionOperatorMulResult;

  Quaternion quaternionOperatoManuallyCalObj(  (COS_THETA_BY_TWO * fReverseCount),
      (I_BY_SINE_THETA * fReverseCount),
      (fReverseCount * (J_BY_SINE_THETA + fReverseCount)),
      (K_BY_SINE_THETA * fReverseCount));
  gQuaternion1=quaternionOperatoManuallyCalObj;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionOperatoManuallyCalObj);
}
void VTQuaternionOperatorMultiplicationScale001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  if(quaternionCurrentRot != gQuaternion1)
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed " );
    test_return_value=1;
    return;
  }

  DALI_CHECK_FAIL(gQuaternion2 != quaternionCurrentRot, "Quaternion::operator*(float) is failed " );
  Stage::GetCurrent().Remove(gActorQuaternion);
  DaliLog::PrintPass();
}
void QuaternionOperatorMultiplicationWithAssignment(void)
{
  float fReverseCount = 2.0f;
  const float COS_THETA_BY_ONE = 2.0f, I_BY_SINE_THETA_ONE = 2.0f, J_BY_SINE_THETA_ONE = 2.0f, K_BY_SINE_THETA_ONE = 2.0f;
  const float COS_THETA_BY_TWO = 0.0f, I_BY_SINE_THETA_TWO = 10.0f, J_BY_SINE_THETA_TWO = 10.0f, K_BY_SINE_THETA_TWO = 0.0f;

  const Quaternion quaternionOperatorMulDivObj(COS_THETA_BY_ONE, I_BY_SINE_THETA_ONE, J_BY_SINE_THETA_ONE, K_BY_SINE_THETA_ONE);
  gQuaternion1=quaternionOperatorMulDivObj;

  Quaternion quaternionOperatorMulDivResultObj(COS_THETA_BY_TWO, I_BY_SINE_THETA_TWO, J_BY_SINE_THETA_TWO + fReverseCount, K_BY_SINE_THETA_TWO);
  gQuaternion2=quaternionOperatorMulDivResultObj;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed " );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionOperatorMulDivResultObj);
}
void VTQuaternionOperatorMultiplicationWithAssignment001(void)
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  if(quaternionCurrentRot != gQuaternion2)
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed " );
    test_return_value=1;
    return;
  }

  gQuaternion2 *= gQuaternion1;
  gQuaternion2 = gQuaternion2 / gQuaternion1;
  DALI_CHECK_FAIL(quaternionCurrentRot != gQuaternion2, "Quaternion::operator*=(Quaternion) is failed" );
  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionOperatorDivisionScale(void)
{
  const float COS_THETA_BY_TWO = 0.0f, I_BY_SINE_THETA = 1.0f, J_BY_SINE_THETA = 1.0f, K_BY_SINE_THETA = 0.0f;
  float fReverseCount = 2.0f;

  Quaternion quaternionOperatorScaleObj(COS_THETA_BY_TWO, I_BY_SINE_THETA, J_BY_SINE_THETA + fReverseCount, K_BY_SINE_THETA);

  Quaternion quaternionOperatorDivResult = quaternionOperatorScaleObj / fReverseCount;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionOperatorDivResult);
}
void VTQuaternionOperatorDivisionScale001(void)
{
  const float COS_THETA_BY_TWO = 0.0f, I_BY_SINE_THETA = 1.0f, J_BY_SINE_THETA = 1.0f, K_BY_SINE_THETA = 0.0f;
  float fReverseCount = 2.0f;

  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  Quaternion quaternionOperatoManuallyCalObj(  (COS_THETA_BY_TWO / fReverseCount),
      (I_BY_SINE_THETA / fReverseCount),
      (J_BY_SINE_THETA + fReverseCount) / fReverseCount,
      (K_BY_SINE_THETA / fReverseCount));
  if(!quaternionOperatoManuallyCalObj.Length())
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Quaternion::Quaternion() is failed " );
    test_return_value=1;
    return;
  }

  DALI_CHECK_FAIL(quaternionCurrentRot != quaternionOperatoManuallyCalObj, "Quaternion::operator/(float)is failed " );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionOperatorScaleDivAssignement()
{
  string strMemoryInfo;
  string strTimeInfo;

  const float COS_THETA_BY_TWO = 0.0f, I_BY_SINE_THETA = 10.0f, J_BY_SINE_THETA = 10.0f, K_BY_SINE_THETA = 0.0f;
  float fReverseCount = 2.0f;

  Quaternion quaternionOperatorResultScaleObj(COS_THETA_BY_TWO, I_BY_SINE_THETA, J_BY_SINE_THETA + fReverseCount, K_BY_SINE_THETA);
  gQuaternion1=quaternionOperatorResultScaleObj;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionOperatorResultScaleObj);
}
void VTQuaternionOperatorScaleDivAssignement001()
{
  const float QUATERNION_SCALING_FACTOR = 2.0f;
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  if(quaternionCurrentRot != gQuaternion1)
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed " );
    test_return_value=1;
    return;
  }

  gActorQuaternion.SetOrientation(gQuaternion1);

  gQuaternion1 /= QUATERNION_SCALING_FACTOR;
  gQuaternion1 *= QUATERNION_SCALING_FACTOR;

  DALI_CHECK_FAIL(quaternionCurrentRot != gQuaternion1, "Quaternion::operator/=(float) is failed" );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionOperatorSetEuler()
{
  const float COS_THETA_BY_TWO = 0.0f, I_BY_SINE_THETA = 10.0f, J_BY_SINE_THETA = 10.0f, K_BY_SINE_THETA = 0.0f;
  float fReverseCount = 2.0f;
  const float EULER_ANGLE_X = 45.0f, EULER_ANGLE_Y = 60.0f, EULER_ANGLE_Z = 30.0f;

  Quaternion quaternionSetEular(COS_THETA_BY_TWO, I_BY_SINE_THETA, J_BY_SINE_THETA + fReverseCount, K_BY_SINE_THETA);
  quaternionSetEular.SetEuler(Radian(Degree(EULER_ANGLE_X + fReverseCount)), Radian(Degree(EULER_ANGLE_Y - fReverseCount)), Radian(Degree(EULER_ANGLE_Z + fReverseCount)));
  gQuaternion1=quaternionSetEular;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed " );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionSetEular);
}
void VTQuaternionOperatorSetEuler001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  DALI_CHECK_FAIL(quaternionCurrentRot.EulerAngles() != gQuaternion1.EulerAngles(), " Quaternion::SetEuler is failed" );
  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionOperatorToAxisAngleVec4()
{
  float fReverseCount = 2.0f;
  const Radian ANGLE_ROTATION_RAD(Degree(120.0f));
  const float X  = 10.0f, Y = 10.0f, Z = 10.0f;

  Quaternion quaternionSetAngleAxis(ANGLE_ROTATION_RAD, Vector3(X, Y, Z + fReverseCount));
  gQuaternion1=quaternionSetAngleAxis;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, " Actor::New() is failed" );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionSetAngleAxis);
}
void VTQuaternionOperatorToAxisAngleVec4001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();

  Vector3 vec3RotAxis;
  Radian fRotAngle;
  quaternionCurrentRot.ToAxisAngle(vec3RotAxis, fRotAngle);

  Vector3 vec3Axis;
  Radian fAngle;

  gQuaternion1.ToAxisAngle(vec3Axis, fAngle);

  DALI_CHECK_FAIL(vec3Axis != vec3RotAxis && fRotAngle != fAngle, "Quaternion::ToAxisAngle(Vector3 &,Radian &) is failed");
  Stage::GetCurrent().Add(gActorQuaternion);
  DaliLog::PrintPass();
}
void QuaternionOperatorToAxisAngleVec3()
{
  float fReverseCount = 2.0f;
  const float MAX_ROT_ANGLE = 120.0f;

  Quaternion quaternionSetAngleAxis(Radian(Degree(MAX_ROT_ANGLE - fReverseCount)), Vector3(10.0f, 10.0f, 10.0f + fReverseCount));
  gQuaternion1=quaternionSetAngleAxis;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionSetAngleAxis);
}
void VTQuaternionOperatorToAxisAngleVec3001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  Vector3 vec3RotAxis;
  Radian fRotAngle;
  bool bRet1=quaternionCurrentRot.ToAxisAngle(vec3RotAxis, fRotAngle);
  DALI_CHECK_FAIL(!bRet1, "Quaternion::ToAxisAngle(Vector3 &,Radian &) is failed" );

  Vector3 vec3Axis;
  Radian fAngle;

  bool bRet2=gQuaternion1.ToAxisAngle(vec3Axis, fAngle);
  DALI_CHECK_FAIL(!bRet2, "Quaternion::ToAxisAngle(Vector3 &,Radian &) is failed" );

  DALI_CHECK_FAIL(vec3Axis != vec3RotAxis && fRotAngle == fAngle, "Quaternion::ToAxisAngle(Vector3 &,Radian &) is failed" );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionSubtractionAdditionWithAssignmentOperator()
{
  enum ETargetAPIs { QuaternionOperAddAssign = 0, QuaternionOperSubtractAssign };

  const float COS_THETA_BY_TWO_LHS = 0.0f, I_BY_SINE_THETA_LHS = 8.0f, J_BY_SINE_THETA_LHS = 6.0f, K_BY_SINE_THETA_LHS = 0.0f;
  const float COS_THETA_BY_TWO_RHS = 0.0f, I_BY_SINE_THETA_RHS = 2.0f, J_BY_SINE_THETA_RHS = 2.0f, K_BY_SINE_THETA_RHS = 0.0f;

  Quaternion quaternionAdditionAssignmentObj(COS_THETA_BY_TWO_LHS , I_BY_SINE_THETA_LHS, J_BY_SINE_THETA_LHS ,K_BY_SINE_THETA_LHS);

  Quaternion quaternionSubtractionObj(COS_THETA_BY_TWO_RHS, I_BY_SINE_THETA_RHS , J_BY_SINE_THETA_RHS , K_BY_SINE_THETA_RHS);
  gQuaternion2=quaternionSubtractionObj;

  quaternionAdditionAssignmentObj += quaternionSubtractionObj;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionAdditionAssignmentObj);
  gQuaternion1=quaternionAdditionAssignmentObj;
}
void VTQuaternionSubtractionAdditionWithAssignmentOperator001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  Quaternion qResultObj = quaternionCurrentRot - gQuaternion2;

  DALI_CHECK_FAIL(qResultObj != (gQuaternion1 - gQuaternion2), "Quaternion::operator+=, Quaternion::operator- is failed" );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionUnaryMinusOperator()
{
  const float COS_THETA_BY_TWO_LHS = 0.0f, I_BY_SINE_THETA_LHS = 8.0f, J_BY_SINE_THETA_LHS = 6.0f, K_BY_SINE_THETA_LHS = 0.0f;
  const float COS_THETA_BY_TWO_RHS = 0.0f, I_BY_SINE_THETA_RHS = 2.0f, J_BY_SINE_THETA_RHS = 2.0f, K_BY_SINE_THETA_RHS = 0.0f;

  Quaternion quaternionAdditionTestObj(COS_THETA_BY_TWO_LHS , I_BY_SINE_THETA_LHS, J_BY_SINE_THETA_LHS ,K_BY_SINE_THETA_LHS);
  gQuaternion1=quaternionAdditionTestObj;

  Quaternion quaternionSubtractionObj(COS_THETA_BY_TWO_RHS, I_BY_SINE_THETA_RHS , J_BY_SINE_THETA_RHS , K_BY_SINE_THETA_RHS);

  Quaternion quaternionUnaryMinusObj = -quaternionAdditionTestObj;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed " );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionUnaryMinusObj);
}
void VTQuaternionUnaryMinusOperator001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();

  //Note: If conjugate value and minus value of x y z are not equal  than fail
  if(quaternionCurrentRot.AsVector().x != -gQuaternion1.AsVector().x)
  {

    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Quaternion::operator- is failed for x co-ordinate value" );
    test_return_value=1;
    return;
  }

  if(quaternionCurrentRot.AsVector().y != -gQuaternion1.AsVector().y)
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Quaternion::operator- is failed for y co-ordinate value" );
    test_return_value=1;
    return;
  }

  DALI_CHECK_FAIL(quaternionCurrentRot.AsVector().z != -gQuaternion1.AsVector().z, "Quaternion::operator- is failed for z co-ordinate value" );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionRotateVec4()
{
  const float MIN_ROT_ANGLE = 45.0f;
  const int ROT_SCALING_FACTOR = 10;

  Quaternion quaternionRotationObj(Radian(Degree(MIN_ROT_ANGLE  * ROT_SCALING_FACTOR)), Vector3::ZAXIS);
  gQuaternion1=quaternionRotationObj;

  Vector4 vec4RotationObj(0.0f , 8.0f , 6.0f , 0.0f);
  gVector40=vec4RotationObj;

  Vector4 vec4RotationResult = quaternionRotationObj.Rotate(vec4RotationObj);
  gVector4=vec4RotationResult;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionRotationObj);
}
void VTQuaternionRotateVec4001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  if(quaternionCurrentRot != gQuaternion1 )
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed " );
    test_return_value=1;
    return;
  }

  const float COS_THETA_BY_TWO = 0.0f;
  Quaternion quaternionManuallyCalculatedRotationObj(COS_THETA_BY_TWO, gVector40.x, gVector40.y, gVector40.z);
  Quaternion quaternionConjugate = quaternionCurrentRot;
  quaternionConjugate.Invert();
  Vector4 vecManualRotResult = (quaternionCurrentRot * quaternionManuallyCalculatedRotationObj * quaternionConjugate).AsVector();

  //Note : If the difference of manually calculated rotation and automatic rotation vector4 objects are less than Math error than pass
  DALI_CHECK_FAIL((vecManualRotResult.x - gVector4.x) >QUAT_EPSILON || (vecManualRotResult.y - gVector4.y) > QUAT_EPSILON || (vecManualRotResult.z - gVector4.z) > QUAT_EPSILON , "Quaternion::Rotate(Vector4) is failed" );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionRotateVec3()
{
  const float MIN_ROT_ANGLE = 35.0f;
  const int ROT_SCALING_FACTOR = 10;

  Quaternion quaternionRotationObj(Radian(Degree(MIN_ROT_ANGLE * ROT_SCALING_FACTOR)), Vector3::ZAXIS);

  Vector3 vec3RotationObj(0.0f , 8.0f , 6.0f );
  gVector30=vec3RotationObj;

  Vector3 vec3RotationResult = quaternionRotationObj.Rotate(vec3RotationObj);
  gVector3=vec3RotationResult;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed " );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionRotationObj);
}
void VTQuaternionRotateVec3001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();

  const float COS_THETA_BY_TWO = 0.0f;
  Quaternion quaternionManuallyCalculatedRotationObj(COS_THETA_BY_TWO, gVector30.x, gVector30.y, gVector30.z);
  Quaternion quaternionConjugate = quaternionCurrentRot;
  quaternionConjugate.Invert();
  Vector3 vecManualRotResult = (Vector3)(quaternionCurrentRot * quaternionManuallyCalculatedRotationObj * quaternionConjugate).AsVector();

  //Note : //Note : If the difference of manually calculated rotation and automatic rotation vector3 objects are less than Math error than pass
  DALI_CHECK_FAIL((vecManualRotResult.x - gVector3.x) > QUAT_EPSILON || (vecManualRotResult.y - gVector3.y) > QUAT_EPSILON || (vecManualRotResult.z - gVector3.z) >QUAT_EPSILON , "Quaternion::Rotate(Vector3) is failed" );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionAngleBetween()
{
  const float COS_THETA_BY_TWO_LHS = 0.0f, I_BY_SINE_THETA_LHS = 8.0f, J_BY_SINE_THETA_LHS = 6.0f, K_BY_SINE_THETA_LHS = 0.0f;

  Quaternion quaternionFirstObj(COS_THETA_BY_TWO_LHS , I_BY_SINE_THETA_LHS, J_BY_SINE_THETA_LHS ,K_BY_SINE_THETA_LHS);

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "Stage::GetCurrent is not created " );

  stage.Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionFirstObj);

}
void VTQuaternionAngleBetween001()
{
  const float COS_THETA_BY_TWO_LHS = 0.0f, I_BY_SINE_THETA_LHS = 8.0f, J_BY_SINE_THETA_LHS = 6.0f, K_BY_SINE_THETA_LHS = 0.0f;
  const float COS_THETA_BY_TWO_RHS = 0.0f, I_BY_SINE_THETA_RHS = 2.0f, J_BY_SINE_THETA_RHS = 2.0f, K_BY_SINE_THETA_RHS = 0.0f;
  Quaternion quaternionFirstObj(COS_THETA_BY_TWO_LHS , I_BY_SINE_THETA_LHS, J_BY_SINE_THETA_LHS ,K_BY_SINE_THETA_LHS);
  Quaternion quaternionSecondObj(COS_THETA_BY_TWO_RHS, I_BY_SINE_THETA_RHS , J_BY_SINE_THETA_RHS , K_BY_SINE_THETA_RHS);

  Stage stage = Stage::GetCurrent();
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  if(quaternionCurrentRot != quaternionFirstObj )
  {
    stage.Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed " );
    test_return_value=1;
    return;
  }

  float fAngleBetween = Quaternion::AngleBetween(quaternionCurrentRot, quaternionSecondObj);

  float fManuallyCalculatedAngleBetween = Quaternion::AngleBetween(quaternionFirstObj, quaternionSecondObj);

  quaternionFirstObj.Normalize();
  quaternionSecondObj.Normalize();
  float fDot4 = quaternionFirstObj.AsVector().Dot4(quaternionSecondObj.AsVector());
  //@NOTE: angle = acos(v1•v2) -> θ=cos^−1(2⟨q1,q2⟩^2−1)
  float fAngle = acos( (2 * fDot4 * fDot4) - 1);
  DALI_CHECK_FAIL(fabs(fManuallyCalculatedAngleBetween - fAngleBetween) >= QUAT_EPSILON || fabs(fManuallyCalculatedAngleBetween - fAngle) >= QUAT_EPSILON, "Quaternion::AngleBetween is failed" );

  stage.Remove(gActorQuaternion);

  DaliLog::PrintPass();
}

void QuaternionDot()
{
  const float COS_THETA_BY_TWO_LHS = 0.0f, I_BY_SINE_THETA_LHS = 8.0f, J_BY_SINE_THETA_LHS = 6.0f, K_BY_SINE_THETA_LHS = 0.0f;
  const float COS_THETA_BY_TWO_RHS = 0.0f, I_BY_SINE_THETA_RHS = 2.0f, J_BY_SINE_THETA_RHS = 2.0f, K_BY_SINE_THETA_RHS = 0.0f;

  Quaternion quaternionFirstObj(COS_THETA_BY_TWO_LHS , I_BY_SINE_THETA_LHS, J_BY_SINE_THETA_LHS ,K_BY_SINE_THETA_LHS);
  gQuaternion1=quaternionFirstObj;

  Quaternion quaternionSecondObj(COS_THETA_BY_TWO_RHS, I_BY_SINE_THETA_RHS , J_BY_SINE_THETA_RHS , K_BY_SINE_THETA_RHS);
  gQuaternion2=quaternionSecondObj;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed " );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionFirstObj);
}
void VTQuaternionDot001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  if(quaternionCurrentRot != gQuaternion1 )
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed" );
    test_return_value=1;
    return;
  }

  float fDotProduct = Quaternion::Dot(quaternionCurrentRot, gQuaternion2);
  float fManualDotProduct = quaternionCurrentRot.AsVector().Dot4(gQuaternion2.AsVector());

  DALI_CHECK_FAIL(fManualDotProduct != fDotProduct, " Quaternion::Dot is failed" );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}

void QuaternionFromAxisAngle()
{
  const float MIN_ROT_ANGLE = 20.0f;
  const int ROT_SCALING_FACTOR = 10;

  Vector3 vec3Axis(2.0f , 4.0f , 6.0f);
  float fAngle = MIN_ROT_ANGLE * ROT_SCALING_FACTOR;

  Quaternion quaternionObj( Radian(fAngle), vec3Axis );
  gQuaternion1=quaternionObj;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionObj);
}
void VTQuaternionFromAxisAngle001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  if(quaternionCurrentRot != gQuaternion1)
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed" );
    test_return_value=1;
    return;
  }
  Stage::GetCurrent().Remove(gActorQuaternion);
  DaliLog::PrintPass();
}
void QuaternionLerp()
{
  const float MIN_ROT_ANGLE = 1.0f, ROT_SCALING_FACTOR = 1.0f;

  const float COS_THETA_BY_TWO_LHS = 0.0f, I_BY_SINE_THETA_LHS = 13.0f, J_BY_SINE_THETA_LHS = 10.0f, K_BY_SINE_THETA_LHS = 0.0f;
  const float COS_THETA_BY_TWO_RHS = 0.0f, I_BY_SINE_THETA_RHS = 13.0f, J_BY_SINE_THETA_RHS = 8.0f, K_BY_SINE_THETA_RHS = 0.0f;

  Quaternion quaternionFirstObj(COS_THETA_BY_TWO_LHS , I_BY_SINE_THETA_LHS, J_BY_SINE_THETA_LHS ,K_BY_SINE_THETA_LHS);
  gQuaternion1=quaternionFirstObj;
  Quaternion quaternionSecondObj(COS_THETA_BY_TWO_RHS, I_BY_SINE_THETA_RHS , J_BY_SINE_THETA_RHS , K_BY_SINE_THETA_RHS);
  gQuaternion2=quaternionSecondObj;

  gDistance = MIN_ROT_ANGLE + ROT_SCALING_FACTOR ;
  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );
  gActorQuaternion.SetOrientation(quaternionFirstObj);

  Stage::GetCurrent().Add(gActorQuaternion);
}
void VTQuaternionLerp001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  if(quaternionCurrentRot != gQuaternion1 )
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed" );
    test_return_value=1;
    return;
  }
  Quaternion quaternionAxisAngle = Quaternion::Lerp(quaternionCurrentRot, gQuaternion2, gDistance);

  //@NOTE: lerp = ((1-t)*v0 + t*v1) @see http://en.wikipedia.org/wiki/Linear_interpolation
  Quaternion quaternionCompareObj = ((gQuaternion1 * (1.0f - gDistance)) + gQuaternion2 * gDistance).Normalized();

  DALI_CHECK_FAIL(quaternionAxisAngle != quaternionCompareObj, "Quaternion::Lerp is failed" );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionSlerp()
{
  const float MIN_ROT_ANGLE = 1.0f, ROT_SCALING_FACTOR = 1.0f;

  const float COS_THETA_BY_TWO_LHS = 0.0f, I_BY_SINE_THETA_LHS = 13.0f, J_BY_SINE_THETA_LHS = 10.0f, K_BY_SINE_THETA_LHS = 0.0f;
  const float COS_THETA_BY_TWO_RHS = 0.0f, I_BY_SINE_THETA_RHS = 13.0f, J_BY_SINE_THETA_RHS = 8.0f, K_BY_SINE_THETA_RHS = 0.0f;
  const float COS_THETA_BY_TWO = 1.0f, I_BY_SINE_THETA = 1.0f, J_BY_SINE_THETA = 1.0f, K_BY_SINE_THETA = 1.0f;

  Quaternion quaternionFirstObj(COS_THETA_BY_TWO_LHS , I_BY_SINE_THETA_LHS, J_BY_SINE_THETA_LHS ,K_BY_SINE_THETA_LHS);
  gQuaternion1=quaternionFirstObj;

  Quaternion quaternionSecondObj(COS_THETA_BY_TWO_RHS, I_BY_SINE_THETA_RHS , J_BY_SINE_THETA_RHS , K_BY_SINE_THETA_RHS);
  gQuaternion2=quaternionSecondObj;

  Quaternion quaternionCompareObj(COS_THETA_BY_TWO,I_BY_SINE_THETA,J_BY_SINE_THETA,K_BY_SINE_THETA);
  gQuaternion3=quaternionCompareObj;

  float fDistance = MIN_ROT_ANGLE + ROT_SCALING_FACTOR;
  gDistance=fDistance;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed" );
  gActorQuaternion.SetOrientation(quaternionFirstObj);

  Stage::GetCurrent().Add(gActorQuaternion);
}
void VTQuaternionSlerp001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();

  if(quaternionCurrentRot != gQuaternion1)
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed " );
    test_return_value=1;
    return;
  }

  Quaternion quaternionSlerp = Quaternion::Slerp(quaternionCurrentRot, gQuaternion2, gDistance);

  float fCosTheta = Quaternion::Dot(gQuaternion1, gQuaternion2);
  const float MIN_RANGE_DOTP = -0.95f, MAX_RANGE_DOTP = 0.95f;

  if (fCosTheta > MIN_RANGE_DOTP && fCosTheta < MAX_RANGE_DOTP)
  {
    float fTheta = acosf(fCosTheta);
    //@NOTE: slerp(q0, q1,t) = (q0 * q1^-1)^t * q0 and q^t = cos t Ω + v sin t Ω @see http://en.wikipedia.org/wiki/Slerp
    gQuaternion3 = (gQuaternion1 * sinf(fTheta * (1.0f - gDistance)) + gQuaternion2 * sinf(fTheta * gDistance)) / sinf(fTheta);
  }
  else
  {
    gQuaternion3 = Quaternion::Lerp(gQuaternion1, gQuaternion2, gDistance);
  }

  DALI_CHECK_FAIL(quaternionSlerp != gQuaternion3, "Quaternion::Slerp is failed " );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionSlerpNoInvert()
{
  const float MIN_ROT_ANGLE = 1.00f;
  const int ROT_SCALING_FACTOR = 10;

  const float COS_THETA_BY_TWO_LHS = 2.0f, I_BY_SINE_THETA_LHS = 4.0f, J_BY_SINE_THETA_LHS = 6.0f, K_BY_SINE_THETA_LHS = 8.0f;
  const float COS_THETA_BY_TWO_RHS = 1.0f, I_BY_SINE_THETA_RHS = 2.0f, J_BY_SINE_THETA_RHS = 5.0f, K_BY_SINE_THETA_RHS = 1.0f;
  const float COS_THETA_BY_TWO = 1.0f, I_BY_SINE_THETA = 1.0f, J_BY_SINE_THETA = 1.0f, K_BY_SINE_THETA = 1.0f;

  Quaternion quaternionFirstObj(COS_THETA_BY_TWO_LHS , I_BY_SINE_THETA_LHS, J_BY_SINE_THETA_LHS ,K_BY_SINE_THETA_LHS);
  gQuaternion1=quaternionFirstObj;

  Quaternion quaternionSecondObj(COS_THETA_BY_TWO_RHS, I_BY_SINE_THETA_RHS , J_BY_SINE_THETA_RHS , K_BY_SINE_THETA_RHS);
  gQuaternion2=quaternionSecondObj;

  Quaternion quaternionCompareObje(COS_THETA_BY_TWO,I_BY_SINE_THETA,J_BY_SINE_THETA,K_BY_SINE_THETA);
  gQuaternion3=quaternionCompareObje;

  float fDistance = MIN_ROT_ANGLE  / ROT_SCALING_FACTOR;
  gDistance=fDistance;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed " );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionFirstObj);
}
void VTQuaternionSlerpNoInvert001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  if(quaternionCurrentRot != gQuaternion1)
  {
    Stage::GetCurrent().Remove(gActorQuaternion);
    LOG_E("Actor::GetCurrentOrientation is failed " );
    test_return_value=1;
    return;
  }

  Quaternion quaternionSlerpNoInvert = Quaternion::SlerpNoInvert(quaternionCurrentRot, gQuaternion2, gDistance);

  float fCosTheta = Quaternion::Dot(quaternionCurrentRot, gQuaternion2);
  const float MIN_RANGE_DOTP = -0.95f, MAX_RANGE_DOTP = 0.95f;

  if (fCosTheta > MIN_RANGE_DOTP && fCosTheta < MAX_RANGE_DOTP)
  {

    float fTheta = acosf(fCosTheta);
    gQuaternion3 =  (quaternionCurrentRot * sinf(fTheta * (1.0f - gDistance)) + gQuaternion2 * sinf(fTheta * gDistance)) / sinf(fTheta);
  }
  else
  {
    gQuaternion3 = Quaternion::Lerp(quaternionCurrentRot, gQuaternion2, gDistance);
  }

  DALI_CHECK_FAIL(gQuaternion3 != quaternionSlerpNoInvert, "Quaternion::SlerpNoInvert is failed," );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionSquad()
{
  const float MIN_ROT_ANGLE = 1.0f;
  const int ROT_SCALING_FACTOR = 1.5f;

  const float COS_THETA_BY_TWO_LHS = 0.0f, I_BY_SINE_THETA_LHS = 13.0f, J_BY_SINE_THETA_LHS = 10.0f, K_BY_SINE_THETA_LHS = 0.0f;
  const float COS_THETA_BY_TWO_RHS = 6.0f, I_BY_SINE_THETA_RHS = 13.0f, J_BY_SINE_THETA_RHS = 8.0f, K_BY_SINE_THETA_RHS = 10.0f;

  Quaternion quaternionFirstObj(COS_THETA_BY_TWO_LHS , I_BY_SINE_THETA_LHS, J_BY_SINE_THETA_LHS ,K_BY_SINE_THETA_LHS);

  Quaternion quaternionSecondObj(COS_THETA_BY_TWO_RHS, I_BY_SINE_THETA_RHS , J_BY_SINE_THETA_RHS , K_BY_SINE_THETA_RHS);

  Quaternion quaternionStartObj(COS_THETA_BY_TWO_LHS, I_BY_SINE_THETA_LHS, J_BY_SINE_THETA_LHS, K_BY_SINE_THETA_LHS);
  gQuaternion1=quaternionStartObj;

  Quaternion quaternionFinishObj(COS_THETA_BY_TWO_LHS, I_BY_SINE_THETA_LHS, J_BY_SINE_THETA_LHS, K_BY_SINE_THETA_LHS);
  gQuaternion2=quaternionFinishObj;

  Quaternion quaternionPt1(COS_THETA_BY_TWO_LHS, I_BY_SINE_THETA_LHS, J_BY_SINE_THETA_LHS, K_BY_SINE_THETA_LHS );
  gQuaternion3=quaternionPt1;

  Quaternion quaternionPt2(COS_THETA_BY_TWO_RHS , I_BY_SINE_THETA_RHS , J_BY_SINE_THETA_RHS, K_BY_SINE_THETA_RHS);
  gQuaternion4=quaternionPt2;

  float fDistance = MIN_ROT_ANGLE + ROT_SCALING_FACTOR ;
  gDistance=fDistance;

  Quaternion quaternionSquad = Quaternion::Squad(quaternionStartObj, quaternionFinishObj, quaternionPt1, quaternionPt2, fDistance);

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed " );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionSquad);
}
void VTQuaternionSquad001()
{
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();

  Quaternion quaternionTestObj1 = Quaternion::SlerpNoInvert(gQuaternion1, gQuaternion2, gDistance);
  Quaternion quaternionTestObj2 = Quaternion::SlerpNoInvert(gQuaternion3, gQuaternion4, gDistance);
  Quaternion quaternionManualSquad = Quaternion::SlerpNoInvert(quaternionTestObj1, quaternionTestObj2, 2 * gDistance * ( 1 - gDistance ));

  DALI_CHECK_FAIL(quaternionCurrentRot != quaternionManualSquad, "Quaternion::Squad is failed " );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionOperatorMultiplicationWithVector3()
{
  const float MIN_ANGLE_PITCH = 0.0f, MIN_ANGLE_YAW = 10.0f, MAX_ANGLE_ROLL = 0.0f;
  float fReverseCount = 2.0f;

  Quaternion quaternionOperatorMulDivObj(MIN_ANGLE_PITCH, MIN_ANGLE_YAW, MIN_ANGLE_YAW + fReverseCount, MAX_ANGLE_ROLL);
  gQuaternion1=quaternionOperatorMulDivObj;

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed " );

  Stage::GetCurrent().Add(gActorQuaternion);
  gActorQuaternion.SetOrientation(quaternionOperatorMulDivObj);
}
void VTQuaternionOperatorMultiplicationWithVector3001()
{
  Vector3 vec3Multi(2.0f, 2.0f, 2.0f);
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();

  Vector3 vec3Result = quaternionCurrentRot * vec3Multi;

  Vector3 vec3CompareResult = gQuaternion1 * vec3Multi;
  DALI_CHECK_FAIL(vec3CompareResult != vec3Result , "Quaternion::operator*(Vector3) is failed" );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionByAngleVector3Axis()
{
  const float MAX_ROT_ANGLE = 90.0f;
  const int ROT_SCALING_FACTOR = 10;
  const Vector3 vect3(1.5f , 1.9f, 0.5f);

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL(!gActorQuaternion, "Actor::New() is failed " );

  Stage::GetCurrent().Add(gActorQuaternion);

  Quaternion quaternionConstructorByAngleVec3Axis(Radian(Degree(MAX_ROT_ANGLE  * ROT_SCALING_FACTOR)), vect3);

  gActorQuaternion.SetOrientation(quaternionConstructorByAngleVec3Axis);
}
void VTQuaternionByAngleVector3Axis001()
{
  const float MAX_ROT_ANGLE = 90.0f;
  const int ROT_SCALING_FACTOR = 10;
  const Vector3 vect3(1.5f , 1.9f, 0.5f);

  Quaternion quaternionConstructorByAngleVec3Axis(Radian(Degree(MAX_ROT_ANGLE  * ROT_SCALING_FACTOR)), vect3);
  Quaternion quaternionCurrentRot = gActorQuaternion.GetCurrentOrientation();
  DALI_CHECK_FAIL(quaternionCurrentRot != quaternionConstructorByAngleVec3Axis, "Quaternion::Quaternion(float,const Vector3 &) is failed" );

  Stage::GetCurrent().Remove(gActorQuaternion);

  DaliLog::PrintPass();
}
void QuaternionByTwoVector3(void)
{
  Vector3 vec3One( 5.0f, 2.0f, 3.0f );
  Vector3 vec3Two( -2.0f, 7.0f, -1.0f );

  vec3One.Normalize();
  vec3Two.Normalize();
  Quaternion quaternion( vec3One, vec3Two );

  gConstructCheck = QuaternionCompareVector3(quaternion*vec3One, vec3Two, QUATERNION_TOLERANCE);

  gActorQuaternion = Actor::New();
  DALI_CHECK_FAIL( !gActorQuaternion, "Actor handle is empty." );

  gActorQuaternion.SetOrientation( quaternion );
  Stage::GetCurrent().Add( gActorQuaternion );
}
void VTQuaternionByTwoVector3001(void)
{
  bool bRetrieveCheck = false;
  Vector3 vec3One( 5.0f, 2.0f, 3.0f );
  Vector3 vec3Two( -2.0f, 7.0f, -1.0f );

  vec3One.Normalize();
  vec3Two.Normalize();
  Quaternion quaternion( vec3One, vec3Two );

  Quaternion quaternionGet = gActorQuaternion.GetCurrentOrientation();
  bRetrieveCheck = QuaternionCompare( quaternionGet, quaternion, QUATERNION_TOLERANCE );

  DALI_CHECK_FAIL( !gConstructCheck || !bRetrieveCheck, "Quaternion::Quaternion(const Vector3&, const Vector3&) is failed." );

  Stage::GetCurrent().Remove( gActorQuaternion );
  DaliLog::PrintPass();
}
void QuaternionSubstractAssignOStreamOperator()
{
  Quaternion quaternionOne( 0.123f, 0.924f, 0.383f, 0.450f );
  Quaternion quaternionTwo( 0.234f, 1.917f, 0.383f, 0.690f );

  Quaternion quaternionResult( 0.111f, 0.993f, 0.0f, 0.240f );
  ostringstream ossResult;
  ossResult << quaternionResult;

  quaternionTwo -= quaternionOne;
  DALI_CHECK_FAIL( !QuaternionCompare(quaternionTwo, quaternionResult, QUATERNION_TOLERANCE), "Quaternion::operator-= is failed." );

  ostringstream ossSubAssign;
  ossSubAssign << quaternionTwo;

  DALI_CHECK_FAIL( ossSubAssign.str() != ossResult.str(), "The output stream operator is failed for Quaternion is failed to print expected result." );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/
