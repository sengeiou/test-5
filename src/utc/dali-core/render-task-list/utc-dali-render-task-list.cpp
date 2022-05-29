#include "utc-dali-render-task-list-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Rendertasklist

/**
 * @function            utc_Dali_Animation_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_rendertasklist_startup(void)
{
  test_return_value = 0;
}

/**
 * @function            utc_Dali_rendertasklist_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_rendertasklist_cleanup(void)
{
}

void RenderTaskListCreateTaskAndRemoveTaskP();
void RenderTaskListGetTaskAndGetTaskCountP();
void RenderTaskListCopyConstructorP();
void RenderTaskListConstructorP();
void RenderTaskListOperatorAssignmentP();
void RenderTaskListDownCastP();
void RenderTaskListDownCastN();

namespace
{
  enum TEST_CASES_LIST
  {
    RENDER_TAST_LIST_CREATE_TASK_REMOVE_TASK_P,
    RENDER_TAST_LIST_GET_TASK_COUNT_P,
    RENDER_TAST_LIST_CONSTRUCTOR_P,
    RENDER_TAST_LIST_COPY_CONSTRUCTOR_P,
    RENDER_TAST_LIST_OPERATORASSIGNMENT_P,
    RENDER_TAST_LIST_DOWNCAST_P,
    RENDER_TAST_LIST_DOWNCAST_N
  };

  struct TestApp : public ConnectionTracker
  {
    TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &TestApp::Tick );
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
        case RENDER_TAST_LIST_CREATE_TASK_REMOVE_TASK_P:
          RenderTaskListCreateTaskAndRemoveTaskP();
          break;

        case RENDER_TAST_LIST_GET_TASK_COUNT_P:
          RenderTaskListGetTaskAndGetTaskCountP();
          break;

        case RENDER_TAST_LIST_CONSTRUCTOR_P:
          RenderTaskListConstructorP();
          break;

        case RENDER_TAST_LIST_COPY_CONSTRUCTOR_P:
          RenderTaskListCopyConstructorP();
          break;

        case RENDER_TAST_LIST_OPERATORASSIGNMENT_P:
          RenderTaskListOperatorAssignmentP();
          break;

        case RENDER_TAST_LIST_DOWNCAST_N:
          RenderTaskListDownCastN();
          break;

        case RENDER_TAST_LIST_DOWNCAST_P:
          RenderTaskListDownCastP();
          break;
      }
    }

    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };
} // unnamed namespace

/**
 * @testcase        UtcDaliRenderTaskListCreateTaskAndRemoveTaskP
 * @since_tizen     2.4
 * @description     Checks whether CreateTask and RemoveTask api is executed successfully or not
 */
int UtcDaliRenderTaskListCreateTaskAndRemoveTaskP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TAST_LIST_CREATE_TASK_REMOVE_TASK_P);
  application.MainLoop();
  return test_return_value;
}

void RenderTaskListCreateTaskAndRemoveTaskP()
{
  Stage stage =  Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "Stage is empty." );

  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  DALI_CHECK_FAIL(renderTaskList.GetTaskCount() == 0, "renderTaskList is empty." );

  unsigned int uTaskCount = renderTaskList.GetTaskCount();

  RenderTask renderTask = renderTaskList.CreateTask();
  DALI_CHECK_FAIL(renderTaskList.GetTaskCount() != (uTaskCount + 1), "CreateTask is failed to create render task" );

  renderTaskList.RemoveTask(renderTask);
  DALI_CHECK_FAIL(renderTaskList.GetTaskCount() != uTaskCount, " RemoveTask is failed to remove render task." );

  DaliLog::PrintPass();
}


/**
 * @testcase        UtcDaliRenderTaskListGetTaskAndGetTaskCountP
 * @since_tizen     2.4
 * @description     Checks whether GetTask and GetTaskCount api is executed successfully or not
 */
int UtcDaliRenderTaskListGetTaskAndGetTaskCountP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TAST_LIST_GET_TASK_COUNT_P);
  application.MainLoop();
  return test_return_value;
}

void RenderTaskListGetTaskAndGetTaskCountP()
{
  int nTaskNumber = 0 ;

  Stage stage =  Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is empty." );

  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  DALI_CHECK_FAIL(renderTaskList.GetTaskCount() == 0, "enderTaskList is empty." );

  RenderTask defaultTask = renderTaskList.GetTask(nTaskNumber);
  DALI_CHECK_FAIL(!defaultTask, " etTask is failed to get RenderTask." );

  unsigned int uTaskCountDefault = renderTaskList.GetTaskCount();
  DALI_CHECK_FAIL(uTaskCountDefault != 1u, " GetTaskCount is failed to get RenderTask " );

  DaliLog::PrintPass();
}


/**
 * @testcase        UtcDaliRenderTaskListDownCastP
 * @since_tizen     2.4
 * @description     To Check RenderTaskList DownCast  Api is working properly or not.
 */
int UtcDaliRenderTaskListDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TAST_LIST_DOWNCAST_P);
  application.MainLoop();
  return test_return_value;
}

void RenderTaskListDownCastP()
{
  Stage stage =  Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "Stage is empty." );

  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  DALI_CHECK_FAIL(renderTaskList.GetTaskCount() == 0, "renderTaskList is empty." );

  BaseHandle baseHandle(renderTaskList);
  RenderTaskList renderTaskListDownCast = RenderTaskList::DownCast(baseHandle);
  DALI_CHECK_FAIL(!renderTaskListDownCast, "RenderTaskList DownCast is failed" );

  unsigned int uTaskCount = renderTaskListDownCast.GetTaskCount();
  DALI_CHECK_FAIL(uTaskCount != 1u, " GetTaskCount is failed to get RenderTask " );

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliRenderTaskListDownCastN
 * @since_tizen     2.4
 * @description     To Check RenderTaskList DownCast  Api is working properly or not.
 */
int UtcDaliRenderTaskListDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TAST_LIST_DOWNCAST_N);
  application.MainLoop();
  return test_return_value;
}

void RenderTaskListDownCastN()
{
  Stage stage =  Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "Stage is empty." );

  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  DALI_CHECK_FAIL(renderTaskList.GetTaskCount() == 0, "renderTaskList is empty." );

  Actor actor = Actor::New();
  BaseHandle baseHandle(actor);
  RenderTaskList renderTaskListDownCast = RenderTaskList::DownCast(baseHandle);
  DALI_CHECK_FAIL(renderTaskListDownCast, "RenderTaskList DownCast is failed" );

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliRenderTaskListCopyConstructorP
 * @since_tizen     2.4
 * @description     To Check RenderTaskList CopyConstructor  Api is working properly or not.
 */
int UtcDaliRenderTaskListCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TAST_LIST_COPY_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

void RenderTaskListCopyConstructorP()
{
  Stage stage =  Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "Stage is empty." );

  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  DALI_CHECK_FAIL(renderTaskList.GetTaskCount() == 0, "renderTaskList is empty." );
  renderTaskList.CreateTask(); //default task is 1u, task will be incremented by 1u after creating task by CreateTask()

  RenderTaskList renderTaskListCopyConst(renderTaskList);
  DALI_CHECK_FAIL(!renderTaskListCopyConst, "RenderTaskList copyconstructor  is failed " );

  unsigned int uTaskCount = renderTaskListCopyConst.GetTaskCount();
  DALI_CHECK_FAIL(uTaskCount != 2u, " GetTaskCount on RenderTaskListCopyConstructor is failed to get RenderTask " );

  DaliLog::PrintPass();
}


/**
 * @testcase        UtcDaliRenderTaskListConstructorP
 * @since_tizen     2.4
 * @description     To Check RenderTaskList default Constructor  Api is working properly or not.
 */
int UtcDaliRenderTaskListConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TAST_LIST_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

void RenderTaskListConstructorP()
{

  RenderTaskList renderTaskList;
  DALI_CHECK_FAIL(renderTaskList, "renderTaskList is empty." );

  DaliLog::PrintPass();
}

void RenderTaskListOperatorAssignmentP()
{

  RenderTaskList renderTaskList;
  DALI_CHECK_FAIL(renderTaskList, "renderTaskList is empty." );

  RenderTaskList renderTaskList2;
  renderTaskList2 = renderTaskList;
  DALI_CHECK_FAIL(renderTaskList2, "RenderTaskList operator=()  is failed " );

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliRenderTaskListOperatorAssignmentP
 * @since_tizen     2.4
 * @description     To Check RenderTaskList operator=() is working properly or not.
 */
int UtcDaliRenderTaskListOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TAST_LIST_OPERATORASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}



