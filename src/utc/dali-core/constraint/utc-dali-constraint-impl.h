#include "utc-dali-constraint-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

Actor gConstraintActor;             /** Actor instance**/
Actor gSourceActor;                 /** Actor instance**/
Constraint gConstraint;             /** Constraint instance**/
Property::Index gConstraintIndex;   /** Index of property**/
Property::Index gConstraintSourceIndex;   /** Index of property**/
int gRenderCountConstraint = 0;     /** Render count **/

/**Matrix start and target value**/
Matrix gConstraintMatStartValue, gConstraintMatTargetValue;
/**Matrix3 start and target value**/
Matrix3 gConstraintMat3StartValue(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
Matrix3 gConstraintMat3TargetValue(2.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 2.0f);


/**
 * ##############################
 * TC Logic Implementation Area.
 * ##############################
 **/

void ConstraintSetGetTagP()
{
  bool bZero(false);

  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintIndex = gConstraintActor.RegisterProperty("boolean-property", bZero);
  if(!ConstraintTypeEquals<bool>(gConstraintActor.GetProperty<bool>(gConstraintIndex), bZero, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    LOG_E("Actor::RegisterProperty() is failed.");
    test_return_value=TC_FAIL;
  }
  gConstraint = Constraint::New<bool>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<bool>(CONSTRAINT_BOOL_START));
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<bool>() is failed.");
  //    gConstraint.Apply();
  DALI_CHECK_FAIL(gConstraint.GetTag() != 0u, "Constraint::GetTag() has failed");
  DaliLog::PrintPass();
}

void ConstraintSetGetTagP2()
{
  bool bZero(false);

  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintIndex = gConstraintActor.RegisterProperty("boolean-property", bZero);
  if(!ConstraintTypeEquals<bool>(gConstraintActor.GetProperty<bool>(gConstraintIndex), bZero, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    LOG_E("Actor::RegisterProperty() is failed.");
    test_return_value=TC_FAIL;
  }
  gConstraint = Constraint::New<bool>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<bool>(CONSTRAINT_BOOL_START));
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<bool>() is failed.");
  const unsigned int tag = 123;
  gConstraint.SetTag( tag );
  DALI_CHECK_FAIL((gConstraint.GetTag() != tag), "Constraint::GetTag() has failed");
  DaliLog::PrintPass();
}


void ConstraintNewOnStageBooleanP()
{
  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintIndex = gConstraintActor.RegisterProperty( "boolean-property", CONSTRAINT_BOOL_START );
  if ( !ConstraintTypeEquals< bool >( gConstraintActor.GetProperty< bool >( gConstraintIndex ), CONSTRAINT_BOOL_START, CONSTRAINT_EPSILON ) )
  {
    Stage::GetCurrent().Remove( gConstraintActor );
    LOG_E( "Actor::RegisterProperty() is failed." );
    test_return_value = TC_FAIL;
  }

  gConstraintSourceIndex = gConstraintActor.RegisterProperty( "source-boolean-property", CONSTRAINT_BOOL_START );
  if( !ConstraintTypeEquals< bool >( gConstraintActor.GetProperty< bool >( gConstraintSourceIndex ), CONSTRAINT_BOOL_START, CONSTRAINT_EPSILON ) )
  {
    Stage::GetCurrent().Remove( gConstraintActor );
    LOG_E( "Actor::RegisterProperty() is failed." );
    test_return_value = TC_FAIL;
  }

  gConstraint = Constraint::New<bool>( gConstraintActor, gConstraintIndex, STConstraintTypeValue< bool >() );
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New< bool >() is failed.");
  gConstraint.AddSource( LocalSource( gConstraintSourceIndex ) );
  gConstraint.Apply();
}

void ConstraintNewOnStageIntegerP()
{
  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintIndex = gConstraintActor.RegisterProperty( "integer-property", CONSTRAINT_INT_START );
  if( !ConstraintTypeEquals< int >( gConstraintActor.GetProperty< int >( gConstraintIndex ), CONSTRAINT_INT_START, CONSTRAINT_EPSILON ) )
  {
    Stage::GetCurrent().Remove( gConstraintActor );
    LOG_E( "Actor::RegisterProperty() is failed" );
    test_return_value = TC_FAIL;
    return;
  }

  gConstraintSourceIndex = gConstraintActor.RegisterProperty( "source-integer-property", CONSTRAINT_INT_START );
  if( !ConstraintTypeEquals< int >( gConstraintActor.GetProperty< int >( gConstraintSourceIndex ), CONSTRAINT_INT_START, CONSTRAINT_EPSILON ) )
  {
    Stage::GetCurrent().Remove( gConstraintActor );
    LOG_E( "Actor::RegisterProperty() is failed." );
    test_return_value = TC_FAIL;
  }

  gConstraint = Constraint::New< int >( gConstraintActor, gConstraintIndex, STConstraintTypeValue< int >() );
  DALI_CHECK_FAIL( !gConstraint, "Constraint::New< int >() is failed" );
  gConstraint.AddSource( LocalSource( gConstraintSourceIndex ) );
  gConstraint.Apply();
}

void ConstraintNewOnStageFloatP()
{
  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintIndex = gConstraintActor.RegisterProperty( "float-property", CONSTRAINT_FLOAT_START );
  if( !ConstraintTypeEquals< float >( gConstraintActor.GetProperty< float >( gConstraintIndex ), CONSTRAINT_FLOAT_START, CONSTRAINT_EPSILON ) )
  {
    Stage::GetCurrent().Remove( gConstraintActor );
    LOG_E( "Actor::RegisterProperty() is failed" );
    test_return_value = TC_FAIL;
    return;
  }

  gConstraintSourceIndex = gConstraintActor.RegisterProperty( "source-float-property", CONSTRAINT_FLOAT_START );
  if( !ConstraintTypeEquals< float >( gConstraintActor.GetProperty< float >( gConstraintSourceIndex ), CONSTRAINT_FLOAT_START, CONSTRAINT_EPSILON ) )
  {
    Stage::GetCurrent().Remove( gConstraintActor );
    LOG_E( "Actor::RegisterProperty() is failed." );
    test_return_value = TC_FAIL;
  }

  gConstraint = Constraint::New< float >( gConstraintActor, gConstraintIndex, STConstraintTypeValue< float >() );
  DALI_CHECK_FAIL( !gConstraint, "Constraint::New< float >() is failed" );
  gConstraint.AddSource( LocalSource( gConstraintSourceIndex ) );
  gConstraint.Apply();
}

void ConstraintNewOnStageVector2P()
{
  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintIndex = gConstraintActor.RegisterProperty( "vector2-property", CONSTRAINT_VEC2_START );
  if( !ConstraintTypeEquals< Vector2 >( gConstraintActor.GetProperty< Vector2 >( gConstraintIndex ), CONSTRAINT_VEC2_START, CONSTRAINT_EPSILON ) )
  {
    Stage::GetCurrent().Remove( gConstraintActor );
    LOG_E( "Actor::RegisterProperty() is failed" );
    test_return_value = TC_FAIL;
    return;
  }

  gConstraintSourceIndex = gConstraintActor.RegisterProperty( "source-vector2-property", CONSTRAINT_VEC2_START );
  if( !ConstraintTypeEquals< Vector2 >( gConstraintActor.GetProperty< Vector2 >( gConstraintSourceIndex ), CONSTRAINT_VEC2_START, CONSTRAINT_EPSILON ) )
  {
    Stage::GetCurrent().Remove( gConstraintActor );
    LOG_E( "Actor::RegisterProperty() is failed." );
    test_return_value = TC_FAIL;
  }

  gConstraint = Constraint::New< Vector2 >( gConstraintActor, gConstraintIndex, STConstraintTypeValue< Vector2 >() );
  DALI_CHECK_FAIL( !gConstraint, "Constraint::New< Vector2 >() is failed" );
  gConstraint.AddSource( LocalSource( gConstraintSourceIndex ) );
  gConstraint.Apply();
}

void ConstraintNewOnStageVector3P()
{
  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintIndex = gConstraintActor.RegisterProperty( "vector3-property", CONSTRAINT_VEC3_START );
  if( !ConstraintTypeEquals< Vector3 >( gConstraintActor.GetProperty< Vector3 >( gConstraintIndex ), CONSTRAINT_VEC3_START, CONSTRAINT_EPSILON ) )
  {
    Stage::GetCurrent().Remove( gConstraintActor );
    LOG_E( "Actor::RegisterProperty() is failed" );
    test_return_value = TC_FAIL;
    return;
  }

  gConstraintSourceIndex = gConstraintActor.RegisterProperty( "source-vector3-property", CONSTRAINT_VEC3_START );
  if( !ConstraintTypeEquals< Vector3 >( gConstraintActor.GetProperty< Vector3 >( gConstraintSourceIndex ), CONSTRAINT_VEC3_START, CONSTRAINT_EPSILON ) )
  {
    Stage::GetCurrent().Remove( gConstraintActor );
    LOG_E( "Actor::RegisterProperty() is failed." );
    test_return_value = TC_FAIL;
  }

  gConstraint = Constraint::New< Vector3 >( gConstraintActor, gConstraintIndex, STConstraintTypeValue< Vector3 >() );
  DALI_CHECK_FAIL( !gConstraint, "Constraint::New< Vector3 >() is failed" );
  gConstraint.AddSource( LocalSource( gConstraintSourceIndex ) );
  gConstraint.Apply();
}

void ConstraintNewOnStageVector4P()
{
  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintIndex = gConstraintActor.RegisterProperty( "vector4-property", CONSTRAINT_VEC4_START );
  if( !ConstraintTypeEquals< Vector4 >( gConstraintActor.GetProperty< Vector4 >( gConstraintIndex ), CONSTRAINT_VEC4_START, CONSTRAINT_EPSILON ) )
  {
    Stage::GetCurrent().Remove( gConstraintActor );
    LOG_E( "Actor::RegisterProperty() is failed" );
    test_return_value = TC_FAIL;
    return;
  }

  gConstraintSourceIndex = gConstraintActor.RegisterProperty( "source-vector4-property", CONSTRAINT_VEC4_START );
  if( !ConstraintTypeEquals< Vector4 >( gConstraintActor.GetProperty< Vector4 >( gConstraintSourceIndex ), CONSTRAINT_VEC4_START, CONSTRAINT_EPSILON ) )
  {
    Stage::GetCurrent().Remove( gConstraintActor );
    LOG_E( "Actor::RegisterProperty() is failed." );
    test_return_value = TC_FAIL;
  }

  gConstraint = Constraint::New< Vector4 >( gConstraintActor, gConstraintIndex, STConstraintTypeValue< Vector4 >() );
  DALI_CHECK_FAIL( !gConstraint, "Constraint::New< Vector4 >() is failed" );
  gConstraint.AddSource( LocalSource( gConstraintSourceIndex ) );
  gConstraint.Apply();
}

void ConstraintNewOnStageMatrixP()
{
  gConstraintMatStartValue.SetTranslation(CONSTRAINT_VEC4_START);
  gConstraintMatTargetValue.SetTranslation(CONSTRAINT_VEC4_TARGET);

  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintIndex = gConstraintActor.RegisterProperty( "matrix-property", gConstraintMatStartValue );
  if( !ConstraintTypeEquals< Matrix >( gConstraintActor.GetProperty< Matrix >( gConstraintIndex ), gConstraintMatStartValue, CONSTRAINT_EPSILON ) )
  {
    Stage::GetCurrent().Remove( gConstraintActor );
    LOG_E( "Actor::RegisterProperty() is failed" );
    test_return_value = TC_FAIL;
    return;
  }

  gConstraintSourceIndex = gConstraintActor.RegisterProperty( "source-matrix-property", gConstraintMatStartValue );
  if( !ConstraintTypeEquals< Matrix >( gConstraintActor.GetProperty< Matrix >( gConstraintSourceIndex ), gConstraintMatStartValue, CONSTRAINT_EPSILON ) )
  {
    Stage::GetCurrent().Remove( gConstraintActor );
    LOG_E( "Actor::RegisterProperty() is failed." );
    test_return_value = TC_FAIL;
  }

  gConstraint = Constraint::New< Matrix >( gConstraintActor, gConstraintIndex, STConstraintTypeValue< Matrix >() );
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New< Matrix >() is failed");
  gConstraint.AddSource( LocalSource( gConstraintSourceIndex ) );
  gConstraint.Apply();
}

void ConstraintNewOnStageMatrix3P()
{
  gConstraintMat3StartValue.Scale(1.1f);
  gConstraintMat3TargetValue.Scale(1.1f);

  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintIndex = gConstraintActor.RegisterProperty( "matrix3-property", gConstraintMat3StartValue );
  if( !ConstraintTypeEquals< Matrix3 >( gConstraintActor.GetProperty< Matrix3 >( gConstraintIndex ), gConstraintMat3StartValue, CONSTRAINT_EPSILON ) )
  {
    Stage::GetCurrent().Remove( gConstraintActor );
    LOG_E( "Actor::RegisterProperty() is failed" );
    test_return_value = TC_FAIL;
    return;
  }

  gConstraintSourceIndex = gConstraintActor.RegisterProperty( "source-matrix3-property", gConstraintMat3StartValue );
  if( !ConstraintTypeEquals< Matrix3 >( gConstraintActor.GetProperty< Matrix3 >( gConstraintSourceIndex ), gConstraintMat3StartValue, CONSTRAINT_EPSILON ) )
  {
    Stage::GetCurrent().Remove( gConstraintActor );
    LOG_E( "Actor::RegisterProperty() is failed." );
    test_return_value = TC_FAIL;
  }

  gConstraint = Constraint::New< Matrix3 >( gConstraintActor, gConstraintIndex, STConstraintTypeValue< Matrix3 >() );
  DALI_CHECK_FAIL( !gConstraint, "Constraint::New< Matrix3 >() is failed" );
  gConstraint.AddSource( LocalSource( gConstraintSourceIndex ) );
  gConstraint.Apply();
}

void ConstraintNewOnStageQuaternionP()
{
  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintIndex = gConstraintActor.RegisterProperty( "quaternion-property", CONSTRAINT_QT_START );
  if( !ConstraintTypeEquals< Quaternion >( gConstraintActor.GetProperty< Quaternion >( gConstraintIndex ), CONSTRAINT_QT_START, CONSTRAINT_EPSILON ) )
  {
    Stage::GetCurrent().Remove( gConstraintActor );
    LOG_E( "Actor::RegisterProperty() is failed" );
    test_return_value = TC_FAIL;
    return;
  }

  gConstraintSourceIndex = gConstraintActor.RegisterProperty( "source-quaternion-property", CONSTRAINT_QT_START );
  if( !ConstraintTypeEquals< Quaternion >( gConstraintActor.GetProperty< Quaternion >( gConstraintSourceIndex ), CONSTRAINT_QT_START, CONSTRAINT_EPSILON ) )
  {
    Stage::GetCurrent().Remove( gConstraintActor );
    LOG_E( "Actor::RegisterProperty() is failed." );
    test_return_value = TC_FAIL;
  }

  gConstraint = Constraint::New< Quaternion >( gConstraintActor, gConstraintIndex, STConstraintTypeValue< Quaternion >() );
  DALI_CHECK_FAIL( !gConstraint, "Constraint::New< Quaternion >() is failed" );
  gConstraint.AddSource( LocalSource( gConstraintSourceIndex ) );
  gConstraint.Apply();
}

void ConstraintNewOnStageBooleanAddSourceP()
{
  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  if(!ConstraintCreateHandle(gSourceActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintIndex = gConstraintActor.RegisterProperty("boolean-property", CONSTRAINT_BOOL_START);
  if(!ConstraintTypeEquals<bool>(gConstraintActor.GetProperty<bool>(gConstraintIndex), CONSTRAINT_BOOL_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for propertyIndex");
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintSourceIndex = gSourceActor.RegisterProperty("source-boolean-property", CONSTRAINT_BOOL_START);
  if(!ConstraintTypeEquals<bool>(gSourceActor.GetProperty<bool>(gConstraintSourceIndex), CONSTRAINT_BOOL_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for gConstraintSourceIndex");
    test_return_value=TC_FAIL;
    return;
  }

  ConstraintSource constraintSource = Source(gSourceActor, gConstraintSourceIndex);
  gConstraint = Constraint::New<bool>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<bool>());
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<bool>() is failed");
  gConstraint.AddSource(constraintSource);
  gConstraint.Apply();
}

void ConstraintNewOnStageBooleanAddSourceParentP()
{
  if(!ConstraintCreateHandle(gSourceActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  if(!ConstraintCreateHandle(gConstraintActor, false))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gSourceActor.Add(gConstraintActor);
  gConstraintIndex = gConstraintActor.RegisterProperty("boolean-property", CONSTRAINT_BOOL_START);
  if(!ConstraintTypeEquals<bool>(gConstraintActor.GetProperty<bool>(gConstraintIndex), CONSTRAINT_BOOL_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for propertyIndex");
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintSourceIndex = gSourceActor.RegisterProperty("parent-boolean-property", CONSTRAINT_BOOL_START);
  if(!ConstraintTypeEquals<bool>(gSourceActor.GetProperty<bool>(gConstraintSourceIndex), CONSTRAINT_BOOL_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for gConstraintSourceIndex");
    test_return_value=TC_FAIL;
    return;
  }

  ConstraintSource constraintParentSource = ParentSource(gConstraintSourceIndex);
  gConstraint = Constraint::New<bool>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<bool>());
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<bool>() is failed");
  gConstraint.AddSource(constraintParentSource);
  gConstraint.Apply();
}

void ConstraintNewOnStageIntegerAddSourceP()
{
  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }
  if(!ConstraintCreateHandle(gSourceActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }
  gConstraintIndex = gConstraintActor.RegisterProperty("integer-property", CONSTRAINT_INT_START);
  if(!ConstraintTypeEquals<int>(gConstraintActor.GetProperty<int>(gConstraintIndex), CONSTRAINT_INT_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for propertyIndex");
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintSourceIndex = gSourceActor.RegisterProperty("source-integer-property", CONSTRAINT_INT_START);
  if(!ConstraintTypeEquals<int>(gSourceActor.GetProperty<int>(gConstraintSourceIndex), CONSTRAINT_INT_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for gConstraintSourceIndex");
    test_return_value=TC_FAIL;
    return;
  }

  ConstraintSource constraintSource = Source(gSourceActor, gConstraintSourceIndex);
  gConstraint = Constraint::New<int>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<int>());
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<int>() is failed");
  gConstraint.AddSource(constraintSource);
  gConstraint.Apply();
}

void ConstraintNewOnStageIntegerAddSourceParentP()
{
  if(!ConstraintCreateHandle(gSourceActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  if(!ConstraintCreateHandle(gConstraintActor, false))
  {
    test_return_value=TC_FAIL;
    return;
  }
  gSourceActor.Add(gConstraintActor);

  gConstraintIndex = gConstraintActor.RegisterProperty("integer-property", CONSTRAINT_INT_START);
  if(!ConstraintTypeEquals<int>(gConstraintActor.GetProperty<int>(gConstraintIndex), CONSTRAINT_INT_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for propertyIndex");
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintSourceIndex = gSourceActor.RegisterProperty("parent-integer-property", CONSTRAINT_INT_START);
  if(!ConstraintTypeEquals<int>(gSourceActor.GetProperty<int>(gConstraintSourceIndex), CONSTRAINT_INT_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for gConstraintSourceIndex");
    test_return_value=TC_FAIL;
  }

  ConstraintSource constraintParentSource = ParentSource(gConstraintSourceIndex);
  gConstraint = Constraint::New<int>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<int>());
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<int>() is failed");
  gConstraint.AddSource(constraintParentSource);
  gConstraint.Apply();
}

void ConstraintNewOnStageFloatAddSourceP()
{
  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }
  if(!ConstraintCreateHandle(gSourceActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }
  gConstraintIndex = gConstraintActor.RegisterProperty("float-property", CONSTRAINT_FLOAT_START);
  if(!ConstraintTypeEquals<float>(gConstraintActor.GetProperty<float>(gConstraintIndex), CONSTRAINT_FLOAT_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for propertyIndex");
    test_return_value=TC_FAIL;
  }
  gConstraintSourceIndex = gSourceActor.RegisterProperty("source-float-property", CONSTRAINT_FLOAT_START);
  if(!ConstraintTypeEquals<float>(gSourceActor.GetProperty<float>(gConstraintSourceIndex), CONSTRAINT_FLOAT_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for gConstraintSourceIndex");
    test_return_value=TC_FAIL;
  }
  ConstraintSource constraintSource = Source(gSourceActor, gConstraintSourceIndex);
  gConstraint = Constraint::New<float>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<float>());
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<float>() is failed");
  gConstraint.AddSource(constraintSource);
  gConstraint.Apply();
}

void ConstraintNewOnStageFloatAddSourceParentP()
{
  if(!ConstraintCreateHandle(gSourceActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  if(!ConstraintCreateHandle(gConstraintActor, false))
  {
    test_return_value=TC_FAIL;
    return;
  }
  gSourceActor.Add(gConstraintActor);
  gConstraintIndex = gConstraintActor.RegisterProperty("float-property", CONSTRAINT_FLOAT_START);
  if(!ConstraintTypeEquals<float>(gConstraintActor.GetProperty<float>(gConstraintIndex), CONSTRAINT_FLOAT_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for propertyIndex");
    test_return_value=TC_FAIL;
    return;
  }
  gConstraintSourceIndex = gSourceActor.RegisterProperty("parent-float-property", CONSTRAINT_FLOAT_START);
  if(!ConstraintTypeEquals<float>(gSourceActor.GetProperty<float>(gConstraintSourceIndex), CONSTRAINT_FLOAT_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for gConstraintSourceIndex");
    test_return_value=TC_FAIL;
    return;
  }

  ConstraintSource constraintParentSource = ParentSource(gConstraintSourceIndex);
  gConstraint = Constraint::New<float>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<float>());
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<float>() is failed");
  gConstraint.AddSource(constraintParentSource);
  gConstraint.Apply();
}

void ConstraintNewOnStageVector2AddSourceP()
{
  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }
  if(!ConstraintCreateHandle(gSourceActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }
  gConstraintIndex = gConstraintActor.RegisterProperty("vector2-property", CONSTRAINT_VEC2_START);
  if(!ConstraintTypeEquals<Vector2>(gConstraintActor.GetProperty<Vector2>(gConstraintIndex), CONSTRAINT_VEC2_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for propertyIndex");
    test_return_value=TC_FAIL;
    return;
  }
  gConstraintSourceIndex = gSourceActor.RegisterProperty("source-vector2-property", CONSTRAINT_VEC2_START);
  if(!ConstraintTypeEquals<Vector2>(gSourceActor.GetProperty<Vector2>(gConstraintSourceIndex), CONSTRAINT_VEC2_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for gConstraintSourceIndex");
    test_return_value=TC_FAIL;
    return;
  }
  ConstraintSource constraintSource = Source(gSourceActor, gConstraintSourceIndex);
  gConstraint = Constraint::New<Vector2>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<Vector2>());
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<Vector2>() is failed");
  gConstraint.AddSource(constraintSource);
  gConstraint.Apply();
}

void ConstraintNewOnStageVector2AddSourceParentP()
{
  if(!ConstraintCreateHandle(gSourceActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  if(!ConstraintCreateHandle(gConstraintActor, false))
  {
    test_return_value=TC_FAIL;
    return;
  }
  gSourceActor.Add(gConstraintActor);

  gConstraintIndex = gConstraintActor.RegisterProperty("vector2-property", CONSTRAINT_VEC2_START);
  if(!ConstraintTypeEquals<Vector2>(gConstraintActor.GetProperty<Vector2>(gConstraintIndex), CONSTRAINT_VEC2_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for propertyIndex");
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintSourceIndex = gSourceActor.RegisterProperty("parent-vector2-property", CONSTRAINT_VEC2_START);
  if(!ConstraintTypeEquals<Vector2>(gSourceActor.GetProperty<Vector2>(gConstraintSourceIndex), CONSTRAINT_VEC2_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for gConstraintSourceIndex");
    test_return_value=TC_FAIL;
    return;
  }

  ConstraintSource constraintParentSource = ParentSource(gConstraintSourceIndex);
  gConstraint = Constraint::New<Vector2>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<Vector2>());
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<Vector2>() is failed");
  gConstraint.AddSource(constraintParentSource);
  gConstraint.Apply();
}

void ConstraintNewOnStageVector3AddSourceP()
{
  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }
  if(!ConstraintCreateHandle(gSourceActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintIndex = gConstraintActor.RegisterProperty("vector3-property", CONSTRAINT_VEC3_START);
  if(!ConstraintTypeEquals<Vector3>(gConstraintActor.GetProperty<Vector3>(gConstraintIndex), CONSTRAINT_VEC3_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for propertyIndex");
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintSourceIndex = gSourceActor.RegisterProperty("source-vector3-property", CONSTRAINT_VEC3_START);
  if(!ConstraintTypeEquals<Vector3>(gSourceActor.GetProperty<Vector3>(gConstraintSourceIndex), CONSTRAINT_VEC3_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for gConstraintSourceIndex");
    test_return_value=TC_FAIL;
    return;
  }
  ConstraintSource constraintSource = Source(gSourceActor, gConstraintSourceIndex);
  gConstraint = Constraint::New<Vector3>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<Vector3>());
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<Vector3>() is failed");
  gConstraint.AddSource(constraintSource);
  gConstraint.Apply();
}

void ConstraintNewOnStageVector3AddSourceParentP()
{
  if(!ConstraintCreateHandle(gSourceActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  if(!ConstraintCreateHandle(gConstraintActor, false))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gSourceActor.Add(gConstraintActor);
  gConstraintIndex = gConstraintActor.RegisterProperty("vector3-property", CONSTRAINT_VEC3_START);
  if(!ConstraintTypeEquals<Vector3>(gConstraintActor.GetProperty<Vector3>(gConstraintIndex), CONSTRAINT_VEC3_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for propertyIndex");
    test_return_value=TC_FAIL;
    return;
  }
  gConstraintSourceIndex = gSourceActor.RegisterProperty("parent-vector3-property", CONSTRAINT_VEC3_START);
  if(!ConstraintTypeEquals<Vector3>(gSourceActor.GetProperty<Vector3>(gConstraintSourceIndex), CONSTRAINT_VEC3_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for gConstraintSourceIndex");
    test_return_value=TC_FAIL;
    return;
  }

  ConstraintSource constraintParentSource = ParentSource(gConstraintSourceIndex);
  gConstraint = Constraint::New<Vector3>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<Vector3>());
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<Vector3>() is failed");
  gConstraint.AddSource(constraintParentSource);
  gConstraint.Apply();
}

void ConstraintNewOnStageMatrixAddSourceP()
{
  gConstraintMatStartValue.SetTranslation(CONSTRAINT_VEC4_START);
  gConstraintMatTargetValue.SetTranslation(CONSTRAINT_VEC4_TARGET);

  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  if(!ConstraintCreateHandle(gSourceActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }
  gConstraintIndex = gConstraintActor.RegisterProperty("matrix-property", gConstraintMatStartValue);
  if(!ConstraintTypeEquals<Matrix>(gConstraintActor.GetProperty<Matrix>(gConstraintIndex), gConstraintMatStartValue, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for propertyIndex");
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintSourceIndex = gSourceActor.RegisterProperty("source-matrix-property", gConstraintMatStartValue);
  if(!ConstraintTypeEquals<Matrix>(gSourceActor.GetProperty<Matrix>(gConstraintSourceIndex), gConstraintMatStartValue, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for gConstraintSourceIndex");
    test_return_value=TC_FAIL;
    return;
  }

  ConstraintSource constraintSource = Source(gSourceActor, gConstraintSourceIndex);
  gConstraint = Constraint::New<Matrix>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<Matrix>());
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<Matrix>() is failed");
  gConstraint.AddSource(constraintSource);
  gConstraint.Apply();
}

void ConstraintNewOnStageMatrixAddSourceParentP()
{
  gConstraintMatStartValue.SetTranslation(CONSTRAINT_VEC4_START);
  gConstraintMatTargetValue.SetTranslation(CONSTRAINT_VEC4_TARGET);

  if(!ConstraintCreateHandle(gSourceActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  if(!ConstraintCreateHandle(gConstraintActor, false))
  {
    test_return_value=TC_FAIL;
    return;
  }
  gSourceActor.Add(gConstraintActor);
  gConstraintIndex = gConstraintActor.RegisterProperty("matrix-property", gConstraintMatStartValue);
  if(!ConstraintTypeEquals<Matrix>(gConstraintActor.GetProperty<Matrix>(gConstraintIndex), gConstraintMatStartValue, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for propertyIndex");
    test_return_value=TC_FAIL;
    return;
  }
  gConstraintSourceIndex = gSourceActor.RegisterProperty("parent-matrix-property", gConstraintMatStartValue);
  if(!ConstraintTypeEquals<Matrix>(gSourceActor.GetProperty<Matrix>(gConstraintSourceIndex), gConstraintMatStartValue, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for gConstraintSourceIndex");
    test_return_value=TC_FAIL;
    return;
  }

  ConstraintSource constraintParentSource = ParentSource(gConstraintSourceIndex);
  gConstraint = Constraint::New<Matrix>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<Matrix>());
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<Matrix>() is failed");
  gConstraint.AddSource(constraintParentSource);
  gConstraint.Apply();
}

void ConstraintNewOnStageMatrix3AddSourceP()
{
  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }
  if(!ConstraintCreateHandle(gSourceActor, true))
  {
    test_return_value=TC_FAIL;
  }
  gConstraintIndex = gConstraintActor.RegisterProperty("matrix3-property", gConstraintMat3StartValue);
  if(!ConstraintTypeEquals<Matrix3>(gConstraintActor.GetProperty<Matrix3>(gConstraintIndex), gConstraintMat3StartValue, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for propertyIndex");
    test_return_value=TC_FAIL;
    return;
  }
  gConstraintSourceIndex = gSourceActor.RegisterProperty("source-matrix3-property", gConstraintMat3StartValue);
  if(!ConstraintTypeEquals<Matrix3>(gSourceActor.GetProperty<Matrix3>(gConstraintSourceIndex), gConstraintMat3StartValue, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for gConstraintSourceIndex");
    test_return_value=TC_FAIL;
    return;
  }
  ConstraintSource constraintSource = Source(gSourceActor, gConstraintSourceIndex);
  gConstraint = Constraint::New<Matrix3>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<Matrix3>());
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<Matrix3>() is failed");
  gConstraint.AddSource(constraintSource);
  gConstraint.Apply();
}

void ConstraintNewOnStageMatrix3AddSourceParentP()
{
  if(!ConstraintCreateHandle(gSourceActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  if(!ConstraintCreateHandle(gConstraintActor, false))
  {
    test_return_value=TC_FAIL;
    return;
  }
  gSourceActor.Add(gConstraintActor);
  gConstraintIndex = gConstraintActor.RegisterProperty("matrix3-property", gConstraintMat3StartValue);
  if(!ConstraintTypeEquals<Matrix3>(gConstraintActor.GetProperty<Matrix3>(gConstraintIndex), gConstraintMat3StartValue, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for propertyIndex");
    test_return_value=TC_FAIL;
    return;
  }
  gConstraintSourceIndex = gSourceActor.RegisterProperty("parent-matrix3-property", gConstraintMat3StartValue);
  if(!ConstraintTypeEquals<Matrix3>(gSourceActor.GetProperty<Matrix3>(gConstraintSourceIndex), gConstraintMat3StartValue, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for gConstraintSourceIndex");
    test_return_value=TC_FAIL;
    return;
  }

  ConstraintSource constraintParentSource = ParentSource(gConstraintSourceIndex);
  gConstraint = Constraint::New<Matrix3>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<Matrix3>());
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<Matrix3>() is failed");
  gConstraint.AddSource(constraintParentSource);
  gConstraint.Apply();
}

void ConstraintNewOnStageQuaternionAddSourceP()
{
  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }
  if(!ConstraintCreateHandle(gSourceActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }
  gConstraintIndex = gConstraintActor.RegisterProperty("quaternion-property", CONSTRAINT_QT_START);
  if(!ConstraintTypeEquals<Quaternion>(gConstraintActor.GetProperty<Quaternion>(gConstraintIndex), CONSTRAINT_QT_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for propertyIndex");
    test_return_value=TC_FAIL;
    return;
  }
  gConstraintSourceIndex = gSourceActor.RegisterProperty("source-quaternion-property", CONSTRAINT_QT_START);
  if(!ConstraintTypeEquals<Quaternion>(gSourceActor.GetProperty<Quaternion>(gConstraintSourceIndex), CONSTRAINT_QT_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for gConstraintSourceIndex");
    test_return_value=TC_FAIL;
    return;
  }
  ConstraintSource constraintSource = Source(gSourceActor, gConstraintSourceIndex);
  gConstraint = Constraint::New<Quaternion>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<Quaternion>());
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<Quaternion>() is failed");
  gConstraint.AddSource(constraintSource);
  gConstraint.Apply();
}

void ConstraintNewOnStageQuaternionAddSourceParentP()
{
  if(!ConstraintCreateHandle(gSourceActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  if(!ConstraintCreateHandle(gConstraintActor, false))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gSourceActor.Add(gConstraintActor);
  gConstraintIndex = gConstraintActor.RegisterProperty("quaternion-property", CONSTRAINT_QT_START);
  if(!ConstraintTypeEquals<Quaternion>(gConstraintActor.GetProperty<Quaternion>(gConstraintIndex), CONSTRAINT_QT_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for propertyIndex");
    test_return_value=TC_FAIL;
    return;
  }
  gConstraintSourceIndex = gSourceActor.RegisterProperty("parent-quaternion-property", CONSTRAINT_QT_START);
  if(!ConstraintTypeEquals<Quaternion>(gSourceActor.GetProperty<Quaternion>(gConstraintSourceIndex), CONSTRAINT_QT_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for gConstraintSourceIndex");
    test_return_value=TC_FAIL;
    return;
  }

  ConstraintSource constraintParentSource = ParentSource(gConstraintSourceIndex);
  gConstraint = Constraint::New<Quaternion>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<Quaternion>());
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<Quaternion>() is failed");
  gConstraint.AddSource(constraintParentSource);
  gConstraint.Apply();
}

void ConstraintNewOnStageVector2AddSourceLocalP()
{
  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintIndex = gConstraintActor.RegisterProperty("Vector2Property", CONSTRAINT_VEC2_START );
  if( !ConstraintTypeEquals<Vector2>(gConstraintActor.GetProperty<Vector2>(gConstraintIndex), CONSTRAINT_VEC2_START, CONSTRAINT_EPSILON) )
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    LOG_E("Actor::RegisterProperty() is failed for property 'Vector2Property'.");
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintSourceIndex = gConstraintActor.RegisterProperty("Vector2Property2", CONSTRAINT_VEC2_START );
  if( !ConstraintTypeEquals<Vector2>(gConstraintActor.GetProperty<Vector2>(gConstraintSourceIndex), CONSTRAINT_VEC2_START, CONSTRAINT_EPSILON) )
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    LOG_E("Actor::RegisterProperty() is failed for property 'Vector2Property2'.");
    test_return_value=TC_FAIL;
    return;
  }

  ConstraintSource constraintLocalSource = LocalSource(gConstraintSourceIndex);

  gConstraint = Constraint::New<Vector2>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<Vector2>());
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<Vector2>() is failed");
  gConstraint.AddSource(constraintLocalSource);
  gConstraint.Apply();
}

void ConstraintClonedDowncastP()
{
  if(!ConstraintCreateHandle(gSourceActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  if(!ConstraintCreateHandle(gConstraintActor, false))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gSourceActor.Add(gConstraintActor);
  gConstraintIndex = gConstraintActor.RegisterProperty("float-property", CONSTRAINT_FLOAT_START);
  if(!ConstraintTypeEquals<float>(gConstraintActor.GetProperty<float>(gConstraintIndex), CONSTRAINT_FLOAT_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for propertyIndex");
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintSourceIndex = gSourceActor.RegisterProperty("parent-float-property", CONSTRAINT_FLOAT_START);
  if(!ConstraintTypeEquals<float>(gSourceActor.GetProperty<float>(gConstraintSourceIndex), CONSTRAINT_FLOAT_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gSourceActor);
    LOG_E("Actor::RegisterProperty() is failed for gConstraintSourceIndex");
    test_return_value=TC_FAIL;
    return;
  }

  ConstraintSource constraintParentSource = ParentSource(gConstraintSourceIndex);
  Constraint constraint = Constraint::New<float>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<float>());
  DALI_CHECK_FAIL(!constraint, "Constraint::New<float>() is failed");

  BaseHandle baseHandle(constraint);
  Constraint downcastedConstraint = Constraint::DownCast(baseHandle);
  DALI_CHECK_FAIL(!downcastedConstraint, "Constraint::DownCast() is failed");
  downcastedConstraint.AddSource(constraintParentSource);

  gConstraint = downcastedConstraint.Clone(downcastedConstraint.GetTargetObject());
  DALI_CHECK_FAIL(!gConstraint, "Constraint::Clone is failed");
  gConstraint.Apply();
}


void ConstraintCopyConstructorP()
{
  bool bZero(false);

  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintIndex = gConstraintActor.RegisterProperty("boolean-property", bZero);
  if(!ConstraintTypeEquals<bool>(gConstraintActor.GetProperty<bool>(gConstraintIndex), bZero, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    LOG_E("Actor::RegisterProperty() is failed.");
    test_return_value=TC_FAIL;
  }
  gConstraint = Constraint::New<bool>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<bool>(CONSTRAINT_BOOL_START));
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<bool>() has failed.");


  Constraint constraint2 = gConstraint;
  DALI_CHECK_FAIL(!constraint2, "Constraint(const Constraint& constraint ) has failed.");

  //    gConstraint.Apply();
  DaliLog::PrintPass();

}

void ConstraintOperatorAssignmentP()
{
  bool bZero(false);

  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintIndex = gConstraintActor.RegisterProperty("boolean-property", bZero);
  if(!ConstraintTypeEquals<bool>(gConstraintActor.GetProperty<bool>(gConstraintIndex), bZero, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    LOG_E("Actor::RegisterProperty() is failed.");
    test_return_value=TC_FAIL;
  }
  gConstraint = Constraint::New<bool>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<bool>(CONSTRAINT_BOOL_START));
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<bool>() has failed.");

  Constraint constraint2;
  constraint2 = gConstraint;
  DALI_CHECK_FAIL(!constraint2, "Constraint::operator=(const Constraint& constraint ) has failed.");

  DaliLog::PrintPass();
}


void ConstraintGetTargetObjectP()
{
  bool bZero(false);

  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintIndex = gConstraintActor.RegisterProperty("boolean-property", bZero);
  if(!ConstraintTypeEquals<bool>(gConstraintActor.GetProperty<bool>(gConstraintIndex), bZero, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    LOG_E("Actor::RegisterProperty() is failed.");
    test_return_value=TC_FAIL;
  }
  gConstraint = Constraint::New<bool>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<bool>(CONSTRAINT_BOOL_START));
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<bool>() is failed.");

  DALI_CHECK_FAIL((gConstraint.GetTargetObject() != gConstraintActor), "Constraint::GetTargetObject() failed." );

  Actor actor2 = Actor::New();
  DALI_CHECK_FAIL( (gConstraint.GetTargetObject() == actor2 ), "Constraint::GetTargetObject() failed." );
  DaliLog::PrintPass();
}


void ConstraintGetTargetObjectN()
{
  // Attempt to retrieve from uninitialised constraint

  Constraint constraint;
  try
  {
    Handle handle = constraint.GetTargetObject();
    DALI_CHECK_FAIL( true, "Should not reach here" ); // Should not reach here!
  }
  catch( ... )
  {
    DALI_CHECK_FAIL( false, "Not able to get any target object from an uninitialized constraint" );
  }
  DaliLog::PrintPass();
}

void ConstraintGetTargetPropertyP()
{
  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintIndex = gConstraintActor.RegisterProperty("boolean-property", CONSTRAINT_BOOL_START);
  if(!ConstraintTypeEquals<bool>(gConstraintActor.GetProperty<bool>(gConstraintIndex), CONSTRAINT_BOOL_START, CONSTRAINT_EPSILON))
  {
    Stage::GetCurrent().Remove(gConstraintActor);
    LOG_E("Actor::RegisterProperty() is failed.");
    test_return_value=TC_FAIL;
  }

  gConstraintSourceIndex = gConstraintActor.RegisterProperty( "source-boolean-property", CONSTRAINT_BOOL_START );
  if( !ConstraintTypeEquals< bool >( gConstraintActor.GetProperty< bool >( gConstraintSourceIndex ), CONSTRAINT_BOOL_START, CONSTRAINT_EPSILON ) )
  {
    Stage::GetCurrent().Remove( gConstraintActor );
    LOG_E( "Actor::RegisterProperty() is failed." );
    test_return_value = TC_FAIL;
  }

  gConstraint = Constraint::New<bool>(gConstraintActor, gConstraintIndex, STConstraintTypeValue<bool>());
  DALI_CHECK_FAIL(!gConstraint, "Constraint::New<bool>() is failed.");
  gConstraint.AddSource( LocalSource( gConstraintSourceIndex ) );
  gConstraint.Apply();
}

void ConstraintGetTargetPropertyN()
{
  Constraint constraint;
  try
  {
    Property::Index propertyIndex = constraint.GetTargetProperty();
    ( void )propertyIndex;
    DALI_CHECK_FAIL( true, "Should not reach here" ); // Should not reach here!
  }
  catch( ... )
  {
    DALI_CHECK_FAIL( false, "Not able to get any target object from an uninitialized constraint" );
  }
  DaliLog::PrintPass();
}


template< class type >
void VTConstraintAppliedCheck( Actor actor, type tExpectedValue, type tTargetValue )
{
  DALI_CHECK_FAIL( gConstraint.GetTargetObject() != gConstraintActor, "Dali::Constraint::Apply() is failed to apply on actor." );
  DALI_CHECK_FAIL( gConstraint.GetTargetProperty() != gConstraintIndex, "Dali::Constraint::Apply() is failed to apply on actors property." );

  DALI_CHECK_FAIL( !ConstraintTypeEquals< type >( gConstraintActor.GetCurrentProperty< type >( gConstraintIndex ), tExpectedValue, CONSTRAINT_EPSILON ), "Property should be updated by constraint" );
  actor.SetProperty( gConstraintSourceIndex, tTargetValue );
}

template< class type >
void VTConstraintCheckPropertyBeforeRemove( Actor actor, type tExpectedValue, type tTargetValue )
{
  DALI_CHECK_FAIL( !ConstraintTypeEquals< type >( gConstraintActor.GetCurrentProperty< type >( gConstraintIndex ), tExpectedValue, CONSTRAINT_EPSILON ), "Property should be updated by constraint" );
  gConstraintActor.RemoveConstraints();
  actor.SetProperty( gConstraintSourceIndex, tTargetValue );
}

template<class type>
void VTConstraintFinalCheck( type tExpectedValue )
{
  DALI_CHECK_FAIL( ConstraintTypeEquals< type >( gConstraintActor.GetCurrentProperty< type >( gConstraintIndex ), tExpectedValue, CONSTRAINT_EPSILON ), "Constraint is not removed properly" );
  Stage::GetCurrent().Remove( gConstraintActor );
  DaliLog::PrintPass();
}

void ConstraintGetRemoveActionP()
{
  if(!ConstraintCreateHandle(gConstraintActor, true))
  {
    test_return_value=TC_FAIL;
    return;
  }

  gConstraintActor.SetPosition(Vector3::ONE);
}

void VTConstraintGetRemoveAction001()
{
  DALI_CHECK_FAIL( gConstraintActor.GetCurrentPosition() != Vector3::ONE,
      "Failed to get actor's initial position." );

  gConstraint = Constraint::New<Vector3>(gConstraintActor, Actor::Property::POSITION, STConstraintTypeValue<Vector3>(CONSTRAINT_VEC3_START));
  Constraint::RemoveAction removeActionGet = gConstraint.GetRemoveAction();
  DALI_CHECK_FAIL( removeActionGet != Constraint::Bake, "Failed to get default remove action" );
  gConstraint.Apply();
}

void VTConstraintGetRemoveAction002()
{
  DALI_CHECK_FAIL( gConstraintActor.GetCurrentPosition() == Vector3::ONE,
      "Actor's position should not be initially set position after constraint being appled." );

  DALI_CHECK_FAIL( gConstraintActor.GetCurrentPosition() != CONSTRAINT_VEC3_START,
      "Failed to get Actor's position applied bt constraint." );

  gConstraintActor.SetPosition(CONSTRAINT_VEC3_TARGET);
}

void VTConstraintGetRemoveAction003()
{
  DALI_CHECK_FAIL( gConstraintActor.GetCurrentPosition() != CONSTRAINT_VEC3_START,
      "Actor's position should not be changed before removal of constraint." );
  gConstraint.Remove();
}

void VTConstraintGetRemoveAction004()
{
  //Actor's position is baked, require set position again which change the actor's posion after constraint removal
  DALI_CHECK_FAIL( gConstraintActor.GetCurrentPosition() != CONSTRAINT_VEC3_START,
      "Failed to get actor's position which is baked." );
  gConstraintActor.SetPosition(CONSTRAINT_VEC3_TARGET);
}

void VTConstraintGetRemoveAction005()
{
  DALI_CHECK_FAIL( gConstraintActor.GetCurrentPosition() != CONSTRAINT_VEC3_TARGET,
      "Actor's position should be changed due to change in position after removal of constraint." );
  gConstraint.SetRemoveAction(Constraint::Discard);
  gConstraint.Apply();
}

void VTConstraintGetRemoveAction006()
{
  //Again checking the actor's position applied by constraint
  DALI_CHECK_FAIL( gConstraintActor.GetCurrentPosition() != CONSTRAINT_VEC3_START,
      "Failed to get actor's position after applying constraint for second time." );
  gConstraint.Remove();
}

void VTConstraintGetRemoveAction007()
{
  //After remove with Discard action, position is autometically changed into its previous position
  DALI_CHECK_FAIL( gConstraintActor.GetCurrentPosition() != CONSTRAINT_VEC3_TARGET,
      "Failed to get actor's previous position after constraint removal with remove action 'Discard'." );
  Stage::GetCurrent().Remove(gConstraintActor);
  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

