#include "utc-dali-constraint-function-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

using namespace Dali;

namespace
{
  bool gFunctionCalled = false;

  template< typename T >
    void TestCallbackFunction( T& /* current*/ , const PropertyInputContainer& /* inputs */ )
    {
      gFunctionCalled = true;
    }

  bool gFunctorCalled = false;
  template< typename T >
    struct TestCallbackFunctor
    {
      TestCallbackFunctor() { }

      void operator()( T& /* current*/ , const PropertyInputContainer& /* inputs */ )
      {
        gFunctorCalled = true;
      }

    };

  bool gMethodFunctorCalled = false;
  template< typename T >
    struct TestFunctorMethod
    {
      TestFunctorMethod() { }

      void Method( T& /* current*/ , const PropertyInputContainer& /* inputs */ )
      {
        gMethodFunctorCalled = true;
      }

    };

} // unnamed namespace

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Constraint::Function::Function( void( *function )( P&, const PropertyInputContainer& ) )
///////////////////////////////////////////////////////////////////////////////
namespace
{
  template< typename T >
    void TestFunctionConstructor()
    {
      gFunctionCalled = false;
      Constraint::Function< T > function( &TestCallbackFunction< T > );
      T current;
      PropertyInputContainer inputs;

      DALI_CHECK_FAIL( gFunctionCalled != false, "Constraint::Function callback is not called");
      CallbackBase::Execute< T&, const PropertyInputContainer& >( function, current, inputs );
      DALI_CHECK_FAIL( gFunctionCalled != true, "Constraint::Function callback is called" );
    }
} // unnamed namespace

void ConstraintFunctionConstructorWithFunctionP()
{
  TestFunctionConstructor< bool >();
  TestFunctionConstructor< int >();
  TestFunctionConstructor< unsigned int >();
  TestFunctionConstructor< float >();
  TestFunctionConstructor< Vector2 >();
  TestFunctionConstructor< Vector3 >();
  TestFunctionConstructor< Vector4 >();
  TestFunctionConstructor< Quaternion >();
  TestFunctionConstructor< Matrix >();
  TestFunctionConstructor< Matrix3 >();

  DaliLog::PrintPass();
}

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Constraint::Function::Function( const T& object )
///////////////////////////////////////////////////////////////////////////////
namespace
{
  template< typename T >
    void TestFunctorConstructor()
    {
      gFunctorCalled = false;
      TestCallbackFunctor< T > functor;
      Constraint::Function< T > callback( functor );
      T current;
      PropertyInputContainer inputs;

      DALI_CHECK_FAIL( gFunctorCalled != false, "Constraint::Function::Function with functor is not called" );
      CallbackBase::Execute< T&, const PropertyInputContainer& >( callback, current, inputs );
      DALI_CHECK_FAIL( gFunctorCalled != true, "Constraint::Function::Function with functor is called");
    }
} // unnamed namespace

void ConstraintFunctionConstructorWithFunctorP()
{
  TestFunctorConstructor< bool >();
  TestFunctorConstructor< int >();
  TestFunctorConstructor< unsigned int >();
  TestFunctorConstructor< float >();
  TestFunctorConstructor< Vector2 >();
  TestFunctorConstructor< Vector3 >();
  TestFunctorConstructor< Vector4 >();
  TestFunctorConstructor< Quaternion >();
  TestFunctorConstructor< Matrix >();
  TestFunctorConstructor< Matrix3 >();

  DaliLog::PrintPass();
}

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Constraint::Function::Function( const T& object, void ( T::*memberFunction ) ( P&, const PropertyInputContainer& ) )
///////////////////////////////////////////////////////////////////////////////
namespace
{
  template< typename T >
    void TestFunctorMethodConstructor()
    {
      gMethodFunctorCalled = false;
      TestFunctorMethod< T > functor;
      Constraint::Function< T > callback( functor, &TestFunctorMethod< T >::Method );
      T current;
      PropertyInputContainer inputs;

      DALI_CHECK_FAIL( gMethodFunctorCalled != false, "Constraint::Function::Function constructor which copies a function object and allows a connection to a member method is not called");
      CallbackBase::Execute< T&, const PropertyInputContainer& >( callback, current, inputs );
      DALI_CHECK_FAIL( gMethodFunctorCalled != true, "Constraint::Function::Function constructor which copies a function object and allows a connection to a member method is called" );
    }
} // unnamed namespace

void ConstraintFunctionConstructorWithMethodFunctorP()
{
  TestFunctorMethodConstructor< bool >();
  TestFunctorMethodConstructor< int >();
  TestFunctorMethodConstructor< unsigned int >();
  TestFunctorMethodConstructor< float >();
  TestFunctorMethodConstructor< Vector2 >();
  TestFunctorMethodConstructor< Vector3 >();
  TestFunctorMethodConstructor< Vector4 >();
  TestFunctorMethodConstructor< Quaternion >();
  TestFunctorMethodConstructor< Matrix >();
  TestFunctorMethodConstructor< Matrix3 >();

  DaliLog::PrintPass();
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Constraint::Function::Clone
///////////////////////////////////////////////////////////////////////////////
namespace
{
  template< typename T >
    void TestFunctionClone()
    {
      gFunctionCalled = false;
      Constraint::Function< T > callback( &TestCallbackFunction< T > );
      CallbackBase* clone = callback.Clone();

      T current;
      PropertyInputContainer inputs;

      DALI_CHECK_FAIL( gFunctionCalled != false, "Constraint::Function::Clone is not called" );
      CallbackBase::Execute< T&, const PropertyInputContainer& >( *clone, current, inputs );
      DALI_CHECK_FAIL( gFunctionCalled != true, "Constraint::Function::Clone is called");
      delete clone;
    }

  template< typename T >
    void TestFunctorClone()
    {
      gFunctorCalled = false;
      TestCallbackFunctor< T > functor;
      Constraint::Function< T > callback( functor );
      CallbackBase* clone = callback.Clone();

      T current;
      PropertyInputContainer inputs;

      DALI_CHECK_FAIL( gFunctorCalled != false, "Constraint::Function::Clone with functor is not called" );
      CallbackBase::Execute< T&, const PropertyInputContainer& >( *clone, current, inputs );
      DALI_CHECK_FAIL( gFunctorCalled != true, "Constraint::Function::Clone with functor is called" );
      delete clone;
    }

  template< typename T >
    void TestMethodFunctorClone()
    {
      gMethodFunctorCalled = false;
      TestFunctorMethod< T > functor;
      Constraint::Function< T > callback( functor, &TestFunctorMethod< T >::Method );
      CallbackBase* clone = callback.Clone();

      T current;
      PropertyInputContainer inputs;

      DALI_CHECK_FAIL( gMethodFunctorCalled != false, "Constraint::Function::Clone with method functor is not called");
      CallbackBase::Execute< T&, const PropertyInputContainer& >( *clone, current, inputs );
      DALI_CHECK_FAIL( gMethodFunctorCalled != true, "Constraint::Function::Clone with method functor is called");
      delete clone;
    }

} // unnamed namespace

void ConstraintFunctionFunctionCloneP()
{
  TestFunctionClone< bool >();
  TestFunctionClone< int >();
  TestFunctionClone< unsigned int >();
  TestFunctionClone< float >();
  TestFunctionClone< Vector2 >();
  TestFunctionClone< Vector3 >();
  TestFunctionClone< Vector4 >();
  TestFunctionClone< Quaternion >();
  TestFunctionClone< Matrix >();
  TestFunctionClone< Matrix3 >();

  DaliLog::PrintPass();
}

void ConstraintFunctionFunctorCloneP()
{
  TestFunctorClone< bool >();
  TestFunctorClone< int >();
  TestFunctorClone< unsigned int >();
  TestFunctorClone< float >();
  TestFunctorClone< Vector2 >();
  TestFunctorClone< Vector3 >();
  TestFunctorClone< Vector4 >();
  TestFunctorClone< Quaternion >();
  TestFunctorClone< Matrix >();
  TestFunctorClone< Matrix3 >();

  DaliLog::PrintPass();
}

void ConstraintFunctionMethodFunctorCloneP()
{
  TestMethodFunctorClone< bool >();
  TestMethodFunctorClone< int >();
  TestMethodFunctorClone< unsigned int >();
  TestMethodFunctorClone< float >();
  TestMethodFunctorClone< Vector2 >();
  TestMethodFunctorClone< Vector3 >();
  TestMethodFunctorClone< Vector4 >();
  TestMethodFunctorClone< Quaternion >();
  TestMethodFunctorClone< Matrix >();
  TestMethodFunctorClone< Matrix3 >();

  DaliLog::PrintPass();
}
