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
#include "CTs-opengl-common.h"

/** @addtogroup ctc-opengl
* @ingroup		ctc
* @{
*/

//& set: Opengl

/**
* @function 		CTs_opengl_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_opengl_startup(void)
{
	struct stat stBuff;   
	g_elm_init = false;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_System_Libstorage_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function 		CTs_opengl_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_opengl_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_System_Libstorage_p\\n", __LINE__, API_NAMESPACE);
#endif
	if (g_elm_init)
	{
		OpenGl2ElmShutdown();
		elm_shutdown();
	}

	return;
}

/**
* @function			Opengl2_init_gl_cb
* @description		Initializes openGL
* @parameter		Evas_Object *pEvasObj
* @return			NA
*/
static void Opengl2_init_gl_cb(Evas_Object *pEvasObj)
{
	g_eOpenGl2State = GL_STATE_NONE;
	const char *pchAttribPositionLoc = "vPosition";
	const char *pchAttribColorLoc = "color";
	const char *pchUniformModelView = "Modelview";

	gl2_renderer_st *pstGld = evas_object_data_get(pEvasObj, EVAS_OBJECT_DATA_KEY_01);
	if ( pstGld == NULL )
	{
		FPRINTF("[Line : %d][%s] evas_object_data_get is failed to return an attached data pointer by its given string key.\\n", __LINE__, API_NAMESPACE);
		g_eOpenGl2State = INIT_GL_FAILED;
		return;
	}
	
	Evas_GL_API *pGL = pstGld->pGLApi;
	GLfloat arVertices[] = {

		// front
		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,

		// Right
		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, -0.5f,

		// back
		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		// Left
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,

		// Top
		-0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,

		// Bottom
		-0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f

	};

	GLfloat arColors[] = {

		// front
		0.0625f,0.57421875f,0.92578125f,1.0f,
		0.0625f,0.57421875f,0.92578125f,1.0f,
		0.0625f,0.57421875f,0.92578125f,1.0f,
		0.0625f,0.57421875f,0.92578125f,1.0f,
		0.0625f,0.57421875f,0.92578125f,1.0f,
		0.0625f,0.57421875f,0.92578125f,1.0f,

		// Right
		0.29296875f,0.66796875f,0.92578125f,1.0f,
		0.29296875f,0.66796875f,0.92578125f,1.0f,
		0.29296875f,0.66796875f,0.92578125f,1.0f,
		0.29296875f,0.66796875f,0.92578125f,1.0f,
		0.29296875f,0.66796875f,0.92578125f,1.0f,
		0.29296875f,0.66796875f,0.92578125f,1.0f,

		// back
		0.52734375f,0.76171875f,0.92578125f,1.0f,
		0.52734375f,0.76171875f,0.92578125f,1.0f,
		0.52734375f,0.76171875f,0.92578125f,1.0f,
		0.52734375f,0.76171875f,0.92578125f,1.0f,
		0.52734375f,0.76171875f,0.92578125f,1.0f,
		0.52734375f,0.76171875f,0.92578125f,1.0f,

		// fLeft
		0.0625f,0.57421875f,0.92578125f,1.0f,
		0.0625f,0.57421875f,0.92578125f,1.0f,
		0.0625f,0.57421875f,0.92578125f,1.0f,
		0.0625f,0.57421875f,0.92578125f,1.0f,
		0.0625f,0.57421875f,0.92578125f,1.0f,
		0.0625f,0.57421875f,0.92578125f,1.0f,

		// Top
		0.29296875f,0.66796875f,0.92578125f,1.0f,
		0.29296875f,0.66796875f,0.92578125f,1.0f,
		0.29296875f,0.66796875f,0.92578125f,1.0f,
		0.29296875f,0.66796875f,0.92578125f,1.0f,
		0.29296875f,0.66796875f,0.92578125f,1.0f,
		0.29296875f,0.66796875f,0.92578125f,1.0f,

		// Bottom
		0.52734375f,0.76171875f,0.92578125f,1.0f,
		0.52734375f,0.76171875f,0.92578125f,1.0f,
		0.52734375f,0.76171875f,0.92578125f,1.0f,
		0.52734375f,0.76171875f,0.92578125f,1.0f,
		0.52734375f,0.76171875f,0.92578125f,1.0f,
		0.52734375f,0.76171875f,0.92578125f,1.0f
	};

	if ( !OpenGl2InitShader(pstGld) )
	{
		FPRINTF("[Line : %d][%s] Error Initializing Shaders\\n", __LINE__, API_NAMESPACE);
		g_eOpenGl2State = INIT_GL_FAILED;
		return;
	}

	pGL->glEnable(GL_DEPTH_TEST);

	pGL->glGenBuffers(1, &pstGld->glunVBO);
	pGL->glBindBuffer(GL_ARRAY_BUFFER, pstGld->glunVBO);
	pGL->glBufferData(GL_ARRAY_BUFFER, 36*3*4, arVertices, GL_STATIC_DRAW);
	pstGld->glunPositionLoc = pGL->glGetAttribLocation(pstGld->glunProgram, pchAttribPositionLoc);

	FPRINTF("[Line : %d][%s] position loc: %d \\n", __LINE__, API_NAMESPACE, pstGld->glunPositionLoc);

	pGL->glGenBuffers(1, &pstGld->glunFBO);
	pGL->glBindBuffer(GL_ARRAY_BUFFER, pstGld->glunFBO);
	pGL->glBufferData(GL_ARRAY_BUFFER, 36*4*4, arColors, GL_STATIC_DRAW);
	pstGld->glunColorLoc = pGL->glGetAttribLocation(pstGld->glunProgram, pchAttribColorLoc);
	FPRINTF("[Line : %d][%s] glunColorLoc: %d \\n", __LINE__, API_NAMESPACE, pstGld->glunColorLoc);

	g_pstOpenGl2ProjectionMat = malloc( sizeof(gl2_matrix_st) );
	OpenGl2LoadIdentity( g_pstOpenGl2ProjectionMat );

	float fSurfaceWidth = 800.0f;
	float fSurfaceHeight = 600.0f;

	GLfloat Aspect = (float)fSurfaceWidth/(float)fSurfaceHeight;
	GLfloat Near = -2.0f;
	GLfloat Far  = 200.0f;
	GLfloat YFOV  = 75.0f;
	GLfloat Height = tanf( YFOV / 360.0f * M_PI ) * Near;
	GLfloat Width = Height * Aspect;

	OpenGl2FrustumMatrix( g_pstOpenGl2ProjectionMat, -Width, Width, -Height, Height, Near, Far );

	OpenGl2ScaleMatrix( g_pstOpenGl2ProjectionMat, 1.0f, (float)fSurfaceHeight/(float)fSurfaceWidth, 1.0f );

	g_pstOpenGl2ModelViewMat = malloc( sizeof(gl2_matrix_st) );
	OpenGl2LoadIdentity( g_pstOpenGl2ModelViewMat );
	g_pstOpenGl2MVPMat = malloc( sizeof(gl2_matrix_st) );
	pstGld->glunMVPLoc = pGL->glGetUniformLocation(pstGld->glunProgram, pchUniformModelView);

	g_eOpenGl2State = INIT_GL_SUCCESS;
}

/**
* @function		Opengl2_del_gl_cb
* @description	Get called when glview is deleted
* @parameter	Evas_Object *pEvasObj
* @return		NA
*/
static void Opengl2_del_gl_cb(Evas_Object *pEvasObj)
{
	gl2_renderer_st *pstGld = evas_object_data_get(pEvasObj, EVAS_OBJECT_DATA_KEY_01);
	if ( !pstGld )
	{
		FPRINTF("[Line : %d][%s] Unable to get gl2_renderer_st.\\n", __LINE__, API_NAMESPACE);
		g_eOpenGl2State = DEL_GL_FAILED;
		return;
	}
	
	Evas_GL_API *pGL = pstGld->pGLApi;
	pGL->glDeleteShader(pstGld->glunVTXShader);
	pGL->glDeleteShader(pstGld->glunFGMTShader);
	pGL->glDeleteProgram(pstGld->glunProgram);
	pGL->glDeleteBuffers(1, &pstGld->glunVBO);

	// Delete an attached data pointer from an object.
	evas_object_data_del((Evas_Object*) pEvasObj, EVAS_OBJECT_DATA_KEY_01);
	// Delete an attached data pointer from an object.
	evas_object_data_del((Evas_Object*) pEvasObj, EVAS_OBJECT_DATA_KEY_02);

	FREE_MEMORY(pstGld);
	FREE_MEMORY(g_pstOpenGl2ProjectionMat);
	FREE_MEMORY(g_pstOpenGl2ModelViewMat);
	FREE_MEMORY(g_pstOpenGl2MVPMat);

	g_pOpenGl2EOWin = NULL;
	g_eOpenGl2State = DEL_GL_SUCCESS;
}

/**
* @function		Opengl2_resize_gl_cb
* @description	Get called every time object is resized
* @parameter	Evas_Object *pEvasObj
* @return		NA
*/
static void Opengl2_resize_gl_cb(Evas_Object *pEvasObj)
{
	int nW = -1, nH = -1;
	gl2_renderer_st *pstGld = evas_object_data_get(pEvasObj, EVAS_OBJECT_DATA_KEY_01);
	if ( pstGld == NULL )
	{
		FPRINTF("[Line : %d][%s] evas_object_data_get is failed to return an attached data pointer by its given string key.\\n", __LINE__, API_NAMESPACE);
		g_eOpenGl2State = DEL_GL_FAILED;
		return;
	}
	
	Evas_GL_API *pGL = pstGld->pGLApi;
	if ( pGL == NULL )
	{
		FPRINTF("[Line : %d][%s] Evas_GL_API is found invalid\\n", __LINE__, API_NAMESPACE);
		g_eOpenGl2State = DEL_GL_FAILED;
		return;
	}
	
	elm_glview_size_get(pEvasObj, &nW, &nH);
	pGL->glViewport(0, 0, nW, nH);
	g_eOpenGl2State = DEL_GL_SUCCESS;
}

/**
* @function		Opengl2_draw_gl_cb
* @description	Draw callback is where all the main GL rendering happens
* @parameter	Evas_Object *pEvasObj
* @return		NA
*/
static void Opengl2_draw_gl_cb(Evas_Object *pEvasObj)
{		
	Evas_GL_API *pGL = elm_glview_gl_api_get(pEvasObj);
	gl2_renderer_st *pstGld = evas_object_data_get(pEvasObj, EVAS_OBJECT_DATA_KEY_01);
	if ( !pstGld )
	{
		FPRINTF("[Line : %d][%s] evas_object_data_get is failed to return an attached data pointer by its given string key.\\n", __LINE__, API_NAMESPACE);
		g_eOpenGl2State = DRAW_GL_FAILED;
		return;
	}
	
	int nW = -1, nH = -1;
	elm_glview_size_get(pEvasObj, &nW, &nH);
	if ( nW < 0 || nH < 0 )
	{
		FPRINTF("[Line : %d][%s] elm_glview_size_get is failed for invalid size returned\\n", __LINE__, API_NAMESPACE);
		g_eOpenGl2State = DRAW_GL_FAILED;
		return;
	}
	
	pGL->glViewport(0, 0, nW, nH);
	pGL->glClearColor(0.0f,0.0f,0.0f,1);
	pGL->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pGL->glUseProgram(pstGld->glunProgram);

	OpenGl2RotationMatrix( g_pstOpenGl2ModelViewMat, 1.0f, -1.0f, -1.0f, 0.0f);
	OpenGl2MulMatrix( g_pstOpenGl2MVPMat, g_pstOpenGl2ModelViewMat, g_pstOpenGl2ProjectionMat);

	pGL->glUniformMatrix4fv(pstGld->glunMVPLoc, 1, GL_FALSE, &g_pstOpenGl2MVPMat->Mat[0][0]);
	pGL->glEnableVertexAttribArray(pstGld->glunPositionLoc);
	pGL->glBindBuffer(GL_ARRAY_BUFFER, pstGld->glunVBO);
	pGL->glVertexAttribPointer(pstGld->glunPositionLoc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);
	pGL->glEnableVertexAttribArray(pstGld->glunColorLoc);
	pGL->glBindBuffer(GL_ARRAY_BUFFER, pstGld->glunFBO);
	pGL->glVertexAttribPointer(pstGld->glunColorLoc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);
	pGL->glDrawArrays(GL_TRIANGLES, 0, 3 * 12);
	pGL->glFinish();
	g_nOpenGl2FrameCount++;
	g_eOpenGl2State = DRAW_GL_SUCCESS;

	if ( g_nOpenGl2FrameCount > MAX_FRAME_COUNT )
	{
		elm_exit();
	}
}

/**
* @function		Opengl2_animation_cb
* @description	To notify that glview has changed so it can render
* @parameter	void *pData
* @return		Eina_Bool (EINA_TRUE)
*/
static Eina_Bool Opengl2_animation_cb(void *pData)
{
	elm_glview_changed_set(pData);
	return EINA_TRUE;
}

/**
* @function		Opengl2_win_del_cb
* @description	Adds or registers a callback function to the smart event specified by event on the smart object obj. 
* @parameter	void *pData, Evas_Object *pEvasObj, void *pEvent
*/
static void Opengl2_win_del_cb(void *pData, Evas_Object *pEvasObj, void *pEvent)
{
	elm_exit();
}

/**
* @function		Opengl2_animator_del_cb
* @description	Deletes the animator
* @parameter	void *pData, Evas *pEvas, Evas_Object *pEvasObj, void *pEventInfo
* @return		NA
*/
static void Opengl2_animator_del_cb(void *pData, Evas *pEvas, Evas_Object *pEvasObj, void *pEventInfo)
{
	Ecore_Animator *pAnim = evas_object_data_get(pEvasObj, EVAS_OBJECT_DATA_KEY_02);
	pData = ecore_animator_del(pAnim);
	if ( pData == NULL )
	{
		FPRINTF("[Line : %d][%s] ecore_animator_del failed to delete animator\\n", __LINE__, API_NAMESPACE);
	}
}

/** @addtogroup	ctc-opengl-testcases
* @brief 		Integration testcases for module opengl
* @ingroup		ctc-opengl
* @{
*/

//& purpose: Rendering a 3D model cube using opengl 2.0
//& type: auto
/**
* @testcase			CTc_Opengl2_GlDrawCube_p
* @since_tizen		2.3
* @author            SRID(tewari.r)
* @reviewer         SRID(gupta.sanjay)
* @type 			auto
* @description		Rendering a 3D model cube using opengl 2.0
* @scenario			Initialize Elementary\n
* 					Set Elementary's rendering engine for use\n
* 					Set new policy value\n
* 					Adds a window object with standard setup\n
* 					Set the window's autodel state\n
* 					Add a new box to the parent\n
* 					Sets the hints for an object's weight\n
* 					Add subobj as a resize object of window obj\n
* 					Makes the given Evas object visible\n
* 					Add a new glview to the parent\n
* 					Get the gl API struct for gl rendering\n
* 					Sets the hints for an object's alignment\n
* 					Sets the hints for an object's weight\n
* 					Set the mode of the GLView\n
* 					Set the resize policy for the glview object\n
* 					Set the render policy for the glview object\n
* 					Set the init function that runs once in the main loop\n
* 					Set the delete function that runs once in the main loop\n
* 					Set the resize function that Get called when resize happens\n
* 					Set the render function that runs in the main loop\n
* 					Add an object at the end of the pack list\n
* 					Makes the given Evas object visible\n
* 					Set/unset focus to a given Elementary object\n
* 					Add an animator to call func at every animation tick during main loop execution\n
* 					Set an attached data pointers to an object with a given string key\n
* 					Add (register) a callback function to a given Evas object event\n
* 					Add a back button\n
* 					Run Elementary's main loop\n
* 					Hide the evas object\n
* 					Shut down Elementary\n
* 					Exit elementary
* @apicovered		NA
* @passcase			If a 3D cube is rendered on the screen.
* @failcase			If shaders do not compile, do not attach after compile, display buffer fails
* @precondition		Target must support opengl 2.0
* @postcondition	Autmatically elementary objects should be removed after rendering a time interval
*/
int CTc_Opengl2_GlDrawCube_p(void)
{
	START_TEST;

	bool bIsFeatureSupported;
	IS_FEATURE_SUPPORTED(OPENGL_VERSION_2_FEATURE, bIsFeatureSupported, API_NAMESPACE);
	if ( !bIsFeatureSupported )
	{
		FPRINTF("[Line : %d][%s] Feature (%s) is not supported.\\n", __LINE__, API_NAMESPACE, OPENGL_VERSION_2_FEATURE);
		return 0;
	}

	Evas_Object  *pEOBX = NULL,*pEOGL = NULL;
	int nRet = 0;
	const char* pchNameOfWindow = "glview simple";
	const char* pchTitleOfWindow = "GLView Simple";
	Eina_Bool bIsSuccess = EINA_FALSE;
	Ecore_Animator *pEcoreAnim = NULL;

	g_pstOpenGl2ProjectionMat = NULL;
	g_pstOpenGl2ModelViewMat = NULL;
	g_pstOpenGl2MVPMat = NULL;
	g_pOpenGl2EOWin = NULL;
	g_nOpenGl2FrameCount = 0;

	nRet = elm_init(0, NULL);
	if ( nRet < 0 )
	{
		FPRINTF("[Line : %d][%s] elm_init failed and returned invalid new counter's value: %d\\n", __LINE__, API_NAMESPACE, nRet);
		return 1;
	}
	g_elm_init = true;
	g_pstGld = NULL;
	if ( !(g_pstGld = calloc(1, sizeof(gl2_renderer_st))) )
	{
		FPRINTF("[Line : %d][%s] Insufficient memory for allocation. (calloc failed)\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	elm_config_accel_preference_set(GL_RENDERING_ENGINE);
	bIsSuccess = elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
	if ( bIsSuccess == EINA_FALSE )
	{
		FPRINTF("[Line : %d][%s] elm_policy_set failed to set elementary policy.\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_pOpenGl2EOWin = elm_win_util_standard_add(pchNameOfWindow, pchTitleOfWindow);
	if ( g_pOpenGl2EOWin == NULL )
	{
		FPRINTF("[Line : %d][%s] elm_win_util_standard_add failed to add a window object with standard setup\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	elm_win_autodel_set(g_pOpenGl2EOWin, EINA_TRUE);

	evas_object_smart_callback_add(g_pOpenGl2EOWin, "delete,request", Opengl2_win_del_cb, NULL);

	pEOBX = elm_box_add(g_pOpenGl2EOWin);
	if ( pEOBX == NULL )
	{
		FPRINTF("[Line : %d][%s] elm_box_add failed to add box\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	evas_object_size_hint_weight_set(pEOBX, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(g_pOpenGl2EOWin, pEOBX);
	evas_object_show(pEOBX);

	pEOGL = elm_glview_add(g_pOpenGl2EOWin);
	if ( pEOGL == NULL )
	{
		FPRINTF("[Line : %d][%s] elm_glview_add failed to add glview\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	g_pstGld->pGLApi = elm_glview_gl_api_get(pEOGL);
	if ( g_pstGld->pGLApi == NULL )
	{
		FPRINTF("[Line : %d][%s] elm_glview_gl_api_get failed to get gl api\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	evas_object_size_hint_align_set(pEOGL, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(pEOGL, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_glview_mode_set(pEOGL, ELM_GLVIEW_ALPHA | ELM_GLVIEW_DEPTH);

	elm_glview_resize_policy_set(pEOGL, ELM_GLVIEW_RESIZE_POLICY_RECREATE);
	elm_glview_render_policy_set(pEOGL, ELM_GLVIEW_RENDER_POLICY_ON_DEMAND);

	elm_glview_init_func_set(pEOGL, Opengl2_init_gl_cb);

	elm_glview_del_func_set(pEOGL, Opengl2_del_gl_cb);

	elm_glview_resize_func_set(pEOGL, Opengl2_resize_gl_cb);

	elm_glview_render_func_set(pEOGL, Opengl2_draw_gl_cb);

	elm_box_pack_end(pEOBX, pEOGL);

	evas_object_show(pEOGL);

	elm_object_focus_set(pEOGL, EINA_TRUE);
	pEcoreAnim = ecore_animator_add(Opengl2_animation_cb, pEOGL);
	if ( pEcoreAnim == NULL )
	{
		FPRINTF("[Line : %d][%s] ecore_animator_add failed to add animator\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	evas_object_data_set(pEOGL, EVAS_OBJECT_DATA_KEY_02, pEcoreAnim);
	evas_object_data_set(pEOGL, EVAS_OBJECT_DATA_KEY_01, g_pstGld);
	evas_object_event_callback_add(pEOGL, EVAS_CALLBACK_DEL, Opengl2_animator_del_cb, pEOGL);
	g_nOpenGl2Delay = 0;
	
	do
	{
		if ( g_eOpenGl2State == INIT_GL_FAILED ||
			g_eOpenGl2State == DRAW_GL_FAILED ||
			g_eOpenGl2State == RESIZE_GL_FAILED ||
			g_eOpenGl2State == DEL_GL_FAILED ||
			g_eOpenGl2State == ANIMATOR_DEL_FAILED )
		{
			return 1;
		}
		
		sleep(1);
		g_nOpenGl2Delay++;
	} while ( g_nOpenGl2Delay < TIME_DELAY );

	evas_object_resize(g_pOpenGl2EOWin, OPENGL2_WIN_WIDTH, OPENGL2_WIN_HEIGHT);
	evas_object_show(g_pOpenGl2EOWin);
	elm_run();
	return 0;
}

//& purpose: Check device's open GL versions 1_1 and 2_0 are supported or not
//& type: auto
/**
* @testcase			CTc_Opengl2_OpenGlVersion_p
* @since_tizen		2.3
* @author            SRID(tewari.r)
* @reviewer         SRID(gupta.sanjay)
* @type 			auto
* @description		Check device's open GL versions 1_1 and 2_0 are supported or not
* @scenario			Get the Device's two OpenGL version\n
*					Check  version's are  supported
* @apicovered		system_info_get_platform_bool
* @passcase			Covered api's should return zero success value and supported boolean value
* @failcase			Covered API returns negative error value and wrong supported boolean value
* @precondition		NA
* @postcondition	NA
*/
int CTc_Opengl2_OpenGlVersion_p(void)
{
	START_TEST;
	
	int nRet = -1;
	bool bOpenGLVersion1 = false, bOpenGLVersion2 = false;
	nRet =  system_info_get_platform_bool(OPENGL_VERSION_1_FEATURE,&bOpenGLVersion1);
	if ( nRet != SYSTEM_INFO_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool is failed, error returned = %s.\\n", __LINE__, API_NAMESPACE, TCTSystemInfoGetError(nRet));
		return 1;
	}
	if ( bOpenGLVersion1 != true )
	{
		FPRINTF("[Line : %d][%s] OpenGL version.1_1 is not Supported\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet =  system_info_get_platform_bool(OPENGL_VERSION_2_FEATURE,&bOpenGLVersion2);
	if ( nRet != SYSTEM_INFO_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool is failed, error returned = %s.\\n", __LINE__, API_NAMESPACE, TCTSystemInfoGetError(nRet));
		return 1;
	}
	if ( bOpenGLVersion2 != true )
	{
		FPRINTF("[Line : %d][%s] OpenGL version.2_0 is not Supported\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Check device's open GL Context version can add glview to parent for 1.1 and 2.0 both (default is 2.0)
//& type: autoevas_object_show
/**
* @testcase			CTc_Opengl2_OpenGlContextVersion_p
* @since_tizen		2.3
* @author            SRID(tewari.r)
* @reviewer         SRID(gupta.sanjay)
* @type 			auto
* @description		Check device's open GL Context version can add glview to parent for 1.1 and 2.0 both (default is 2.0)
* @scenario			Initialize Elementary\n
* 					Set Elementary rendering engine for use\n
* 					Set new policy value\n
* 					Adds a window object with standard setup\n
* 					Set the window's autodel state\n
* 					Add a new box to the parent\n
* 					Sets the hints for an object's weight\n
* 					Add subobj as a resize object of window obj\n
* 					Makes the given Evas object visible\n
* 					Add a new glview to the parent\n
* 					Hide the evas object\n
* 					Shut down Elementary\n
* 					Exit elementary
* @apicovered		NA
* @passcase			Covered api's should return zero success value and supported boolean value
* @failcase			Covered API returns negative error value and wrong supported boolean value
* @precondition		NA
* @postcondition	NA
*/
int CTc_Opengl2_OpenGlContextVersion_p(void)
{
	START_TEST;

	bool bIsFeatureSupported_v1, bIsFeatureSupported_v2;
	IS_FEATURE_SUPPORTED(OPENGL_VERSION_1_FEATURE, bIsFeatureSupported_v1, API_NAMESPACE);
	if ( !bIsFeatureSupported_v1 )
	{
		FPRINTF("[Line : %d][%s] Feature (%s) is not supported.\\n", __LINE__, API_NAMESPACE, OPENGL_VERSION_1_FEATURE);
	}
	IS_FEATURE_SUPPORTED(OPENGL_VERSION_2_FEATURE, bIsFeatureSupported_v2, API_NAMESPACE);
	if ( !bIsFeatureSupported_v2 )
	{
		FPRINTF("[Line : %d][%s] Feature (%s) is not supported.\\n", __LINE__, API_NAMESPACE, OPENGL_VERSION_2_FEATURE);
	}

	Evas_Object  *pEOBX = NULL, *pEOGL = NULL;
	int nRet = 0;
	const char* pchNameOfWindow = "glview simple";
	const char* pchTitleOfWindow = "GLView Simple";
	Eina_Bool bIsSuccess = EINA_FALSE;
	g_pOpenGl2EOWin = NULL;
	g_nOpenGl2FrameCount = 0;

	nRet = elm_init(0, NULL);
	if ( nRet < 0 )
	{
		FPRINTF("[Line : %d][%s] elm_init failed and returned invalid new counter's value: %d\\n", __LINE__, API_NAMESPACE, nRet);
		return 1;
	}
	g_elm_init = true;
	elm_config_accel_preference_set(GL_RENDERING_ENGINE);
	bIsSuccess = elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
	if ( bIsSuccess == EINA_FALSE )
	{
		FPRINTF("[Line : %d][%s] elm_policy_set failed to set elementary policy.\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	g_pOpenGl2EOWin = elm_win_util_standard_add(pchNameOfWindow, pchTitleOfWindow);
	if ( g_pOpenGl2EOWin == NULL )
	{
		FPRINTF("[Line : %d][%s] elm_win_util_standard_add failed to add a window object with standard setup\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	elm_win_autodel_set(g_pOpenGl2EOWin, EINA_TRUE);

	pEOBX = elm_box_add(g_pOpenGl2EOWin);
	if ( pEOBX == NULL )
	{
		FPRINTF("[Line : %d][%s] elm_box_add failed to add box\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	evas_object_size_hint_weight_set(pEOBX, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(g_pOpenGl2EOWin, pEOBX);
	evas_object_show(pEOBX);

	if ( bIsFeatureSupported_v1 )
	{
		pEOGL = elm_glview_version_add(g_pOpenGl2EOWin, EVAS_GL_GLES_1_X);
		if ( pEOGL == NULL )
		{
			FPRINTF("[Line : %d][%s] elm_glview_version_add for EVAS_GL_GLES_1_X is failed to add glview\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	if ( bIsFeatureSupported_v2 )
	{
		pEOGL = elm_glview_version_add(g_pOpenGl2EOWin, EVAS_GL_GLES_2_X);
		if ( pEOGL == NULL )
		{
			FPRINTF("[Line : %d][%s] elm_glview_version_add for EVAS_GL_GLES_2_X is failed to add glview\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	// Delete subobj as a resize object of window obj.
	elm_win_resize_object_del(g_pOpenGl2EOWin, pEOBX);

	return 0;
}

/** @} */ //end of ctc-opengl
/** @} */ //end of ctc-opengl-testcases
