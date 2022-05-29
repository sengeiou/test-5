#include "utc-dali-render-task-common.h"
#include <sstream>

int gRenderCountRenderTask;
RenderTask gRenderTask;
bool gBoolFinished;
Vector2 gVector2;
Viewport gViewportSet;
Vector2 gVec2NewAnimatedSize, gViewportSizeSet;
Actor gRenderTaskActor;

class TestNativeImageInterface : public NativeImageInterface
{
  public:
    int mWidth ;
    int mHeight;
    TestNativeImageInterface(int nWidth, int nHeight)
      : mWidth(nWidth),
      mHeight(nHeight)
  {}

    virtual bool GlExtensionCreate()
    {
      return true;
    };

    /**
     * Destroy the GL resource for the NativeImageInterface.
     * e.g. For the EglImageKHR extension, this corresponds to calling eglDestroyImageKHR()
     * @pre There is a GL context for the current thread.
     */
    virtual void GlExtensionDestroy() {};

    /**
     * Use the NativeImageInterface as a texture for rendering
     * @pre There is a GL context for the current thread.
     * @return A GL error code
     */
    virtual unsigned int TargetTexture()
    {
      return 0;
    };

    /**
     * Called in each NativeTexture::Bind() call to allow implementation specific operations.
     * The correct texture sampler has already been bound before the function gets called.
     * @pre glAbstraction is being used by context in current thread
     */
    virtual void PrepareTexture() {}

    /**
     * Returns the width of the NativeImageInterface
     * @return width
     */
    virtual unsigned int GetWidth() const
    {
      return mWidth;
    }

    /**
     * Returns the height of the NativeImageInterface
     * @return height
     */
    virtual unsigned int GetHeight() const
    {
      return mHeight;
    }

    /**
     * Returns whether the Blending is required or not
     * @return bool
     */
    virtual bool RequiresBlending() const
    {
      return true;
    }

    /**
     * @brief Query whether an image is y-inverted.
     *
     * @return true if an image is y-inverted, otherwise false.
     */
    virtual bool IsYInverted() const
    {
      return true;
    }

    /**
     * Returns the internal pixel NativeImageInterface::PixelFormat of the NativeImageInterface
     * @return pixel format
     */
    virtual Pixel::Format GetPixelFormat() const
    {
      return Pixel::RGBA8888;
    }
  protected:
    ~TestNativeImageInterface() {}
};

void RenderTaskFinishedP(RenderTask& renderTask)
{
  DALI_CHECK_FAIL( !renderTask , "RenderTask not received");
  gBoolFinished = true;
}

void RenderTaskSetGetViewportSizeP()
{
  Vector2 vec2NewStageSize( 200.0f, 100.0f );
  gVec2NewAnimatedSize=Vector2( 100.0f, 50.0f );

  if ( !RenderTaskConstruction( gRenderTask ) )
  {
    test_return_value=1;
    return;
  }

  Vector2 vec2StageSize = Stage::GetCurrent().GetSize();
  Viewport viewport = gRenderTask.GetViewport();
  Viewport viewportExpected( START_POINT, START_POINT, vec2StageSize.width, vec2StageSize.height );

  DALI_CHECK_FAIL( viewport != viewportExpected ,  "Default viewport mismatched with expected viewport");

  gRenderTask.SetViewportSize( vec2NewStageSize );
  gViewportSizeSet = vec2NewStageSize;
}

void VTRenderTaskSetGetViewportSize001()
{
  Vector2 vec2GetStageSize = gRenderTask.GetCurrentViewportSize();
  if( !RenderTaskSizeCompare( gViewportSizeSet, vec2GetStageSize) )
  {
    test_return_value=1;
    return;
  }
  Vector2 vec2StageSizebyProperty( 150.0f, 75.0f );
  gRenderTask.SetProperty( RenderTask::Property::VIEWPORT_SIZE, vec2StageSizebyProperty );
  gViewportSizeSet = vec2StageSizebyProperty;
}

void VTRenderTaskSetGetViewportSize002()
{
  Vector2 vec2GetStageSize = gRenderTask.GetCurrentViewportSize();
  if( !RenderTaskSizeCompare( gViewportSizeSet, vec2GetStageSize) )
  {
    test_return_value=1;
    return;
  }
  const float F_TIME = 0.3f;
  Animation animation = Animation::New( F_TIME );
  DALI_CHECK_FAIL( !animation ,  "Animation is not created");

  animation.AnimateTo( Property( gRenderTask, RenderTask::Property::VIEWPORT_SIZE ), gVec2NewAnimatedSize, AlphaFunction::LINEAR );
  animation.Play();
}

void VTRenderTaskSetGetViewportSize003()
{
  Vector2 vec2GetStageSize = gRenderTask.GetCurrentViewportSize();
  if( !RenderTaskSizeCompare( gVec2NewAnimatedSize, vec2GetStageSize) )
  {
    test_return_value=1;
    return;
  }

  DaliLog::PrintPass();
}

void RenderTaskSetGetCullModeP()
{
  Actor iActor;
  bool bSetCullMode = true, bSetDrawMode = true;
  const float F_WIDTH = 80.0f, F_HEIGHT = 80.0f;
  const unsigned int TEXTURE_ID_OFFSET = 23;
  RenderTask renderTask;
  if ( !RenderTaskConstruction( renderTask ) )
  {
    test_return_value=1;
    return;
  }

  Image image = ImageInitialization( TEXTURE_ID_OFFSET, F_WIDTH, F_HEIGHT );
  DALI_CHECK_FAIL( !image ,  "image is not created.");

  iActor = ImageView::New(image);
  DALI_CHECK_FAIL(!iActor,  " Could not create iActor.");

  // Setting CullMode to false.
  renderTask.SetCullMode( !bSetCullMode );
  DALI_CHECK_FAIL( renderTask.GetCullMode() ,  "Cull mode is not set to false mode properly.");

  // Calculating actor's position points outside the stage
  Vector2 vec2StageSize = Stage::GetCurrent().GetSize();
  Vector3 vec3ImageSize = iActor.GetCurrentSize();

  float x1 = -vec2StageSize.x - vec3ImageSize.x;
  float x2 =  vec2StageSize.x + vec3ImageSize.x;
  float y1 = -vec2StageSize.y - vec3ImageSize.y;
  float y2 =  vec2StageSize.y + vec3ImageSize.y;

  // Positioning actors outside stage, with no culling, they should still be drawn.
  if ( !RenderTaskActorRepositionOutside( iActor, x1, y1, bSetDrawMode ) )
  {
    test_return_value=1;
    return;
  }
  if ( !RenderTaskActorRepositionOutside( iActor, x2, y1, bSetDrawMode ) )
  {
    test_return_value=1;
    return;
  }
  if ( !RenderTaskActorRepositionOutside( iActor, x1, y2, bSetDrawMode ) )
  {
    test_return_value=1;
    return;
  }
  if ( !RenderTaskActorRepositionOutside( iActor, x2, y2, bSetDrawMode ) )
  {
    test_return_value=1;
    return;
  }

  // Setting CullMode to true
  renderTask.SetCullMode( bSetCullMode );
  DALI_CHECK_FAIL( !renderTask.GetCullMode() ,  "Cull mode is set to true properly.");

  // Positioning actors outside stage, with culling, they should not be drawn.
  if ( !RenderTaskActorRepositionOutside( iActor, x1, y1, !bSetDrawMode ) )
  {
    test_return_value=1;
    return;
  }
  if ( !RenderTaskActorRepositionOutside( iActor, x2, y1, !bSetDrawMode ) )
  {
    test_return_value=1;
    return;
  }
  if ( !RenderTaskActorRepositionOutside( iActor, x1, y2, !bSetDrawMode ) )
  {
    test_return_value=1;
    return;
  }
  if ( !RenderTaskActorRepositionOutside( iActor, x2, y2, !bSetDrawMode ) )
  {
    test_return_value=1;
    return;
  }

  Stage::GetCurrent().Remove( iActor );

  DaliLog::PrintPass();
}

void RenderTaskSetCullModeN()
{
  RenderTask task;
  try
  {
    task.SetCullMode( false );
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "RenderTask handle is empty" );
  }
  DaliLog::PrintPass();
}

void RenderTaskGetCullModeN()
{

  RenderTask task;
  try
  {
    bool x = task.GetCullMode();
    x=x;
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "RenderTask handle is empty" );
  }
  DaliLog::PrintPass();
}

void RenderTaskConstructorAssignmentOperatorP()
{
  Stage stage;
  RenderTaskList renderTaskList;
  RenderTask renderTask;
  DALI_CHECK_FAIL(!RenderTaskinit(stage, renderTaskList, renderTask),  "RenderTask Initialization Failed " );
  RenderTask renderTask2(renderTask);
  DALI_CHECK_FAIL(!renderTask2,  "rendertask copy constractor is failed");
  RenderTask renderTask3 = renderTask;
  DALI_CHECK_FAIL(renderTask3 != renderTask,  "rendertask assigment operator is failed");
  DaliLog::PrintPass();
}

void RenderTaskDownCastP()
{
  const int TASK_NUMBER = 0;
  Stage stage =  Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "stage is empty.");

  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  DALI_CHECK_FAIL(renderTaskList.GetTaskCount() == INVALID_TASK_COUNT,  "renderTaskList is empty.");

  BaseHandle baseHandle = renderTaskList.GetTask(TASK_NUMBER);
  DALI_CHECK_FAIL(!baseHandle,  "baseHandle is not created");

  RenderTask renderTask = RenderTask::DownCast(baseHandle);
  DALI_CHECK_FAIL(!renderTask,  "DownCast  is failed to create render task object");

  DaliLog::PrintPass();
}

void RenderTaskDownCastN()
{
  Actor actor = Actor::New();
  RenderTask renderTask = RenderTask::DownCast( actor );
  DALI_CHECK_FAIL(renderTask,  "DownCast  is failed to create render task object");

  DaliLog::PrintPass();
}

void RenderTaskFinishedSignalP()
{
  Actor rootActor;
  const int WIDTH = 10 , HEIGHT = 10 ;
  const float F_HEIGHT = 10.0f , F_WIDTH =  10.0f ;
  const float F_X = 0.0f , F_Y = 0.0f  , F_Z = 0.0f  , F_W = 0.0f ;

  Stage stage =  Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "stage is empty.");

  CameraActor offscreenCameraActor = CameraActor::New();
  DALI_CHECK_FAIL(!offscreenCameraActor,  "CameraActor::New is failed to create camera actor.");

  stage.Add(offscreenCameraActor);
  RenderTaskList renderTaskList = stage.GetRenderTaskList();

  DALI_CHECK_FAIL(renderTaskList.GetTaskCount() == INVALID_TASK_COUNT,  "RenderTaskList is empty.");
  gBoolFinished = false;
  BufferImage image = BufferImage::New(WIDTH, HEIGHT);
  DALI_CHECK_FAIL(!image, "BufferImage is not created");

  rootActor = ImageView::New(image);
  DALI_CHECK_FAIL(!rootActor,  " Could not create rootActor.");

  rootActor.SetSize(F_WIDTH , F_HEIGHT);
  stage.Add(rootActor);

  //NativeImageInterfacePtr testNativeImageInterfacePtr = new TestNativeImageInterface(F_X, F_Y);
  FrameBufferImage frameBufferImage = FrameBufferImage::New();

  // Flush all outstanding messages

  RenderTask newTask = renderTaskList.CreateTask();
  newTask.SetCameraActor(offscreenCameraActor);
  newTask.SetSourceActor(rootActor);
  newTask.SetInputEnabled(false);
  newTask.SetClearColor(Vector4(F_X, F_Y, F_Z, F_W));
  newTask.SetClearEnabled(true);
  newTask.SetExclusive(true);
  newTask.SetRefreshRate(RenderTask::REFRESH_ONCE);
  newTask.SetTargetFrameBuffer(frameBufferImage);

  newTask.FinishedSignal().Connect(&RenderTaskFinishedP);
  // Flush the queue and render.
  DaliLog::PrintPass();
}

void RenderTaskSetGetSourceActorP()
{
  Actor iActor;
  const int WIDTH = 10 , HEIGHT = 120 ;
  Stage stage;
  RenderTaskList renderTaskList;
  RenderTask renderTask;
  DALI_CHECK_FAIL(!RenderTaskinit(stage, renderTaskList, renderTask),  "RenderTask Initialization Failed " );

  Actor sourceActorDefault = renderTask.GetSourceActor();
  DALI_CHECK_FAIL(!sourceActorDefault,  " GetSourceActor is returned null as default");

  BufferImage bufferimage = BufferImage::New(WIDTH, HEIGHT);
  DALI_CHECK_FAIL(!bufferimage,  "BufferImage::New is failed to create BufferImage object");

  iActor = ImageView::New(bufferimage);
  DALI_CHECK_FAIL(!iActor,  " Could not create iActor.");

  iActor.SetSize(WIDTH, HEIGHT);
  stage.Add(iActor);
  renderTask.SetSourceActor(iActor);

  Actor sourceActor1 = renderTask.GetSourceActor();
  DALI_CHECK_FAIL(iActor != sourceActor1,  "SetSourceActor and GetSourceActor is not matched");
  stage.Remove(iActor);
  renderTask.SetSourceActor(sourceActorDefault);

  DaliLog::PrintPass();
}

void RenderTaskGetSourceActorN()
{
  RenderTask task;
  try
  {
    Actor actor = task.GetSourceActor();
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "RenderTask handle is empty" );
  }
  DaliLog::PrintPass();
}

void RenderTaskSetGetScreenToFrameBufferMappingActorP()
{
  Stage stage;
  RenderTaskList renderTaskList;
  RenderTask renderTask;
  DALI_CHECK_FAIL(!RenderTaskinit(stage, renderTaskList, renderTask),  "RenderTask Initialization Failed " );

  Actor mappingSetActor = Actor::New();
  DALI_CHECK_FAIL(!mappingSetActor,  " Actor::New is failed to create actor object.");
  renderTask.SetScreenToFrameBufferMappingActor(mappingSetActor);

  Actor mappingGetActor = renderTask.GetScreenToFrameBufferMappingActor();
  DALI_CHECK_FAIL(mappingGetActor != mappingSetActor,  " SetScreenToFrameBufferMappingActor and GetScreenToFrameBufferMappingActor is not matched");

  DaliLog::PrintPass();
}

void RenderTaskSetScreenToFrameBufferMappingActorN()
{
  RenderTask task;
  try
  {
    Actor mappingActor;
    task.SetScreenToFrameBufferMappingActor(mappingActor);
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "RenderTask handle is empty" );
  }
  DaliLog::PrintPass();
}

void RenderTaskSetGetClearColorP()
{
  const float F_X = 0.0f, F_Y = 0.0f, F_Z = 0.0f, F_W = 0.0f  ;
  Vector4 vec4GetColor, vec4GetColor2;
  Vector4 vec4SetColor(F_X, F_Y, F_Z, F_W);
  Stage stage;
  RenderTaskList renderTaskList;
  RenderTask renderTask;
  DALI_CHECK_FAIL(!RenderTaskinit(stage, renderTaskList, renderTask),  "RenderTask Initialization Failed " );

  renderTask.SetClearEnabled(true);
  vec4GetColor =    renderTask.GetClearColor();
  renderTask.SetClearColor(vec4SetColor);
  vec4GetColor2 =    renderTask.GetClearColor();
  DALI_CHECK_FAIL(vec4GetColor !=  vec4GetColor2,  "SetClearColor and GetClearColor is not matched.");

  DaliLog::PrintPass();
}

void RenderTaskSetClearColorN()
{
  RenderTask task;
  try
  {
    task.SetClearColor( Vector4::ZERO );
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "RenderTask handle is empty" );
  }

  DaliLog::PrintPass();
}

void RenderTaskGetClearColorN()
{
  RenderTask task;
  try
  {
    Vector4 color = task.GetClearColor();
    color = color;
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "RenderTask handle is empty" );
  }

  DaliLog::PrintPass();
}

void RenderTaskSetGetClearEnabledP()
{
  const int WIDTH = 10 , HEIGHT = 10 ;
  const float F_HEIGHT = 10.0f , F_WIDTH =  10.0f ;
  const float F_X = 0.0f , F_Y = 0.0f  , F_Z = 0.0f  , F_W = 0.0f ;

  bool bGetClearEnable;

  Stage stage =  Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "stage is empty.");

  CameraActor offscreenCameraActor = CameraActor::New();
  DALI_CHECK_FAIL(!offscreenCameraActor,  "CameraActor::New is failed to create camera actor.");

  stage.Add(offscreenCameraActor);
  RenderTaskList renderTaskList = stage.GetRenderTaskList();

  DALI_CHECK_FAIL(renderTaskList.GetTaskCount() == INVALID_TASK_COUNT,  "RenderTaskList is empty.");
  BufferImage image = BufferImage::New(WIDTH, HEIGHT);
  DALI_CHECK_FAIL(!image, "BufferImage is not created");
  ImageView rootView = ImageView::New(image);
  DALI_CHECK_FAIL(!rootView,  "rootView is not created.");
  rootView.SetSize(F_WIDTH , F_HEIGHT);
  stage.Add(rootView);

  FrameBufferImage frameBufferImage = FrameBufferImage::New();

  // Flush all outstanding messages
  RenderTask newTask = renderTaskList.CreateTask();
  newTask.SetCameraActor(offscreenCameraActor);
  newTask.SetSourceActor(rootView);
  newTask.SetInputEnabled(false);
  newTask.SetClearColor(Vector4(F_X, F_Y, F_Z, F_W));
  newTask.SetExclusive(true);
  newTask.SetRefreshRate(RenderTask::REFRESH_ONCE);
  newTask.SetTargetFrameBuffer(frameBufferImage);

  bool  bGetDefaultClearEnable  = newTask.GetClearEnabled();
  DALI_CHECK_FAIL(bGetDefaultClearEnable,  "Default ClearEnable should be false");

  newTask.SetClearEnabled(true);

  bGetClearEnable = newTask.GetClearEnabled();

  DALI_CHECK_FAIL(!bGetClearEnable,  "SetClearEnabled and GetClearEnabled is not matched");
  newTask.SetClearEnabled(false);
  newTask.SetClearEnabled(bGetDefaultClearEnable);

  DaliLog::PrintPass();
}

void RenderTaskSetClearEnabledN()
{
  RenderTask task;
  try
  {
    task.SetClearEnabled(true);
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "RenderTask handle is empty" );
  }

  DaliLog::PrintPass();
}

void RenderTaskGetClearEnabledN()
{
  RenderTask task;
  try
  {
    bool x = task.GetClearEnabled();
    x=x;
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "RenderTask handle is empty" );
  }

  DaliLog::PrintPass();
}

void RenderTaskSetGetViewportPositionP()
{
  const float F_X = 25.0f, F_Y = 50.0f;
  DALI_CHECK_FAIL(!RenderTaskConstruction( gRenderTask ),  "RenderTask Initialization Failed " );

  Vector2 vec2SetPosition(F_X, F_Y);
  gVector2=vec2SetPosition;
  gRenderTask.SetViewportPosition(vec2SetPosition);
}

void VTRenderTaskSetGetViewportPosition001()
{
  Vector2 vec2GetPosition = gRenderTask.GetCurrentViewportPosition();

  std::stringstream out;
  out << "SetViewportPosition and GetCurrentViewportPosition is not matched: " << vec2GetPosition.x << ", " << vec2GetPosition.y;

  DALI_CHECK_FAIL(vec2GetPosition != gVector2, out.str().c_str());

  DaliLog::PrintPass();
}

void RenderTaskSetAndGetViewportP()
{
  const float F_X = 0.0f, F_Y = 0.0f, F_WIDTH = 100.0f, F_HEIGHT = 50.0f;
  DALI_CHECK_FAIL(!RenderTaskConstruction( gRenderTask ),  "RenderTask Initialization Failed " );

  Stage stage = Stage::GetCurrent();
  Viewport viewportDefault = gRenderTask.GetViewport();
  Viewport viewportExpected(0, 0, stage.GetSize().width, stage.GetSize().height);
  DALI_CHECK_FAIL(viewportExpected != viewportDefault,  " default viewport is mismatched with expected viewport");

  gViewportSet=Viewport(F_X, F_Y, F_WIDTH, F_HEIGHT);
  gRenderTask.SetViewport(gViewportSet);
}

void VTRenderTaskSetGetViewport001()
{
  Viewport viewportGet;
  viewportGet = gRenderTask.GetViewport();

  std::stringstream out;
  out << "SetViewport and GetViewport is not matched: " << viewportGet.x << ", " << viewportGet.y << ", " << viewportGet.width << ", " << viewportGet.height;

  DALI_CHECK_FAIL(gViewportSet != viewportGet, out.str().c_str());

  DaliLog::PrintPass();
}

void RenderTaskGetViewportN()
{
  RenderTask task;
  try
  {
    Viewport viewport = task.GetViewport();
    viewport = viewport;
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "RenderTask handle is empty" );
  }
  DaliLog::PrintPass();
}

void RenderTaskSetViewportN()
{
  RenderTask task;
  try
  {
    Vector2 stageSize = Stage::GetCurrent().GetSize();
    Viewport newViewport( 0, 0, stageSize.width * 0.5f, stageSize.height * 0.5f );
    task.SetViewport( newViewport );
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "RenderTask handle is empty" );
  }
  DaliLog::PrintPass();
}

void RenderTaskSetGetTargetFrameBufferP()
{
  Actor iActor;
  const float F_X = 1.0f , F_Y = 1.0f  , F_Z = 1.0f  , F_W = 0.0f ;
  Stage stage;
  RenderTaskList renderTaskList;
  RenderTask renderTask;
  DALI_CHECK_FAIL(!RenderTaskinit(stage, renderTaskList, renderTask),  "RenderTask Initialization Failed " );

  FrameBufferImage frameBufferImageDefault = renderTask.GetTargetFrameBuffer();
  DALI_CHECK_FAIL(frameBufferImageDefault,  " frameBufferImageDefault is non empty.");

  FrameBufferImage frameBufferImageSet = FrameBufferImage::New(stage.GetSize().width, stage.GetSize().height, Pixel::RGBA8888);
  DALI_CHECK_FAIL(!frameBufferImageSet,  " FrameBufferImage::New is failed to create frameBufferImage object" );

  iActor = ImageView::New(frameBufferImageSet);
  DALI_CHECK_FAIL(!iActor,  " ImageView::New is failed to create frameBufferImage object");

  iActor.SetParentOrigin(ParentOrigin::CENTER);

  Vector2 startValue( 1.0f, 1.0f );
  Property::Index index = iActor.RegisterProperty( "test-property", startValue );
  Constraint constraint = Constraint::New<Vector3>(iActor, index, EqualToConstraint());
  constraint.Apply();

  iActor.SetColor(Color::WHITE);

  RenderTask renderTask2 = renderTaskList.CreateTask();
  DALI_CHECK_FAIL(!renderTask2,  " CreateTask() is failed to create RenderTask Object.");

  renderTask2.SetRefreshRate(RenderTask::REFRESH_ALWAYS);
  renderTask2.SetSourceActor(iActor);
  renderTask2.SetExclusive(true);
  renderTask2.SetInputEnabled(false);
  renderTask2.SetClearColor(Vector4(F_X, F_Y,F_Z,F_W));
  renderTask2.SetClearEnabled(true);

  renderTask2.SetTargetFrameBuffer(frameBufferImageSet);

  FrameBufferImage frameBufferImageGet = renderTask2.GetTargetFrameBuffer();
  DALI_CHECK_FAIL(frameBufferImageGet != frameBufferImageSet,  " SetTargetFrameBuffer and GetTargetFrameBuffer is not matched.");

  renderTaskList.RemoveTask(renderTask2);

  DaliLog::PrintPass();
}

void RenderTaskSetGetRefreshRateP()
{
  unsigned int U_SET_REFRESH_RATE = 2, U_GET_REFRESH_RATE = 1;
  Stage stage;
  RenderTaskList renderTaskList;
  RenderTask renderTask;
  DALI_CHECK_FAIL(!RenderTaskinit(stage, renderTaskList, renderTask),  "RenderTask Initialization Failed " );

  unsigned int nGetDefaultRefreshRate = renderTask.GetRefreshRate();
  DALI_CHECK_FAIL(nGetDefaultRefreshRate != RenderTask::REFRESH_ALWAYS,  "Default refresh rate  is not RenderTask::REFRESH_ALWAYS.");
  renderTask.SetRefreshRate(U_SET_REFRESH_RATE);

  U_GET_REFRESH_RATE = renderTask.GetRefreshRate();

  DALI_CHECK_FAIL(U_SET_REFRESH_RATE != U_GET_REFRESH_RATE,  "SetRefreshRate and GetRefreshRate is not matched.");
  renderTask.SetRefreshRate(RenderTask::REFRESH_ALWAYS);

  DaliLog::PrintPass();
}

void RenderTaskSetGetInputEnableP()
{
  bool bGetInputEnable = true;
  Stage stage;
  RenderTaskList renderTaskList;
  RenderTask renderTask;
  DALI_CHECK_FAIL(!RenderTaskinit(stage, renderTaskList, renderTask),  "RenderTask Initialization Failed " );

  bool bDefaultIsInputEnable = renderTask.GetInputEnabled();
  DALI_CHECK_FAIL(!bDefaultIsInputEnable,  "GetInputEnabled is returning false.");

  renderTask.SetInputEnabled(false);

  bGetInputEnable = renderTask.GetInputEnabled();

  DALI_CHECK_FAIL(bGetInputEnable,  "SetInputEnabled and GetInputEnabled is not matched");
  renderTask.SetInputEnabled(true);
  renderTask.SetInputEnabled(bDefaultIsInputEnable);

  DaliLog::PrintPass();
}

void RenderTaskSetGetCameraActorP()
{
  Stage stage;
  RenderTaskList renderTaskList;
  RenderTask renderTask;
  DALI_CHECK_FAIL(!RenderTaskinit(stage, renderTaskList, renderTask),  "RenderTask Initialization Failed " );

  CameraActor cameraActorDefault = renderTask.GetCameraActor();
  DALI_CHECK_FAIL(!cameraActorDefault,  "GetCameraActor is  failed to get default camera actor.");
  CameraActor cameraActor =  CameraActor::New();
  DALI_CHECK_FAIL(!cameraActor,  "CameraActor::New is  failed to create camera instance.");
  renderTask.SetCameraActor(cameraActor);
  //~ RenderTaskWait(WAIT_TIME);
  CameraActor cameraActor1 = renderTask.GetCameraActor();

  DALI_CHECK_FAIL(cameraActor !=  cameraActor1,  "SetCameraActor and GetCameraActor is not matched.");

  renderTask.SetCameraActor(cameraActorDefault);

  DaliLog::PrintPass();
}

void RenderTaskGetCameraActorN()
{
  RenderTask task;
  try
  {
    Actor actor = task.GetCameraActor();
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "RenderTask handle is empty" );
  }
  DaliLog::PrintPass();
}

void RenderTaskSetIsExclusiveP()
{
  Stage stage;
  RenderTaskList renderTaskList;
  RenderTask renderTask;
  Actor gActor1, gActor2, gActor3;
  DALI_CHECK_FAIL(!RenderTaskinit(stage, renderTaskList, renderTask),  "RenderTask Initialization Failed " );

  bool bIsExclusiveDefault = renderTask.IsExclusive();
  DALI_CHECK_FAIL(bIsExclusiveDefault,  "IsExclusive is returned  true as default.");

  BufferImage img = BufferImage::New( 1,1 );

  gActor1 = ImageView::New(img);
  DALI_CHECK_FAIL(!gActor1,  " Could not create iActor1.");

  gActor2 = ImageView::New(img);
  DALI_CHECK_FAIL(!gActor2,  " Could not create iActor2.");

  gActor3 = ImageView::New(img);
  DALI_CHECK_FAIL(!gActor3,  " Could not create iActor3.");

  gRenderTask = renderTaskList.CreateTask();
  DALI_CHECK_FAIL(!gRenderTask,  " render task is not created.");
  gRenderTask.SetSourceActor(gActor2);

  stage.Add(gActor1);
  stage.Add(gActor2);
  stage.Add(gActor3);

  gRenderTask.SetExclusive(true);
  DaliLog::PrintPass();
}

void RenderTaskSetExclusiveN()
{
  RenderTask task;
  try
  {
    task.SetExclusive(true);
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "RenderTask handle is empty" );
  }
  DaliLog::PrintPass();
}

void RenderTaskIsExclusiveN()
{
  RenderTask task;
  try
  {
    bool x = task.IsExclusive();
    x=x;
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "RenderTask handle is empty" );
  }
  DaliLog::PrintPass();
}

void RenderTaskSetGetSetScreenToFrameBufferFunctionWithFullScreenP()
{
  Stage stage =  Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  " stage is empty");

  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  DALI_CHECK_FAIL(renderTaskList.GetTaskCount() == INVALID_TASK_COUNT,  " renderTaskList is empty");

  if (!RenderTaskSetGetScreenToFrameBufferFunction(renderTaskList, RenderTask::FULLSCREEN_FRAMEBUFFER_FUNCTION))
  {
    test_return_value=1;
    return;
  }

  DaliLog::PrintPass();
}

void RenderTaskSetGetSetScreenToFrameBufferFunctionWithDefaultScreenP()
{
  Stage stage =  Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  " stage is empty");

  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  DALI_CHECK_FAIL(renderTaskList.GetTaskCount() == INVALID_TASK_COUNT,  " renderTaskList is empty");

  if(!RenderTaskSetGetScreenToFrameBufferFunction(renderTaskList, RenderTask::DEFAULT_SCREEN_TO_FRAMEBUFFER_FUNCTION))
  {
    test_return_value=1;
    return;
  }

  DaliLog::PrintPass();
}

void RenderTaskSetGetSetScreenToFrameBufferFunctionN()
{
  RenderTask task;
  try
  {
    task.SetScreenToFrameBufferFunction( RenderTask::DEFAULT_SCREEN_TO_FRAMEBUFFER_FUNCTION );
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "RenderTask handle is empty" );
  }
  DaliLog::PrintPass();
}

void RenderTaskGetScreenToFrameBufferFunctionN()
{
  RenderTask task;
  try
  {
    RenderTask::ScreenToFrameBufferFunction func = task.GetScreenToFrameBufferFunction();
    func=func;
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "RenderTask handle is empty" );
  }
  DaliLog::PrintPass();
}

void RenderTaskWorldToViewportP()
{
  gRenderTaskActor = Actor::New();
  gRenderTaskActor.SetSize(100.0f, 100.0f);
  gRenderTaskActor.SetPosition( Vector3(0.0, 0.0, 0.0) );
  gRenderTaskActor.SetParentOrigin( Vector3(0.5, 0.5, 0.5) );
  gRenderTaskActor.SetAnchorPoint( Vector3(0.5, 0.5, 0.5) );

  Stage::GetCurrent().Add(gRenderTaskActor);
}

void VTRenderTaskWorldToViewport001()
{
  RenderTaskList taskList = Stage::GetCurrent().GetRenderTaskList();
  RenderTask task = taskList.GetTask( 0u );

  Vector2 viewportSize = task.GetCurrentViewportSize();

  float screenX = 0.0;
  float screenY = 0.0;

  bool ok = task.WorldToViewport(gRenderTaskActor.GetCurrentWorldPosition(), screenX, screenY);

  DALI_CHECK_FAIL( !ok, "WorldToViewport is failed");
  DALI_CHECK_FAIL( !Equals( screenX, viewportSize.x / 2.0f, Math::MACHINE_EPSILON_10000 ), "X Value mismatch" );
  DALI_CHECK_FAIL( !Equals( screenY, viewportSize.y / 2.0f, Math::MACHINE_EPSILON_10000 ), "Y Value mismatch" );

  DaliLog::PrintPass();
}

void RenderTaskViewportToLocalP()
{
  gRenderTaskActor = Actor::New();
  gRenderTaskActor.SetAnchorPoint(AnchorPoint::TOP_LEFT);
  gRenderTaskActor.SetSize(100.0f, 100.0f);
  gRenderTaskActor.SetPosition(10.0f, 10.0f);

  Stage::GetCurrent().Add(gRenderTaskActor);
}

void VTRenderTaskViewportToLocal001()
{
  RenderTaskList taskList = Stage::GetCurrent().GetRenderTaskList();
  RenderTask task = taskList.GetTask( 0u );

  float localX;
  float localY;

  float rtLocalX;
  float rtLocalY;

  float screenX = 50.0f;
  float screenY = 50.0f;

  DALI_CHECK_FAIL( !gRenderTaskActor.ScreenToLocal(localX, localY, screenX, screenY), "screen To Local failed");

  DALI_CHECK_FAIL( !task.ViewportToLocal(gRenderTaskActor, screenX, screenY, rtLocalX, rtLocalY ), "Viewport To local is failed");

  DaliLog::PrintPass();
}
