#ifndef _UTC_DALI_RENDERTASK_COMMON_H_
#define _UTC_DALI_RENDERTASK_COMMON_H_

#include "dali-common.h"
#include <dali/dali.h>
#include <dali-toolkit/dali-toolkit.h>

using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME  "RENDER_TASK_UTC"

#define TASK_INDEX  0
#define INVALID_TASK_COUNT 0
#define START_POINT 0
#define RENDER_TASK_INTERVAL 16
#define WAIT_TIME 10
#define RENDER_DELAY_TIME  1000u

typedef unsigned int GLuint;
extern const char* COMPOSITE_FRAGMENT_SOURCE;


//Helper to construct render task
bool RenderTaskConstruction( RenderTask& renderTask );

// Helper Compare the retrieved viewport size with the set size
bool RenderTaskSizeCompare( Dali::Vector2 vec2Set, Dali::Vector2 vec2Get);

//helper function for set & get ScreenToFrameBufferFunction
bool RenderTaskSetGetScreenToFrameBufferFunction(Dali::RenderTaskList& renderTaskList, RenderTask::ScreenToFrameBufferFunction  conversionFunction);

//Helper function for Initialization
bool RenderTaskinit(Stage &stage, RenderTaskList &renderTaskList, RenderTask  &renderTask);

// Helper function for loading an Image
Image ImageInitialization(GLuint textureId, int width, int height );

// Helper to reposition the actor to outside the stage while rendering with or without culling
bool RenderTaskActorRepositionOutside(Actor actor, float fx, float fy, bool bDrawn );

#endif  //_UTC_DALI_RENDERTASK_COMMON_H_

