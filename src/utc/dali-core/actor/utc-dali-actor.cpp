#include "utc-dali-actor-impl.h"

//& set: Image

/**
 * @function            utc_Dali_Actor_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Actor_startup(void)
{
  test_return_value = 0;
  gRenderCount = 0;
}

/**
 * @function            utc_Dali_Actor_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Actor_cleanup(void)
{

}

namespace
{
  enum TEST_CASES_LIST_ACTOR
  {
    ACTOR_DOWNCAST_P,
    ACTOR_GET_ID_P,
    ACTOR_GET_CHILD_COUNT_P,
    ACTOR_SET_NAME_P,
    ACTOR_GET_NAME_P,
    ACTOR_SET_DRAWMODE_P,
    ACTOR_GET_DRAWMODE_P,
    ACTOR_GET_CHILD_AT_P,
    ACTOR_GET_PARENT_P,
    ACTOR_FIND_CHILD_BY_NAME_P,
    ACTOR_FIND_CHILD_BY_ID_P,
    ACTOR_UNPARENT_P,
    ACTOR_UNPARENT_RESET_P,
    ACTOR_ADD_P,
    ACTOR_SET_KEYBOARD_FOCUSABLE_P,
    ACTOR_IS_KEYBOARD_FOCUSABLE_P,
    ACTOR_SET_VISIBLE_P,
    ACTOR_IS_VISIBLE_P,
    ACTOR_SET_XYZ_P,
    ACTOR_ON_STAGE_P,
    ACTOR_GET_LAYER_P,
    ACTOR_IS_LAYER_P,
    ACTOR_IS_ROOT_P,
    ACTOR_ON_STAGE_SIGNAL_P,
    ACTOR_OFF_STAGE_SIGNAL_P,
    ACTOR_SET_ANCHOR_POINT_P,
    ACTOR_GET_CURRENT_ANCHOR_POINT_P,
    ACTOR_GET_CURRENT_WORLD_COLOR_P,
    ACTOR_GET_CURRENT_COLOR_P,
    ACTOR_SET_COLOR_P,
    ACTOR_SET_COLOR_MODE_P,
    ACTOR_GET_COLOR_MODE_P,
    ACTOR_SET_OPACITY_P,
    ACTOR_GET_CURRENT_OPACITY_P,
    ACTOR_SET_PARENT_ORIGIN_P,
    ACTOR_GET_CURRENT_PARENT_ORIGIN_P,
    ACTOR_GET_CURRENT_WORLD_POSITION_P,
    ACTOR_SET_POSITION_P,
    ACTOR_SET_POSITION_P2,
    ACTOR_SET_POSITION_P3,
    ACTOR_GET_CURRENT_POSITION_P,
    ACTOR_GET_CURRENT_POSITION_P2,
    ACTOR_GET_CURRENT_POSITION_P3,
    ACTOR_GET_CURRENT_WORLD_ORIENTATION_P,
    ACTOR_IS_ORIENTATION_INHERITED_P,
    ACTOR_SET_ORIENTATION_P,
    ACTOR_SET_ORIENTATION_P2,
    ACTOR_SET_ORIENTATION_P3,
    ACTOR_SET_INHERIT_ORIENTATION_P,
    ACTOR_GET_CURRENT_ORIENTATION_P,
    ACTOR_SET_INHERIT_SCALE_P,
    ACTOR_IS_SCALE_INHERITED_P,
    ACTOR_SET_SCALE_P,
    ACTOR_SET_SCALE_P2,
    ACTOR_SET_SCALE_P3,
    ACTOR_SCALE_BY_P,
    ACTOR_GET_CURRENT_WORLD_SCALE_P,
    ACTOR_GET_CURRENT_WORLD_MATRIX_P,
    ACTOR_SET_SENSITIVE_P,
    ACTOR_IS_SENSITIVE_P,
    ACTOR_SET_SIZE_P,
    ACTOR_SET_SIZE_P2,
    ACTOR_SET_SIZE_P3,
    ACTOR_SET_SIZE_P4,
    ACTOR_GET_CURRENT_SIZE_P,
    ACTOR_SET_PADDING_P,
    ACTOR_GET_PADDING_P,
    ACTOR_TRANSLATE_BY_P,
    ACTOR_SET_MAXIMUM_SIZE_P,
    ACTOR_GET_MAXIMUM_SIZE_P,
    ACTOR_GET_MINIMUM_SIZE_P,
    ACTOR_SET_MINIMUM_SIZE_P,
    ACTOR_ON_RELAYOUT_SIGNAL_P,
    ACTOR_SET_RESIZE_POLICY_P,
    ACTOR_GET_HEIGHT_FOR_WIDTH_P,
    ACTOR_GET_WIDTH_FOR_HEIGHT_P,
    ACTOR_SET_SIZE_MODE_FACTOR_P,
    ACTOR_GET_SIZE_MODE_FACTOR_P,
    ACTOR_SET_SIZE_SCALE_POLICY_P,
    ACTOR_GET_SIZE_SCALE_POLICY_P,
    ACTOR_ROTATE_BY_P,
    ACTOR_ROTATE_BY_P2,
    ACTOR_GET_NATURAL_SIZE_P,
    ACTOR_RESIZE_POLICY_P,
    ACTOR_OPERATOR_ASSIGNMENT_P,
    ACTOR_GET_RELAYOUT_SIZE_P,
    ACTOR_CONSTRUCTOR_P,
    ACTOR_COPY_CONSTRUCTOR_P,
    ACTOR_NEW_P,
    ACTOR_GET_HIERARCHY_DEPTH_P,
    ACTOR_SET_LEAVE_REQUIRED_P,
    ACTOR_SET_LEAVE_REQUIRED_P2,
    ACTOR_GET_LEAVE_REQUIRED_P,
    ACTOR_GET_LEAVE_REQUIRED_P2,
    ACTOR_GET_TARGET_SIZE_P,
    ACTOR_SCREEN_TO_LOCAL_P,
    ACTOR_REMOVE_P,
    ACTOR_SET_INHERIT_POSITION_P,
    ACTOR_IS_POSITION_INHERITED_P,
    ACTOR_REMOVE_RENDERER_N,
    ACTOR_GET_RENDERER_COUNT_N,
    ACTOR_LAYOUT_DIRECTION_PROPERTY,
    ACTOR_PROPERTIES,
    ACTOR_RAISE_LOWER,
    ACTOR_LOWER_BELOW,
    ACTOR_RAISE_TO_TOP_LOWER_TO_BOTTOM,
    ACTOR_RAISE_ABOVE,
    ACTOR_RAISE_ABOVE_ACTOR_AND_TARGET_THE_SAME,
  };

  struct Actor_TestApp : public ConnectionTracker
  {
    Actor_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Actor_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Actor_TestApp::Tick );
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
        case ACTOR_DOWNCAST_P:
          ActorDowncastP();
          break;

        case ACTOR_GET_ID_P:
          ActorGetIdP();
          break;

        case ACTOR_GET_CHILD_COUNT_P:
          ActorGetChildCountP();
          break;

        case ACTOR_SET_NAME_P:
          ActorSetNameP();
          break;

        case ACTOR_GET_NAME_P:
          ActorGetNameP();
          break;

        case ACTOR_SET_DRAWMODE_P:
          ActorSetDrawmodeP();
          break;

        case ACTOR_GET_DRAWMODE_P:
          ActorGetDrawmodeP();
          break;

        case ACTOR_GET_CHILD_AT_P:
          ActorGetChildAtP();
          break;

        case ACTOR_GET_PARENT_P:
          ActorGetParentP();
          break;

        case ACTOR_FIND_CHILD_BY_NAME_P:
          ActorFindChildByNameP();
          break;

        case ACTOR_FIND_CHILD_BY_ID_P:
          ActorFindChildByIdP();
          break;

        case ACTOR_UNPARENT_P:
          ActorUnparentP();
          break;

        case ACTOR_UNPARENT_RESET_P:
          ActorUnparentAndResetP();
          break;

        case ACTOR_ADD_P:
          ActorAddP();
          break;

        case ACTOR_SET_KEYBOARD_FOCUSABLE_P:
          ActorSetKeyboardFocusableP();
          break;

        case ACTOR_IS_KEYBOARD_FOCUSABLE_P:
          ActorIsKeyboardFocusableP();
          break;

        case ACTOR_SET_VISIBLE_P:
          ActorSetVisibleP();
          break;

        case ACTOR_IS_VISIBLE_P:
          ActorIsVisibleP();
          break;

        case ACTOR_SET_XYZ_P:
          ActorSetXYZP();
          break;

        case ACTOR_ON_STAGE_P:
          ActorOnStageP();
          break;

        case ACTOR_GET_LAYER_P:
          ActorGetLayerP();
          break;

        case ACTOR_IS_LAYER_P:
          ActorIsLayerP();
          break;

        case ACTOR_IS_ROOT_P:
          ActorIsRootP();
          break;

        case ACTOR_ON_STAGE_SIGNAL_P:
          ActorOnStageSignalP();
          break;

        case ACTOR_OFF_STAGE_SIGNAL_P:
          ActorOffStageSignalP();
          break;

        case ACTOR_SET_ANCHOR_POINT_P:
          ActorSetAnchorPointP();
          break;

        case ACTOR_GET_CURRENT_ANCHOR_POINT_P:
          ActorGetCurrentAnchorPointP();
          break;

        case ACTOR_GET_CURRENT_WORLD_COLOR_P:
          ActorGetCurrentWorldColorP();
          break;

        case ACTOR_GET_CURRENT_COLOR_P:
          ActorGetCurrentColorP();
          break;

        case ACTOR_SET_COLOR_P:
          ActorSetColorP();
          break;

        case ACTOR_SET_COLOR_MODE_P:
          ActorSetColorModeP();
          break;

        case ACTOR_GET_COLOR_MODE_P:
          ActorGetColorModeP();
          break;

        case ACTOR_SET_OPACITY_P:
          ActorSetOpacityP();
          break;

        case ACTOR_GET_CURRENT_OPACITY_P:
          ActorGetCurrentOpacityP();
          break;

        case ACTOR_SET_PARENT_ORIGIN_P:
          ActorSetParentOriginP();
          break;

        case ACTOR_GET_CURRENT_PARENT_ORIGIN_P:
          ActorGetCurrentParentOriginP();
          break;

        case ACTOR_GET_CURRENT_WORLD_POSITION_P:
          ActorGetCurrentWorldPositionP();
          break;

        case ACTOR_SET_POSITION_P:
          ActorSetPositionP();
          break;

        case ACTOR_SET_POSITION_P2:
          ActorSetPositionP2();
          break;

        case ACTOR_SET_POSITION_P3:
          ActorSetPositionP3();
          break;

        case ACTOR_GET_CURRENT_POSITION_P:
          ActorGetCurrentPositionP();
          break;

        case ACTOR_GET_CURRENT_POSITION_P2:
          ActorGetCurrentPositionP2();
          break;

        case ACTOR_GET_CURRENT_POSITION_P3:
          ActorGetCurrentPositionP3();
          break;

        case ACTOR_GET_CURRENT_WORLD_ORIENTATION_P:
          ActorGetCurrentWorldOrientationP();
          break;

        case ACTOR_IS_ORIENTATION_INHERITED_P:
          ActorIsOrientationInheritedP();
          break;

        case ACTOR_SET_ORIENTATION_P:
          ActorSetOrientationP();
          break;

        case ACTOR_SET_ORIENTATION_P2:
          ActorSetOrientationP2();
          break;

        case ACTOR_SET_ORIENTATION_P3:
          ActorSetOrientationP3();
          break;

        case ACTOR_SET_INHERIT_ORIENTATION_P:
          ActorSetInheritOrientationP();
          break;

        case ACTOR_GET_CURRENT_ORIENTATION_P:
          ActorGetCurrentOrientationP();
          break;

        case ACTOR_SET_INHERIT_SCALE_P:
          ActorSetInheritScaleP();
          break;

        case ACTOR_IS_SCALE_INHERITED_P:
          ActorIsScaleInheritedP();
          break;

        case ACTOR_SET_SCALE_P:
          ActorSetScaleP();
          break;

        case ACTOR_SET_SCALE_P2:
          ActorSetScaleP2();
          break;

        case ACTOR_SET_SCALE_P3:
          ActorSetScaleP3();
          break;

        case ACTOR_SCALE_BY_P:
          ActorScaleByP();
          break;

        case ACTOR_GET_CURRENT_WORLD_SCALE_P:
          ActorGetCurrentWorldScaleP();
          break;

        case ACTOR_GET_CURRENT_WORLD_MATRIX_P:
          ActorGetCurrentWorldMatrixP();
          break;

        case ACTOR_SET_SENSITIVE_P:
          ActorSetSensitiveP();
          break;

        case ACTOR_IS_SENSITIVE_P:
          ActorIsSensitiveP();
          break;

        case ACTOR_SET_SIZE_P:
          ActorSetSizeP();
          break;

        case ACTOR_SET_SIZE_P2:
          ActorSetSizeP2();
          break;

        case ACTOR_SET_SIZE_P3:
          ActorSetSizeP3();
          break;

        case ACTOR_SET_SIZE_P4:
          ActorSetSizeP4();
          break;

        case ACTOR_GET_CURRENT_SIZE_P:
          ActorGetCurrentSizeP();
          break;

        case ACTOR_SET_PADDING_P:
          ActorSetPaddingP();
          break;

        case ACTOR_GET_PADDING_P:
          ActorGetPaddingP();
          break;

        case ACTOR_TRANSLATE_BY_P:
          ActorTranslateByP();
          break;

        case ACTOR_SET_MAXIMUM_SIZE_P:
          ActorSetMaximumSizeP();
          break;

        case ACTOR_GET_MAXIMUM_SIZE_P:
          ActorGetMaximumSizeP();
          break;

        case ACTOR_GET_MINIMUM_SIZE_P:
          ActorGetMinimumSizeP();
          break;

        case ACTOR_SET_MINIMUM_SIZE_P:
          ActorSetMinimumSizeP();
          break;

        case ACTOR_ON_RELAYOUT_SIGNAL_P:
          ActorOnRelayoutSignalP();
          break;

        case ACTOR_SET_RESIZE_POLICY_P:
          ActorSetResizePolicyP();
          break;

        case ACTOR_GET_HEIGHT_FOR_WIDTH_P:
          ActorGetHeightForWidthP();
          break;

        case ACTOR_GET_WIDTH_FOR_HEIGHT_P:
          ActorGetWidthForHeightP();
          break;

        case ACTOR_SET_SIZE_MODE_FACTOR_P:
          ActorSetSizeModeFactorP();
          break;

        case ACTOR_GET_SIZE_MODE_FACTOR_P:
          ActorGetSizeModeFactorP();
          break;

        case ACTOR_SET_SIZE_SCALE_POLICY_P:
          ActorSetSizeScalePolicyP();
          break;

        case ACTOR_GET_SIZE_SCALE_POLICY_P:
          ActorGetSizeScalePolicyP();
          break;

        case ACTOR_ROTATE_BY_P:
          ActorRotateByP();
          break;

        case ACTOR_ROTATE_BY_P2:
          ActorRotateByP2();
          break;

        case ACTOR_GET_NATURAL_SIZE_P:
          ActorGetNaturalSizeP();
          break;

        case ACTOR_RESIZE_POLICY_P:
          ActorResizePolicyP();
          break;

        case ACTOR_OPERATOR_ASSIGNMENT_P:
          ActorOperatorAssignmentP();
          break;

        case ACTOR_GET_RELAYOUT_SIZE_P:
          ActorGetRelayoutSizeP();
          break;

        case ACTOR_CONSTRUCTOR_P:
          ActorConstructorP();
          break;

        case ACTOR_COPY_CONSTRUCTOR_P:
          ActorCopyConstructorP();
          break;

        case ACTOR_NEW_P:
          ActorNewP();
          break;

        case ACTOR_GET_HIERARCHY_DEPTH_P:
          ActorGetHierarchyDepthP();
          break;

        case ACTOR_SET_LEAVE_REQUIRED_P:
          ActorSetLeaveRequiredP();
          break;

        case ACTOR_SET_LEAVE_REQUIRED_P2:
          ActorSetLeaveRequiredP2();
          break;

        case ACTOR_GET_LEAVE_REQUIRED_P:
          ActorGetLeaveRequiredP();
          break;

        case ACTOR_GET_LEAVE_REQUIRED_P2:
          ActorGetLeaveRequiredP2();
          break;

        case ACTOR_GET_TARGET_SIZE_P:
          ActorGetTaregetSizeP();
          break;

        case ACTOR_SCREEN_TO_LOCAL_P:
          ActorScreenToLocalP();
          break;

        case ACTOR_REMOVE_P:
          ActorRemoveP();
          break;

        case ACTOR_SET_INHERIT_POSITION_P:
          ActorSetInheritPositionP();
          break;

        case ACTOR_IS_POSITION_INHERITED_P:
          ActorIsPositionInheritedP();
          break;

        case ACTOR_REMOVE_RENDERER_N:
          ActorRemoveRendererN();
          break;

        case ACTOR_GET_RENDERER_COUNT_N:
          ActorGetRendererCountN();
          break;

        case ACTOR_LAYOUT_DIRECTION_PROPERTY:
          ActorLayoutDirectionPropertyP();
          break;

        case ACTOR_PROPERTIES:
          ActorPropertiesP();
          break;

        case ACTOR_RAISE_LOWER:
          ActorRaiseLowerP();
          break;

        case ACTOR_LOWER_BELOW:
          ActorLowerBelowP();
          break;

        case ACTOR_RAISE_TO_TOP_LOWER_TO_BOTTOM:
          ActorRaiseToTopLowerToBottomP();
          break;

        case ACTOR_RAISE_ABOVE:
          ActorRaiseAboveP();
          break;

        case ACTOR_RAISE_ABOVE_ACTOR_AND_TARGET_THE_SAME:
          ActorRaiseAboveActorAndTargetTheSameN();
          break;
      }
    }


    void VerdictTest()
    {
      switch (mTestCase)
      {
        case ACTOR_SET_XYZ_P:
          switch (gRenderCount)
          {
            case 0:
              VTActorCheckXPosition();
              gRenderCount++;
              break;

            case 1:
              VTActorCheckXYPosition();
              gRenderCount++;
              break;

            case 2:
              VTActorCheckXYZPositionFinal();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ACTOR_SET_COLOR_P:
          VTActorCheckColor();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ACTOR_GET_CURRENT_COLOR_P:
          VTActorCheckColor();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ACTOR_GET_RELAYOUT_SIZE_P:
          VTActorCheckRelayoutSize();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ACTOR_ROTATE_BY_P:
          switch (gRenderCount)
          {
            case 0:
              VTActorRotationCheck001();
              gRenderCount++;
              break;

            case 1:
              VTActorRotationCheck002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ACTOR_ROTATE_BY_P2:
          switch (gRenderCount)
          {
            case 0:
              VTActorRotationCheck001();
              gRenderCount++;
              break;

            case 1:
              VTActorRotationCheck002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ACTOR_ON_RELAYOUT_SIGNAL_P:
          switch (gRenderCount)
          {
            case 0:
              VTActorCheckRelayoutSignal001();
              gRenderCount++;
              break;

            case 1:
              VTActorCheckRelayoutSignal002();
              gRenderCount++;
              break;

            case 2:
              VTActorCheckRelayoutSignal003();
              gRenderCount++;
              break;

            case 3:
              VTActorCheckRelayoutSignal004();
              gRenderCount++;
              break;

            case 4:
              VTActorCheckRelayoutSignal005();
              gRenderCount++;
              break;

            case 5:
              VTActorCheckRelayoutSignal006();
              gRenderCount++;
              break;

            case 6:
              VTActorCheckRelayoutSignal007();
              gRenderCount++;
              break;

            case 7:
              VTActorCheckRelayoutSignal008();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ACTOR_SET_RESIZE_POLICY_P:
          switch (gRenderCount)
          {
            case 0:
              VTActorCheckRelayoutSignal001();
              gRenderCount++;
              break;

            case 1:
              VTActorCheckRelayoutSignal002();
              gRenderCount++;
              break;

            case 2:
              VTActorCheckRelayoutSignal003();
              gRenderCount++;
              break;

            case 3:
              VTActorCheckRelayoutSignal004();
              gRenderCount++;
              break;

            case 4:
              VTActorCheckRelayoutSignal005();
              gRenderCount++;
              break;

            case 5:
              VTActorCheckRelayoutSignal006();
              gRenderCount++;
              break;

            case 6:
              VTActorCheckRelayoutSignal007();
              gRenderCount++;
              break;

            case 7:
              VTActorCheckRelayoutSignal008();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ACTOR_TRANSLATE_BY_P:
          switch (gRenderCount)
          {
            case 0:
              VTActorCheckTranslation001();
              gRenderCount++;
              break;

            case 1:
              VTActorCheckTranslation002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ACTOR_GET_CURRENT_ORIENTATION_P:
          VTActorChechCurrentOrientation001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ACTOR_SET_ORIENTATION_P:
          VTActorChechCurrentOrientation001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ACTOR_SET_ORIENTATION_P2:
          VTActorChechCurrentOrientation002();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ACTOR_SET_ORIENTATION_P3:
          VTActorChechCurrentOrientation003();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ACTOR_SET_POSITION_P:
          VTActorCheckCurrentPosition001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ACTOR_SET_POSITION_P2:
          VTActorCheckCurrentPosition002();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ACTOR_SET_POSITION_P3:
          VTActorCheckCurrentPosition003();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ACTOR_GET_CURRENT_POSITION_P:
          VTActorCheckCurrentPosition001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ACTOR_GET_CURRENT_POSITION_P2:
          VTActorCheckCurrentPosition002();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ACTOR_GET_CURRENT_POSITION_P3:
          VTActorCheckCurrentPosition003();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ACTOR_SET_SIZE_P:
          VTActorCheckCurrentSize001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ACTOR_SET_SIZE_P2:
          VTActorCheckCurrentSize002();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ACTOR_SET_SIZE_P3:
          VTActorCheckCurrentSize003();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ACTOR_SET_SIZE_P4:
          VTActorCheckCurrentSize004();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ACTOR_GET_CURRENT_SIZE_P:
          VTActorCheckCurrentSize001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ACTOR_SET_SCALE_P:
          switch (gRenderCount)
          {
            case 0:
              VTActorCheckScaleBy001();
              gRenderCount++;
              break;

            case 1:
              VTActorCheckScaleBy002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ACTOR_SCALE_BY_P:
          switch (gRenderCount)
          {
            case 0:
              VTActorCheckScaleBy001();
              gRenderCount++;
              break;

            case 1:
              VTActorCheckScaleBy002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ACTOR_GET_CURRENT_WORLD_COLOR_P:
          switch (gRenderCount)
          {
            case 0:
              VTActorCheckWorldOwnColor001();
              gRenderCount++;
              break;

            case 1:
              VTActorCheckWorldOwnColor002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ACTOR_SET_COLOR_MODE_P:
          switch (gRenderCount)
          {
            case 0:
              VTActorCheckWorldOwnColor001();
              gRenderCount++;
              break;

            case 1:
              VTActorCheckWorldOwnColor002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ACTOR_GET_COLOR_MODE_P:
          switch (gRenderCount)
          {
            case 0:
              VTActorCheckWorldOwnColor001();
              gRenderCount++;
              break;

            case 1:
              VTActorCheckWorldOwnColor002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ACTOR_GET_CURRENT_WORLD_POSITION_P:
          VTActorGetWorldPositionParent001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ACTOR_SET_INHERIT_SCALE_P:
          switch (gRenderCount)
          {
            case 0:
              VTActorCheckWorldScale001();
              gRenderCount++;
              break;

            case 1:
              VTActorCheckWorldScale002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ACTOR_GET_CURRENT_WORLD_SCALE_P:
          switch (gRenderCount)
          {
            case 0:
              VTActorCheckWorldScale001();
              gRenderCount++;
              break;

            case 1:
              VTActorCheckWorldScale002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ACTOR_IS_SCALE_INHERITED_P:
          switch (gRenderCount)
          {
            case 0:
              VTActorCheckWorldScale001();
              gRenderCount++;
              break;

            case 1:
              VTActorCheckWorldScale002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ACTOR_IS_ORIENTATION_INHERITED_P:
          switch (gRenderCount)
          {
            case 0:
              VTActorCheckWorldOrientation001();
              gRenderCount++;
              break;

            case 1:
              VTActorCheckWorldOrientation002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ACTOR_SET_INHERIT_ORIENTATION_P:
          switch (gRenderCount)
          {
            case 0:
              VTActorCheckWorldOrientation001();
              gRenderCount++;
              break;

            case 1:
              VTActorCheckWorldOrientation002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ACTOR_GET_CURRENT_WORLD_ORIENTATION_P:
          switch (gRenderCount)
          {
            case 0:
              VTActorCheckWorldOrientation001();
              gRenderCount++;
              break;

            case 1:
              VTActorCheckWorldOrientation002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ACTOR_SCREEN_TO_LOCAL_P:
          VTActorCheckScreenToLocal001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        default:
          mTimer.Stop();
          mApplication.Quit();
          break;
      }
    }

    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };
} // unnamed namespace


/**
 * @testcase           UtcDaliActorNewP
 * @since_tizen        2.4
 * @description        check if New api works or not.
 */

int UtcDaliActorNewP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_NEW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorDowncastP
 * @since_tizen        2.4
 * @description        check if DownCast api works or not.
 */

int UtcDaliActorDowncastP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetIdP
 * @since_tizen        2.4
 * @description        check if GetId api works or not.
 */

int UtcDaliActorGetIdP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_ID_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetChildCountP
 * @since_tizen        2.4
 * @description        check if GetChildCount api works or not.
 */

int UtcDaliActorGetChildCountP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_CHILD_COUNT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetNameP
 * @since_tizen        2.4
 * @description        check if SetName api works or not.
 */

int UtcDaliActorSetNameP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_NAME_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetNameP
 * @since_tizen        2.4
 * @description        check if GetName api works or not.
 */

int UtcDaliActorGetNameP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_NAME_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetDrawmodeP
 * @since_tizen        2.4
 * @description        check if SetDrawmode api works or not.
 */

int UtcDaliActorSetDrawmodeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_DRAWMODE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetDrawmodeP
 * @since_tizen        2.4
 * @description        check if GetDrawmode api works or not.
 */

int UtcDaliActorGetDrawmodeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_DRAWMODE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetChildAtP
 * @since_tizen        2.4
 * @description        check if GetChildAt api works or not.
 */

int UtcDaliActorGetChildAtP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_CHILD_AT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetParentP
 * @since_tizen        2.4
 * @description        check if GetParent api works or not.
 */

int UtcDaliActorGetParentP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_PARENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorFindChildByNameP
 * @since_tizen        2.4
 * @description        check if FindChildByName api works or not.
 */

int UtcDaliActorFindChildByNameP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_FIND_CHILD_BY_NAME_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorFindChildByIdP
 * @since_tizen        2.4
 * @description        check if FindChildById api works or not.
 */

int UtcDaliActorFindChildByIdP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_FIND_CHILD_BY_ID_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorUnparentP
 * @since_tizen        2.4
 * @description        check if Unparent api works or not.
 */

int UtcDaliActorUnparentP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_UNPARENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorUnparentAndResetP
 * @since_tizen        2.4
 * @description        check if UnparentAndReset api works or not.
 */

int UtcDaliActorUnparentAndResetP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_UNPARENT_RESET_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorAddP
 * @since_tizen        2.4
 * @description        check if Add api works or not.
 */

int UtcDaliActorAddP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_ADD_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetKeyboardFocusableP
 * @since_tizen        2.4
 * @description        check if SetKeyboardFocusable api works or not.
 */

int UtcDaliActorSetKeyboardFocusableP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_KEYBOARD_FOCUSABLE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorIsKeyboardFocusableP
 * @since_tizen        2.4
 * @description        check if IsKeyboardFocusable api works or not.
 */

int UtcDaliActorIsKeyboardFocusableP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_IS_KEYBOARD_FOCUSABLE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetVisibleP
 * @since_tizen        2.4
 * @description        check if SetVisible api works or not.
 */

int UtcDaliActorSetVisibleP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_VISIBLE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorIsVisibleP
 * @since_tizen        2.4
 * @description        check if IsVisible api works or not.
 */

int UtcDaliActorIsVisibleP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_IS_VISIBLE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetXYZP
 * @since_tizen        2.4
 * @description        check if SetXYZ api works or not.
 */

int UtcDaliActorSetXYZP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_XYZ_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorOnStageP
 * @since_tizen        2.4
 * @description        check if OnStage api works or not.
 */

int UtcDaliActorOnStageP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_ON_STAGE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetLayerP
 * @since_tizen        2.4
 * @description        check if GetLayer api works or not.
 */

int UtcDaliActorGetLayerP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_LAYER_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorIsLayerP
 * @since_tizen        2.4
 * @description        check if IsLayer api works or not.
 */

int UtcDaliActorIsLayerP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_IS_LAYER_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorIsRootP
 * @since_tizen        2.4
 * @description        check if IsRoot api works or not.
 */

int UtcDaliActorIsRootP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_IS_ROOT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorOnStageSignalP
 * @since_tizen        2.4
 * @description        check if OnStageSignal api works or not.
 */

int UtcDaliActorOnStageSignalP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_ON_STAGE_SIGNAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorOffStageSignalP
 * @since_tizen        2.4
 * @description        check if OffStageSignal api works or not.
 */

int UtcDaliActorOffStageSignalP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_OFF_STAGE_SIGNAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetAnchorPointP
 * @since_tizen        2.4
 * @description        check if SetAnchorPoint api works or not.
 */

int UtcDaliActorSetAnchorPointP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_ANCHOR_POINT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetCurrentAnchorPointP
 * @since_tizen        2.4
 * @description        check if GetCurrentAnchorPoint api works or not.
 */

int UtcDaliActorGetCurrentAnchorPointP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_CURRENT_ANCHOR_POINT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetCurrentWorldColorP
 * @since_tizen        2.4
 * @description        check if GetCurrentWorldColor api works or not.
 */

int UtcDaliActorGetCurrentWorldColorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_CURRENT_WORLD_COLOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetCurrentColorP
 * @since_tizen        2.4
 * @description        check if GetCurrentColor api works or not.
 */

int UtcDaliActorGetCurrentColorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_CURRENT_COLOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetColorP
 * @since_tizen        2.4
 * @description        check if SetColor api works or not.
 */

int UtcDaliActorSetColorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_COLOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetColorModeP
 * @since_tizen        2.4
 * @description        check if SetColorMode api works or not.
 */

int UtcDaliActorSetColorModeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_COLOR_MODE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetColorModeP
 * @since_tizen        2.4
 * @description        check if GetColorMode api works or not.
 */

int UtcDaliActorGetColorModeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_COLOR_MODE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetOpacityP
 * @since_tizen        2.4
 * @description        check if SetOpacity api works or not.
 */

int UtcDaliActorSetOpacityP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_OPACITY_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetCurrentOpacityP
 * @since_tizen        2.4
 * @description        check if GetCurrentOpacity api works or not.
 */

int UtcDaliActorGetCurrentOpacityP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_CURRENT_OPACITY_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetParentOriginP
 * @since_tizen        2.4
 * @description        check if SetParentOrigin api works or not.
 */

int UtcDaliActorSetParentOriginP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_PARENT_ORIGIN_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetCurrentParentOriginP
 * @since_tizen        2.4
 * @description        check if GetCurrentParentOrigin api works or not.
 */

int UtcDaliActorGetCurrentParentOriginP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_CURRENT_PARENT_ORIGIN_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetCurrentWorldPositionP
 * @since_tizen        2.4
 * @description        check if GetCurrentWorldPosition api works or not.
 */

int UtcDaliActorGetCurrentWorldPositionP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_CURRENT_WORLD_POSITION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetPositionP
 * @since_tizen        2.4
 * @description        check if SetPosition api works or not.
 */

int UtcDaliActorSetPositionP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_POSITION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetPositionP2
 * @since_tizen        2.4
 * @description        check if SetPosition api works or not.
 */

int UtcDaliActorSetPositionP2(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_POSITION_P2 );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetPositionP3
 * @since_tizen        2.4
 * @description        check if SetPosition api works or not.
 */

int UtcDaliActorSetPositionP3(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_POSITION_P3 );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetCurrentPositionP
 * @since_tizen        2.4
 * @description        check if GetCurrentPosition api works or not.
 */

int UtcDaliActorGetCurrentPositionP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_CURRENT_POSITION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetCurrentPositionP2
 * @since_tizen        2.4
 * @description        check if GetCurrentPosition api works or not.
 */

int UtcDaliActorGetCurrentPositionP2(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_CURRENT_POSITION_P2 );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetCurrentPositionP3
 * @since_tizen        2.4
 * @description        check if GetCurrentPosition api works or not.
 */

int UtcDaliActorGetCurrentPositionP3(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_CURRENT_POSITION_P3 );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetCurrentWorldOrientationP
 * @since_tizen        2.4
 * @description        check if GetCurrentWorldOrientation api works or not.
 */

int UtcDaliActorGetCurrentWorldOrientationP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_CURRENT_WORLD_ORIENTATION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorIsOrientationInheritedP
 * @since_tizen        2.4
 * @description        check if IsOrientationInherited api works or not.
 */

int UtcDaliActorIsOrientationInheritedP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_IS_ORIENTATION_INHERITED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetOrientationP
 * @since_tizen        2.4
 * @description        check if SetOrientation api works or not.
 */

int UtcDaliActorSetOrientationP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_ORIENTATION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetOrientationP2
 * @since_tizen        2.4
 * @description        check if SetOrientation api works or not.
 */

int UtcDaliActorSetOrientationP2(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_ORIENTATION_P2 );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetOrientationP3
 * @since_tizen        2.4
 * @description        check if SetOrientation api works or not.
 */

int UtcDaliActorSetOrientationP3(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_ORIENTATION_P3 );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetInheritOrientationP
 * @since_tizen        2.4
 * @description        check if SetInheritOrientation api works or not.
 */

int UtcDaliActorSetInheritOrientationP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_INHERIT_ORIENTATION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetCurrentOrientationP
 * @since_tizen        2.4
 * @description        check if GetCurrentOrientation api works or not.
 */

int UtcDaliActorGetCurrentOrientationP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_CURRENT_ORIENTATION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetInheritScaleP
 * @since_tizen        2.4
 * @description        check if SetInheritScale api works or not.
 */

int UtcDaliActorSetInheritScaleP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_INHERIT_SCALE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorIsScaleInheritedP
 * @since_tizen        2.4
 * @description        check if IsScaleInherited api works or not.
 */

int UtcDaliActorIsScaleInheritedP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_IS_SCALE_INHERITED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetScaleP
 * @since_tizen        2.4
 * @description        check if SetScale api works or not.
 */

int UtcDaliActorSetScaleP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_SCALE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetScaleP2
 * @since_tizen        2.4
 * @description        check if SetScale api works or not.
 */

int UtcDaliActorSetScaleP2(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_SCALE_P2 );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetScaleP3
 * @since_tizen        2.4
 * @description        check if SetScale api works or not.
 */

int UtcDaliActorSetScaleP3(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_SCALE_P3 );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorScaleByP
 * @since_tizen        2.4
 * @description        check if ScaleBy api works or not.
 */

int UtcDaliActorScaleByP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SCALE_BY_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetCurrentWorldScaleP
 * @since_tizen        2.4
 * @description        check if GetCurrentWorldScale api works or not.
 */

int UtcDaliActorGetCurrentWorldScaleP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_CURRENT_WORLD_SCALE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetCurrentWorldMatrixP
 * @since_tizen        2.4
 * @description        check if GetCurrentWorldMatrix api works or not.
 */

int UtcDaliActorGetCurrentWorldMatrixP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_CURRENT_WORLD_MATRIX_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetSensitiveP
 * @since_tizen        2.4
 * @description        check if SetSensitive api works or not.
 */

int UtcDaliActorSetSensitiveP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_SENSITIVE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorIsSensitiveP
 * @since_tizen        2.4
 * @description        check if IsSensitive api works or not.
 */

int UtcDaliActorIsSensitiveP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_IS_SENSITIVE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetSizeP
 * @since_tizen        2.4
 * @description        check if SetSize api works or not.
 */

int UtcDaliActorSetSizeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_SIZE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetSizeP2
 * @since_tizen        2.4
 * @description        check if SetSize api works or not.
 */

int UtcDaliActorSetSizeP2(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_SIZE_P2 );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetSizeP3
 * @since_tizen        2.4
 * @description        check if SetSize api works or not.
 */

int UtcDaliActorSetSizeP3(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_SIZE_P3 );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetSizeP4
 * @since_tizen        2.4
 * @description        check if SetSize api works or not.
 */

int UtcDaliActorSetSizeP4(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_SIZE_P4 );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetCurrentSizeP
 * @since_tizen        2.4
 * @description        check if GetCurrentSize api works or not.
 */

int UtcDaliActorGetCurrentSizeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_CURRENT_SIZE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetPaddingP
 * @since_tizen        2.4
 * @description        check if SetPadding api works or not.
 */

int UtcDaliActorSetPaddingP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_PADDING_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetPaddingP
 * @since_tizen        2.4
 * @description        check if GetPadding api works or not.
 */

int UtcDaliActorGetPaddingP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_PADDING_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorTranslateByP
 * @since_tizen        2.4
 * @description        check if TranslateBy api works or not.
 */

int UtcDaliActorTranslateByP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_TRANSLATE_BY_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetMaximumSizeP
 * @since_tizen        2.4
 * @description        check if SetMaximumSize api works or not.
 */

int UtcDaliActorSetMaximumSizeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_MAXIMUM_SIZE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetMaximumSizeP
 * @since_tizen        2.4
 * @description        check if GetMaximumSize api works or not.
 */

int UtcDaliActorGetMaximumSizeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_MAXIMUM_SIZE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetMinimumSizeP
 * @since_tizen        2.4
 * @description        check if GetMinimumSize api works or not.
 */

int UtcDaliActorGetMinimumSizeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_MINIMUM_SIZE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetMinimumSizeP
 * @since_tizen        2.4
 * @description        check if SetMinimumSize api works or not.
 */

int UtcDaliActorSetMinimumSizeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_MINIMUM_SIZE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorOnRelayoutSignalP
 * @since_tizen        2.4
 * @description        check if OnRelayoutSignal api works or not.
 */

int UtcDaliActorOnRelayoutSignalP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_ON_RELAYOUT_SIGNAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetResizePolicyP
 * @since_tizen        2.4
 * @description        check if SetResizePolicy api works or not.
 */

int UtcDaliActorSetResizePolicyP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_RESIZE_POLICY_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetHeightForWidthP
 * @since_tizen        2.4
 * @description        check if GetHeightForWidth api works or not.
 */

int UtcDaliActorGetHeightForWidthP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_HEIGHT_FOR_WIDTH_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetWidthForHeightP
 * @since_tizen        2.4
 * @description        check if GetWidthForHeight api works or not.
 */

int UtcDaliActorGetWidthForHeightP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_WIDTH_FOR_HEIGHT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetSizeModeFactorP
 * @since_tizen        2.4
 * @description        check if SetSizeModeFactor api works or not.
 */

int UtcDaliActorSetSizeModeFactorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_SIZE_MODE_FACTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetSizeModeFactorP
 * @since_tizen        2.4
 * @description        check if GetSizeModeFactor api works or not.
 */

int UtcDaliActorGetSizeModeFactorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_SIZE_MODE_FACTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetSizeScalePolicyP
 * @since_tizen        2.4
 * @description        check if SetSizeScalePolicy api works or not.
 */

int UtcDaliActorSetSizeScalePolicyP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_SIZE_SCALE_POLICY_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetSizeScalePolicyP
 * @since_tizen        2.4
 * @description        check if GetSizeScalePolicy api works or not.
 */

int UtcDaliActorGetSizeScalePolicyP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_SIZE_SCALE_POLICY_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorRotateByP
 * @since_tizen        2.4
 * @description        check if RotateBy api works or not.
 */

int UtcDaliActorRotateByP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_ROTATE_BY_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorRotateByP2
 * @since_tizen        2.4
 * @description        check if RotateBy api works or not.
 */

int UtcDaliActorRotateByP2(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_ROTATE_BY_P2 );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetNaturalSizeP
 * @since_tizen        2.4
 * @description        check if GetNaturalSize api works or not.
 */

int UtcDaliActorGetNaturalSizeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_NATURAL_SIZE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorResizePolicyP
 * @since_tizen        2.4
 * @description        check if ResizePolicy api works or not.
 */

int UtcDaliActorResizePolicyP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_RESIZE_POLICY_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorOperatorAssignmentP
 * @since_tizen        2.4
 * @description        check if OperatorAssignment api works or not.
 */

int UtcDaliActorOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetRelayoutSizeP
 * @since_tizen        2.4
 * @description        check if GetRelayoutSize api works or not.
 */

int UtcDaliActorGetRelayoutSizeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_RELAYOUT_SIZE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorConstructorP
 * @since_tizen        2.4
 * @description        check if Constructor api works or not.
 */

int UtcDaliActorConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorCopyConstructorP
 * @since_tizen        2.4
 * @description        check if CopyConstructor api works or not.
 */

int UtcDaliActorCopyConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetHierarchyDepthP
 * @since_tizen        2.4
 * @description        check if GetHierarchyDepth api works or not.
 */

int UtcDaliActorGetHierarchyDepthP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_HIERARCHY_DEPTH_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetLeaveRequiredP
 * @since_tizen        2.4
 * @description        check if SetLeaveRequired api works or not.
 */

int UtcDaliActorSetLeaveRequiredP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_LEAVE_REQUIRED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetLeaveRequiredP2
 * @since_tizen        2.4
 * @description        check if SetLeaveRequired api works or not.
 */

int UtcDaliActorSetLeaveRequiredP2(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_LEAVE_REQUIRED_P2 );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetLeaveRequiredP
 * @since_tizen        2.4
 * @description        check if GetLeaveRequired api works or not.
 */

int UtcDaliActorGetLeaveRequiredP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_LEAVE_REQUIRED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetLeaveRequiredP2
 * @since_tizen        2.4
 * @description        check if GetLeaveRequired api works or not.
 */

int UtcDaliActorGetLeaveRequiredP2(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_LEAVE_REQUIRED_P2 );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetTargetSizeP
 * @since_tizen        2.4
 * @description        check if GetTargetSize api works or not.
 */

int UtcDaliActorGetTargetSizeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_TARGET_SIZE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorScreenToLocalP
 * @since_tizen        2.4
 * @description        check if ScreenToLocal api works or not.
 */

int UtcDaliActorScreenToLocalP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SCREEN_TO_LOCAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorRemoveP
 * @since_tizen        2.4
 * @description        check if Remove api works or not.
 */

int UtcDaliActorRemoveP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_REMOVE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorSetInheritPositionP
 * @since_tizen        2.4
 * @description        check if SetInheritPosition api works or not.
 */

int UtcDaliActorSetInheritPositionP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_SET_INHERIT_POSITION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorIsPositionInheritedP
 * @since_tizen        2.4
 * @description        check if IsPositionInherited api works or not.
 */

int UtcDaliActorIsPositionInheritedP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_IS_POSITION_INHERITED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorRemoveRendererN
 * @since_tizen        2.4
 * @description        check if RemoveRenderer api works or not.
 */

int UtcDaliActorRemoveRendererN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_REMOVE_RENDERER_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorGetRendererCountN
 * @since_tizen        2.4
 * @description        check if GetRendererCount api works or not.
 */

int UtcDaliActorGetRendererCountN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_GET_RENDERER_COUNT_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorLayoutDirectionPropertyP
 * @since_tizen        4.0
 * @description        check direction property of actor
 */
int UtcDaliActorLayoutDirectionPropertyP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_LAYOUT_DIRECTION_PROPERTY);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorPropertiesP
 * @since_tizen        4.0
 * @description        check actor properties
 */
int UtcDaliActorPropertiesP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_PROPERTIES);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorRaiseLowerP
 * @since_tizen        4.0
 * @description        check Raise and Lower api
 */
int UtcDaliActorRaiseLowerP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_RAISE_LOWER);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorLowerBelowP
 * @since_tizen        4.0
 * @description        check LowerBelow api
 */
int UtcDaliActorLowerBelowP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_LOWER_BELOW);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorRaiseToTopLowerToBottomP
 * @since_tizen        4.0
 * @description        check RaiseToTop and LowerToBottom api
 */
int UtcDaliActorRaiseToTopLowerToBottomP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_RAISE_TO_TOP_LOWER_TO_BOTTOM);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorRaiseAboveP
 * @since_tizen        4.0
 * @description        check RaiseAbove api
 */
int UtcDaliActorRaiseAboveP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_RAISE_ABOVE);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliActorRaiseAboveActorAndTargetTheSameN
 * @since_tizen        4.0
 * @description        check RaiseAbove api when target the same
 */
int UtcDaliActorRaiseAboveActorAndTargetTheSameN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Actor_TestApp testApp(application, ACTOR_RAISE_ABOVE_ACTOR_AND_TARGET_THE_SAME);
  application.MainLoop();

  return test_return_value;
}
