#include "utc-dali-vector-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;
#define ZERO 0

//& set: Vector

/**
 * @function      utc_Dali_Vector_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */
void utc_Dali_Vector_startup(void)
{
  test_return_value = 0;
}

/**
 * @function      utc_Dali_Vector_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void utc_Dali_Vector_cleanup(void)
{

}

void VectorResizeP();
void VectorResizeP2();
void VectorOperatorAssignmentP();
void VectorPushbackP();
void VectorInsertP();
void VectorInsertP2();
void VectorReserveP();
void VectorEraseP();
void VectorEraseP2();
void VectorRemoveP();
void VectorSwapP();
void VectorClearP();
void VectorReleaseP();
void VectorCopyConstructorP();

namespace
{
  enum TEST_CASES_LIST_VECTOR
  {
    VECTOR_RESIZE_P,
    VECTOR_RESIZE_P2,
    VECTOR_OPERATOR_ASSIGNMENT_P,
    VECTOR_PUSHBACK_P,
    VECTOR_INSERT_P,
    VECTOR_INSERT_P2,
    VECTOR_RESERVE_P,
    VECTOR_ERASE_P,
    VECTOR_ERASE_P2,
    VECTOR_REMOVE_P,
    VECTOR_SWAP_P,
    VECTOR_CLEAR_P,
    VECTOR_RELEASE_P,
    VECTOR_COPY_CONSTRUCTOR_P
  };

  struct Vector_TestApp : public ConnectionTracker
  {
    Vector_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Vector_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Vector_TestApp::Tick );
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
        case VECTOR_RESIZE_P:
          VectorResizeP();
          break;

        case VECTOR_RESIZE_P2:
          VectorResizeP2();
          break;

        case VECTOR_OPERATOR_ASSIGNMENT_P:
          VectorOperatorAssignmentP();
          break;

        case VECTOR_PUSHBACK_P:
          VectorPushbackP();
          break;

        case VECTOR_INSERT_P:
          VectorInsertP();
          break;

        case VECTOR_INSERT_P2:
          VectorInsertP2();
          break;

        case VECTOR_RESERVE_P:
          VectorReserveP();
          break;

        case VECTOR_ERASE_P:
          VectorEraseP();
          break;

        case VECTOR_ERASE_P2:
          VectorEraseP2();
          break;

        case VECTOR_REMOVE_P:
          VectorRemoveP();
          break;

        case VECTOR_SWAP_P:
          VectorSwapP();
          break;

        case VECTOR_CLEAR_P:
          VectorClearP();
          break;

        case VECTOR_RELEASE_P:
          VectorReleaseP();
          break;

        case VECTOR_COPY_CONSTRUCTOR_P:
          VectorCopyConstructorP();
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

void VectorResizeP()
{
  Vector< int > intVector;
  VectorBase::SizeType nsizeSet = 12;

  intVector.PushBack( 1 );
  intVector.PushBack( 2 );
  intVector.PushBack( 3 );
  intVector.PushBack( 4 );
  intVector.PushBack( 5 );

  Vector< int >::Iterator iRet;
  iRet = intVector.Erase( intVector.Begin() + 1u, intVector.Begin() + 2u );
  DALI_CHECK_FAIL(intVector[0] != 1 || intVector[1] != 3 || intVector[2] != 4 || intVector[3] != 5  || *iRet != 3 , "Erase  is failed to Erase the range of item from the vector ");

  intVector.Erase(iRet);
  DALI_CHECK_FAIL(intVector[1] == 3, "Erase  is failed to Erase the range of item from the vector ");
  intVector.Insert( iRet, 22 );
  DALI_CHECK_FAIL(*iRet != 22, "Erase  is failed to Erase the range of item from the vector ");

  intVector.Resize( nsizeSet, 123 );
  DALI_CHECK_FAIL( static_cast<Dali::VectorBase::SizeType>(12) != intVector.Capacity() || intVector[ nsizeSet-1 ] != 123 , "Resize is failed to resize item  ");

  DaliLog::PrintPass();
}

void VectorResizeP2()
{
  Vector< int > intVector;
  VectorBase::SizeType nsizeSet = 12;

  intVector.PushBack( 1 );
  intVector.PushBack( 2 );
  intVector.PushBack( 3 );
  intVector.PushBack( 4 );
  intVector.PushBack( 5 );

  Vector< int >::Iterator iRet;
  iRet = intVector.Erase( intVector.Begin() + 1u, intVector.Begin() + 2u );
  DALI_CHECK_FAIL(intVector[0] != 1 || intVector[1] != 3 || intVector[2] != 4 || intVector[3] != 5  || *iRet != 3 , "Erase  is failed to Erase the range of item from the vector ");

  intVector.Erase(iRet);
  DALI_CHECK_FAIL(intVector[1] == 3, "Erase  is failed to Erase the range of item from the vector ");
  intVector.Insert( iRet, 22 );
  DALI_CHECK_FAIL(*iRet != 22, "Erase  is failed to Erase the range of item from the vector ");

  intVector.Resize( nsizeSet );
  DALI_CHECK_FAIL( static_cast<Dali::VectorBase::SizeType>(12) != intVector.Capacity() , "Resize is failed to resize item  ");

  DaliLog::PrintPass();
}

void VectorOperatorAssignmentP()
{
  Vector< int > intvector;
  intvector.PushBack( 99 );
  intvector.PushBack( 11 );
  intvector.PushBack( 34 );

  Vector< int > intvector2;
  intvector2 = intvector;
  DALI_CHECK_FAIL( intvector2.Count() != intvector.Count() || intvector2.Capacity() != intvector.Capacity(), "Assignment operator is failed to assign the vector object one to another ");

  DaliLog::PrintPass();
}

void VectorCopyConstructorP()
{
  Vector< int > intvector;
  intvector.PushBack( 99 );
  intvector.PushBack( 11 );
  intvector.PushBack( 34 );

  // copy construct
  Vector< int > intvector2( intvector );
  DALI_CHECK_FAIL( intvector2.Count() != intvector.Count() || intvector2.Capacity() != intvector.Capacity(), "Copy constructor is failed to copy the vector object ");

  DaliLog::PrintPass();
}

void VectorPushbackP()
{
  Vector< int > intVector;
  intVector.PushBack( 1 );
  intVector.PushBack( 2 );
  intVector.PushBack( 3 );
  intVector.PushBack( 4 );
  intVector.PushBack( 5 );

  DALI_CHECK_FAIL( static_cast<Dali::VectorBase::SizeType>(5) != intVector.Count(), "Pushback is failed." );

  DaliLog::PrintPass();
}

void VectorInsertP()
{
  Vector< char > vector;
  vector.PushBack( 1 );
  vector.PushBack( 2 );
  vector.PushBack( 3 );
  vector.PushBack( 4 );
  vector.PushBack( 5 );

  vector.Insert( vector.End(), 6 );
  DALI_CHECK_FAIL( vector[ 5 ] != 6, "Insert is failed");

  DaliLog::PrintPass();
}

void VectorInsertP2()
{
  Vector< char > vector;
  vector.PushBack( 1 );
  vector.PushBack( 2 );
  vector.PushBack( 3 );
  vector.PushBack( 4 );
  vector.PushBack( 5 );

  Vector< char > vector2;
  vector2.PushBack( 6 );
  vector2.PushBack( 7 );
  vector2.PushBack( 8 );
  vector2.PushBack( 9 );
  vector2.PushBack( 10 );

  // Test insert at end
  vector.Insert( vector.End(), vector2.Begin(), vector2.Begin() + 1u );
  DALI_CHECK_FAIL( vector[ 0 ] != 1, "Insert is failed");
  DALI_CHECK_FAIL( vector[ 1 ] != 2, "Insert is failed");
  DALI_CHECK_FAIL( vector[ 2 ] != 3, "Insert is failed");
  DALI_CHECK_FAIL( vector[ 3 ] != 4, "Insert is failed");
  DALI_CHECK_FAIL( vector[ 4 ] != 5, "Insert is failed");
  DALI_CHECK_FAIL( vector[ 5 ] != 6, "Insert is failed");

  DaliLog::PrintPass();
}

void VectorReserveP()
{
  Vector<unsigned int> vector;
  DALI_CHECK_FAIL( ZERO != vector.Count(), "Default constuctor is failed." );
  DALI_CHECK_FAIL( ZERO != vector.Capacity(), "Default Constructor is failed.");

  vector.Reserve( 2u );
  DALI_CHECK_FAIL( ZERO != vector.Count(), "Reserve is failed.");
  DALI_CHECK_FAIL( 2u != vector.Capacity(), "Reserve is failed");

  DaliLog::PrintPass();
}

void VectorEraseP()
{
  Vector< int > intVector;
  VectorBase::SizeType nsizeSet = 12;

  intVector.PushBack( 1 );
  intVector.PushBack( 2 );
  intVector.PushBack( 3 );
  intVector.PushBack( 4 );
  intVector.PushBack( 5 );

  Vector< int >::Iterator iRet;
  iRet = intVector.Erase( intVector.Begin() + 1u, intVector.Begin() + 2u );
  DALI_CHECK_FAIL(intVector[0] !=  1 || intVector[1] !=  3 || intVector[2] !=  4 || intVector[3] !=  5  || *iRet != 3 , "Erase  is failed to Erase the range of item from the vector ");

  DaliLog::PrintPass();
}

void VectorEraseP2()
{
  Vector< int > intVector;
  VectorBase::SizeType nsizeSet = 12;

  intVector.PushBack( 1 );
  intVector.PushBack( 2 );
  intVector.PushBack( 3 );
  intVector.PushBack( 4 );
  intVector.PushBack( 5 );

  Vector< int >::Iterator iRet;
  iRet = intVector.Erase( intVector.Begin() + 1u, intVector.Begin() + 2u );
  DALI_CHECK_FAIL(intVector[0] !=  1 || intVector[1] !=  3 || intVector[2] !=  4 || intVector[3] !=  5  || *iRet != 3 , "Erase  is failed to Erase the range of item from the vector ");

  intVector.Erase(iRet);
  DALI_CHECK_FAIL(intVector[1] ==  3, "Erase  is failed to Erase the range of item from the vector ");

  DaliLog::PrintPass();
}

void VectorRemoveP()
{
  VectorBase::SizeType nGetSize = 0  , nSizeCount = 0 ;
  Vector< int > intvector;

  intvector.PushBack( 99 );
  intvector.PushBack( 11 );
  intvector.PushBack( 34 );

  nGetSize = intvector.Count();
  DALI_CHECK_FAIL(static_cast<Dali::VectorBase::SizeType>(3) != nGetSize , "Count is changed match with the expected value ");

  Vector< int > intvector2;
  intvector2.Swap( intvector );
  nGetSize = intvector.Count();
  nSizeCount = intvector2.Count();
  DALI_CHECK_FAIL(nGetSize != 0 || nSizeCount != static_cast<Dali::VectorBase::SizeType>(3)  , "swap failed to swap the vector ");

  intvector2.Remove( intvector2.End() - 1 );
  nSizeCount = intvector2.Count();
  DALI_CHECK_FAIL(nSizeCount != static_cast<Dali::VectorBase::SizeType>(2), "Remove  is failed to remove the item from the vector ");

  DaliLog::PrintPass();
}

void VectorSwapP()
{
  VectorBase::SizeType nGetSize = 0  , nSizeCount = 0 ;
  Vector< int > intvector;

  intvector.PushBack( 99 );
  intvector.PushBack( 11 );
  intvector.PushBack( 34 );
  nGetSize = intvector.Count();
  DALI_CHECK_FAIL(static_cast<Dali::VectorBase::SizeType>(3) != nGetSize , "Count is changed match with the expected value ");

  Vector< int > intvector2;
  intvector2.Swap( intvector );
  nGetSize = intvector.Count();
  nSizeCount = intvector2.Count();
  DALI_CHECK_FAIL(nGetSize != 0 || nSizeCount != static_cast<Dali::VectorBase::SizeType>(3)  , "swap failed to swap the vector ");

  intvector2.Remove( intvector2.End() - 1 );
  nSizeCount = intvector2.Count();
  DALI_CHECK_FAIL(nSizeCount != static_cast<Dali::VectorBase::SizeType>(2), "Remove  is failed to remove the item from the vector ");

  DaliLog::PrintPass();
}

void VectorClearP()
{
  Vector<unsigned int> vector;
  DALI_CHECK_FAIL( ZERO != vector.Count(), "Default constuctor is failed." );
  DALI_CHECK_FAIL( ZERO != vector.Capacity(), "Default Constructor is failed.");

  vector.PushBack( 1 );
  vector.PushBack( 2 );
  vector.PushBack( 3 );
  vector.PushBack( 4 );
  vector.PushBack( 5 );

  vector.Clear();
  DALI_CHECK_FAIL( ZERO != vector.Count(), "clear is failed.");

  DaliLog::PrintPass();
}

void VectorReleaseP()
{
  Vector<unsigned int> vector;
  DALI_CHECK_FAIL( ZERO != vector.Count(), "Default constuctor is failed." );
  DALI_CHECK_FAIL( ZERO != vector.Capacity(), "Default Constructor is failed.");

  vector.PushBack( 1 );
  vector.PushBack( 2 );
  vector.PushBack( 3 );
  vector.PushBack( 4 );
  vector.PushBack( 5 );

  vector.Release();
  DALI_CHECK_FAIL( ZERO != vector.Capacity(), "release is failed.");

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase      UtcDaliVectorResizeP
 * @since_tizen   2.4
 * @description   check if Resize api works or not.
 */
int UtcDaliVectorResizeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector_TestApp testApp( application, VECTOR_RESIZE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliVectorResizeP2
 * @since_tizen   2.4
 * @description   check if Resize api works or not.
 */
int UtcDaliVectorResizeP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector_TestApp testApp( application, VECTOR_RESIZE_P2);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliVectorOperatorAssignmentP
 * @since_tizen   2.4
 * @description   check if OperatorAssignment api works or not.
 */
int UtcDaliVectorOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector_TestApp testApp( application, VECTOR_OPERATOR_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliVectorPushbackP
 * @since_tizen   2.4
 * @description   check if pushback api works or not.
 */
int UtcDaliVectorPushbackP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector_TestApp testApp( application, VECTOR_PUSHBACK_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliVectorInsertP
 * @since_tizen   2.4
 * @description   check if Insert api works or not.
 */
int UtcDaliVectorInsertP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector_TestApp testApp( application, VECTOR_INSERT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliVectorInsertP2
 * @since_tizen   2.4
 * @description   check if Insert api works or not.
 */
int UtcDaliVectorInsertP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector_TestApp testApp( application, VECTOR_INSERT_P2);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliVectorReserveP
 * @since_tizen   2.4
 * @description   check if Reserve api works or not.
 */
int UtcDaliVectorReserveP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector_TestApp testApp( application, VECTOR_RESERVE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliVectorEraseP
 * @since_tizen   2.4
 * @description   check if Erase api works or not.
 */
int UtcDaliVectorEraseP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector_TestApp testApp( application, VECTOR_ERASE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliVectorEraseP2
 * @since_tizen   2.4
 * @description   check if Erase api works or not.
 */
int UtcDaliVectorEraseP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector_TestApp testApp( application, VECTOR_ERASE_P2);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliVectorRemoveP
 * @since_tizen   2.4
 * @description   check if Remove api works or not.
 */
int UtcDaliVectorRemoveP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector_TestApp testApp( application, VECTOR_REMOVE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliVectorSwapP
 * @since_tizen   2.4
 * @description   check if Swap api works or not.
 */
int UtcDaliVectorSwapP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector_TestApp testApp( application, VECTOR_SWAP_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliVectorClearP
 * @since_tizen   2.4
 * @description   check if Clear api works or not.
 */
int UtcDaliVectorClearP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector_TestApp testApp( application, VECTOR_CLEAR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliVectorCopyConstructorP
 * @since_tizen   2.4
 * @description   check if copy constructor works or not.
 */
int UtcDaliVectorCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector_TestApp testApp( application, VECTOR_COPY_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliVectorReleaseP
 * @since_tizen   2.4
 * @description   check if Release api works or not.
 */
int UtcDaliVectorReleaseP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector_TestApp testApp( application, VECTOR_RELEASE_P);
  application.MainLoop();
  return test_return_value;
}
