#ifndef _UTC_DALI_CAMERA_ACTOR_COMMON_H_
#define _UTC_DALI_CAMERA_ACTOR_COMMON_H_

#include "dali-common.h"

using namespace Dali;

#define SUITE_NAME  "CAMERA_ACTOR_UTC"

#define TASK_NUMBER  0
#define CAMERAACTOR_EPSYLON  0.001f
#define IMAGE_HEIGHT	1920.0f
#define IMAGE_WIDTH	1080.0f

// actor child check
bool  CameraActorHasAncestor (Actor actorChild, Actor actorAncestor);

#endif  //_UTC_DALI_CAMERA_ACTOR_COMMON_H_
