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
#include "ITs-tbm-common.h"

/** @addtogroup itc-tbm
*  @ingroup itc
*  @{
*/

unsigned int *nTbmFormatArray;
unsigned int g_nTotalFormatCount = 0;

/**
* @function 		ITs_tbm_startup
* @description	 	Called before each test, opens pre-defined app
* @parameter		NA
* @return 			NA
*/
void ITs_tbm_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Tbm_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet = tbm_surface_query_formats(&nTbmFormatArray, &g_nTotalFormatCount);
	if ( nRet != TBM_SURFACE_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] No supported TBM surface format\\n", __LINE__, API_NAMESPACE);
		g_bLibtbmInit = false;
	}
	g_bLibtbmInit = true;
}

/**
* @function 		ITs_tbm_cleanup
* @description	 	Called after each test, terminates the app opened in startup
* @parameter		NA
* @return 			NA
*/ 
void ITs_tbm_cleanup(void)
{
	g_bLibtbmInit = false;
	free(nTbmFormatArray);
	g_nTotalFormatCount = 0;

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Tbm_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup itc-tbm-testcases
*  @brief 		Integration testcases for module tbm
*  @ingroup 	itc-tbm
*  @{
*/

//& purpose: To create and destroy tbm_surface
//& type: auto  
/**
* @testcase 				ITc_tbm_surface_create_destroy_p
* @since_tizen 				2.3
* @author            		SRID(m.khalid)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				To create and destroy tbm_surface.
* @scenario					destroy the created tbm_surface\n
*							create tbm_surface\n
*							destroy the created tbm_surface\n
*							create the tbm_surface\n
* @apicovered				tbm_surface_create, tbm_surface_destroy
* @passcase					When tbm_surface_create and tbm_surface_destroy is successful
* @failcase					If tbm_surface_create or tbm_surface_destroy fails
* @precondition				Destroy the already created tbm_surface
* @postcondition			Create the tbm_surface
*/
int ITc_tbm_surface_create_destroy_p(void)
{
	START_TEST;

	int nRet = 0, nTbmFormatCount = 0, nWidth=128, nHeight=128;
	tbm_surface_h hSurface;
	SUPPORT_CHECK;
	for ( nTbmFormatCount = 0; nTbmFormatCount < g_nTotalFormatCount; nTbmFormatCount++ )
	{
		hSurface = tbm_surface_create(nWidth, nHeight, nTbmFormatArray[nTbmFormatCount]);
		CHECK_HANDLE_CLEANUP(hSurface,"tbm_surface_create", LibtbmGetFormatType(nTbmFormatArray[nTbmFormatCount]);get_last_result());

		nRet = tbm_surface_destroy(hSurface);
		PRINT_RESULT(TBM_SURFACE_ERROR_NONE, nRet, "tbm_surface_destroy", LibtbmGetError(nRet))
	}
	return 0;
}

//& purpose: map and unmap the tbm_surface according to access option
//& type: auto  
/**
* @testcase 				ITc_tbm_surface_map_unmap_p
* @since_tizen 				2.3
* @author            		SRID(m.khalid)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				map and unmap the tbm_surface according to access option.
* @scenario					map the tbm_surface according to access option\n
*							unmap the tbm_surface
* @apicovered				tbm_surface_map, tbm_surface_unmap
* @passcase					When tbm_surface_map and tbm_surface_unmap is successful
* @failcase					If tbm_surface_map or tbm_surface_unmap fails
* @precondition				tbm_surface should be created
* @postcondition			tbm_surface should be destroyed
*/

int ITc_tbm_surface_map_unmap_p(void)
{
	START_TEST;

	int nRet = 0, nTbmFormatCount = 0;
	tbm_surface_info_s info;
	SUPPORT_CHECK;

	for ( nTbmFormatCount = 0; nTbmFormatCount<g_nTotalFormatCount; nTbmFormatCount++ )
	{
		if ( LibtbmCreateSurface(nTbmFormatArray[nTbmFormatCount]) == false )
		{
			return 1;
		}

		nRet = tbm_surface_map(g_surface,TBM_SURF_OPTION_WRITE|TBM_SURF_OPTION_READ, &info);
		PRINT_RESULT_CLEANUP(TBM_SURFACE_ERROR_NONE, nRet,"tbm_surface_map", LibtbmGetError(nRet), LibtbmDestroySurface());

		nRet = tbm_surface_unmap(g_surface);
		PRINT_RESULT_CLEANUP(TBM_SURFACE_ERROR_NONE, nRet,"tbm_surface_unmap", LibtbmGetError(nRet), LibtbmDestroySurface());

		LibtbmDestroySurface();
	}
	return 0;
}

//& purpose: Get the width of tbm_surface
//& type: auto  
/**
* @testcase 				ITc_tbm_surface_get_width_p
* @since_tizen 				2.3
* @author            		SRID(m.khalid)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Get the width of tbm_surface.
* @scenario					get the width of tbm_surface by using tbm_surface_get_width API.
* @apicovered				tbm_surface_get_width
* @passcase					When tbm_surface_get_width is successful
* @failcase					If tbm_surface_get_width fails
* @precondition				create tbm_surface
* @postcondition			tbm_surface should be destroyed
*/
int ITc_tbm_surface_get_width_p(void)
{
	START_TEST;

	int nTbmFormatCount = 0;
	int nWidth = 0;
	SUPPORT_CHECK;

	for ( nTbmFormatCount = 0; nTbmFormatCount<g_nTotalFormatCount; nTbmFormatCount++ )
	{
		if ( LibtbmCreateSurface(nTbmFormatArray[nTbmFormatCount]) == false )
		{
			return 1;
		}
		nWidth = tbm_surface_get_width(g_surface);
		if ( nWidth == TBM_SURFACE_ERROR_INVALID_PARAMETER )
		{
			FPRINTF("[Line : %d][%s] tbm_surface_get_width is unsuccessful for tbm format value = %s\\n", __LINE__, API_NAMESPACE, LibtbmGetFormatType(nTbmFormatArray[nTbmFormatCount]));
			LibtbmDestroySurface();
			return 1;
		}
		else
		{
#if DEBUG
			FPRINTF("[Line : %d][%s] tbm_surface_get_width is successful for tbm format value = %s with width value = %d\\n", __LINE__, API_NAMESPACE, LibtbmGetFormatType(nTbmFormatArray[nTbmFormatCount]), nWidth);
#endif
		}
		LibtbmDestroySurface();
	}
	return 0;
}

//& purpose: Get the height of tbm_surface
//& type: auto  
/**
* @testcase 				ITc_tbm_surface_get_height_p
* @since_tizen 				2.3
* @author            		SRID(m.khalid)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Get the height of tbm_surface.
* @scenario					get the height of tbm_surface by using tbm_surface_get_height API.
* @apicovered				tbm_surface_get_height
* @passcase					When tbm_surface_get_height is successful
* @failcase					If tbm_surface_get_height fails
* @precondition				create tbm_surface
* @postcondition			tbm_surface should be destroyed
*/
int ITc_tbm_surface_get_height_p(void)
{
	START_TEST;

	int nTbmFormatCount = 0;
	int nHeight = 0;
	SUPPORT_CHECK;
	for ( nTbmFormatCount = 0; nTbmFormatCount<g_nTotalFormatCount; nTbmFormatCount++ )
	{
		if ( LibtbmCreateSurface(nTbmFormatArray[nTbmFormatCount]) == false )
		{
			return 1;
		}
		nHeight = tbm_surface_get_height(g_surface);
		if ( nHeight == TBM_SURFACE_ERROR_INVALID_PARAMETER )
		{
			FPRINTF("[Line : %d][%s] tbm_surface_get_height is unsuccessful for tbm format value = %s\\n", __LINE__, API_NAMESPACE, LibtbmGetFormatType(nTbmFormatArray[nTbmFormatCount]));
			LibtbmDestroySurface();
			return 1;
		}
		else
		{
#if DEBUG
			FPRINTF("[Line : %d][%s] tbm_surface_get_height is successful for tbm format value = %s with height value = %d\\n", __LINE__, API_NAMESPACE, LibtbmGetFormatType(nTbmFormatArray[nTbmFormatCount]), nHeight);
#endif
		}
		LibtbmDestroySurface();
	}
	return 0;
}

//& purpose: Queries surface format list and number of format supported by the system
//& type: auto  
/**
* @testcase 				ITc_tbm_surface_query_formats_p
* @since_tizen 				2.3
* @author            		SRID(m.khalid)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Queries surface format list and number of format supported by the system
* @scenario					Call tbm_surface_query_formats to get formats and number of format
* @apicovered				tbm_surface_query_formats
* @passcase					When tbm_surface_query_formats is successful
* @failcase					If tbm_surface_query_formats fails
* @precondition				NA
* @postcondition			format must be freed.
*/
int ITc_tbm_surface_query_formats_p(void)
{
	START_TEST;

	unsigned int *nFormats;
	unsigned int nFormatNum;
	int nCount = 0;

	int nRet = tbm_surface_query_formats(&nFormats, &nFormatNum);
	PRINT_RESULT(TBM_SURFACE_ERROR_NONE, nRet, "tbm_surface_query_formats", LibtbmGetError(nRet));

	FPRINTF("[Line : %d][%s]Supported formats are : ", __LINE__, API_NAMESPACE);
	for ( nCount = 0; nCount<nFormatNum; nCount++ )
	{
		FPRINTF("\\n%s\\n", LibtbmGetFormatType(nFormats[nCount]));
	}

	FREE_MEMORY(nFormats);
	return 0;
}

//& purpose: Get the information of tbm_surface
//& type: auto  
/**
* @testcase 				ITc_tbm_surface_get_info_p
* @since_tizen 				2.3
* @author            		SRID(m.khalid)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Get the information of tbm_surface
* @scenario					Get the tbm_surface info by using tbm_surface_get_info API
* @apicovered				tbm_surface_get_info
* @passcase					When tbm_surface_get_info is successful
* @failcase					If tbm_surface_get_info fails
* @precondition				tbm_surface should be created
* @postcondition			Destroy the tbm_surface
*/
int ITc_tbm_surface_get_info_p(void)
{
	START_TEST;

	int nRet = 0, nTbmFormatCount = 0;
	tbm_surface_info_s info;
	SUPPORT_CHECK;
	for ( nTbmFormatCount = 0; nTbmFormatCount<g_nTotalFormatCount; nTbmFormatCount++ )
	{
		if ( LibtbmCreateSurface(nTbmFormatArray[nTbmFormatCount]) == false )
		{
			return 1;
		}
		nRet = tbm_surface_get_info(g_surface, &info);
		PRINT_RESULT_CLEANUP(TBM_SURFACE_ERROR_NONE, nRet,"tbm_surface_get_info", LibtbmGetError(nRet),LibtbmDestroySurface());

		LibtbmDestroySurface();
	}
	return 0;
}

//& purpose: Get the format of tbm_surface
//& type: auto  
/**
* @testcase 				ITc_tbm_surface_get_format_p
* @since_tizen 				2.3
* @author            		SRID(m.khalid)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Get the format of the tbm_surface
* @scenario					Get the format info by using tbm_surface_get_format API
* @apicovered				tbm_surface_get_format
* @passcase					When tbm_surface_get_format is successful
* @failcase					If tbm_surface_get_format fails
* @precondition				tbm_surface should be created
* @postcondition			Destroy the tbm_surface
*/
int ITc_tbm_surface_get_format_p(void)
{
	START_TEST;

	int nRet = 0, nTbmFormatCount = 0;
	SUPPORT_CHECK;
	for ( nTbmFormatCount = 0; nTbmFormatCount<g_nTotalFormatCount; nTbmFormatCount++ )
	{
		if ( LibtbmCreateSurface(nTbmFormatArray[nTbmFormatCount]) == false )
		{
			return 1;
		}
		nRet = tbm_surface_get_format(g_surface);
		if ( nRet != nTbmFormatArray[nTbmFormatCount])
		{
			FPRINTF("[Line : %d][%s] tbm_surface_get_format failed for tbm format value = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, LibtbmGetFormatType(nTbmFormatArray[nTbmFormatCount]), LibtbmGetError(nRet));
			LibtbmDestroySurface();
			return 1;
		}
		LibtbmDestroySurface();
	}
	return 0;
}
/** @} */ 
/** @} */ 