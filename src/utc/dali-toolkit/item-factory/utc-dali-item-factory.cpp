#include "utc-dali-item-factory-common.h"

//& set: ItemFactory

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**Status for item release **/
bool gItemReleasedCalled = false;

/**
 * @function            utc_Dali_ItemFactory_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_ItemFactory_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_ItemFactory_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_ItemFactory_cleanup(void)
{

}


namespace
{
  // Implementation of ItemFactory for providing actors to ItemView
  class TestItemFactory : public ItemFactory
  {
    public:

      /**
       * Constructor
       * @param application class, stored as reference
       */
      TestItemFactory()
      {
        gItemReleasedCalled = false;
      }

    public:

      /**
       * Query the number of items available from the factory.
       * The maximum available item has an ID of GetNumberOfItems() - 1.
       */
      virtual unsigned int GetNumberOfItems()
      {
        return TOTAL_ITEM_NUMBER;
      }

      /**
       * Create an Actor to represent a visible item.
       * @param itemId
       * @return the created actor.
       */
      virtual Actor NewItem(unsigned int itemId)
      {
        // Create an image actor for this item
        string strImagePath=getResourceFullPath(TEST_IMAGE_FILE_NAME);
        if(strImagePath=="")
        {
          LOG_E( "Unable to get resource path from app data directory." );
          return Actor();
        }

        Image image = ResourceImage::New(strImagePath);
        Actor actor = ImageView::New(image);
        return actor;
      }

      /**
       * Query the number of items available from the factory.
       * The maximum available item has an ID of GetNumberOfItems() - 1.
       */
      virtual void ItemReleased(unsigned int itemId, Actor actor)
      {
        gItemReleasedCalled = true;
      }

  };
} // namespace

void ItemFactoryConstructorP();
void ItemFactoryNewP();
void ItemFactoryOperatorAssignmentP();
void ItemFactoryGetNumberOfItemsP();
void ItemFactoryNewItemP();
void ItemFactoryItemReleasedP();
void ItemFactoryGetExtensionP();

namespace
{
  enum TEST_CASES_LIST_ITEM_FACTORY
  {
    ITEM_FACTORY_CONSTRUCTOR_P,
    ITEM_FACTORY_NEW_P,
    ITEM_FACTORY_OPERATOR_ASSIGNMENT_P,
    ITEM_FACTORY_GET_NUMBER_OF_ITEMS_P,
    ITEM_FACTORY_NEW_ITEM_P,
    ITEM_FACTORY_ITEM_RELEASED_P,
    ITEM_FACTORY_GET_EXTENSION_P
  };

  struct ItemFactory_TestApp : public ConnectionTracker
  {
    ItemFactory_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &ItemFactory_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &ItemFactory_TestApp::Tick );
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
        case ITEM_FACTORY_CONSTRUCTOR_P:
          ItemFactoryConstructorP();
          break;

        case ITEM_FACTORY_NEW_P:
          ItemFactoryNewP();
          break;

        case ITEM_FACTORY_OPERATOR_ASSIGNMENT_P:
          ItemFactoryOperatorAssignmentP();
          break;

        case ITEM_FACTORY_GET_NUMBER_OF_ITEMS_P:
          ItemFactoryGetNumberOfItemsP();
          break;

        case ITEM_FACTORY_NEW_ITEM_P:
          ItemFactoryNewItemP();
          break;

        case ITEM_FACTORY_ITEM_RELEASED_P:
          ItemFactoryItemReleasedP();
          break;

        case ITEM_FACTORY_GET_EXTENSION_P:
          ItemFactoryGetExtensionP();
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

void ItemFactoryConstructorP()
{
  Actor actorItemCount;
  DALI_CHECK_FAIL(actorItemCount, "Creating an item factory constructor is failed." );

  DaliLog::PrintPass();
}

void ItemFactoryNewP()
{
  Actor actorItemCount;
  TestItemFactory factory =  TestItemFactory();
  DALI_CHECK_FAIL(factory.GetNumberOfItems() != TOTAL_ITEM_NUMBER, "Creating an item factory new instance is failed." );

  DaliLog::PrintPass();
}

void ItemFactoryOperatorAssignmentP()
{
  Actor actorItemCount;
  TestItemFactory OperatorItemFactory;
  TestItemFactory factory =  TestItemFactory();

  OperatorItemFactory = factory ;
  DALI_CHECK_FAIL( OperatorItemFactory.GetNumberOfItems() != TOTAL_ITEM_NUMBER, "Assigning an item factory to a new instance is failed." );

  DaliLog::PrintPass();
}

void ItemFactoryGetNumberOfItemsP()
{
  TestItemFactory factory;
  unsigned int uItemCount = 0u;

  uItemCount =  factory.GetNumberOfItems();
  DALI_CHECK_FAIL(uItemCount != TOTAL_ITEM_NUMBER, "Get total Number Of Items is mismatched for ItemFactory." );

  DaliLog::PrintPass();
}


void ItemFactoryNewItemP()
{
  TestItemFactory factory;
  const unsigned int ITEM_ID = 9u;
  Actor actorItemCount;

  actorItemCount =  factory.NewItem(ITEM_ID);

  DALI_CHECK_FAIL(!actorItemCount, "Creating an Actor to represent a visible item is failed." );
  UnparentAndReset(actorItemCount);

  DaliLog::PrintPass();
}

void ItemFactoryItemReleasedP()
{
  unsigned int ITEM_ID = 1;
  Actor actor;
  TestItemFactory factory =  TestItemFactory();
  factory.ItemReleased(ITEM_ID, actor);

  DALI_CHECK_FAIL( factory.GetExtension(), "GetExtension is Failed as it should be null." );
  DALI_CHECK_FAIL(!gItemReleasedCalled, "Calling factory ItemReleased() is failed." );

  DaliLog::PrintPass();
}

void ItemFactoryGetExtensionP()
{
  TestItemFactory factory =  TestItemFactory();
  DALI_CHECK_FAIL( factory.GetExtension(), "ItemFactoryGetExtension is falied." );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase            UtcDaliItemFactoryConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object
 */

int UtcDaliItemFactoryConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemFactory_TestApp testApp( application, ITEM_FACTORY_CONSTRUCTOR_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemFactoryNewP
 * @since_tizen         2.4
 * @description         Creating an item factory new instance
 */

int UtcDaliItemFactoryNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemFactory_TestApp testApp( application, ITEM_FACTORY_NEW_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemFactoryOperatorAssignmentP
 * @since_tizen         2.4
 * @description         Assignment operator.Changing handle to point to another real object
 */

int UtcDaliItemFactoryOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemFactory_TestApp testApp( application, ITEM_FACTORY_OPERATOR_ASSIGNMENT_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemFactoryGetNumberOfItemsP
 * @since_tizen         2.4
 * @description         Query the number of items available from the factory.
 */

int UtcDaliItemFactoryGetNumberOfItemsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemFactory_TestApp testApp( application, ITEM_FACTORY_GET_NUMBER_OF_ITEMS_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemFactoryNewItemP
 * @since_tizen         2.4
 * @description         Creating an Actor to represent a visible item.
 */

int UtcDaliItemFactoryNewItemP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemFactory_TestApp testApp( application, ITEM_FACTORY_NEW_ITEM_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemFactoryItemReleasedP
 * @since_tizen         2.4
 * @description         check for correctness of api ItemReleased
 */

int UtcDaliItemFactoryItemReleasedP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemFactory_TestApp testApp( application, ITEM_FACTORY_ITEM_RELEASED_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemFactoryGetExtensionP
 * @since_tizen         2.4
 * @description         Retrieve the extension for this control
 */

int UtcDaliItemFactoryGetExtensionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemFactory_TestApp testApp( application, ITEM_FACTORY_GET_EXTENSION_P);
  application.MainLoop();

  return test_return_value;
}
