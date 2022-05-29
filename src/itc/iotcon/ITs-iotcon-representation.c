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
#include "ITs-iotcon-common.h"
#define LOOP_COUNT 5

//& set: Iotcon

/** @addtogroup itc-iotcon
*  @ingroup itc
*  @{
*/



iotcon_representation_h g_hRepresentation = NULL;

/**
 * @function 		ITs_iotcon_representation_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_representation_startup(void)
{
	struct stat stBuff;
	char *svr_db_path;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	g_bIotconConnect = true;
	g_bFeatureUnsupported = false;

	ic_get_svr_db_path(&svr_db_path);
   int nRet = iotcon_initialize(svr_db_path);
	free(svr_db_path);

	if ( !TCTCheckSystemInfoFeatureSupported(IOTCON_FEATURE, API_NAMESPACE) )
	{

		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] iotcon_initialize API call returned mismatch %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
			g_bIotconConnect = false;
		}
		else
		{
			FPRINTF("[Line : %d][%s] iotcon_initialize API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
			g_bFeatureUnsupported = true;
		}
		return;
	}

	if ( nRet != IOTCON_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] iotcon_initialize failed API return %s error \\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
		g_bIotconConnect = false;
		return;
	}

	nRet = iotcon_representation_create(&g_hRepresentation);
	if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] iotcon_representation_create: %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		iotcon_deinitialize();
		g_bIotconConnect = false;
		return;
	}

	if (g_hRepresentation == NULL )
	{
		FPRINTF("[Line : %d][%s] Handle to representation object is returned NULL \n", __LINE__, API_NAMESPACE);
		iotcon_representation_destroy (g_hRepresentation);
		iotcon_deinitialize();
		g_bIotconConnect = false;
		return;
	}
	return;
}


/**
 * @function 		ITs_iotcon_representation_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_representation_cleanup(void)
{
	if(g_hRepresentation != NULL)
	{
		iotcon_representation_destroy (g_hRepresentation);
		g_hRepresentation = NULL;
	}
	if(g_bIotconConnect)
	{
		iotcon_deinitialize();

	}
	return;
}

//& type: auto
//& purpose:  scenario to create & destroy options
/**
* @testcase 			ITc_iotcon_representation_create_destroy_p
* @author            	SRID(abhishek.y)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to create representation
* @scenario				destroy and create representation \n

* @apicovered			iotcon_representation_create,iotcon_representation_destroy
* @passcase				When iotcon_representation_destroy and iotcon_representation_create are successful.
* @failcase				If target API iotcon_representation_destroy and iotcon_representation_create or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/

int ITc_iotcon_representation_create_destroy_p(void)
{
	START_TEST;
	iotcon_representation_h hRepresentation = NULL;
	int nRet = iotcon_representation_create(&hRepresentation);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_representation_create", IotConGetError(nRet));
	CHECK_HANDLE(hRepresentation,"iotcon_representation_create");

	nRet = iotcon_representation_destroy (hRepresentation);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_representation_destroy", IotConGetError(nRet));
	return 0;
}

/**
* @testcase 			ITc_iotcon_representation_clone_p
* @author            	SRID(abhishek.y)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to clone a already created representation
* @scenario				clone and destroy representation \n
* @apicovered			iotcon_representation_clone,iotcon_representation_destroy
* @passcase				When iotcon_representation_clone and iotcon_representation_destroy are successful.
* @failcase				If target API iotcon_representation_clone and iotcon_representation_destroy or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_representation_clone_p(void)
{
	START_TEST;

	iotcon_representation_h hRepr = NULL;

	int nRet = iotcon_representation_clone(g_hRepresentation, &hRepr);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_representation_clone", IotConGetError(nRet));
	CHECK_HANDLE(hRepr,"iotcon_representation_clone");

	nRet = iotcon_representation_destroy(hRepr);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_representation_destroy", IotConGetError(nRet));

    return 0;
}

/**
* @testcase 			ITc_iotcon_representation_set_get_uri_path_p
* @author            	SRID(abhishek.y)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to set uri path and get uri path for representation
* @scenario				set uriPath and get uriPath representation \n
* @apicovered			iotcon_representation_set_uri_path,iotcon_representation_get_uri_path
* @passcase				When iotcon_representation_set_uri_path and iotcon_representation_get_uri_path are successful.
* @failcase				If target API iotcon_representation_get_uri_path and iotcon_representation_set_uri_path or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_representation_set_get_uri_path_p(void)
{
	START_TEST;
	char *uri=NULL;
	int nRet = iotcon_representation_set_uri_path(g_hRepresentation, "/a/led");
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_representation_set_uri_path", IotConGetError(nRet));

	nRet = iotcon_representation_get_uri_path(g_hRepresentation, &uri);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_representation_get_uri_path", IotConGetError(nRet));
	CHECK_HANDLE(uri,"iotcon_representation_get_uri_path");

	if (0 != strcmp("/a/led", uri))
	{
		FPRINTF("[Line : %d][%s] Values of set get not matched!!! !!!\\n", __LINE__, API_NAMESPACE);
        return 1;
	}
    return 0;
}
/**
* @testcase 			ITc_iotcon_representation_set_get_resource_types_p
* @author            	SRID(abhishek.y)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to set resource type and get resource type for representation
* @scenario				first create resource type then add resource type and the set for representation and get for representation\n
* @apicovered			iotcon_resource_types_create,iotcon_resource_types_add,iotcon_representation_set_resource_types,iotcon_representation_get_resource_types.
* @passcase				When iotcon_representation_set_resource_types and iotcon_representation_get_resource_types are successful.
* @failcase				If target API iotcon_representation_get_resource_types and iotcon_representation_set_resource_types or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_representation_set_get_resource_types_p(void)
{
	START_TEST;
	int ret;
	iotcon_resource_types_h hTypes = NULL;
	iotcon_resource_types_h hGettype = NULL;

	ret = iotcon_resource_types_create(&hTypes);
	PRINT_RESULT(IOTCON_ERROR_NONE, ret, "iotcon_resource_types_create", IotConGetError(ret));
	CHECK_HANDLE(hTypes,"iotcon_resource_types_create");

	ret = iotcon_resource_types_add(hTypes, REMOTE_RESOURCE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_resource_types_add", IotConGetError(ret),iotcon_resource_types_destroy(hTypes));

	ret = iotcon_representation_set_resource_types(g_hRepresentation, hTypes);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_representation_set_resource_types", IotConGetError(ret),iotcon_resource_types_destroy(hTypes));

	ret = iotcon_representation_get_resource_types(g_hRepresentation, &hGettype);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_representation_get_resource_types", IotConGetError(ret),iotcon_resource_types_destroy(hTypes));
	if (hGettype == NULL )
	{
		FPRINTF("[Line : %d][%s] Handle to resource type object is returned NULL \n", __LINE__, API_NAMESPACE);
		iotcon_resource_types_destroy(hTypes);
		return 1;
	}
	if(hTypes != hGettype)
	{
		FPRINTF("[Line : %d][%s] Values of set get not matched!!!\\n", __LINE__, API_NAMESPACE);
		iotcon_resource_types_destroy(hTypes);
        return 1;
	}

	iotcon_resource_types_destroy(hTypes);

    return 0;
}
/**
* @testcase 			ITc_iotcon_representation_set_get_resource_interfaces_p
* @author            	SRID(abhishek.y)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to set resource interfaces and get resource interfaces for representation
* @scenario				set different different resource interfaces and get each resource interfaces for representation \n
* @apicovered			iotcon_representation_set_resource_interfaces,iotcon_representation_get_resource_interfaces
* @passcase				When iotcon_representation_set_resource_interfaces and iotcon_representation_get_resource_interfaces are successful.
* @failcase				If target API iotcon_representation_get_resource_interfaces and iotcon_representation_set_resource_interfaces or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_representation_set_get_resource_interfaces_p(void)
{
	START_TEST;

	int nRet = 0;
	iotcon_resource_interfaces_h hfaces = NULL;
	iotcon_resource_interfaces_h hfacesOut;

	nRet = iotcon_resource_interfaces_create(&hfaces);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_create", IotConGetError(nRet));
	CHECK_HANDLE(hfaces,"iotcon_resource_interfaces_create");

	nRet = iotcon_resource_interfaces_add(hfaces, IOTCON_INTERFACE_DEFAULT);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_add", IotConGetError(nRet),iotcon_resource_interfaces_destroy(hfaces));

	nRet = iotcon_representation_set_resource_interfaces(g_hRepresentation, hfaces);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_representation_set_resource_interfaces", IotConGetError(nRet),iotcon_resource_interfaces_destroy(hfaces));

	nRet = iotcon_representation_get_resource_interfaces(g_hRepresentation, &hfacesOut);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_representation_get_resource_interfaces", IotConGetError(nRet) ,iotcon_resource_interfaces_destroy(hfaces));

	if(hfaces != hfacesOut)
	{
		FPRINTF("[Line : %d][%s] Values of set get not matched!!!\\n", __LINE__, API_NAMESPACE);
		iotcon_resource_interfaces_destroy(hfaces);
		return 1;
	}

	nRet = iotcon_resource_interfaces_destroy(hfaces);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_destroy", IotConGetError(nRet));
	
    return 0;
}

/**
* @testcase 			ITc_iotcon_representation_set_get_attributes_p
* @author            	SRID(abhishek.y)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to set state and get state for representation
* @scenario				set state and get state for representation \n
* @apicovered			iotcon_representation_set_attributes,iotcon_representation_get_attributes
* @passcase				When iotcon_representation_set_attributes and iotcon_representation_get_attributes are successful.
* @failcase				If target API iotcon_representation_get_attributes and iotcon_representation_set_attributes or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/

int ITc_iotcon_representation_set_get_attributes_p(void)
{
	START_TEST;
	int ret;
	iotcon_attributes_h hSetAttributes=NULL;
	iotcon_attributes_h hGetState=NULL;
	int value = 10;
	ret = iotcon_attributes_create(&hSetAttributes);
	PRINT_RESULT(IOTCON_ERROR_NONE, ret, "iotcon_attributes_create", IotConGetError(ret));
	CHECK_HANDLE(hSetAttributes,"iotcon_attributes_create");

	ret = iotcon_attributes_add_int(hSetAttributes, REPRESENTATION_KEY, value);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_attributes_add_int", IotConGetError(ret),iotcon_attributes_destroy(hSetAttributes));

	ret = iotcon_representation_set_attributes(g_hRepresentation, hSetAttributes);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_representation_set_attributes", IotConGetError(ret),iotcon_attributes_destroy(hSetAttributes));

	ret = iotcon_representation_get_attributes(g_hRepresentation, &hGetState);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_representation_get_attributes", IotConGetError(ret),iotcon_attributes_destroy(hSetAttributes));
	if (hGetState == NULL )
	{
		FPRINTF("[Line : %d][%s] Handle to hGetState object is returned NULL \n", __LINE__, API_NAMESPACE);
		iotcon_attributes_destroy(hSetAttributes);
		return 1;
	}
	if(hSetAttributes != hGetState)
	{
		FPRINTF("[Line : %d][%s] Values of set get state not matched!!!\\n", __LINE__, API_NAMESPACE);
		iotcon_attributes_destroy(hSetAttributes);
        return 1;
	}

	iotcon_attributes_destroy(hSetAttributes);
    return 0;
}

/**
* @testcase 			ITc_iotcon_representation_add_remove_child_p
* @author            	SRID(abhishek.y)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to add child and remove child for representation
* @scenario				add child and remove child for representation \n
* @apicovered			iotcon_representation_add_child,iotcon_representation_remove_child
* @passcase				When iotcon_representation_add_child and iotcon_representation_remove_child are successful.
* @failcase				If target API iotcon_representation_remove_child and iotcon_representation_add_child or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_representation_add_remove_child_p(void)
{
	START_TEST;
	int ret;
	iotcon_representation_h hRepr = NULL;

	ret = iotcon_representation_create(&hRepr);
	PRINT_RESULT(IOTCON_ERROR_NONE, ret, "iotcon_representation_create", IotConGetError(ret));
	CHECK_HANDLE(hRepr,"iotcon_representation_create");

	ret = iotcon_representation_add_child(g_hRepresentation, hRepr);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_representation_add_child", IotConGetError(ret),iotcon_representation_destroy(hRepr));

	ret = iotcon_representation_remove_child(g_hRepresentation, hRepr);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_representation_remove_child", IotConGetError(ret),iotcon_representation_destroy(hRepr));

	iotcon_representation_destroy(hRepr);
    return 0;
}

/**
* @function			IotconForeachChildrenCB
* @description		Specifies the type of function passed to iotcon_representation_foreach_children()
* @parameter[IN]	child is iotcon representation handle
* @parameter[IN]	user_data The user data to pass to the function
* @return			true to continue with the next iteration of the loop.
*/

static bool IotconForeachChildrenCB(iotcon_representation_h child, void *user_data)
{
	if (user_data)
		++ (*((int *)user_data));
	if(child == NULL)
	{
		FPRINTF("[Line : %d][%s] IotconForeachChildrenCB input resource is NULL failed !!!\\n", __LINE__, API_NAMESPACE);
	}
	g_bCheckCb = true;

	return IOTCON_FUNC_CONTINUE;
}
/**
* @testcase 			ITc_iotcon_representation_foreach_children_p
* @author            	SRID(abhishek.y)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to add child and remove child for representation
* @scenario				add child and remove child for representation \n
* @apicovered			iotcon_representation_create,iotcon_representation_add_child,iotcon_representation_foreach_children
* @passcase				When iotcon_representation_add_child and iotcon_representation_remove_child are successful.
* @failcase				If target API iotcon_representation_remove_child and iotcon_representation_add_child or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_representation_foreach_children_p(void)
{
	START_TEST;
	int ret;
	int count = 0;

	iotcon_representation_h hRepr1=NULL;
	iotcon_representation_h hRepr2=NULL;
	iotcon_representation_h	hRepr3=NULL;
	g_bCheckCb = false;

	ret = iotcon_representation_create(&hRepr1);
	PRINT_RESULT(IOTCON_ERROR_NONE, ret, "iotcon_representation_create", IotConGetError(ret));
	CHECK_HANDLE(hRepr1,"iotcon_representation_create");

	ret = iotcon_representation_create(&hRepr2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_representation_create", IotConGetError(ret),iotcon_representation_destroy(hRepr1));
	if (hRepr2 == NULL )
	{
		FPRINTF("[Line : %d][%s] Handle to representation object is returned NULL \n", __LINE__, API_NAMESPACE);
		iotcon_representation_destroy(hRepr1);
		return 1;
	}

	ret = iotcon_representation_create(&hRepr3);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_representation_create", IotConGetError(ret),iotcon_representation_destroy(hRepr2);iotcon_representation_destroy(hRepr1));
	if (hRepr3 == NULL )
	{
		FPRINTF("[Line : %d][%s] Handle to representation object is returned NULL \n", __LINE__, API_NAMESPACE);
		iotcon_representation_destroy(hRepr2);
		iotcon_representation_destroy(hRepr1);
		return 1;
	}

	ret = iotcon_representation_add_child(g_hRepresentation, hRepr1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_representation_add_child", IotConGetError(ret),iotcon_representation_destroy(hRepr3);iotcon_representation_destroy(hRepr2);iotcon_representation_destroy(hRepr1));

	ret = iotcon_representation_add_child(g_hRepresentation, hRepr2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_representation_add_child", IotConGetError(ret),iotcon_representation_destroy(hRepr3);iotcon_representation_destroy(hRepr2);iotcon_representation_destroy(hRepr1));

	ret = iotcon_representation_add_child(g_hRepresentation, hRepr3);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_representation_add_child", IotConGetError(ret),iotcon_representation_destroy(hRepr3);iotcon_representation_destroy(hRepr2);iotcon_representation_destroy(hRepr1));

	ret = iotcon_representation_foreach_children(g_hRepresentation, IotconForeachChildrenCB, &count);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_representation_foreach_children", IotConGetError(ret),iotcon_representation_destroy(hRepr3);iotcon_representation_destroy(hRepr2);iotcon_representation_destroy(hRepr1));

	if (count != 3)
	{
		FPRINTF("[Line : %d][%s] Count values of foreach_children not matched!!!\\n", __LINE__, API_NAMESPACE);
		iotcon_representation_destroy(hRepr3);
		iotcon_representation_destroy(hRepr2);
		iotcon_representation_destroy(hRepr1);
        return 1;
	}

	iotcon_representation_destroy(hRepr3);
	iotcon_representation_destroy(hRepr2);
	iotcon_representation_destroy(hRepr1);
    return 0;
}

/**
* @testcase 			ITc_iotcon_representation_get_child_count_p
* @author            	SRID(abhishek.y)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to add child and remove child for representation
* @scenario				add child and remove child for representation \n
* @apicovered			iotcon_representation_create,iotcon_representation_add_child, iotcon_representation_get_child_count
* @passcase				When iotcon_representation_add_child and iotcon_representation_remove_child are successful.
* @failcase				If target API iotcon_representation_remove_child and iotcon_representation_add_child or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_representation_get_child_count_p(void)
{
	START_TEST;
	int ret;
	unsigned int count = 0;
	iotcon_representation_h hRepr1 = NULL;
	iotcon_representation_h hRepr2 = NULL;
	iotcon_representation_h hReprChld = NULL;

	ret = iotcon_representation_create(&hReprChld);
	PRINT_RESULT(IOTCON_ERROR_NONE, ret, "iotcon_representation_create", IotConGetError(ret));
	CHECK_HANDLE(hReprChld,"iotcon_representation_create");

	ret = iotcon_representation_create(&hRepr1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_representation_create", IotConGetError(ret), iotcon_representation_destroy(hReprChld));
	if (hRepr1 == NULL )
	{
		FPRINTF("[Line : %d][%s] Handle to representation object is returned NULL \n", __LINE__, API_NAMESPACE);
		iotcon_representation_destroy(hReprChld);
		return 1;
	}

	ret = iotcon_representation_create(&hRepr2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_representation_create", IotConGetError(ret), iotcon_representation_destroy(hReprChld);	iotcon_representation_destroy(hRepr1));
	if (hRepr2 == NULL )
	{
		FPRINTF("[Line : %d][%s] Handle to representation object is returned NULL \n", __LINE__, API_NAMESPACE);
		iotcon_representation_destroy(hReprChld);
		iotcon_representation_destroy(hRepr1);
		return 1;
	}

	ret = iotcon_representation_add_child(hReprChld, hRepr1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_representation_add_child", IotConGetError(ret),iotcon_representation_destroy(hRepr2);iotcon_representation_destroy(hRepr1);iotcon_representation_destroy(hReprChld));

	ret = iotcon_representation_add_child(hReprChld, hRepr2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_representation_add_child", IotConGetError(ret),iotcon_representation_destroy(hRepr2);iotcon_representation_destroy(hRepr1);iotcon_representation_destroy(hReprChld));

	ret =  iotcon_representation_get_child_count(hReprChld, &count);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, " iotcon_representation_get_child_count", IotConGetError(ret),iotcon_representation_destroy(hRepr2);iotcon_representation_destroy(hRepr1);iotcon_representation_destroy(hReprChld));

	if (count != VAL3)
	{
		FPRINTF("[Line : %d][%s] Count values of  iotcon_representation_get_child_count not matched!!!\\n", __LINE__, API_NAMESPACE);
		iotcon_representation_destroy(hRepr2);
		iotcon_representation_destroy(hRepr1);
		iotcon_representation_destroy(hReprChld);
        return 1;
	}

	iotcon_representation_destroy(hReprChld);
	iotcon_representation_destroy(hRepr2);
	iotcon_representation_destroy(hRepr1);
    return 0;
}

/**
* @testcase 			ITc_iotcon_representation_get_nth_child_p
* @author            	SRID(abhishek.y)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to add child sequentially and fetch a particular child for representation
* @scenario				create and add children to representation one by one and get 2nd child using API
*                       iotcon_representation_get_nth_child and match the result.
* @apicovered			iotcon_representation_create,iotcon_representation_add_child,iotcon_representation_get_nth_child
* @passcase				When iotcon_representation_add_child and iotcon_representation_get_nth_child are successful.
* @failcase				If target API iotcon_representation_get_nth_child and iotcon_representation_add_child or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_representation_get_nth_child_p(void)
{
	START_TEST;
	int i;
	int ret;
	iotcon_representation_h hRepr = NULL;
	iotcon_representation_h hReprChld = NULL;

	ret = iotcon_representation_create(&hRepr);
	PRINT_RESULT(IOTCON_ERROR_NONE, ret, "iotcon_representation_create", IotConGetError(ret));
	CHECK_HANDLE(hRepr,"iotcon_representation_create");

	for (i = 0; i < LOOP_COUNT; i++)
	{
		ret = iotcon_representation_create(&hReprChld);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_representation_create", IotConGetError(ret),iotcon_representation_destroy(hRepr));
		if (hReprChld == NULL )
		{
			FPRINTF("[Line : %d][%s] Handle to representation object is returned NULL \n", __LINE__, API_NAMESPACE);
			iotcon_representation_destroy(hRepr);
			return 1;
		}

		ret = iotcon_representation_add_child(hRepr, hReprChld);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_representation_add_child", IotConGetError(ret), iotcon_representation_destroy(hReprChld));

		iotcon_representation_destroy(hReprChld);
		hReprChld = NULL;
	}

	for (i = 0; i < LOOP_COUNT; i++)
	{
		ret = iotcon_representation_get_nth_child(hRepr, i, &hReprChld);
		PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, ret, "iotcon_representation_get_nth_child", IotConGetError(ret), iotcon_representation_destroy(hRepr));
	}

	iotcon_representation_destroy(hRepr);
	return 0;
}

/** @} */
/** @} */
