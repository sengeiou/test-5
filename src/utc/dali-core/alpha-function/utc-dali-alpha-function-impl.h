#include "utc-dali-alpha-function-common.h"

int gRenderCountAlphaFunction;
Actor gActorAlphaFunction ;
Animation gAnimationAlphaFunction;
AlphaFunction gAlphaFunction;
Vector3 gVec3TargetPosition1;
Vector2 gVec2CPoint0, gVec2CPoint1;

float customAlphaFunction( float progress )
{
  return progress;
}

void AlphaFunctionDefault()
{
  float fX = FLOAT_VALUE_10F , fY = FLOAT_VALUE_10F , fZ = FLOAT_VALUE_10F ;
  gVec3TargetPosition1=Vector3(fX, fY, fZ);

  DALI_CHECK_FAIL(AlphaFunctionsInit(gActorAlphaFunction, gAnimationAlphaFunction) != true, "Alpha Functions Init Failed!");
  gAnimationAlphaFunction.AnimateTo(Property(gActorAlphaFunction, Actor::Property::POSITION), Property::Value(gVec3TargetPosition1), gAlphaFunction);
  gAnimationAlphaFunction.Play();
}
void VTAlphaFunctionDefault001()
{
  DALI_CHECK_FAIL(gActorAlphaFunction.GetCurrentPosition() != gVec3TargetPosition1, "Current position is not matched with target position.");

  AlphaFunction::BuiltinFunction getBuiltInFunc =  gAlphaFunction.GetBuiltinFunction();
  if(getBuiltInFunc != AlphaFunction::DEFAULT)
  {
    LOG_E("AlphaFunctions Default constructor failed to return default BuiltinFunction." );
    AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);
    test_return_value=1;
    return;
  }

  AlphaFunction::Mode mode = gAlphaFunction.GetMode();
  if(mode != AlphaFunction::BUILTIN_FUNCTION)
  {
    LOG_E("AlphaFunctions Default constructor failed to return default Mode." );
    AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);
    test_return_value=1;
    return;
  }

  AlphaFunctionPrototype prorotypeFunc = gAlphaFunction.GetCustomFunction();
  if(prorotypeFunc != 0)
  {
    LOG_E("AlphaFunctions Default constructor failed to return default prototype function." );
    AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);
    test_return_value=1;
    return;
  }

  Vector4 vec4BezierControlPoints = gAlphaFunction.GetBezierControlPoints();
  if(vec4BezierControlPoints != Vector4::ZERO)
  {
    LOG_E("AlphaFunctions Default constructor failed to return default Bezier control points." );
    AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);
    test_return_value=1;
    return;
  }

  AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);

  DaliLog::PrintPass();
}

void AlphaFunctionBuiltinFunction()
{
  float fX = FLOAT_VALUE_10F , fY = FLOAT_VALUE_10F , fZ = FLOAT_VALUE_10F ;

  DALI_CHECK_FAIL(AlphaFunctionsInit(gActorAlphaFunction, gAnimationAlphaFunction) != true, "Alpha Functions Init Failed!");

  gVec3TargetPosition1=Vector3(fX, fY, fZ);
  gAlphaFunction=AlphaFunction(AlphaFunction::LINEAR);

  gAnimationAlphaFunction.AnimateTo(Property(gActorAlphaFunction, Actor::Property::POSITION), Property::Value(gVec3TargetPosition1), gAlphaFunction);
  gAnimationAlphaFunction.Play();
}
void VTAlphaFunctionBuiltinFunction001()
{
  DALI_CHECK_FAIL(gActorAlphaFunction.GetCurrentPosition() != gVec3TargetPosition1, "Current position is not matched with target position.");

  AlphaFunction::BuiltinFunction builtInfunction =  gAlphaFunction.GetBuiltinFunction();
  if(builtInfunction != AlphaFunction::LINEAR)
  {
    LOG_E("AlphaFunctions constructor failed to create for BuiltinFunction LINEAR" );
    AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);
    test_return_value=1;
    return;
  }

  gAlphaFunction = AlphaFunction(AlphaFunction::REVERSE);
  builtInfunction =  gAlphaFunction.GetBuiltinFunction();
  if(builtInfunction != AlphaFunction::REVERSE)
  {
    LOG_E("AlphaFunctions constructor failed to create for BuiltinFunction REVERSE" );
    AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);
    test_return_value=1;
    return;
  }

  gAlphaFunction = AlphaFunction(AlphaFunction::EASE_IN_SQUARE);
  builtInfunction =  gAlphaFunction.GetBuiltinFunction();
  if(builtInfunction != AlphaFunction::EASE_IN_SQUARE)
  {
    LOG_E("AlphaFunctions constructor failed to create for BuiltinFunction EASE_IN_SQUARE" );
    AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);
    test_return_value=1;
    return;
  }

  gAlphaFunction = AlphaFunction(AlphaFunction::EASE_OUT_SQUARE);
  builtInfunction =  gAlphaFunction.GetBuiltinFunction();
  if(builtInfunction != AlphaFunction::EASE_OUT_SQUARE)
  {
    LOG_E("AlphaFunctions constructor failed to create for BuiltinFunction EASE_OUT_SQUARE" );
    AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);
    test_return_value=1;
    return;
  }

  gAlphaFunction = AlphaFunction(AlphaFunction::EASE_IN);
  builtInfunction =  gAlphaFunction.GetBuiltinFunction();
  if(builtInfunction != AlphaFunction::EASE_IN)
  {
    LOG_E("AlphaFunctions constructor failed to create for BuiltinFunction EASE_IN" );
    AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);
    test_return_value=1;
    return;
  }

  gAlphaFunction = AlphaFunction(AlphaFunction::EASE_OUT);
  builtInfunction =  gAlphaFunction.GetBuiltinFunction();
  if(builtInfunction != AlphaFunction::EASE_OUT)
  {
    LOG_E("AlphaFunctions constructor failed to create for BuiltinFunction EASE_OUT" );
    AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);
    test_return_value=1;
    return;
  }

  gAlphaFunction = AlphaFunction(AlphaFunction::EASE_IN_OUT);
  builtInfunction =  gAlphaFunction.GetBuiltinFunction();
  if(builtInfunction != AlphaFunction::EASE_IN_OUT)
  {
    LOG_E("AlphaFunctions constructor failed to create for BuiltinFunction EASE_IN_OUT" );
    AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);
    test_return_value=1;
    return;
  }

  gAlphaFunction = AlphaFunction(AlphaFunction:: EASE_IN_SINE);
  builtInfunction =  gAlphaFunction.GetBuiltinFunction();
  if(builtInfunction != AlphaFunction:: EASE_IN_SINE)
  {
    LOG_E("AlphaFunctions constructor failed to create for BuiltinFunction  EASE_IN_SINE" );
    AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);
    test_return_value=1;
    return;
  }

  gAlphaFunction = AlphaFunction(AlphaFunction:: EASE_OUT_SINE );
  builtInfunction =  gAlphaFunction.GetBuiltinFunction();
  if(builtInfunction != AlphaFunction:: EASE_OUT_SINE )
  {
    LOG_E("AlphaFunctions constructor failed to create for BuiltinFunction  EASE_OUT_SINE" );
    AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);
    test_return_value=1;
    return;
  }

  gAlphaFunction = AlphaFunction(AlphaFunction:: EASE_IN_OUT_SINE);
  builtInfunction =  gAlphaFunction.GetBuiltinFunction();
  if(builtInfunction != AlphaFunction:: EASE_IN_OUT_SINE )
  {
    LOG_E("AlphaFunctions constructor failed to create for BuiltinFunction  EASE_IN_OUT_SINE" );
    AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);
    test_return_value=1;
    return;
  }

  gAlphaFunction = AlphaFunction(AlphaFunction:: BOUNCE);
  builtInfunction =  gAlphaFunction.GetBuiltinFunction();
  if(builtInfunction != AlphaFunction:: BOUNCE  )
  {
    LOG_E("AlphaFunctions constructor failed to create for BuiltinFunction  BOUNCE" );
    AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);
    test_return_value=1;
    return;
  }

  gAlphaFunction = AlphaFunction(AlphaFunction:: SIN);
  builtInfunction =  gAlphaFunction.GetBuiltinFunction();
  if(builtInfunction != AlphaFunction:: SIN)
  {
    LOG_E("AlphaFunctions constructor failed to create for BuiltinFunction SIN" );
    AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);
    test_return_value=1;
    return;
  }

  gAlphaFunction = AlphaFunction(AlphaFunction:: EASE_OUT_BACK);
  builtInfunction =  gAlphaFunction.GetBuiltinFunction();
  if(builtInfunction != AlphaFunction:: EASE_OUT_BACK)
  {
    LOG_E("AlphaFunctions constructor failed to create for BuiltinFunction EASE_OUT_BACK" );
    AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);
    test_return_value=1;
    return;
  }

  gAlphaFunction = AlphaFunction(AlphaFunction:: COUNT);
  builtInfunction =  gAlphaFunction.GetBuiltinFunction();
  if(builtInfunction != AlphaFunction:: COUNT)
  {
    LOG_E("AlphaFunctions constructor failed to create for BuiltinFunction COUNT" );
    AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);
    test_return_value=1;
    return;
  }

  AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);

  DaliLog::PrintPass();
}

void AlphaFunctionByControlPointsGetBezierControlPoints()
{
  float fX = FLOAT_VALUE_10F , fY = FLOAT_VALUE_10F , fZ = FLOAT_VALUE_10F ;

  DALI_CHECK_FAIL(AlphaFunctionsInit(gActorAlphaFunction, gAnimationAlphaFunction) != true, "Alpha Functions Init Failed!");
  gVec3TargetPosition1=Vector3(fX, fY, fZ);
  gVec2CPoint0=Vector2(0.0f,1.0f);
  gVec2CPoint1=Vector2(1.0f,0.0f);

  AlphaFunction alphaFunction(gVec2CPoint0, gVec2CPoint1);
  gAlphaFunction=alphaFunction;

  gAnimationAlphaFunction.AnimateTo(Property(gActorAlphaFunction, Actor::Property::POSITION), Property::Value(gVec3TargetPosition1), gAlphaFunction);
  gAnimationAlphaFunction.Play();
}
void VTAlphaFunctionByControlPointsGetBezierControlPoints001()
{
  DALI_CHECK_FAIL(gActorAlphaFunction.GetCurrentPosition() != gVec3TargetPosition1, "Current position is not matched with target position.");
  gVec2CPoint0 = Vector2(-9.0f,1.0f);
  gVec2CPoint1 = Vector2(9.0f,0.0f);
  gAlphaFunction = AlphaFunction(gVec2CPoint0,gVec2CPoint1);

  gAnimationAlphaFunction.AnimateTo(Property(gActorAlphaFunction, Actor::Property::POSITION), Property::Value(gVec3TargetPosition1), gAlphaFunction);
  gAnimationAlphaFunction.Play();
  DaliLog::PrintPass();
}
void VTAlphaFunctionByControlPointsGetBezierControlPoints002()
{
  Vector4 vec4BeizerPoints = gAlphaFunction.GetBezierControlPoints();
  Vector2 vec2GetCPoint0 = Vector2(vec4BeizerPoints.x,vec4BeizerPoints.y);
  Vector2 vec2GetCPoint1 = Vector2(vec4BeizerPoints.z,vec4BeizerPoints.w);

  DALI_CHECK_FAIL(vec2GetCPoint0 != gVec2CPoint0, "Control point 0 mismatched with beizer point");
  DALI_CHECK_FAIL(vec2GetCPoint1 != gVec2CPoint1, "Control point 1 mismatched with beizer point");
  //ensure the curve is monotonic[0,1]
  vec4BeizerPoints = gAlphaFunction.GetBezierControlPoints();
  vec2GetCPoint0 = Vector2(vec4BeizerPoints.x,vec4BeizerPoints.y);
  vec2GetCPoint1 = Vector2(vec4BeizerPoints.z,vec4BeizerPoints.w);

  DALI_CHECK_FAIL(vec2GetCPoint0 != Vector2(0.0f,1.0f), "Control point 0 mismatched with beizer point monotonic");
  DALI_CHECK_FAIL(vec2GetCPoint1 != Vector2(1.0f,0.0f), "Control point 1 mismatched with beizer point monotonic");

  AlphaFunction::Mode mode = gAlphaFunction.GetMode();
  DALI_CHECK_FAIL( mode != AlphaFunction::BEZIER, "Failed to get alpha function mode.");

  AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);

  DaliLog::PrintPass();
}

void AlphaFunctionByFunctionPrototypeGetCustomFunction()
{
  float fX = FLOAT_VALUE_10F , fY = FLOAT_VALUE_10F , fZ = FLOAT_VALUE_10F ;

  DALI_CHECK_FAIL(AlphaFunctionsInit(gActorAlphaFunction, gAnimationAlphaFunction) != true, "Alpha Functions Init Failed!");
  gVec3TargetPosition1=Vector3(fX, fY, fZ);

  gAlphaFunction=AlphaFunction(&customAlphaFunction);
  gAnimationAlphaFunction.AnimateTo(Property(gActorAlphaFunction, Actor::Property::POSITION), Property::Value(gVec3TargetPosition1), gAlphaFunction);
  gAnimationAlphaFunction.Play();
}

void VTAlphaFunctionByFunctionPrototypeGetCustomFunction001()
{
  DALI_CHECK_FAIL(gActorAlphaFunction.GetCurrentPosition() != gVec3TargetPosition1, "Current position is not matched with target position.");
  AlphaFunctionPrototype prototype = gAlphaFunction.GetCustomFunction();
  DALI_CHECK_FAIL( prototype != (&customAlphaFunction), "Failed to get custom function pointer.");

  AlphaFunction::Mode mode = gAlphaFunction.GetMode();
  DALI_CHECK_FAIL( mode != AlphaFunction::CUSTOM_FUNCTION, "Failed to get custom function mode.");

  AlphaFunctionRemoveAnimationActor(gActorAlphaFunction, gAnimationAlphaFunction);

  DaliLog::PrintPass();
}

void AlphaFunctionGetMode()
{
  //Create alpha function using a built-in function
  AlphaFunction alphaBuiltin( AlphaFunction::EASE_OUT);

  //AlphaFunction::Mode mode = gAlphaFunction.GetMode();
  //Check the mode is BUILTIN_FUNCTION
  DALI_CHECK_FAIL( alphaBuiltin.GetMode() != AlphaFunction::BUILTIN_FUNCTION, "Failed to get Mode for Built-In Function");

  //Create alpha function with pointer to function
  AlphaFunction alphaCustom( &customAlphaFunction );
  //Check the mode is CUSTOM_FUNCTION
  DALI_CHECK_FAIL( alphaCustom.GetMode()!= AlphaFunction::CUSTOM_FUNCTION, "Failed to get Mode for Custom Function");

  //Create alpha function with control points
  Vector2 controlPoint0 = Vector2(0.0f,1.0f);
  Vector2 controlPoint1 = Vector2(1.0f,0.0f);
  AlphaFunction alphaBezier( controlPoint0,controlPoint1 );
  //Check the mode is BEZIER
  DALI_CHECK_FAIL( alphaBezier.GetMode()!= AlphaFunction::BEZIER, "Failed to get Mode for Bezier Function");

  DaliLog::PrintPass();
}


void AlphaFunctionConstructorFromFunctionPointer()
{
  AlphaFunction alpha( &customAlphaFunction );

  //Check that the custom function points to the custom alpha function
  DALI_CHECK_FAIL( alpha.GetCustomFunction() != (&customAlphaFunction), "Failed to get Custom Function");

  //Check the mode is CUSTOM_FUNCTION
  DALI_CHECK_FAIL( alpha.GetMode() != AlphaFunction::CUSTOM_FUNCTION, "Invalid Mode for Function");

  DaliLog::PrintPass();
}
