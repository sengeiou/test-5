#include "utc-dali-model-3d-view-common.h"


//& set: Model3dView
extern int gArgc;
extern char ** gArgv;
extern int test_return_value;
int gRenderCountModel3dView;
Model3dView gView;
Vector3 gVecSize( 200.0f, 300.0f, 0.0f );

/**
 * @function            utc_Dali_Model3dView_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Model3dView_startup(void)
{
  gRenderCountModel3dView=0;
  test_return_value=TC_PASS;
}

/**
 * @function            utc_Dali_Model3dView_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Model3dView_cleanup(void)
{

}

void Model3dviewConstructorP();
void Model3dviewNewP();
void Model3dviewCopyConstructorP();
void Model3dviewOperatorAssignmentP();
void Model3dviewDownCastP();
void Model3dviewDownCastN();
void Model3dviewAddRemoveTypeRegistrySizeP();
void VTModel3dviewAddRemoveTypeRegistrySize001P();
void Model3dviewPropertiesP();

namespace
{
  enum TEST_CASES_LIST_MODEL_3D_VIEW
  {
    MODEL_3D_VIEW_CONSTRUCTOR_P,
    MODEL_3D_VIEW_NEW_P,
    MODEL_3D_VIEW_COPY_CONSTRUCTOR_P,
    MODEL_3D_VIEW_OPERATOR_ASSIGNMENT_P,
    MODEL_3D_VIEW_DOWNCAST_P,
    MODEL_3D_VIEW_DOWNCAST_N,
    MODEL_3D_VIEW_ADD_REMOVE_TYPE_REGISTRY_SIZE_P,
    MODEL_3D_VIEW_PROPERTIES_P
  };

  struct Model3dView_TestApp : public ConnectionTracker
  {
    Model3dView_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Model3dView_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Model3dView_TestApp::Tick );
      mTimer.Start();
    }

    bool Tick()
    {
      if(test_return_value==TC_FAIL)
      {
        mTimer.Stop();
        mApplication.Quit();
        return true;
      }
      VerdictTest();
      if(test_return_value==TC_FAIL)
      {
        mTimer.Stop();
        mApplication.Quit();
      }
      return true;
    }

    void ExcuteTest()
    {
      switch (mTestCase)
      {
        case MODEL_3D_VIEW_CONSTRUCTOR_P:
          {
            Model3dviewConstructorP();
            break;
          }

        case MODEL_3D_VIEW_NEW_P:
          {
            Model3dviewNewP();
            break;
          }

        case MODEL_3D_VIEW_COPY_CONSTRUCTOR_P:
          {
            Model3dviewCopyConstructorP();
            break;
          }

        case MODEL_3D_VIEW_OPERATOR_ASSIGNMENT_P:
          {
            Model3dviewOperatorAssignmentP();
            break;
          }

        case MODEL_3D_VIEW_PROPERTIES_P:
          {
            Model3dviewPropertiesP();
            break;
          }

        case MODEL_3D_VIEW_ADD_REMOVE_TYPE_REGISTRY_SIZE_P:
          {
            Model3dviewAddRemoveTypeRegistrySizeP();
            break;
          }

        case MODEL_3D_VIEW_DOWNCAST_P:
          {
            Model3dviewDownCastP();
            break;
          }

        case MODEL_3D_VIEW_DOWNCAST_N:
          {
            Model3dviewDownCastN();
            break;
          }

      }
    }
    void VerdictTest()
    {
      switch (mTestCase)
      {
        case MODEL_3D_VIEW_ADD_REMOVE_TYPE_REGISTRY_SIZE_P:
          {
            switch(gRenderCountModel3dView)
            {
              case 0:
                {
                  VTModel3dviewAddRemoveTypeRegistrySize001P();
                  mTimer.Stop();
                  mApplication.Quit();
                  break;
                }

            }
            break;
          }


        default:
          mTimer.Stop();
          mApplication.Quit();
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


void Model3dviewConstructorP()
{
  Model3dView view;
  DALI_CHECK_FAIL(view,  "Model3dview Default Contructor is failed.");

  DaliLog::PrintPass();
}

void Model3dviewNewP()
{
  string strActualPathObj=getResourceFullPath(TEST_OBJ_FILE_NAME);
  if(strActualPathObj=="")
  {
    LOG_E( "Unable to get resource path from app data directory for Object file." );
    test_return_value=1;
    return;
  }
  string strActualPathMtl=getResourceFullPath(TEST_MTL_FILE_NAME);
  if(strActualPathMtl=="")
  {
    LOG_E( "Unable to get resource path from app data directory for Metarial file." );
    test_return_value=1;
    return;
  }
  string strActualPathImg=getResourceFullPath(TEST_IMG_FILE_PATH);
  if(strActualPathImg=="")
  {
    LOG_E( "Unable to get resource path from app data directory for Image file." );
    test_return_value=1;
    return;
  }
  Model3dView view = Model3dView::New();
  DALI_CHECK_FAIL(!view,  "Toolkit::Model3dView::New() is failed.");

  Model3dView viewModel = Model3dView::New(strActualPathObj, strActualPathMtl, strActualPathImg);
  DALI_CHECK_FAIL(!viewModel,  "Toolkit::Model3dView::New(obj, mtl, image) is failed.");

  DaliLog::PrintPass();

}

void Model3dviewCopyConstructorP()
{
  string strActualPathObj=getResourceFullPath(TEST_OBJ_FILE_NAME);
  if(strActualPathObj=="")
  {
    LOG_E( "Unable to get resource path from app data directory for Object file." );
    test_return_value=1;
    return;
  }
  string strActualPathMtl=getResourceFullPath(TEST_MTL_FILE_NAME);
  if(strActualPathMtl=="")
  {
    LOG_E( "Unable to get resource path from app data directory for Metarial file." );
    test_return_value=1;
    return;
  }
  string strActualPathImg=getResourceFullPath(TEST_IMG_FILE_PATH);
  if(strActualPathImg=="")
  {
    LOG_E( "Unable to get resource path from app data directory for Image file." );
    test_return_value=1;
    return;
  }
  Model3dView view = Model3dView::New();
  DALI_CHECK_FAIL(!view,  "Toolkit::Model3dView::New() is failed.");

  Model3dView viewModel = Model3dView::New(strActualPathObj, strActualPathMtl, strActualPathImg);
  DALI_CHECK_FAIL(!viewModel,  "Toolkit::Model3dView::New(obj, mtl, image) is failed.");

  Stage::GetCurrent().Add(viewModel);

  Model3dView copyView( view );
  DALI_CHECK_FAIL(copyView != view,  "Toolkit::Model3dView Copy Constructor is failed .");
  DaliLog::PrintPass();

}

void Model3dviewDownCastP()
{
  string strActualPathObj=getResourceFullPath(TEST_OBJ_FILE_NAME);
  if(strActualPathObj=="")
  {
    LOG_E( "Unable to get resource path from app data directory for Object file." );
    test_return_value=1;
    return;
  }
  string strActualPathMtl=getResourceFullPath(TEST_MTL_FILE_NAME);
  if(strActualPathMtl=="")
  {
    LOG_E( "Unable to get resource path from app data directory for Metarial file." );
    test_return_value=1;
    return;
  }
  string strActualPathImg=getResourceFullPath(TEST_IMG_FILE_PATH);
  if(strActualPathImg=="")
  {
    LOG_E( "Unable to get resource path from app data directory for Image file." );
    test_return_value=1;
    return;
  }
  Model3dView view = Model3dView::New();
  DALI_CHECK_FAIL(!view,  "Toolkit::Model3dView::New() is failed.");

  Model3dView viewModel = Model3dView::New(strActualPathObj, strActualPathMtl, strActualPathImg);
  DALI_CHECK_FAIL(!viewModel,  "Toolkit::Model3dView::New(obj, mtl, image) is failed.");

  Stage::GetCurrent().Add(viewModel);

  BaseHandle handle(view);
  Model3dView modelView = Model3dView::DownCast( handle );
  DALI_CHECK_FAIL(modelView != view,  "Toolkit::Model3dView::DownCast() is failed .");
  DaliLog::PrintPass();
}

void Model3dviewDownCastN()
{
  BaseHandle unInitializedObject;

  Model3dView model3dview1 = Model3dView::DownCast( unInitializedObject );
  DALI_CHECK_FAIL(model3dview1, "Model3dview handle is not empty." );

  Model3dView model3dview2 = DownCast< Model3dView >( unInitializedObject );
  DALI_CHECK_FAIL(model3dview2, "Model3dview handle is not empty." );

  DaliLog::PrintPass();
}

void Model3dviewAddRemoveTypeRegistrySizeP()
{
  Model3dView view = Model3dView::New();
  DALI_CHECK_FAIL(!view,  "Toolkit::Model3dView::New() is failed.");
  gView=view;

  view.SetParentOrigin(ParentOrigin::CENTER);
  view.SetSize(Stage::GetCurrent().GetSize());

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor,  "Toolkit::Actor::New() is failed.");
  view.Add(actor);
  Stage::GetCurrent().Add(view);
  DALI_CHECK_FAIL(!actor.OnStage(),"Model3dView::Add() is failed.");

  TypeRegistry typeRegistry = TypeRegistry::Get();
  DALI_CHECK_FAIL(!typeRegistry,"TypeRegistry::Get() is failed.");

  TypeInfo typeInfo = typeRegistry.GetTypeInfo( "Model3dView" );
  DALI_CHECK_FAIL(!typeInfo,"TypeRegistry::GetTypeInfo() is failed.");

  BaseHandle handle = typeInfo.CreateInstance();
  DALI_CHECK_FAIL(!handle,"TypeRegistry::CreateInstance() is failed.");

  Model3dView viewDown = Model3dView::DownCast( handle );
  DALI_CHECK_FAIL(!viewDown,"Model3dView::DownCast is failed.");

  gView.SetSize( gVecSize );
}

void Model3dviewOperatorAssignmentP()
{
  string strActualPathObj=getResourceFullPath(TEST_OBJ_FILE_NAME);
  if(strActualPathObj=="")
  {
    LOG_E( "Unable to get resource path from app data directory for Object file." );
    test_return_value=1;
    return;
  }
  string strActualPathMtl=getResourceFullPath(TEST_MTL_FILE_NAME);
  if(strActualPathMtl=="")
  {
    LOG_E( "Unable to get resource path from app data directory for Metarial file." );
    test_return_value=1;
    return;
  }
  string strActualPathImg=getResourceFullPath(TEST_IMG_FILE_PATH);
  if(strActualPathImg=="")
  {
    LOG_E( "Unable to get resource path from app data directory for Image file." );
    test_return_value=1;
    return;
  }
  Model3dView view = Model3dView::New();
  DALI_CHECK_FAIL(!view,  "Toolkit::Model3dView::New() is failed.");

  Model3dView assignView;
  assignView=view;
  DALI_CHECK_FAIL(view != assignView,  "Toolkit::Model3dView Assignment Operator is failed .");

  DaliLog::PrintPass();
}

void VTModel3dviewAddRemoveTypeRegistrySize001P()
{
  Vector3 getSize = gView.GetCurrentSize();
  if(gVecSize.x != getSize.x || gVecSize.y != getSize.y)
  {
    LOG_E( "Model3dView size get set value not equal." );
    test_return_value=1;
    return;
  }

  DaliLog::PrintPass();
}

void Model3dviewPropertiesP(void)
{
  string file_name;
  Property::Value val;

  string strActualPathObj=getResourceFullPath(TEST_OBJ_FILE_NAME);
  if(strActualPathObj=="")
  {
    LOG_E( "Unable to get resource path from app data directory for Object file." );
    test_return_value=1;
    return;
  }
  string strActualPathMtl=getResourceFullPath(TEST_MTL_FILE_NAME);
  if(strActualPathMtl=="")
  {
    LOG_E( "Unable to get resource path from app data directory for Metarial file." );
    test_return_value=1;
    return;
  }
  string strActualPathImg=getResourceFullPath(TEST_IMG_FILE_PATH);
  if(strActualPathImg=="")
  {
    LOG_E( "Unable to get resource path from app data directory for Image file." );
    test_return_value=1;
    return;
  }

  Model3dView view = Model3dView::New();
  DALI_CHECK_FAIL(!view,  "Toolkit::Model3dView::New() is failed.");

  try
  {
    view.SetProperty( Model3dView::Property::GEOMETRY_URL, Dali::Property::Value( strActualPathObj ) );
    val = view.GetProperty( Model3dView::Property::GEOMETRY_URL );
    val.Get( file_name );
    if(file_name != strActualPathObj)
    {
      LOG_E( "Model3dView Geomatry file url does not match." );
      test_return_value=1;
      return;
    }

    view.SetProperty( Model3dView::Property::MATERIAL_URL, Dali::Property::Value( strActualPathMtl ) );
    val = view.GetProperty( Model3dView::Property::MATERIAL_URL );
    val.Get( file_name );
    if(file_name != strActualPathMtl)
    {
      LOG_E( "Model3dView Material file url does not match." );
      test_return_value=1;
      return;
    }

    view.SetProperty( Model3dView::Property::IMAGES_URL, Dali::Property::Value( strActualPathImg ) );
    val = view.GetProperty( Model3dView::Property::IMAGES_URL );
    val.Get( file_name );
    if(file_name != strActualPathImg)
    {
      LOG_E( "Model3dview Image file url does not match." );
      test_return_value=1;
      return;
    }
  }
  catch(Dali::DaliException& e)
  {
    LOG_E( "Model3dviewProperties TC is failed with dali exception." );
    test_return_value=1;
    return;
  }

  DaliLog::PrintPass();
}

/**
 * @testcase            UtcDaliModel3dViewConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object for Model3dView
 */

int UtcDaliModel3dViewConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Model3dView_TestApp testApp( application, MODEL_3D_VIEW_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliModel3dViewNewP
 * @since_tizen         2.4
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliModel3dViewNewP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Model3dView_TestApp testApp( application, MODEL_3D_VIEW_NEW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliModel3dViewCopyConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of a copy of object
 */

int UtcDaliModel3dViewCopyConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Model3dView_TestApp testApp( application, MODEL_3D_VIEW_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliModel3dViewOperatorAssignmentP
 * @since_tizen         2.4
 * @description         Checks correct assigntment of one object to other object
 */

int UtcDaliModel3dViewOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Model3dView_TestApp testApp( application, MODEL_3D_VIEW_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliModel3dViewDowncastP
 * @since_tizen         2.4
 * @description         Checks for correct downcasting of Base Handle
 */

int UtcDaliModel3dViewDowncastP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Model3dView_TestApp testApp( application, MODEL_3D_VIEW_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliModel3dViewDowncastN
 * @since_tizen         2.4
 * @description         Negative test for checking downcasting of Base Handle
 */

int UtcDaliModel3dViewDowncastN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Model3dView_TestApp testApp( application, MODEL_3D_VIEW_DOWNCAST_N );
  application.MainLoop();

  return test_return_value;
}
/**
 * @testcase            UtcDaliModel3dViewAddRemoveTypeRegistrySizeP
 * @since_tizen         2.4
 * @description         Check for Add and Remove Type Registry size
 */


int UtcDaliModel3dViewAddRemoveTypeRegistrySizeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Model3dView_TestApp testApp( application, MODEL_3D_VIEW_ADD_REMOVE_TYPE_REGISTRY_SIZE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliModel3dViewPropertiesP
 * @since_tizen         2.4
 * @description         Checks Model3dView Properties
 */

int UtcDaliModel3dViewPropertiesP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Model3dView_TestApp testApp( application, MODEL_3D_VIEW_PROPERTIES_P );
  application.MainLoop();

  return test_return_value;
}

