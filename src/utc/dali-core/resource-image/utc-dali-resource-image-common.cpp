#include "utc-dali-resource-image-common.h"

void ResourceImageAddActorToStage(Dali::Image image)
{
  Actor imageActor = ImageView::New(image);
  Stage::GetCurrent().Add(imageActor);
  imageActor.SetSize((float)RESOURCE_IMAGE_WIDTH, (float)RESOURCE_IMAGE_HEIGHT);
  imageActor.SetVisible(true);
}
