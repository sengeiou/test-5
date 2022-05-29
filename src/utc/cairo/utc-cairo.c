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

#include <stdio.h>
#include "assert.h"
#include <cairo.h>
#include <cairo-evas-gl.h>
#include <Evas_GL.h>
#include <Elementary.h>

#include <system_info.h>

#define OPENGL_VERSION_1_FEATURE	"tizen.org/feature/opengles.version.1_1"
#define OPENGL_VERSION_2_FEATURE	"tizen.org/feature/opengles.version.2_0"

Evas_Object *win;
Evas_GL *evas_gl;
Evas_GL_Config *evas_gl_config;
Evas_GL_Surface *evas_gl_surface;
Evas_GL_Context *evas_gl_context;
cairo_device_t *cairo_device = NULL;
cairo_surface_t *surface = NULL;

int is_supported = 1;
int evas_state = 1;

/**
 * @function		utc_cairo_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_cairo_startup(void)
{
	int ret = -1;
	evas_state = 1;
	bool bOpenGLVersion1 = false, bOpenGLVersion2 = false;
	ret =  system_info_get_platform_bool(OPENGL_VERSION_1_FEATURE,&bOpenGLVersion1);
	if ( ret != SYSTEM_INFO_ERROR_NONE )
	{
		fprintf(stderr, "\\n[Line : %d] system_info_get_platform_bool is failed.\\n", __LINE__);
		is_supported = 0;
	}
	if (!bOpenGLVersion1 )
	{
		fprintf(stderr, "\\n[Line : %d] OpenGL version.1_1 is not Supported\\n", __LINE__);
		is_supported = 0;
	}
	ret =  system_info_get_platform_bool(OPENGL_VERSION_2_FEATURE,&bOpenGLVersion2);
	if ( ret != SYSTEM_INFO_ERROR_NONE )
	{
		fprintf(stderr, "\\n[Line : %d] system_info_get_platform_bool is failed.\\n", __LINE__);
		is_supported = 0;
	}
	if (!bOpenGLVersion2)
	{
		fprintf(stderr, "\\n[Line : %d] OpenGL version.2_0 is not Supported\\n", __LINE__);
		is_supported = 0;
	}

	if(is_supported)
	{
		elm_init(0,NULL);
		elm_config_accel_preference_set("opengl");
		win = elm_win_add(NULL, "utc cairo", ELM_WIN_BASIC);
		if(win == NULL)
		{
			fprintf(stderr, "\\n[Line : %d] error elm_win_add\\n", __LINE__);
			evas_state = 0;
		}
		else
		{
			elm_win_title_set(win, "utc cairo");
			evas_object_show(win);

			evas_gl = evas_gl_new(evas_object_evas_get(win));
			if(evas_gl == NULL)
			{
				fprintf(stderr, "\\n[Line : %d] error evas_gl_new\\n", __LINE__);
				evas_state = 0;
			}

			evas_gl_config = evas_gl_config_new();
			if(evas_gl_config == NULL)
			{
				fprintf(stderr, "\\n[Line : %d] error evas_gl_config_new\\n", __LINE__);
				evas_state = 0;
			}
			else
				evas_gl_config->color_format = EVAS_GL_RGBA_8888;

			if(evas_state)
			{
				int width = 30;
				int height = 30;
				evas_gl_surface = evas_gl_surface_create(evas_gl, evas_gl_config, width, height);
				if(evas_gl_surface == NULL)
					evas_state = 0;

				evas_gl_context = evas_gl_context_create(evas_gl, NULL);
				if(evas_gl_context == NULL)
					evas_state = 0;

				setenv("CAIRO_GL_COMPOSITOR", "msaa", 1);
			}
		}
	}
}

/**
 * @function		utc_cairo_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_cairo_cleanup(void)
{
	if(surface != NULL)
	{
		cairo_surface_destroy (surface);
		surface = NULL;
	}
	if(cairo_device != NULL)
	{
		cairo_device_destroy(cairo_device);
		cairo_device = NULL;
	}

	if(evas_gl_surface != NULL)
	{
		evas_gl_make_current (evas_gl, NULL, NULL);
		evas_gl_surface_destroy(evas_gl, evas_gl_surface);
		evas_gl_surface = NULL;
	}

	if(evas_gl_context != NULL)
	{
		evas_gl_make_current (evas_gl, NULL, NULL);
		evas_gl_context_destroy(evas_gl, evas_gl_context);
		evas_gl_context = NULL;
	}

	if(evas_gl_config != NULL)
	{
		evas_gl_config_free(evas_gl_config);
		evas_gl_config = NULL;
	}

	if(evas_gl != NULL)
	{
		evas_gl_free(evas_gl);
		evas_gl = NULL;
	}

	if(win != NULL)
	{
		evas_object_del(win);
		win = NULL;
	}
	elm_shutdown();
}

/**
 * @testcase		utc_cairo_evas_gl_device_create_n
 * @since_tizen		2.3.1
 * @description		testcase for check invalid input evas_gl_context (NULL).
 */
int utc_cairo_evas_gl_device_create_n(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			cairo_status_t ret = CAIRO_STATUS_SUCCESS;
			cairo_device = (cairo_device_t *)cairo_evas_gl_device_create (evas_gl, NULL);
			ret = cairo_device_status(cairo_device);
			fprintf(stderr, "\\n[Line : %d] : %d \\n", __LINE__, ret);
			assert_eq(ret, CAIRO_STATUS_NO_MEMORY);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}
    return 0;
}

/**
 * @testcase		utc_cairo_evas_gl_device_create_n1
 * @since_tizen		2.3.1
 * @description		testcase for check invalid input evas_gl (NULL).
 */
int utc_cairo_evas_gl_device_create_n1(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			cairo_status_t ret = CAIRO_STATUS_SUCCESS;
			cairo_device = (cairo_device_t *)cairo_evas_gl_device_create (NULL, evas_gl_context);
			ret = cairo_device_status(cairo_device);
			fprintf(stderr, "\\n[Line : %d] : %d \\n", __LINE__, ret);
			assert_eq(ret, CAIRO_STATUS_NO_MEMORY);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_evas_gl_device_create_p
 * @since_tizen		2.3.1
 * @description		testcase for check normal inputs.
 */
int utc_cairo_evas_gl_device_create_p(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			cairo_status_t ret = CAIRO_STATUS_SUCCESS;
			cairo_device = (cairo_device_t *)cairo_evas_gl_device_create (evas_gl, evas_gl_context);
			ret = cairo_device_status(cairo_device);
			fprintf(stderr, "\\n[Line : %d] : %d \\n", __LINE__, ret);
			assert_eq(ret, CAIRO_STATUS_SUCCESS);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_gl_surface_create_for_evas_gl_n
 * @since_tizen		2.3.1
 * @description		testcase for check invalid inputs (evas_gl_surface, evas_gl_config as NULL).
 */
int utc_cairo_gl_surface_create_for_evas_gl_n(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			cairo_status_t ret = CAIRO_STATUS_SUCCESS;
			int width = 30;
			int height = 30;

			cairo_device = (cairo_device_t *)cairo_evas_gl_device_create (evas_gl, evas_gl_context);
			surface = (cairo_surface_t *)cairo_gl_surface_create_for_evas_gl(cairo_device,  NULL, NULL, width, height);

			ret = cairo_surface_status(surface);
			fprintf(stderr, "\\n[Line : %d] : %d \\n", __LINE__, ret);
			assert_eq(ret, CAIRO_STATUS_NO_MEMORY);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_gl_surface_create_for_evas_gl_n1
 * @since_tizen		2.3.1
 * @description		testcase for check invalid input cairo_device (get_device from image surface).
 */
int utc_cairo_gl_surface_create_for_evas_gl_n1(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			cairo_status_t ret = CAIRO_STATUS_SUCCESS;
			int width = 30;
			int height = 25;

			surface = (cairo_surface_t *)cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
			cairo_device = (cairo_device_t *)cairo_surface_get_device(surface);
			cairo_surface_destroy(surface);

			surface = (cairo_surface_t *)cairo_gl_surface_create_for_evas_gl(cairo_device, evas_gl_surface, evas_gl_config, width, height);
			ret = cairo_surface_status(surface);
			fprintf(stderr, "\\n[Line : %d] : %d \\n", __LINE__, ret);
			assert_eq(ret, CAIRO_STATUS_NO_MEMORY);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_gl_surface_create_for_evas_gl_n2
 * @since_tizen		2.3.1
 * @description		testcase for check invalid input width (0).
 */
int utc_cairo_gl_surface_create_for_evas_gl_n2(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			cairo_status_t ret = CAIRO_STATUS_SUCCESS;
			int width = 0;
			int height = 30;

			cairo_device = (cairo_device_t *)cairo_evas_gl_device_create (evas_gl, evas_gl_context);
			surface = (cairo_surface_t *)cairo_gl_surface_create_for_evas_gl(cairo_device, evas_gl_surface, evas_gl_config, width, height);
			ret = cairo_surface_status(surface);
			fprintf(stderr, "\\n[Line : %d] : %d \\n", __LINE__, ret);
			assert_eq(ret, CAIRO_STATUS_INVALID_SIZE);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_gl_surface_create_for_evas_gl_n3
 * @since_tizen		2.3.1
 * @description		testcase for check invalid input height (0).
 */
int utc_cairo_gl_surface_create_for_evas_gl_n3(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			cairo_status_t ret = CAIRO_STATUS_SUCCESS;
			int width = 30;
			int height = 0;

			cairo_device = (cairo_device_t *)cairo_evas_gl_device_create (evas_gl, evas_gl_context);
			surface = (cairo_surface_t *)cairo_gl_surface_create_for_evas_gl(cairo_device, evas_gl_surface, evas_gl_config, width, height);

			ret = cairo_surface_status(surface);
			fprintf(stderr, "\\n[Line : %d] : %d \\n", __LINE__, ret);
			assert_eq(ret, CAIRO_STATUS_INVALID_SIZE);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_gl_surface_create_for_evas_gl_p
 * @since_tizen		2.3.1
 * @description		testcase for check normal inputs.
 */
int utc_cairo_gl_surface_create_for_evas_gl_p(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			cairo_status_t ret = CAIRO_STATUS_SUCCESS;
			int width = 30;
			int height = 25;

			cairo_device = (cairo_device_t *)cairo_evas_gl_device_create (evas_gl, evas_gl_context);
			surface = (cairo_surface_t *)cairo_gl_surface_create_for_evas_gl(cairo_device, evas_gl_surface, evas_gl_config, width, height);
			ret = cairo_surface_status(surface);
			fprintf(stderr, "\\n[Line : %d] : %d \\n", __LINE__, ret);
			assert_eq(ret, CAIRO_STATUS_SUCCESS);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_evas_gl_device_get_gl_n
 * @since_tizen		2.3.1
 * @description		testcase for check invalid input evas_gl (NULL).
 */
int utc_cairo_evas_gl_device_get_gl_n(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			Evas_GL *ret_evas_gl = NULL;
			cairo_device = (cairo_device_t *)cairo_evas_gl_device_create (NULL, evas_gl_context);
			ret_evas_gl = cairo_evas_gl_device_get_gl(cairo_device);
			if(ret_evas_gl != NULL)
				fprintf(stderr, "\\n[Line : %d] error : cairo_evas_gl_device_get_gl() return NOT NULL\\n", __LINE__);
			else
				fprintf(stderr, "\\n[Line : %d] : cairo_evas_gl_device_get_gl() return NULL\\n", __LINE__);
			assert_eq(ret_evas_gl, NULL);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_evas_gl_device_get_gl_n1
 * @since_tizen		2.3.1
 * @description		testcase for check invalid input cairo_device (get_device from image surface).
 */
int utc_cairo_evas_gl_device_get_gl_n1(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			int width = 30;
			int height = 25;
			Evas_GL *ret_evas_gl = NULL;
			surface = (cairo_surface_t *)cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
			cairo_device = (cairo_device_t *)cairo_surface_get_device(surface);

			ret_evas_gl = cairo_evas_gl_device_get_gl(cairo_device);
			if(ret_evas_gl != NULL)
				fprintf(stderr, "\\n[Line : %d] error : cairo_evas_gl_device_get_gl() return NOT NULL\\n", __LINE__);
			else
				fprintf(stderr, "\\n[Line : %d] : cairo_evas_gl_device_get_gl() return NULL\\n", __LINE__);
			assert_eq(ret_evas_gl, NULL);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_evas_gl_device_get_gl_p
 * @since_tizen		2.3.1
 * @description		testcase for check normal inputs.
 */
int utc_cairo_evas_gl_device_get_gl_p(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			Evas_GL *ret_evas_gl = NULL;
			cairo_device = (cairo_device_t *)cairo_evas_gl_device_create (evas_gl, evas_gl_context);
			ret_evas_gl = cairo_evas_gl_device_get_gl(cairo_device);
			if(ret_evas_gl == NULL)
				fprintf(stderr, "\\n[Line : %d] error : cairo_evas_gl_device_get_gl() return NULL\\n", __LINE__);
			else
				fprintf(stderr, "\\n[Line : %d] : cairo_evas_gl_device_get_gl() return NOT NULL\\n", __LINE__);
			assert_neq(ret_evas_gl, NULL);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_evas_gl_device_get_context_n
 * @since_tizen		2.3.1
 * @description		testcase for check invalid input evas_gl_context (NULL).
 */
int utc_cairo_evas_gl_device_get_context_n(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			Evas_GL_Context *ret_evas_gl_context;
			cairo_device = (cairo_device_t *)cairo_evas_gl_device_create (evas_gl, NULL);
			ret_evas_gl_context = cairo_evas_gl_device_get_context(cairo_device);
			if(ret_evas_gl_context != NULL)
				fprintf(stderr, "\\n[Line : %d] error : cairo_evas_gl_device_get_context() return NOT NULL \\n", __LINE__);
			else
				fprintf(stderr, "\\n[Line : %d] : cairo_evas_gl_device_get_context() return NULL \\n", __LINE__);
			assert_eq(ret_evas_gl_context, NULL);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_evas_gl_device_get_context_n1
 * @since_tizen		2.3.1
 * @description		testcase for check invalid input cairo_device (get_device from image surface).
 */
int utc_cairo_evas_gl_device_get_context_n1(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			int width = 30;
			int height = 25;
			Evas_GL_Context *ret_evas_gl_context;
			surface = (cairo_surface_t *)cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
			cairo_device = (cairo_device_t *)cairo_surface_get_device(surface);

			ret_evas_gl_context = cairo_evas_gl_device_get_context(cairo_device);
			if(ret_evas_gl_context != NULL)
				fprintf(stderr, "\\n[Line : %d] error : cairo_evas_gl_device_get_context() return NOT NULL \\n", __LINE__);
			else
				fprintf(stderr, "\\n[Line : %d] : cairo_evas_gl_device_get_context() return NULL \\n", __LINE__);
			assert_eq(ret_evas_gl_context, NULL);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_evas_gl_device_get_context_p
 * @since_tizen		2.3.1
 * @description		testcase for check normal inputs.
 */
int utc_cairo_evas_gl_device_get_context_p(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			Evas_GL_Context *ret_evas_gl_context;
			cairo_device = (cairo_device_t *)cairo_evas_gl_device_create (evas_gl, evas_gl_context);
			ret_evas_gl_context = cairo_evas_gl_device_get_context(cairo_device);
			if(ret_evas_gl_context == NULL)
				fprintf(stderr, "\\n[Line : %d] error : cairo_evas_gl_device_get_context() return NULL \\n", __LINE__);
			else
				fprintf(stderr, "\\n[Line : %d] : cairo_evas_gl_device_get_context() return NOT NULL \\n", __LINE__);
			assert_neq(ret_evas_gl_context, NULL);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_gl_surface_create_n
 * @since_tizen		2.3.1
 * @description		testcase for check invalid input content (0x4000).
 */
int utc_cairo_gl_surface_create_n(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			cairo_status_t ret = CAIRO_STATUS_SUCCESS;
			int width = 30;
			int height = 0;

			cairo_device = (cairo_device_t *)cairo_evas_gl_device_create (evas_gl, evas_gl_context);
			surface = (cairo_surface_t *)cairo_gl_surface_create(cairo_device, 0x4000, width, height);

			ret = cairo_surface_status(surface);
			fprintf(stderr, "\\n[Line : %d] : %d \\n", __LINE__, ret);
			assert_eq(ret, CAIRO_STATUS_INVALID_CONTENT);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_gl_surface_create_p
 * @since_tizen		2.3.1
 * @description		testcase for check normal inputs.
 */
int utc_cairo_gl_surface_create_p(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			cairo_status_t ret = CAIRO_STATUS_SUCCESS;
			int width = 30;
			int height = 30;

			cairo_device = (cairo_device_t *)cairo_evas_gl_device_create (evas_gl, evas_gl_context);
			surface = (cairo_surface_t *)cairo_gl_surface_create(cairo_device, CAIRO_CONTENT_COLOR_ALPHA, width, height);
			ret = cairo_surface_status(surface);
			fprintf(stderr, "\\n[Line : %d] : %d \\n", __LINE__, ret);
			assert_eq(ret, CAIRO_STATUS_SUCCESS);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_gl_surface_create_for_texture_n
 * @since_tizen		2.3.1
 * @description		testcase for check invalid input cairo_device (get_device from image surface).
 */
int utc_cairo_gl_surface_create_for_texture_n(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			cairo_status_t ret = CAIRO_STATUS_SUCCESS;
			int width = 30;
			int height = 30;

			surface = (cairo_surface_t *)cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
			cairo_device = (cairo_device_t *)cairo_surface_get_device(surface);
			cairo_surface_destroy(surface);

			surface = (cairo_surface_t *)cairo_gl_surface_create_for_texture(cairo_device, CAIRO_CONTENT_COLOR_ALPHA, 0, width, height);

			ret = cairo_surface_status(surface);
			fprintf(stderr, "\\n[Line : %d] : %d \\n", __LINE__, ret);
			assert_eq(ret, CAIRO_STATUS_NO_MEMORY);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_gl_surface_create_for_texture_p
 * @since_tizen		2.3.1
 * @description		testcase for check normal inputs.
 */
int utc_cairo_gl_surface_create_for_texture_p(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			cairo_status_t ret = CAIRO_STATUS_SUCCESS;
			int width = 30;
			int height = 30;

			cairo_device = (cairo_device_t *)cairo_evas_gl_device_create (evas_gl, evas_gl_context);
			surface = (cairo_surface_t *)cairo_gl_surface_create_for_texture(cairo_device, CAIRO_CONTENT_COLOR_ALPHA, 0, width, height);
			ret = cairo_surface_status(surface);
			fprintf(stderr, "\\n[Line : %d] : %d \\n", __LINE__, ret);
			assert_eq(ret, CAIRO_STATUS_SUCCESS);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_gl_surface_get_width_n
 * @since_tizen		2.3.1
 * @description		testcase for check invalid input cairo_device (NULL).
 */
int utc_cairo_gl_surface_get_width_n(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			int width = 30;
			int height = 25;
			int ret = 0;

			surface = (cairo_surface_t *)cairo_gl_surface_create(NULL, CAIRO_CONTENT_COLOR_ALPHA, width, height);
			ret = cairo_gl_surface_get_width(surface);
			fprintf(stderr, "\\n[Line : %d] : %d \\n", __LINE__, ret);
			assert_eq(ret, 0);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_gl_surface_get_width_p
 * @since_tizen		2.3.1
 * @description		testcase for check normal inputs.
 */
int utc_cairo_gl_surface_get_width_p(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			int width = 30;
			int height = 25;
			int ret = 0;

			cairo_device = (cairo_device_t *)cairo_evas_gl_device_create (evas_gl, evas_gl_context);
			surface = (cairo_surface_t *)cairo_gl_surface_create(cairo_device, CAIRO_CONTENT_COLOR_ALPHA, width, height);
			ret = cairo_gl_surface_get_width(surface);
			fprintf(stderr, "\\n[Line : %d] : %d \\n", __LINE__, ret);
			assert_eq(ret, width);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_gl_surface_get_height_n
 * @since_tizen		2.3.1
 * @description		testcase for check invalid input cairo_device (NULL).
 */
int utc_cairo_gl_surface_get_height_n(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			int width = 30;
			int height = 25;
			int ret = 0;

			surface = (cairo_surface_t *)cairo_gl_surface_create(NULL, CAIRO_CONTENT_COLOR_ALPHA, width, height);
			ret = cairo_gl_surface_get_height(surface);
			fprintf(stderr, "\\n[Line : %d] : %d \\n", __LINE__, ret);
			assert_eq(ret, 0);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_gl_surface_get_height_p
 * @since_tizen		2.3.1
 * @description		testcase for check normal inputs.
 */
int utc_cairo_gl_surface_get_height_p(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			int width = 30;
			int height = 25;
			int ret = 0;

			cairo_device = (cairo_device_t *)cairo_evas_gl_device_create (evas_gl, evas_gl_context);
			surface = (cairo_surface_t *)cairo_gl_surface_create(cairo_device, CAIRO_CONTENT_COLOR_ALPHA, width, height);
			ret = cairo_gl_surface_get_height(surface);
			fprintf(stderr, "\\n[Line : %d] : %d \\n", __LINE__, ret);
			assert_eq(ret, height);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_gl_device_set_thread_aware_n
 * @since_tizen		2.3.1
 * @description		testcase for check invalid input state (-1).
 */
int utc_cairo_gl_device_set_thread_aware_n(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			cairo_status_t ret = CAIRO_STATUS_SUCCESS;
			cairo_device = (cairo_device_t *)cairo_evas_gl_device_create (evas_gl, evas_gl_context);
			cairo_gl_device_set_thread_aware(cairo_device, -1);
			ret = cairo_device_status(cairo_device);
			fprintf(stderr, "\\n[Line : %d] : %d \\n", __LINE__, ret);
			assert_eq(ret, CAIRO_STATUS_INVALID_STATUS);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

/**
 * @testcase		utc_cairo_gl_device_set_thread_aware_p
 * @since_tizen		2.3.1
 * @description		testcase for check normal inputs.
 */
int utc_cairo_gl_device_set_thread_aware_p(void)
{
	if(is_supported)
	{
		if(evas_state)
		{
			cairo_status_t ret = CAIRO_STATUS_SUCCESS;
			cairo_device = (cairo_device_t *)cairo_evas_gl_device_create (evas_gl, evas_gl_context);
			cairo_gl_device_set_thread_aware(cairo_device, 0);
			ret = cairo_device_status(cairo_device);
			fprintf(stderr, "\\n[Line : %d] : %d \\n", __LINE__, ret);
			assert_eq(ret, CAIRO_STATUS_SUCCESS);
		}
		else
		{
			assert_eq(evas_state, 1);
		}
	}
	else
	{
		assert_eq(is_supported, 0);
	}

    return 0;
}

