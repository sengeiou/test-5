#include "utc-dali-animation-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/** Global Variables*/
Animation gAnimation;
Actor gActorAnim;
Path gPathAnim;
int gRenderCountAnim;
float gPlayFrom(0.0f);
float gPlayTo(1.0f);
float gSetProgress(0.3f);
float gFloatAnimDefaultStart =10.0f;
float gFloatAnimDefaultTarget = 50.0f;
int gIntAnimDefaultStart = 10;
int gIntAnimDefaultTarget = 50;
bool gBoolAnimStart(false);
Vector3 gVec3Progress;
Vector3 gVec3ProgressNext;
Vector3 gVec3TargetPosition(10.0f, 10.0f, 10.0f);
Property::Index gAnimPropertyIndex;
const bool gBoolAnimRelativeValue(true);
const float ANIM_SPEED_FACTOR(0.5f);


/******************************
 * TC Logic Area Starts Here
 * ****************************
 */

void AnimationSetGetSpeedFactorP()
{
  Stage stage;
  DALI_CHECK_FAIL(!AnimationActorInit(gActorAnim,gAnimation ,stage), "Animation actor and stage initialization failed.");

  gActorAnim.SetPosition(Vector3::ZERO);
  gAnimation.AnimateTo(Property(gActorAnim, Actor::Property::POSITION), gVec3TargetPosition, AlphaFunction::LINEAR);

  gAnimation.SetSpeedFactor(ANIM_SPEED_FACTOR);
  gAnimation.Play();
}
void VTAnimationSetGetSpeedFactor001()
{
  float fGetSpeedFactor = gAnimation.GetSpeedFactor();

  DALI_CHECK_FAIL(fGetSpeedFactor != ANIM_SPEED_FACTOR, "Animation SetSpeedFactor is not matched with GetSpeedFactor.");
  gAnimation.Stop();
  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}

void AnimationSetGetCurrentProgressP()
{
  Vector3 vec3targetPosition(100.0f, 100.0f, 100.0f);

  Stage stage;
  DALI_CHECK_FAIL(!AnimationActorInit(gActorAnim,gAnimation ,stage), "Animation actor and stage initialization failed.");

  gAnimation.SetDuration(gFloatAnimationSetDuration);
  gActorAnim.SetPosition(Vector3::ZERO);

  gAnimation.AnimateTo(Property(gActorAnim, Actor::Property::POSITION), vec3targetPosition, AlphaFunction::LINEAR);
  gAnimation.SetCurrentProgress(gSetProgress);
  gAnimation.Play();
}

void VTAnimationSetGetCurrentProgress001()
{
  float fGetCurrentProgress(0.0f);
  fGetCurrentProgress = gAnimation.GetCurrentProgress();

  if( fGetCurrentProgress <= gSetProgress )
  {
    LOG_E("GetCurrentProgress should be at least greater than SetCurrentProgress");
    test_return_value = TC_FAIL;
    return;
  }
  else
  {
    //@note: tick interval is 500ms = 500ms/1000 = 0.5s; anim duration is 1.0s;
    //So, progress due to one tick expected 50%;
    //So, overall expected progress after one tick interval = anim duration - tick duration + set current progress
    // overall progress may range from (expectedProgress -0.1f) to expectedProgress
    float fExpectedExactProgress = gFloatAnimationSetDuration - ((float)INTERVAL)/1000.0f + gSetProgress;
    if( fabsf(fGetCurrentProgress - fExpectedExactProgress) <= ANIMATION_EPSILON )
    {
      LOG_I("GetCurrentProgress is found almost exactly as expected.");
    }
    else if ( fabsf( fGetCurrentProgress - fExpectedExactProgress ) <= 0.2 )
    {
      LOG_I("GetCurrentProgress is found near to the expected exact progress value.");
    }
    else
    {
      LOG_E("GetCurrentProgress is not found properly.");
      test_return_value = TC_FAIL;
      return;
    }
  }

  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}

void AnimationSetGetPlayRangeP()
{
  gFloatAnimationSetDuration = 0.3f;
  gPlayFrom = 0.2f, gPlayTo = 0.8f;

  Stage stage;
  if(!AnimationActorInit(gActorAnim,gAnimation ,stage))
  {
    test_return_value = TC_FAIL;
    return;
  }

  gAnimation.SetDuration(gFloatAnimationSetDuration);
  gAnimation.SetPlayRange(Vector2( gPlayFrom, gPlayTo ));

  gAnimation.AnimateTo(Property(gActorAnim, Actor::Property::POSITION), gVec3TargetPosition, AlphaFunction::LINEAR);
  gAnimation.Play();
}
void VTAnimationSetGetPlayRange001()
{
  Vector2 vec2GetPlayRange = gAnimation.GetPlayRange();
  //Check whether PlayRange has been changed or not
  DALI_CHECK_FAIL((vec2GetPlayRange.x != gPlayFrom ) || (vec2GetPlayRange.y != gPlayTo), "Animation GetPlayRange is not matched with SetPlayRange.");
  DALI_CHECK_FAIL( gActorAnim.GetCurrentPosition() != gVec3TargetPosition*gPlayTo, "Failed to get expected target position satisfying the range.");

  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);

  DaliLog::PrintPass();
}

void AnimationSetGetDisconnectActionCommonInitP()
{
  gBoolSignalReceived = false;
  Stage stage;
  if(!AnimationActorInit(gActorAnim, gAnimation ,stage))
  {
    test_return_value = TC_FAIL;
    return;
  }
  gActorAnim.SetPosition(Vector3::ONE);
}

void VTAnimationSetGetDisconnectActionBake001()
{
  DALI_CHECK_FAIL(gActorAnim.GetCurrentPosition() != Vector3::ONE, "Failed to set an initial position of actor.");
  //Animation::Bake
  gAnimation.SetDisconnectAction( Animation::Bake );
  gAnimation.AnimateTo(Property(gActorAnim, Actor::Property::POSITION), gVec3TargetPosition, AlphaFunction::EASE_IN);
  gAnimation.Play();
}
void VTAnimationSetGetDisconnectActionBake002()
{
  Animation::EndAction eGetEndActiontype = gAnimation.GetDisconnectAction();
  DALI_CHECK_FAIL(eGetEndActiontype != Animation::Bake,
      "Animation GetDisconnectAction is not matched with SetDisconnectAction for Animation::Bake");

  gVec3Progress = gActorAnim.GetCurrentPosition();
  bool bCheckValue = (gVec3Progress.x > (Vector3::ONE).x && gVec3Progress.x < gVec3TargetPosition.x) &&
    (gVec3Progress.y > (Vector3::ONE).y && gVec3Progress.y < gVec3TargetPosition.y) &&
    (gVec3Progress.z > (Vector3::ONE).z && gVec3Progress.z < gVec3TargetPosition.z);

  DALI_CHECK_FAIL(!bCheckValue, "Animation is not in progress.");
  gActorAnim.Unparent();
}
void VTAnimationSetGetDisconnectActionBake003()
{
  Vector3 position = gActorAnim.GetCurrentPosition();
  bool bCheckValue = (position.x >= gVec3Progress.x && gVec3Progress.x < gVec3TargetPosition.x) &&
                     (position.y >= gVec3Progress.y && gVec3Progress.y < gVec3TargetPosition.y) &&
                     (position.z >= gVec3Progress.z && gVec3Progress.z < gVec3TargetPosition.z);
  DALI_CHECK_FAIL( !bCheckValue, "Disconnect action for Animation::Bake is failed; could not get expected position after unparenting.");
  gAnimation.Clear();
  DaliLog::PrintPass();
}

void VTAnimationSetGetDisconnectActionBakeFinal001()
{
  DALI_CHECK_FAIL(gActorAnim.GetCurrentPosition() != Vector3::ONE, "Failed to set an initial position of actor.");
  //Animation::Bake
  gAnimation.SetDisconnectAction( Animation::BakeFinal );
  gAnimation.AnimateTo(Property(gActorAnim, Actor::Property::POSITION), gVec3TargetPosition, AlphaFunction::LINEAR);
  gAnimation.Play();
}
void VTAnimationSetGetDisconnectActionBakeFinal002()
{
  Animation::EndAction eGetEndActiontype = gAnimation.GetDisconnectAction();
  DALI_CHECK_FAIL(eGetEndActiontype != Animation::BakeFinal,
      "Animation GetDisconnectAction is not matched with SetDisconnectAction for Animation::BakeFinal");

  gVec3Progress = gActorAnim.GetCurrentPosition();
  bool bCheckValue = (gVec3Progress.x > (Vector3::ONE).x && gVec3Progress.x < gVec3TargetPosition.x) &&
    (gVec3Progress.y > (Vector3::ONE).y && gVec3Progress.y < gVec3TargetPosition.y) &&
    (gVec3Progress.z > (Vector3::ONE).z && gVec3Progress.z < gVec3TargetPosition.z);

  DALI_CHECK_FAIL(!bCheckValue, "Animation is not in progress.");
  gActorAnim.Unparent();
}
void VTAnimationSetGetDisconnectActionBakeFinal003()
{
  DALI_CHECK_FAIL( gActorAnim.GetCurrentPosition() != gVec3TargetPosition,
      "Disconnect action for Animation::BakeFinal is failed; could not get expected target position after unparenting.");
  gAnimation.Clear();
  DaliLog::PrintPass();
}

void VTAnimationSetGetDisconnectActionDiscard001()
{
  DALI_CHECK_FAIL(gActorAnim.GetCurrentPosition() != Vector3::ONE, "Failed to set an initial position of actor.");
  //Animation::Bake
  gAnimation.SetDisconnectAction( Animation::Discard );
  gAnimation.AnimateTo(Property(gActorAnim, Actor::Property::POSITION), gVec3TargetPosition, AlphaFunction::LINEAR);
  gAnimation.Play();
}
void VTAnimationSetGetDisconnectActionDiscard002()
{
  Animation::EndAction eGetEndActiontype = gAnimation.GetDisconnectAction();
  DALI_CHECK_FAIL(eGetEndActiontype != Animation::Discard,
      "Animation GetDisconnectAction is not matched with SetDisconnectAction for Animation::Discard");

  gVec3Progress = gActorAnim.GetCurrentPosition();
  bool bCheckValue = (gVec3Progress.x > (Vector3::ONE).x && gVec3Progress.x < gVec3TargetPosition.x) &&
    (gVec3Progress.y > (Vector3::ONE).y && gVec3Progress.y < gVec3TargetPosition.y) &&
    (gVec3Progress.z > (Vector3::ONE).z && gVec3Progress.z < gVec3TargetPosition.z);

  DALI_CHECK_FAIL(!bCheckValue, "Animation is not in progress.");
  gActorAnim.Unparent();
}
void VTAnimationSetGetDisconnectActionDiscard003()
{
  DALI_CHECK_FAIL( gActorAnim.GetCurrentPosition() != Vector3::ONE,
      "Disconnect action for Animation::Discard is failed; could not get expected initial position after unparenting.");
  gAnimation.Clear();
  DaliLog::PrintPass();
}

void AnimationPlayFromP()
{
  float fStartPos(0.0f);
  Stage stage;

  if(!AnimationActorInit(gActorAnim ,gAnimation ,stage))
  {
    test_return_value = TC_FAIL;
    return;
  }

  gAnimation.SetDuration(gFloatAnimationSetDuration);
  gAnimation.FinishedSignal().Connect(&CbAnimationFinishCheck);
  gActorAnim.SetPosition(Vector3::ZERO);

  gAnimation.AnimateTo(Property(gActorAnim, Actor::Property::POSITION), Vector3(100.0f, 100.0f, 100.0f), AlphaFunction::LINEAR);

  gAnimation.SetPlayRange(Vector2(gPlayFrom, gPlayTo));
  //check with outside the PlayRange, ignore case
  gPlayFrom = 1.1f;
  gAnimation.PlayFrom(gPlayFrom);

  float fGetProgress = gAnimation.GetCurrentProgress();
  DALI_CHECK_FAIL( fGetProgress > fStartPos, "Checked with outside the PlayRange, Progress = , outside the range[0,1], Play is not ignored.");

  //check with inside the PlayRange, pass case
  gPlayFrom = 0.2f;
  gAnimation.PlayFrom(gPlayFrom);
  gAnimation.Play();
}
void VTAnimationPlayFrom001()
{
  float fGetProgress = gAnimation.GetCurrentProgress();

  if( fGetProgress <= gPlayFrom )
  {
    LOG_E("GetCurrentProgress should be at least greater than SetCurrentProgress");
    test_return_value = TC_FAIL;
    return;
  }
  else
  {
    //@note: tick interval is 500ms = 500ms/1000 = 0.5s; anim duration is 1.0s;
    //So, progress due to one tick expected 50%;
    //So, overall expected progress after one tick interval = anim duration - tick duration + progress from where anim will play
    // overall progress may range from (expectedProgress -0.1f) to expectedProgress
    float fExpectedExactProgress = gFloatAnimationSetDuration - ((float)INTERVAL)/1000.0f + gPlayFrom;
    if( fabsf(fGetProgress - fExpectedExactProgress) <= ANIMATION_EPSILON )
    {
      LOG_I("GetCurrentProgress is found almost exactly as expected.");
    }
    else if ( (fGetProgress > (fExpectedExactProgress - 0.2f ) ) && (fGetProgress < fExpectedExactProgress ) )
    {
      LOG_I("GetCurrentProgress is found near to the expected exact progress value.");
    }
    else
    {
      LOG_E("GetCurrentProgress is not found properly.");
      test_return_value = TC_FAIL;
      return;
    }
  }
  DALI_CHECK_FAIL( (gAnimation.GetState() != Animation::PLAYING), "GetState() had Failed. ");
  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}

void AnimationSetGetEndActionWithBakeFinalP()
{
  gBoolSignalReceived = false;
  Animation::EndAction setEndActiontype = Animation::BakeFinal;
  Animation::EndAction getEndActiontype;

  gAnimation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL(!gAnimation, " Animation::New() is Failed.");

  gActorAnim = Actor::New();
  DALI_CHECK_FAIL(!gActorAnim, " Actor::New() is Failed.");
  Stage::GetCurrent().Add(gActorAnim);

  gAnimation.FinishedSignal().Connect( &CbAnimationFinishCheck );

  gAnimation.SetEndAction(setEndActiontype);
  getEndActiontype= gAnimation.GetEndAction();
  DALI_CHECK_FAIL(getEndActiontype!=setEndActiontype, " SetEndAction is mismatched with GetEndAction value.");

  gAnimation.AnimateTo(Property(gActorAnim, Actor::Property::POSITION), gVec3TargetPosition, AlphaFunction::LINEAR);
  gAnimation.Play();
}
void VTAnimationSetGetEndActionWithBakeFinal001()
{
  DALI_CHECK_FAIL( gBoolSignalReceived, " Animation is should not be finished before animation time. ");
  // Stop the animation early; animation time is set 1.0s, but only 0.5s is elapsed due to one tick
  gAnimation.Stop();
}
void VTAnimationSetGetEndActionWithBakeFinal002()
{
  DALI_CHECK_FAIL( !gBoolSignalReceived, " Animation is not finished.");
  //Target position is found due to bakefinal action after another update and render followed by second tick
  DALI_CHECK_FAIL(gActorAnim.GetCurrentPosition() != gVec3TargetPosition, "position is not match with expected position.");

  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}

void AnimationDowncastP()
{
  bool bIsLoop = true;
  bool bSetLoop= true;
  Animation animation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL(!animation, "Animation::New is Failed.");
  bIsLoop=animation.IsLooping();
  DALI_CHECK_FAIL(bIsLoop, "IsLooping is failed to get default value.");

  animation.SetLooping(bSetLoop);

  bIsLoop=animation.IsLooping();
  DALI_CHECK_FAIL(bIsLoop!=bSetLoop, "IsLooping is failed to get expected value.");
  BaseHandle baseObject(animation);
  DALI_CHECK_FAIL(!baseObject, "baseObject is empty.");

  Animation animationDowncast = Animation::DownCast(baseObject);

  DALI_CHECK_FAIL(!animationDowncast, " DownCast is Failed.");
  bIsLoop=animationDowncast.IsLooping();
  DALI_CHECK_FAIL(bIsLoop!=bSetLoop, " Downcast object is failed to match the value of  SetLooping of real object");

  DaliLog::PrintPass();
}

void AnimationDowncastN()
{
  BaseHandle unInitializedObject;

  Animation animation1 = Animation::DownCast( unInitializedObject );
  DALI_CHECK_FAIL(animation1, "DownCast is Failed." );

  Animation animation2 = DownCast< Animation >( unInitializedObject );
  DALI_CHECK_FAIL(animation2, "DownCast is Failed." );

  DaliLog::PrintPass();
}


void AnimationSetGetDurationP()
{
  float fZero = 0.0f;
  gFloatAnimationSetDuration = 0.3f;
  gBoolSignalReceived = false;
  gAnimation = Animation::New(fZero);
  DALI_CHECK_FAIL( !gAnimation, "Animation is not created." );

  gActorAnim = Actor::New();
  DALI_CHECK_FAIL( !gActorAnim, "Actor is not created." );
  Stage::GetCurrent().Add(gActorAnim);

  gAnimation.FinishedSignal().Connect(&CbAnimationFinishCheck);
  gAnimation.SetDuration(gFloatAnimationSetDuration);
  gAnimation.AnimateTo(Property(gActorAnim, Actor::Property::POSITION), gVec3TargetPosition, AlphaFunction::LINEAR);
  gAnimation.Play();
}
void VTAnimationSetGetDuration001()
{
  float fGetDuration = gAnimation.GetDuration();

  DALI_CHECK_FAIL( fGetDuration != gFloatAnimationSetDuration, " GetDuration is failed to match with SetDuration value.");
  DALI_CHECK_FAIL( !gBoolSignalReceived, "Animation is not finished after set duration");
  DALI_CHECK_FAIL(gVec3TargetPosition!=gActorAnim.GetCurrentPosition(), " Current position is not matched with target position.");

  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}

void AnimationSetGetLoopCountP()
{
  float fZero = 0.0f;
  int loopCount = 4;
  gBoolSignalReceived = false;
  gAnimation = Animation::New(fZero);
  DALI_CHECK_FAIL( !gAnimation, "Animation is not created." );

  gActorAnim = Actor::New();
  DALI_CHECK_FAIL( !gActorAnim, "Actor is not created." );
  Stage::GetCurrent().Add(gActorAnim);

  gAnimation.FinishedSignal().Connect(&CbAnimationFinishCheck);
  gAnimation.SetLoopCount(loopCount);
  gAnimation.AnimateTo(Property(gActorAnim, Actor::Property::POSITION), gVec3TargetPosition, AlphaFunction::LINEAR);

  DALI_CHECK_FAIL( (gAnimation.GetLoopCount() != loopCount), " GetLoopCount is failed to match with SetLoopCount value.");

  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}

void AnimationSetGetCurrentLoopP()
{
  float fZero = 0.0f;
  int loopCount = 4;
  gBoolSignalReceived = false;
  gAnimation = Animation::New(fZero);
  DALI_CHECK_FAIL( !gAnimation, "Animation is not created." );

  gActorAnim = Actor::New();
  DALI_CHECK_FAIL( !gActorAnim, "Actor is not created." );
  Stage::GetCurrent().Add(gActorAnim);

  gAnimation.FinishedSignal().Connect(&CbAnimationFinishCheck);
  gAnimation.SetLoopCount(loopCount);
  gAnimation.AnimateTo(Property(gActorAnim, Actor::Property::POSITION), gVec3TargetPosition, AlphaFunction::LINEAR);

  DALI_CHECK_FAIL( (gAnimation.GetCurrentLoop() == loopCount), " GetCurrentLoop is failed. ");

  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}

void AnimationHideIsVisibleP()
{
  gFloatAnimationSetDuration = 0.6f;
  gBoolSignalReceived = false;
  gAnimation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL(!gAnimation, "invalid animation object");

  gActorAnim = Actor::New();
  DALI_CHECK_FAIL(!gActorAnim, "invalid actor object");
  Stage::GetCurrent().Add(gActorAnim);
}
void VTAnimationHideIsVisible001()
{
  DALI_CHECK_FAIL( !gActorAnim.IsVisible(), " Actor hides unexpectedly.");
  gAnimation.FinishedSignal().Connect(&CbAnimationFinishCheck);

  //at 50% of anim time
  gAnimation.Hide(gActorAnim, gFloatAnimationSetDuration*0.5f);
  gAnimation.Play();
}
void VTAnimationHideIsVisible002()
{
  //Actor should be invisible here but signal will not trigger
  DALI_CHECK_FAIL(gActorAnim.IsVisible(), " Actor shows unexpectedly.");
  DALI_CHECK_FAIL( gBoolSignalReceived, "Signal is received unexpectedly.");
}
void VTAnimationHideIsVisible003()
{
  //Actor will remain invisible and signal will trigger
  DALI_CHECK_FAIL(gActorAnim.IsVisible(), " Actor shows unexpectedly.");
  DALI_CHECK_FAIL( !gBoolSignalReceived, "Signal is not received unexpectedly.");

  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}

void AnimationShowIsVisibleP()
{
  gFloatAnimationSetDuration = 0.8f;
  gBoolSignalReceived = false;
  gAnimation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL(!gAnimation, "invalid animation object");

  gActorAnim = Actor::New();
  DALI_CHECK_FAIL(!gActorAnim, "invalid actor object");
  Stage::GetCurrent().Add(gActorAnim);
  gActorAnim.SetVisible(false);
}
void VTAnimationShowIsVisible001()
{
  DALI_CHECK_FAIL(gActorAnim.IsVisible(), "Actor do not hide properly");
  gAnimation.FinishedSignal().Connect(&CbAnimationFinishCheck);

  //Setting actor to show at 50% of the animation duration
  gAnimation.Show(gActorAnim, gFloatAnimationSetDuration*0.5f);
  gAnimation.Play();
}
void VTAnimationShowIsVisible002()
{
  //Checking beyond 50% of animation time, finish signal will not be received but actor will be visible
  DALI_CHECK_FAIL( gBoolSignalReceived, "Animation should not be finished before animation time" );
  DALI_CHECK_FAIL( !gActorAnim.IsVisible(), "Actor is not visible after expected time.");
}
void VTAnimationShowIsVisible003()
{
  DALI_CHECK_FAIL( !gActorAnim.IsVisible(), "Actor is not visible finished beyond animation time");
  DALI_CHECK_FAIL( !gBoolSignalReceived, "Animation is not finished beyond animation time." )
    gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}


void AnimationSetGetEndActionWithBakeP()
{
  gBoolSignalReceived = false;
  gFloatAnimationSetDuration = 0.3f;
  Animation::EndAction setEndActiontype = Animation::Bake;
  Animation::EndAction getEndActiontype;

  gAnimation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL(!gAnimation, " Animation::New() is Failed.");

  gActorAnim = Actor::New();
  DALI_CHECK_FAIL(!gActorAnim, " Actor::New() is Failed.");
  Stage::GetCurrent().Add(gActorAnim);

  gAnimation.FinishedSignal().Connect( &CbAnimationFinishCheck );

  gAnimation.SetEndAction(setEndActiontype);
  getEndActiontype= gAnimation.GetEndAction();
  DALI_CHECK_FAIL(getEndActiontype!=setEndActiontype, " SetEndAction is mismatched with GetEndAction value.");

  gAnimation.AnimateTo(Property(gActorAnim, Actor::Property::POSITION), gVec3TargetPosition, AlphaFunction::LINEAR);
  gAnimation.Play();
}

void VTAnimationSetGetEndActionWithBake001()
{
  DALI_CHECK_FAIL( !gBoolSignalReceived, " Animation is not finished. ");
  DALI_CHECK_FAIL(gActorAnim.GetCurrentPosition() != gVec3TargetPosition, "Current position is not matched with target position..");

  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}

void AnimationSetGetEndActionWithDiscardP()
{
  gBoolSignalReceived = false;
  gFloatAnimationSetDuration = 0.6f;
  Animation::EndAction setEndActiontype = Animation::Discard;
  Animation::EndAction getEndActiontype;

  Stage stage;
  DALI_CHECK_FAIL(!AnimationActorInit(gActorAnim,gAnimation ,stage), "Animation actor and stage initialization failed.");

  gAnimation.FinishedSignal().Connect(&CbAnimationFinishCheck);
  gAnimation.SetEndAction(setEndActiontype);
  getEndActiontype = gAnimation.GetEndAction();
  DALI_CHECK_FAIL(getEndActiontype!=setEndActiontype, "SetEndAction is mismatched with GetEndAction value.");

  gAnimation.AnimateTo(Property(gActorAnim, Actor::Property::POSITION), gVec3TargetPosition, AlphaFunction::LINEAR);
  gAnimation.Play();
}
void AnimationSetGetEndActionWithDiscard001()
{
  // Finish signal will trigger before animation time is over
  DALI_CHECK_FAIL( gBoolSignalReceived, "Anination should not finished just at animation time." );
  gVec3Progress = gActorAnim.GetCurrentPosition();
  bool bIsInProgress = (gVec3Progress.x > 0.0f && gVec3Progress.x < gVec3TargetPosition.x) &&
    (gVec3Progress.y > 0.0f && gVec3Progress.y < gVec3TargetPosition.y) &&
    (gVec3Progress.z > 0.0f && gVec3Progress.z < gVec3TargetPosition.z);
  DALI_CHECK_FAIL( !bIsInProgress,
      "Animatin is not in progress; failed to update actor's position using Animation::Discard end action." );
}
void AnimationSetGetEndActionWithDiscard002()
{
  DALI_CHECK_FAIL( !gBoolSignalReceived, "Anination should finish here." );
  //Actor's property will be discarded due to discard action beyond the animation time
  DALI_CHECK_FAIL( gActorAnim.GetCurrentPosition() != Vector3::ZERO,
      "Failed to discard actor's property." );
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}

void AnimationSetGetDefaultAlphfunctionLinearP()
{
  Stage stage;
  gFloatAnimationSetDuration = 0.3f;
  if(!AnimationActorInit(gActorAnim, gAnimation, stage ))
  {
    test_return_value = TC_FAIL;
    return;
  }

  AlphaFunction getDefaultFunc = gAnimation.GetDefaultAlphaFunction();
  DALI_CHECK_FAIL(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::DEFAULT, "GetDefaultAlphaFunction is Failed to get Default Value .");

  AlphaFunction setAlphaFunction = AlphaFunction::LINEAR;
  gAnimation.SetDefaultAlphaFunction(setAlphaFunction);
  gAnimation.AnimateTo(Property(gActorAnim, Actor::Property::POSITION), gVec3TargetPosition );
  gAnimation.Play();
}
void VTAnimationSetGetDefaultAlphfunctionLinear001()
{
  AlphaFunction getDefaultFunc = gAnimation.GetDefaultAlphaFunction();
  DALI_CHECK_FAIL( getDefaultFunc.GetBuiltinFunction() != AlphaFunction::LINEAR, "GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction." );
  DALI_CHECK_FAIL( gActorAnim.GetCurrentPosition() != gVec3TargetPosition,
      "Failed to get target position after animation with linear alpha function." );
  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}

void AnimationSetGetDefaultAlphfunctionEaseInP()
{
  Stage stage;
  gFloatAnimationSetDuration = 0.3f;
  if(!AnimationActorInit(gActorAnim, gAnimation, stage ))
  {
    test_return_value = TC_FAIL;
    return;
  }

  AlphaFunction getDefaultFunc = gAnimation.GetDefaultAlphaFunction();
  DALI_CHECK_FAIL(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::DEFAULT, "GetDefaultAlphaFunction is Failed to get Default Value .");

  AlphaFunction setAlphaFunction = AlphaFunction::EASE_IN;
  gAnimation.SetDefaultAlphaFunction(setAlphaFunction);
  gAnimation.AnimateTo(Property(gActorAnim, Actor::Property::POSITION), gVec3TargetPosition );
  gAnimation.Play();
}
void VTAnimationSetGetDefaultAlphfunctionEaseIn001()
{
  AlphaFunction getDefaultFunc = gAnimation.GetDefaultAlphaFunction();
  DALI_CHECK_FAIL( getDefaultFunc.GetBuiltinFunction() != AlphaFunction::EASE_IN, "GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction." );
  DALI_CHECK_FAIL( gActorAnim.GetCurrentPosition() != gVec3TargetPosition,
      "Failed to get target position after animation with ease_in alpha function." );
  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}

void AnimationStopP()
{
  Stage stage;
  gBoolSignalReceived = false;
  DALI_CHECK_FAIL(!AnimationActorInit(gActorAnim,gAnimation ,stage), "Animation actor and stage initialization failed.");

  gAnimation.FinishedSignal().Connect( &CbAnimationFinishCheck );
  gAnimation.AnimateTo(Property(gActorAnim, Actor::Property::POSITION), gVec3TargetPosition, AlphaFunction::LINEAR);
  gAnimation.Play();
}
void VTAnimationStop001()
{
  // We didn't expect the animation to finish yet
  DALI_CHECK_FAIL( gBoolSignalReceived, "Animation should not be finished" );
  DALI_CHECK_FAIL(gActorAnim.GetCurrentPosition() == gVec3TargetPosition, "Target position should not be found before animation time .");
  // Stop the animation early
  gAnimation.Stop();
}
void VTAnimationStop002()
{
  //Animation is early stopped so, finish signal is connected but, target postion will not be found
  DALI_CHECK_FAIL( !gBoolSignalReceived, "Animation should be finished due to stop" );
  DALI_CHECK_FAIL(gActorAnim.GetCurrentPosition() == gVec3TargetPosition, "Target position should not be found due to early animation stop.");

  DALI_CHECK_FAIL( (gAnimation.GetState() != Animation::STOPPED), "GetState() had Failed. ");

  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}

void AnimationClearP()
{
  gBoolSignalReceived = false;

  Stage stage;
  DALI_CHECK_FAIL(!AnimationActorInit(gActorAnim,gAnimation ,stage), "Animation actor and stage initialization failed.");

  gAnimation.FinishedSignal().Connect(&CbAnimationFinishCheck);
  gAnimation.AnimateTo(Property(gActorAnim, Actor::Property::POSITION), gVec3TargetPosition, AlphaFunction::LINEAR);
  gAnimation.Play();
}
void VTAnimationClear001()
{
  DALI_CHECK_FAIL( gBoolSignalReceived, " Signal is  received which is not expected.");
  gVec3Progress = gActorAnim.GetCurrentPosition();
  bool bIsInProgress = (gVec3Progress.x > 0.0f && gVec3Progress.x < gVec3TargetPosition.x) &&
    (gVec3Progress.y > 0.0f && gVec3Progress.y < gVec3TargetPosition.y) &&
    (gVec3Progress.z > 0.0f && gVec3Progress.z < gVec3TargetPosition.z) ;

  DALI_CHECK_FAIL( !bIsInProgress, "Animatin is not in progress; failed to update actor's position." );
  // Clear the animation
  gAnimation.Clear();
}
void VTAnimationClear002()
{
  DALI_CHECK_FAIL( gBoolSignalReceived, " Signal is received which is unexpected after clear.");
  gVec3ProgressNext = gActorAnim.GetCurrentPosition();
  bool bIsInProgress = ( gVec3ProgressNext.x >= gVec3Progress.x && gVec3ProgressNext.x < gVec3TargetPosition.x ) &&
    ( gVec3ProgressNext.y >= gVec3Progress.y && gVec3ProgressNext.y < gVec3TargetPosition.y ) &&
    ( gVec3ProgressNext.z >= gVec3Progress.z && gVec3ProgressNext.z < gVec3TargetPosition.z ) ;

  DALI_CHECK_FAIL( !bIsInProgress,
      "Actor's property should be still within the progress value due to clearing the animation before animation time." );

  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}

void AnimationPauseP()
{
  gBoolSignalReceived = false;
  Stage stage;
  DALI_CHECK_FAIL(!AnimationActorInit(gActorAnim,gAnimation ,stage), "Animation actor and stage initialization failed.");

  gAnimation.SetDuration(1.1f);
  gAnimation.FinishedSignal().Connect(&CbAnimationFinishCheck);
  gAnimation.AnimateTo(Property(gActorAnim, Actor::Property::POSITION), gVec3TargetPosition, AlphaFunction::LINEAR);
  gAnimation.Play();
}
void VTAnimationPause001()
{
  DALI_CHECK_FAIL( gBoolSignalReceived, " Signal is  received which is not expected.");

  gVec3Progress = gActorAnim.GetCurrentPosition();
  bool bIsInProgress = (gVec3Progress.x > 0.0f && gVec3Progress.x < gVec3TargetPosition.x) &&
    (gVec3Progress.y > 0.0f && gVec3Progress.y < gVec3TargetPosition.y) &&
    (gVec3Progress.z > 0.0f && gVec3Progress.z < gVec3TargetPosition.z);
  DALI_CHECK_FAIL( !bIsInProgress, "Animatin is not in progress; failed to update actor's position." );
  // Pause the animation
  gAnimation.Pause();
}
void VTAnimationPause002()
{
  DALI_CHECK_FAIL( (gAnimation.GetState() != Animation::PAUSED), "GetState() had Failed. ");

  DALI_CHECK_FAIL( gBoolSignalReceived, " Signal is  received which is not expected.");
  DALI_CHECK_FAIL( gVec3Progress != gActorAnim.GetCurrentPosition(), "Animation is not paused properly.");
  gAnimation.Play();
}
void VTAnimationPause003()
{
  DALI_CHECK_FAIL( gBoolSignalReceived, " Signal is  received which is not expected.");
  Vector3 vec3Progress = gActorAnim.GetCurrentPosition();
  bool bIsInProgress = (vec3Progress.x > gVec3Progress.x && vec3Progress.x < gVec3TargetPosition.x) &&
    (vec3Progress.y > gVec3Progress.y && vec3Progress.y < gVec3TargetPosition.y) &&
    (vec3Progress.z > gVec3Progress.z && vec3Progress.z < gVec3TargetPosition.z);

  DALI_CHECK_FAIL( !bIsInProgress, "Animatin is failed to play again after pause." );
}
void VTAnimationPause004()
{
  DALI_CHECK_FAIL( !gBoolSignalReceived, " Signal is not received which is unexpected.");
  DALI_CHECK_FAIL( gActorAnim.GetCurrentPosition() != gVec3TargetPosition, "Failed to get arget position after animation." );
  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}

void AnimationConstructorP()
{
  Animation animation;
  DALI_CHECK_FAIL(animation, "Animation::New() is Failed..");

  DaliLog::PrintPass();
}

void AnimationNewP()
{
  Animation animation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL(!animation, "Animation::New() is Failed..");

  DaliLog::PrintPass();
}

void AnimationNewN()
{
  Animation animation = Animation::New(-1.0f);
  DALI_CHECK_FAIL(!animation, "Animation::New() is Failed..");
  DALI_CHECK_FAIL((animation.GetDuration() != 0.0f), "GetDuration for animation failed.");

  DaliLog::PrintPass();
}

void AnimationSetIsLoopingP()
{
  bool bIsLoop = true;
  bool bSetLoop= true;
  Animation animation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL(!animation, "Animation::New() is Failed..");
  bIsLoop=animation.IsLooping();
  DALI_CHECK_FAIL(bIsLoop, "IsLooping is Failed  to get default value.");

  animation.SetLooping(bSetLoop);

  bIsLoop=animation.IsLooping();
  DALI_CHECK_FAIL(bIsLoop!=bSetLoop, "SetLooping is mismatched with IsLooping value.");

  bSetLoop = false;
  animation.SetLooping(bSetLoop);

  bIsLoop=animation.IsLooping();
  DALI_CHECK_FAIL(bIsLoop!=bSetLoop, "SetLooping is mismatched with IsLooping value.");

  DaliLog::PrintPass();
}

void AnimationCopyConstructorP()
{
  bool bIsLoop = true;
  bool bSetLoop= true;
  Animation animation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL(!animation, "Animation::New() is Failed..");
  bIsLoop=animation.IsLooping();
  DALI_CHECK_FAIL(bIsLoop, "IsLooping is Failed  to get default value.");

  animation.SetLooping(bSetLoop);

  bIsLoop=animation.IsLooping();
  DALI_CHECK_FAIL(bIsLoop!=bSetLoop, "SetLooping is mismatched with IsLooping value.");
  Animation animationCopyConst(animation);

  DALI_CHECK_FAIL(!animationCopyConst, "Copy Constructor  object is failed .");
  bIsLoop=animationCopyConst.IsLooping();
  DALI_CHECK_FAIL(bIsLoop!=bSetLoop, "Copy Constructor  object is failed to match the value of  SetLooping of real object.");

  DaliLog::PrintPass();
}

void AnimationOperatorAssignMentP()
{
  bool bIsLoop = true;
  bool bSetLoop= true;
  Animation animation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL(!animation, "Animation::New() is Failed..");
  bIsLoop=animation.IsLooping();
  DALI_CHECK_FAIL(bIsLoop, "IsLooping is Failed  to get default value..");

  animation.SetLooping(bSetLoop);

  bIsLoop=animation.IsLooping();
  DALI_CHECK_FAIL(bIsLoop!=bSetLoop, "SetLooping is mismatched with IsLooping value.");

  Animation animationAssigned = animation ;

  DALI_CHECK_FAIL(!animationAssigned, "assignment is Failed.");
  bIsLoop=animationAssigned.IsLooping();
  DALI_CHECK_FAIL(bIsLoop!=bSetLoop, "Assigned  object is failed to match the value of  SetLooping of real object .");

  DaliLog::PrintPass();
}


void AnimationAnimateByBoolP()
{
  if(!ActorAnimatePropInit(gActorAnim, gBoolAnimStart ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateByTemplate (gActorAnim, gAnimation, gBoolAnimRelativeValue, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}
void VTAnimationAnimateByBool001()
{
  const bool bFinalValue( false || gBoolAnimRelativeValue );
  if(!AnimationAnimateByTemplateCheck(gActorAnim, gAnimation, bFinalValue, gAnimPropertyIndex ) )
  {
    test_return_value = TC_FAIL;
    return;
  }
  DaliLog::PrintPass();
}

void AnimationAnimateByFloatP()
{
  float fRelativeValue(gFloatAnimDefaultTarget - gFloatAnimDefaultStart);

  if(!ActorAnimatePropInit(gActorAnim, gFloatAnimDefaultStart ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateByTemplate (gActorAnim, gAnimation, fRelativeValue, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}

void AnimationAnimateByFloatTimePeriodP()
{
  float fRelativeValue(gFloatAnimDefaultTarget - gFloatAnimDefaultStart);

  if(!ActorAnimatePropInit(gActorAnim, gFloatAnimDefaultStart ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateByTimePeriod (gActorAnim, gAnimation, fRelativeValue, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}

void AnimationAnimateToFloatTimePeriodAlphaFunctionP()
{
  if(!ActorAnimatePropInit(gActorAnim, gFloatAnimDefaultStart ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateToTimePeriodAlphaFunction (gActorAnim, gAnimation, gFloatAnimDefaultTarget, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}

void AnimationAnimateToFloatP()
{
  if(!ActorAnimatePropInit(gActorAnim, gFloatAnimDefaultStart ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateToDiffProperty(gActorAnim, gAnimation, gFloatAnimDefaultTarget, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}

void AnimationAnimateToFloatTimePeriodP()
{
  if(!ActorAnimatePropInit(gActorAnim, gFloatAnimDefaultStart ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateToTimePeriod(gActorAnim, gAnimation, gFloatAnimDefaultTarget, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}


void VTAnimationAnimateCheckFloat001()
{
  if(!AnimationAnimateByTemplateCheck(gActorAnim, gAnimation, gFloatAnimDefaultTarget, gAnimPropertyIndex ) )
  {
    test_return_value = TC_FAIL;
    return;
  }
  DaliLog::PrintPass();
}

void AnimationAnimatePathTimePeriodAlphaFunctionP()
{
  gSetProgress = 1.0f;
  gFloatAnimationSetDuration = 0.3f;
  TimePeriod timePeriod(0.0f, 0.3f);

  gAnimation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL(!gAnimation, "Animation::New is failed .");

  gActorAnim = Actor::New();
  DALI_CHECK_FAIL(!gActorAnim, "Actor::New is failed .");

  //Build the path
  Vector3 positionStart( 30.0,  80.0,  0.0);
  Vector3 positionMid( 70.0,  120.0, 0.0);
  Vector3 positionEnd( 100.0, 100.0, 0.0);

  gPathAnim = Path::New();
  DALI_CHECK_FAIL(!gPathAnim, "Path::New is failed .");

  gPathAnim.AddPoint(positionStart);
  gPathAnim.AddPoint(positionMid);
  gPathAnim.AddPoint(positionEnd);

  //Control points for first segment
  gPathAnim.AddControlPoint( Vector3( 39.0,  90.0, 0.0) );
  gPathAnim.AddControlPoint(Vector3( 56.0, 119.0, 0.0) );

  //Control points for second segment
  gPathAnim.AddControlPoint(Vector3( 78.0, 120.0, 0.0));
  gPathAnim.AddControlPoint(Vector3( 93.0, 104.0, 0.0));

  Stage::GetCurrent().Add(gActorAnim);

  gAnimation.Animate(gActorAnim, gPathAnim, Vector3::XAXIS, AlphaFunction::LINEAR , timePeriod );
  gAnimation.Play();
}
void VTAnimationAnimatePathTimePeriodAlphaFunction001()
{
  Vector3 vec3Position, vec3Tangent;
  Quaternion quatRotation;

  //at 100% progress
  gPathAnim.Sample( gSetProgress, vec3Position, vec3Tangent );
  quatRotation = Quaternion( Vector3::XAXIS, vec3Tangent );

  DALI_CHECK_FAIL( gActorAnim.GetCurrentPosition() != vec3Position, "Animate api is not working properly" );
  DALI_CHECK_FAIL( gActorAnim.GetCurrentOrientation() !=  quatRotation, "Animate api is not working properly" );

  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}

void AnimationAnimateByIntegerP()
{
  int nRelativeValue(gIntAnimDefaultTarget - gIntAnimDefaultStart);

  if(!ActorAnimatePropInit(gActorAnim, gIntAnimDefaultStart ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateByTemplate (gActorAnim, gAnimation, nRelativeValue, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}
void VTAnimationAnimateByInteger001()
{
  if(!AnimationAnimateByTemplateCheck(gActorAnim, gAnimation, gIntAnimDefaultTarget, gAnimPropertyIndex ) )
  {
    test_return_value = TC_FAIL;
    return;
  }
  DaliLog::PrintPass();
}

void AnimationAnimateByVector2P()
{
  Vector2 vec2StartValue(gFloatAnimDefaultStart, gFloatAnimDefaultStart);
  Vector2 vec2TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget);
  Vector2 vec2RelativeValue(vec2TargetValue - vec2StartValue);

  if(!ActorAnimatePropInit(gActorAnim, vec2StartValue ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateByTemplate (gActorAnim, gAnimation, vec2RelativeValue, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}

void AnimationAnimateByVector2TimePeriodP()
{
  Vector2 vec2StartValue(gFloatAnimDefaultStart, gFloatAnimDefaultStart);
  Vector2 vec2TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget);
  Vector2 vec2RelativeValue(vec2TargetValue - vec2StartValue);

  if(!ActorAnimatePropInit(gActorAnim, vec2StartValue ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateByTimePeriod (gActorAnim, gAnimation, vec2RelativeValue, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}

void AnimationAnimateToVector2TimePeriodAlphaFunctionP()
{
  Vector2 vec2StartValue(gFloatAnimDefaultStart, gFloatAnimDefaultStart);
  Vector2 vec2TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget);

  if(!ActorAnimatePropInit(gActorAnim, vec2StartValue ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateToTimePeriodAlphaFunction (gActorAnim, gAnimation, vec2TargetValue, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}

void AnimationAnimateToP()
{
  gFloatAnimationSetDuration = 0.3f;
  Vector3 vec3StartValue(gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart);
  Vector3 vec3TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget);
  TimePeriod timePeriod (gFloatAnimationDelay, gFloatAnimationSetDuration - gFloatAnimationDelay);

  gAnimation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL( !gAnimation, "Failed to create animation instance." );

  if(!ActorAnimatePropInit(gActorAnim, vec3StartValue ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
  Stage::GetCurrent().Add(gActorAnim);

  gAnimation.FinishedSignal().Connect(&CbAnimationFinishCheck);

  gAnimation.AnimateTo(Property(gActorAnim, gAnimPropertyIndex), vec3TargetValue, AlphaFunction::EASE_OUT);
  gAnimation.Play();

  gAnimation.AnimateTo(Property(gActorAnim, gAnimPropertyIndex), vec3TargetValue, AlphaFunction::EASE_OUT, timePeriod);
  gAnimation.Play();

  gAnimation.AnimateTo(Property(gActorAnim, gAnimPropertyIndex), vec3TargetValue, timePeriod);
  gAnimation.Play();
}

void AnimationAnimateToVector2P()
{
  Vector2 vec2StartValue(gFloatAnimDefaultStart, gFloatAnimDefaultStart);
  Vector2 vec2TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget);

  if(!ActorAnimatePropInit(gActorAnim, vec2StartValue ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateToDiffProperty (gActorAnim, gAnimation, vec2TargetValue, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}

void AnimationAnimateToVector2TimePeriodP()
{
  Vector2 vec2StartValue(gFloatAnimDefaultStart, gFloatAnimDefaultStart);
  Vector2 vec2TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget);

  if(!ActorAnimatePropInit(gActorAnim, vec2StartValue ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateToTimePeriod (gActorAnim, gAnimation, vec2TargetValue, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}

void VTAnimationAnimateCheckVector2()
{
  Vector2 vec2TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget); /**Checking with set target*/
  if(!AnimationAnimateByTemplateCheck(gActorAnim, gAnimation, vec2TargetValue, gAnimPropertyIndex ) )
  {
    test_return_value = TC_FAIL;
    return;
  }
  DaliLog::PrintPass();
}

void AnimationAnimateByVector3P()
{
  Vector3 vec3StartValue(gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart);
  Vector3 vec3TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget);
  Vector3 vec3RelativeValue(vec3TargetValue - vec3StartValue);

  if(!ActorAnimatePropInit(gActorAnim, vec3StartValue ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateByTemplate (gActorAnim, gAnimation, vec3RelativeValue, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}


void AnimationAnimateByVector3TimePeriodP()
{
  Vector3 vec3StartValue(gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart);
  Vector3 vec3TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget);
  Vector3 vec3RelativeValue(vec3TargetValue - vec3StartValue);

  if(!ActorAnimatePropInit(gActorAnim, vec3StartValue ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateByTimePeriod (gActorAnim, gAnimation, vec3RelativeValue, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}


void AnimationAnimateToVector3TimePeriodAlphaFunctionP()
{
  Vector3 vec3StartValue(gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart);
  Vector3 vec3TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget);

  if(!ActorAnimatePropInit(gActorAnim, vec3StartValue ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateToTimePeriodAlphaFunction (gActorAnim, gAnimation, vec3TargetValue, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}

void AnimationAnimateToVector3P()
{
  Vector3 vec3StartValue(gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart);
  Vector3 vec3TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget);

  if(!ActorAnimatePropInit(gActorAnim, vec3StartValue ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateToDiffProperty (gActorAnim, gAnimation, vec3TargetValue, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}


void AnimationAnimateToVector3TimePeriodP()
{
  Vector3 vec3StartValue(gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart);
  Vector3 vec3TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget);

  if(!ActorAnimatePropInit(gActorAnim, vec3StartValue ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateToTimePeriod (gActorAnim, gAnimation, vec3TargetValue, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}

void AnimationAnimateToVector3AlphaFunctionP()
{
  gFloatAnimationSetDuration = 0.3f;
  TimePeriod timePeriod (gFloatAnimationDelay, gFloatAnimationSetDuration - gFloatAnimationDelay);
  Vector3 vec3StartValue(gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart);
  Vector3 vec3TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget);

  gAnimation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL( !gAnimation, "Failed to create animation instance." );

  if(!ActorAnimatePropInit(gActorAnim, vec3StartValue ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
  Stage::GetCurrent().Add(gActorAnim);

  gAnimation.FinishedSignal().Connect(&CbAnimationFinishCheck);
  gAnimation.AnimateTo(Property(gActorAnim, gAnimPropertyIndex), vec3TargetValue, AlphaFunction::EASE_OUT);
  gAnimation.Play();

  gAnimation.AnimateTo(Property(gActorAnim, gAnimPropertyIndex), vec3TargetValue, AlphaFunction::EASE_OUT, timePeriod );
  gAnimation.Play();

  gAnimation.AnimateTo(Property(gActorAnim, gAnimPropertyIndex), vec3TargetValue, timePeriod );
  gAnimation.Play();
}

void VTAnimationAnimateCheckVector3()
{
  Vector3 vec3TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget); /**Checking with set target*/
  if(!AnimationAnimateByTemplateCheck(gActorAnim, gAnimation, vec3TargetValue, gAnimPropertyIndex ) )
  {
    test_return_value = TC_FAIL;
    return;
  }
  DaliLog::PrintPass();
}

void AnimationAnimateByVector4P()
{
  Vector4 vec4StartValue(gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart);
  Vector4 vec4TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget);
  Vector4 vec4RelativeValue(vec4TargetValue - vec4StartValue);

  if(!ActorAnimatePropInit(gActorAnim, vec4StartValue ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateByTemplate (gActorAnim, gAnimation, vec4RelativeValue, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}

void AnimationAnimateByVector4TimePeriodP()
{
  Vector4 vec4StartValue(gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart);
  Vector4 vec4TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget);
  Vector4 vec4RelativeValue(vec4TargetValue - vec4StartValue);

  if(!ActorAnimatePropInit(gActorAnim, vec4StartValue ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateByTimePeriod (gActorAnim, gAnimation, vec4RelativeValue, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}

void AnimationAnimateToVector4TimePeriodAlphaFunctionP()
{
  Vector4 vec4StartValue(gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart);
  Vector4 vec4TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget);

  if(!ActorAnimatePropInit(gActorAnim, vec4StartValue ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateToTimePeriodAlphaFunction (gActorAnim, gAnimation, vec4TargetValue, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}

void AnimationAnimateToVector4P()
{
  Vector4 vec4StartValue(gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart);
  Vector4 vec4TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget);

  if(!ActorAnimatePropInit(gActorAnim, vec4StartValue ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateToDiffProperty (gActorAnim, gAnimation, vec4TargetValue, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}


void AnimationAnimateToVector4TimePeriodP()
{
  Vector4 vec4StartValue(gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart);
  Vector4 vec4TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget);

  if(!ActorAnimatePropInit(gActorAnim, vec4StartValue ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }

  if(!AnimationAnimateToTimePeriod (gActorAnim, gAnimation, vec4TargetValue, gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
}


void AnimationAnimateByVector4TimePeriodAlphaFunctionP()
{
  gFloatAnimationSetDuration = 0.6f;
  TimePeriod timePeriod (gFloatAnimationDelay, gFloatAnimationSetDuration - gFloatAnimationDelay);
  Vector4 vec4StartValue(gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart);
  Vector4 vec4TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget);
  Vector4 vec4RelativeValue(vec4TargetValue - vec4StartValue);

  gAnimation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL( !gAnimation, "Failed to create animation instance." );

  if(!ActorAnimatePropInit(gActorAnim, vec4StartValue ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
  Stage::GetCurrent().Add(gActorAnim);

  gAnimation.FinishedSignal().Connect(&CbAnimationFinishCheck);
  gAnimation.AnimateBy(Property(gActorAnim, gAnimPropertyIndex), vec4RelativeValue ,ALPHA_FUNCTION, timePeriod);
  gAnimation.Play();
}

void AnimationAnimateByVector4AlphaFunctionP()
{
  gFloatAnimationSetDuration = 0.3f;
  AlphaFunction setAlphaFunction =  AlphaFunction::EASE_OUT;
  Vector4 vec4StartValue(gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart, gFloatAnimDefaultStart);
  Vector4 vec4TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget);
  Vector4 vec4RelativeValue(vec4TargetValue - vec4StartValue);

  gAnimation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL( !gAnimation, "Failed to create animation instance." );

  if(!ActorAnimatePropInit(gActorAnim, vec4StartValue ,gAnimPropertyIndex))
  {
    test_return_value = TC_FAIL;
    return;
  }
  Stage::GetCurrent().Add(gActorAnim);

  gAnimation.FinishedSignal().Connect(&CbAnimationFinishCheck);
  gAnimation.AnimateBy(Property(gActorAnim, gAnimPropertyIndex), vec4RelativeValue, setAlphaFunction);
  gAnimation.Play();
}

void VTAnimationAnimateCheckVector4()
{
  Vector4 vec4TargetValue(gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget, gFloatAnimDefaultTarget); /**Checking with set target*/
  if(!AnimationAnimateByTemplateCheck(gActorAnim, gAnimation, vec4TargetValue, gAnimPropertyIndex ) )
  {
    test_return_value = TC_FAIL;
    return;
  }
  DaliLog::PrintPass();
}

void AnimationAnimatePathVectorP()
{
  gSetProgress = 1.0f;
  gFloatAnimationSetDuration = 0.3f;

  gAnimation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL(!gAnimation, "Animation::New is failed .");

  gActorAnim = Actor::New();
  DALI_CHECK_FAIL(!gActorAnim, "Actor::New is failed .");

  //Build the path
  Vector3 positionStart( 30.0f,  80.0f,  0.0f);
  Vector3 positionMid( 70.0f,  120.0f, 0.0f);
  Vector3 positionEnd( 100.0f, 100.0f, 0.0f);

  gPathAnim = Path::New();
  DALI_CHECK_FAIL(!gPathAnim, "Path::New is failed .");

  gPathAnim.AddPoint(positionStart);
  gPathAnim.AddPoint(positionMid);
  gPathAnim.AddPoint(positionEnd);

  //Control points for first segment
  gPathAnim.AddControlPoint( Vector3( 39.0f,  90.0f, 0.0f) );
  gPathAnim.AddControlPoint(Vector3( 56.0f, 119.0f, 0.0f) );

  //Control points for second segment
  gPathAnim.AddControlPoint(Vector3( 78.0f, 120.0f, 0.0f));
  gPathAnim.AddControlPoint(Vector3( 93.0f, 104.0f, 0.0f));

  Stage::GetCurrent().Add(gActorAnim);

  gAnimation.Animate(gActorAnim, gPathAnim, Vector3::XAXIS);
  gAnimation.Play();
}
void VTAnimationAnimatePathVector001()
{
  Vector3 vec3Position, vec3Tangent;
  Quaternion quatRotation;

  //at 100% progress
  gPathAnim.Sample( gSetProgress, vec3Position, vec3Tangent );
  quatRotation = Quaternion( Vector3::XAXIS, vec3Tangent );

  DALI_CHECK_FAIL( gActorAnim.GetCurrentPosition() != vec3Position, "Animate api for path with Vector is not working properly for position" );
  DALI_CHECK_FAIL( gActorAnim.GetCurrentOrientation() !=  quatRotation, "Animate api for path with Vector is not working properly for orientation " );

  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);

  DaliLog::PrintPass();
}

void AnimationAnimateBetweenActorVisibleP()
{
  gFloatAnimationSetDuration = 0.3f;

  gAnimation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL(!gAnimation, "Animation:;new() is failed.");

  gActorAnim = Actor::New();
  DALI_CHECK_FAIL(!gActorAnim, "Actor:;new() is failed.");
  gActorAnim.SetVisible(false);
  Stage::GetCurrent().Add(gActorAnim);
}
void VTAnimationAnimateBetweenActorVisible001()
{
  DALI_CHECK_FAIL(gActorAnim.IsVisible()!=false, "Failed to make the actor invisible initially.");

  float fAdd(0.0f);
  bool bSetAddVal(true);
  KeyFrames keyFrames = KeyFrames::New();
  DALI_CHECK_FAIL(!keyFrames, "KeyFrames:;new() is failed.");
  for(int nLoopCounter = 0 ; nLoopCounter <= 2 ; nLoopCounter++)
  {
    keyFrames.Add(fAdd, bSetAddVal);
    fAdd+=0.5f;
    bSetAddVal ? bSetAddVal = false : bSetAddVal = true;
  }

  gAnimation.AnimateBetween( Property(gActorAnim, Actor::Property::VISIBLE), keyFrames );
  gAnimation.Play();
}

void VTAnimationAnimateBetweenActorVisible002()
{
  //after full frame progress and animation time, actor should be visible
  DALI_CHECK_FAIL(gActorAnim.IsVisible() != true, "Actor is not visible which is unexpected after animation is over.");

  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}

void AnimationAnimateBetweenActorRotationP()
{
  float fAdd(0.0f);
  gFloatAnimationSetDuration = 0.3f;
  AngleAxis angleAxis(Degree(90), Vector3::XAXIS);
  Quaternion quatStart(Radian(angleAxis.angle), angleAxis.axis);

  gAnimation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL(!gAnimation, "Animation::New is failed .");

  gActorAnim = Actor::New();
  DALI_CHECK_FAIL(!gActorAnim, "Actor::New is failed .");
  gActorAnim.SetOrientation(angleAxis.angle, angleAxis.axis);

  Stage::GetCurrent().Add(gActorAnim);

  KeyFrames keyFrames = KeyFrames::New();
  DALI_CHECK_FAIL(!keyFrames, "Keyframes::New is failed .");
  keyFrames.Add(fAdd, AngleAxis(Degree(60), Vector3::ZAXIS)); //set target orientation for animation
  gAnimation.AnimateBetween( Property(gActorAnim, Actor::Property::ORIENTATION), keyFrames );
  gAnimation.Play();
}
void VTAnimationAnimateBetweenActorRotation001()
{
  Quaternion quatCheck (Radian(Degree(60)) , Vector3::ZAXIS);    //matching to the orientation which was set for animation

  DALI_CHECK_FAIL(!AnimationTemplateCheck<Quaternion>(gActorAnim.GetCurrentOrientation(), quatCheck, ANIMATION_EPSILON), "Actor rotation animate between failed .");
  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}


void AnimationAnimateBetweenColorAlphaP()
{
  gFloatAnimationSetDuration = 0.3f;
  gAnimation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL(!gAnimation, "Animation::New is failed .");

  gActorAnim = Actor::New();
  DALI_CHECK_FAIL(!gActorAnim, "Actor::New is failed .");
  gActorAnim.SetColor(ANIM_INIT_COLOR);

  Stage::GetCurrent().Add(gActorAnim);
}
void VTAnimationAnimateBetweenColorAlpha001()
{
  DALI_CHECK_FAIL( gActorAnim.GetCurrentColor().a != ANIM_INIT_COLOR.a, "Failed to set initial alpha component of actor's color." );

  float fAdd = 0.0f;
  KeyFrames keyFrames = KeyFrames::New();
  DALI_CHECK_FAIL(!keyFrames, "KeyFrames::New is failed .");
  for(int nLoopCounter = 0 ; nLoopCounter < 2 ; nLoopCounter++)
  {
    fAdd += (ANIM_TARGET_COLOR.a)/2.0f;
    keyFrames.Add( fAdd, fAdd );
  }

  gAnimation.AnimateBetween( Property(gActorAnim, Actor::Property::COLOR_ALPHA), keyFrames ,AlphaFunction::LINEAR);
  gAnimation.Play();
}
void VTAnimationAnimateBetweenColorAlpha002()
{
  DALI_CHECK_FAIL(!AnimationTemplateCheck<float>(gActorAnim.GetCurrentColor().a, ANIM_TARGET_COLOR.a, ANIMATION_EPSILON), "Actor coloar alpha animate between failed .");

  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}

void AnimationAnimatPathTimePeriodP()
{
  gSetProgress = 1.0f;
  gFloatAnimationSetDuration = 0.4f;
  TimePeriod timePeriod(0.0f, 0.3f);

  gAnimation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL(!gAnimation, "Animation::New is failed .");

  gActorAnim = Actor::New();
  DALI_CHECK_FAIL(!gActorAnim, "Actor::New is failed .");

  //Build the path
  Vector3 positionStart( 30.0,  80.0,  0.0);
  Vector3 positionMid( 70.0,  120.0, 0.0);
  Vector3 positionEnd( 100.0, 100.0, 0.0);

  gPathAnim = Path::New();
  DALI_CHECK_FAIL(!gPathAnim, "Path::New is failed .");

  gPathAnim.AddPoint(positionStart);
  gPathAnim.AddPoint(positionMid);
  gPathAnim.AddPoint(positionEnd);

  //Control points for first segment
  gPathAnim.AddControlPoint( Vector3( 39.0,  90.0, 0.0) );
  gPathAnim.AddControlPoint(Vector3( 56.0, 119.0, 0.0) );

  //Control points for second segment
  gPathAnim.AddControlPoint(Vector3( 78.0, 120.0, 0.0));
  gPathAnim.AddControlPoint(Vector3( 93.0, 104.0, 0.0));

  Stage::GetCurrent().Add(gActorAnim);

  gAnimation.Animate(gActorAnim, gPathAnim, Vector3::XAXIS, timePeriod);
  gAnimation.Play();
}
void VTAnimationAnimatPathTimePeriod001()
{
  Vector3 vec3Position, vec3Tangent;
  Quaternion quatRotation;
  //at 100% progress
  gPathAnim.Sample( gSetProgress, vec3Position, vec3Tangent );
  quatRotation = Quaternion( Vector3::XAXIS, vec3Tangent );

  DALI_CHECK_FAIL( gActorAnim.GetCurrentPosition() != vec3Position, "Animate api is not working properly" );
  DALI_CHECK_FAIL( gActorAnim.GetCurrentOrientation() !=  quatRotation, "Animate api is not working properly" );

  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}

void AnimationAnimatePathAlphafunctionP()
{
  gSetProgress = 1.0f; //for 100% progress
  gFloatAnimationSetDuration = 0.3f;

  gActorAnim = Actor::New();
  DALI_CHECK_FAIL(!gActorAnim, "Actor::New is failed .");

  //Build the path
  Vector3 positionStart( 30.0,  80.0,  0.0);
  Vector3 positionMid( 70.0,  120.0, 0.0);
  Vector3 positionEnd( 100.0, 100.0, 0.0);

  gPathAnim = Path::New();
  DALI_CHECK_FAIL(!gPathAnim, "Path::New is failed .");

  gPathAnim.AddPoint(positionStart);
  gPathAnim.AddPoint(positionMid);
  gPathAnim.AddPoint(positionEnd);

  //Control points for first segment
  gPathAnim.AddControlPoint( Vector3( 39.0,  90.0, 0.0) );
  gPathAnim.AddControlPoint(Vector3( 56.0, 119.0, 0.0) );

  //Control points for second segment
  gPathAnim.AddControlPoint(Vector3( 78.0, 120.0, 0.0));
  gPathAnim.AddControlPoint(Vector3( 93.0, 104.0, 0.0));

  Stage::GetCurrent().Add(gActorAnim);

  gAnimation = Animation::New(gFloatAnimationSetDuration);
  DALI_CHECK_FAIL(!gAnimation, "Animation::New is failed .");

  gAnimation.Animate(gActorAnim, gPathAnim, Vector3::XAXIS, AlphaFunction::LINEAR);
  gAnimation.Play();
}
void VTAnimationAnimatePathAlphafunction001()
{
  Vector3 vec3Position, vec3Tangent;
  Quaternion quatRotation;

  //at 100% progress
  gPathAnim.Sample( gSetProgress, vec3Position, vec3Tangent );
  quatRotation = Quaternion( Vector3::XAXIS, vec3Tangent );

  DALI_CHECK_FAIL( gActorAnim.GetCurrentPosition() != vec3Position, "Animate api is not working properly for position" );
  DALI_CHECK_FAIL( gActorAnim.GetCurrentOrientation() !=  quatRotation, "Animate api is not working properlyfor rotation" );

  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);

  DaliLog::PrintPass();
}


void AnimationAnimateBetweenKeyframesCommonInitalizeP()
{
  if ( !AnimationZeroColorActorInit( gActorAnim, gAnimation ) )
  {
    test_return_value = TC_FAIL;
    return;
  }
}
void VTAnimationAnimateBetweenKeyframesInterpolation001()
{
  KeyFrames keyFrames;
  if( !AnimationInitColorCheckSetKeyFrame(gActorAnim, keyFrames) )
  {
    test_return_value = TC_FAIL;
    return;
  }

  Animation::Interpolation interPolation = Animation::Cubic;
  gAnimation.AnimateBetween( Property(gActorAnim, Actor::Property::COLOR), keyFrames, interPolation );
  gAnimation.Play();
}
void VTAnimationAnimateBetweenKeyframesAlphafunctionInterpolation001()
{
  KeyFrames keyFrames;
  if( !AnimationInitColorCheckSetKeyFrame(gActorAnim, keyFrames) )
  {
    test_return_value = TC_FAIL;
    return;
  }

  Animation::Interpolation interPolation = Animation::Cubic;
  gAnimation.AnimateBetween( Property(gActorAnim, Actor::Property::COLOR), keyFrames, AlphaFunction::LINEAR, interPolation );
  gAnimation.Play();
}

void VTAnimationAnimateBetweenKeyframesInterpolationWithTimePeriod001()
{
  KeyFrames keyFrames;
  if( !AnimationInitColorCheckSetKeyFrame(gActorAnim, keyFrames) )
  {
    test_return_value = TC_FAIL;
    return;
  }

  float fDelay(0.15f);
  Animation::Interpolation interPolation = Animation::Linear;
  TimePeriod timePeriod( fDelay, gFloatAnimationSetDuration - fDelay );
  gAnimation.AnimateBetween( Property(gActorAnim, Actor::Property::COLOR), keyFrames, timePeriod, interPolation );
  gAnimation.Play();
}

void VTAnimationAnimateBetweenKeyframesInterpolationTimePeriodAlphaFunc001()
{
  KeyFrames keyFrames;
  if( !AnimationInitColorCheckSetKeyFrame(gActorAnim, keyFrames) )
  {
    test_return_value = TC_FAIL;
    return;
  }

  float fDelay(0.15f);
  Animation::Interpolation interPolation = Animation::Cubic;
  TimePeriod timePeriod( fDelay, gFloatAnimationSetDuration - fDelay );
  gAnimation.AnimateBetween( Property(gActorAnim, Actor::Property::COLOR), keyFrames, AlphaFunction::LINEAR ,timePeriod, interPolation );
  gAnimation.Play();
}

void VTAnimationAnimateBetweenKeyframesAlphafunctionLinearTimePeriod001()
{
  KeyFrames keyFrames;
  if( !AnimationInitColorCheckSetKeyFrame(gActorAnim, keyFrames) )
  {
    test_return_value = TC_FAIL;
    return;
  }

  float fDelay(0.15f);
  TimePeriod timePeriod( fDelay, gFloatAnimationSetDuration - fDelay );
  gAnimation.AnimateBetween( Property(gActorAnim, Actor::Property::COLOR), keyFrames,AlphaFunction::LINEAR, timePeriod );
  gAnimation.Play();
}

void VTAnimationAnimateBetweenKeyframesTimePeriod001()
{
  KeyFrames keyFrames;
  if( !AnimationInitColorCheckSetKeyFrame(gActorAnim, keyFrames) )
  {
    test_return_value = TC_FAIL;
    return;
  }

  float fDelay(0.15f);
  TimePeriod timePeriod( fDelay, gFloatAnimationSetDuration - fDelay );
  gAnimation.AnimateBetween( Property(gActorAnim, Actor::Property::COLOR), keyFrames, timePeriod );
  gAnimation.Play();
}

void VTAnimationAnimateBetweenKeyframesCommonCheckFinalColor002()
{
  if ( !AnimationFinalColorCheck(gActorAnim) )
  {
    test_return_value = TC_FAIL;
    return;
  }

  gAnimation.Clear();
  Stage::GetCurrent().Remove(gActorAnim);
  DaliLog::PrintPass();
}


void AnimationGetLoopingModeP()
{
  Animation animation = Animation::New(1.0f);

  // default mode
  DALI_CHECK_FAIL(animation.GetLoopingMode() != Animation::RESTART, "animation looping mode is wrong");

  animation.SetLoopingMode( Animation::AUTO_REVERSE );
  DALI_CHECK_FAIL(animation.GetLoopingMode() != Animation::AUTO_REVERSE, "animation looping mode is wrong");

  DaliLog::PrintPass();
}

void VTAnimationPlayAfterP()
{
  float fGetProgress = gAnimation.GetCurrentProgress();
  float fExpectedExactProgress = gFloatAnimationSetDuration - ((float)500.0f) / 1000.0f - 0.2f;

  if(gAnimation.GetState() != Animation::PLAYING)
  {
     test_return_value = TC_FAIL;
     return;
  }

  if( fabsf(fGetProgress - fExpectedExactProgress) <= ANIMATION_EPSILON )
  {
      LOG_I("GetCurrentProgress is found almost exactly as expected.");
  }
  else if ( (fGetProgress > (fExpectedExactProgress - 0.2f ) ) && (fGetProgress < fExpectedExactProgress ) )
  {
      LOG_I("GetCurrentProgress is found near to the expected exact progress value.");
  }
  else
  {
      LOG_E("GetCurrentProgress is not found properly.");
      test_return_value = TC_FAIL;
      return;
  }
  DaliLog::PrintPass();
}

void AnimationPlayAfterP()
{
  float fStartPos(0.0f);

  gActorAnim = Actor::New();
  Stage::GetCurrent().Add(gActorAnim);

  gAnimation= Animation::New(gFloatAnimationSetDuration);
  gActorAnim.SetPosition(Vector3::ZERO);
  gAnimation.AnimateTo( Property(gActorAnim, Actor::Property::POSITION ), Vector3(100.0f, 100.0f, 100.0f), AlphaFunction::LINEAR, TimePeriod( 0.5f, 0.5f ) );

  gAnimation.SetPlayRange(Vector2(gPlayFrom, gPlayTo));
  float fGetProgress = gAnimation.GetCurrentProgress();
  DALI_CHECK_FAIL( fGetProgress > fStartPos, "Checked with outside the PlayRange, Progress = , outside the range[0,1], Play is not ignored.");

  // Play animation after the initial delay time
  gAnimation.PlayAfter( 0.2f );
  fGetProgress = gAnimation.GetCurrentProgress();
  DALI_CHECK_FAIL( fGetProgress > fStartPos, "Checked with outside the PlayRange, Progress = , outside the range[0,1], Play is not ignored.");

}

void VTAnimationPlayAfterN()
{
  float fGetProgress = gAnimation.GetCurrentProgress();
  float fExpectedExactProgress = gFloatAnimationSetDuration - ((float)500.0f) / 1000.0f;

  if(gAnimation.GetState() != Animation::PLAYING)
  {
     test_return_value = TC_FAIL;
     return;
  }

  if( fabsf(fGetProgress - fExpectedExactProgress) <= ANIMATION_EPSILON )
  {
      LOG_I("GetCurrentProgress is found almost exactly as expected.");
  }
  else if ( (fGetProgress > (fExpectedExactProgress - 0.2f ) ) && (fGetProgress < fExpectedExactProgress ) )
  {
      LOG_I("GetCurrentProgress is found near to the expected exact progress value.");
  }
  else
  {
      LOG_E("GetCurrentProgress is not found properly.");
      test_return_value = TC_FAIL;
  }
  DaliLog::PrintPass();
}

void AnimationPlayAfterN()
{
  float fStartPos(0.0f);

  gActorAnim = Actor::New();
  Stage::GetCurrent().Add(gActorAnim);

  gAnimation= Animation::New(gFloatAnimationSetDuration);
  gActorAnim.SetPosition(Vector3::ZERO);
  gAnimation.AnimateTo( Property(gActorAnim, Actor::Property::POSITION ), Vector3(100.0f, 100.0f, 100.0f), AlphaFunction::LINEAR, TimePeriod( 0.5f, 0.5f ) );

  gAnimation.SetPlayRange(Vector2(gPlayFrom, gPlayTo));
  float fGetProgress = gAnimation.GetCurrentProgress();
  DALI_CHECK_FAIL( fGetProgress > fStartPos, "Checked with outside the PlayRange, Progress = , outside the range[0,1], Play is not ignored.");

  // When the delay time is negative value, it would treat as play immediately.
  gAnimation.PlayAfter( -0.2f );
  fGetProgress = gAnimation.GetCurrentProgress();
  DALI_CHECK_FAIL( fGetProgress > fStartPos, "Checked with outside the PlayRange, Progress = , outside the range[0,1], Play is not ignored.");
}

void VTAnimationSetLoopingModeP()
{
  float fGetProgress = gAnimation.GetCurrentProgress();
  float gChkTimer = 0.0f;
  if(gRenderCountAnim % 2 == 1)
     gChkTimer = 0.5f;
  float fExpectedExactProgress = gFloatAnimationSetDuration - ((float)500.0f) / 1000.0f + gChkTimer;

  if(gAnimation.GetState() != Animation::PLAYING)
  {
     test_return_value = TC_FAIL;
     return;
  }

  if( fabsf(fGetProgress - fExpectedExactProgress) <= ANIMATION_EPSILON )
  {
      LOG_I("GetCurrentProgress is found almost exactly as expected.");
  }
  else if ( (fGetProgress > (fExpectedExactProgress - 0.2f ) ) && (fGetProgress < fExpectedExactProgress ) )
  {
      LOG_I("GetCurrentProgress is found near to the expected exact progress value.");
  }
  else
  {
      LOG_E("GetCurrentProgress is not found properly.");
      test_return_value = TC_FAIL;
      return;
  }
  DaliLog::PrintPass();
}

void AnimationSetLoopingModeP()
{
  float fStartPos(0.0f);
  gActorAnim = Actor::New();
  Stage::GetCurrent().Add(gActorAnim);

  gAnimation= Animation::New(gFloatAnimationSetDuration);
  gActorAnim.SetPosition(Vector3::ZERO);
  gAnimation.AnimateTo( Property(gActorAnim, Actor::Property::POSITION ), Vector3(100.0f, 100.0f, 100.0f));

  //LoopingMode::RESTART
  gAnimation.SetLoopingMode( Animation::RESTART );
  gAnimation.SetLooping(1);
  float fGetProgress = gAnimation.GetCurrentProgress();
  DALI_CHECK_FAIL( fGetProgress > fStartPos, "Checked with outside the PlayRange, Progress = , outside the range[0,1], Play is not ignored.");

  // Play animation after the initial delay time
  gAnimation.PlayAfter( 0.0f );
  fGetProgress = gAnimation.GetCurrentProgress();
  DALI_CHECK_FAIL( fGetProgress > fStartPos, "Checked with outside the PlayRange, Progress = , outside the range[0,1], Play is not ignored.");
}

void VTAnimationSetLoopingModeP2()
{
  float fGetProgress = gAnimation.GetCurrentProgress();
  float gChkTimer = 0.0f;
  if(gRenderCountAnim % 2 == 1)
     gChkTimer = 0.5f;
  float fExpectedExactProgress = gFloatAnimationSetDuration - ((float)500.0f) / 1000.0f - gChkTimer;

  if(gAnimation.GetState() != Animation::PLAYING)
  {
     test_return_value = TC_FAIL;
     return;
  }
  if( fabsf(fGetProgress - fExpectedExactProgress) <= ANIMATION_EPSILON )
  {
      LOG_I("GetCurrentProgress is found almost exactly as expected.");
  }
  else if ( (fGetProgress > (fExpectedExactProgress ) ) && (fGetProgress < fExpectedExactProgress + 0.2f ) )
  {
      LOG_I("GetCurrentProgress is found near to the expected exact progress value.");
  }
  else
  {
      LOG_E("GetCurrentProgress is not found properly.");
      test_return_value = TC_FAIL;
      return;
  }
  DaliLog::PrintPass();
}

void AnimationSetLoopingModeP2()
{
  float fStartPos(0.0f);
  gActorAnim = Actor::New();
  Stage::GetCurrent().Add(gActorAnim);

  gAnimation= Animation::New(gFloatAnimationSetDuration);
  gActorAnim.SetPosition(Vector3::ZERO);
  gAnimation.AnimateTo( Property(gActorAnim, Actor::Property::POSITION ), Vector3(100.0f, 100.0f, 100.0f));

  //LoopingMode::AUTO_REVERSE
  gAnimation.SetLoopingMode( Animation::AUTO_REVERSE );
  gAnimation.SetLooping(1);
  gAnimation.SetSpeedFactor( -1.0f );
  float fGetProgress = gAnimation.GetCurrentProgress();
  DALI_CHECK_FAIL( fGetProgress > fStartPos, "Checked with outside the PlayRange, Progress = , outside the range[0,1], Play is not ignored.");

  // Play animation after the initial delay time
  gAnimation.PlayAfter( 0.0f );
  fGetProgress = gAnimation.GetCurrentProgress();
  DALI_CHECK_FAIL( fGetProgress > fStartPos, "Checked with outside the PlayRange, Progress = , outside the range[0,1], Play is not ignored.");
}

