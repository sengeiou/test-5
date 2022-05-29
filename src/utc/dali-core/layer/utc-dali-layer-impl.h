#include "utc-dali-layer-common.h"

Actor gActor1, gActor2;
static int gLayerTestSortFunctionCalled;
int gRenderCountLinearLayer;
#define PUSH_BUTTON_IMAGE_ONE  "dali_imagemodule_image.png"

static float LayerTestSortFunction(const Vector3& /*position*/)
{
  ++gLayerTestSortFunctionCalled;
  return 0.0f;
}

void LayerConstructorP()
{
  Layer layer;
  DALI_CHECK_FAIL(layer, "Layer::Layer() is failed." );
  DaliLog::PrintPass();
}

void LayerCopyConstructorP()
{
  Layer layer1 = Layer::New();
  DALI_CHECK_FAIL(!layer1, "Layer::New() is failed." );

  Layer layer2(layer1);
  DALI_CHECK_FAIL(!layer2, "Layer::Layer(Layer &) is failed." );
  DaliLog::PrintPass();
}

void LayerOperatorAssignmentP()
{
  Layer layer1 = Layer::New();
  DALI_CHECK_FAIL(!layer1, "Layer::New() is failed." );
  Layer layer2 = layer1;
  DALI_CHECK_FAIL(!layer2, "Layer::operator= is failed." );
  DaliLog::PrintPass();
}

void LayerNewP()
{
  Layer layer = Layer::New();
  DALI_CHECK_FAIL(!layer, "Layer::New() is failed." );
  DaliLog::PrintPass();
}

void LayerIsHoverConsumedP()
{
  bool bIsHoverConsumed = true;

  Layer layer = Layer::New();
  DALI_CHECK_FAIL(!layer, "Layer::New() is failed." );
  Stage::GetCurrent().Add(layer);
  layer.SetHoverConsumed(bIsHoverConsumed);
  DALI_CHECK_FAIL(layer.IsHoverConsumed() != bIsHoverConsumed, "Layer::IsHoverConsumed() is failed. mismatches with the previously set value by Layer::SetHoverConsumed()." );
  bIsHoverConsumed = false;
  layer.SetHoverConsumed(bIsHoverConsumed);
  DALI_CHECK_FAIL(layer.IsHoverConsumed() != bIsHoverConsumed, "Layer::IsHoverConsumed() is failed. mismatches with the previously set value by Layer::SetHoverConsumed()." );

  Stage::GetCurrent().Remove(layer);
  DaliLog::PrintPass();
}

void LayerSetHoverConsumedP()
{
  bool bIsHoverConsumed = true;

  Layer layer = Layer::New();
  DALI_CHECK_FAIL(!layer, "Layer::New() is failed." );
  Stage::GetCurrent().Add(layer);
  layer.SetHoverConsumed(bIsHoverConsumed);
  DALI_CHECK_FAIL(layer.IsHoverConsumed() != bIsHoverConsumed, "Layer::IsHoverConsumed() is failed. mismatches with the previously set value by Layer::SetHoverConsumed()." );
  bIsHoverConsumed = false;
  layer.SetHoverConsumed(bIsHoverConsumed);
  DALI_CHECK_FAIL(layer.IsHoverConsumed() != bIsHoverConsumed, "Layer::IsHoverConsumed() is failed. mismatches with the previously set value by Layer::SetHoverConsumed()." );

  Stage::GetCurrent().Remove(layer);
  DaliLog::PrintPass();
}

void LayerIsTouchConsumedP()
{
  bool bIsTouchConsumed = true;
  Layer layer = Layer::New();
  DALI_CHECK_FAIL(!layer, "Layer::New() is failed." );
  Stage::GetCurrent().Add(layer);
  layer.SetTouchConsumed(bIsTouchConsumed);

  DALI_CHECK_FAIL(layer.IsTouchConsumed() != bIsTouchConsumed, "Layer::IsTouchConsumed() is failed. mismatches with the previously set value by Layer::SetTouchConsumed()." );
  bIsTouchConsumed = false;
  layer.SetTouchConsumed(bIsTouchConsumed);
  DALI_CHECK_FAIL(layer.IsTouchConsumed() != bIsTouchConsumed, "Layer::IsTouchConsumed() is failed. mismatches with the previously set value by Layer::SetTouchConsumed()." );

  Stage::GetCurrent().Remove(layer);
  DaliLog::PrintPass();
}

void LayerSetTouchConsumedP()
{
  bool bIsTouchConsumed = true;
  Layer layer = Layer::New();
  DALI_CHECK_FAIL(!layer, "Layer::New() is failed." );
  Stage::GetCurrent().Add(layer);
  layer.SetTouchConsumed(bIsTouchConsumed);

  DALI_CHECK_FAIL(layer.IsTouchConsumed() != bIsTouchConsumed, "Layer::IsTouchConsumed() is failed. mismatches with the previously set value by Layer::SetTouchConsumed()." );
  bIsTouchConsumed = false;
  layer.SetTouchConsumed(bIsTouchConsumed);
  DALI_CHECK_FAIL(layer.IsTouchConsumed() != bIsTouchConsumed, "Layer::IsTouchConsumed() is failed. mismatches with the previously set value by Layer::SetTouchConsumed()." );

  Stage::GetCurrent().Remove(layer);
  DaliLog::PrintPass();
}

void LayerDownCastP()
{
  Layer layer = Layer::New();
  DALI_CHECK_FAIL(!layer, "Layer::New() is failed." );

  Stage::GetCurrent().Add(layer);
  BaseHandle object(layer);
  Layer layer2 = Layer::DownCast(object);
  DALI_CHECK_FAIL(!layer2, "Layer::DownCast is failed." );

  Stage::GetCurrent().Remove(layer);
  DaliLog::PrintPass();
}

void LayerDownCastP2()
{
  Layer layer = Layer::New();
  DALI_CHECK_FAIL(!layer, "Layer::New() is failed." );
  Stage::GetCurrent().Add(layer);
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed." );

  actor.Add(layer);
  Actor childActor = actor.GetChildAt(0);

  Layer layer2 = DownCast< Layer >(childActor);
  DALI_CHECK_FAIL(!layer2, "Layer::DownCast is failed" );

  Stage::GetCurrent().Remove(layer);
  DaliLog::PrintPass();
}

void LayerGetDepthP()
{
  unsigned int unGetDepth = 11u;

  Layer layer1 = Layer::New();
  DALI_CHECK_FAIL(!layer1, "Layer::New() is failed" );
  Layer layer2 = Layer::New();
  DALI_CHECK_FAIL(!layer2, "Layer::New() is failed" );
  Layer rootLayer = Stage::GetCurrent().GetLayer(0);

  Stage::GetCurrent().Add(layer1);
  Stage::GetCurrent().Add(layer2);
  unGetDepth = rootLayer.GetDepth();
  if (unGetDepth != 0u)
  {
    LOG_E("unGetDepth should be 0u but it is:");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  unGetDepth = layer1.GetDepth();
  if (unGetDepth != 1u)
  {
    LOG_E("unGetDepth should be 1u but it is:");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  unGetDepth = layer2.GetDepth();
  if (unGetDepth != 2u)
  {
    LOG_E("unGetDepth should be 2u but it is:");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  Stage::GetCurrent().Remove(layer1);
  unGetDepth = layer2.GetDepth();
  DALI_CHECK_FAIL(unGetDepth != 1u, "unGetDepth should be 1u but it is:");

  Stage::GetCurrent().Remove(layer2);
  DaliLog::PrintPass();
}

void LayerLowerBelowToBottomP()
{
  unsigned int unGetDepth = 11u;

  Layer layer1 = Layer::New();
  DALI_CHECK_FAIL(!layer1, "Layer::New() is failed" );
  Layer layer2 = Layer::New();
  DALI_CHECK_FAIL(!layer2, "Layer::New() is failed" );

  Layer rootLayer = Stage::GetCurrent().GetLayer(0);
  unGetDepth = rootLayer.GetDepth();
  DALI_CHECK_FAIL(unGetDepth != 0u, "unGetDepth should be 0u but it is:");

  Stage::GetCurrent().Add(layer1);
  Stage::GetCurrent().Add(layer2);
  unGetDepth = layer1.GetDepth();
  if (unGetDepth != 1u)
  {
    LOG_E("unGetDepth should be 1u but it is:");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  unGetDepth = layer2.GetDepth();
  if (unGetDepth != 2u)
  {
    LOG_E("unGetDepth should be 2u but it is:");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  layer2.Lower();

  unGetDepth = layer2.GetDepth();
  if (unGetDepth != 1u)
  {
    LOG_E("unGetDepth should be 1u but it is:");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }
  unGetDepth = layer1.GetDepth();
  if (unGetDepth != 2u)
  {
    LOG_E("unGetDepth should be 2u but it is:");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }
  layer1.LowerBelow(layer2);
  unGetDepth = layer1.GetDepth();
  if (unGetDepth != 1u)
  {
    LOG_E("unGetDepth should be 1u but it is:");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  unGetDepth = layer2.GetDepth();
  if (unGetDepth != 2u)
  {
    LOG_E("unGetDepth should be 2u but it is:");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  layer2.LowerToBottom();

  unGetDepth = layer2.GetDepth();
  if (unGetDepth != 0u)
  {
    LOG_E("unGetDepth should be 0u but it is:");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  unGetDepth = rootLayer.GetDepth();
  if (unGetDepth != 1u)
  {
    LOG_E("unGetDepth should be 1u but it is:");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  unGetDepth = layer1.GetDepth();
  DALI_CHECK_FAIL(unGetDepth != 2u, "unGetDepth should be 2u but it is:");

  Stage::GetCurrent().Remove(layer1);
  Stage::GetCurrent().Remove(layer2);

  DaliLog::PrintPass();
}

void LayerMoveAboveBelowP()
{
  unsigned int unGetDepth = 11u;

  Layer layer1 = Layer::New();
  DALI_CHECK_FAIL(!layer1, "Layer::New() is failed " );
  Layer layer2 = Layer::New();
  DALI_CHECK_FAIL(!layer2, "Layer::New() is failed " );

  Layer rootLayer = Stage::GetCurrent().GetLayer(0);
  unGetDepth = rootLayer.GetDepth();
  DALI_CHECK_FAIL(unGetDepth != 0u, "unGetDepth should be 0u but it is:");

  Stage::GetCurrent().Add(layer1);
  Stage::GetCurrent().Add(layer2);

  unGetDepth = layer1.GetDepth();
  if (unGetDepth != 1u)
  {
    LOG_E("unGetDepth should be 1u but it is:");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  unGetDepth = layer2.GetDepth();
  if (unGetDepth != 2u)
  {

    LOG_E("unGetDepth should be 2u but it is:");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  layer1.MoveAbove(layer2);
  unGetDepth = layer1.GetDepth();
  if (unGetDepth != 2u)
  {

    LOG_E("unGetDepth should be 2u but it is:");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  unGetDepth = layer2.GetDepth();
  if (unGetDepth != 1u)
  {
    LOG_E("unGetDepth should be 1u but it is:");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  layer2.MoveBelow(rootLayer);
  unGetDepth = layer2.GetDepth();
  if (unGetDepth != 0u)
  {
    LOG_E("unGetDepth should be 0u but it is:");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  unGetDepth = rootLayer.GetDepth();
  if (unGetDepth != 1u)
  {
    LOG_E("unGetDepth should be 1u but it is:");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  unGetDepth = layer1.GetDepth();
  DALI_CHECK_FAIL(unGetDepth != 2u, "unGetDepth should be 2u but it is:");

  Stage::GetCurrent().Remove(layer1);
  Stage::GetCurrent().Remove(layer2);
  DaliLog::PrintPass();
}

void LayerRaiseAboveToTopP()
{
  unsigned int unGetDepth = 11u;

  Layer layer1 = Layer::New();
  DALI_CHECK_FAIL(!layer1, "Layer::New() is failed" );
  Layer layer2 = Layer::New();
  DALI_CHECK_FAIL(!layer2, "Layer::New() is failed" );

  Layer rootLayer = Stage::GetCurrent().GetLayer(0);
  unGetDepth = rootLayer.GetDepth();
  DALI_CHECK_FAIL(unGetDepth != 0u, "unGetDepth should be 0u but it is");

  Stage::GetCurrent().Add(layer1);
  Stage::GetCurrent().Add(layer2);
  unGetDepth = layer1.GetDepth();
  if (unGetDepth != 1u)
  {
    LOG_E("unGetDepth should be 1u but it is:");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  unGetDepth = layer2.GetDepth();
  if (unGetDepth != 2u)
  {
    LOG_E("unGetDepth should be 2u but it is:");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  layer1.Raise();
  unGetDepth = layer1.GetDepth();
  if (unGetDepth != 2u)
  {
    LOG_E("unGetDepth should be 2u but it is");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  unGetDepth = layer2.GetDepth();
  if (unGetDepth != 1u)
  {
    LOG_E("unGetDepth should be 1u but it is");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  layer2.RaiseAbove(layer1);
  unGetDepth = layer2.GetDepth();
  if (unGetDepth != 2u)
  {
    LOG_E("unGetDepth should be 2u but it is");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  unGetDepth = layer1.GetDepth();
  if (unGetDepth != 1u)
  {
    LOG_E("unGetDepth should be 0u but it is");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  rootLayer.RaiseToTop();
  unGetDepth = rootLayer.GetDepth();
  if (unGetDepth != 2u)
  {
    LOG_E("unGetDepth should be 2u but it is");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  unGetDepth = layer1.GetDepth();
  if (unGetDepth != 0u)
  {
    LOG_E("unGetDepth should be 0u but it is");
    Stage::GetCurrent().Remove(layer1);
    Stage::GetCurrent().Remove(layer2);
    test_return_value=1;
    return;
  }

  unGetDepth = layer2.GetDepth();
  DALI_CHECK_FAIL(unGetDepth != 1u, "unGetDepth should be 1u but it is");

  Stage::GetCurrent().Remove(layer1);
  Stage::GetCurrent().Remove(layer2);

  DaliLog::PrintPass();
}

void LayerSetClippingBoxP()
{
  int nX=0, nY=0, nHeight=0, nWidth=0;

  Layer layer = Layer::New();
  DALI_CHECK_FAIL(!layer, "Layer::New() is failed" );
  Stage::GetCurrent().Add(layer);

  ClippingBox clipGetTestBox = layer.GetClippingBox();
  DALI_CHECK_FAIL(clipGetTestBox != ClippingBox(nX,nY,nHeight,nWidth), "The set and get value is not matched" );

  nX++; nY++; nHeight+=5; nWidth+=5;
  layer.SetClippingBox(nX,nY,nHeight,nWidth);

  clipGetTestBox = layer.GetClippingBox();
  DALI_CHECK_FAIL(clipGetTestBox != ClippingBox(nX,nY,nHeight,nWidth), "The set and get value is not matched" );

  Stage::GetCurrent().Remove(layer);
  DaliLog::PrintPass();
}

void LayerSetClippingBoxP2()
{
  int nX=0, nY=0, nHeight=0, nWidth=0;

  Layer layer = Layer::New();
  DALI_CHECK_FAIL(!layer, "Layer::New() is failed" );
  Stage::GetCurrent().Add(layer);

  ClippingBox clipGetTestBox = layer.GetClippingBox();
  DALI_CHECK_FAIL(clipGetTestBox != ClippingBox(nX,nY,nHeight,nWidth), "The set and get value is not matched" );

  nX++; nY++; nHeight+=5; nWidth+=5;
  layer.SetClippingBox(nX,nY,nHeight,nWidth);

  clipGetTestBox = layer.GetClippingBox();
  DALI_CHECK_FAIL(clipGetTestBox != ClippingBox(nX,nY,nHeight,nWidth), "The set and get value is not matched" );

  ClippingBox clipTestBox(nX,nY,nHeight,nWidth);
  layer.SetClippingBox(clipTestBox);
  clipGetTestBox = layer.GetClippingBox();
  DALI_CHECK_FAIL(clipGetTestBox != clipTestBox, "The set and get value is not matched" );

  Stage::GetCurrent().Remove(layer);
  DaliLog::PrintPass();
}

void LayerGetClippingBoxP()
{
  int nX=0, nY=0, nHeight=0, nWidth=0;

  Layer layer = Layer::New();
  DALI_CHECK_FAIL(!layer, "Layer::New() is failed" );
  Stage::GetCurrent().Add(layer);

  ClippingBox clipGetTestBox = layer.GetClippingBox();
  DALI_CHECK_FAIL(clipGetTestBox != ClippingBox(nX,nY,nHeight,nWidth), "The set and get value is not matched" );

  nX++; nY++; nHeight+=5; nWidth+=5;
  layer.SetClippingBox(nX,nY,nHeight,nWidth);

  clipGetTestBox = layer.GetClippingBox();
  DALI_CHECK_FAIL(clipGetTestBox != ClippingBox(nX,nY,nHeight,nWidth), "The set and get value is not matched" );

  ClippingBox clipTestBox(nX,nY,nHeight,nWidth);
  layer.SetClippingBox(clipTestBox);
  clipGetTestBox = layer.GetClippingBox();
  DALI_CHECK_FAIL(clipGetTestBox != clipTestBox, "The set and get value is not matched" );

  Stage::GetCurrent().Remove(layer);
  DaliLog::PrintPass();
}

void LayerSetDepthTestDisabledP()
{
  bool bIsDepthTest = true , bSetTestDisable = true ;

  Layer layer = Layer::New();
  DALI_CHECK_FAIL(!layer, "Layer::New() is failed" );
  Stage::GetCurrent().Add(layer);

  layer.SetDepthTestDisabled(bSetTestDisable);
  bIsDepthTest = layer.IsDepthTestDisabled();

  DALI_CHECK_FAIL(bSetTestDisable!=bIsDepthTest, "IsDepthTestDisabled should be true but it is false" );

  Stage::GetCurrent().Remove(layer);

  DaliLog::PrintPass();
}

void LayerIsDepthTestDisabledP()
{
  bool bIsDepthTest = true , bSetTestDisable = true ;

  Layer layer = Layer::New();
  DALI_CHECK_FAIL(!layer, "Layer::New() is failed" );
  Stage::GetCurrent().Add(layer);

  layer.SetDepthTestDisabled(bSetTestDisable);
  bIsDepthTest = layer.IsDepthTestDisabled();

  DALI_CHECK_FAIL(bSetTestDisable!=bIsDepthTest, "IsDepthTestDisabled should be true but it is false" );

  Stage::GetCurrent().Remove(layer);

  DaliLog::PrintPass();
}

void LayerSetClippingP()
{
  bool bIsClipEnabled = true , bSetClipEnable = true ;

  Layer layer = Layer::New();
  DALI_CHECK_FAIL(!layer, "Layer::New() is failed" );
  Stage::GetCurrent().Add(layer);

  layer.SetClipping(bSetClipEnable);
  bIsClipEnabled = layer.IsClipping();
  DALI_CHECK_FAIL(bSetClipEnable!=bIsClipEnabled, "IsClipping should be true but it is false" );
  Stage::GetCurrent().Remove(layer);
  DaliLog::PrintPass();
}

void LayerIsClippingP()
{
  bool bIsClipEnabled = true , bSetClipEnable = true ;

  Layer layer = Layer::New();
  DALI_CHECK_FAIL(!layer, "Layer::New() is failed" );
  Stage::GetCurrent().Add(layer);

  layer.SetClipping(bSetClipEnable);
  bIsClipEnabled = layer.IsClipping();
  DALI_CHECK_FAIL(bSetClipEnable!=bIsClipEnabled, "IsClipping should be true but it is false" );
  Stage::GetCurrent().Remove(layer);
  DaliLog::PrintPass();
}

void LayerSetSortFunctionP(void)
{
  BufferImage img = BufferImage::New( 1,1 );

  // create two transparent actors so there is something to sort
  gActor1 = ImageView::New(img);
  gActor2 = ImageView::New(img);
  gActor1.SetSize(1,1);
  gActor1.SetColor( Vector4(1, 1, 1, 0.5f ) ); // 50% transparent
  gActor2.SetSize(1,1);
  gActor2.SetColor( Vector4(1, 1, 1, 0.5f ) ); // 50% transparent

  // add to stage
  Stage::GetCurrent().Add( gActor1 );
  Stage::GetCurrent().Add( gActor2 );

  Layer root = Stage::GetCurrent().GetLayer( 0 );
  gLayerTestSortFunctionCalled = 0;
  root.SetSortFunction(LayerTestSortFunction);
}

void VTLayerSetSortFunction001(void)
{
  DALI_CHECK_FAIL(gLayerTestSortFunctionCalled == 0, "SetSortFunction  is not  called." );

  Stage::GetCurrent().Remove(gActor1);
  Stage::GetCurrent().Remove(gActor2);

  DaliLog::PrintPass();
}

void LayerSetBehaviorP()
{
  Layer layer = Layer::New();

  DALI_CHECK_FAIL(layer.GetBehavior() != Dali::Layer::LAYER_UI, "setbehavior and getbehavior mismatch" );
  layer.SetBehavior(Dali::Layer::LAYER_3D );
  DALI_CHECK_FAIL(layer.GetBehavior() != Dali::Layer::LAYER_3D, "setbehavior and getbehavior mismatch" );
  DaliLog::PrintPass();
}

void LayerGetBehaviorP()
{
  Layer layer = Layer::New();

  DALI_CHECK_FAIL(layer.GetBehavior() != Dali::Layer::LAYER_UI, "setbehavior and getbehavior mismatch" );
  layer.SetBehavior(Dali::Layer::LAYER_3D );
  DALI_CHECK_FAIL(layer.GetBehavior() != Dali::Layer::LAYER_3D, "setbehavior and getbehavior mismatch" );
  DaliLog::PrintPass();
}
