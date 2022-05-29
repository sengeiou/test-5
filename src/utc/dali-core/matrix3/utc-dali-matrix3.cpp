#include "utc-dali-matrix3-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_Matrix3_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Matrix3_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_Matrix3_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Matrix3_cleanup(void)
{

}

void Matrix3Constructor();
void Matrix3ConstructorP2();
void Matrix3CopyConstructor();
void Matrix3CopyConstructorP2();
void Matrix3Scale();
void Matrix3OperatorAssignment();
void Matrix3OperatorEqualityCheck();
void Matrix3OperatorInEqualityCheck();
void Matrix3Magnitude();
void Matrix3ScaledInverseTranspose();
void Matrix3AsFloat();
void Matrix3Invert();
void Matrix3SetIdentity();
void Matrix3Transpose();
void Matrix3MultiplyOStream();
namespace
{
  enum TEST_CASES_LIST_MATRIX3
  {
    MATRIX3_CONSTRUCTOR,
    MATRIX3_CONSTRUCTOR_P2,
    MATRIX3_COPY_CONSTRUCTOR,
    MATRIX3_COPY_CONSTRUCTOR_P2,
    MATRIX3_OPERATOR_ASSIGNMENT,
    MATRIX3_SCALE,
    MATRIX3_MAGNITUDE,
    MATRIX3_SCALED_INVERSE_TRANSPOSE,
    MATRIX3_AS_FLOAT,
    MATRIX3_INVERT,
    MATRIX3_SET_IDENTITY,
    MATRIX3_TRANSPOSE,
    MATRIX3_OPERATOR_EQUALITY_CHECK,
    MATRIX3_OPERATOR_INEQUALITY_CHECK,
    MATRIX3_MULTIPLY_OSTREAM
  };

  struct Matrix3_TestApp : public ConnectionTracker
  {
    Matrix3_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Matrix3_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Matrix3_TestApp::Tick );
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
        case MATRIX3_CONSTRUCTOR:
          Matrix3Constructor();
          break;

        case MATRIX3_CONSTRUCTOR_P2:
          Matrix3ConstructorP2();
          break;

        case MATRIX3_COPY_CONSTRUCTOR:
          Matrix3CopyConstructor();
          break;

        case MATRIX3_COPY_CONSTRUCTOR_P2:
          Matrix3CopyConstructorP2();
          break;

        case MATRIX3_OPERATOR_ASSIGNMENT:
          Matrix3OperatorAssignment();
          break;

        case MATRIX3_SCALE:
          Matrix3Scale();
          break;

        case MATRIX3_MAGNITUDE:
          Matrix3Magnitude();
          break;

        case MATRIX3_SCALED_INVERSE_TRANSPOSE:
          Matrix3ScaledInverseTranspose();
          break;

        case MATRIX3_AS_FLOAT:
          Matrix3AsFloat();
          break;

        case MATRIX3_INVERT:
          Matrix3Invert();
          break;

        case MATRIX3_SET_IDENTITY:
          Matrix3SetIdentity();
          break;

        case MATRIX3_TRANSPOSE:
          Matrix3Transpose();
          break;

        case MATRIX3_OPERATOR_EQUALITY_CHECK:
          Matrix3OperatorEqualityCheck();
          break;

        case MATRIX3_OPERATOR_INEQUALITY_CHECK:
          Matrix3OperatorInEqualityCheck();
          break;

        case MATRIX3_MULTIPLY_OSTREAM:
          Matrix3MultiplyOStream();
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
void Matrix3Constructor()
{
  Matrix3 mat3();
  DaliLog::PrintPass();
}
void Matrix3ConstructorP2()
{
  Matrix3 m0(0.0f,  1.0f,  2.0f,
      4.0f,  5.0f,  6.0f,
      8.0f,  9.0f, 10.0f);

  Matrix3 m1(0.0f,  1.0f,  2.0f,
      4.0f,  5.0f,  6.0f,
      8.0f,  9.0f, 10.0f);

  Matrix3 m2;
  m2 = m0;

  DALI_CHECK_FAIL(m1!=m2,  "Matrix3::constructor failed." );

  DaliLog::PrintPass();
}
void Matrix3CopyConstructor()
{
  float els0[] = { 0.0f,  1.0f,  2.0f, 3.0f,
    4.0f,  5.0f,  6.0f, 7.0f,
    8.0f,  9.0f, 10.0f, 11.0f,
    12.0f, 13.0f, 14.0f, 15.0f};
  Matrix m0(els0);
  Matrix3 m1(0.0f,  1.0f,  2.0f,
      4.0f,  5.0f,  6.0f,
      8.0f,  9.0f, 10.0f);

  Matrix3 m2(m0);
  DALI_CHECK_FAIL(m2 != m1,  "Matrix3::Copy constructor failed." );

  DaliLog::PrintPass();
}
void Matrix3CopyConstructorP2()
{
  float els0[] = { 0.0f,  1.0f,  2.0f, 3.0f,
    4.0f,  5.0f,  6.0f, 7.0f,
    8.0f,  9.0f, 10.0f, 11.0f,
    12.0f, 13.0f, 14.0f, 15.0f};
  Matrix m0(els0);
  Matrix3 m1(0.0f,  1.0f,  2.0f,
      4.0f,  5.0f,  6.0f,
      8.0f,  9.0f, 10.0f);

  Matrix3 m2(m0);

  DALI_CHECK_FAIL(m2 != m1,  "Matrix3::Copy constructor failed." );


  DaliLog::PrintPass();
}
void Matrix3Scale()
{

  Matrix3 m1( 0.0f,  1.0f,  2.0f,
      4.0f,  5.0f,  6.0f,
      8.0f,  9.0f, 10.0f);

  Matrix3 m2( 0.0f,  3.0f,  6.0f,
      12.0f,  15.0f, 18.0f,
      24.0f,  27.0f, 30.0f);

  m1.Scale(3.0f);

  DaliLog::PrintPass();
}
void Matrix3Magnitude()
{
  float rgfSetVals[] = {    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f,
    7.0f, 8.0f, 9.0f, };
  Matrix3 mat3(    rgfSetVals[s00], rgfSetVals[s01], rgfSetVals[s02],
      rgfSetVals[s10], rgfSetVals[s11], rgfSetVals[s12],
      rgfSetVals[s20], rgfSetVals[s21], rgfSetVals[s22]  );

  DALI_CHECK_FAIL(Matrix3GetMagnitude(rgfSetVals) * N_OF_MATRIX_SIZE_NxN != mat3.Magnitude(), "Matrix3::Magnitude() is failed. Magnitude does not return the average of the absolute values of the elements * 3." );

  DaliLog::PrintPass();
}
void Matrix3ScaledInverseTranspose()
{
  float rgfSetVals[] = {    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f,
    7.0f, 8.0f, 10.0f, };
  Matrix3 mat3(    rgfSetVals[s00], rgfSetVals[s01], rgfSetVals[s02],
      rgfSetVals[s10], rgfSetVals[s11], rgfSetVals[s12],
      rgfSetVals[s20], rgfSetVals[s21], rgfSetVals[s22]  );
  Matrix3 mat3Origin(mat3);

  DALI_CHECK_FAIL(!mat3.Invert(),  "Matrix3::Invert() is failed. some rows are not linearly independent." );
  DALI_CHECK_FAIL(!mat3.Transpose(),  "Matrix3::Transpose() is failed. Its not a non-empty 3x3 matrix" );

  float inverseMagnitude = N_OF_MATRIX_SIZE_NxN/ mat3.Magnitude();
  mat3.Scale(inverseMagnitude);

  DALI_CHECK_FAIL(!mat3Origin.ScaledInverseTranspose(),  "Matrix3::ScaledInverseTranspose() is failed. Not in invertible matrix." );
  DALI_CHECK_FAIL(mat3 != mat3Origin,  "Matrix3::ScaledInverseTranspose() is failed. matrix mismatched with custom calculated matrix." );

  DaliLog::PrintPass();
}
void Matrix3AsFloat()
{
  float rgfpSetValue1[] = {    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f,
    7.0f, 8.0f, 9.0f,
  };

  float *rgfpSetValue2 = NULL;
  bool bResult = false;
  Matrix3 mat3(    rgfpSetValue1[s00], rgfpSetValue1[s01], rgfpSetValue1[s02],
      rgfpSetValue1[s10], rgfpSetValue1[s11], rgfpSetValue1[s12],
      rgfpSetValue1[s20], rgfpSetValue1[s21], rgfpSetValue1[s22]  );
  bResult = true;
  rgfpSetValue2 = mat3.AsFloat();

  for(int i =0; i< ELEMENTS_COUNT;i++)
  {
    bResult &= (rgfpSetValue2[i] ==  rgfpSetValue1[i]);
  }

  DALI_CHECK_FAIL(!bResult,  "Dali::AsFloat is Failed: matrix3 to float array pointer convertion is failed" );

  DaliLog::PrintPass();
}
void Matrix3Invert()
{
  float rgfpSetValue1[] = {    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f,
    7.0f, 8.0f, 10.0f,
  };

  bool bResult = false;
  Matrix3 mat3(    rgfpSetValue1[s00], rgfpSetValue1[s01], rgfpSetValue1[s02],
      rgfpSetValue1[s10], rgfpSetValue1[s11], rgfpSetValue1[s12],
      rgfpSetValue1[s20], rgfpSetValue1[s21], rgfpSetValue1[s22]  );
  Matrix3 mat3Copy(mat3);
  bResult = mat3.Invert();
  DALI_CHECK_FAIL(!bResult,  "Dali::Matrix::Invert is Failed." );
  if(mat3Copy == mat3)
  {
    LOG_E("Dali::Matrix3::Invert() is failed for matching with initial and inverted matrices.");
    cout << "[I][" << SUITE_NAME << "][LINE: " << __LINE__ << "] Initial matrix " << mat3Copy << endl;
    cout << "[I][" << SUITE_NAME << "][LINE: " << __LINE__ << "] Inverted matrix " << mat3 << endl;
    test_return_value=1;
    return;
  }
  DaliLog::PrintPass();
}
void Matrix3SetIdentity()
{
  float rgfpSetValue1[] = {    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f,
    7.0f, 8.0f, 9.0f,
  };

  Matrix3 mat3(    rgfpSetValue1[s00], rgfpSetValue1[s01], rgfpSetValue1[s02],
      rgfpSetValue1[s10], rgfpSetValue1[s11], rgfpSetValue1[s12],
      rgfpSetValue1[s20], rgfpSetValue1[s21], rgfpSetValue1[s22]  );

  mat3.SetIdentity();
  DALI_CHECK_FAIL(mat3 != Matrix::IDENTITY,  "Dali::Matrix::SetIdentity is Failed." );

  DaliLog::PrintPass();
}
void Matrix3Transpose()
{
  float rgfpSetValue1[] = {     0.0f,  1.0f,  2.0f,
    3.0f,  4.0f,  5.0f,
    6.0f,  7.0f,  8.0f };
  const int ROWS = 3, COLS = 3;
  bool bSuccess = true;
  Matrix3 mat3(    rgfpSetValue1[s00], rgfpSetValue1[s01], rgfpSetValue1[s02],
      rgfpSetValue1[s10], rgfpSetValue1[s11], rgfpSetValue1[s12],
      rgfpSetValue1[s20], rgfpSetValue1[s21], rgfpSetValue1[s22]  );

  mat3.Transpose();
  for (int x=0;x<ROWS;++x)
  {
    for (int y=0;y<COLS;++y)
    {
      bSuccess &= (mat3.AsFloat()[x+y*ROWS] == rgfpSetValue1[x*COLS+y]);
    }
  }

  DALI_CHECK_FAIL(!bSuccess,  "Dali::Matrix::Transpose is Failed." );

  DaliLog::PrintPass();
}
void Matrix3OperatorAssignment()
{

  float els0[] = { 0.0f,  1.0f,  2.0f, 3.0f,
    4.0f,  5.0f,  6.0f, 7.0f,
    8.0f,  9.0f, 10.0f, 11.0f,
    12.0f, 13.0f, 14.0f, 15.0f};
  Matrix m0(els0);

  Matrix3 m1(0.0f,  1.0f,  2.0f,
      4.0f,  5.0f,  6.0f,
      8.0f,  9.0f, 10.0f);

  Matrix3 m2;
  m2 = m0;
  m2 = m2;
  DALI_CHECK_FAIL(m1 != m2,  "Dali::Matrix::Asignment is Failed." );

  DaliLog::PrintPass();
}
void Matrix3OperatorEqualityCheck()
{
  float rgfpSetValue1[] = {     1.0f,  0.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  0.0f,  1.0f
  };

  float rgfpSetValue2[] = {     1.0f,  0.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  0.0f,  1.0f
  };
  bool bEqual = false;
  Matrix3 mat1(    rgfpSetValue1[s00], rgfpSetValue1[s01], rgfpSetValue1[s02],
      rgfpSetValue1[s10], rgfpSetValue1[s11], rgfpSetValue1[s12],
      rgfpSetValue1[s20], rgfpSetValue1[s21], rgfpSetValue1[s22]  );
  Matrix3 mat2(    rgfpSetValue2[s00], rgfpSetValue2[s01], rgfpSetValue2[s02],
      rgfpSetValue2[s10], rgfpSetValue2[s11], rgfpSetValue2[s12],
      rgfpSetValue2[s20], rgfpSetValue2[s21], rgfpSetValue2[s22]  );

  bEqual = (mat1 == mat2);
  DALI_CHECK_FAIL(!bEqual,  "The equality operator is failed." );

  DaliLog::PrintPass();
}
void Matrix3OperatorInEqualityCheck()
{
  float rgfpSetValue1[] = {     1.0f,  0.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  0.0f,  1.0f
  };

  float rgfpSetValue2[] = {     1.0f,  0.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  0.0f,  1.0f
  };
  bool bEqual = false;
  Matrix3 mat1(    rgfpSetValue1[s00], rgfpSetValue1[s01], rgfpSetValue1[s02],
      rgfpSetValue1[s10], rgfpSetValue1[s11], rgfpSetValue1[s12],
      rgfpSetValue1[s20], rgfpSetValue1[s21], rgfpSetValue1[s22]  );
  Matrix3 mat2(    rgfpSetValue2[s00], rgfpSetValue2[s01], rgfpSetValue2[s02],
      rgfpSetValue2[s10], rgfpSetValue2[s11], rgfpSetValue2[s12],
      rgfpSetValue2[s20], rgfpSetValue2[s21], rgfpSetValue2[s22]  );

  bEqual = (mat1 != mat2);
  DALI_CHECK_FAIL(bEqual,  "The equality operator is failed." );

  DaliLog::PrintPass();
}
void Matrix3MultiplyOStream()
{
  bool bResultCheck = false;
  int nS_ZERO = 0, nS_ONE = 0, nS_TWO = 0;
  float fValueZero = 0.0f, fValueOne  = 0.0f, fValueTwo  = 0.0f;

  float rgfpSetValueOne[] = { 0.0f,  1.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    0.0f,  0.0f,  1.0f};

  float rgfpSetValueTwo[] = { 0.0f,  3.0f,  6.0f,
    12.0f,  15.0f, 18.0f,
    24.0f,  27.0f, 30.0f };

  float rgfResultMatrix3[ELEMENTS_COUNT] = {0.0f};

  Matrix3 mat3Result;
  const Matrix3 MATRIX3_ONE(    rgfpSetValueOne[s00], rgfpSetValueOne[s01], rgfpSetValueOne[s02],
      rgfpSetValueOne[s10], rgfpSetValueOne[s11], rgfpSetValueOne[s12],
      rgfpSetValueOne[s20], rgfpSetValueOne[s21], rgfpSetValueOne[s22]  );

  const Matrix3 MATRIX3_TWO(    rgfpSetValueTwo[s00], rgfpSetValueTwo[s01], rgfpSetValueTwo[s02],
      rgfpSetValueTwo[s10], rgfpSetValueTwo[s11], rgfpSetValueTwo[s12],
      rgfpSetValueTwo[s20], rgfpSetValueTwo[s21], rgfpSetValueTwo[s22]  );

  //Calculation of two 3x3 matrices using mathematical formular
  const int ROW_COL = sqrt( ELEMENTS_COUNT );
  for( int nI = 0; nI < ROW_COL; nI++ )
  {
    nS_ONE   = nS_ZERO + s01;
    nS_TWO   = nS_ZERO + s02;

    fValueZero = rgfpSetValueOne[nS_ZERO];
    fValueOne  = rgfpSetValueOne[nS_ONE];
    fValueTwo  = rgfpSetValueOne[nS_TWO];

    rgfResultMatrix3[nS_ZERO]  = (fValueZero * rgfpSetValueTwo[s00]) + (fValueOne * rgfpSetValueTwo[s10]) + (fValueTwo * rgfpSetValueTwo[s20]);
    rgfResultMatrix3[nS_ONE]   = (fValueZero * rgfpSetValueTwo[s01]) + (fValueOne * rgfpSetValueTwo[s11]) + (fValueTwo * rgfpSetValueTwo[s21]);
    rgfResultMatrix3[nS_TWO]   = (fValueZero * rgfpSetValueTwo[s02]) + (fValueOne * rgfpSetValueTwo[s12]) + (fValueTwo * rgfpSetValueTwo[s22]);

    nS_ZERO = nS_ZERO + ROW_COL;
  }

  Matrix3 mat3ResultCalculated(  rgfResultMatrix3[s00], rgfResultMatrix3[s01], rgfResultMatrix3[s02],
      rgfResultMatrix3[s10], rgfResultMatrix3[s11], rgfResultMatrix3[s12],
      rgfResultMatrix3[s20], rgfResultMatrix3[s21], rgfResultMatrix3[s22]);

  //Multiplication of two 3x3 matrices using API
  Matrix3::Multiply(mat3Result, MATRIX3_ONE, MATRIX3_TWO);

  bResultCheck = Matrix3CheckEquals( mat3Result, mat3ResultCalculated );
  DALI_CHECK_FAIL( !bResultCheck , "Matrix3::Multiply is failed." );

  ostringstream oStringStreamResult;
  oStringStreamResult << mat3Result;

  ostringstream oStringStreamCalculated;
  oStringStreamCalculated << mat3ResultCalculated;

  DALI_CHECK_FAIL( oStringStreamResult.str() != oStringStreamCalculated.str() , "The output stream operator for Matrix3 is failed to print expected result." );

  DaliLog::PrintPass();
}
/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase             UtcDaliMatrix3ConstructorP
 * @since_tizen            2.4
 * @description            Check that magnitude returns the average of the absolute values of the elements * 3 and which is positive
 */

int UtcDaliMatrix3ConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix3_TestApp testApp( application, MATRIX3_CONSTRUCTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliMatrix3ConstructorP2
 * @since_tizen            2.4
 * @description            Check that magnitude returns the average of the absolute values of the elements * 3 and which is positive
 */

int UtcDaliMatrix3ConstructorP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix3_TestApp testApp( application, MATRIX3_CONSTRUCTOR_P2);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliMatrix3CopyConstructorP
 * @since_tizen          2.4
 * @description          Check that magnitude returns the average of the absolute values of the elements * 3 and which is positive
 */

int UtcDaliMatrix3CopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix3_TestApp testApp( application, MATRIX3_COPY_CONSTRUCTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliMatrix3CopyConstructorP2
 * @since_tizen          2.4
 * @description          Check that magnitude returns the average of the absolute values of the elements * 3 and which is positive
 */

int UtcDaliMatrix3CopyConstructorP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix3_TestApp testApp( application, MATRIX3_COPY_CONSTRUCTOR_P2);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliMatrix3ScaleP
 * @since_tizen          2.4
 * @description          Check that magnitude returns the average of the absolute values of the elements * 3 and which is positive
 */

int UtcDaliMatrix3ScaleP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix3_TestApp testApp( application, MATRIX3_SCALE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliMatrix3MagnitudeP
 * @since_tizen          2.4
 * @description          Check that magnitude returns the average of the absolute values of the elements * 3 and which is positive
 */

int UtcDaliMatrix3MagnitudeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix3_TestApp testApp( application, MATRIX3_MAGNITUDE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliMatrix3ScaledInverseTransposeP
 * @since_tizen          2.4
 * @description          Check that If the matrix is invertible, then this method inverts, transposes \n
 */

int UtcDaliMatrix3ScaledInverseTransposeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix3_TestApp testApp( application, MATRIX3_SCALED_INVERSE_TRANSPOSE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliMatrix3AsFloatP
 * @since_tizen          2.4
 * @description          Returns the contents of the matrix as an array of 9 floats.
 */

int UtcDaliMatrix3AsFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix3_TestApp testApp( application, MATRIX3_AS_FLOAT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliMatrix3InvertP
 * @since_tizen            2.4
 * @description            Inverts the matrix.
 */

int UtcDaliMatrix3InvertP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix3_TestApp testApp( application, MATRIX3_INVERT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliMatrix3SetIdentityP
 * @since_tizen          2.4
 * @description          Sets this matrix to be an identity matrix.
 */

int UtcDaliMatrix3SetIdentityP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix3_TestApp testApp( application, MATRIX3_SET_IDENTITY);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliMatrix3TransposeP
 * @since_tizen          2.4
 * @description          Swaps the rows to columns.
 */

int UtcDaliMatrix3TransposeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix3_TestApp testApp( application, MATRIX3_TRANSPOSE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliMatrix3OperatorAssignmentP
 * @since_tizen          2.4
 * @description          The equality operator.
 */
int UtcDaliMatrix3OperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix3_TestApp testApp( application, MATRIX3_OPERATOR_ASSIGNMENT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliMatrix3OperatorEqualityCheckP
 * @since_tizen          2.4
 * @description          The equality operator.
 */
int UtcDaliMatrix3OperatorEqualityCheckP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix3_TestApp testApp( application, MATRIX3_OPERATOR_EQUALITY_CHECK);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliMatrix3OperatorInEqualityCheckP
 * @since_tizen          2.4
 * @description          The equality operator.
 */
int UtcDaliMatrix3OperatorInEqualityCheckP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix3_TestApp testApp( application, MATRIX3_OPERATOR_INEQUALITY_CHECK);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase             UtcDaliMatrix3MultiplyOStreamP
 * @since_tizen          2.4
 * @description          Multiply two 3x3 matrices and print the result
 */
int UtcDaliMatrix3MultiplyOStreamP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Matrix3_TestApp testApp( application, MATRIX3_MULTIPLY_OSTREAM);
  application.MainLoop();
  return test_return_value;
}
