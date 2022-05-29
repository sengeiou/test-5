#include "utc-dali-stage-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;
int gRenderCountStage;

static const float DEFAULT_ZERO_HORIZONTAL_DPI = 0.0f;
static const float DEFAULT_ZERO_VERTICAL_DPI = 0.0f;
static const unsigned int DEFAULT_ZERO_WIDTH = 0u;
static const unsigned int DEFAULT_ZERO_HEIGHT = 0u;

namespace
{

  // Functor for EventProcessingFinished signal
  struct EventProcessingFinishedFunctor
  {
    /**
     * @param[in] eventProcessingFinished reference to a boolean variable used to check if signal has been called.
     */
    EventProcessingFinishedFunctor( bool& eventProcessingFinished )
      : mEventProcessingFinished( eventProcessingFinished )
    {}

    void operator()()
    {
      mEventProcessingFinished = true;
    }

    bool& mEventProcessingFinished;
  };

  // Stores data that is populated in the key-event callback and will be read by the TET cases
  struct KeyEventSignalData
  {
    KeyEventSignalData()
      : functorCalled(false)
    {}

    void Reset()
    {
      functorCalled = false;

      receivedKeyEvent.keyModifier = 0;
      receivedKeyEvent.keyPressedName.clear();
      receivedKeyEvent.keyPressed.clear();
    }

    bool functorCalled;
    KeyEvent receivedKeyEvent;
  };

  // Functor that sets the data when called
  struct KeyEventReceivedFunctor
  {
    KeyEventReceivedFunctor( KeyEventSignalData& data ) : signalData( data ) { }

    bool operator()( const KeyEvent& keyEvent )
    {
      signalData.functorCalled = true;
      signalData.receivedKeyEvent = keyEvent;

      return true;
    }

    KeyEventSignalData& signalData;
  };

  // Stores data that is populated in the touched signal callback and will be read by the TET cases
  struct TouchedSignalData
  {
    TouchedSignalData()
      : functorCalled(false)
    {}

    void Reset()
    {
      functorCalled = false;

      receivedTouchEvent.points.clear();
      receivedTouchEvent.time = 0;
    }

    bool functorCalled;
    TouchEvent receivedTouchEvent;
  };

  // Functor that sets the data when touched signal is received
  struct TouchedFunctor
  {
    TouchedFunctor( TouchedSignalData& data ) : signalData( data ) { }

    void operator()( const TouchEvent& touch )
    {
      signalData.functorCalled = true;
      signalData.receivedTouchEvent = touch;
    }

    TouchedSignalData& signalData;
  };

  // Stores data that is populated in the wheel-event callback and will be read by the TET cases
  struct WheelEventSignalData
  {
    WheelEventSignalData()
      : functorCalled(false)
    {}

    void Reset()
    {
      functorCalled = false;
    }

    bool functorCalled;
    WheelEvent receivedWheelEvent;
  };

  // Functor that sets the data when wheel-event signal is received
  struct WheelEventReceivedFunctor
  {
    WheelEventReceivedFunctor( WheelEventSignalData& data ) : signalData( data ) { }

    bool operator()( const WheelEvent& wheelEvent )
    {
      signalData.functorCalled = true;
      signalData.receivedWheelEvent = wheelEvent;
      return true;
    }

    WheelEventSignalData& signalData;
  };

  struct ContextStatusFunctor
  {
    ContextStatusFunctor(bool& calledFlag) : mCalledFlag( calledFlag )
    {
      mCalledFlag = false;
    }

    void operator()()
    {
      mCalledFlag = true;
    }
    void Reset()
    {
      mCalledFlag = false;
    }

    bool& mCalledFlag;
  };

  struct SceneCreatedStatusFunctor
  {
    SceneCreatedStatusFunctor(bool& calledFlag) : mCalledFlag( calledFlag )
    {
      mCalledFlag = false;
    }

    void operator()()
    {
      mCalledFlag = true;
    }
    void Reset()
    {
      mCalledFlag = false;
    }

    bool& mCalledFlag;
  };

  struct ActorCreatedFunctor
  {
    ActorCreatedFunctor( bool& signalReceived )
      : mSignalVerified( signalReceived )
    {
    }

    void operator()( BaseHandle object )
    {
      Actor actor = Actor::DownCast( object );
      if( actor )
      {
        mSignalVerified = true;
      }
    }

    bool& mSignalVerified;
  };

} // unnamed namespace

void StageConstructor()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");

  DaliLog::PrintPass();
}

void StageGetCurrentP()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");

  DaliLog::PrintPass();
}

void StageGetCurrentN()
{
  try
  {
    Stage stage = Stage::GetCurrent();
  }
  catch( Dali::DaliException& e )
  {
    DALI_CHECK_FAIL( false, "GetCurrent failed" );
  }

  DaliLog::PrintPass();
}

void StageIsInstalled()
{
  bool bIsInstall = false;

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");

  bIsInstall=stage.IsInstalled();

  DALI_CHECK_FAIL(!bIsInstall,  "IsInstalled is failed to get expected value.");

  DaliLog::PrintPass();
}

void StageIsInstalledN()
{
  bool bIsInstall = Stage::IsInstalled();

  DALI_CHECK_FAIL(!bIsInstall,  "IsInstalled is failed to get expected value.");

  DaliLog::PrintPass();
}

void StageCopyConstructor()
{
  Vector4 vec4SetColor = Color::RED;
  Vector4 vec4GetColor = Color::WHITE;
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");
  stage.SetBackgroundColor( vec4SetColor);

  Stage stageCopy (stage) ;

  vec4GetColor = stageCopy.GetBackgroundColor();
  DALI_CHECK_FAIL(vec4GetColor!=vec4SetColor,  "CopyConstructor is failed.");

  DaliLog::PrintPass();
}

void StageOperatorAssignment()
{
  Vector4 vec4SetColor = Color::RED;
  Vector4    vec4GetColor = Color::WHITE;
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");
  stage.SetBackgroundColor( vec4SetColor);

  Stage stageOperator = stage;

  vec4GetColor= stageOperator.GetBackgroundColor( );
  DALI_CHECK_FAIL(vec4GetColor!=vec4SetColor,  "AssignmentOperator is failed to get expected value.");

  DaliLog::PrintPass();
}

void StageAdd()
{
  bool bIsOnStage = false;
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor,  "Actor::New() is Failed..");

  bIsOnStage=actor.OnStage();
  DALI_CHECK_FAIL(bIsOnStage,  "OnStage is Failed to get default value .");
  stage.Add( actor );

  bIsOnStage=actor.OnStage();
  DALI_CHECK_FAIL(!bIsOnStage,  "OnStage is Failed to get the expected value ");

  DaliLog::PrintPass();
}

void StageAddN()
{
  bool bIsOnStage = false;
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor,  "Actor::New() is Failed..");

  bIsOnStage=actor.OnStage();
  DALI_CHECK_FAIL(bIsOnStage,  "OnStage is Failed to get default value .");
  stage.Add( actor );

  bIsOnStage=actor.OnStage();
  DALI_CHECK_FAIL(!bIsOnStage,  "OnStage is Failed to get the expected value ");

  DaliLog::PrintPass();
}

void StageRemove()
{
  bool bIsOnStage = false;
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(actor.OnStage(),  "Actor should not be on stage. Failed..");

  stage.Add( actor );
  DALI_CHECK_FAIL(!actor.OnStage(),  "Actor should not be on stage. Failed..");

  stage.Remove(actor);
  bIsOnStage=actor.OnStage();
  DALI_CHECK_FAIL(bIsOnStage,  "OnStage is Failed to get the expected value ");

  DaliLog::PrintPass();
}

void StageRemoveN1()
{
  Stage stage = Stage::GetCurrent();
  Actor actor;

  bool asserted = false;
  try
  {
    // Actor is not valid, confirm a removal attempt does assert.
    stage.Remove( actor );
  }
  catch( Dali::DaliException& e )
  {
    DALI_CHECK_FAIL( asserted, "actor && \"Actor handle is empty\"" );
    asserted = true;
  }

  DALI_CHECK_FAIL( !asserted, "failed" );


  DaliLog::PrintPass();
}

void StageRemoveN2()
{
  Stage stage = Stage::GetCurrent();
  Actor actor = Actor::New();
  try
  {
    // Actor is not on stage, confirm a removal attempt does not assert / segfault.
    stage.Remove( actor );
  }
  catch( Dali::DaliException& e )
  {
    DALI_CHECK_FAIL( false, "actor && \"Actor handle is empty\"" );
  }

  DaliLog::PrintPass();
}

void StageRemoveN3()
{
  Stage stage = Stage::GetCurrent();

  // Initially we have a default layer
  DALI_CHECK_FAIL( stage.GetLayerCount() != 1u, "GetLayerCount Failed" );

  // Check we cannot remove the root layer from the stage.
  Layer layer = stage.GetRootLayer();
  bool asserted = true;
  try
  {
    stage.Remove( layer );
  }
  catch( Dali::DaliException& e )
  {
    DALI_CHECK_FAIL( asserted, "actor && \"Actor handle is empty\"" );
    asserted = true;
  }

  DALI_CHECK_FAIL( !asserted, "failed" );
  DALI_CHECK_FAIL( stage.GetLayerCount() !=  1u, "GetLayerCount Failed" );

  DaliLog::PrintPass();
}

void StageGetSize()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");

  Vector2 size = stage.GetSize();

  DALI_CHECK_FAIL(size.width <= static_cast<float>( DEFAULT_ZERO_WIDTH ), "Get Dpi horizontal failed");
  DALI_CHECK_FAIL(size.height <= static_cast<float>( DEFAULT_ZERO_HEIGHT ), "Get Dpi vertical failed");

  DaliLog::PrintPass();
}

void StageGetSizeN()
{
  Stage stage;
  Vector2 size;
  try
  {
    size = stage.GetSize();
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "GetSize handle is empty" );
  }

  DaliLog::PrintPass();
}

void StageGetRenderTaskList()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");

  // Check we get a valid instance.
  const RenderTaskList& tasks = stage.GetRenderTaskList();
  DALI_CHECK_FAIL( tasks.GetTaskCount() != 1u,  "GetTaskCount is Failed to get the expected value ");

  // RenderTaskList has it's own UTC tests.
  // But we can confirm that GetRenderTaskList in Stage retrieves the same RenderTaskList each time.
  RenderTask newTask = stage.GetRenderTaskList().CreateTask();
  DALI_CHECK_FAIL( stage.GetRenderTaskList().GetTask( 1 ) != newTask,  "GetTaskList is Failed to get the expected value ");

  DaliLog::PrintPass();
}

void StageGetRenderTaskListN()
{
  Stage stage;
  try
  {
    const RenderTaskList& tasks = stage.GetRenderTaskList();
    DALI_CHECK_FAIL( tasks.GetTaskCount() != 1u,  "GetTaskCount is Failed to get the expected value ")

  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "Stage test case is failed" );
  }

  DaliLog::PrintPass();
}

void StageGetLayerCount()
{
  unsigned int uGetLayerCount=0,uSetCount=2u;
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");
  Layer layer = Layer::New();
  DALI_CHECK_FAIL(!layer,  "Layer::New is Failed.");

  stage.Add(layer);

  uGetLayerCount= stage.GetLayerCount();
  // default layer count is 1u so checked with 2u
  DALI_CHECK_FAIL(uGetLayerCount!=uSetCount,  "GetLayerCount is Failed to get the expected value.");

  stage.Remove(layer);

  DaliLog::PrintPass();
}

void StageGetLayerCountN()
{
  Stage stage;
  unsigned int uGetLayerCount=0, uSetCount=2u;
  try
  {
    Layer layer = Layer::New();
    DALI_CHECK_FAIL(!layer,  "Layer::New is Failed.");

    stage.Add(layer);
    uGetLayerCount= stage.GetLayerCount();
    // default layer count is 1u so checked with 2u
    DALI_CHECK_FAIL(uGetLayerCount!=uSetCount,  "GetLayerCount is Failed to get the expected value.");
    stage.Remove(layer);

  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "Stage test case is failed" );
  }

  DaliLog::PrintPass();
}

void StageGetLayer()
{
  unsigned int uGetDepth =0u;

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");
  Layer layer = Layer::New();
  DALI_CHECK_FAIL(!layer,  "layer:;New() is Failed..");

  stage.Add(layer);

  uGetDepth = layer.GetDepth();

  Layer layerCheck = stage.GetLayer(uGetDepth);

  DALI_CHECK_FAIL(layerCheck!=layer,  "GetLayer is failed to get the expected value.");
  stage.Remove(layer);

  DaliLog::PrintPass();
}

void StageGetLayerN()
{
  Stage stage;
  unsigned int uGetDepth =0u;
  try
  {
    Layer layer = Layer::New();
    DALI_CHECK_FAIL(!layer,  "Layer::New is Failed.");

    uGetDepth = layer.GetDepth();

    Layer layerCheck = stage.GetLayer(uGetDepth);

    stage.Add(layer);
    DALI_CHECK_FAIL(layerCheck!=layer,  "GetLayer is failed to get the expected value.");
    stage.Remove(layer);

  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "Stage test case is failed" );
  }

  DaliLog::PrintPass();
}

void StageGetRootLayer()
{
  unsigned int uGetDepth = 0u;
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");
  Layer layer = Layer::New();
  DALI_CHECK_FAIL(!layer,  "Layer::New is Failed. to get expected value");
  uGetDepth = layer.GetDepth();

  Layer layerRoot = stage.GetLayer(uGetDepth);
  DALI_CHECK_FAIL(!layerRoot,  "GetLayer is Failed. to get expected value ");

  stage.Add( layer );
  layer.LowerToBottom();

  Layer layerRootCheck =stage.GetRootLayer();

  DALI_CHECK_FAIL(layerRootCheck!=layerRoot,  "GetRootLayer is failed to get expected value ");

  stage.Remove(layer);

  DaliLog::PrintPass();
}

void StageGetRootLayerN()
{
  Stage stage;
  unsigned int uGetDepth =0u;
  try
  {
    Layer layer = Layer::New();
    DALI_CHECK_FAIL(!layer,  "Layer::New is Failed. to get expected value");

    uGetDepth = layer.GetDepth();
    Layer layerCheck = stage.GetLayer(uGetDepth);
    DALI_CHECK_FAIL(!layerCheck,  "GetLayer is Failed. to get expected value ");

    Layer layerRootCheck =stage.GetRootLayer();
    DALI_CHECK_FAIL(layerRootCheck!=layerCheck,  "GetRootLayer is failed to get expected value ");

    DALI_CHECK_FAIL(layerCheck!=layer,  "GetLayer is failed to get the expected value.");
    stage.Remove(layer);
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "Stage test case is failed" );
  }

  DaliLog::PrintPass();
}

void StageSetBackgroundColor()
{
  bool bGetVal = false;
  Vector4 vec4SetColor = Color::RED;

  bGetVal = StageSetGetBackgroundColor(vec4SetColor);
  if(!bGetVal)
  {
    test_return_value=TC_FAIL;
    return;
  }
  DaliLog::PrintPass();
}

void StageGetBackgroundColor()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");

  DALI_CHECK_FAIL(Stage::DEFAULT_BACKGROUND_COLOR != stage.GetBackgroundColor(), "Get Background color failed");

  DaliLog::PrintPass();
}

void StageGetDpi()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");

  // Test the default DPI.
  Vector2 dpi = stage.GetDpi();

  DALI_CHECK_FAIL(dpi.x <= static_cast<float>( DEFAULT_ZERO_HORIZONTAL_DPI ), "Get Dpi horizontal failed");
  DALI_CHECK_FAIL(dpi.y <= static_cast<float>( DEFAULT_ZERO_VERTICAL_DPI), "Get Dpi vertical failed");

  DaliLog::PrintPass();
}

void StageGetDpiN()
{
  Stage stage;
  try
  {
    Vector2 dpi = stage.GetDpi();
    DALI_CHECK_FAIL(dpi.x <= static_cast<float>( DEFAULT_ZERO_HORIZONTAL_DPI ), "Get Dpi horizontal failed");
    DALI_CHECK_FAIL(dpi.y <= static_cast<float>( DEFAULT_ZERO_VERTICAL_DPI), "Get Dpi vertical failed");
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "GetDPi test case is failed" );
  }

  DaliLog::PrintPass();

}

void StageGetObjectRegistry()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");

  ObjectRegistry objRegistry= stage.GetObjectRegistry();

  DALI_CHECK_FAIL(!objRegistry,  "GetObjectRegistry is Failed.");

  DaliLog::PrintPass();
}

void StageGetObjectRegistryN()
{
  Stage stage;
  try
  {
    ObjectRegistry objRegistry= stage.GetObjectRegistry();
    DALI_CHECK_FAIL(!objRegistry,  "GetObjectRegistry is Failed.");
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "Stage test case is failed" );
  }

  DaliLog::PrintPass();
}

void StageKeepRendering()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");
  // Force rendering for the next 5 seconds
  stage.KeepRendering( 5.0f );

  DaliLog::PrintPass();
}

void StageKeepRenderingN()
{
  Stage stage;
  try
  {
    // Force rendering for the next 5 seconds
    stage.KeepRendering( -1.0f );
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "Stage test case is failed" );
  }

  DaliLog::PrintPass();
}

void StageKeyEventSignal()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");

  KeyEventSignalData data;
  KeyEventReceivedFunctor functor( data );

  KeyEvent event( "i", "i", 0, 0, 0, KeyEvent::Down );

  DaliLog::PrintPass();
}

void StageKeyEventSignalN()
{
  Stage stage;
  try
  {
    KeyEventSignalData data;
    KeyEventReceivedFunctor functor( data );

    KeyEvent event( "i", "i", 0, 0, 0, KeyEvent::Down );
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "Stage test case is failed" );
  }

  DaliLog::PrintPass();
}

void StageEventProcessingFinishedSignal()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");

  bool eventProcessingFinished = false;

  EventProcessingFinishedFunctor functor( eventProcessingFinished );
  Actor actor( Actor::New() );
  stage.Add( actor );

  DaliLog::PrintPass();
}

void StageEventProcessingFinishedSignalN()
{
  Stage stage;
  bool eventProcessingFinished = false;
  try
  {
    EventProcessingFinishedFunctor functor( eventProcessingFinished );

    Actor actor( Actor::New() );
    stage.Add( actor );
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "Stage test case is failed" );
  }

  DaliLog::PrintPass();
}

void StageTouchedSignal()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");

  DaliLog::PrintPass();
}

void StageTouchedSignalN()
{
  Stage stage;
  try
  {
    //TODO: Add code for handling h/w events.
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "Stage test case is failed" );
  }

  DaliLog::PrintPass();
}

void StageContextLostSignal()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");

  bool contextLost = false;
  ContextStatusFunctor contextLostFunctor( contextLost );

  DaliLog::PrintPass();
}

void StageContextLostSignalN()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");

  // Check that connecting to the signal with a bad stage instance causes an assert.
  bool contextLost = false;
  ContextStatusFunctor contextLostFunctor( contextLost );
  try
  {
    //TODO: Add code for handling h/w events.
  }
  catch(DaliException& e )
  {
    DALI_CHECK_FAIL( false, "Stage test case is failed" );
  }

  DaliLog::PrintPass();
}

void StageContextRegainedSignal()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");

  bool contextRegained = false;
  ContextStatusFunctor contextRegainedFunctor( contextRegained );

  DaliLog::PrintPass();
}

void StageContextRegainedSignalN()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "GetCurrent is Failed..");

  bool contextRegained = false;
  ContextStatusFunctor contextRegainedFunctor( contextRegained );
  try
  {
    //TODO: Add code for handling h/w events.
  }
  catch(DaliException& e )
  {
    DALI_CHECK_FAIL( false, "Stage test case is failed" );
  }

  DaliLog::PrintPass();
}

void StageSceneCreatedSignal()
{
  Stage stage = Stage::GetCurrent();

  bool signalCalled = false;
  SceneCreatedStatusFunctor sceneCreatedFunctor( signalCalled );

  DaliLog::PrintPass();
}

void StageSceneCreatedSignalN()
{
  Stage stage = Stage::GetCurrent();

  bool signalCalled = false;
  SceneCreatedStatusFunctor sceneCreatedFunctor( signalCalled );

  DaliLog::PrintPass();
}
