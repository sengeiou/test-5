#include "utc-dali-actor-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

static int gActorOnStageCallBackCalled = 0;
static int gActorOffStageCallBackCalled = 0;
static std::vector< std::string > gVecActorNamesOnOffStage;
static bool gOnRelayoutCallBackCalled = false;
static bool gHoverCallBackCalled = false;
static bool gTouchCallBackCalled = false;
static bool gWheelEventCallBackCalled = false;
static std::vector< std::string > gActorNamesRelayout;

int gRenderCount;                      /** Render count **/
Actor gActor;                       /** Actor instance **/
Vector3 gVec3ActorPositionGet(0.0f, 0.0f, 0.0f);    /** Getting position x, y, z**/
Matrix gActorChildWorldMatrix(false);         /** World matrix of child actor **/
Vector4 gVec4ExpectedColorGet;             /**Expected current world color **/

LayoutDirection::Type gLayoutDirectionType;

void LayoutDirectionChanged( Actor actor, LayoutDirection::Type type )
{
  gLayoutDirectionType = type;
}

namespace
{
struct PropertyStringIndex
{
  const char * const name;
  const Property::Index index;
  const Property::Type type;
};

const PropertyStringIndex PROPERTY_TABLE[] =
{
  { "parentOrigin",             Actor::Property::PARENT_ORIGIN,            Property::VECTOR3     },
  { "parentOriginX",            Actor::Property::PARENT_ORIGIN_X,          Property::FLOAT       },
  { "parentOriginY",            Actor::Property::PARENT_ORIGIN_Y,          Property::FLOAT       },
  { "parentOriginZ",            Actor::Property::PARENT_ORIGIN_Z,          Property::FLOAT       },
  { "anchorPoint",              Actor::Property::ANCHOR_POINT,             Property::VECTOR3     },
  { "anchorPointX",             Actor::Property::ANCHOR_POINT_X,           Property::FLOAT       },
  { "anchorPointY",             Actor::Property::ANCHOR_POINT_Y,           Property::FLOAT       },
  { "anchorPointZ",             Actor::Property::ANCHOR_POINT_Z,           Property::FLOAT       },
  { "size",                     Actor::Property::SIZE,                     Property::VECTOR3     },
  { "sizeWidth",                Actor::Property::SIZE_WIDTH,               Property::FLOAT       },
  { "sizeHeight",               Actor::Property::SIZE_HEIGHT,              Property::FLOAT       },
  { "sizeDepth",                Actor::Property::SIZE_DEPTH,               Property::FLOAT       },
  { "position",                 Actor::Property::POSITION,                 Property::VECTOR3     },
  { "positionX",                Actor::Property::POSITION_X,               Property::FLOAT       },
  { "positionY",                Actor::Property::POSITION_Y,               Property::FLOAT       },
  { "positionZ",                Actor::Property::POSITION_Z,               Property::FLOAT       },
  { "worldPosition",            Actor::Property::WORLD_POSITION,           Property::VECTOR3     },
  { "worldPositionX",           Actor::Property::WORLD_POSITION_X,         Property::FLOAT       },
  { "worldPositionY",           Actor::Property::WORLD_POSITION_Y,         Property::FLOAT       },
  { "worldPositionZ",           Actor::Property::WORLD_POSITION_Z,         Property::FLOAT       },
  { "orientation",              Actor::Property::ORIENTATION,              Property::ROTATION    },
  { "worldOrientation",         Actor::Property::WORLD_ORIENTATION,        Property::ROTATION    },
  { "scale",                    Actor::Property::SCALE,                    Property::VECTOR3     },
  { "scaleX",                   Actor::Property::SCALE_X,                  Property::FLOAT       },
  { "scaleY",                   Actor::Property::SCALE_Y,                  Property::FLOAT       },
  { "scaleZ",                   Actor::Property::SCALE_Z,                  Property::FLOAT       },
  { "worldScale",               Actor::Property::WORLD_SCALE,              Property::VECTOR3     },
  { "visible",                  Actor::Property::VISIBLE,                  Property::BOOLEAN     },
  { "color",                    Actor::Property::COLOR,                    Property::VECTOR4     },
  { "colorRed",                 Actor::Property::COLOR_RED,                Property::FLOAT       },
  { "colorGreen",               Actor::Property::COLOR_GREEN,              Property::FLOAT       },
  { "colorBlue",                Actor::Property::COLOR_BLUE,               Property::FLOAT       },
  { "colorAlpha",               Actor::Property::COLOR_ALPHA,              Property::FLOAT       },
  { "worldColor",               Actor::Property::WORLD_COLOR,              Property::VECTOR4     },
  { "worldMatrix",              Actor::Property::WORLD_MATRIX,             Property::MATRIX      },
  { "name",                     Actor::Property::NAME,                     Property::STRING      },
  { "sensitive",                Actor::Property::SENSITIVE,                Property::BOOLEAN     },
  { "leaveRequired",            Actor::Property::LEAVE_REQUIRED,           Property::BOOLEAN     },
  { "inheritOrientation",       Actor::Property::INHERIT_ORIENTATION,      Property::BOOLEAN     },
  { "inheritScale",             Actor::Property::INHERIT_SCALE,            Property::BOOLEAN     },
  { "colorMode",                Actor::Property::COLOR_MODE,               Property::STRING      },
  { "drawMode",                 Actor::Property::DRAW_MODE,                Property::STRING      },
  { "sizeModeFactor",           Actor::Property::SIZE_MODE_FACTOR,         Property::VECTOR3     },
  { "widthResizePolicy",        Actor::Property::WIDTH_RESIZE_POLICY,      Property::STRING      },
  { "heightResizePolicy",       Actor::Property::HEIGHT_RESIZE_POLICY,     Property::STRING      },
  { "sizeScalePolicy",          Actor::Property::SIZE_SCALE_POLICY,        Property::STRING      },
  { "widthForHeight",           Actor::Property::WIDTH_FOR_HEIGHT,         Property::BOOLEAN     },
  { "heightForWidth",           Actor::Property::HEIGHT_FOR_WIDTH,         Property::BOOLEAN     },
  { "padding",                  Actor::Property::PADDING,                  Property::VECTOR4     },
  { "minimumSize",              Actor::Property::MINIMUM_SIZE,             Property::VECTOR2     },
  { "maximumSize",              Actor::Property::MAXIMUM_SIZE,             Property::VECTOR2     },
  { "inheritPosition",          Actor::Property::INHERIT_POSITION,         Property::BOOLEAN     },
  { "clippingMode",             Actor::Property::CLIPPING_MODE,            Property::STRING      },
};
const unsigned int PROPERTY_TABLE_COUNT = sizeof( PROPERTY_TABLE ) / sizeof( PROPERTY_TABLE[0] );
} // unnamed namespace

void ActorOnStageCallback( Actor actor )
{
  ++gActorOnStageCallBackCalled;
  gVecActorNamesOnOffStage.push_back( actor.GetName() );
}


void ActorOffStageCallback( Actor actor )
{
  ++gActorOffStageCallBackCalled;
  gVecActorNamesOnOffStage.push_back( actor.GetName() );
}


void OnRelayoutCallback( Actor actor )
{
  LOG_I( "OnRelayoutCallback is called." );
  gOnRelayoutCallBackCalled = true;
  gActorNamesRelayout.push_back( actor.GetName() );
}

/*static bool TestCallback(Actor actor, const TouchEvent& event)
  {
  gTouchCallBackCalled = true;
  return false;
  }

  static bool TestCallback2(Actor actor, const WheelEvent& event)
  {
  gWheelEventCallBackCalled = true;
  return false;
  }


  static bool TestCallback3(Actor actor, const HoverEvent& event)
  {
  gHoverCallBackCalled = true;
  return false;
  }*/

/**
 * ##############################
 * TC Logic Implementation Area.
 * ##############################
 **/

void ActorDowncastP()
{
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Animation actor and stage initialization failed.");

  Stage::GetCurrent().Add(actor);
  BaseHandle object(actor);

  Actor actor2 = Actor::DownCast(object);
  DALI_CHECK_FAIL(!actor2, "Actor::DownCast is failed.");

  Stage::GetCurrent().Remove(actor);
  DaliLog::PrintPass();
}

void ActorGetIdP()
{
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);
  unsigned int uActorId = actor.GetId();

  DALI_CHECK_FAIL(uActorId == ACTOR_ID, "ActorId should not equal with set ID");

  Stage::GetCurrent().Remove(actor);
  DaliLog::PrintPass();
}

void ActorGetChildCountP()
{
  unsigned const int uInitChildCount = 1;
  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(parentActor);

  Actor childActor = Actor::New();
  DALI_CHECK_FAIL(!childActor, "childActor::New() is failed ");

  parentActor.Add(childActor);

  unsigned int uChildCount = parentActor.GetChildCount();
  DALI_CHECK_FAIL(uChildCount != uInitChildCount, "nChildCount should be equal to set value.");

  parentActor.Remove(childActor);
  Stage::GetCurrent().Remove(parentActor);

  DaliLog::PrintPass();
}

void ActorSetNameP()
{
  string strActorName("New_Actor");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);

  actor.SetName(strActorName);

  string strGetActorName("");
  strGetActorName = actor.GetName();

  DALI_CHECK_FAIL(strGetActorName.compare(strActorName) != 0, "GetActorName should be New_Actor");

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorGetNameP()
{
  string strActorName("New_Actor");

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);

  actor.SetName(strActorName);

  string strGetActorName("");
  strGetActorName = actor.GetName();

  DALI_CHECK_FAIL(strGetActorName.compare(strActorName) != 0, "GetActorName should be New_Actor");

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorSetDrawmodeP()
{
  Vector3 vec3Position( 1.0f, 2.0f, 3.0f );
  DrawMode::Type eSetDrawMode = DrawMode::OVERLAY_2D;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  actor.SetPosition( vec3Position );
  actor.SetParentOrigin( ParentOrigin::CENTER );
  actor.SetAnchorPoint( AnchorPoint::CENTER );
  actor.SetSize(vec3Position);
  Stage::GetCurrent().Add(actor);

  actor.SetDrawMode(eSetDrawMode);

  DrawMode::Type getDrawModeType = actor.GetDrawMode();
  DALI_CHECK_FAIL(getDrawModeType!=eSetDrawMode, "getDrawModeType should match with setDrawmode.");

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorGetDrawmodeP()
{
  Vector3 vec3Position( 1.0f, 2.0f, 3.0f );
  DrawMode::Type eSetDrawMode = DrawMode::OVERLAY_2D;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  actor.SetPosition( vec3Position );
  actor.SetParentOrigin( ParentOrigin::CENTER );
  actor.SetAnchorPoint( AnchorPoint::CENTER );
  actor.SetSize(vec3Position);
  Stage::GetCurrent().Add(actor);

  actor.SetDrawMode(eSetDrawMode);

  DrawMode::Type getDrawModeType = actor.GetDrawMode();
  DALI_CHECK_FAIL(getDrawModeType!=eSetDrawMode, "getDrawModeType should match with setDrawmode.");

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorGetChildAtP()
{
  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(parentActor);
  Actor childActor = Actor::New();

  DALI_CHECK_FAIL(!childActor, "Actor::New() is failed ");

  parentActor.Add(childActor);

  Actor getChildAt = parentActor.GetChildAt(0);

  DALI_CHECK_FAIL(getChildAt != childActor, "getChildAt should be childActor" );

  parentActor.Remove(childActor);
  Stage::GetCurrent().Remove(parentActor);

  DaliLog::PrintPass();
}

void ActorGetParentP()
{
  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(parentActor);

  Actor childActor = Actor::New();
  DALI_CHECK_FAIL(!childActor, "Actor::New() is failed ");

  parentActor.Add(childActor);

  Actor getParent = childActor.GetParent();

  DALI_CHECK_FAIL(getParent != parentActor, "getParent should be parentActor");
  Stage::GetCurrent().Remove(parentActor);

  DaliLog::PrintPass();
}

void ActorFindChildByNameP()
{
  const string strSetChildString = "childActor" ;
  Actor parentActor = Actor::New();

  DALI_CHECK_FAIL(!parentActor, "Actor::New() is failed ");

  parentActor.SetName( "parentActor" );
  Stage::GetCurrent().Add(parentActor);

  Actor childActor = Actor::New();
  DALI_CHECK_FAIL(!childActor, "Actor::New() is failed ");

  childActor.SetName( strSetChildString );
  parentActor.Add(childActor);

  Actor childFound = parentActor.FindChildByName(strSetChildString);

  if(childFound != childActor)
  {
    LOG_E("parentActor.FindChildByName() is faild");
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }

  parentActor.Remove(childActor);
  Stage::GetCurrent().Remove(parentActor);

  DaliLog::PrintPass();
}

void ActorFindChildByIdP()
{
  const string strSetChildString = "childActor" ;
  Actor parentActor = Actor::New();

  DALI_CHECK_FAIL(!parentActor, "Actor::New() is failed ");

  parentActor.SetName( "parentActor" );
  Stage::GetCurrent().Add(parentActor);

  Actor childActor = Actor::New();
  DALI_CHECK_FAIL(!childActor, "Actor::New() is failed ");

  childActor.SetName( strSetChildString );
  parentActor.Add(childActor);

  Actor childFound = parentActor.FindChildById(childActor.GetId());

  if(childFound != childActor)
  {
    LOG_E("parentActor.FindChildById() is faild");
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }

  parentActor.Remove(childActor);
  Stage::GetCurrent().Remove(parentActor);

  DaliLog::PrintPass();
}

void ActorUnparentP()
{
  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(parentActor);

  Actor childActor = Actor::New();
  DALI_CHECK_FAIL(!childActor, "Actor::New() is failed ");

  parentActor.Add(childActor);

  DALI_CHECK_FAIL(parentActor.GetChildCount() != 1, "ChildCount  Mismatched. ");

  childActor.Unparent();
  DALI_CHECK_FAIL(parentActor.GetChildCount() != 0, "ChildCount should be 0. ");

  Stage::GetCurrent().Remove(parentActor);

  DaliLog::PrintPass();
}

void ActorUnparentAndResetP()
{
  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(parentActor);

  Actor childActor = Actor::New();
  DALI_CHECK_FAIL(!childActor, "Actor::New() is failed ");

  parentActor.Add(childActor);

  DALI_CHECK_FAIL(parentActor.GetChildCount() != 1, "ChildCount  Mismatched. ");

  UnparentAndReset(childActor);
  DALI_CHECK_FAIL(parentActor.GetChildCount() != 0, "ChildCount should be 0. ");

  Stage::GetCurrent().Remove(parentActor);

  DaliLog::PrintPass();
}

void ActorAddP()
{
  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(parentActor);

  Actor childActor = Actor::New();
  DALI_CHECK_FAIL(!childActor, "Actor::New() is failed ");

  parentActor.Add(childActor);

  DALI_CHECK_FAIL(parentActor.GetChildCount() != 1, "ChildCount  Mismatched. ");

  Stage::GetCurrent().Remove(parentActor);

  DaliLog::PrintPass();
}

void ActorSetKeyboardFocusableP()
{
  bool bIsKeyboardFocusable = false , bSetkeyboardFocus = true ;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);

  actor.SetKeyboardFocusable(bSetkeyboardFocus);

  bIsKeyboardFocusable = actor.IsKeyboardFocusable();
  DALI_CHECK_FAIL(bSetkeyboardFocus != bIsKeyboardFocusable, "focusable by keyboard navigation should be enabled but it is disabled ");
  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorIsKeyboardFocusableP()
{
  bool bIsKeyboardFocusable = false , bSetkeyboardFocus = true ;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);

  actor.SetKeyboardFocusable(bSetkeyboardFocus);

  bIsKeyboardFocusable = actor.IsKeyboardFocusable();
  DALI_CHECK_FAIL(bSetkeyboardFocus != bIsKeyboardFocusable, "focusable by keyboard navigation should be enabled but it is disabled ");
  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorSetVisibleP()
{
  bool bIsVisible = false , bSetVisible = true ;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);

  actor.SetVisible(bSetVisible);

  bIsVisible = actor.IsVisible();
  DALI_CHECK_FAIL(bSetVisible != bIsVisible, "the visibility flag should be match with  set visible flag ");
  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorIsVisibleP()
{
  bool bIsVisible = false , bSetVisible = true ;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);

  actor.SetVisible(bSetVisible);

  bIsVisible = actor.IsVisible();
  DALI_CHECK_FAIL(bSetVisible != bIsVisible, "the visibility flag should be match with  set visible flag ");
  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorSetXYZP()
{
  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);

  gActor.SetX(DEFAULT_XYZ);

}

void VTActorCheckXPosition()
{
  gVec3ActorPositionGet = gActor.GetCurrentPosition();
  DALI_CHECK_FAIL(gVec3ActorPositionGet != Vector3(DEFAULT_XYZ, 0, 0), "set and get value mismatched for x position.");
  gActor.SetY(DEFAULT_XYZ);
}

void VTActorCheckXYPosition()
{
  gVec3ActorPositionGet = gActor.GetCurrentPosition();
  DALI_CHECK_FAIL(gVec3ActorPositionGet != Vector3(DEFAULT_XYZ, DEFAULT_XYZ, 0), "set and get value mismatched for x and y postion." );
  gActor.SetZ(DEFAULT_XYZ);
}

void VTActorCheckXYZPositionFinal()
{
  gVec3ActorPositionGet = gActor.GetCurrentPosition();
  DALI_CHECK_FAIL(gVec3ActorPositionGet != Vector3(DEFAULT_XYZ, DEFAULT_XYZ, DEFAULT_XYZ), "set and get value mismatched for x, y and z position." );
  Stage::GetCurrent().Remove(gActor);

  DaliLog::PrintPass();
}

void ActorOnStageP()
{
  bool bIsLayer = false, bOnStage = false;
  Layer layer;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  bOnStage = actor.OnStage();
  DALI_CHECK_FAIL(bOnStage, "the actor should not be connected to the Stage.");

  bIsLayer = actor.IsLayer();
  DALI_CHECK_FAIL(bIsLayer, "the actor should not be a layer.");

  layer = actor.GetLayer();
  DALI_CHECK_FAIL(layer, "the actor should not have a layer.");

  actor = Stage::GetCurrent().GetLayer( 0 );

  bOnStage = actor.OnStage();
  DALI_CHECK_FAIL(!bOnStage, "the actor should be connected to the Stage.");

  DaliLog::PrintPass();
}

void ActorGetLayerP()
{
  bool bIsLayer = false, bOnStage = false;
  Layer layer;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  bOnStage = actor.OnStage();
  DALI_CHECK_FAIL(bOnStage, "the actor should not be connected to the Stage.");

  bIsLayer = actor.IsLayer();
  DALI_CHECK_FAIL(bIsLayer, "the actor should not be a layer.");

  layer = actor.GetLayer();
  DALI_CHECK_FAIL(layer, "the actor should not have a layer.");

  actor = Stage::GetCurrent().GetLayer( 0 );

  bOnStage = actor.OnStage();
  DALI_CHECK_FAIL(!bOnStage, "the actor should be connected to the Stage.");

  layer = actor.GetLayer();
  DALI_CHECK_FAIL(!layer, "the actor should have a layer.");

  DaliLog::PrintPass();
}

void ActorIsLayerP()
{
  bool bIsLayer = false, bOnStage = false;
  Layer layer;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  bOnStage = actor.OnStage();
  DALI_CHECK_FAIL(bOnStage, "the actor should not be connected to the Stage.");

  bIsLayer = actor.IsLayer();
  DALI_CHECK_FAIL(bIsLayer, "the actor should not be a layer.");

  layer = actor.GetLayer();
  DALI_CHECK_FAIL(layer, "the actor should not have a layer.");

  actor = Stage::GetCurrent().GetLayer( 0 );

  bOnStage = actor.OnStage();
  DALI_CHECK_FAIL(!bOnStage, "the actor should be connected to the Stage.");

  bIsLayer = actor.IsLayer();
  DALI_CHECK_FAIL(!bIsLayer, "the actor should be a layer.");

  DaliLog::PrintPass();
}

void ActorIsRootP()
{
  bool bIsRoot = false;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  bIsRoot = actor.IsRoot();
  DALI_CHECK_FAIL(bIsRoot, "the actor should not be root actor ");

  actor = Stage::GetCurrent().GetLayer( 0 );
  bIsRoot = actor.IsRoot();
  DALI_CHECK_FAIL(!bIsRoot, "the actor should be root actor ");

  DaliLog::PrintPass();
}

void ActorOnStageSignalP()
{
  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, "Actor::New() is failed ");

  parentActor.SetName( "parent" );
  Actor childActor = Actor::New();

  DALI_CHECK_FAIL(!childActor, "Actor::New() child is failed ");

  childActor.SetName( "child" );
  gActorOnStageCallBackCalled = gActorOffStageCallBackCalled = 0;
  gVecActorNamesOnOffStage.clear();

  parentActor.OnStageSignal().Connect( ActorOnStageCallback );

  DALI_CHECK_FAIL(gActorOnStageCallBackCalled != 0, "Callback function for OnStageSignal should not be called.");
  parentActor.OffStageSignal().Connect( ActorOffStageCallback );

  DALI_CHECK_FAIL(gActorOffStageCallBackCalled != 0, "callback func for OffStageSignal should not be called");

  Stage::GetCurrent().Add(parentActor);
  if(gActorOnStageCallBackCalled != 1)
  {
    LOG_E("callback func for OnStageSignal should be called");
    Stage::GetCurrent().Remove(parentActor);
    test_return_value=TC_FAIL;
    return;
  }

  if(gActorOffStageCallBackCalled != 0)
  {
    LOG_E("callback func for OffStageSignal should not be called");
    Stage::GetCurrent().Remove(parentActor);
    test_return_value=TC_FAIL;
    return;
  }

  childActor.OnStageSignal().Connect( ActorOnStageCallback );
  childActor.OffStageSignal().Connect( ActorOffStageCallback );

  parentActor.Add(childActor);
  gActorOnStageCallBackCalled = gActorOffStageCallBackCalled = 0;
  gVecActorNamesOnOffStage.clear();

  Stage::GetCurrent().Remove(parentActor);
  if(gActorOffStageCallBackCalled != 2)
  {
    LOG_E("callback counter for OffStageSignal should be 2");
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }

  if(gActorOnStageCallBackCalled != 0)
  {
    LOG_E("callback func for OnStageSignal should not be called");
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }

  gActorOnStageCallBackCalled = gActorOffStageCallBackCalled = 0;
  gVecActorNamesOnOffStage.clear();

  Stage::GetCurrent().Add(parentActor);
  if(gActorOnStageCallBackCalled != 2)
  {
    LOG_E("callback counter for OnStageSignal should be 2");
    Stage::GetCurrent().Remove(parentActor);
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }

  if(gActorOffStageCallBackCalled != 0)
  {
    LOG_E("callback func for OffStageSignal should not be called");
    Stage::GetCurrent().Remove(parentActor);
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }

  gActorOnStageCallBackCalled = gActorOffStageCallBackCalled = 0;
  gVecActorNamesOnOffStage.clear();

  parentActor.Remove(childActor);
  if(gActorOnStageCallBackCalled != 0)
  {
    LOG_E("callback func for OnStageSignal should not be called");
    Stage::GetCurrent().Remove(parentActor);
    test_return_value=TC_FAIL;
    return;
  }

  DALI_CHECK_FAIL(gActorOffStageCallBackCalled != 1, "callback counter for OffStageSignal should be 1");

  Stage::GetCurrent().Remove(parentActor);

  DaliLog::PrintPass();
}

void ActorOffStageSignalP()
{
  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, "Actor::New() is failed ");

  parentActor.SetName( "parent" );
  Actor childActor = Actor::New();

  DALI_CHECK_FAIL(!childActor, "Actor::New() child is failed ");

  childActor.SetName( "child" );
  gActorOnStageCallBackCalled = gActorOffStageCallBackCalled = 0;
  gVecActorNamesOnOffStage.clear();

  parentActor.OnStageSignal().Connect( ActorOnStageCallback );

  DALI_CHECK_FAIL(gActorOnStageCallBackCalled != 0, "Callback function for OnStageSignal should not be called.");
  parentActor.OffStageSignal().Connect( ActorOffStageCallback );

  DALI_CHECK_FAIL(gActorOffStageCallBackCalled != 0, "callback func for OffStageSignal should not be called");

  Stage::GetCurrent().Add(parentActor);
  if(gActorOnStageCallBackCalled != 1)
  {
    LOG_E("callback func for OnStageSignal should be called");
    Stage::GetCurrent().Remove(parentActor);
    test_return_value=TC_FAIL;
    return;
  }

  if(gActorOffStageCallBackCalled != 0)
  {
    LOG_E("callback func for OffStageSignal should not be called");
    Stage::GetCurrent().Remove(parentActor);
    test_return_value=TC_FAIL;
    return;
  }

  childActor.OnStageSignal().Connect( ActorOnStageCallback );
  childActor.OffStageSignal().Connect( ActorOffStageCallback );

  parentActor.Add(childActor);
  gActorOnStageCallBackCalled = gActorOffStageCallBackCalled = 0;
  gVecActorNamesOnOffStage.clear();

  Stage::GetCurrent().Remove(parentActor);
  if(gActorOffStageCallBackCalled != 2)
  {
    LOG_E("callback counter for OffStageSignal should be 2");
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }

  if(gActorOnStageCallBackCalled != 0)
  {
    LOG_E("callback func for OnStageSignal should not be called");
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }

  gActorOnStageCallBackCalled = gActorOffStageCallBackCalled = 0;
  gVecActorNamesOnOffStage.clear();

  Stage::GetCurrent().Add(parentActor);
  if(gActorOnStageCallBackCalled != 2)
  {
    LOG_E("callback counter for OnStageSignal should be 2");
    Stage::GetCurrent().Remove(parentActor);
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }

  if(gActorOffStageCallBackCalled != 0)
  {
    LOG_E("callback func for OffStageSignal should not be called");
    Stage::GetCurrent().Remove(parentActor);
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }

  gActorOnStageCallBackCalled = gActorOffStageCallBackCalled = 0;
  gVecActorNamesOnOffStage.clear();

  parentActor.Remove(childActor);
  if(gActorOnStageCallBackCalled != 0)
  {
    LOG_E("callback func for OnStageSignal should not be called");
    Stage::GetCurrent().Remove(parentActor);
    test_return_value=TC_FAIL;
    return;
  }

  DALI_CHECK_FAIL(gActorOffStageCallBackCalled != 1, "callback counter for OffStageSignal should be 1");

  Stage::GetCurrent().Remove(parentActor);

  DaliLog::PrintPass();
}

void ActorSetAnchorPointP()
{
  float fX=0.0f, fY=0.0f, fZ=0.0f;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);
  Vector3 vec3SetAnchorPoint(fX, fY, fZ);
  actor.SetAnchorPoint(vec3SetAnchorPoint);

  Vector3 vec3GetAnchorPoint(0.1f, 0.1f, 0.1f);

  vec3GetAnchorPoint = actor.GetCurrentAnchorPoint();

  DALI_CHECK_FAIL(vec3GetAnchorPoint != vec3SetAnchorPoint, "Set and Get value mismatched.");
  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorGetCurrentAnchorPointP()
{
  float fX=0.0f, fY=0.0f, fZ=0.0f;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);
  Vector3 vec3SetAnchorPoint(fX, fY, fZ);
  actor.SetAnchorPoint(vec3SetAnchorPoint);

  Vector3 vec3GetAnchorPoint(0.1f, 0.1f, 0.1f);

  vec3GetAnchorPoint = actor.GetCurrentAnchorPoint();

  DALI_CHECK_FAIL(vec3GetAnchorPoint != vec3SetAnchorPoint, "Set and Get value mismatched.");
  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorGetCurrentWorldColorP()
{
  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, " Actor::New() is failed ");
  parentActor.SetColor(ACTOR_SET_COLOR);
  Stage::GetCurrent().Add(parentActor);

  Actor childActor = Actor::New();
  DALI_CHECK_FAIL(!childActor, "Actor::New() is failed ");

  parentActor.Add(childActor);
  childActor.SetColor(ACTOR_CHILD_SET_COLOR);
  ColorMode eColorMode = childActor.GetColorMode();
  if(eColorMode != USE_OWN_MULTIPLY_PARENT_ALPHA)
  {
    LOG_E("eColorMode should be USE_OWN_MULTIPLY_PARENT_ALPHA");
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }
  gActor = parentActor;
}

void VTActorCheckWorldOwnColor001()
{
  Actor childActor = gActor.GetChildAt(0);
  Vector4 vec4WorldColor = childActor.GetCurrentWorldColor();
  Vector4 vec4ExpectedColor(ACTOR_CHILD_SET_COLOR);
  vec4ExpectedColor.a *= ACTOR_SET_COLOR.a;

  if(vec4WorldColor != vec4ExpectedColor)
  {
    LOG_E("vec4WorldColor should be vec4ExpectedColor");
    gActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }

  childActor.SetColorMode(USE_OWN_COLOR);
  ColorMode eClrMode = childActor.GetColorMode();

  if(eClrMode != USE_OWN_COLOR)
  {
    LOG_E("eColorMode should be USE_OWN_COLOR");
    gActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }
}

void VTActorCheckWorldOwnColor002()
{
  Actor childActor = gActor.GetChildAt(0);
  Vector4 vec4ExpColor(childActor.GetCurrentWorldColor());

  DALI_CHECK_FAIL(vec4ExpColor != ACTOR_CHILD_SET_COLOR, "vec4WorldColor should be ACTOR_CHILD_SET_COLOR");

  gActor.Remove(childActor);
  Stage::GetCurrent().Remove(gActor);

  DaliLog::PrintPass();
}


void ActorGetCurrentColorP()
{
  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetColor(ACTOR_SET_COLOR);
}

void ActorSetColorP()
{
  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetColor(ACTOR_SET_COLOR);
}

void VTActorCheckColor()
{
  Vector4 vec4GetColor = gActor.GetCurrentColor();
  DALI_CHECK_FAIL(vec4GetColor != ACTOR_SET_COLOR, "vec4GetColor should be (1.0f, 1.0f, 1.0f, 0.5f)" );

  Stage::GetCurrent().Remove(gActor);

  DaliLog::PrintPass();
}

void ActorSetColorModeP()
{
  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, " Actor::New() is failed ");
  parentActor.SetColor(ACTOR_SET_COLOR);
  Stage::GetCurrent().Add(parentActor);

  Actor childActor = Actor::New();
  DALI_CHECK_FAIL(!childActor, "Actor::New() is failed ");

  parentActor.Add(childActor);
  childActor.SetColor(ACTOR_CHILD_SET_COLOR);
  ColorMode eColorMode = childActor.GetColorMode();
  if(eColorMode != USE_OWN_MULTIPLY_PARENT_ALPHA)
  {
    LOG_E("eColorMode should be USE_OWN_MULTIPLY_PARENT_ALPHA");
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }
  gActor = parentActor;

}

void ActorGetColorModeP()
{
  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, " Actor::New() is failed ");
  parentActor.SetColor(ACTOR_SET_COLOR);
  Stage::GetCurrent().Add(parentActor);

  Actor childActor = Actor::New();
  DALI_CHECK_FAIL(!childActor, "Actor::New() is failed ");

  parentActor.Add(childActor);
  childActor.SetColor(ACTOR_CHILD_SET_COLOR);
  ColorMode eColorMode = childActor.GetColorMode();
  if(eColorMode != USE_OWN_MULTIPLY_PARENT_ALPHA)
  {
    LOG_E("eColorMode should be USE_OWN_MULTIPLY_PARENT_ALPHA");
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }
  gActor = parentActor;

}

void ActorSetOpacityP()
{
  float fSetOpacity = 1.0f, fGetOpacity = 0.0f;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);
  actor.SetOpacity(fSetOpacity);

  fGetOpacity = 0.0f;
  fGetOpacity = actor.GetCurrentOpacity();

  DALI_CHECK_FAIL(fSetOpacity != fGetOpacity, "set and get value mismatched" );

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorGetCurrentOpacityP()
{
  float fSetOpacity = 1.0f, fGetOpacity = 0.0f;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);
  actor.SetOpacity(fSetOpacity);

  fGetOpacity = 0.0f;
  fGetOpacity = actor.GetCurrentOpacity();

  DALI_CHECK_FAIL(fSetOpacity != fGetOpacity, "set and get value mismatched" );

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorSetParentOriginP()
{
  float fX=0.0f, fY=0.0f, fZ=0.0f;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);
  Vector3 vec3SetParentOrigin(fX, fY, fZ);
  actor.SetParentOrigin(vec3SetParentOrigin);

  Vector3 vec3GetParentOrigin(0.1f, 0.1f, 0.1f);
  vec3GetParentOrigin = actor.GetCurrentParentOrigin();

  DALI_CHECK_FAIL(vec3GetParentOrigin != vec3SetParentOrigin, "Set and get value mismatched.");
  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorGetCurrentParentOriginP()
{
  float fX=0.0f, fY=0.0f, fZ=0.0f;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);
  Vector3 vec3SetParentOrigin(fX, fY, fZ);
  actor.SetParentOrigin(vec3SetParentOrigin);

  Vector3 vec3GetParentOrigin(0.1f, 0.1f, 0.1f);
  vec3GetParentOrigin = actor.GetCurrentParentOrigin();

  DALI_CHECK_FAIL(vec3GetParentOrigin != vec3SetParentOrigin, "Set and get value mismatched.");
  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorGetCurrentWorldPositionP()
{
  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, "Actor::New() is failed ");

  parentActor.SetPosition(ACTOR_SET_POSITION);
  parentActor.SetParentOrigin( ParentOrigin::CENTER );
  parentActor.SetAnchorPoint( AnchorPoint::CENTER );
  Stage::GetCurrent().Add(parentActor);

  Actor childActor = Actor::New();
  DALI_CHECK_FAIL(!childActor, "Actor::New() is failed ");
  childActor.SetParentOrigin( ParentOrigin::CENTER );
  childActor.SetAnchorPoint( AnchorPoint::CENTER );
  childActor.SetPosition(ACTOR_CHILD_SET_POSITION);
  parentActor.Add(childActor);

  gActor = parentActor;
}

void VTActorGetWorldPositionParent001()
{
  Actor childActor = gActor.GetChildAt(0);
  Vector3 vec3WorldPosition = childActor.GetCurrentWorldPosition();
  if(vec3WorldPosition != (ACTOR_SET_POSITION+ACTOR_CHILD_SET_POSITION))
  {
    LOG_E("vec3WorldPosition should be sum of parent and child position");
    gActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }

  gActor.Remove(childActor);
  Stage::GetCurrent().Remove(gActor);

  DaliLog::PrintPass();
}

void ActorSetPositionP()
{
  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, " Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetPosition(DEFAULT_XYZ, DEFAULT_XYZ);
}

void VTActorCheckCurrentPosition001()
{
  Vector3 ve3Position(Vector2(DEFAULT_XYZ, DEFAULT_XYZ));
  DALI_CHECK_FAIL(!ActorGetCurrentPosition(gActor,ve3Position, ACTORPOSITION_DOUBLE_INPUT_PARAM), "Set Get Current position failed for double input.");

  Stage::GetCurrent().Remove(gActor);
  DaliLog::PrintPass();
}


void ActorSetPositionP2()
{
  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, " Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetPosition(DEFAULT_XYZ, DEFAULT_XYZ, DEFAULT_XYZ);
}
void VTActorCheckCurrentPosition002()
{
  Vector3 ve3Position(DEFAULT_XYZ, DEFAULT_XYZ, DEFAULT_XYZ);
  DALI_CHECK_FAIL(!ActorGetCurrentPosition(gActor,ve3Position,ACTORPOSITION_MULTI_INPUT_PARAM), "Set Get Current position failed for multi input param.");

  Stage::GetCurrent().Remove(gActor);
  DaliLog::PrintPass();
}


void ActorSetPositionP3()
{
  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, " Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetPosition(ACTOR_SET_POSITION);
}
void VTActorCheckCurrentPosition003()
{
  DALI_CHECK_FAIL(!ActorGetCurrentPosition(gActor,ACTOR_SET_POSITION,ACTORPOSITION_VECTOR_INPUT_PARAM), "Set Get Current position failed for vector input param.");

  Stage::GetCurrent().Remove(gActor);
  DaliLog::PrintPass();
}

void ActorGetCurrentPositionP()
{
  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, " Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetPosition(DEFAULT_XYZ, DEFAULT_XYZ);
}

void ActorGetCurrentPositionP2()
{
  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, " Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetPosition(DEFAULT_XYZ, DEFAULT_XYZ, DEFAULT_XYZ);
}

void ActorGetCurrentPositionP3()
{
  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, " Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetPosition(ACTOR_SET_POSITION);
}

void ActorGetCurrentWorldOrientationP()
{
  bool bIsOrientationInherited = false;
  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, "Actor::New() is failed ");
  parentActor.SetOrientation(ACTOR_SET_ORIENTATION);
  Stage::GetCurrent().Add(parentActor);

  Actor childActor = Actor::New();
  DALI_CHECK_FAIL(!childActor, "Actor::New() is failed ");

  parentActor.Add(childActor);
  bIsOrientationInherited = false;
  bIsOrientationInherited = childActor.IsOrientationInherited();

  if(!bIsOrientationInherited)
  {
    LOG_E("bIsOrientationInherited should be true.");
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }

  gActor = parentActor;

}

void ActorIsOrientationInheritedP()
{
  bool bIsOrientationInherited = false;
  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, "Actor::New() is failed ");
  parentActor.SetOrientation(ACTOR_SET_ORIENTATION);
  Stage::GetCurrent().Add(parentActor);

  Actor childActor = Actor::New();
  DALI_CHECK_FAIL(!childActor, "Actor::New() is failed ");

  parentActor.Add(childActor);
  bIsOrientationInherited = false;
  bIsOrientationInherited = childActor.IsOrientationInherited();

  if(!bIsOrientationInherited)
  {
    LOG_E("bIsOrientationInherited should be true.");
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }

  gActor = parentActor;
}

void VTActorCheckWorldOrientation001()
{
  Actor childActor = gActor.GetChildAt(0);
  Quaternion quatGetWorldOrientation = childActor.GetCurrentWorldOrientation();

  if(quatGetWorldOrientation != ACTOR_SET_ORIENTATION)
  {
    LOG_E("quatGetWorldOrientation should be parent rotation");
    gActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }

  childActor.SetInheritOrientation(false);
  if(childActor.IsOrientationInherited())
  {
    LOG_E("bIsOrientationInherited should be false");
    gActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }
}

void VTActorCheckWorldOrientation002()
{
  Actor childActor = gActor.GetChildAt(0);
  DALI_CHECK_FAIL(childActor.GetCurrentWorldOrientation() != Quaternion::IDENTITY, "quatGetWorldOrientation should be [ Axis: [0, 0, 0], Angle: 0 degrees ]");

  gActor.Remove(childActor);
  Stage::GetCurrent().Remove(gActor);

  DaliLog::PrintPass();
}

void ActorGetCurrentOrientationP()
{
  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, " Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetOrientation(Degree(ACTOR_DEGREE_ANGLE), ACTOR_AXIS_VEC3);
}

void ActorSetOrientationP()
{
  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, " Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetOrientation(Degree(ACTOR_DEGREE_ANGLE), ACTOR_AXIS_VEC3);
}
void VTActorChechCurrentOrientation001()
{
  DALI_CHECK_FAIL(!ActorGetCurrentOrientation(gActor,ACTOR_DEGREE_ANGLE, ACTOR_AXIS_VEC3, ACTORROTATION_DEGREE), "Set Get Current Orientation Failed for degree.");

  Stage::GetCurrent().Remove(gActor);

  DaliLog::PrintPass();
}


void ActorSetOrientationP2()
{
  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, " Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetOrientation(Radian(ACTOR_SET_ANGLE), ACTOR_AXIS_VEC3);
}
void VTActorChechCurrentOrientation002()
{
  DALI_CHECK_FAIL(!ActorGetCurrentOrientation(gActor,ACTOR_SET_ANGLE, ACTOR_AXIS_VEC3, ACTORROTATION_RADIAN), "Set Get Current Orientation Failed for radian.");

  Stage::GetCurrent().Remove(gActor);

  DaliLog::PrintPass();
}

void ActorSetOrientationP3()
{
  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, " Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetOrientation(Quaternion(Radian(ACTOR_SET_ANGLE), ACTOR_AXIS_VEC3));
}
void VTActorChechCurrentOrientation003()
{
  DALI_CHECK_FAIL(!ActorGetCurrentOrientation(gActor,ACTOR_SET_ANGLE, ACTOR_AXIS_VEC3, ACTORROTATION_QUATERNION), "Set Get Current Orientation Failed for quaternion.");

  Stage::GetCurrent().Remove(gActor);

  DaliLog::PrintPass();
}


void ActorSetInheritOrientationP()
{
  bool bIsOrientationInherited = false;
  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, "Actor::New() is failed ");
  parentActor.SetOrientation(ACTOR_SET_ORIENTATION);
  Stage::GetCurrent().Add(parentActor);

  Actor childActor = Actor::New();
  DALI_CHECK_FAIL(!childActor, "Actor::New() is failed ");

  parentActor.Add(childActor);
  bIsOrientationInherited = false;
  bIsOrientationInherited = childActor.IsOrientationInherited();

  if(!bIsOrientationInherited)
  {
    LOG_E("bIsOrientationInherited should be true.");
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }

  gActor = parentActor;
}

void ActorSetInheritScaleP()
{
  bool bIsInheritScale = false;

  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, "Actor::New() is failed ");

  parentActor.SetScale(ACTOR_SET_SCALE);
  Stage::GetCurrent().Add(parentActor);

  Actor childActor = Actor::New();
  DALI_CHECK_FAIL(!childActor, "Actor::New() is failed ");

  childActor.SetScale(ACTOR_SCALE_BY);
  parentActor.Add(childActor);
  bIsInheritScale = false;

  bIsInheritScale = childActor.IsScaleInherited();

  if(!bIsInheritScale)
  {
    LOG_E("bIsInheritScale should be true");
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }
  gActor = parentActor;
}

void VTActorCheckWorldScale001()
{
  Actor childActor = gActor.GetChildAt(0);
  Vector3 vec3WorldScale = childActor.GetCurrentWorldScale();

  if(vec3WorldScale != (ACTOR_SET_SCALE*ACTOR_SCALE_BY))
  {
    LOG_E("Failed to get expected vec3WorldScale when inherited from parent");
    gActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }

  childActor.SetInheritScale(false);
  if(childActor.IsScaleInherited())
  {
    LOG_E("bIsInheritScale should be false");
    gActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }
}

void VTActorCheckWorldScale002()
{
  Actor childActor = gActor.GetChildAt(0);
  DALI_CHECK_FAIL(childActor.GetCurrentWorldScale() != ACTOR_SCALE_BY, "vec3WorldScale should be child");

  gActor.Remove(childActor);
  Stage::GetCurrent().Remove(gActor);
  DaliLog::PrintPass();
}


void ActorIsScaleInheritedP()
{
  bool bIsInheritScale = false;

  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, "Actor::New() is failed ");

  parentActor.SetScale(ACTOR_SET_SCALE);
  Stage::GetCurrent().Add(parentActor);

  Actor childActor = Actor::New();
  DALI_CHECK_FAIL(!childActor, "Actor::New() is failed ");

  childActor.SetScale(ACTOR_SCALE_BY);
  parentActor.Add(childActor);
  bIsInheritScale = false;

  bIsInheritScale = childActor.IsScaleInherited();

  if(!bIsInheritScale)
  {
    LOG_E("bIsInheritScale should be true");
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }
  gActor = parentActor;
}

void ActorSetScaleP()
{
  Vector3 vec3Scale(10.0f, 10.0f, 10.0f);
  Vector3 vec3ScaleBy(1.0f, 1.0f, 1.0f);

  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetScale(ACTOR_SET_SCALE);
}

void VTActorCheckScaleBy001()
{
  Vector3 vec3GetScale = gActor.GetCurrentScale();

  DALI_CHECK_FAIL(vec3GetScale != ACTOR_SET_SCALE, "set and get scale value mismatched" );

  gActor.ScaleBy(ACTOR_SCALE_BY);
}

void VTActorCheckScaleBy002()
{
  Vector3 vec3GetScale = gActor.GetCurrentScale();

  DALI_CHECK_FAIL(vec3GetScale != ACTOR_SET_SCALE*ACTOR_SCALE_BY, "set and get scale value mismatched after scale by" );

  Stage::GetCurrent().Remove(gActor);
  DaliLog::PrintPass();
}


void ActorSetScaleP2()
{
  float size = 1.0f;

  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetScale(size);

  DaliLog::PrintPass();
}

void ActorSetScaleP3()
{
  float scaleX = 1.0f;
  float scaleY = 1.0f;
  float scaleZ = 1.0f;

  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetScale(scaleX, scaleY, scaleZ);

  DaliLog::PrintPass();
}

void ActorScaleByP()
{
  Vector3 vec3Scale(10.0f, 10.0f, 10.0f);
  Vector3 vec3ScaleBy(1.0f, 1.0f, 1.0f);

  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetScale(ACTOR_SET_SCALE);
}

void ActorGetCurrentWorldScaleP()
{
  bool bIsInheritScale = false;

  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, "Actor::New() is failed ");

  parentActor.SetScale(ACTOR_SET_SCALE);
  Stage::GetCurrent().Add(parentActor);

  Actor childActor = Actor::New();
  DALI_CHECK_FAIL(!childActor, "Actor::New() is failed ");

  childActor.SetScale(ACTOR_SCALE_BY);
  parentActor.Add(childActor);
  bIsInheritScale = false;

  bIsInheritScale = childActor.IsScaleInherited();

  if(!bIsInheritScale)
  {
    LOG_E("bIsInheritScale should be true");
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }
  gActor = parentActor;

}

void ActorGetCurrentWorldMatrixP()
{
  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, " Actor::New() is failed ");

  parentActor.SetParentOrigin(ParentOrigin::CENTER);
  parentActor.SetAnchorPoint(AnchorPoint::CENTER);
  Vector3 parentPosition( 10.0f, 20.0f, 30.0f);
  Radian rotationAngle(Degree(85.0f));
  Quaternion parentOrientation(rotationAngle, Vector3::ZAXIS);
  Vector3 parentScale( 1.0f, 2.0f, 3.0f );
  parentActor.SetPosition( parentPosition );
  parentActor.SetOrientation( parentOrientation );
  parentActor.SetScale( parentScale );
  Stage::GetCurrent().Add(parentActor);

  Actor childActor = Actor::New();
  DALI_CHECK_FAIL(!childActor, "Actor::New() is failed ");

  childActor.SetParentOrigin(ParentOrigin::CENTER);
  Vector3 childPosition( 0.0f, 0.0f, DEFAULT_XYZ );
  Radian childOrientationAngle(Degree(23.0f));
  Quaternion childOrientation( childOrientationAngle, Vector3::YAXIS );

  Vector3 childScale( 2.0f, 2.0f, 2.0f );
  childActor.SetPosition( childPosition );
  childActor.SetOrientation( childOrientation );
  childActor.SetScale( childScale );
  parentActor.Add(childActor);
  Matrix matWorldMatrix = childActor.GetCurrentWorldMatrix();

  if(matWorldMatrix != Matrix::IDENTITY)
  {
    LOG_E("matWorldMatrix should be Matrix::IDENTITY");
    parentActor.Remove(childActor);
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void ActorSetSensitiveP()
{
  bool bIsSensitive = false;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);
  actor.SetSensitive(true);

  bIsSensitive = actor.IsSensitive();

  DALI_CHECK_FAIL(!bIsSensitive, "touch event signals should be enabled but it is disabled ");
  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorIsSensitiveP()
{
  bool bIsSensitive = false;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);
  actor.SetSensitive(true);

  bIsSensitive = actor.IsSensitive();

  DALI_CHECK_FAIL(!bIsSensitive, "touch event signals should be enabled but it is disabled ");
  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorSetSizeP()
{
  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, " Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetSize(ACTOR_SET_SIZE.x, ACTOR_SET_SIZE.y);
}

void VTActorCheckCurrentSize001()
{
  DALI_CHECK_FAIL(!ActorGetCurrentSize(gActor,ACTOR_SET_SIZE,ACTORSIZE_DOUBLE_INPUT_PARAM), "Set Get Current size Failed for double input param.");

  Stage::GetCurrent().Remove(gActor);
  DaliLog::PrintPass();
}

void ActorSetSizeP2()
{
  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, " Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetSize(ACTOR_SET_SIZE.x, ACTOR_SET_SIZE.y, ACTOR_SET_SIZE.z);
}

void VTActorCheckCurrentSize002()
{
  DALI_CHECK_FAIL(!ActorGetCurrentSize(gActor,ACTOR_SET_SIZE,ACTORSIZE_MULTI_INPUT_PARAM), "Set Get Current size Failed for multi input param.");

  Stage::GetCurrent().Remove(gActor);
  DaliLog::PrintPass();
}


void ActorSetSizeP3()
{
  Vector2 vec2SetSize(ACTOR_SET_SIZE.x, ACTOR_SET_SIZE.y);
  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, " Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetSize(vec2SetSize);
}

void VTActorCheckCurrentSize003()
{
  DALI_CHECK_FAIL(!ActorGetCurrentSize(gActor,ACTOR_SET_SIZE,ACTORSIZE_VECTOR2_INPUT_PARAM), "Set Get Current size Failed for vector2 input param.");

  Stage::GetCurrent().Remove(gActor);
  DaliLog::PrintPass();
}

void ActorSetSizeP4()
{
  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, " Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetSize(ACTOR_SET_SIZE);
}

void VTActorCheckCurrentSize004()
{
  DALI_CHECK_FAIL(!ActorGetCurrentSize(gActor,ACTOR_SET_SIZE,ACTORSIZE_VECTOR3_INPUT_PARAM), "Set Get Current size Failed for vector3 input param.");

  Stage::GetCurrent().Remove(gActor);
  DaliLog::PrintPass();
}

void ActorGetCurrentSizeP()
{
  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, " Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);
  gActor.SetSize(ACTOR_SET_SIZE.x, ACTOR_SET_SIZE.y);
}

void ActorSetPaddingP()
{
  Padding pGetPadding;
  Padding pSetPadding(10.0f, 11.0f, 12.0f, 13.0f);
  Padding pDefaultPadding(0.0f, 0.0f, 0.0f, 0.0f);

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);
  actor.GetPadding(pGetPadding);
  DALI_CHECK_FAIL(pDefaultPadding != pGetPadding, "Failed to get actor's default padding.");

  actor.SetPadding(pSetPadding);
  actor.GetPadding(pGetPadding);
  DALI_CHECK_FAIL(pSetPadding != pGetPadding, "Failed to get actor's correct padding.");

  Vector3 vec3Position( 4.0f, 2.0f, 3.0f);
  pSetPadding = Padding(5.0f, 7.0f, 9.0f, 11.0f);
  Vector3 vec3Size(22.0f, 23.0f, 3.0f);

  actor.SetPadding(pSetPadding);
  actor.SetSize(vec3Size);
  actor.SetPosition(vec3Position);

  actor.GetPadding(pGetPadding);

  DALI_CHECK_FAIL( pGetPadding.left != pSetPadding.left, "Failed to get left padding value.");
  DALI_CHECK_FAIL( pGetPadding.right != pSetPadding.right, "Failed to get right padding value.");
  DALI_CHECK_FAIL( pGetPadding.bottom != pSetPadding.bottom, "Failed to get bottom padding value.");
  DALI_CHECK_FAIL( pGetPadding.top != pSetPadding.top, "Failed to get bottom padding value.");

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorGetPaddingP()
{
  Padding pGetPadding;
  Padding pSetPadding(10.0f, 11.0f, 12.0f, 13.0f);
  Padding pDefaultPadding(0.0f, 0.0f, 0.0f, 0.0f);

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);
  actor.GetPadding(pGetPadding);
  DALI_CHECK_FAIL(pDefaultPadding != pGetPadding, "Failed to get actor's default padding.");

  actor.SetPadding(pSetPadding);
  actor.GetPadding(pGetPadding);
  DALI_CHECK_FAIL(pSetPadding != pGetPadding, "Failed to get actor's correct padding.");

  Vector3 vec3Position( 4.0f, 2.0f, 3.0f);
  pSetPadding = Padding(5.0f, 7.0f, 9.0f, 11.0f);
  Vector3 vec3Size(22.0f, 23.0f, 3.0f);

  actor.SetPadding(pSetPadding);
  actor.SetSize(vec3Size);
  actor.SetPosition(vec3Position);

  actor.GetPadding(pGetPadding);

  DALI_CHECK_FAIL( pGetPadding.left != pSetPadding.left, "Failed to get left padding value.");
  DALI_CHECK_FAIL( pGetPadding.right != pSetPadding.right, "Failed to get right padding value.");
  DALI_CHECK_FAIL( pGetPadding.bottom != pSetPadding.bottom, "Failed to get bottom padding value.");
  DALI_CHECK_FAIL( pGetPadding.top != pSetPadding.top, "Failed to get bottom padding value.");

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorTranslateByP()
{
  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);

  gActor.TranslateBy(ACTOR_SET_POSITION);
}

void VTActorCheckTranslation001()
{
  Vector3 vec3Position = gActor.GetCurrentPosition();
  DALI_CHECK_FAIL(ACTOR_SET_POSITION != vec3Position, "Failed to translate given distance.");

  gActor.SetSize(vec3Position);
  gActor.TranslateBy(ACTOR_SET_TRANSLATE);

  Padding padding(5.0f, 7.0f, 9.0f, 11.0f);
  gActor.SetPadding(padding);
}

void VTActorCheckTranslation002()
{
  Vector3 vec3Distance = ACTOR_SET_POSITION + ACTOR_SET_TRANSLATE;
  Vector3 vec3Position = gActor.GetCurrentPosition();

  DALI_CHECK_FAIL(vec3Distance != vec3Position, "Failed to translate given distance after padding.");
  Stage::GetCurrent().Remove(gActor);

  DaliLog::PrintPass();
}


void ActorSetMaximumSizeP()
{
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);

  Vector2 vec2SetMaxSize(FLT_MAX, FLT_MAX);
  Vector2 vec2GetMaxSize, vec2Size;

  vec2GetMaxSize = actor.GetMaximumSize();

  DALI_CHECK_FAIL(vec2GetMaxSize != vec2SetMaxSize, "GetMaximumSize mismatched with default Maximum value.");

  vec2Size = Vector2(300.0f, 310.0f);
  vec2SetMaxSize = Vector2(320.0f, 330.0f);

  actor.SetSize(vec2Size);
  actor.SetMaximumSize(vec2SetMaxSize);

  vec2GetMaxSize = actor.GetMaximumSize();
  DALI_CHECK_FAIL(vec2GetMaxSize.width != vec2SetMaxSize.width, "Actor's maximum width mismatched.");
  DALI_CHECK_FAIL(vec2GetMaxSize.height != vec2SetMaxSize.height, "Actor's maximum height mismatched.");

  vec2Size = Vector2(290.0f, 340.0f);
  actor.SetSize(vec2Size);

  Padding padding(1.0f, 2.0f, 2.0f, 1.0f);
  actor.SetPadding(padding);

  vec2GetMaxSize = actor.GetMaximumSize();
  DALI_CHECK_FAIL(vec2GetMaxSize.width != vec2SetMaxSize.width, "Actor's maximum width mismatched after change size and padding.");
  DALI_CHECK_FAIL(vec2GetMaxSize.height != vec2SetMaxSize.height, "Actor's maximum height mismatched  after change size and padding.");

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorGetMaximumSizeP()
{
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);

  Vector2 vec2SetMaxSize(FLT_MAX, FLT_MAX);
  Vector2 vec2GetMaxSize, vec2Size;

  vec2GetMaxSize = actor.GetMaximumSize();

  DALI_CHECK_FAIL(vec2GetMaxSize != vec2SetMaxSize, "GetMaximumSize mismatched with default Maximum value.");

  vec2Size = Vector2(300.0f, 310.0f);
  vec2SetMaxSize = Vector2(320.0f, 330.0f);

  actor.SetSize(vec2Size);
  actor.SetMaximumSize(vec2SetMaxSize);

  vec2GetMaxSize = actor.GetMaximumSize();
  DALI_CHECK_FAIL(vec2GetMaxSize.width != vec2SetMaxSize.width, "Actor's maximum width mismatched.");
  DALI_CHECK_FAIL(vec2GetMaxSize.height != vec2SetMaxSize.height, "Actor's maximum height mismatched.");

  vec2Size = Vector2(290.0f, 340.0f);
  actor.SetSize(vec2Size);

  Padding padding(1.0f, 2.0f, 2.0f, 1.0f);
  actor.SetPadding(padding);

  vec2GetMaxSize = actor.GetMaximumSize();
  DALI_CHECK_FAIL(vec2GetMaxSize.width != vec2SetMaxSize.width, "Actor's maximum width mismatched after change size and padding.");
  DALI_CHECK_FAIL(vec2GetMaxSize.height != vec2SetMaxSize.height, "Actor's maximum height mismatched  after change size and padding.");

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorGetMinimumSizeP()
{
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);

  Vector2 vec2SetMinSize;
  Vector2 vec2GetMinSize, vec2Size;

  vec2GetMinSize = actor.GetMinimumSize();

  DALI_CHECK_FAIL(vec2GetMinSize != vec2SetMinSize, "GetMinimumSize mismatched with default Minimum value.");

  vec2Size = Vector2(150.0f, 140.0f);
  vec2SetMinSize = Vector2(120.0f, 115.0f);

  actor.SetSize(vec2Size);
  actor.SetMinimumSize(vec2SetMinSize);

  vec2GetMinSize = actor.GetMinimumSize();
  DALI_CHECK_FAIL(vec2GetMinSize.width != vec2SetMinSize.width, "Actor's Minimum width mismatched.");
  DALI_CHECK_FAIL(vec2GetMinSize.height != vec2SetMinSize.height, "Actor's Minimum height mismatched.");

  vec2Size = Vector2(290.0f, 340.0f);
  actor.SetSize(vec2Size);

  Padding padding(1.0f, 2.0f, 2.0f, 1.0f);
  actor.SetPadding(padding);

  vec2GetMinSize = actor.GetMinimumSize();
  DALI_CHECK_FAIL(vec2GetMinSize.width != vec2SetMinSize.width, "Actor's Minimum width mismatched after change size and padding.");
  DALI_CHECK_FAIL(vec2GetMinSize.height != vec2SetMinSize.height, "Actor's Minimum height mismatched  after change size and padding.");

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorSetMinimumSizeP()
{
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);

  Vector2 vec2SetMinSize;
  Vector2 vec2GetMinSize, vec2Size;

  vec2GetMinSize = actor.GetMinimumSize();

  DALI_CHECK_FAIL(vec2GetMinSize != vec2SetMinSize, "GetMinimumSize mismatched with default Minimum value.");

  vec2Size = Vector2(150.0f, 140.0f);
  vec2SetMinSize = Vector2(120.0f, 115.0f);

  actor.SetSize(vec2Size);
  actor.SetMinimumSize(vec2SetMinSize);

  vec2GetMinSize = actor.GetMinimumSize();
  DALI_CHECK_FAIL(vec2GetMinSize.width != vec2SetMinSize.width, "Actor's Minimum width mismatched.");
  DALI_CHECK_FAIL(vec2GetMinSize.height != vec2SetMinSize.height, "Actor's Minimum height mismatched.");

  vec2Size = Vector2(290.0f, 340.0f);
  actor.SetSize(vec2Size);

  Padding padding(1.0f, 2.0f, 2.0f, 1.0f);
  actor.SetPadding(padding);

  vec2GetMinSize = actor.GetMinimumSize();
  DALI_CHECK_FAIL(vec2GetMinSize.width != vec2SetMinSize.width, "Actor's Minimum width mismatched after change size and padding.");
  DALI_CHECK_FAIL(vec2GetMinSize.height != vec2SetMinSize.height, "Actor's Minimum height mismatched  after change size and padding.");

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorOnRelayoutSignalP()
{
  gRenderCount = 1;

  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);

  gOnRelayoutCallBackCalled = false;
  gActorNamesRelayout.clear();

  gActor.SetName( ACTOR_SET_NAME );
  gActor.OnRelayoutSignal().Connect( OnRelayoutCallback );

  DALI_CHECK_FAIL( gOnRelayoutCallBackCalled != 0,"On layout Signal initialize failed.");

  gActor.SetResizePolicy( ResizePolicy::FIXED, Dimension::ALL_DIMENSIONS );
  gActor.SetSize( Vector2( 1.0f, 2.0f));
}

void VTActorCheckRelayoutSignal001()
{
  DALI_CHECK_FAIL(!gOnRelayoutCallBackCalled, "Failed to proper callback for fixed resize policy.");
  DALI_CHECK_FAIL(ACTOR_SET_NAME != gActorNamesRelayout[ 0 ], "Failed to get actor name for fixed resize policy.");

  //USE_NATURAL_SIZE
  gOnRelayoutCallBackCalled = false;

  gActor.SetResizePolicy( ResizePolicy::USE_NATURAL_SIZE, Dimension::ALL_DIMENSIONS );
  gActor.SetSize( Vector2( 7.0f, 62.0f ) );
}

void VTActorCheckRelayoutSignal002()
{
  DALI_CHECK_FAIL(!gOnRelayoutCallBackCalled, "Failed to proper callback for USE_NATURAL_SIZE resize policy.");

  //FILL_TO_PARENT
  gOnRelayoutCallBackCalled = false;

  gActor.SetResizePolicy( ResizePolicy::FILL_TO_PARENT , Dimension::ALL_DIMENSIONS );
  gActor.SetSize( Vector2( 2.0f, 9.0f) );
}

void VTActorCheckRelayoutSignal003()
{
  DALI_CHECK_FAIL(!gOnRelayoutCallBackCalled, "Failed to proper callback for FILL_TO_PARENT  resize policy.");

  //SIZE_RELATIVE_TO_PARENT
  gOnRelayoutCallBackCalled = false;

  gActor.SetResizePolicy( ResizePolicy::SIZE_RELATIVE_TO_PARENT  , Dimension::ALL_DIMENSIONS );
  gActor.SetSize( Vector2( 2.0f, 32.0f) );
}

void VTActorCheckRelayoutSignal004()
{
  DALI_CHECK_FAIL(!gOnRelayoutCallBackCalled, "Failed to proper callback for SIZE_RELATIVE_TO_PARENT resize policy.");

  //SIZE_FIXED_OFFSET_FROM_PARENT
  gOnRelayoutCallBackCalled = false;

  gActor.SetResizePolicy( ResizePolicy::SIZE_FIXED_OFFSET_FROM_PARENT   , Dimension::ALL_DIMENSIONS );
  gActor.SetSize( Vector2( 45.0f, 3.0f) );
}

void VTActorCheckRelayoutSignal005()
{
  DALI_CHECK_FAIL(!gOnRelayoutCallBackCalled, "Failed to proper callback for SIZE_FIXED_OFFSET_FROM_PARENT resize policy.");

  //FIT_TO_CHILDREN
  gOnRelayoutCallBackCalled = false;

  gActor.SetResizePolicy( ResizePolicy::FIT_TO_CHILDREN, Dimension::ALL_DIMENSIONS );
  gActor.SetSize( Vector2( 1.0f, 12.0f) );
}

void VTActorCheckRelayoutSignal006()
{
  DALI_CHECK_FAIL(!gOnRelayoutCallBackCalled, "Failed to proper callback for FIT_TO_CHILDREN resize policy.");

  //DIMENSION_DEPENDENCY
  gOnRelayoutCallBackCalled = false;

  gActor.SetResizePolicy( ResizePolicy::DIMENSION_DEPENDENCY, Dimension::ALL_DIMENSIONS );
  gActor.SetSize( Vector2( 11.0f, 22.0f) );
}

void VTActorCheckRelayoutSignal007()
{
  DALI_CHECK_FAIL(!gOnRelayoutCallBackCalled, "Failed to proper callback for DIMENSION_DEPENDENCY resize policy.");

  //USE_ASSIGNED_SIZE
  gOnRelayoutCallBackCalled = false;

  gActor.SetResizePolicy( ResizePolicy::USE_ASSIGNED_SIZE, Dimension::ALL_DIMENSIONS );
  gActor.SetSize( Vector2( 21.0f, 233.0f) );
}

void VTActorCheckRelayoutSignal008()
{
  DALI_CHECK_FAIL(!gOnRelayoutCallBackCalled, "Failed to proper callback for USE_ASSIGNED_SIZE resize policy.");

  gActor.OnRelayoutSignal().Disconnect( OnRelayoutCallback );
  Stage::GetCurrent().Remove(gActor);

  DaliLog::PrintPass();
}


void ActorSetResizePolicyP()
{
  gRenderCount = 1;

  gActor = Actor::New();
  DALI_CHECK_FAIL(!gActor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(gActor);

  gOnRelayoutCallBackCalled = false;
  gActorNamesRelayout.clear();

  gActor.SetName( ACTOR_SET_NAME );
  gActor.OnRelayoutSignal().Connect( OnRelayoutCallback );

  DALI_CHECK_FAIL( gOnRelayoutCallBackCalled != 0,"On layout Signal initialize failed.");

  gActor.SetResizePolicy( ResizePolicy::FIXED, Dimension::ALL_DIMENSIONS );
  gActor.SetSize( Vector2( 1.0f, 2.0f));
}

void ActorGetHeightForWidthP()
{
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);

  float fWidth = 0.0f;
  float fHeight = 0.0f;

  fHeight = actor.GetHeightForWidth(1.0f);
  DALI_CHECK_FAIL(fHeight != 1.0f, "Failed to get fHeight for width.");

  fWidth = 20.0f;
  fHeight = 30.0f;
  actor.SetSize(Vector2(fWidth, fHeight) );

  float fGetHeight = actor.GetHeightForWidth(fHeight);
  DALI_CHECK_FAIL(fGetHeight != fHeight, "Failed to get Height for width after changing actor size.");

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorGetWidthForHeightP()
{
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);

  float fWidth = 0.0f;
  float fHeight = 0.0f;

  fWidth = actor.GetWidthForHeight(1.0f);
  DALI_CHECK_FAIL(fWidth != 1.0f, "Failed to get default width for height.");

  fWidth = 20.0f;
  fHeight = 30.0f;
  actor.SetSize(Vector2(fWidth, fHeight) );

  float fGetWidth = actor.GetWidthForHeight(fWidth);
  DALI_CHECK_FAIL(fWidth != fGetWidth, "Failed to get width for height after changing actor size.");

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorSetSizeModeFactorP()
{
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);

  Vector3 vec3SizeModeproperty(1.0f, 1.0f, 1.0f);
  Vector3 vec3GetSizeModeproperty = actor.GetProperty(Actor::Property::SIZE_MODE_FACTOR).Get< Vector3 >();
  DALI_CHECK_FAIL(vec3SizeModeproperty != vec3GetSizeModeproperty, "Failed to get actor SIZE_MODE_FACTOR default property.");

  Vector3 vec3SizeMode(1.0f, 1.0f, 1.0f);
  Vector3 vec3GetSizeMode = actor.GetSizeModeFactor();
  DALI_CHECK_FAIL(vec3SizeMode != vec3GetSizeMode, "Failed to get actor's default size mode factor.");

  vec3SizeMode = Vector3(111.0f, 2.0f, 49.0f);
  actor.SetSizeModeFactor(vec3SizeMode);

  vec3GetSizeMode = actor.GetSizeModeFactor();
  DALI_CHECK_FAIL(vec3SizeMode != vec3GetSizeMode, "Get size mode factor mismatched with set size mode factor.");

  actor.SetSize(vec3SizeMode);

  vec3SizeMode = Vector3(3.0f, 4.0f, 5.0f);
  actor.SetProperty( Actor::Property::SIZE_MODE_FACTOR, vec3SizeMode );

  vec3GetSizeModeproperty = actor.GetProperty(Actor::Property::SIZE_MODE_FACTOR).Get< Vector3 >();
  DALI_CHECK_FAIL(vec3SizeMode != vec3GetSizeModeproperty, "Failed to get actor SIZE_MODE_FACTOR default property.");

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorGetSizeModeFactorP()
{
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);

  Vector3 vec3SizeModeproperty(1.0f, 1.0f, 1.0f);
  Vector3 vec3GetSizeModeproperty = actor.GetProperty(Actor::Property::SIZE_MODE_FACTOR).Get< Vector3 >();
  DALI_CHECK_FAIL(vec3SizeModeproperty != vec3GetSizeModeproperty, "Failed to get actor SIZE_MODE_FACTOR default property.");

  Vector3 vec3SizeMode(1.0f, 1.0f, 1.0f);
  Vector3 vec3GetSizeMode = actor.GetSizeModeFactor();
  DALI_CHECK_FAIL(vec3SizeMode != vec3GetSizeMode, "Failed to get actor's default size mode factor.");

  vec3SizeMode = Vector3(111.0f, 2.0f, 49.0f);
  actor.SetSizeModeFactor(vec3SizeMode);

  vec3GetSizeMode = actor.GetSizeModeFactor();
  DALI_CHECK_FAIL(vec3SizeMode != vec3GetSizeMode, "Get size mode factor mismatched with set size mode factor.");

  actor.SetSize(vec3SizeMode);

  vec3SizeMode = Vector3(3.0f, 4.0f, 5.0f);
  actor.SetProperty( Actor::Property::SIZE_MODE_FACTOR, vec3SizeMode );

  vec3GetSizeModeproperty = actor.GetProperty(Actor::Property::SIZE_MODE_FACTOR).Get< Vector3 >();
  DALI_CHECK_FAIL(vec3SizeMode != vec3GetSizeModeproperty, "Failed to get actor SIZE_MODE_FACTOR default property.");

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorSetSizeScalePolicyP()
{
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);

  SizeScalePolicy::Type pGetPolicy;
  SizeScalePolicy::Type pSetPolicy = SizeScalePolicy::USE_SIZE_SET;

  actor.SetSizeScalePolicy(pSetPolicy);
  pGetPolicy = actor.GetSizeScalePolicy();
  DALI_CHECK_FAIL(pGetPolicy != pSetPolicy, "Failed to get actor's size scale policy for USE_SIZE_SET.");

  //change actor size
  Vector3 vec3Size(7.0f, 8.0f, 9.0f);
  actor.SetSize(vec3Size);

  pSetPolicy = SizeScalePolicy::FIT_WITH_ASPECT_RATIO;
  actor.SetSizeScalePolicy(pSetPolicy);
  pGetPolicy = actor.GetSizeScalePolicy();
  DALI_CHECK_FAIL(pGetPolicy != pSetPolicy, "Failed to get actor's size scale policy for FIT_WITH_ASPECT_RATIO.");

  pSetPolicy = SizeScalePolicy::FILL_WITH_ASPECT_RATIO;
  actor.SetSizeScalePolicy(pSetPolicy);
  pGetPolicy = actor.GetSizeScalePolicy();
  DALI_CHECK_FAIL(pGetPolicy != pSetPolicy, "Failed to get actor's size scale policy for FILL_WITH_ASPECT_RATIO.");

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorGetSizeScalePolicyP()
{
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed ");

  Stage::GetCurrent().Add(actor);

  SizeScalePolicy::Type pGetPolicy;
  SizeScalePolicy::Type pSetPolicy = SizeScalePolicy::USE_SIZE_SET;

  actor.SetSizeScalePolicy(pSetPolicy);
  pGetPolicy = actor.GetSizeScalePolicy();
  DALI_CHECK_FAIL(pGetPolicy != pSetPolicy, "Failed to get actor's size scale policy for USE_SIZE_SET.");

  //change actor size
  Vector3 vec3Size(7.0f, 8.0f, 9.0f);
  actor.SetSize(vec3Size);

  pSetPolicy = SizeScalePolicy::FIT_WITH_ASPECT_RATIO;
  actor.SetSizeScalePolicy(pSetPolicy);
  pGetPolicy = actor.GetSizeScalePolicy();
  DALI_CHECK_FAIL(pGetPolicy != pSetPolicy, "Failed to get actor's size scale policy for FIT_WITH_ASPECT_RATIO.");

  pSetPolicy = SizeScalePolicy::FILL_WITH_ASPECT_RATIO;
  actor.SetSizeScalePolicy(pSetPolicy);
  pGetPolicy = actor.GetSizeScalePolicy();
  DALI_CHECK_FAIL(pGetPolicy != pSetPolicy, "Failed to get actor's size scale policy for FILL_WITH_ASPECT_RATIO.");

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorRotateByP()
{
  Actor testActor;
  unsigned int uCount;
  unsigned int uIndex = 0u;

  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, "Actor::New() is failed parentActor.");
  Stage::GetCurrent().Add(parentActor);

  Actor childActor1 = Actor::New();
  DALI_CHECK_FAIL(!childActor1, "Actor::New() is failed childActor1");

  Actor childActor2 = Actor::New();
  DALI_CHECK_FAIL(!childActor2, "Actor::New() is failed childActor2");

  Actor childActor3 = Actor::New();
  DALI_CHECK_FAIL(!childActor3, "Actor::New() is failed childActor3");

  uIndex++;
  parentActor.Add(childActor1);
  uCount = parentActor.GetChildCount();
  DALI_CHECK_FAIL(uCount != uIndex, "Number of child count mismatched atfer insering first child.");

  uIndex++;
  parentActor.Add(childActor2);
  uCount = parentActor.GetChildCount();
  DALI_CHECK_FAIL(uCount != uIndex, "Number of child count mismatched  atfer insering second child.");

  uIndex++;
  parentActor.Add(childActor3);
  uCount = parentActor.GetChildCount();
  DALI_CHECK_FAIL(uCount != uIndex, "Number of child count mismatched  atfer insering third child.");

  testActor = parentActor.GetChildAt(uIndex-3);
  DALI_CHECK_FAIL(testActor != childActor1, "Failed to retrieve first child.");

  testActor = parentActor.GetChildAt(uIndex-2);
  DALI_CHECK_FAIL(testActor != childActor2, "Failed to retrieve second child.");

  testActor = parentActor.GetChildAt(uIndex-1);
  DALI_CHECK_FAIL(testActor != childActor3, "Failed to retrieve third child.");

  //search check
  testActor = parentActor.FindChildById(childActor3.GetId());
  DALI_CHECK_FAIL(testActor != childActor3, "Failed to find child by Id.");

  parentActor.RotateBy((ACTOR_SET_ANGLE), Vector3::ZAXIS);
  gActor = parentActor;
}

void VTActorRotationCheck001()
{
  Quaternion quaternion(ACTOR_SET_ANGLE, Vector3::ZAXIS);
  Quaternion orientation = gActor.GetCurrentOrientation();
  DALI_CHECK_FAIL(quaternion != orientation, "Actor current orientation mismatched by radian");

  gActor.RotateBy(quaternion);
}

void VTActorRotationCheck002()
{
  Quaternion quaternion = Quaternion(ACTOR_SET_ANGLE * 2.0f, Vector3::ZAXIS);
  Quaternion orientation = gActor.GetCurrentOrientation();
  DALI_CHECK_FAIL(quaternion != orientation, "Actor current orientation mismatched by Quaternion");

  Stage::GetCurrent().Remove(gActor);

  DaliLog::PrintPass();
}


void ActorRotateByP2()
{
  Actor testActor;
  unsigned int uCount;
  unsigned int uIndex = 0u;

  Actor parentActor = Actor::New();
  DALI_CHECK_FAIL(!parentActor, "Actor::New() is failed parentActor.");
  Stage::GetCurrent().Add(parentActor);

  Actor childActor1 = Actor::New();
  DALI_CHECK_FAIL(!childActor1, "Actor::New() is failed childActor1");

  Actor childActor2 = Actor::New();
  DALI_CHECK_FAIL(!childActor2, "Actor::New() is failed childActor2");

  Actor childActor3 = Actor::New();
  DALI_CHECK_FAIL(!childActor3, "Actor::New() is failed childActor3");

  uIndex++;
  parentActor.Add(childActor1);
  uCount = parentActor.GetChildCount();
  DALI_CHECK_FAIL(uCount != uIndex, "Number of child count mismatched atfer insering first child.");

  uIndex++;
  parentActor.Add(childActor2);
  uCount = parentActor.GetChildCount();
  DALI_CHECK_FAIL(uCount != uIndex, "Number of child count mismatched  atfer insering second child.");

  uIndex++;
  parentActor.Add(childActor3);
  uCount = parentActor.GetChildCount();
  DALI_CHECK_FAIL(uCount != uIndex, "Number of child count mismatched  atfer insering third child.");

  testActor = parentActor.GetChildAt(uIndex-3);
  DALI_CHECK_FAIL(testActor != childActor1, "Failed to retrieve first child.");

  testActor = parentActor.GetChildAt(uIndex-2);
  DALI_CHECK_FAIL(testActor != childActor2, "Failed to retrieve second child.");

  testActor = parentActor.GetChildAt(uIndex-1);
  DALI_CHECK_FAIL(testActor != childActor3, "Failed to retrieve third child.");

  //search check
  testActor = parentActor.FindChildById(childActor3.GetId());
  DALI_CHECK_FAIL(testActor != childActor3, "Failed to find child by Id.");

  parentActor.RotateBy((ACTOR_SET_ANGLE), Vector3::ZAXIS);
  gActor = parentActor;
}

void ActorGetNaturalSizeP()
{
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed.");
  Stage::GetCurrent().Add(actor);

  Vector3 vec3GetNutaralSize;
  Vector3 vec3NutaralSize( 0.0f, 0.0f, 0.0f );
  vec3GetNutaralSize = actor.GetNaturalSize();
  DALI_CHECK_FAIL(vec3GetNutaralSize != vec3GetNutaralSize, "Natural size mismatched.");
  DaliLog::PrintPass();
}

void ActorResizePolicyP()
{
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed.");
  Stage::GetCurrent().Add(actor);

  Vector3 vec3GetNutaralSize;
  Vector3 vec3NutaralSize( 0.0f, 0.0f, 0.0f );
  vec3GetNutaralSize = actor.GetNaturalSize();
  DALI_CHECK_FAIL(vec3GetNutaralSize != vec3GetNutaralSize, "Natural size mismatched.");

  const std::string strDefaultPolicy = "USE_NATURAL_SIZE";
  std::string strGetDefaultPolicy = actor.GetProperty(Actor::Property::WIDTH_RESIZE_POLICY).Get< std::string >();
  DALI_CHECK_FAIL(strDefaultPolicy != strGetDefaultPolicy, "Default resize policy for width mismatched.");

  strGetDefaultPolicy = actor.GetProperty( Actor::Property::HEIGHT_RESIZE_POLICY ).Get< std::string >();
  DALI_CHECK_FAIL(strDefaultPolicy != strGetDefaultPolicy, "Default resize policy for height mismatched.");

  actor.SetResizePolicy(ResizePolicy::USE_NATURAL_SIZE, Dimension::ALL_DIMENSIONS);

  ResizePolicy::Type policy;
  for( unsigned int i = 0; i < Dimension::DIMENSION_COUNT; ++i)
  {
    policy = actor.GetResizePolicy( static_cast< Dimension::Type >(1 << i));
    DALI_CHECK_FAIL(policy != ResizePolicy::USE_NATURAL_SIZE, "Resize policy USE_NATURAL_SIZE failed for ALL_DIMENSIONS.");
  }

  actor.SetResizePolicy(ResizePolicy::FILL_TO_PARENT , Dimension::ALL_DIMENSIONS);
  for( unsigned int i = 0; i < Dimension::DIMENSION_COUNT; ++i)
  {
    policy = actor.GetResizePolicy( static_cast< Dimension::Type >(1 << i));
    DALI_CHECK_FAIL(policy != ResizePolicy::FILL_TO_PARENT, "Resize policy failed for FILL_TO_PARENT.");
  }

  actor.SetResizePolicy(ResizePolicy::SIZE_RELATIVE_TO_PARENT  , Dimension::ALL_DIMENSIONS);
  for( unsigned int i = 0; i < Dimension::DIMENSION_COUNT; ++i)
  {
    policy = actor.GetResizePolicy( static_cast< Dimension::Type >(1 << i));
    DALI_CHECK_FAIL(policy != ResizePolicy::SIZE_RELATIVE_TO_PARENT , "Resize policy failed for SIZE_RELATIVE_TO_PARENT.");
  }

  actor.SetResizePolicy(ResizePolicy::DIMENSION_DEPENDENCY    , Dimension::ALL_DIMENSIONS);
  for( unsigned int i = 0; i < Dimension::DIMENSION_COUNT; ++i)
  {
    policy = actor.GetResizePolicy( static_cast< Dimension::Type >(1 << i));
    DALI_CHECK_FAIL(policy != ResizePolicy::DIMENSION_DEPENDENCY   , "Resize policy failed for DIMENSION_DEPENDENCY");
  }

  actor.SetResizePolicy(ResizePolicy::FIT_TO_CHILDREN, Dimension::ALL_DIMENSIONS);
  for( unsigned int i = 0; i < Dimension::DIMENSION_COUNT; ++i)
  {
    policy = actor.GetResizePolicy( static_cast< Dimension::Type >(1 << i));
    DALI_CHECK_FAIL(policy != ResizePolicy::FIT_TO_CHILDREN, "Resize policy failed for FIT_TO_CHILDREN.");
  }

  actor.SetResizePolicy(ResizePolicy::USE_ASSIGNED_SIZE, Dimension::ALL_DIMENSIONS);
  for( unsigned int i = 0; i < Dimension::DIMENSION_COUNT; ++i)
  {
    policy = actor.GetResizePolicy( static_cast< Dimension::Type >(1 << i));
    DALI_CHECK_FAIL(policy != ResizePolicy::USE_ASSIGNED_SIZE, "Resize policy failed for USE_ASSIGNED_SIZE.");
  }

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void ActorOperatorAssignmentP()
{
  Actor tmpActor = Actor::New();
  DALI_CHECK_FAIL(!tmpActor, "Actor::New() is failed.");

  gActor = tmpActor;
  DALI_CHECK_FAIL(!gActor, "Actor (const Actor &copy) is failed.");

  DaliLog::PrintPass();
}

void ActorGetRelayoutSizeP()
{
  Actor tmpActor = Actor::New();
  DALI_CHECK_FAIL(!tmpActor, "Actor::New() is failed.");

  gActor = Actor(tmpActor);
  DALI_CHECK_FAIL(!gActor, "Actor (const Actor &copy) is failed.");
  Stage::GetCurrent().Add(gActor);

  float fRelayoutSize = gActor.GetRelayoutSize( Dimension::WIDTH);
  DALI_CHECK_FAIL( fRelayoutSize != 0.0f, "Failed to get default relayout size for WIDTH");

  fRelayoutSize = gActor.GetRelayoutSize( Dimension::HEIGHT);
  DALI_CHECK_FAIL( fRelayoutSize != 0.0f, "Failed to get default relayout size for HEIGHT");

  gActor.SetResizePolicy( ResizePolicy::FIXED, Dimension::WIDTH );
  gActor.SetSize( Vector2(ACTOR_SET_WIDTH, ACTOR_SET_HEIGHT));

}

void VTActorCheckRelayoutSize()
{
  float fRelayoutSize = gActor.GetRelayoutSize( Dimension::WIDTH);
  DALI_CHECK_FAIL( fRelayoutSize != ACTOR_SET_WIDTH, "Failed to get relayout size for WIDTH");

  gActor.SetResizePolicy( ResizePolicy::FIXED, Dimension::HEIGHT);
  fRelayoutSize = gActor.GetRelayoutSize( Dimension::HEIGHT);
  DALI_CHECK_FAIL(fRelayoutSize != ACTOR_SET_HEIGHT, "Failed to get relayout size for HEIGHT");

  Stage::GetCurrent().Remove(gActor);

  DaliLog::PrintPass();
}


void ActorConstructorP()
{
  Actor actor;
  DALI_CHECK_FAIL(actor, "Actor::Actor() is failed.");

  DaliLog::PrintPass();
}

void ActorCopyConstructorP()
{
  Actor tmpActor = Actor::New();
  DALI_CHECK_FAIL(!tmpActor, "Actor::New() is failed.");

  gActor = Actor(tmpActor);
  DALI_CHECK_FAIL(!gActor, "Actor (const Actor &copy) is failed.");

  DaliLog::PrintPass();
}

void ActorNewP()
{
  Actor tmpActor = Actor::New();
  DALI_CHECK_FAIL(!tmpActor, "Actor::New() is failed.");
  DaliLog::PrintPass();
}

void ActorGetHierarchyDepthP()
{
  /* Build tree of actors:
   *
   *              Depth
   *
   *       A (parent)       1
   *      / \
   *     B   C          2`
   *    / \   \
   *   D   E   F        3
   *
   * GetHierarchyDepth should return 1 for A, 2 for B and C, and 3 for D, E and F.
   */
  Stage stage( Stage::GetCurrent() );

  Actor actorA = Actor::New();
  Actor actorB = Actor::New();
  Actor actorC = Actor::New();
  Actor actorD = Actor::New();
  Actor actorE = Actor::New();
  Actor actorF = Actor::New();

  //Test that root actor has depth equal 0
  DALI_CHECK_FAIL( 0 != stage.GetRootLayer().GetHierarchyDepth(), "" );

  //Test actors return depth -1 when not connected to the tree
  DALI_CHECK_FAIL( -1 != actorA.GetHierarchyDepth(), "Default failed" );
  DALI_CHECK_FAIL( -1 != actorB.GetHierarchyDepth(), "Default failed" );
  DALI_CHECK_FAIL( -1 != actorC.GetHierarchyDepth(), "Default failed" );
  DALI_CHECK_FAIL( -1 != actorD.GetHierarchyDepth(), "Default failed" );
  DALI_CHECK_FAIL( -1 != actorE.GetHierarchyDepth(), "Default failed" );
  DALI_CHECK_FAIL( -1 != actorF.GetHierarchyDepth(), "Default failed" );

  //Create the hierarchy
  stage.Add( actorA );
  actorA.Add( actorB );
  actorA.Add( actorC );
  actorB.Add( actorD );
  actorB.Add( actorE );
  actorC.Add( actorF );

  //Test actors return correct depth
  DALI_CHECK_FAIL( 1 != actorA.GetHierarchyDepth(), "Failed to add"  );
  DALI_CHECK_FAIL( 2 != actorB.GetHierarchyDepth(), "Failed to add"  );
  DALI_CHECK_FAIL( 2 != actorC.GetHierarchyDepth(), "Failed to add"  );
  DALI_CHECK_FAIL( 3 != actorD.GetHierarchyDepth(), "Failed to add"  );
  DALI_CHECK_FAIL( 3 != actorE.GetHierarchyDepth(), "Failed to add"  );
  DALI_CHECK_FAIL( 3 != actorF.GetHierarchyDepth(), "Failed to add"  );

  //Removing actorB from the hierarchy. actorB, actorD and actorE should now have depth equal -1
  actorA.Remove( actorB );

  DALI_CHECK_FAIL( -1 != actorB.GetHierarchyDepth(), "Failed to remove"  );
  DALI_CHECK_FAIL( -1 != actorD.GetHierarchyDepth(), "Failed to remove"  );
  DALI_CHECK_FAIL( -1 != actorE.GetHierarchyDepth(), "Failed to remove"  );

  //Removing actorA from the stage. All actors should have depth equal -1
  stage.Remove( actorA );

  DALI_CHECK_FAIL( -1 != actorA.GetHierarchyDepth(), "Failed to remove"  );
  DALI_CHECK_FAIL( -1 != actorB.GetHierarchyDepth(), "Failed to remove"  );
  DALI_CHECK_FAIL( -1 != actorC.GetHierarchyDepth(), "Failed to remove"  );
  DALI_CHECK_FAIL( -1 != actorD.GetHierarchyDepth(), "Failed to remove"  );
  DALI_CHECK_FAIL( -1 != actorE.GetHierarchyDepth(), "Failed to remove"  );
  DALI_CHECK_FAIL( -1 != actorF.GetHierarchyDepth(), "Failed to remove"  );

  DaliLog::PrintPass();

}

void ActorSetLeaveRequiredP()
{
  Actor actor = Actor::New();

  actor.SetLeaveRequired(false);
  DALI_CHECK_FAIL(actor.GetLeaveRequired() != false , "Set and Get mismatch for Leave Required");

  DaliLog::PrintPass();
}

void ActorSetLeaveRequiredP2()
{
  Actor actor = Actor::New();

  actor.SetLeaveRequired(true);
  DALI_CHECK_FAIL(actor.GetLeaveRequired() != true , "Set and Get mismatch for Leave Required");

  DaliLog::PrintPass();
}

void ActorGetLeaveRequiredP()
{
  Actor actor = Actor::New();

  actor.SetLeaveRequired(false);
  DALI_CHECK_FAIL(actor.GetLeaveRequired() != false , "Set and Get mismatch for Leave Required");

  DaliLog::PrintPass();
}

void ActorGetLeaveRequiredP2()
{
  Actor actor = Actor::New();

  actor.SetLeaveRequired(true);
  DALI_CHECK_FAIL(actor.GetLeaveRequired() != true , "Set and Get mismatch for Leave Required");

  DaliLog::PrintPass();
}


void ActorGetTaregetSizeP()
{
  Actor actor = Actor::New();
  Vector3 vector(100.0f, 100.0f, 20.0f);

  DALI_CHECK_FAIL(vector == actor.GetTargetSize() , "Default size mismatch");
  actor.SetSize(vector);

  DALI_CHECK_FAIL(vector != actor.GetTargetSize() , "GetTargetSize is failed");

  DaliLog::PrintPass();
}

void ActorScreenToLocalP()
{
  gActor = Actor::New();
  gActor.SetAnchorPoint(AnchorPoint::TOP_LEFT);
  gActor.SetSize(100.0f, 100.0f);
  gActor.SetPosition(10.0f, 10.0f);
  Stage::GetCurrent().Add(gActor);
}

void VTActorCheckScreenToLocal001()
{
  float localX;
  float localY;

  DALI_CHECK_FAIL(!gActor.ScreenToLocal(localX, localY, 50.0f, 50.0f) , "screenToLocal is failed");

  DaliLog::PrintPass();
}

void ActorRemoveP()
{
  Actor parent = Actor::New();
  Actor child = Actor::New();
  Actor random = Actor::New();

  Stage::GetCurrent().Add( parent );

  DALI_CHECK_FAIL(parent.GetChildCount() != 0 , "Default Child Count is wrong");

  parent.Add(child);

  DALI_CHECK_FAIL(parent.GetChildCount() != 1 , "Adding of child is wrong");

  parent.Remove(random);

  DALI_CHECK_FAIL(parent.GetChildCount() != 1 , "Adding of child is wrong");

  DaliLog::PrintPass();
}

void ActorSetInheritPositionP()
{

  Actor parent = Actor::New();
  Vector3 parentPosition( 1.0f, 2.0f, 3.0f );
  parent.SetPosition( parentPosition );
  parent.SetParentOrigin( ParentOrigin::CENTER );
  parent.SetAnchorPoint( AnchorPoint::CENTER );
  Stage::GetCurrent().Add( parent );

  Actor child = Actor::New();
  child.SetParentOrigin( ParentOrigin::CENTER );
  child.SetAnchorPoint( AnchorPoint::CENTER );
  Vector3 childPosition( 10.0f, 11.0f, 12.0f );
  child.SetPosition( childPosition );
  parent.Add( child );

  // The actors should not have a world position yet
  DALI_CHECK_FAIL(parent.GetCurrentWorldPosition() !=  Vector3::ZERO, "Position of parent is wrong." );
  DALI_CHECK_FAIL(child.GetCurrentWorldPosition() != Vector3::ZERO,   "Position of child is wrong." );

  // first test default, which is to inherit position
  DALI_CHECK_FAIL(child.IsPositionInherited() != true,   "Inherited Position of child is wrong." );

  //Change child position
  Vector3 childOffset( -1.0f, 1.0f, 0.0f );
  child.SetPosition( childOffset );

  // Use local position as world postion
  child.SetInheritPosition( false );
  DALI_CHECK_FAIL(child.IsPositionInherited() != false,   "Inherited Position of child is wrong." );

  DaliLog::PrintPass();

}

void ActorIsPositionInheritedP()
{

  Actor parent = Actor::New();
  Vector3 parentPosition( 1.0f, 2.0f, 3.0f );
  parent.SetPosition( parentPosition );
  parent.SetParentOrigin( ParentOrigin::CENTER );
  parent.SetAnchorPoint( AnchorPoint::CENTER );
  Stage::GetCurrent().Add( parent );

  Actor child = Actor::New();
  child.SetParentOrigin( ParentOrigin::CENTER );
  child.SetAnchorPoint( AnchorPoint::CENTER );
  Vector3 childPosition( 10.0f, 11.0f, 12.0f );
  child.SetPosition( childPosition );
  parent.Add( child );

  // The actors should not have a world position yet
  DALI_CHECK_FAIL(parent.GetCurrentWorldPosition() !=  Vector3::ZERO, "Position of parent is wrong." );
  DALI_CHECK_FAIL(child.GetCurrentWorldPosition() != Vector3::ZERO,   "Position of child is wrong." );

  // first test default, which is to inherit position
  DALI_CHECK_FAIL(child.IsPositionInherited() != true,   "Inherited Position of child is wrong." );

  DaliLog::PrintPass();
}

void ActorRemoveRendererN()
{
  Actor parent = Actor::New();
  Actor child = Actor::New();

  Stage::GetCurrent().Add( parent );

  DALI_CHECK_FAIL(parent.GetChildCount() != 0 , "Default Child Count is wrong");

  parent.Add(child);

  DALI_CHECK_FAIL(parent.GetChildCount() != 1 , "Adding of child is wrong");

  parent.RemoveRenderer(0);

  DALI_CHECK_FAIL(parent.GetChildCount() != 1 , "Adding of child is wrong");

  DaliLog::PrintPass();
}

void ActorGetRendererCountN()
{
  Actor parent = Actor::New();
  Actor child = Actor::New();

  Stage::GetCurrent().Add( parent );

  DALI_CHECK_FAIL(parent.GetChildCount() != 0 , "Default Child Count is wrong");

  parent.Add(child);

  DALI_CHECK_FAIL(parent.GetChildCount() != 1 , "Adding of child is wrong");

  unsigned int count = parent.GetRendererCount();

  DALI_CHECK_FAIL(parent.GetChildCount() != 1 , "Adding of child is wrong");

  DaliLog::PrintPass();
}

void ActorLayoutDirectionPropertyP()
{
  Actor actor0 = Actor::New();

  DALI_CHECK_FAIL(actor0.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION ) != static_cast< int >( LayoutDirection::LEFT_TO_RIGHT ), "actor0 property is wrong");
  Stage::GetCurrent().Add( actor0 );

  Actor actor1 = Actor::New();
  DALI_CHECK_FAIL(actor1.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION ) != static_cast< int >( LayoutDirection::LEFT_TO_RIGHT ), "actor1 property is wrong");
  Actor actor2 = Actor::New();
  DALI_CHECK_FAIL(actor2.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION ) != static_cast< int >( LayoutDirection::LEFT_TO_RIGHT ), "actor2 property is wrong");
  Actor actor3 = Actor::New();
  DALI_CHECK_FAIL(actor3.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION ) != static_cast< int >( LayoutDirection::LEFT_TO_RIGHT ), "actor3 property is wrong");
  Actor actor4 = Actor::New();
  DALI_CHECK_FAIL(actor4.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION ) != static_cast< int >( LayoutDirection::LEFT_TO_RIGHT ), "actor4 property is wrong");
  Actor actor5 = Actor::New();
  DALI_CHECK_FAIL(actor5.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION ) != static_cast< int >( LayoutDirection::LEFT_TO_RIGHT ), "actor5 property is wrong");
  Actor actor6 = Actor::New();
  DALI_CHECK_FAIL(actor6.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION ) != static_cast< int >( LayoutDirection::LEFT_TO_RIGHT ), "actor6 property is wrong");
  Actor actor7 = Actor::New();
  DALI_CHECK_FAIL(actor7.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION ) != static_cast< int >( LayoutDirection::LEFT_TO_RIGHT ), "actor7 property is wrong");
  Actor actor8 = Actor::New();
  DALI_CHECK_FAIL(actor8.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION ) != static_cast< int >( LayoutDirection::LEFT_TO_RIGHT ), "actor8 property is wrong");
  Actor actor9 = Actor::New();
  DALI_CHECK_FAIL(actor9.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION ) != static_cast< int >( LayoutDirection::LEFT_TO_RIGHT ), "actor9 property is wrong");

  actor1.Add( actor2 );
  gLayoutDirectionType = LayoutDirection::LEFT_TO_RIGHT;
  actor2.LayoutDirectionChangedSignal().Connect( LayoutDirectionChanged );
  DALI_CHECK_FAIL(actor1.GetProperty< bool >( Actor::Property::INHERIT_LAYOUT_DIRECTION ) != 1 , "actor2 property is wrong");

  actor1.SetProperty( Actor::Property::LAYOUT_DIRECTION, LayoutDirection::RIGHT_TO_LEFT );
  DALI_CHECK_FAIL(actor1.GetProperty< bool >( Actor::Property::INHERIT_LAYOUT_DIRECTION ) != 0 , "actor1 property is wrong");
  DALI_CHECK_FAIL(actor1.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION ) !=  static_cast< int >( LayoutDirection::RIGHT_TO_LEFT ), "actor1 property is wrong");

  DALI_CHECK_FAIL(actor2.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION ) != static_cast< int >( LayoutDirection::RIGHT_TO_LEFT ), "actor2 property is wrong");
  DALI_CHECK_FAIL(gLayoutDirectionType != LayoutDirection::RIGHT_TO_LEFT , "gLayoutDirectionType is wrong");

  actor1.SetProperty( Actor::Property::INHERIT_LAYOUT_DIRECTION, true );
  actor0.Add( actor1 );

  DALI_CHECK_FAIL(actor1.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION )!= static_cast< int >( LayoutDirection::LEFT_TO_RIGHT ), "actor1 property is wrong");
  DALI_CHECK_FAIL(actor2.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION )!= static_cast< int >( LayoutDirection::LEFT_TO_RIGHT ), "actor2 property is wrong");

  Stage::GetCurrent().Add( actor3 );
  actor3.Add( actor4 );
  actor4.Add( actor5 );
  actor5.Add( actor6 );
  actor5.Add( actor7 );
  actor7.Add( actor8 );
  actor8.Add( actor9 );
  actor3.SetProperty( Actor::Property::LAYOUT_DIRECTION, "RIGHT_TO_LEFT" );
  actor5.SetProperty( Actor::Property::LAYOUT_DIRECTION, LayoutDirection::LEFT_TO_RIGHT );

  DALI_CHECK_FAIL(actor8.GetProperty< bool >( Actor::Property::INHERIT_LAYOUT_DIRECTION )!=1, "actor8 property is wrong");

  actor8.SetProperty( Actor::Property::INHERIT_LAYOUT_DIRECTION, false );
  DALI_CHECK_FAIL(actor8.GetProperty< bool >( Actor::Property::INHERIT_LAYOUT_DIRECTION )!=0, "actor8 property is wrong");

  actor7.SetProperty( Actor::Property::LAYOUT_DIRECTION, "RIGHT_TO_LEFT" );

  DALI_CHECK_FAIL(actor3.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION ) != static_cast< int >( LayoutDirection::RIGHT_TO_LEFT ), "actor3 property is wrong");
  DALI_CHECK_FAIL(actor4.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION ) != static_cast< int >( LayoutDirection::RIGHT_TO_LEFT ), "actor4 property is wrong");
  DALI_CHECK_FAIL(actor5.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION ) != static_cast< int >( LayoutDirection::LEFT_TO_RIGHT ), "actor5 property is wrong");
  DALI_CHECK_FAIL(actor6.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION ) != static_cast< int >( LayoutDirection::LEFT_TO_RIGHT ), "actor6 property is wrong");
  DALI_CHECK_FAIL(actor7.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION ) != static_cast< int >( LayoutDirection::RIGHT_TO_LEFT ), "actor7 property is wrong");
  DALI_CHECK_FAIL(actor8.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION ) != static_cast< int >( LayoutDirection::LEFT_TO_RIGHT ), "actor8 property is wrong");
  DALI_CHECK_FAIL(actor9.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION ) != static_cast< int >( LayoutDirection::LEFT_TO_RIGHT ), "actor9 property is wrong");

  actor8.SetProperty( Actor::Property::LAYOUT_DIRECTION, "RIGHT_TO_LEFT" );
  DALI_CHECK_FAIL(actor8.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION )!= static_cast< int >( LayoutDirection::RIGHT_TO_LEFT ), "actor8 property is wrong");
  DALI_CHECK_FAIL(actor9.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION )!= static_cast< int >( LayoutDirection::RIGHT_TO_LEFT ), "actor9 property is wrong");

  actor7.SetProperty( Actor::Property::LAYOUT_DIRECTION, LayoutDirection::LEFT_TO_RIGHT );
  DALI_CHECK_FAIL(actor7.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION )!= static_cast< int >( LayoutDirection::LEFT_TO_RIGHT ), "actor7 property is wrong");
  DALI_CHECK_FAIL(actor8.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION )!= static_cast< int >( LayoutDirection::RIGHT_TO_LEFT ), "actor8 property is wrong");
  DALI_CHECK_FAIL(actor9.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION )!= static_cast< int >( LayoutDirection::RIGHT_TO_LEFT ), "actor9 property is wrong");

  actor8.SetProperty( Actor::Property::INHERIT_LAYOUT_DIRECTION, true );
  DALI_CHECK_FAIL(actor8.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION )!= static_cast< int >( LayoutDirection::LEFT_TO_RIGHT ), "actor8 property is wrong");
  DALI_CHECK_FAIL(actor9.GetProperty< int >( Actor::Property::LAYOUT_DIRECTION )!= static_cast< int >( LayoutDirection::LEFT_TO_RIGHT ), "actor9 property is wrong");

  DaliLog::PrintPass();

}

void ActorPropertiesP()
{
  Actor actor = Actor::New();

  for ( unsigned int i = 0; i < PROPERTY_TABLE_COUNT; ++i )
  {
    DALI_CHECK_FAIL(actor.GetPropertyName( PROPERTY_TABLE[i].index )!= PROPERTY_TABLE[i].name, "Property name is wrong");
    DALI_CHECK_FAIL(actor.GetPropertyIndex( PROPERTY_TABLE[i].name )!= PROPERTY_TABLE[i].index, "Property index is wrong");
    DALI_CHECK_FAIL(actor.GetPropertyType( PROPERTY_TABLE[i].index )!= PROPERTY_TABLE[i].type, "Property type is wrong");
  }

  DaliLog::PrintPass();
}

void ActorRaiseLowerP()
{
  Actor parent = Actor::New();
  Actor actorA = Actor::New();
  Actor actorB = Actor::New();

  actorA.SetName("actorA");
  actorB.SetName("actorB");

  parent.Add(actorA);
  parent.Add(actorB);

  DALI_CHECK_FAIL(parent.GetChildAt(0).GetName().compare("actorA") != 0, "name of actorA is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(1).GetName().compare("actorB") != 0, "name of actorB is wrong");

  actorA.Raise();
  DALI_CHECK_FAIL(parent.GetChildAt(0).GetName().compare("actorB") != 0, "name of actorA is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(1).GetName().compare("actorA") != 0, "name of actorB is wrong");

  actorA.Lower();
  DALI_CHECK_FAIL(parent.GetChildAt(0).GetName().compare("actorA") != 0, "name of actorA is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(1).GetName().compare("actorB") != 0, "name of actorB is wrong");

  DaliLog::PrintPass();
}

void ActorLowerBelowP()
{
  Actor parent = Actor::New();
  Actor actorA = Actor::New();
  Actor actorB = Actor::New();
  Actor actorC = Actor::New();

  actorA.SetName("actorA");
  actorB.SetName("actorB");
  actorC.SetName("actorC");

  parent.Add(actorA);
  parent.Add(actorB);
  parent.Add(actorC);

  DALI_CHECK_FAIL(parent.GetChildAt(0).GetName().compare("actorA") != 0, "name of actorA is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(1).GetName().compare("actorB") != 0, "name of actorB is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(2).GetName().compare("actorC") != 0, "name of actorC is wrong");

  actorC.LowerBelow(actorB);
  DALI_CHECK_FAIL(parent.GetChildAt(0).GetName().compare("actorA") != 0, "name of actorA is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(1).GetName().compare("actorC") != 0, "name of actorB is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(2).GetName().compare("actorB") != 0, "name of actorC is wrong");

  actorC.LowerBelow(actorA);
  DALI_CHECK_FAIL(parent.GetChildAt(0).GetName().compare("actorC") != 0, "name of actorA is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(1).GetName().compare("actorA") != 0, "name of actorB is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(2).GetName().compare("actorB") != 0, "name of actorC is wrong");

  DaliLog::PrintPass();
}

void ActorRaiseToTopLowerToBottomP()
{
  Actor parent = Actor::New();
  Actor actorA = Actor::New();
  Actor actorB = Actor::New();
  Actor actorC = Actor::New();

  actorA.SetName("actorA");
  actorB.SetName("actorB");
  actorC.SetName("actorC");

  parent.Add(actorA);
  parent.Add(actorB);
  parent.Add(actorC);

  DALI_CHECK_FAIL(parent.GetChildAt(0).GetName().compare("actorA") != 0, "name of actorA is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(1).GetName().compare("actorB") != 0, "name of actorB is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(2).GetName().compare("actorC") != 0, "name of actorC is wrong");

  actorB.RaiseToTop();
  DALI_CHECK_FAIL(parent.GetChildAt(0).GetName().compare("actorA") != 0, "name of actorA is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(1).GetName().compare("actorC") != 0, "name of actorB is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(2).GetName().compare("actorB") != 0, "name of actorC is wrong");

  actorB.LowerToBottom();
  DALI_CHECK_FAIL(parent.GetChildAt(0).GetName().compare("actorB") != 0, "name of actorA is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(1).GetName().compare("actorA") != 0, "name of actorB is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(2).GetName().compare("actorC") != 0, "name of actorC is wrong");

  DaliLog::PrintPass();
}


void ActorRaiseAboveP()
{
  Actor parent = Actor::New();
  Actor actorA = Actor::New();
  Actor actorB = Actor::New();
  Actor actorC = Actor::New();

  actorA.SetName("actorA");
  actorB.SetName("actorB");
  actorC.SetName("actorC");

  parent.Add(actorA);
  parent.Add(actorB);
  parent.Add(actorC);
  DALI_CHECK_FAIL(parent.GetChildAt(0).GetName().compare("actorA") != 0, "name of actorA is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(1).GetName().compare("actorB") != 0, "name of actorB is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(2).GetName().compare("actorC") != 0, "name of actorC is wrong");

  actorA.RaiseAbove(actorB);
  DALI_CHECK_FAIL(parent.GetChildAt(0).GetName().compare("actorB") != 0, "name of actorA is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(1).GetName().compare("actorA") != 0, "name of actorB is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(2).GetName().compare("actorC") != 0, "name of actorC is wrong");

  actorA.RaiseAbove(actorC);
  DALI_CHECK_FAIL(parent.GetChildAt(0).GetName().compare("actorB") != 0, "name of actorA is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(1).GetName().compare("actorC") != 0, "name of actorB is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(2).GetName().compare("actorA") != 0, "name of actorC is wrong");

  DaliLog::PrintPass();
}

void ActorRaiseAboveActorAndTargetTheSameN()
{
  Actor parent = Actor::New();
  Actor actorA = Actor::New();
  Actor actorB = Actor::New();
  Actor actorC = Actor::New();

  actorA.SetName("actorA");
  actorB.SetName("actorB");
  actorC.SetName("actorC");

  parent.Add(actorA);
  parent.Add(actorB);
  parent.Add(actorC);

  DALI_CHECK_FAIL(parent.GetChildAt(0).GetName().compare("actorA") != 0, "name of actorA is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(1).GetName().compare("actorB") != 0, "name of actorB is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(2).GetName().compare("actorC") != 0, "name of actorC is wrong");

  actorA.RaiseAbove( actorA );
  DALI_CHECK_FAIL(parent.GetChildAt(0).GetName().compare("actorA") != 0, "name of actorA is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(1).GetName().compare("actorB") != 0, "name of actorB is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(2).GetName().compare("actorC") != 0, "name of actorC is wrong");

  actorA.RaiseAbove( actorC );
  DALI_CHECK_FAIL(parent.GetChildAt(0).GetName().compare("actorB") != 0, "name of actorA is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(1).GetName().compare("actorC") != 0, "name of actorB is wrong");
  DALI_CHECK_FAIL(parent.GetChildAt(2).GetName().compare("actorA") != 0, "name of actorC is wrong");

  DaliLog::PrintPass();
}
