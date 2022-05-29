#include "utc-dali-animation-impl.h"


//& set: Animation

unsigned int gInterVal = INTERVAL;

/**
 * @function            utc_Dali_Animation_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Animation_startup(void)
{
  test_return_value = 0;
  gRenderCountAnim = 0;
}


/**
 * @function            utc_Dali_Animation_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Animation_cleanup(void)
{
}

namespace
{
  enum TEST_CASES_LIST_ACTOR
  {
    ANIMATION_CONSTRUCTOR_P,
    ANIMATION_NEW_P,
    ANIMATION_NEW_N,
    ANIMATION_SET_GET_SPEED_FACTOR_P,
    ANIMATION_SET_GET_CURRENT_PROGRESS_P,
    ANIMATION_SET_GET_PLAY_RANGE_P,
    ANIMATION_PLAYFROM_P,
    ANIMATION_SET_GET_ENDACTION_WITHBAKEFINAL_P,
    ANIMATION_DOWNCAST_P,
    ANIMATION_DOWNCAST_N,
    ANIMATION_SET_GET_DURATION_P,
    ANIMATION_SET_GET_LOOPCOUNT_P,
    ANIMATION_GET_CURRENTLOOP_P,
    ANIMATION_SET_ISLOOPING_P,
    ANIMATION_HIDEISVISIBLE_P,
    ANIMATION_SHOWISVISIBLE_P,
    ANIMATION_SET_GET_ENDACTION_WITHBAKE_P,
    ANIMATION_SET_GET_ENDACTION_WITHDISCARD_P,
    ANIMATION_SET_GET_DEFAULT_ALPHFUNCTION_LINEAR_P,
    ANIMATION_SET_GET_DEFAULT_ALPHFUNCTION_EASEIN_P,
    ANIMATION_STOP_P,
    ANIMATION_CLEAR_P,
    ANIMATION_PAUSE_P,
    ANIMATION_COPYCONSTRUCTOR_P,
    ANIMATION_OPERATOR_ASSIGNMENT_P,
    ANIMATION_ANIMATE_BYBOOL_P,
    ANIMATION_ANIMATE_BYFLOAT_P,
    ANIMATION_ANIMATE_PATHTIMEPERIODALPHAFUNCTION_P,
    ANIMATION_ANIMATE_BYINTEGER_P,
    ANIMATION_ANIMATE_BYVECTOR2_P,
    ANIMATION_ANIMATE_BYVECTOR3_P,
    ANIMATION_ANIMATE_BYVECTOR4_P,
    ANIMATION_ANIMATE_PATHVECTOR_P,
    ANIMATION_ANIMATE_BYVECTOR4TIMEPERIOD_P,
    ANIMATION_ANIMATE_BYVECTOR3TIMEPERIOD_P,
    ANIMATION_ANIMATE_BYVECTOR2TIMEPERIOD_P,
    ANIMATION_ANIMATE_BYFLOATTIMEPERIOD_P,
    ANIMATION_ANIMATE_BYVECTOR4TIMEPERIODALPHAFUNCTION_P,
    ANIMATION_ANIMATE_BYVECTOR4ALPHAFUNCTION_P,
    ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_ALPHAFUNCTIONLINEARTIMEPERIOD_P,
    ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_TIMEPERIOD_P,
    ANIMATION_ANIMATE_TOVECTOR4_P,
    ANIMATION_ANIMATE_TOVECTOR3_P,
    ANIMATION_ANIMATE_TOVECTOR2_P,
    ANIMATION_ANIMATE_TOFLOAT_P,
    ANIMATION_ANIMATE_TOVECTOR4TIMEPERIOD_P,
    ANIMATION_ANIMATE_TOVECTOR2TIMEPERIOD_P,
    ANIMATION_ANIMATE_TOVECTOR3TIMEPERIOD_P,
    ANIMATION_ANIMATE_TOFLOATTIMEPERIOD_P,
    ANIMATION_ANIMATE_TOVECTOR4TIMEPERIODALPHAFUNCTION_P,
    ANIMATION_ANIMATE_TOVECTOR2TIMEPERIODALPHAFUNCTION_P,
    ANIMATION_ANIMATE_TOVECTOR3TIMEPERIODALPHAFUNCTION_P,
    ANIMATION_ANIMATE_TOFLOATTIMEPERIODALPHAFUNCTION_P,
    ANIMATION_ANIMATE_TOVECTOR3ALPHAFUNCTION_P,
    ANIMATION_ANIMATE_BETWEEN_ACTORVISIBLE_P,
    ANIMATION_ANIMATE_BETWEEN_ACTORROTATION_P,
    ANIMATION_ANIMATE_BETWEEN_COLORALPHA_P,
    ANIMATION_ANIMATE_PATHTIMEPERIOD_P,
    ANIMATION_ANIMATE_PATHALPHAFUNCTION_P,
    ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_INTERPOLATION_P,
    ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_ALPHAFUNCTIONINTERPOLATION_P,
    ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_INTERPOLATIONTIMEPERIOD_P,
    ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_INTERPOLATIONTIMEPERIODALPHAFUNC_P,
    ANIMATION_SET_GET_DISCONNECTACTION_BAKE_P,
    ANIMATION_SET_GET_DISCONNECTACTION_BAKE_FINAL_P,
    ANIMATION_SET_GET_DISCONNECTACTION_DISCARD_P,
    ANIMATION_ANIMATE_TO_P,
    ANIMATION_GET_LOOPING_MODE_P,
    ANIMATION_PLAY_AFTER_P,
    ANIMATION_PLAY_AFTER_N,
    ANIMATION_SET_LOOPING_MODE_P,
    ANIMATION_SET_LOOPING_MODE_P2,
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
      mTimer = Timer::New( gInterVal );
      mTimer.TickSignal().Connect( this, &TestApp::Tick );
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
        case ANIMATION_SET_GET_SPEED_FACTOR_P:
          AnimationSetGetSpeedFactorP();
          break;

        case ANIMATION_SET_GET_CURRENT_PROGRESS_P:
          AnimationSetGetCurrentProgressP();
          break;

        case ANIMATION_SET_GET_PLAY_RANGE_P:
          AnimationSetGetPlayRangeP();
          break;

        case ANIMATION_PLAYFROM_P:
          AnimationPlayFromP();
          break;

        case ANIMATION_SET_GET_ENDACTION_WITHBAKEFINAL_P:
          AnimationSetGetEndActionWithBakeFinalP();
          break;

        case ANIMATION_DOWNCAST_P:
          AnimationDowncastP();
          break;

        case ANIMATION_DOWNCAST_N:
          AnimationDowncastN();
          break;

        case ANIMATION_SET_GET_DURATION_P:
          AnimationSetGetDurationP();
          break;

        case ANIMATION_SET_GET_LOOPCOUNT_P:
          AnimationSetGetLoopCountP();
          break;

        case ANIMATION_GET_CURRENTLOOP_P:
          AnimationSetGetCurrentLoopP();
          break;

        case ANIMATION_SET_ISLOOPING_P:
          AnimationSetIsLoopingP();
          break;

        case ANIMATION_HIDEISVISIBLE_P:
          AnimationHideIsVisibleP();
          break;

        case ANIMATION_SHOWISVISIBLE_P:
          AnimationShowIsVisibleP();
          break;

        case ANIMATION_SET_GET_ENDACTION_WITHBAKE_P:
          AnimationSetGetEndActionWithBakeP();
          break;

        case ANIMATION_SET_GET_ENDACTION_WITHDISCARD_P:
          AnimationSetGetEndActionWithDiscardP();
          break;

        case ANIMATION_SET_GET_DEFAULT_ALPHFUNCTION_LINEAR_P:
          AnimationSetGetDefaultAlphfunctionLinearP();
          break;

        case ANIMATION_SET_GET_DEFAULT_ALPHFUNCTION_EASEIN_P:
          AnimationSetGetDefaultAlphfunctionEaseInP();
          break;

        case ANIMATION_STOP_P:
          AnimationStopP();
          break;

        case ANIMATION_CLEAR_P:
          AnimationClearP();
          break;

        case ANIMATION_PAUSE_P:
          AnimationPauseP();
          break;

        case ANIMATION_CONSTRUCTOR_P:
          AnimationConstructorP();
          break;

        case ANIMATION_NEW_P:
          AnimationNewP();
          break;

        case ANIMATION_NEW_N:
          AnimationNewN();
          break;

        case ANIMATION_COPYCONSTRUCTOR_P:
          AnimationCopyConstructorP();
          break;

        case ANIMATION_OPERATOR_ASSIGNMENT_P:
          AnimationOperatorAssignMentP();
          break;

        case ANIMATION_ANIMATE_BYBOOL_P:
          AnimationAnimateByBoolP();
          break;

        case ANIMATION_ANIMATE_BYFLOAT_P:
          AnimationAnimateByFloatP();
          break;

        case ANIMATION_ANIMATE_PATHTIMEPERIODALPHAFUNCTION_P:
          AnimationAnimatePathTimePeriodAlphaFunctionP();
          break;

        case ANIMATION_ANIMATE_BYINTEGER_P:
          AnimationAnimateByIntegerP();
          break;

        case ANIMATION_ANIMATE_BYVECTOR2_P:
          AnimationAnimateByVector2P();
          break;

        case ANIMATION_ANIMATE_BYVECTOR3_P:
          AnimationAnimateByVector3P();
          break;

        case ANIMATION_ANIMATE_BYVECTOR4_P:
          AnimationAnimateByVector4P();
          break;

        case ANIMATION_ANIMATE_PATHVECTOR_P:
          AnimationAnimatePathVectorP();
          break;

        case ANIMATION_ANIMATE_BYVECTOR4TIMEPERIOD_P:
          AnimationAnimateByVector4TimePeriodP();
          gInterVal = RENDER_DELAY_TIME;
          break;

        case ANIMATION_ANIMATE_BYVECTOR3TIMEPERIOD_P:
          AnimationAnimateByVector3TimePeriodP();
          gInterVal = RENDER_DELAY_TIME;
          break;

        case ANIMATION_ANIMATE_BYVECTOR2TIMEPERIOD_P:
          AnimationAnimateByVector2TimePeriodP();
          gInterVal = RENDER_DELAY_TIME;
          break;

        case ANIMATION_ANIMATE_BYFLOATTIMEPERIOD_P:
          AnimationAnimateByFloatTimePeriodP();
          gInterVal = RENDER_DELAY_TIME;
          break;

        case ANIMATION_ANIMATE_BYVECTOR4TIMEPERIODALPHAFUNCTION_P:
          AnimationAnimateByVector4TimePeriodAlphaFunctionP();
          gInterVal = RENDER_DELAY_TIME;
          break;

        case ANIMATION_ANIMATE_BYVECTOR4ALPHAFUNCTION_P:
          AnimationAnimateByVector4AlphaFunctionP();
          break;

        case ANIMATION_ANIMATE_TOVECTOR4_P:
          AnimationAnimateToVector4P();
          break;

        case ANIMATION_ANIMATE_TOVECTOR3_P:
          AnimationAnimateToVector3P();
          break;

        case ANIMATION_ANIMATE_TOVECTOR2_P:
          AnimationAnimateToVector2P();
          break;

        case ANIMATION_ANIMATE_TO_P:
          AnimationAnimateToP();
          break;

        case ANIMATION_ANIMATE_TOFLOAT_P:
          AnimationAnimateToFloatP();
          break;

        case ANIMATION_ANIMATE_TOVECTOR4TIMEPERIOD_P:
          AnimationAnimateToVector4TimePeriodP();
          gInterVal = RENDER_DELAY_TIME;
          break;

        case ANIMATION_ANIMATE_TOVECTOR2TIMEPERIOD_P:
          AnimationAnimateToVector2TimePeriodP();
          gInterVal = RENDER_DELAY_TIME;
          break;

        case ANIMATION_ANIMATE_TOVECTOR3TIMEPERIOD_P:
          AnimationAnimateToVector3TimePeriodP();
          gInterVal = RENDER_DELAY_TIME;
          break;

        case ANIMATION_ANIMATE_TOFLOATTIMEPERIOD_P:
          AnimationAnimateToFloatTimePeriodP();
          gInterVal = RENDER_DELAY_TIME;
          break;

        case ANIMATION_ANIMATE_TOVECTOR4TIMEPERIODALPHAFUNCTION_P:
          AnimationAnimateToVector4TimePeriodAlphaFunctionP();
          gInterVal = RENDER_DELAY_TIME;
          break;

        case ANIMATION_ANIMATE_TOVECTOR2TIMEPERIODALPHAFUNCTION_P:
          AnimationAnimateToVector2TimePeriodAlphaFunctionP();
          gInterVal = RENDER_DELAY_TIME;
          break;

        case ANIMATION_ANIMATE_TOVECTOR3TIMEPERIODALPHAFUNCTION_P:
          AnimationAnimateToVector3TimePeriodAlphaFunctionP();
          gInterVal = RENDER_DELAY_TIME;
          break;

        case ANIMATION_ANIMATE_TOFLOATTIMEPERIODALPHAFUNCTION_P:
          AnimationAnimateToFloatTimePeriodAlphaFunctionP();
          gInterVal = RENDER_DELAY_TIME;
          break;

        case ANIMATION_ANIMATE_TOVECTOR3ALPHAFUNCTION_P:
          AnimationAnimateToVector3AlphaFunctionP();
          break;

        case ANIMATION_ANIMATE_BETWEEN_ACTORVISIBLE_P:
          AnimationAnimateBetweenActorVisibleP();
          break;

        case ANIMATION_ANIMATE_BETWEEN_ACTORROTATION_P:
          AnimationAnimateBetweenActorRotationP();
          break;

        case ANIMATION_ANIMATE_BETWEEN_COLORALPHA_P:
          AnimationAnimateBetweenColorAlphaP();
          break;

        case ANIMATION_ANIMATE_PATHTIMEPERIOD_P:
          AnimationAnimatPathTimePeriodP();
          break;

        case ANIMATION_ANIMATE_PATHALPHAFUNCTION_P:
          AnimationAnimatePathAlphafunctionP();
          break;

        case ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_INTERPOLATION_P:
        case ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_ALPHAFUNCTIONINTERPOLATION_P:
        case ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_INTERPOLATIONTIMEPERIOD_P:
        case ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_INTERPOLATIONTIMEPERIODALPHAFUNC_P:
        case ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_ALPHAFUNCTIONLINEARTIMEPERIOD_P:
        case ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_TIMEPERIOD_P:
          AnimationAnimateBetweenKeyframesCommonInitalizeP();
          break;

        case ANIMATION_SET_GET_DISCONNECTACTION_BAKE_P:
        case ANIMATION_SET_GET_DISCONNECTACTION_BAKE_FINAL_P:
        case ANIMATION_SET_GET_DISCONNECTACTION_DISCARD_P:
          AnimationSetGetDisconnectActionCommonInitP();
          break;

        case ANIMATION_GET_LOOPING_MODE_P:
          AnimationGetLoopingModeP();
          break;

        case ANIMATION_PLAY_AFTER_P:
          AnimationPlayAfterP();
          break;

        case ANIMATION_PLAY_AFTER_N:
          AnimationPlayAfterN();
          break;

        case ANIMATION_SET_LOOPING_MODE_P:
          AnimationSetLoopingModeP();
          break;

        case ANIMATION_SET_LOOPING_MODE_P2:
          AnimationSetLoopingModeP2();
          break;

      }
    }

    void VerdictTest()
    {
      switch (mTestCase)
      {
        case ANIMATION_SET_GET_SPEED_FACTOR_P:
          VTAnimationSetGetSpeedFactor001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ANIMATION_SET_GET_CURRENT_PROGRESS_P:
          VTAnimationSetGetCurrentProgress001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ANIMATION_SET_GET_ENDACTION_WITHBAKEFINAL_P:
          switch(gRenderCountAnim)
          {
            case 0:
              VTAnimationSetGetEndActionWithBakeFinal001();
              gRenderCountAnim++;
              break;

            case 1:
              VTAnimationSetGetEndActionWithBakeFinal002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ANIMATION_SET_GET_DURATION_P:
          VTAnimationSetGetDuration001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ANIMATION_HIDEISVISIBLE_P:
          switch(gRenderCountAnim)
          {
            case 0:
              VTAnimationHideIsVisible001();
              gRenderCountAnim++;
              break;

            case 1:
              VTAnimationHideIsVisible002();
              gRenderCountAnim++;
              break;

            case 2:
              VTAnimationHideIsVisible003();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ANIMATION_SHOWISVISIBLE_P:
          switch(gRenderCountAnim)
          {
            case 0:
              VTAnimationShowIsVisible001();
              gRenderCountAnim++;
              break;

            case 1:
              VTAnimationShowIsVisible002();
              gRenderCountAnim++;
              break;

            case 2:
              VTAnimationShowIsVisible003();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ANIMATION_SET_GET_ENDACTION_WITHBAKE_P:
          VTAnimationSetGetEndActionWithBake001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ANIMATION_SET_GET_ENDACTION_WITHDISCARD_P:
          switch(gRenderCountAnim)
          {
            case 0:
              AnimationSetGetEndActionWithDiscard001();
              gRenderCountAnim++;
              break;

            case 1:
              AnimationSetGetEndActionWithDiscard002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ANIMATION_STOP_P:
          switch(gRenderCountAnim)
          {
            case 0:
              VTAnimationStop001();
              gRenderCountAnim++;
              break;

            case 1:
              VTAnimationStop002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ANIMATION_CLEAR_P:
          switch(gRenderCountAnim)
          {
            case 0:
              VTAnimationClear001();
              gRenderCountAnim++;
              break;

            case 1:
              VTAnimationClear002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ANIMATION_PAUSE_P:
          switch(gRenderCountAnim)
          {
            case 0:
              VTAnimationPause001();
              gRenderCountAnim++;
              break;

            case 1:
              VTAnimationPause002();
              gRenderCountAnim++;
              break;

            case 2:
              VTAnimationPause003();
              gRenderCountAnim++;
              break;

            case 3:
              VTAnimationPause004();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ANIMATION_ANIMATE_BYBOOL_P:
          VTAnimationAnimateByBool001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ANIMATION_ANIMATE_BYFLOAT_P:
        case ANIMATION_ANIMATE_BYFLOATTIMEPERIOD_P:
        case ANIMATION_ANIMATE_TOFLOAT_P:
        case ANIMATION_ANIMATE_TOFLOATTIMEPERIOD_P:
        case ANIMATION_ANIMATE_TOFLOATTIMEPERIODALPHAFUNCTION_P:
          VTAnimationAnimateCheckFloat001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ANIMATION_ANIMATE_PATHTIMEPERIODALPHAFUNCTION_P:
          VTAnimationAnimatePathTimePeriodAlphaFunction001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ANIMATION_ANIMATE_BYINTEGER_P:
          VTAnimationAnimateByInteger001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ANIMATION_ANIMATE_BYVECTOR2_P:
        case ANIMATION_ANIMATE_BYVECTOR2TIMEPERIOD_P:
        case ANIMATION_ANIMATE_TOVECTOR2_P:
        case ANIMATION_ANIMATE_TOVECTOR2TIMEPERIODALPHAFUNCTION_P:
        case ANIMATION_ANIMATE_TOVECTOR2TIMEPERIOD_P:
          VTAnimationAnimateCheckVector2();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ANIMATION_ANIMATE_BYVECTOR3_P:
        case ANIMATION_ANIMATE_BYVECTOR3TIMEPERIOD_P:
        case ANIMATION_ANIMATE_TOVECTOR3_P:
        case ANIMATION_ANIMATE_TO_P:
        case ANIMATION_ANIMATE_TOVECTOR3TIMEPERIOD_P:
        case ANIMATION_ANIMATE_TOVECTOR3TIMEPERIODALPHAFUNCTION_P:
        case ANIMATION_ANIMATE_TOVECTOR3ALPHAFUNCTION_P:
          VTAnimationAnimateCheckVector3();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ANIMATION_ANIMATE_BYVECTOR4_P:
        case ANIMATION_ANIMATE_BYVECTOR4TIMEPERIOD_P:
        case ANIMATION_ANIMATE_BYVECTOR4TIMEPERIODALPHAFUNCTION_P:
        case ANIMATION_ANIMATE_BYVECTOR4ALPHAFUNCTION_P:
        case ANIMATION_ANIMATE_TOVECTOR4_P:
        case ANIMATION_ANIMATE_TOVECTOR4TIMEPERIOD_P:
        case ANIMATION_ANIMATE_TOVECTOR4TIMEPERIODALPHAFUNCTION_P:
          VTAnimationAnimateCheckVector4();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ANIMATION_ANIMATE_PATHVECTOR_P:
          VTAnimationAnimatePathVector001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ANIMATION_ANIMATE_BETWEEN_ACTORROTATION_P:
          VTAnimationAnimateBetweenActorRotation001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ANIMATION_ANIMATE_PATHTIMEPERIOD_P:
          VTAnimationAnimatPathTimePeriod001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ANIMATION_ANIMATE_PATHALPHAFUNCTION_P:
          VTAnimationAnimatePathAlphafunction001();
          mTimer.Stop();
          mApplication.Quit();
          break;


        case ANIMATION_PLAYFROM_P:
          VTAnimationPlayFrom001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_INTERPOLATION_P:
          switch(gRenderCountAnim)
          {
            case 0:
              VTAnimationAnimateBetweenKeyframesInterpolation001();
              gRenderCountAnim++;
              break;

            case 1:
              VTAnimationAnimateBetweenKeyframesCommonCheckFinalColor002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_ALPHAFUNCTIONINTERPOLATION_P:
          switch(gRenderCountAnim)
          {
            case 0:
              VTAnimationAnimateBetweenKeyframesAlphafunctionInterpolation001();
              gRenderCountAnim++;
              break;

            case 1:
              VTAnimationAnimateBetweenKeyframesCommonCheckFinalColor002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_INTERPOLATIONTIMEPERIOD_P:
          switch(gRenderCountAnim)
          {
            case 0:
              VTAnimationAnimateBetweenKeyframesInterpolationWithTimePeriod001();
              gRenderCountAnim++;
              break;

            case 1:
              VTAnimationAnimateBetweenKeyframesCommonCheckFinalColor002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_INTERPOLATIONTIMEPERIODALPHAFUNC_P:
          switch(gRenderCountAnim)
          {
            case 0:
              VTAnimationAnimateBetweenKeyframesInterpolationTimePeriodAlphaFunc001();
              gRenderCountAnim++;
              break;

            case 1:
              VTAnimationAnimateBetweenKeyframesCommonCheckFinalColor002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ANIMATION_SET_GET_PLAY_RANGE_P:
          VTAnimationSetGetPlayRange001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ANIMATION_ANIMATE_BETWEEN_COLORALPHA_P:
          switch(gRenderCountAnim)
          {
            case 0:
              VTAnimationAnimateBetweenColorAlpha001();
              gRenderCountAnim++;
              break;

            case 1:
              VTAnimationAnimateBetweenColorAlpha002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_ALPHAFUNCTIONLINEARTIMEPERIOD_P:
          switch(gRenderCountAnim)
          {
            case 0:
              VTAnimationAnimateBetweenKeyframesAlphafunctionLinearTimePeriod001();
              gRenderCountAnim++;
              break;

            case 1:
              VTAnimationAnimateBetweenKeyframesCommonCheckFinalColor002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_TIMEPERIOD_P:
          switch(gRenderCountAnim)
          {
            case 0:
              VTAnimationAnimateBetweenKeyframesTimePeriod001();
              gRenderCountAnim++;
              break;

            case 1:
              VTAnimationAnimateBetweenKeyframesCommonCheckFinalColor002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ANIMATION_ANIMATE_BETWEEN_ACTORVISIBLE_P:
          switch(gRenderCountAnim)
          {
            case 0:
              VTAnimationAnimateBetweenActorVisible001();
              gRenderCountAnim++;
              break;

            case 1:
              VTAnimationAnimateBetweenActorVisible002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;


        case ANIMATION_SET_GET_DEFAULT_ALPHFUNCTION_LINEAR_P:
          VTAnimationSetGetDefaultAlphfunctionLinear001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ANIMATION_SET_GET_DEFAULT_ALPHFUNCTION_EASEIN_P:
          VTAnimationSetGetDefaultAlphfunctionEaseIn001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ANIMATION_SET_GET_DISCONNECTACTION_BAKE_P:
          switch(gRenderCountAnim)
          {
            case 0:
              VTAnimationSetGetDisconnectActionBake001();
              gRenderCountAnim++;
              break;

            case 1:
              VTAnimationSetGetDisconnectActionBake002();
              gRenderCountAnim++;
              break;

            case 2:
              VTAnimationSetGetDisconnectActionBake003();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ANIMATION_SET_GET_DISCONNECTACTION_BAKE_FINAL_P:
          switch(gRenderCountAnim)
          {
            case 0:
              VTAnimationSetGetDisconnectActionBakeFinal001();
              gRenderCountAnim++;
              break;

            case 1:
              VTAnimationSetGetDisconnectActionBakeFinal002();
              gRenderCountAnim++;
              break;

            case 2:
              VTAnimationSetGetDisconnectActionBakeFinal003();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ANIMATION_SET_GET_DISCONNECTACTION_DISCARD_P:
          switch(gRenderCountAnim)
          {
            case 0:
              VTAnimationSetGetDisconnectActionDiscard001();
              gRenderCountAnim++;
              break;

            case 1:
              VTAnimationSetGetDisconnectActionDiscard002();
              gRenderCountAnim++;
              break;

            case 2:
              VTAnimationSetGetDisconnectActionDiscard003();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;
        case ANIMATION_PLAY_AFTER_P:
          VTAnimationPlayAfterP();
          mTimer.Stop();
          mApplication.Quit();
        break;

        case ANIMATION_SET_LOOPING_MODE_P:
          VTAnimationSetLoopingModeP();
          gRenderCountAnim++;
          if(gRenderCountAnim  > 6)
          {
            mTimer.Stop();
            mApplication.Quit();
          }
          break;

        case ANIMATION_SET_LOOPING_MODE_P2:
          VTAnimationSetLoopingModeP2();
          gRenderCountAnim++;
          if(gRenderCountAnim  > 6)
          {
            mTimer.Stop();
            mApplication.Quit();
          }
          break;

        case ANIMATION_PLAY_AFTER_N:
          VTAnimationPlayAfterN();
          mTimer.Stop();
          mApplication.Quit();
          break;

        default:
          mTimer.Stop();
          mApplication.Quit();

      }
    }

    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };
} // unnamed namespace

/**
 * @testcase        UtcDaliAnimationSetGetSpeedFactorP
 * @since_tizen     2.4
 * @description     Checks whether the SetSpeedFactor and GetSpeedFactor Api is working properly or not
 */
int UtcDaliAnimationSetGetSpeedFactorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_SET_GET_SPEED_FACTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationSetGetCurrentProgressP
 * @since_tizen     2.4
 * @description     Checks whether the SetCurrentProgress and GetCurrentProgress Api is working properly or not
 */
int UtcDaliAnimationSetGetCurrentProgressP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_SET_GET_CURRENT_PROGRESS_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationSetGetPlayRangeP
 * @since_tizen     2.4
 * @description     Checks whether the SetPlayRange and GetPlayRange Api is working properly or not
 */
int UtcDaliAnimationSetGetPlayRangeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_SET_GET_PLAY_RANGE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationSetGetDisconnectActionWithBakeP
 * @since_tizen     2.4
 * @description     Checks whether the SetDisconnectAction and GetDisconnectAction Api is working properly or not for Animation::Bake
 */
int UtcDaliAnimationSetGetDisconnectActionWithBakeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_SET_GET_DISCONNECTACTION_BAKE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationSetGetDisconnectActionBakeFinalP
 * @since_tizen     2.4
 * @description     Checks whether the SetDisconnectAction and GetDisconnectAction Api is working properly or not for Animation::BakeFinal
 */
int UtcDaliAnimationSetGetDisconnectActionBakeFinalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_SET_GET_DISCONNECTACTION_BAKE_FINAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationSetGetDisconnectActionDiscardP
 * @since_tizen     2.4
 * @description     Checks whether the SetDisconnectAction and GetDisconnectAction Api is working properly or not for Animation::Discard
 */
int UtcDaliAnimationSetGetDisconnectActionDiscardP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_SET_GET_DISCONNECTACTION_DISCARD_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationPlayFromP
 * @since_tizen     2.4
 * @description     Checks whether the UtcDaliAnimationPlayFrom Api is working properly or not. Checked wheather animation starts from a given point.
 */
int UtcDaliAnimationPlayFromP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_PLAYFROM_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliAnimationSetGetEndActionWithBakeFinalP
 * @since_tizen     2.4
 * @description     Checks whether the SetEndAction and GetEndAction Api is working properly or not for EndAction BakeFinal
 */
int UtcDaliAnimationSetGetEndActionWithBakeFinalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_SET_GET_ENDACTION_WITHBAKEFINAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationDowncastP
 * @since_tizen     2.4
 * @description     Downcast an Object handle to Animation New
 */
int UtcDaliAnimationDowncastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_DOWNCAST_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationDowncastN
 * @since_tizen     2.4
 * @description     Downcast an Object handle to Animation using invalid Handle
 */
int UtcDaliAnimationDowncastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_DOWNCAST_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationSetGetDurationP
 * @since_tizen     2.4
 * @description     Checks whether the SetDuration and GetDuration Api is working properly or not
 */
int UtcDaliAnimationSetGetDurationP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_SET_GET_DURATION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationSetIsLoopingP
 * @since_tizen     2.4
 * @description     Checks whether the SetLooping and IsLooping Api is working properly or not
 */
int UtcDaliAnimationSetIsLoopingP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_SET_ISLOOPING_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationSetGetLoopCountP
 * @since_tizen     2.4
 * @description     Checks whether the SetLoopCount and GetLoopCount Api is working properly or not
 */
int UtcDaliAnimationSetGetLoopCountP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_SET_GET_LOOPCOUNT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliAnimationGetCurrentLoopP
 * @since_tizen     2.4
 * @description     Checks whether the GetCurrentLoop Api is working properly or not
 */
int UtcDaliAnimationGetCurrentLoopP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_GET_CURRENTLOOP_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationHideIsVisibleP
 * @since_tizen     2.4
 * @description     Checks whether the Hide and IsVisible Api is working properly or not
 */
int UtcDaliAnimationHideIsVisibleP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_HIDEISVISIBLE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationShowIsVisibleP
 * @since_tizen     2.4
 * @description     Checks whether the Show and IsVisible Api is working properly or not
 */
int UtcDaliAnimationShowIsVisibleP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_SHOWISVISIBLE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliAnimationSetGetEndActionWithEnumBakeP
 * @since_tizen     2.4
 * @description     Checks whether the SetEndAction and GetEndAction Api is working properly or not as Bake
 */
int UtcDaliAnimationSetGetEndActionWithEnumBakeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_SET_GET_ENDACTION_WITHBAKE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliAnimationSetGetEndActionWithDiscardP
 * @since_tizen     2.4
 * @description     Checks whether the SetEndAction and GetEndAction Api is working properly or not for EndAction Discard
 */
int UtcDaliAnimationSetGetEndActionWithDiscardP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_SET_GET_ENDACTION_WITHDISCARD_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationSetGetDefaultAlphfunctionLinearP
 * @since_tizen     2.4
 * @description     Checks whether GetDefaultAlphaFunction and SetDefaultAlphaFunction is working properly or not as Linear
 */
int UtcDaliAnimationSetGetDefaultAlphfunctionLinearP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_SET_GET_DEFAULT_ALPHFUNCTION_LINEAR_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliAnimationSetGetDefaultAlphfunctionEaseInP
 * @since_tizen     2.4
 * @description     Checks whether GetDefaultAlphaFunction and SetDefaultAlphaFunction is working properly or not as EaseIn
 */

int UtcDaliAnimationSetGetDefaultAlphfunctionEaseInP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_SET_GET_DEFAULT_ALPHFUNCTION_EASEIN_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationStopP
 * @since_tizen     2.4
 * @description     Checks whether the Animation Stop Api is working properly or not
 */
int UtcDaliAnimationStopP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_STOP_P);
  application.MainLoop();
  return test_return_value;
}



/**
 * @testcase        UtcDaliAnimationClearP
 * @since_tizen     2.4
 * @description     Checks whether the Animation Clear Api is working properly or not
 */
int UtcDaliAnimationClearP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_CLEAR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationConstructorP
 * @since_tizen     2.4
 * @description     Checks whether the Animation Pause Api is working properly or not
 */
int UtcDaliAnimationPauseP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_PAUSE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliAnimationConstructorP
 * @since_tizen     2.4
 * @description     Check for default constructor.
 */
int UtcDaliAnimationConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliAnimationNewP
 * @since_tizen     2.4
 * @description     Check for New Method.
 */
int UtcDaliAnimationNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_NEW_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationNewN
 * @since_tizen     2.4
 * @description     Check for New Method with invalid arg.
 */
int UtcDaliAnimationNewN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_NEW_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationCopyConstructorP
 * @since_tizen     2.4
 * @description    Copy Constructor of  an animation  Object handle to Animation New
 */
int UtcDaliAnimationCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_COPYCONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationOperatorAssignmentP
 * @since_tizen     2.4
 * @description    Assignment  of  an animation  Object handle to Animation New
 */
int UtcDaliAnimationOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_OPERATOR_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliAnimationAnimateByBoolP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBy  Api is working properly or not with BOOL
 */
int UtcDaliAnimationAnimateByBoolP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BYBOOL_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliAnimationAnimateByFloatP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBy  Api is working properly or not with FLOAT
 */
int UtcDaliAnimationAnimateByFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BYFLOAT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationTimePeriodAlphaFunctionP
 * @since_tizen     2.4
 * @description     Checks whether the Animation Animate  Api is working properly or not with path and time period and alpha function
 */
int UtcDaliAnimationAnimatePathTimePeriodAlphaFunctionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_PATHTIMEPERIODALPHAFUNCTION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateByIntegerP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBy  Api is working properly or not with Integer
 */
int UtcDaliAnimationAnimateByIntegerP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BYINTEGER_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliAnimationAnimateByVector2P
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBy  Api is working properly or not with Vector2
 */
int UtcDaliAnimationAnimateByVector2P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BYVECTOR2_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateByVector3P
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBy  Api is working properly or not with Vector3
 */
int UtcDaliAnimationAnimateByVector3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BYVECTOR3_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateByVector4P
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBy  Api is working properly or not with Vector4
 */
int UtcDaliAnimationAnimateByVector4P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BYVECTOR4_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimatePathVectorP
 * @since_tizen     2.4
 * @description     Checks whether the Animation Animate  Api is working properly or not with path and vector
 */
int UtcDaliAnimationAnimatePathVectorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_PATHVECTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateBetweenKeyframesAlphafunctionLinearTimePeriodP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBetween  Api is working properly or not with keyframes   and time period and alpha function
 */
int UtcDaliAnimationAnimateBetweenKeyframesAlphafunctionLinearTimePeriodP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_ALPHAFUNCTIONLINEARTIMEPERIOD_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliAnimationAnimateBetweenKeyframesTimePeriodP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBetween  Api is working properly or not with keyframes   and time period
 */
int UtcDaliAnimationAnimateBetweenKeyframesTimePeriodP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_TIMEPERIOD_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateByVector4TimePeriodP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBy  Api is working properly or not with Vector4 and time period
 */
int UtcDaliAnimationAnimateByVector4TimePeriodP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BYVECTOR4TIMEPERIOD_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliAnimationAnimateByVector3TimePeriodP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBy  Api is working properly or not with Vector3 and time period
 */
int UtcDaliAnimationAnimateByVector3TimePeriodP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BYVECTOR3TIMEPERIOD_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateByVector2TimePeriodP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBy  Api is working properly or not with Vector2 and time period
 */
int UtcDaliAnimationAnimateByVector2TimePeriodP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BYVECTOR2TIMEPERIOD_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliAnimationAnimateByFloatTimePeriodP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBy  Api is working properly or not with FLOAT
 */
int UtcDaliAnimationAnimateByFloatTimePeriodP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BYFLOATTIMEPERIOD_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateByVector4TimePeriodAlphaFunctionP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBy  Api is working properly or not with Vector4 and time period
 */
int UtcDaliAnimationAnimateByVector4TimePeriodAlphaFunctionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BYVECTOR4TIMEPERIODALPHAFUNCTION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateByVector4AlphaFunctionP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBy  Api is working properly or not with Vector4 and alpha function
 */
int UtcDaliAnimationAnimateByVector4AlphaFunctionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BYVECTOR4ALPHAFUNCTION_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliAnimationAnimateToVector4P
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateTo  Api is working properly or not with Vector4
 */
int UtcDaliAnimationAnimateToVector4P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_TOVECTOR4_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateToVector3P
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateTo  Api is working properly or not with Vector3
 */
int UtcDaliAnimationAnimateToVector3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_TOVECTOR3_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateToVector2P
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateTo  Api is working properly or not with Vector2
 */
int UtcDaliAnimationAnimateToVector2P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_TOVECTOR2_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateToP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateTo  Api is working properly or not with Vector2
 */
int UtcDaliAnimationAnimateToP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_TO_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateToFloatP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateTo  Api is working properly or not with float
 */
int UtcDaliAnimationAnimateToFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_TOFLOAT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateToVector4TimePeriodP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateTo  Api is working properly or not with Vector4 and time period
 */
int UtcDaliAnimationAnimateToVector4TimePeriodP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_TOVECTOR4TIMEPERIOD_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliAnimationAnimateToVector2TimePeriodP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateTo  Api is working properly or not with Vector2 and time period
 */
int UtcDaliAnimationAnimateToVector2TimePeriodP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_TOVECTOR2TIMEPERIOD_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliAnimationAnimateToVector3TimePeriodP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateTo  Api is working properly or not with Vector3 and time period
 */
int UtcDaliAnimationAnimateToVector3TimePeriodP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_TOVECTOR3TIMEPERIOD_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateToFloatTimePeriodP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateTo  Api is working properly or not with float and time period
 */
int UtcDaliAnimationAnimateToFloatTimePeriodP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_TOFLOATTIMEPERIOD_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateToVector4TimePeriodAlphaFunctionP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateTo  Api is working properly or not with Vector4 and time period and alpha function
 */
int UtcDaliAnimationAnimateToVector4TimePeriodAlphaFunctionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_TOVECTOR4TIMEPERIODALPHAFUNCTION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateToVector2TimePeriodAlphaFunctionP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateTo  Api is working properly or not with Vector2 and time period and alpha function
 */
int UtcDaliAnimationAnimateToVector2TimePeriodAlphaFunctionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_TOVECTOR2TIMEPERIODALPHAFUNCTION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateToVector3TimePeriodAlphaFunctionP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateTo  Api is working properly or not with Vector3 and time period and alpha function
 */
int UtcDaliAnimationAnimateToVector3TimePeriodAlphaFunctionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_TOVECTOR3TIMEPERIODALPHAFUNCTION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateToFloatTimePeriodAlphaFunctionP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateTo  Api is working properly or not with float and time period and alpha function
 */
int UtcDaliAnimationAnimateToFloatTimePeriodAlphaFunctionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_TOFLOATTIMEPERIODALPHAFUNCTION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateToVector3AlphaFunctionP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateTo  Api is working properly or not with Vector3 and Alpha Function EaseOut
 */
int UtcDaliAnimationAnimateToVector3AlphaFunctionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_TOVECTOR3ALPHAFUNCTION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateBetweenActorVisibleP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBetween  Api is working properly or not with Actor Visible
 */
int UtcDaliAnimationAnimateBetweenActorVisibleP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BETWEEN_ACTORVISIBLE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateBetweenActorRotationP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBetween  Api is working properly or not with Actor rotation
 */
int UtcDaliAnimationAnimateBetweenActorRotationP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BETWEEN_ACTORROTATION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateBetweenColorAlphaP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBetween  Api is working properly or not with Actor color_alpha
 */
int UtcDaliAnimationAnimateBetweenColorAlphaP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BETWEEN_COLORALPHA_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimatPathTimePeriodP
 * @since_tizen     2.4
 * @description     Checks whether the Animation Animate  Api is working properly or not with path and time period
 */
int UtcDaliAnimationAnimatPathTimePeriodP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_PATHTIMEPERIOD_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateBetweenKeyframesInterpolationP
 * @since_tizen     2.4
 * @description     Checks whether the Animation Animate  Api is working properly or not with path and alpha function
 */
int UtcDaliAnimationAnimatePathAlphafunctionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_PATHALPHAFUNCTION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateBetweenKeyframesInterpolationP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBetween  Api is working properly or not with keyframes and interpolation
 */
int UtcDaliAnimationAnimateBetweenKeyframesInterpolationP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_INTERPOLATION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateBetweenKeyframesAlphafunctionInterpolationP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBetween  Api is working properly or not with keyframes and interpolation and alpha function linear
 */
int UtcDaliAnimationAnimateBetweenKeyframesAlphafunctionInterpolationP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_ALPHAFUNCTIONINTERPOLATION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateBetweenKeyframesInterpolationWithTimePeriodP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBetween  Api is working properly or not with keyframes and interpolation  and time period
 */
int UtcDaliAnimationAnimateBetweenKeyframesInterpolationWithTimePeriodP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_INTERPOLATIONTIMEPERIOD_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationAnimateBetweenKeyframesInterpolationWithTimePeriodP
 * @since_tizen     2.4
 * @description     Checks whether the Animation AnimateBetween  Api is working properly or not with keyframes and interpolation  and time period and alpha function
 */
int UtcDaliAnimationAnimateBetweenKeyframesInterpolationTimePeriodAlphaFuncP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_ANIMATE_BETWEEN_KEYFRAMES_INTERPOLATIONTIMEPERIODALPHAFUNC_P);
  application.MainLoop();
  return test_return_value;
}

/////////////////////////////////////////////////////////////////////
/**
 * @testcase        UtcDaliAnimationGetLoopingModeP
 * @since_tizen    4.0
 * @description     Checks whether the GetLoopingMode Api is working properly or not
 */
int UtcDaliAnimationGetLoopingModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_GET_LOOPING_MODE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationPlayAfterP
 * @since_tizen    4.0
 * @description     Checks whether the PlayAfter Api is working properly or not
 */
int UtcDaliAnimationPlayAfterP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_PLAY_AFTER_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationPlayAfterN
 * @since_tizen    4.0
 * @description     Checks whether the PlayAfter Api is working properly or not
 */
int UtcDaliAnimationPlayAfterN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_PLAY_AFTER_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationSetLoopingModeP
 * @since_tizen     4.0
 * @description     Checks whether the SetLoopingMode Api is working properly or not
 */
int UtcDaliAnimationSetLoopingModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_SET_LOOPING_MODE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliAnimationSetLoopingModeP2
 * @since_tizen     4.0
 * @description     Checks whether the SetLoopingMode Api is working properly or not
 */
int UtcDaliAnimationSetLoopingModeP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, ANIMATION_SET_LOOPING_MODE_P2);
  application.MainLoop();
  return test_return_value;
}
