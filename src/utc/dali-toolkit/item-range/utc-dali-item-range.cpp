#include "utc-dali-item-range-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_ItemRange_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_ItemRange_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_ItemRange_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_ItemRange_cleanup(void)
{

}


void ItemRangeConstructorP();
void ItemRangeOperatorAssignmentP();
void ItemRangeCopyConstructorP();
void ItemRangeWithinP();
void ItemRangeIntersectionP();

namespace
{
  enum TEST_CASES_LIST_ITEM_RANGE
  {
    ITEM_RANGE_CONSTRUCTOR_P,
    ITEM_RANGE_ASSIGNMENT_OPERATOR_P,
    ITEM_RANGE_COPY_CONSTRUCTOR_P,
    ITEM_RANGE_WITHIN_P,
    ITEM_RANGE_INTER_SECTION_P
  };

  struct ItemRange_TestApp : public ConnectionTracker
  {
    ItemRange_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &ItemRange_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &ItemRange_TestApp::Tick );
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
        case ITEM_RANGE_CONSTRUCTOR_P:
          ItemRangeConstructorP();
          break;

        case ITEM_RANGE_ASSIGNMENT_OPERATOR_P:
          ItemRangeOperatorAssignmentP();
          break;

        case ITEM_RANGE_COPY_CONSTRUCTOR_P:
          ItemRangeCopyConstructorP();
          break;

        case ITEM_RANGE_WITHIN_P:
          ItemRangeWithinP();
          break;

        case ITEM_RANGE_INTER_SECTION_P:
          ItemRangeIntersectionP();
          break;
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

void ItemRangeConstructorP()
{
  unsigned int uBeginItem = 100u, uEndItem = 300u;

  ItemRange objItemRange(uBeginItem, uEndItem);

  Toolkit::ItemRange* pOperatorItemRange = &objItemRange;

  DALI_CHECK_FAIL(pOperatorItemRange == NULL,  "ItemRange Constructor operator is Failed.");

  DaliLog::PrintPass();
}

void ItemRangeOperatorAssignmentP()
{
  unsigned int uBeginItem = 100u, uEndItem = 300u;

  Toolkit::ItemRange objItemRange(uBeginItem, uEndItem);

  Toolkit::ItemRange* pOperatorItemRange = &objItemRange;

  DALI_CHECK_FAIL(pOperatorItemRange == NULL,  "ItemRange Assignment operator is Failed.");

  DALI_CHECK_FAIL(pOperatorItemRange->begin != uBeginItem || pOperatorItemRange->end != uEndItem,  "ItemRange Assignment operator is Failed  values are mismatched! .");

  DaliLog::PrintPass();
}

void ItemRangeCopyConstructorP()
{
  unsigned int uBeginItem = 100u, uEndItem = 300u;

  Toolkit::ItemRange objItemRange(uBeginItem, uEndItem);

  Toolkit::ItemRange* pcpyConstrctr(&objItemRange);

  DALI_CHECK_FAIL(pcpyConstrctr == NULL,  "Copy Constructor do not work properly.");

  DALI_CHECK_FAIL(pcpyConstrctr->begin != uBeginItem || pcpyConstrctr->end != uEndItem,  "Copy Constructor do not work properly, values mismatched .");

  DaliLog::PrintPass();
}

void ItemRangeWithinP()
{
  unsigned int uBeginItem = 100u, uEndItem = 300u , uInterBeginCheck = 200u , uInterEndCheck = 400u ;
  bool bIsInThisRange = false, bOutOfThisRange = false;

  Toolkit::ItemRange objItemRange(uBeginItem, uEndItem);

  bIsInThisRange = false;
  bOutOfThisRange = true;

  bIsInThisRange = objItemRange.Within(uInterBeginCheck);

  bOutOfThisRange = objItemRange.Within(uInterEndCheck);

  DALI_CHECK_FAIL(bIsInThisRange != true,  "ItemRange Within out Range is Failed.");
  DALI_CHECK_FAIL(bOutOfThisRange != false,  "ItemRange Within out Range is Failed.");

  DaliLog::PrintPass();
}

void ItemRangeIntersectionP()
{
  unsigned int uBeginItemFirst = 100u, uEndItemFirst = 300u, uBeginItemSecond = 290u, uEndItemSecond = 400, uInterBeginCheck = 290u , uInterEndCheck = 301u;
  bool bIsInThisRange = false, bOutOfThisRange = false;

  Toolkit::ItemRange objItemRangeFirst(uBeginItemFirst, uEndItemFirst);
  Toolkit::ItemRange objItemRangeSecond(uBeginItemSecond, uEndItemSecond);

  bIsInThisRange = false;
  bOutOfThisRange = true;

  ItemRange itmInterSect = objItemRangeFirst.Intersection(objItemRangeSecond);

  bIsInThisRange = itmInterSect.Within(uInterBeginCheck);

  DALI_CHECK_FAIL(bIsInThisRange != true,  "ItemRange Intersection is Failed.");

  bOutOfThisRange = itmInterSect.Within(uInterEndCheck);

  DALI_CHECK_FAIL(bOutOfThisRange != false,  "ItemRange Intersection is Failed.");

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase             UtcDaliItemRangeConstructorP
 * @since_tizen          2.4
 * @description          Copy constructor to ItemRange
 */

int UtcDaliItemRangeConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemRange_TestApp testApp( application, ITEM_RANGE_CONSTRUCTOR_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase             UtcDaliItemRangeOperatorAssignmentP
 * @since_tizen          2.4
 * @description          Assignment operator.Changes this handle to point to another real object
 */

int UtcDaliItemRangeOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemRange_TestApp testApp( application, ITEM_RANGE_ASSIGNMENT_OPERATOR_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase             UtcDaliItemRangeCopyConstructorP
 * @since_tizen          2.4
 * @description          Copy constructor to ItemRange
 */

int UtcDaliItemRangeCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemRange_TestApp testApp( application, ITEM_RANGE_COPY_CONSTRUCTOR_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase             UtcDaliItemRangeWithinP
 * @since_tizen          2.4
 * @description          Test whether an item is within the range.
 */

int UtcDaliItemRangeWithinP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemRange_TestApp testApp( application, ITEM_RANGE_WITHIN_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase             UtcDaliItemRangeIntersectionP
 * @since_tizen          2.4
 * @description          Test whether an item is within the intersection of two ranges.
 */
int UtcDaliItemRangeIntersectionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemRange_TestApp testApp( application, ITEM_RANGE_INTER_SECTION_P);
  application.MainLoop();

  return test_return_value;
}
