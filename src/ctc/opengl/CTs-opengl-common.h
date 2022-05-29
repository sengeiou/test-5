//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef _CTS_OPENGL_COMMON_H_
#define _CTS_OPENGL_COMMON_H_

//Add test package related includes here

#include "tct_common.h"
#include <Elementary.h>
#include <Evas_GL.h>
#include <dlog.h>

/** @addtogroup ctc-opengl
* @ingroup		ctc
* @{
*/

#define API_NAMESPACE				"OPENGL2_CTC"
#define MAX_BLOCK_SIZE          	25
#define OPENGL2_WIN_WIDTH			320
#define OPENGL2_WIN_HEIGHT			480
#define TIME_DELAY					3
#define MAX_FRAME_COUNT				500
#define GL_NO_OF_ELEMENTS_IN_SRC	1
#define EVAS_OBJECT_DATA_KEY_01		"EVAS_OBJ_KEY_01_GLD"
#define EVAS_OBJECT_DATA_KEY_02		"EVAS_OBJ_KEY_02_ECORE_ANIMATOR"
#define OPENGL_VERSION_1_FEATURE	"tizen.org/feature/opengles.version.1_1"
#define OPENGL_VERSION_2_FEATURE	"tizen.org/feature/opengles.version.2_0"
#define GL_RENDERING_ENGINE			"opengl"	

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

typedef struct _gl2_matrix_st
{
	GLfloat Mat[4][4];
} gl2_matrix_st;

typedef struct _gl2_renderer_st
{
	Evas_GL_API *pGLApi;
	GLuint glunProgram;
	GLuint glunVTXShader;
	GLuint glunFGMTShader;
	GLuint glunVBO;
	GLuint glunFBO;
	GLuint glunPositionLoc;
	GLuint glunColorLoc;
	GLuint glunMVPLoc;
	int nInitialized : 1;
} gl2_renderer_st;

typedef enum _gl2_states_e
{
	GL_STATE_NONE = 0,
	INIT_GL_SUCCESS,
	INIT_GL_FAILED,
	DEL_GL_SUCCESS,
	DEL_GL_FAILED,
	RESIZE_GL_SUCCESS,
	RESIZE_GL_FAILED,
	DRAW_GL_SUCCESS,
	DRAW_GL_FAILED,
	ANIMATION_START,
	ANIMATION_FAILED,
	ANIMATOR_DEL_SUCCESS,
	ANIMATOR_DEL_FAILED
} gl2_states_e;

gl2_states_e g_eOpenGl2State;
Evas_Object *g_pOpenGl2EOWin; 
gl2_matrix_st *g_pstOpenGl2ProjectionMat;
gl2_matrix_st *g_pstOpenGl2ModelViewMat;
gl2_matrix_st *g_pstOpenGl2MVPMat;
gl2_renderer_st *g_pstGld;

int g_nOpenGl2Delay;
int g_nOpenGl2FrameCount;
bool g_elm_init;

//Add helper function declarations here
/** print the error of sysinfo information */
void OpenGl2ElmShutdown(void);
void OpenGl2ScaleMatrix(gl2_matrix_st *pstResult, GLfloat SX, GLfloat SY, GLfloat SZ);
void OpenGl2FrustumMatrix(gl2_matrix_st *pstResult, float fLeft, float fRight, float fBottom, float fTop, float fNearZ, float fFarZ);
void OpenGl2LoadIdentity(gl2_matrix_st *pstResult);
void OpenGl2MulMatrix(gl2_matrix_st *pstResult, gl2_matrix_st *pstSrcA, gl2_matrix_st *pstSrcB);
void OpenGl2RotationMatrix(gl2_matrix_st *pstResult, GLfloat glfAngle, GLfloat X, GLfloat Y, GLfloat Z);
int OpenGl2InitShader(gl2_renderer_st *pstRenderder);
GLuint OpenGl2LoadShader(gl2_renderer_st *pstRenderder, GLenum eType, const char *pchShaderSrc);

/** @} */ //end of ctc-opengl

#endif  //_CTS_OPENGL_COMMON_H_
