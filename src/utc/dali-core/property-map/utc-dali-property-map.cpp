#include "utc-dali-property-map-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_PropertyMap_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_PropertyMap_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_PropertyMap_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_PropertyMap_cleanup(void)
{

}


void PropertyMapConstructor();
void PropertyMapConstructorInitializerList();
void PropertyMapCopyConstructor();
void PropertyMapCount();
void PropertyMapEmpty();
void PropertyMapInsert();
void PropertyMapInsertP2();
void PropertyMapInsertP3();
void PropertyMapInsertP4();
void PropertyMapAdd();
void PropertyMapAddChain();
void PropertyMapAnonymousAddChain();
void PropertyMapGetValue();
void PropertyMapGetKey();
void PropertyMapGetKeyAt();
void PropertyMapGetKeyValuePair();
void PropertyMapGetKeyValue();
void PropertyMapFind();
void PropertyMapFindP2();
void PropertyMapFindP3();
void PropertyMapFindP4();
void PropertyMapFindP5();
void PropertyMapFindP6();
void PropertyMapFindN();
void PropertyMapClear();
void PropertyMapMerge();
void PropertyMapOperatorAssignment();
void PropertyMapOperatorAssignmentP2();
void PropertyMapOperatorAssignmentP3();
void PropertyMapSquareOperatorP();
void PropertyMapConstSquareOperatorP();
void PropertyKeyConstructorP();
void PropertyKeyEqualityOperatorP();
void PropertyKeyInequalityOperatorP();
void PropertyKeyOutputStream();
namespace
{
  enum TEST_CASES_LIST_PROPERTY_MAP
  {
    PROPERTY_MAP_CONSTRUCTOR,
    PROPERTY_MAP_CONSTRUCTOR_INITIALIZER_LIST,
    PROPERTY_MAP_COPYCONSTRUCTOR,
    PROPERTY_MAP_COUNT,
    PROPERTY_MAP_EMPTY,
    PROPERTY_MAP_INSERT,
    PROPERTY_MAP_INSERT_P2,
    PROPERTY_MAP_INSERT_P3,
    PROPERTY_MAP_INSERT_P4,
    PROPERTY_MAP_ADD,
    PROPERTY_MAP_ADD_CHAIN,
    PROPERTY_MAP_ANONYMOUS_ADD_CHAIN,
    PROPERTY_MAP_GET_KEY,
    PROPERTY_MAP_GET_KEY_AT,
    PROPERTY_MAP_GET_VALUE,
    PROPERTY_MAP_GET_KEY_VALUE_PAIR,
    PROPERTY_MAP_GET_KEY_VALUE,
    PROPERTY_MAP_FIND,
    PROPERTY_MAP_FIND_P2,
    PROPERTY_MAP_FIND_P3,
    PROPERTY_MAP_FIND_P4,
    PROPERTY_MAP_FIND_P5,
    PROPERTY_MAP_FIND_P6,
    PROPERTY_MAP_FIND_N,
    PROPERTY_MAP_MERGE,
    PROPERTY_MAP_CLEAR,
    PROPERTY_MAP_ASSIGNMENT_OPERATOR,
    PROPERTY_MAP_ASSIGNMENT_OPERATOR_P2,
    PROPERTY_MAP_ASSIGNMENT_OPERATOR_P3,
    PROPERTY_MAP_SQUARE_OPERATOR_P,
    PROPERTY_MAP_CONST_SQUARE_OPERATOR_P,
    PROPERTY_KEY_CONSTRUCTOR_P,
    PROPERTY_KEY_EQUALITY_OPERATOR_P,
    PROPERTY_KEY_INEQUALITY_OPERATOR_P,
    PROPERTY_KEY_OUTPUT_STREAM
  };

  struct Property_Map_TestApp : public ConnectionTracker
  {
    Property_Map_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Property_Map_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Property_Map_TestApp::Tick );
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
        case PROPERTY_MAP_CONSTRUCTOR:
          PropertyMapConstructor();
          break;

        case PROPERTY_MAP_CONSTRUCTOR_INITIALIZER_LIST:
          PropertyMapConstructorInitializerList();
          break;

        case PROPERTY_MAP_COPYCONSTRUCTOR:
          PropertyMapCopyConstructor();
          break;

        case PROPERTY_MAP_COUNT:
          PropertyMapCount();
          break;

        case PROPERTY_MAP_EMPTY:
          PropertyMapEmpty();
          break;

        case PROPERTY_MAP_INSERT:
          PropertyMapInsert();
          break;

        case PROPERTY_MAP_INSERT_P2:
          PropertyMapInsertP2();
          break;

        case PROPERTY_MAP_INSERT_P3:
          PropertyMapInsertP3();
          break;

        case PROPERTY_MAP_INSERT_P4:
          PropertyMapInsertP4();
          break;

        case PROPERTY_MAP_ADD:
          PropertyMapAdd();
          break;

        case PROPERTY_MAP_ADD_CHAIN:
          PropertyMapAddChain();
          break;

        case PROPERTY_MAP_ANONYMOUS_ADD_CHAIN:
          PropertyMapAnonymousAddChain();
          break;

        case PROPERTY_MAP_FIND:
          PropertyMapFind();
          break;

        case PROPERTY_MAP_FIND_P2:
          PropertyMapFindP2();
          break;

        case PROPERTY_MAP_FIND_P3:
          PropertyMapFindP3();
          break;

        case PROPERTY_MAP_FIND_P4:
          PropertyMapFindP4();
          break;

        case PROPERTY_MAP_FIND_P5:
          PropertyMapFindP5();
          break;

        case PROPERTY_MAP_FIND_P6:
          PropertyMapFindP6();
          break;

        case PROPERTY_MAP_FIND_N:
          PropertyMapFindN();
          break;

        case PROPERTY_MAP_CLEAR:
          PropertyMapClear();
          break;

        case PROPERTY_MAP_MERGE:
          PropertyMapMerge();
          break;

        case PROPERTY_MAP_GET_VALUE:
          PropertyMapGetValue();
          break;

        case PROPERTY_MAP_GET_KEY:
          PropertyMapGetKey();
          break;

        case PROPERTY_MAP_GET_KEY_AT:
          PropertyMapGetKeyAt();
          break;

        case PROPERTY_MAP_GET_KEY_VALUE_PAIR:
          PropertyMapGetKeyValuePair();
          break;

        case PROPERTY_MAP_GET_KEY_VALUE:
          PropertyMapGetKeyValue();
          break;

        case PROPERTY_MAP_ASSIGNMENT_OPERATOR:
          PropertyMapOperatorAssignment();
          break;

        case PROPERTY_MAP_ASSIGNMENT_OPERATOR_P2:
          PropertyMapOperatorAssignmentP2();
          break;

        case PROPERTY_MAP_ASSIGNMENT_OPERATOR_P3:
          PropertyMapOperatorAssignmentP3();
          break;

        case PROPERTY_MAP_SQUARE_OPERATOR_P:
          PropertyMapSquareOperatorP();
          break;

        case PROPERTY_MAP_CONST_SQUARE_OPERATOR_P:
          PropertyMapConstSquareOperatorP();
          break;

        case PROPERTY_KEY_CONSTRUCTOR_P:
          PropertyKeyConstructorP();
          break;

        case PROPERTY_KEY_EQUALITY_OPERATOR_P:
          PropertyKeyEqualityOperatorP();
          break;

        case PROPERTY_KEY_INEQUALITY_OPERATOR_P:
          PropertyKeyInequalityOperatorP();
          break;

        case PROPERTY_KEY_OUTPUT_STREAM:
          PropertyKeyOutputStream();
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



void PropertyMapConstructor()
{
  const string strMapFirst = "hello";
  const string strMapTwo = "world";
  const string strMapThree = "Tizen";
  const string strMapAssign = "Assing Me";
  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  propMap[ strMapFirst] =  1;
  propMap[ strMapTwo  ]   =  2;
  propMap[ strMapThree] =  3;

  unsigned int uCountReal = propMap.Count();

  DALI_CHECK_FAIL(propMap.Empty(), "property is  empty which is not expected");

  DALI_CHECK_FAIL( uCountReal != 3 , "property count should be 3 but it is not match with expected"); //Should only have three items !!

  Property::Map propMapAssign ;

  propMapAssign [strMapAssign ] = 4 ;
  DALI_CHECK_FAIL(propMapAssign.Count() != 1, "property count should be 1 but it is not match with expected"); //Should only have one item !!

  propMapAssign = propMap ;

  unsigned int uCountAssign  = propMapAssign.Count();
  DALI_CHECK_FAIL( uCountAssign != uCountReal , "property count should be match with real map count");

  Property::Map propMapCopy (propMap) ;

  unsigned int uCountCopy  = propMapCopy.Count();
  DALI_CHECK_FAIL( uCountCopy != uCountReal , "property count should be match with real map count");

  propMap.Clear();
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not  empty after using clear Api  which is not expected");

  DaliLog::PrintPass();
}
void PropertyMapConstructorInitializerList()
{
  Property::Map propMap{ { "one", 1 }, { "two", 2 }, { "three", 3 } };
  unsigned int uCountReal = propMap.Count();

  DALI_CHECK_FAIL(propMap.Empty(), "property is  empty which is not expected");

  DALI_CHECK_FAIL( uCountReal != 3 , "property count should be 3 but it does not match with expected"); //Should only have three items !!

  DaliLog::PrintPass();
}
void PropertyMapCopyConstructor()
{
  const string strMapFirst = "hello";
  const string strMapTwo = "world";
  const string strMapThree = "Tizen";
  const string strMapAssign = "Assing Me";
  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  propMap[ strMapFirst] =  1;
  propMap[ strMapTwo  ] =  2;
  propMap[ strMapThree] =  3;

  unsigned int uCountReal = propMap.Count();

  DALI_CHECK_FAIL(propMap.Empty(), "property is  empty which is not expected");

  DALI_CHECK_FAIL( uCountReal != 3 , "property count should be 3 but it is not match with expected"); //Should only have three items !!

  Property::Map propMapAssign ;

  propMapAssign [strMapAssign ] = 4 ;
  DALI_CHECK_FAIL(propMapAssign.Count() != 1, "property count should be 1 but it is not match with expected"); //Should only have one item !!

  propMapAssign = propMap ;

  unsigned int uCountAssign  = propMapAssign.Count();
  DALI_CHECK_FAIL( uCountAssign != uCountReal , "property count should be match with real map count");

  Property::Map propMapCopy (propMap) ;

  unsigned int uCountCopy  = propMapCopy.Count();
  DALI_CHECK_FAIL( uCountCopy != uCountReal , "property count should be match with real map count");

  propMap.Clear();
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not  empty after using clear Api  which is not expected");

  DaliLog::PrintPass();
}
void PropertyMapCount()
{
  const string strMapFirst = "hello";
  const string strMapTwo = "world";
  const string strMapThree = "Tizen";
  const string strMapAssign = "Assing Me";
  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  propMap[ strMapFirst] =  1;
  propMap[ strMapTwo  ]   =  2;
  propMap[ strMapThree] =  3;

  unsigned int uCountReal = propMap.Count();

  DALI_CHECK_FAIL(propMap.Empty(), "property is  empty which is not expected");

  DALI_CHECK_FAIL( uCountReal != 3 , "property count should be 3 but it is not match with expected"); //Should only have three items !!

  Property::Map propMapAssign ;

  propMapAssign [strMapAssign ] = 4 ;
  DALI_CHECK_FAIL(propMapAssign.Count() != 1, "property count should be 1 but it is not match with expected"); //Should only have one item !!

  propMapAssign = propMap ;

  unsigned int uCountAssign  = propMapAssign.Count();
  DALI_CHECK_FAIL( uCountAssign != uCountReal , "property count should be match with real map count");

  Property::Map propMapCopy (propMap) ;

  unsigned int uCountCopy  = propMapCopy.Count();
  DALI_CHECK_FAIL( uCountCopy != uCountReal , "property count should be match with real map count");

  DaliLog::PrintPass();
}
void PropertyMapEmpty()
{
  const string strMapFirst = "hello";
  const string strMapTwo = "world";

  Property::Map propMap;

  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  propMap[ strMapFirst] =  1;
  propMap[ strMapTwo  ]   =  2;

  DALI_CHECK_FAIL(propMap.Empty(), "property is  empty which is not expected");

  DaliLog::PrintPass();
}
void PropertyMapInsert()
{
  const string strMapFirst = "hello";
  const string strMapTwo = "world";
  const string strMapThree = "Tizen";

  const int nSetValueOne = 1 ,nSetValueTwo = 2  , nSetValueThree = 3 ;

  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  unsigned int uCountReal = propMap.Count();
  DALI_CHECK_FAIL( uCountReal != 0 , "property count should be 0 but it is not match with expected"); //Should only have zero items !!

  propMap.Insert(strMapFirst, nSetValueOne);
  Property::Value* valueGet = propMap.Find( strMapFirst );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueOne ," Find is not working properly while returning reference of the key");

  propMap.Insert(strMapTwo, nSetValueTwo);
  valueGet = propMap.Find( strMapTwo );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueTwo ," Find is not working properly while returning reference of the key");

  propMap.Insert(strMapThree, nSetValueThree);
  valueGet = propMap.Find( strMapThree );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueThree ," Find is not working properly while returning reference of the key");

  DaliLog::PrintPass();
}
void PropertyMapInsertP2()
{
  const string strMapFirst = "hello";
  const string strMapTwo = "world";
  const int nSetValueOne = 1 ,nSetValueTwo = 2;

  Property::Map propMap;

  propMap.Insert(strMapFirst, nSetValueOne);
  DALI_CHECK_FAIL( 1 != propMap.Count() ," Only one item should be in Map");

  propMap.Insert(std::string(strMapTwo), nSetValueTwo);
  DALI_CHECK_FAIL( 2 != propMap.Count() ," Only two items should be in Map");

  DaliLog::PrintPass();
}
void PropertyMapInsertP3()
{
  const Property::Index indexMapFirst = 10;
  const Property::Index indexMapTwo = 20;
  const Property::Index indexMapThree = 30;

  const int nSetValueOne = 1 ,nSetValueTwo = 2  , nSetValueThree = 3 ;

  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  unsigned int uCountReal = propMap.Count();
  DALI_CHECK_FAIL( uCountReal != 0 , "property count should be 0 but it is not match with expected"); //Should only have zero items !!

  propMap.Insert(indexMapFirst, nSetValueOne);
  Property::Value* valueGet = propMap.Find( indexMapFirst );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueOne ," Find is not working properly while returning reference of the key");

  propMap.Insert(indexMapTwo, nSetValueTwo);
  valueGet = propMap.Find( indexMapTwo );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueTwo ," Find is not working properly while returning reference of the key");

  propMap.Insert(indexMapThree, nSetValueThree);
  valueGet = propMap.Find( indexMapThree );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueThree ," Find is not working properly while returning reference of the key");

  DaliLog::PrintPass();
}
void PropertyMapInsertP4()
{
  const Property::Index indexMapFirst = 10;
  const Property::Index indexMapTwo = 11;
  const int nSetValueOne = 1 ,nSetValueTwo = 2;

  Property::Map propMap;

  propMap.Insert(indexMapFirst, nSetValueOne);
  DALI_CHECK_FAIL( 1 != propMap.Count() ," Only one item should be in Map");

  propMap.Insert(indexMapTwo, nSetValueTwo);
  DALI_CHECK_FAIL( 2 != propMap.Count() ," Only two items should be in Map");

  DaliLog::PrintPass();
}
void PropertyMapAdd()
{ 
  const std::string strValue1 = "bar";
  const std::string strValue2 = "testing";
  const std::string strValue3 = "DALi";
  const int intValue = 9;

  Property::Map map;
  DALI_CHECK_FAIL( 0 != map.Count() ," Property is not empty which is not expected");

  map.Add( "foo", strValue1);
  DALI_CHECK_FAIL( 1 != map.Count() ," Only one item should be in Map");

  Property::Value* value = map.Find( "foo" );
  DALI_CHECK_FAIL( ! ( value->Get<std::string>() == strValue1 ), " Find is not working properly while returning reference of the key" );

  map.Add( std::string("foo2"), strValue2 );
  DALI_CHECK_FAIL( 2 != map.Count() ," Only two items should be in Map");
  value = map.Find( "foo2" );
  DALI_CHECK_FAIL( ! ( value->Get<std::string>() == strValue2 ), " Find is not working properly while returning reference of the key" );

  map.Add( 10, strValue3 );
  DALI_CHECK_FAIL( 3 != map.Count() ," Only three items should be in Map");
  value = map.Find( 10 );
  DALI_CHECK_FAIL( ! ( value->Get<std::string>() == strValue3 ), " Find is not working properly while returning reference of the key" );

  map.Add( 100, intValue );
  DALI_CHECK_FAIL( 4 != map.Count() ," Only four items should be in Map");
  value = map.Find( 100 );
  DALI_CHECK_FAIL( value->Get<int>() != intValue , " Find is not working properly while returning reference of the key" );

  DaliLog::PrintPass();
}
void PropertyMapAddChain()
{ 
  const std::string strValue1 = "bar";
  const std::string strValue2 = "testing";
  const std::string strValue3 = "DALi";
  const int intValue = 9;

  Property::Map map;
  DALI_CHECK_FAIL( 0 != map.Count() ," Property is not empty which is not expected");
  map
    .Add( "foo", strValue1)
    .Add( std::string("foo2"), strValue2 )
    .Add( 10, strValue3 )
    .Add( 100, intValue );

  DALI_CHECK_FAIL( 4 != map.Count() ," 4 items should be in Map");

  Property::Value* value = map.Find( "foo" );
  DALI_CHECK_FAIL( ! ( value->Get<std::string>() == strValue1 ), " Find is not working properly while returning reference of the key" );

  value = map.Find( "foo2" );
  DALI_CHECK_FAIL( ! ( value->Get<std::string>() == strValue2 ), " Find is not working properly while returning reference of the key" );

  value = map.Find( 10 );
  DALI_CHECK_FAIL( ! ( value->Get<std::string>() == strValue3 ), " Find is not working properly while returning reference of the key" );

  value = map.Find( 100 );
  DALI_CHECK_FAIL( value->Get<int>() != intValue, " Find is not working properly while returning reference of the key" );

  DaliLog::PrintPass();
}
void PropertyMapAnonymousAddChain(void)
{
  const std::string strValue1 = "bar";
  const std::string strValue2 = "testing";
  const std::string strValue3 = "DALi";
  const int intValue = 9;

  class TestMap
  {
  public:
    TestMap(Property::Map map)
    : mMap(map)
    {
    }
    Property::Map mMap;
  };

  TestMap mapTest( Property::Map().Add( "foo", "bar")
                                  .Add( std::string("foo2"), "testing" )
                                  .Add( 10, "DALi" )
                                  .Add( 100, 9 ));


  Property::Value* value = mapTest.mMap.Find( "foo" );
  DALI_CHECK_FAIL( ! ( value->Get<std::string>() == strValue1 ), " Find is not working properly while returning reference of the key" );

  value = mapTest.mMap.Find( "foo2" );
  DALI_CHECK_FAIL( ! ( value->Get<std::string>() == strValue2 ), " Find is not working properly while returning reference of the key" );

  value = mapTest.mMap.Find( 10 );
  DALI_CHECK_FAIL( ! ( value->Get<std::string>() == strValue3 ), " Find is not working properly while returning reference of the key" );

  value = mapTest.mMap.Find( 100 );
  DALI_CHECK_FAIL( value->Get<int>() != intValue , " Find is not working properly while returning reference of the key" );

  DaliLog::PrintPass();;
}
void PropertyMapGetKey()
{
  const string strMapFirst = "hello";
  const string strMapTwo = "world";
  const string strMapThree = "Tizen";
 
  const int nSetValueOne = 1 ,nSetValueTwo = 2  , nSetValueThree = 3 ;

  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  propMap[ strMapFirst]   =  nSetValueOne ;
  propMap[ strMapTwo  ]   =  nSetValueTwo;
  propMap[ strMapThree]   =  nSetValueThree;

  string strGetKey = propMap.GetKey( 0 );
  DALI_CHECK_FAIL(strGetKey != strMapFirst ," GetKey is not working properly while returning the key");

  strGetKey = propMap.GetKey( 1 );
  DALI_CHECK_FAIL(strGetKey != strMapTwo ," GetKey is not working properly while returning the key");

  strGetKey = propMap.GetKey( 2 );
  DALI_CHECK_FAIL(strGetKey != strMapThree ," GetKey is not working properly while returning the key");

  DaliLog::PrintPass();
}

void PropertyMapGetKeyAt()
{
  const string strMapFirst = "hello";
  const string strMapTwo = "world";
  const Dali::Property::Index idxMapThree = Actor::Property::COLOR;

  const int nSetValueOne = 1 ,nSetValueTwo = 2 ;
  const Vector4 nSetValueThree = Color::MAGENTA;

  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  propMap[ strMapFirst]   =  nSetValueOne ;
  propMap[ strMapTwo  ]   =  nSetValueTwo;
  propMap[ idxMapThree ]  =  nSetValueThree;

  DALI_CHECK_FAIL(propMap.GetKeyAt( 0 ) != strMapFirst ," GetKeyAt is not working properly while returning the key");

  DALI_CHECK_FAIL(propMap.GetKeyAt( 1 ) != strMapTwo ," GetKeyAt is not working properly while returning the key");
  
  DALI_CHECK_FAIL(propMap.GetKeyAt( 2 ) != idxMapThree ," GetKeyAt is not working properly while returning the key");
  DaliLog::PrintPass();
}
void PropertyMapGetValue()
{
  const string strMapFirst = "hello";
  const string strMapTwo = "world";
  const Dali::Property::Index idxMapThree = Actor::Property::COLOR;

  const int nSetValueOne = 1 ,nSetValueTwo = 2;
  const Vector4 nSetValueThree = Color::MAGENTA;

  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  propMap[ strMapFirst]   =  nSetValueOne;
  propMap[ strMapTwo  ]   =  nSetValueTwo;
  propMap[ idxMapThree ]  =  nSetValueThree;

  Property::Value& value = propMap.GetValue( 0 );
  DALI_CHECK_FAIL( value.Get<int>() != nSetValueOne ," getvalue is not working properly while returning reference");

  value = propMap.GetValue( 1 );
  DALI_CHECK_FAIL( value.Get<int>() != nSetValueTwo ," getvalue is not working properly while returning reference");

  value = propMap.GetValue( 2 );
  DALI_CHECK_FAIL( value.Get<Vector4>() != nSetValueThree ," getvalue is not working properly while returning reference");

  value = Color::CYAN;
  DALI_CHECK_FAIL( value.Get<Vector4>() != Color::CYAN ," value changing is not working properly while returning reference");

  DaliLog::PrintPass();
}
void PropertyMapGetKeyValuePair()
{
  const string strMapFirst = "hello";
  const string strMapTwo = "world";
  const string strMapThree = "Tizen";

  const int nSetValueOne = 1 ,nSetValueTwo = 2  , nSetValueThree = 3 ;

  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  propMap[ strMapFirst]   =  nSetValueOne ;
  propMap[ strMapTwo  ]   =  nSetValueTwo;
  propMap[ strMapThree]   =  nSetValueThree;

  Property::Value& value = propMap.GetValue( 0 );
  DALI_CHECK_FAIL( value.Get<int>() != nSetValueOne ," getvalue is not working properly while returning reference");

  string strGetKey = propMap.GetKey( 0 );
  DALI_CHECK_FAIL(strGetKey != strMapFirst ," GetKey is not working properly while returning the key");

  string strGetPairKey = propMap.GetPair( 0 ).first;
  DALI_CHECK_FAIL(strGetPairKey != strMapFirst ," GetPair is not working properly while returning the pair key");

  DALI_CHECK_FAIL( propMap.GetPair( 0 ).second.Get< int >() != nSetValueOne, "pair value is not match properly" );

  Property::Value* valueGet = propMap.Find( strMapFirst );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueOne ," Find is not working properly while returning reference of the key");

  DaliLog::PrintPass();
}
void PropertyMapGetKeyValue()
{
  const string strMapFirst = "hello";
  const string strMapTwo = "world";
  const string strMapThree = "Tizen";
  const Dali::Property::Index idxMapFour = Actor::Property::COLOR;

  const int nSetValueOne = 1 ,nSetValueTwo = 2  , nSetValueThree = 3 ;
  const Vector4 nSetValueFour = Color::MAGENTA;


  

  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  propMap[ strMapFirst]   =  nSetValueOne ;
  propMap[ strMapTwo  ]   =  nSetValueTwo;
  propMap[ strMapThree]   =  nSetValueThree;
  propMap[ idxMapFour  ]  =  nSetValueFour;

  DALI_CHECK_FAIL( propMap.GetKeyValue( 0 ).first != strMapFirst,                " GetPair is not working properly while returning the pair key");
  DALI_CHECK_FAIL( propMap.GetKeyValue( 0 ).second.Get< int >() != nSetValueOne, " getvalue is not working properly while returning reference");
  DALI_CHECK_FAIL( propMap.GetKeyValue( 1 ).first != strMapTwo,                  " GetPair is not working properly while returning the pair key");
  DALI_CHECK_FAIL( propMap.GetKeyValue( 1 ).second.Get< int >() != nSetValueTwo, " getvalue is not working properly while returning reference");

  DALI_CHECK_FAIL( propMap.GetKeyValue( 2 ).first != strMapThree,                  " GetPair is not working properly while returning the pair key");
  DALI_CHECK_FAIL( propMap.GetKeyValue( 2 ).second.Get< int >() != nSetValueThree, " getvalue is not working properly while returning reference");

  DALI_CHECK_FAIL( propMap.GetKeyValue( 3 ).first != idxMapFour,                      " GetPair is not working properly while returning the pair key");
  DALI_CHECK_FAIL( propMap.GetKeyValue( 3 ).second.Get< Vector4 >() != nSetValueFour, " getvalue is not working properly while returning reference");

  DaliLog::PrintPass();
}
void PropertyMapFind()
{
  const string strMapFirst = "hello";
  const string strMapTwo = "world";
  const string strMapThree = "Tizen";

  const int nSetValueOne = 1, nSetValueTwo = 2, nSetValueThree = 3 ;

  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  propMap[ strMapFirst]   = nSetValueOne;
  propMap[ strMapTwo ]   =  nSetValueTwo;
  propMap[ strMapThree]   = nSetValueThree;

  Property::Value* valueGet = propMap.Find( strMapFirst );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueOne ," Find is not working properly while returning reference of the key");

  valueGet = propMap.Find( strMapTwo );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueTwo ," Find is not working properly while returning reference of the key");

  valueGet = propMap.Find( strMapThree );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueThree ," Find is not working properly while returning reference of the key");

  DaliLog::PrintPass();
}
void PropertyMapFindP2()
{
  const string strMapFirst = "hello";
  const string strMapTwo = "world";
  const string strMapThree = "Tizen";

  const int nSetValueOne = 1, nSetValueTwo = 2, nSetValueThree = 3 ;

  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  propMap[ strMapFirst]   = nSetValueOne;
  propMap[ strMapTwo ]   =  nSetValueTwo;
  propMap[ strMapThree]   = nSetValueThree;

  Property::Value* valueGet = propMap.Find( strMapFirst );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueOne ," Find is not working properly while returning reference of the key");

  valueGet = propMap.Find( strMapTwo );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueTwo ," Find is not working properly while returning reference of the key");

  valueGet = propMap.Find( strMapThree );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueThree ," Find is not working properly while returning reference of the key");

  DaliLog::PrintPass();
}
void PropertyMapFindP3()
{
  const string strMapFirst = "hello";
  const string strMapTwo = "world";
  const string strMapThree = "Tizen";

  const int nSetValueOne = 1, nSetValueTwo = 2, nSetValueThree = 3 ;

  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  propMap[ strMapFirst]   = nSetValueOne;
  propMap[ strMapTwo ]   =  nSetValueTwo;
  propMap[ strMapThree]   = nSetValueThree;

  Property::Value* valueGet = propMap.Find( strMapFirst );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueOne ," Find is not working properly while returning reference of the key");

  valueGet = propMap.Find( strMapTwo );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueTwo ," Find is not working properly while returning reference of the key");

  valueGet = propMap.Find( strMapThree );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueThree ," Find is not working properly while returning reference of the key");

  DaliLog::PrintPass();
}
void PropertyMapFindP4()
{
  const Property::Index indexMapFirst = 10;
  const Property::Index indexMapTwo = 20;
  const Property::Index indexMapThree = 30;

  const int nSetValueOne = 1 ,nSetValueTwo = 2  , nSetValueThree = 3 ;

  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  unsigned int uCountReal = propMap.Count();
  DALI_CHECK_FAIL( uCountReal != 0 , "property count should be 0 but it is not match with expected"); //Should only have zero items !!

  propMap.Insert(indexMapFirst, nSetValueOne);
  Property::Value* valueGet = propMap.Find( indexMapFirst );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueOne ," Find is not working properly while returning reference of the key");

  propMap.Insert(indexMapTwo, nSetValueTwo);
  valueGet = propMap.Find( indexMapTwo );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueTwo ," Find is not working properly while returning reference of the key");

  propMap.Insert(indexMapThree, nSetValueThree);
  valueGet = propMap.Find( indexMapThree );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueThree ," Find is not working properly while returning reference of the key");

  DaliLog::PrintPass();
}
void PropertyMapFindP5()
{
  const Property::Index indexMapFirst = 10;
  const Property::Index indexMapTwo = 20;
  const Property::Index indexMapThree = 30;

  const int nSetValueOne = 1 ,nSetValueTwo = 2  , nSetValueThree = 3 ;

  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  unsigned int uCountReal = propMap.Count();
  DALI_CHECK_FAIL( uCountReal != 0 , "property count should be 0 but it is not match with expected"); //Should only have zero items !!

  propMap.Insert(indexMapFirst, nSetValueOne);
  Property::Value* valueGet = propMap.Find( indexMapFirst, Property::INTEGER );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueOne ," Find is not working properly while returning reference of the key");

  propMap.Insert(indexMapTwo, nSetValueTwo);
  valueGet = propMap.Find( indexMapTwo, Property::INTEGER );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueTwo ," Find is not working properly while returning reference of the key");

  propMap.Insert(indexMapThree, nSetValueThree);
  valueGet = propMap.Find( indexMapThree, Property::INTEGER );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueThree ," Find is not working properly while returning reference of the key");

  DaliLog::PrintPass();
}

void PropertyMapFindP6()
{
  // Define the valid keys and values to test with.
  std::string stringKeyValid = "bar";
  std::string stringKeyInvalid = "aardvark";
  int indexKeyValid = 100;
  int indexKeyInvalid = 101;

  // Define invalid key and value to test with.
  std::string stringValueValid = "DALi";
  int indexValueValid = 3;

  // Set up a property map containing the valid keys and values defined above.
  Property::Map map;
  map[ "foo" ] = 1;
  map[ 10 ] = "string";
  map[ stringKeyValid ] = stringValueValid;
  map[ indexKeyValid ] = indexValueValid;

  Property::Value* value = NULL;

  // TEST: If both index and string are valid, the Property::Value of the index is returned.
  value = map.Find( indexKeyValid, stringKeyValid );
  DALI_CHECK_FAIL( ! ( value->Get<int>() == indexValueValid ), "PropertyMapFindP6 test failed" );

  // TEST: If only the index is valid, the Property::Value of the index is returned.
  value = map.Find( indexKeyValid, stringKeyInvalid );
  DALI_CHECK_FAIL( ! ( value->Get<int>() == indexValueValid ), "PropertyMapFindP6 test failed" );

  // TEST: If only the string is valid, the Property::Value of the string is returned.
  value = map.Find( indexKeyInvalid, stringKeyValid );
  DALI_CHECK_FAIL( ! ( value->Get<std::string>() == stringValueValid ), "PropertyMapFindP6 test failed" );

  // TEST: If neither the index or string are valid, then a NULL pointer is returned.
  value = map.Find( indexKeyInvalid, stringKeyInvalid );
  DALI_CHECK_FAIL( ! ( value == NULL ), "PropertyMapFindP6 test failed" );

  DaliLog::PrintPass();
}
void PropertyMapFindN()
{
  const Property::Index indexMapFirst = 10;
  const int nSetValueOne = 1;

  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  unsigned int uCountReal = propMap.Count();
  DALI_CHECK_FAIL( uCountReal != 0 , "property count should be 0 but it is not match with expected"); //Should only have zero items !!

  propMap.Insert(indexMapFirst, nSetValueOne);
  Property::Value* valueGet = propMap.Find( indexMapFirst, Property::MAP );
  DALI_CHECK_FAIL( valueGet," Find should not return a valid value if the property type we pass in is wrong");

  DaliLog::PrintPass();
}
void PropertyMapClear()
{
  const string strMapFirst = "hello";
  const string strMapTwo = "world";
  const string strMapThree = "Tizen_2.4";

  int nSetValueOne = 1 ,nSetValueTwo = 2 ;

  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  propMap[ strMapFirst]   =  nSetValueOne ;
  propMap[ strMapTwo  ]   =  nSetValueTwo;

  DALI_CHECK_FAIL(propMap.Empty(), "property is empty which is not expected");

  propMap.Clear();
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  DaliLog::PrintPass();
}
void PropertyMapMerge()
{
  const string strMapFirst = "hello";
  const string strMapTwo = "world";
  const string strMapThree = "Tizen_2.4";

  int nSetValueOne = 1 ,nSetValueTwo = 2 ;

  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  propMap[ strMapFirst]   =  nSetValueOne ;
  propMap[ strMapTwo  ]   =  nSetValueTwo;

  DALI_CHECK_FAIL( propMap.Count() != 2,"property is not match with count  which is not expected" );//should be two

  Property::Map mapSecond;
  mapSecond[ "Tizen" ]     = 3;
  mapSecond[ "DALI" ]     = 4;

  propMap.Merge(mapSecond);
  // Merge mapSecond into propMap, count should still be 6, map values should be from mapSecond

  DALI_CHECK_FAIL( propMap.Count() != 4,"property is not Merge properly as it is giving wrong count" );
  DALI_CHECK_FAIL( propMap[ "Tizen" ].Get< int >() != 3,"property is not Merge properly as it is giving wrong index value" );
  DALI_CHECK_FAIL( propMap[ "DALI"].Get< int >() != 4,"property is not Merge properly as it is giving wrong index value" );

  DaliLog::PrintPass();
}
void PropertyMapOperatorAssignment()
{
  const string strMapFirst = "hello";
  const string strMapTwo = "world";
  const string strMapThree = "Tizen";
  const string strMapAssign = "Assing Me";
  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  propMap[ strMapFirst] =  1;
  propMap[ strMapTwo  ]   =  2;
  propMap[ strMapThree] =  3;

  unsigned int uCountReal = propMap.Count();

  DALI_CHECK_FAIL(propMap.Empty(), "property is  empty which is not expected");

  DALI_CHECK_FAIL( uCountReal != 3 , "property count should be 3 but it is not match with expected"); //Should only have three items !!

  Property::Map propMapAssign ;

  propMapAssign [strMapAssign ] = 4 ;
  DALI_CHECK_FAIL(propMapAssign.Count() != 1, "property count should be 1 but it is not match with expected"); //Should only have one item !!

  propMapAssign = propMap ;

  unsigned int uCountAssign  = propMapAssign.Count();
  DALI_CHECK_FAIL( uCountAssign != uCountReal , "property count should be match with real map count");

  Property::Map propMapCopy (propMap) ;

  unsigned int uCountCopy  = propMapCopy.Count();
  DALI_CHECK_FAIL( uCountCopy != uCountReal , "property count should be match with real map count");

  propMap.Clear();
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not  empty after using clear Api  which is not expected");

  DaliLog::PrintPass();
}
void PropertyMapOperatorAssignmentP2()
{
  const string strMapFirst = "hello";
  const string strMapTwo = "world";
  const string strMapThree = "Tizen";
  const string strMapAssign = "Assing Me";
  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  propMap[ strMapFirst] =  1;
  propMap[ strMapTwo  ]   =  2;
  propMap[ strMapThree] =  3;

  unsigned int uCountReal = propMap.Count();

  DALI_CHECK_FAIL(propMap.Empty(), "property is  empty which is not expected");

  DALI_CHECK_FAIL( uCountReal != 3 , "property count should be 3 but it is not match with expected"); //Should only have three items !!

  Property::Map propMapAssign ;

  propMapAssign [strMapAssign ] = 4 ;
  DALI_CHECK_FAIL(propMapAssign.Count() != 1, "property count should be 1 but it is not match with expected"); //Should only have one item !!

  propMapAssign = propMap ;

  unsigned int uCountAssign  = propMapAssign.Count();
  DALI_CHECK_FAIL( uCountAssign != uCountReal , "property count should be match with real map count");

  Property::Map propMapCopy (propMap) ;

  unsigned int uCountCopy  = propMapCopy.Count();
  DALI_CHECK_FAIL( uCountCopy != uCountReal , "property count should be match with real map count");

  propMap.Clear();
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not  empty after using clear Api  which is not expected");

  DaliLog::PrintPass();
}
void PropertyMapOperatorAssignmentP3()
{
  const string strMapFirst = "hello";
  const string strMapTwo = "world";
  const string strMapThree = "Tizen";
  const string strMapAssign = "Assing Me";
  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  propMap[ strMapFirst] =  1;
  propMap[ strMapTwo  ]   =  2;
  propMap[ strMapThree] =  3;

  unsigned int uCountReal = propMap.Count();

  DALI_CHECK_FAIL(propMap.Empty(), "property is  empty which is not expected");

  DALI_CHECK_FAIL( uCountReal != 3 , "property count should be 3 but it is not match with expected"); //Should only have three items !!

  Property::Map propMapAssign ;

  propMapAssign [strMapAssign ] = 4 ;
  DALI_CHECK_FAIL(propMapAssign.Count() != 1, "property count should be 1 but it is not match with expected"); //Should only have one item !!

  propMapAssign = propMap ;

  unsigned int uCountAssign  = propMapAssign.Count();
  DALI_CHECK_FAIL( uCountAssign != uCountReal , "property count should be match with real map count");

  Property::Map propMapCopy (propMap) ;

  unsigned int uCountCopy  = propMapCopy.Count();
  DALI_CHECK_FAIL( uCountCopy != uCountReal , "property count should be match with real map count");

  propMap.Clear();
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not  empty after using clear Api  which is not expected");

  DaliLog::PrintPass();
}
void PropertyMapSquareOperatorP()
{
  const Property::Index indexMapFirst = 10;
  const Property::Index indexMapTwo = 20;
  const Property::Index indexMapThree = 30;

  const int nSetValueOne = 1 ,nSetValueTwo = 2  , nSetValueThree = 3 ;

  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  unsigned int uCountReal = propMap.Count();
  DALI_CHECK_FAIL( uCountReal != 0 , "property count should be 0 but it is not match with expected"); //Should only have zero items !!

  propMap[indexMapFirst] = nSetValueOne;
  Property::Value* valueGet = propMap.Find( indexMapFirst );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueOne ," Square operator is setting the wrong value");

  propMap[indexMapTwo] = nSetValueTwo;
  valueGet = propMap.Find( indexMapTwo );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueTwo ," Square operator is setting the wrong value");

  propMap[indexMapThree] = nSetValueThree;
  valueGet = propMap.Find( indexMapThree );
  DALI_CHECK_FAIL( valueGet->Get<int>() != nSetValueThree ," Square operator is setting the wrong value");

  DaliLog::PrintPass();
}

void PropertyMapConstSquareOperatorP()
{
  const Property::Index indexMapFirst = 10;
  const int nSetValueOne = 1;

  Property::Map propMap;
  DALI_CHECK_FAIL(!propMap.Empty(), "property is not empty which is not expected");

  unsigned int uCountReal = propMap.Count();
  DALI_CHECK_FAIL( uCountReal != 0 , "property count should be 0 but it is not match with expected"); //Should only have zero items !!

  propMap[indexMapFirst] = nSetValueOne;
  Property::Value* valueGet = propMap.Find( indexMapFirst );

  const Property::Map& constPropMap = propMap;
  DALI_CHECK_FAIL( constPropMap[indexMapFirst].Get<int>() != nSetValueOne, "Square operator is retrieving the wrong value" );

  DaliLog::PrintPass();
}
void PropertyKeyConstructorP()
{
  Property::Key key1( "aKey" );
  DALI_CHECK_FAIL( key1.type != Property::Key::STRING, " Property::Key type is not matched");
  DALI_CHECK_FAIL( key1.stringKey != "aKey", " Property::Key stringkey is not matched");
  DALI_CHECK_FAIL( key1.indexKey != Property::INVALID_INDEX, " Property::Key indexkey is not matched");

  Property::Key key2( Actor::Property::COLOR );
  DALI_CHECK_FAIL( key2.type != Property::Key::INDEX, " Property::Key type is not matched");
  DALI_CHECK_FAIL( key2.indexKey != (Dali::Property::Index)Actor::Property::COLOR, " Property::Key indexkey is not matched");

  DaliLog::PrintPass();
  
}

void PropertyKeyEqualityOperatorP()
{
  Property::Key key1( "aKey" );
  Property::Key key2( 113 );

  DALI_CHECK_FAIL( !(key1 == "aKey")    , " Property::Key EqualityOperator test failed");
  DALI_CHECK_FAIL( key1 == "notTheKey" , " Property::Key EqualityOperator test failed");
  DALI_CHECK_FAIL( key1 == 1            , " Property::Key EqualityOperator test failed");

  DALI_CHECK_FAIL( !(key2 == 113)                     , " Property::Key EqualityOperator test failed");
  DALI_CHECK_FAIL( key2 == 0                          , " Property::Key EqualityOperator test failed");
  DALI_CHECK_FAIL( key2 == "One hundred and thirteen" , " Property::Key EqualityOperator test failed");

  DALI_CHECK_FAIL( key1 == key2    , " Property::Key EqualityOperator test failed");
  DALI_CHECK_FAIL( !(key1 != key2) , " Property::Key EqualityOperator test failed");

  Property::Key key1B( "aKey" );
  Property::Key key2B( 113 );

  DALI_CHECK_FAIL( !(key1 == key1B) , " Property::Key EqualityOperator test failed");
  DALI_CHECK_FAIL( !(key2 == key2B) , " Property::Key EqualityOperator test failed");

  DaliLog::PrintPass();;
}
void PropertyKeyInequalityOperatorP()
{
  Property::Key key1( "aKey" );
  Property::Key key2( 113 );

  DALI_CHECK_FAIL( !(key1 != "notTheKey") , " Property::Key EqualityOperator test failed");
  DALI_CHECK_FAIL( !(key1 != 1)           , " Property::Key EqualityOperator test failed");

  DALI_CHECK_FAIL( !(key2 != 0)                         , " Property::Key EqualityOperator test failed");
  DALI_CHECK_FAIL( !(key2 != "One hundred and thirteen"), " Property::Key EqualityOperator test failed");

  DALI_CHECK_FAIL( !(key1 != key2)                      , " Property::Key EqualityOperator test failed");

  DaliLog::PrintPass();
}

void PropertyKeyOutputStream()
{
  Property::Key key1( "aKey" );
  Property::Key key2( 113 );

  std::ostringstream oss;
  oss << key1;
  DALI_CHECK_FAIL( oss.str() != "aKey", " PropertyKey output stream test failed");

  std::ostringstream oss2;
  oss2 << key2;
  DALI_CHECK_FAIL( oss2.str() != "113", " PropertyKey output stream test failed");

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/



/**
 * @testcase         UtcDaliPropertyMapConstructorP
 * @since_tizen      2.4
 * @description      Check if property map constructor works fine
 */
int UtcDaliPropertyMapConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_CONSTRUCTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcPropertyMapConstructorInitializerListP
 * @since_tizen      5.5
 * @description      Check if property map initializer_list constructor works fine
 */
int UtcDaliPropertyMapConstructorInitializerListP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_CONSTRUCTOR_INITIALIZER_LIST);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapCopyConstructorP
 * @since_tizen      2.4
 * @description      Check if property map copy constructor and assignment operator works fine
 */
int UtcDaliPropertyMapCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_COPYCONSTRUCTOR);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase         UtcDaliPropertyMapCountP
 * @since_tizen      2.4
 * @description      Check if property map count works fine
 */
int UtcDaliPropertyMapCountP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_COUNT);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase         UtcDaliPropertyMapEmptyP
 * @since_tizen      2.4
 * @description      Check if property map empty works fine
 */
int UtcDaliPropertyMapEmptyP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_EMPTY);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase         UtcDaliPropertyMapInsertP
 * @since_tizen      2.4
 * @description      Check if property map empty works fine
 */
int UtcDaliPropertyMapInsertP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_INSERT);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase         UtcDaliPropertyMapInsertP2
 * @since_tizen      2.4
 * @description      Check if property map empty works fine
 */
int UtcDaliPropertyMapInsertP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_INSERT_P2);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapInsertP3
 * @since_tizen      3.0
 * @description      Check if we can insert an index-value pair to a property-map
 */
int UtcDaliPropertyMapInsertP3(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_INSERT_P3);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapInsertP4
 * @since_tizen      3.0
 * @description      Check if we can insert an index-value pair to a property-map
 */
int UtcDaliPropertyMapInsertP4(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_INSERT_P4);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapAddP
 * @since_tizen      4.0
 * @description      Check if we can add an index-value pair to a property-map
 */
int UtcDaliPropertyMapAddP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_ADD);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapAddChainP
 * @since_tizen      4.0
 * @description      Check if we can add an index-value pair to a property-map
 */
int UtcDaliPropertyMapAddChainP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_ADD_CHAIN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapAnonymousAddChainP
 * @since_tizen      4.0
 * @description      Check if we can add an index-value pair to a property-map
 */
int UtcDaliPropertyMapAnonymousAddChainP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_ANONYMOUS_ADD_CHAIN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapGetValueP
 * @since_tizen      2.4
 * @description      Check if Getpair,GetValue,GetKey Api working properly or not
 */
int UtcDaliPropertyMapGetValueP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_GET_VALUE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapGetKeyP
 * @since_tizen      2.4
 * @description      Check if Getpair,GetValue,GetKey Api working properly or not
 */
int UtcDaliPropertyMapGetKeyP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_GET_KEY);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapGetKeyAtP
 * @since_tizen      4.0
 * @description      Check if Getpair,GetValue,GetKey Api working properly or not
 */
int UtcDaliPropertyMapGetKeyAtP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_GET_KEY_AT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapGetPairP
 * @since_tizen      2.4
 * @description      Check if Getpair,GetValue,GetKey Api working properly or not
 */
int UtcDaliPropertyMapGetPairP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_GET_KEY_VALUE_PAIR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapGetKeyValueP
 * @since_tizen      4.0
 * @description      Check if Getpair,GetValue,GetKey Api working properly or not
 */
int UtcDaliPropertyMapGetKeyValueP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_GET_KEY_VALUE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapFindP
 * @since_tizen      2.4
 * @description      Check if Getpair,GetValue,GetKey Api working properly or not
 */
int UtcDaliPropertyMapFindP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_FIND);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapFindP2
 * @since_tizen      2.4
 * @description      Check if Getpair,GetValue,GetKey Api working properly or not
 */
int UtcDaliPropertyMapFindP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_FIND_P2);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapFindP3
 * @since_tizen      2.4
 * @description      Check if Getpair,GetValue,GetKey Api working properly or not
 */
int UtcDaliPropertyMapFindP3(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_FIND_P3);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapFindP4
 * @since_tizen      2.4
 * @description      Check Find with an index param
 */
int UtcDaliPropertyMapFindP4(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_FIND_P4);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapFindP5
 * @since_tizen      2.4
 * @description      Check Find with an index param and a property type param
 */
int UtcDaliPropertyMapFindP5(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_FIND_P5);
  application.MainLoop();
  return test_return_value;
}

/**
* @testcase         UtcDaliPropertyMapFindP6
* @since_tizen      3.0
* @description      Check if Find with 2 params api works properly or not
*/
int UtcDaliPropertyMapFindP6(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_FIND_P6);
  application.MainLoop();
    return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapFindN
 * @since_tizen      2.4
 * @description      Check Find with an index param and a mismatching property type
 */
int UtcDaliPropertyMapFindN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_FIND_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapClearP
 * @since_tizen      2.4
 * @description      Check if Getpair,GetValue,GetKey Api working properly or not
 */
int UtcDaliPropertyMapClearP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_CLEAR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapMergeP
 * @since_tizen      2.4
 * @description      Check if Getpair,GetValue,GetKey Api working properly or not
 */
int UtcDaliPropertyMapMergeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_MERGE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapOperatorAssignment
 * @since_tizen      2.4
 * @description      Check if assignment operator is working properly or not
 */
int UtcDaliPropertyMapOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_ASSIGNMENT_OPERATOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapOperatorAssignmentP2
 * @since_tizen      2.4
 * @description      Check if assignment operator is working properly or not
 */
int UtcDaliPropertyMapOperatorAssignmentP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_ASSIGNMENT_OPERATOR_P2);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapOperatorAssignmentP3
 * @since_tizen      2.4
 * @description      Check if assignment operator is working properly or not
 */
int UtcDaliPropertyMapOperatorAssignmentP3(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_ASSIGNMENT_OPERATOR_P3);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapSquareOperatorP
 * @since_tizen      2.4
 * @description      Check if the square operator works
 */
int UtcDaliPropertyMapSquareOperatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_SQUARE_OPERATOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyMapConstSquareOperatorP
 * @since_tizen      2.4
 * @description      Check if the const square operator works
 */
int UtcDaliPropertyMapConstSquareOperatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_MAP_CONST_SQUARE_OPERATOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyKeyConstructorP
 * @since_tizen      4.0
 * @description      Check if property key constructor works fine
 */
int UtcDaliPropertyKeyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_KEY_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyKeyEqualityOperatorP
 * @since_tizen      4.0
 * @description      Check if property key equality operation works
 */
int UtcDaliPropertyKeyEqualityOperatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_KEY_EQUALITY_OPERATOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyKeyInequalityOperatorP
 * @since_tizen      4.0
 * @description      Check if property key inequality operation works
 */
int UtcDaliPropertyKeyInequalityOperatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_KEY_INEQUALITY_OPERATOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyKeyOutputStream
 * @since_tizen      4.0
 * @description      Check if property key output stream works
 */
int UtcDaliPropertyKeyOutputStream(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Map_TestApp testApp( application, PROPERTY_KEY_OUTPUT_STREAM);
  application.MainLoop();
  return test_return_value;
}
