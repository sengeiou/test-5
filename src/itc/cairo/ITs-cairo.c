//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-cairo-common.h"

Evas_Object *g_pWin;
Evas_GL *g_pEvas_gl;
Evas_GL_Config *g_pEvas_gl_config;
Evas_GL_Surface *g_pEvas_gl_surface;
Evas_GL_Context *g_pEvas_gl_context;
cairo_device_t *g_pCairo_device = NULL;
cairo_surface_t *g_pSurface = NULL;

int g_nEvas_state = 1;

//& set: Cairo

/**
 * @function 		ITs_cairo_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_cairo_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	g_nEvas_state = 1;

	elm_init(0,NULL);
	elm_config_accel_preference_set("opengl");
	
	g_pWin = elm_win_add(NULL, "test cairo", ELM_WIN_BASIC);
	if(g_pWin == NULL)
	{
		g_nEvas_state = 0;
		FPRINTF( " [Line : %d] [%s] elm_win_add failed, error returned = Handle is NULL \\n",__LINE__, API_NAMESPACE);
	}			
	else
	{
		elm_win_title_set(g_pWin, "test cairo");
		evas_object_show(g_pWin);
		
		g_pEvas_gl = evas_gl_new(evas_object_evas_get(g_pWin));
		if(g_pEvas_gl == NULL) 
		{
			g_nEvas_state = 0;
			FPRINTF( " [Line : %d] [%s] evas_gl_new failed, error returned = Handle is NULL \\n",__LINE__, API_NAMESPACE);
		}		
		
		g_pEvas_gl_config = evas_gl_config_new();
		if(g_pEvas_gl_config == NULL)
		{
			g_nEvas_state = 0;
			FPRINTF( " [Line : %d] [%s] evas_gl_config_new failed, error returned = Handle is NULL \\n",__LINE__, API_NAMESPACE);
		}			
		else 
		{
			g_pEvas_gl_config->color_format = EVAS_GL_RGBA_8888;
		}			

		if(g_nEvas_state)
		{
			g_pEvas_gl_surface = evas_gl_surface_create(g_pEvas_gl, g_pEvas_gl_config, WIDTH, HEIGHT);
			if(g_pEvas_gl_surface == NULL) 
			{
				g_nEvas_state = 0;
				FPRINTF( " [Line : %d] [%s] evas_gl_surface_create failed, error returned = Handle is NULL \\n",__LINE__, API_NAMESPACE);
			}			
			
			g_pEvas_gl_context = evas_gl_context_create(g_pEvas_gl, NULL);
			if(g_pEvas_gl_context == NULL)
			{
				g_nEvas_state = 0;
				FPRINTF( " [Line : %d] [%s] evas_gl_context_create failed, error returned = Handle is NULL \\n",__LINE__, API_NAMESPACE);
			}			
			setenv("CAIRO_GL_COMPOSITOR", "msaa", 1);
		}
	}	
	return;
}


/**
 * @function 		ITs_cairo_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_cairo_cleanup(void)
{

	if(g_pSurface != NULL)
	{
		cairo_surface_destroy (g_pSurface);
		g_pSurface = NULL;
	}
	
	if(g_pCairo_device != NULL )
	{	
		cairo_device_destroy(g_pCairo_device);
		g_pCairo_device = NULL;
	}

	if(g_pEvas_gl_surface != NULL )
	{	
		evas_gl_make_current(g_pEvas_gl, NULL, NULL);
		evas_gl_surface_destroy(g_pEvas_gl, g_pEvas_gl_surface);
		g_pEvas_gl_surface = NULL;
	}
	
	if(g_pEvas_gl_context != NULL )
	{	
		evas_gl_make_current(g_pEvas_gl, NULL, NULL);
		evas_gl_context_destroy(g_pEvas_gl, g_pEvas_gl_context);
		g_pEvas_gl_context = NULL;
	}
	
	if(g_pEvas_gl_config != NULL )
	{	
		evas_gl_config_free(g_pEvas_gl_config);
		g_pEvas_gl_config = NULL;
	}
	
	if(g_pEvas_gl != NULL )
	{	
		evas_gl_free(g_pEvas_gl);
		g_pEvas_gl = NULL;
	}

	if(g_pWin != NULL )
	{	
		evas_object_del(g_pWin);
		g_pWin = NULL;
	}
	
	elm_shutdown();

	return;
}

//& purpose: Creates and returns a new cairo_device structure for interface to underlying rendering system. 
//& type: auto 
/**
 * @testcase 				ITc_cairo_evas_gl_device_create_p
 * @since_tizen 			2.3.1
 * @author            		SRID(ajay.kr1)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Creates and returns a new cairo_device structure.
 * @scenario				Creates and returns a new cairo_device.
 * @apicovered				cairo_evas_gl_device_create					
 * @passcase				When cairo_evas_gl_device_create are execute successful and return 0
 * @failcase				If target api cairo_evas_gl_device_create are return negative number.
 * @precondition			NA
 * @postcondition			NA
 * 
 */
int ITc_cairo_evas_gl_device_create_p(void)
{
	bool bIsSupported = false;
	START_TEST;
	int nRetVal = -1;
	
	g_pCairo_device = (cairo_device_t *)cairo_evas_gl_device_create (g_pEvas_gl, g_pEvas_gl_context);
	nRetVal = cairo_device_status(g_pCairo_device);
	PRINT_RESULT_CAIRO(nRetVal, "cairo_evas_gl_device_create", bIsSupported);	
    return 0;
}


//& purpose: Creates and returns a new cairo_surface structure for representing Evas_GL_Surface object that cairo can render to.
//& type: auto 
/**
 * @testcase 				ITc_cairo_gl_surface_create_for_evas_gl_p
 * @since_tizen 			2.3.1
 * @author            		SRID(ajay.kr1)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Creates and returns a new cairo_surface structure.
 * @scenario				Creates and returns a new cairo_surface.
 * @apicovered				cairo_gl_surface_create_for_evas_gl					
 * @passcase				When cairo_gl_surface_create_for_evas_gl are execute successful and return 0
 * @failcase				If target api cairo_gl_surface_create_for_evas_gl are return negative number.
 * @precondition			cairo_evas_gl_device_create
 * @postcondition			NA
 * 
 */
int ITc_cairo_gl_surface_create_for_evas_gl_p(void)
{
	bool bIsSupported = false;
	START_TEST;
	int nRetVal = -1;
	
	g_pCairo_device = (cairo_device_t *)cairo_evas_gl_device_create (g_pEvas_gl, g_pEvas_gl_context);
	nRetVal = cairo_device_status(g_pCairo_device);
	PRINT_RESULT_CAIRO(nRetVal, "cairo_evas_gl_device_create", bIsSupported);
	
	g_pSurface = (cairo_surface_t *)cairo_gl_surface_create_for_evas_gl(g_pCairo_device, g_pEvas_gl_surface, g_pEvas_gl_config, WIDTH, HEIGHT);
	nRetVal = cairo_surface_status(g_pSurface);
	PRINT_RESULT(CAIRO_STATUS_SUCCESS, nRetVal, "cairo_gl_surface_create_for_evas_gl", CairoGetError(nRetVal));
    return 0;
}

//& purpose: Returns the underlying EvasGL object used to create cairo device object.
//& type: auto 
/**
 * @testcase 				ITc_cairo_evas_gl_device_get_gl_p
 * @since_tizen 			2.3.1
 * @author            		SRID(ajay.kr1)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns the underlying EvasGL object used to create cairo device object.
 * @scenario				Get underlying EvasGL object.
 * @apicovered				cairo_evas_gl_device_get_gl					
 * @passcase				When cairo_evas_gl_device_get_gl executes successfully.
 * @failcase				If target api cairo_evas_gl_device_get_gl returns NULL.
 * @precondition			cairo_evas_gl_device_create
 * @postcondition			NA
 * 
 */
int ITc_cairo_evas_gl_device_get_gl_p(void)
{
	bool bIsSupported = false;
	START_TEST;
	int nRetVal = -1;
	Evas_GL *pRetEvasGl = NULL;

	g_pCairo_device = (cairo_device_t *)cairo_evas_gl_device_create (g_pEvas_gl, g_pEvas_gl_context);
	nRetVal = cairo_device_status(g_pCairo_device);
	PRINT_RESULT_CAIRO(nRetVal, "cairo_evas_gl_device_create", bIsSupported);

	pRetEvasGl = cairo_evas_gl_device_get_gl(g_pCairo_device);
	CHECK_HANDLE(pRetEvasGl, "cairo_evas_gl_device_get_gl");
    return 0;
}

//& purpose: Returns the underlying Evasl_GL_Context object used to create cairo device object.
//& type: auto 
/**
 * @testcase 				ITc_cairo_evas_gl_device_get_context_p
 * @since_tizen 			2.3.1
 * @author            		SRID(ajay.kr1)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns the underlying Evasl_GL_Context object used to create cairo device object.
 * @scenario				Get underlying Evasl_GL_Context object.
 * @apicovered				cairo_evas_gl_device_get_context					
 * @passcase				When cairo_evas_gl_device_get_context executes successfully.
 * @failcase				If target api cairo_evas_gl_device_get_context returns NULL.
 * @precondition			cairo_evas_gl_device_create
 * @postcondition			NA
 * 
 */
int ITc_cairo_evas_gl_device_get_context_p(void)
{
	bool bIsSupported = false;
	START_TEST;
	int nRetVal = -1;
	Evas_GL_Context *pRetEvasGlContext;

	g_pCairo_device = (cairo_device_t *)cairo_evas_gl_device_create (g_pEvas_gl, g_pEvas_gl_context);
	nRetVal = cairo_device_status(g_pCairo_device);
	PRINT_RESULT_CAIRO(nRetVal, "cairo_evas_gl_device_create", bIsSupported);

	pRetEvasGlContext = cairo_evas_gl_device_get_context(g_pCairo_device);
	CHECK_HANDLE(pRetEvasGlContext, "cairo_evas_gl_device_get_context");	
    return 0;
}

//& purpose: Create a cairo GL surface using the device as the underlying rendering system
//& type: auto 
/**
 * @testcase 				ITc_cairo_gl_surface_create_p
 * @since_tizen 			2.3.1
 * @author            		SRID(ajay.kr1)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Create a cairo GL surface using the device as the underlying rendering system
 * @scenario				Create a cairo GL surface
 * @apicovered				cairo_evas_gl_device_create, cairo_gl_surface_create					
 * @passcase				When cairo_gl_surface_create are execute successful and return 0
 * @failcase				If target api cairo_gl_surface_create returns negative number.
 * @precondition			cairo_evas_gl_device_create
 * @postcondition			NA
 * 
 */
int ITc_cairo_gl_surface_create_p(void)
{
	bool bIsSupported = false;
	START_TEST;
	int nRetVal = -1;
	
	g_pCairo_device = (cairo_device_t *)cairo_evas_gl_device_create (g_pEvas_gl, g_pEvas_gl_context);
	nRetVal = cairo_device_status(g_pCairo_device);
	PRINT_RESULT_CAIRO(nRetVal, "cairo_evas_gl_device_create", bIsSupported);
	
	g_pSurface = (cairo_surface_t *)cairo_gl_surface_create(g_pCairo_device, CAIRO_CONTENT_COLOR_ALPHA, WIDTH, HEIGHT);
	nRetVal = cairo_surface_status(g_pSurface);
	PRINT_RESULT(CAIRO_STATUS_SUCCESS, nRetVal, "cairo_gl_surface_create", CairoGetError(nRetVal));
	
    return 0;
}

//& purpose: Create a cairo GL surface using the texture as the render target, and the device as the underlying rendering system
//& type: auto 
/**
 * @testcase 				ITc_cairo_gl_surface_create_for_texture_p
 * @since_tizen 			2.3.1
 * @author            		SRID(ajay.kr1)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Create a cairo GL surface using the texture as the render target, and the device as the underlying rendering system
 * @scenario				Create a cairo GL surface using the texture
 * @apicovered				cairo_evas_gl_device_create, cairo_gl_surface_create_for_texture					
 * @passcase				When cairo_gl_surface_create_for_texture are execute successful and return 0
 * @failcase				If target api cairo_gl_surface_create_for_texture returns negative number.
 * @precondition			cairo_evas_gl_device_create
 * @postcondition			NA
 * 
 */
int ITc_cairo_gl_surface_create_for_texture_p(void)
{
	bool bIsSupported = false;
	START_TEST;
	int nRetVal = -1;
	
	g_pCairo_device = (cairo_device_t *)cairo_evas_gl_device_create (g_pEvas_gl, g_pEvas_gl_context);
	nRetVal = cairo_device_status(g_pCairo_device);
	PRINT_RESULT_CAIRO(nRetVal, "cairo_evas_gl_device_create", bIsSupported);

	g_pSurface = (cairo_surface_t *)cairo_gl_surface_create_for_texture(g_pCairo_device, CAIRO_CONTENT_COLOR_ALPHA, 0, WIDTH, HEIGHT);
	nRetVal = cairo_surface_status(g_pSurface);
	PRINT_RESULT(CAIRO_STATUS_SUCCESS, nRetVal, "cairo_gl_surface_create_for_texture", CairoGetError(nRetVal));

    return 0;
}

//& purpose: Get width of given cairo surface object
//& type: auto 
/**
 * @testcase 				ITc_cairo_gl_surface_get_width_p
 * @since_tizen 			2.3.1
 * @author            		SRID(ajay.kr1)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Get width of given cairo surface object
 * @scenario				Get width of given cairo surface object
 * @apicovered				cairo_evas_gl_device_create, cairo_gl_surface_create,  cairo_gl_surface_get_width					
 * @passcase				When cairo_gl_surface_get_width executes successfully and return the set width
 * @failcase				If target api cairo_gl_surface_get_width returns value different than the set width value
 * @precondition			cairo_evas_gl_device_create
 * @postcondition			NA
 * 
 */
int ITc_cairo_gl_surface_get_width_p(void)
{
	bool bIsSupported = false;
	START_TEST;
	int nRetVal = -1;
	
	g_pCairo_device = (cairo_device_t *)cairo_evas_gl_device_create(g_pEvas_gl, g_pEvas_gl_context);
	nRetVal = cairo_device_status(g_pCairo_device);
	PRINT_RESULT_CAIRO(nRetVal, "cairo_evas_gl_device_create", bIsSupported);

	g_pSurface = (cairo_surface_t *)cairo_gl_surface_create(g_pCairo_device, CAIRO_CONTENT_COLOR_ALPHA, WIDTH, HEIGHT);
	nRetVal = cairo_surface_status(g_pSurface);
	PRINT_RESULT(CAIRO_STATUS_SUCCESS, nRetVal, "cairo_gl_surface_create", CairoGetError(nRetVal));
	
	nRetVal = cairo_gl_surface_get_width(g_pSurface);
	if( nRetVal != WIDTH)
	{
		FPRINTF( " [Line : %d] [%s] cairo_gl_surface_get_width failed, width returned = %d \\n",__LINE__, API_NAMESPACE, nRetVal);
		return 1;
	}
	
    return 0;
}

//& purpose: Get height of given cairo surface object
//& type: auto 
/**
 * @testcase 				ITc_cairo_gl_surface_get_height_p
 * @since_tizen 			2.3.1
 * @author            		SRID(ajay.kr1)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Get height of given cairo surface object
 * @scenario				Get height of given cairo surface object
 * @apicovered				cairo_evas_gl_device_create, cairo_gl_surface_create,  cairo_gl_surface_get_height					
 * @passcase				When cairo_gl_surface_get_height executes successfully and return the set height
 * @failcase				If target api cairo_gl_surface_get_height returns value different than the set height value
 * @precondition			cairo_evas_gl_device_create
 * @postcondition			NA
 * 
 */
int ITc_cairo_gl_surface_get_height_p(void)
{
	bool bIsSupported = false;
	START_TEST;
	int nRetVal = -1;
	
	g_pCairo_device = (cairo_device_t *)cairo_evas_gl_device_create(g_pEvas_gl, g_pEvas_gl_context);
	nRetVal = cairo_device_status(g_pCairo_device);
	PRINT_RESULT_CAIRO(nRetVal, "cairo_evas_gl_device_create", bIsSupported);

	g_pSurface = (cairo_surface_t *)cairo_gl_surface_create(g_pCairo_device, CAIRO_CONTENT_COLOR_ALPHA, WIDTH, HEIGHT);
	nRetVal = cairo_surface_status(g_pSurface);
	PRINT_RESULT(CAIRO_STATUS_SUCCESS, nRetVal, "cairo_gl_surface_create", CairoGetError(nRetVal));
	
	nRetVal = cairo_gl_surface_get_height(g_pSurface);
	if( nRetVal != HEIGHT)
	{
		FPRINTF( " [Line : %d] [%s] cairo_gl_surface_get_height failed, height returned = %d \\n",__LINE__, API_NAMESPACE, nRetVal);
		return 1;
	}
	
    return 0;
}

//& purpose: Cairo can be used in multithreaded environment
//& type: auto 
/**
 * @testcase 				ITc_cairo_gl_device_set_thread_aware_p
 * @since_tizen 			2.3.1
 * @author            		SRID(ajay.kr1)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Cairo can be used in multithreaded environment
 * @scenario				Cairo used for multithreaded environment
 * @apicovered				cairo_evas_gl_device_create, cairo_gl_device_set_thread_aware					
 * @passcase				When cairo_gl_device_set_thread_aware are execute successful and return 0
 * @failcase				If target api cairo_gl_device_set_thread_aware returns negative number.
 * @precondition			cairo_evas_gl_device_create
 * @postcondition			NA
 * 
 */
int ITc_cairo_gl_device_set_thread_aware_p(void)
{
	bool bIsSupported = false;
	START_TEST;
	int nRetVal = -1;
	
	g_pCairo_device = (cairo_device_t *)cairo_evas_gl_device_create (g_pEvas_gl, g_pEvas_gl_context);
	nRetVal = cairo_device_status(g_pCairo_device);
	PRINT_RESULT_CAIRO(nRetVal, "cairo_evas_gl_device_create", bIsSupported);
	
	cairo_gl_device_set_thread_aware(g_pCairo_device, 0);
	nRetVal = cairo_device_status(g_pCairo_device);
	PRINT_RESULT(CAIRO_STATUS_SUCCESS, nRetVal, "cairo_gl_device_set_thread_aware", CairoGetError(nRetVal));
	
    return 0;
}
