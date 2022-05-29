#include "utc-dali-render-task-common.h"
#include <sstream>

const int RENDERTASK_RENDER_FRAME_INTERVAL = 16;

const char* COMPOSITE_FRAGMENT_SOURCE =    "void main()"
"{\n"
"  gl_FragColor = uColor;\n"
"  gl_FragColor.a *= texture2D( sTexture, vTexCoord).a;"
"}\n";

/**
 * @function       RenderTaskConstruction
 * @description    Construct render task from current stage
 * @param[in]      NA
 * @param[out]     renderTask [ RenderTask ]
 * @return         false : if render task list is not found from current stage or render task is not created.
 *                 true  : if render task is created from the current stage.
 */

bool RenderTaskConstruction( RenderTask& renderTask  )
{
  RenderTaskList renderTaskList = Stage::GetCurrent().GetRenderTaskList();
  DALI_CHECK_FALSE( renderTaskList.GetTaskCount() == INVALID_TASK_COUNT , "RenderTaskList is empty.");

  renderTask = renderTaskList.CreateTask();

  // Create camera actor with the simplest screen size;
  CameraActor cameraActor = Dali::CameraActor::New( Dali::Size( 360, 360 ) );
  cameraActor.SetParentOrigin( ParentOrigin::CENTER );
  cameraActor.SetAnchorPoint( AnchorPoint::CENTER );

  Stage::GetCurrent().Add( cameraActor );
  renderTask.SetCameraActor( cameraActor );

  auto frameBuffer = Dali::FrameBuffer::New( 360, 360, FrameBuffer::Attachment::COLOR );
  renderTask.SetFrameBuffer( frameBuffer );
  
  DALI_CHECK_FALSE( !renderTask , "RenderTask is not created.");

  return true;
}

/**
 * @function       RenderTaskCompare
 * @description    Compare the retrieved viewport size with the set size
 * @param[in]      vec2Set [ Set viewport size  ]
 * @param[in]      vec2Get [ Retrieved viewport size ]
 * @param[out]     NA
 * @return         false : if retrieved viewport size is not matched with the set size
 *                 true  : if retrieved viewport size is matched with the set size
 */

bool RenderTaskSizeCompare( Dali::Vector2 vec2Set, Dali::Vector2 vec2Get )
{
  float fEpsilon = Math::MACHINE_EPSILON_1;

  std::stringstream out;
  out << "Retrieved viewport size is not matched with the set size: " << vec2Get.x << ", " << vec2Set.x << ", " << vec2Get.y << ", " << vec2Set.y;

  DALI_CHECK_FALSE( ( fabs( vec2Get.x - vec2Set.x ) >= fEpsilon ) || ( fabs( vec2Get.y - vec2Set.y ) >= fEpsilon ), out.str().c_str());
  return true;
}

/**
 * @function        RenderTaskSetGetScreenToFrameBufferFunction
 * @description     Helper function for set & get ScreenToFrameBufferFunction
 * @param[out]      renderTaskList[renderTask list]
 * @param[in]       conversionFunction[screen to frameBuffer conversionFunction]
 * @return          bool
 */
bool RenderTaskSetGetScreenToFrameBufferFunction(Dali::RenderTaskList& renderTaskList, RenderTask::ScreenToFrameBufferFunction  conversionFunction)
{
  RenderTask renderTask = renderTaskList.CreateTask();
  DALI_CHECK_FALSE(!renderTask, "CreateTask() is failed to create RenderTask Object.");

  FrameBufferImage frameBufferImageSet = FrameBufferImage::New(Stage::GetCurrent().GetSize().width, Stage::GetCurrent().GetSize().height, Pixel::RGBA8888);
  DALI_CHECK_FALSE(!frameBufferImageSet, "FrameBufferImage::New is failed to create frameBufferImage object");
  BufferImage img = BufferImage::New( 1,1 );

  Actor iActor = ImageView::New(frameBufferImageSet);
  DALI_CHECK_FALSE(!iActor, "ImageView::New is failed to create frameBufferImage object.");

  Vector2 startValue( 1.0f, 1.0f );
  Property::Index index = iActor.RegisterProperty( "test-property", startValue );
  Constraint constraint = Constraint::New<Vector3>(iActor, index, EqualToConstraint());
  constraint.Apply();

  iActor.SetColor(Color::WHITE);

  renderTask.SetRefreshRate(RenderTask::REFRESH_ALWAYS);
  renderTask.SetSourceActor(iActor);
  renderTask.SetExclusive(true);
  renderTask.SetInputEnabled(false);
  renderTask.SetClearColor(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
  renderTask.SetClearEnabled(true);

  renderTask.SetScreenToFrameBufferFunction(conversionFunction);

  RenderTask::ScreenToFrameBufferFunction conversionFunction1 = renderTask.GetScreenToFrameBufferFunction();
  DALI_CHECK_FALSE(conversionFunction1 !=  conversionFunction, "SetScreenToFrameBufferFunction and GetScreenToFrameBufferFunction is not matched.");

  return true;
}

/**
 * @function      RenderTaskinit
 * @description   RenderTask initialization
 * @param[out]    stage [Handle to the Stage]
 * @param[out]    renderTaskList [Handle to the RenderTaskList]
 * @param[out]    renderTask [Handle to the RenderTask]
 * @return        True/False
 */
bool RenderTaskinit(Stage &stage, RenderTaskList &renderTaskList, RenderTask  &renderTask)
{
  const int TASK_NUMBER = 0;
  stage = Stage::GetCurrent();
  DALI_CHECK_FALSE(!stage, "stage is empty");

  renderTaskList = stage.GetRenderTaskList();
  DALI_CHECK_FALSE(renderTaskList.GetTaskCount() == INVALID_TASK_COUNT, "renderTaskList is empty");

  renderTask = renderTaskList.GetTask(TASK_NUMBER);
  DALI_CHECK_FALSE(!renderTask, "renderTask is not created");

  return true;
}

/**
 * @function     ImageInitialization
 * @description  Image creation
 * @param[in]    textureId  [id of texture]
 * @param[in]    width  [width of image]
 * @param[in]    height [height of image]
 * @return       image
 */

Image ImageInitialization(GLuint textureId, int width, int height )
{
  Image image;
  char* filename = NULL;
  int numChars = asprintf(&filename, "image%u.png", textureId );

  if( numChars > 0 )
  {
    const Vector2 closestImageSize( width, height );

    image = ResourceImage::New( filename );
    free (filename);
  }

  return image;
}

/**
 * @function     RenderTaskActorRepositionOutside
 * @description  To reposition the actor to outside the stage while rendering with or without culling
 * @param[in]    actor [ Actor instance  ]
 * @param[in]    fx [ X-axis position ]
 * @param[in]    fy [ Y-axis position ]
 * @param[in]    bDrawn [ Draw status ]
 * @param[out]   NA
 * @return       false : if without culling actor is not drawn or with culling actor is drawn unncessarily
 *                       at the position outside the stage
 *               true  : if without culling actor is drawn and with culling actor is not drawn
 *                       at the position outside the stage
 */

bool RenderTaskActorRepositionOutside(Actor actor, float fx, float fy, bool bDrawn )
{
  try
  {
    actor.SetPosition( fx, fy, 0.0f ); //Z-axis position set to zero
  }
  catch (DaliException& de)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    return false;
  }
  return true;
}


