//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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
#include "ITs-application-common.h"
#include <app_control_uri.h>

static app_control_uri_h g_hUri;
static app_control_uri_builder_h g_hBuilder;
int g_CallbackQueryHit = false;
int nTimeoutId = 0;
/**
 * @function            Itc_application_app_control_uri_startup
 * @description         Called before some test
 * @parameter           NA
 * @return              NA
 */
void ITc_application_app_control_uri_startup(void)
{
	g_hUri = NULL;
	g_hBuilder = NULL;
	int nRet = app_control_uri_builder_create(&g_hBuilder);
	if (nRet != APP_CONTROL_URI_ERROR_NONE) {
                FPRINTF("[Line : %d][%s] Failed in uri builder creation nRet = %d\\n", __LINE__, API_NAMESPACE, nRet);
				return;
	}
	if(g_hBuilder == NULL){
		FPRINTF("[Line : %d][%s] failed:g_hBuilder returned is NULL  %d\\n", __LINE__, API_NAMESPACE);
	}

}
/**
 * @function            Itc_application_app_control_uri_cleanup
 * @description         Called before some test
 * @parameter           NA
 * @return              NA
 */
void Itc_application_app_control_uri_cleanup(void)
{
	int nRet = 0;
	if(g_hBuilder ){
		nRet = app_control_uri_builder_destroy(g_hBuilder);
		PRINT_RESULT_NORETURN(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_destroy", AppControlUriGetError(nRet));
		g_hBuilder = NULL;
	}

	if (g_hUri) {
		nRet = app_control_uri_destroy(g_hUri);
		PRINT_RESULT_NORETURN(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_destroy", AppControlUriGetError(nRet));
		g_hUri = NULL;
	}
}
/**
 * @function            QueryCallback
 * @description         Called when app_control_uri_query_foreach callback is invoked.
 * @parameter           const char *key, const char *val, void *user_data
 * @return              NA
 */
void QueryCallback(const char *key, const char *val, void *user_data)
{
	char **queryVal = user_data;
	*queryVal = strdup(val);

	g_CallbackQueryHit = true;

	return;
}

//& type: auto
//& purpose: Create and destroy uri handle
/**
* @testcase 			ITc_application_app_control_uri_create_destroy_p
* @since_tizen			5.5
* @author				SRID(bipin.k)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Creates and destroys  the uri handle
* @scenario			Creates  and destroys the uri handle\n
* @apicovered			app_control_uri_create ,app_control_uri_destroy
* @passcase				app_control_uri_create,app_control_uri_destroy are successfull.
* @failcase				If any of the target api fails.
* @precondition			None
* @postcondition		None
*/

int ITc_application_app_control_uri_create_destroy_p(void)
{
	START_TEST;
	const char encUri[] = "https:%2F%2Fjohn.doe%40www.example.com%3A123%2Fforum%2Fquestions%2F?tag=networking&order=newest#top";
	app_control_uri_h hUri = NULL;
	int nRet = APP_CONTROL_URI_ERROR_NONE;

	nRet = app_control_uri_create(encUri, &hUri);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_create", AppControlUriGetError(nRet));
	CHECK_HANDLE(hUri,"app_control_uri_create");

	nRet = app_control_uri_destroy(hUri);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_destroy", AppControlUriGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: creates and destroys  uri builder handle
/**
* @testcase 			ITc_application_app_control_uri_builder_create_destroy_p
* @since_tizen			5.5
* @author				SRID(bipin.k)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Creates the uri builder handle.
* @scenario			Creates the uri builder handle.
* @apicovered			app_control_uri_builder_create ,app_control_uri_builder_destroy
* @passcase				app_control_uri_builder_create,app_control_uri_builder_destroy are succesfull.
* @failcase				If any of the target api fails.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_uri_builder_create_destroy_p(void)
{
	START_TEST;
	app_control_uri_builder_h  hTestBuilder = NULL;
	int nRet = APP_CONTROL_URI_ERROR_NONE;

	nRet = app_control_uri_builder_create(&hTestBuilder);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_create", AppControlUriGetError(nRet));
	CHECK_HANDLE(hTestBuilder,"app_control_uri_builder_create");

	nRet = app_control_uri_builder_destroy(hTestBuilder);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_destroy", AppControlUriGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: add and get uri path
/**
* @testcase 			ITc_application_app_control_uri_add_get_path_p
* @since_tizen			5.5
* @author				SRID(bipin.k)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Adds the path to uri builder handle.
* @scenario			Adds the path data to uri builder handle.
* @apicovered			app_control_uri_builder_add_path
* @passcase				when all the precondition APIs and target api is successfull.
* @failcase				If any of the target api fails.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_uri_add_get_path_p(void)
{
	START_TEST;
	int nRet = APP_CONTROL_URI_ERROR_NONE;
	const char *path = "/questions/";
	const char *getPath = NULL;

	nRet = app_control_uri_builder_add_path(g_hBuilder, path);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_path", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_build(g_hBuilder, &g_hUri);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_build", AppControlUriGetError(nRet));
	CHECK_HANDLE(g_hUri,"app_control_uri_builder_build");

	nRet = app_control_uri_get_path(g_hUri, &getPath);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_get_path", AppControlUriGetError(nRet));

	if(strcmp(path, getPath))
	{
		FPRINTF("[Line : %d][%s] app control uri add path and  get path incorrect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}


	return 0;
}
//& type: auto
//& purpose: uri builder is built
/**
* @testcase 			ITc_application_app_control_uri_builder_build_p
* @since_tizen			5.5
* @author				SRID(bipin.k)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Creates a uri builder handle.
* @scenario			Creates a uri builder handle with the attributes,app_control_uri_builder_build.
* @apicovered			app_control_uri_builder_set_scheme,app_control_uri_builder_set_authority,app_control_uri_builder_set_path
*								app_control_uri_builder_set_fragment,app_control_uri_builder_add_query.
* @passcase				when all the precondition APIs and target api is successfull.
* @failcase				If any of the target api fails.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_uri_builder_build_p(void)
{
	START_TEST;
	int nRet = APP_CONTROL_URI_ERROR_NONE;

	nRet = app_control_uri_builder_set_scheme(g_hBuilder, "https");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_scheme", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_authority(g_hBuilder,
        "//john.doe@www.example.com:123");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_authority", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_path(g_hBuilder, "/forum/questions/");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_path", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_fragment(g_hBuilder, "top");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_fragment", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "tag", "networking");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "order", "newest");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));


	nRet =  app_control_uri_builder_build(g_hBuilder, &g_hUri);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_build", AppControlUriGetError(nRet));
	CHECK_HANDLE(g_hUri,"app_control_uri_builder_build");

	return 0;
}
//& type: auto
//& purpose: encode uri handle to string.
/**
* @testcase 			ITc_application_app_control_uri_encode_p
* @since_tizen			5.5
* @author				SRID(bipin.k)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Encodes the URI handle to string.
* @scenario			Encodes the URI handle to string by using uri builder.
* @apicovered			app_control_uri_encode,app_control_uri_builder_set_scheme,app_control_uri_builder_set_authority,app_control_uri_builder_set_path
*								app_control_uri_builder_set_fragment,app_control_uri_builder_add_query,app_control_uri_builder_build.
* @passcase				when all the precondition APIs and target api is successfull.
* @failcase				If any of the target api fails.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_uri_encode_p(void)
{
	START_TEST;
	int nRet = APP_CONTROL_URI_ERROR_NONE;
	char *encodedAppControlUri = NULL;

	const char ENCODED_URI1[] = "https:%2F%2Fjohn.doe%40www.example.com%3A123%2Fforum%2Fquestions%2F?tag=networking&order=newest#top";

	nRet = app_control_uri_builder_set_scheme(g_hBuilder, "https");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_scheme", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_authority(g_hBuilder,
        "//john.doe@www.example.com:123");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_authority", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_path(g_hBuilder, "/forum/questions/");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_path", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_fragment(g_hBuilder, "top");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_fragment", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "tag", "networking");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "order", "newest");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_build(g_hBuilder, &g_hUri);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_build", AppControlUriGetError(nRet));
	CHECK_HANDLE(g_hUri,"app_control_uri_builder_build");

	nRet = app_control_uri_encode(g_hUri, &encodedAppControlUri);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_encode", AppControlUriGetError(nRet));


	if(strcmp(encodedAppControlUri, ENCODED_URI1))
	{
		FPRINTF("[Line : %d][%s] encoded uri returned is not correct \\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(encodedAppControlUri);
		return 1;
	}

	FREE_MEMORY(encodedAppControlUri);

	return 0;
}
//& type: auto
//& purpose: set and  get scheme from uri handle.
/**
* @testcase 			ITc_application_app_control_uri_set_get_scheme_p
* @since_tizen			5.5
* @author				SRID(bipin.k)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets the scheme from uri builder handle.
* @scenario			Sets and Gets the scheme data from uri builder handle.
* @apicovered			app_control_uri_get_scheme,app_control_uri_builder_set_scheme,app_control_uri_builder_set_authority,app_control_uri_builder_set_path
*								app_control_uri_builder_set_fragment,app_control_uri_builder_add_query,app_control_uri_builder_build.
* @passcase				when all the precondition APIs and target api is successfull.
* @failcase				If any of the target api fails.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_uri_set_get_scheme_p(void)
{
	START_TEST;
	int nRet = APP_CONTROL_URI_ERROR_NONE;
	const char *getScheme = NULL;

	nRet = app_control_uri_builder_set_scheme(g_hBuilder, "https");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_scheme", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_authority(g_hBuilder,
        "//john.doe@www.example.com:123");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_authority", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_path(g_hBuilder, "/forum/questions/");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_path", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_fragment(g_hBuilder, "top");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_fragment", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "tag", "networking");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "order", "newest");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_build(g_hBuilder, &g_hUri);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_build", AppControlUriGetError(nRet));
	CHECK_HANDLE(g_hUri,"app_control_uri_builder_build");

	nRet = app_control_uri_get_scheme(g_hUri, &getScheme);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_get_scheme", AppControlUriGetError(nRet));

	if(strcmp("https", getScheme))
	{
		FPRINTF("[Line : %d][%s] encoded uri returned is not correct \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: set and get authority from uri handle.
/**
* @testcase 			ITc_application_app_control_uri_set_get_authority_p
* @since_tizen			5.5
* @author				SRID(bipin.k)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets the authority from uri builder handle.
* @scenario			Sets and Gets the authority data from uri builder handle.
* @apicovered			app_control_uri_get_authority,app_control_uri_builder_set_scheme,app_control_uri_builder_set_authority,app_control_uri_builder_set_path
*								app_control_uri_builder_set_fragment,app_control_uri_builder_add_query,app_control_uri_builder_build.
* @passcase				when all the precondition APIs and target api is successfull.
* @failcase				If any of the target api fails.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_uri_set_get_authority_p(void)
{
	START_TEST;
	int nRet = APP_CONTROL_URI_ERROR_NONE;
	const char *getAuthority = NULL;

	nRet = app_control_uri_builder_set_scheme(g_hBuilder, "https");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_scheme", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_authority(g_hBuilder,
        "//john.doe@www.example.com:123");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_authority", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_path(g_hBuilder, "/forum/questions/");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_path", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_fragment(g_hBuilder, "top");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_fragment", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "tag", "networking");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "order", "newest");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_build(g_hBuilder, &g_hUri);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_build", AppControlUriGetError(nRet));
	CHECK_HANDLE(g_hUri,"app_control_uri_builder_build");

	nRet = app_control_uri_get_authority(g_hUri, &getAuthority);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_get_authority", AppControlUriGetError(nRet));

	if(strcmp("//john.doe@www.example.com:123", getAuthority))
	{
		FPRINTF("[Line : %d][%s] get authority incorrect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}
//& type: auto
//& purpose: set and get path from uri handle.
/**
* @testcase 			Itc_application_app_control_uri_set_get_path_p
* @since_tizen			5.5
* @author				SRID(bipin.k)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets the path from uri builder handle.
* @scenario			Sets and Gets the path data from uri builder handle.
* @apicovered			app_control_uri_get_path,app_control_uri_builder_set_scheme,app_control_uri_builder_set_authority,app_control_uri_builder_set_path
*								app_control_uri_builder_set_fragment,app_control_uri_builder_add_query,app_control_uri_builder_build.
* @passcase				when all the precondition APIs and target api is successfull.
* @failcase				If any of the target api fails.
* @precondition			None
* @postcondition		None
*/
int Itc_application_app_control_uri_set_get_path_p(void)
{
	START_TEST;
	int nRet = APP_CONTROL_URI_ERROR_NONE;
	const char *getPath = NULL;

	nRet = app_control_uri_builder_set_scheme(g_hBuilder, "https");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_scheme", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_authority(g_hBuilder,
        "//john.doe@www.example.com:123");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_authority", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_path(g_hBuilder, "/forum/questions/");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_path", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_fragment(g_hBuilder, "top");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_fragment", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "tag", "networking");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "order", "newest");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_build(g_hBuilder, &g_hUri);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_build", AppControlUriGetError(nRet));
	CHECK_HANDLE(g_hUri,"app_control_uri_builder_build");

	nRet = app_control_uri_get_path(g_hUri, &getPath);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_get_path", AppControlUriGetError(nRet));

	if(strcmp("/forum/questions/", getPath))
	{
		FPRINTF("[Line : %d][%s] app control uri get path incorrect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: set and get fragment from uri builder handle.
/**
* @testcase 			ITc_application_app_control_uri_set_get_fragment_p
* @since_tizen			5.5
* @author				SRID(bipin.k)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets the fragment from uri builder handle.
* @scenario			Sets and Gets the fragment data from uri builder handle.
* @apicovered			app_control_uri_get_fragment,app_control_uri_builder_set_scheme,app_control_uri_builder_set_authority,app_control_uri_builder_set_path
*								app_control_uri_builder_set_fragment,app_control_uri_builder_add_query,app_control_uri_builder_build.
* @passcase				when all the precondition APIs and target api is successfull.
* @failcase				If any of the target api fails.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_uri_set_get_fragment_p(void)
{
	START_TEST;
	int nRet = APP_CONTROL_URI_ERROR_NONE;
	const char *getFragment = NULL;

	nRet = app_control_uri_builder_set_scheme(g_hBuilder, "https");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_scheme", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_authority(g_hBuilder,
        "//john.doe@www.example.com:123");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_authority", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_path(g_hBuilder, "/forum/questions/");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_path", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_fragment(g_hBuilder, "top");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_fragment", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "tag", "networking");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "order", "newest");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_build(g_hBuilder, &g_hUri);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_build", AppControlUriGetError(nRet));
	CHECK_HANDLE(g_hUri,"app_control_uri_builder_build");

	nRet = app_control_uri_get_fragment(g_hUri, &getFragment);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_get_fragment", AppControlUriGetError(nRet));

	if(strcmp("top", getFragment))
	{
		FPRINTF("[Line : %d][%s] app control uri get fragment :incorrect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}
//& type: auto
//& purpose: get host from uri builder handle.
/**
* @testcase 			ITc_application_app_control_uri_get_host_p
* @since_tizen			5.5
* @author				SRID(bipin.k)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Gets the host from uri builder handle.
* @scenario			Gets the host data from uri builder handle.
* @apicovered			app_control_uri_get_host,app_control_uri_builder_set_scheme,app_control_uri_builder_set_authority,app_control_uri_builder_set_path
*								app_control_uri_builder_set_fragment,app_control_uri_builder_add_query,app_control_uri_builder_build.
* @passcase				when all the precondition APIs and target api is successfull.
* @failcase				If any of the target api fails.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_uri_get_host_p(void)
{
	START_TEST;
	int nRet = APP_CONTROL_URI_ERROR_NONE;
	const char *getHost = NULL;

	nRet = app_control_uri_builder_set_scheme(g_hBuilder, "https");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_scheme", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_authority(g_hBuilder,
        "//john.doe@www.example.com:123");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_authority", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_path(g_hBuilder, "/forum/questions/");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_path", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_fragment(g_hBuilder, "top");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_fragment", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "tag", "networking");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "order", "newest");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_build(g_hBuilder, &g_hUri);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_build", AppControlUriGetError(nRet));
	CHECK_HANDLE(g_hUri,"app_control_uri_builder_build");

	nRet = app_control_uri_get_host(g_hUri, &getHost);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_get_host", AppControlUriGetError(nRet));

	if(strcmp("www.example.com", getHost))
	{
		FPRINTF("[Line : %d][%s] app control uri app control uri get host :incorrect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: get port from uri handle.
/**
* @testcase 			ITc_application_app_control_uri_get_port_p
* @since_tizen			5.5
* @author				SRID(bipin.k)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Gets the port from uri handle.
* @scenario			Gets the port data from uri handle.
* @apicovered			app_control_uri_get_port,app_control_uri_builder_set_scheme,app_control_uri_builder_set_authority,app_control_uri_builder_set_path
*								app_control_uri_builder_set_fragment,app_control_uri_builder_add_query,app_control_uri_builder_build.
* @passcase				when all the precondition APIs and target api is successfull.
* @failcase				If any of the target api fails.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_uri_get_port_p(void)
{
	START_TEST;
	int nRet = APP_CONTROL_URI_ERROR_NONE;
	const char *getPort = NULL;

	nRet = app_control_uri_builder_set_scheme(g_hBuilder, "https");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_scheme", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_authority(g_hBuilder,
        "//john.doe@www.example.com:123");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_authority", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_path(g_hBuilder, "/forum/questions/");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_path", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_fragment(g_hBuilder, "top");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_fragment", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "tag", "networking");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "order", "newest");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_build(g_hBuilder, &g_hUri);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_build", AppControlUriGetError(nRet));
	CHECK_HANDLE(g_hUri,"app_control_uri_builder_build");

	nRet = app_control_uri_get_port(g_hUri, &getPort);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_get_port", AppControlUriGetError(nRet));

	if(strcmp("123", getPort))
	{
		FPRINTF("[Line : %d][%s] app control uri app control uri get port :incorrect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}
//& type: auto
//& purpose: get user from uri handle.
/**
* @testcase 			ITc_application_app_control_uri_get_user_p
* @since_tizen			5.5
* @author				SRID(bipin.k)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Gets the user from uri handle.
* @scenario			Gets the user data from uri handle.
* @apicovered			app_control_uri_get_user,app_control_uri_builder_set_scheme,app_control_uri_builder_set_authority,app_control_uri_builder_set_path
*								app_control_uri_builder_set_fragment,app_control_uri_builder_add_query,app_control_uri_builder_build.
* @passcase				when all the precondition APIs and target api is successfull.
* @failcase				If any of the target api fails.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_uri_get_user_p(void)
{
	START_TEST;
	int nRet = APP_CONTROL_URI_ERROR_NONE;
	const char *getUser = NULL;

	nRet = app_control_uri_builder_set_scheme(g_hBuilder, "https");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_scheme", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_authority(g_hBuilder,
        "//john.doe@www.example.com:123");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_authority", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_path(g_hBuilder, "/forum/questions/");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_path", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_fragment(g_hBuilder, "top");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_fragment", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "tag", "networking");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "order", "newest");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_build(g_hBuilder, &g_hUri);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_build", AppControlUriGetError(nRet));
	CHECK_HANDLE(g_hUri,"app_control_uri_builder_build");

	nRet = app_control_uri_get_user(g_hUri, &getUser);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_get_user", AppControlUriGetError(nRet));

	if(strcmp("john.doe", getUser))
	{
		FPRINTF("[Line : %d][%s] app control uri app control uri get user:incorrect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose:get query from uri handle
/**
* @testcase 			ITc_application_app_control_uri_add_get_query_p
* @since_tizen			5.5
* @author				SRID(bipin.k)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Gets the query from uri handle.
* @scenario			Gets the query data from uri handle.
* @apicovered			app_control_uri_get_query,app_control_uri_builder_set_scheme,app_control_uri_builder_set_authority,app_control_uri_builder_set_path
*								app_control_uri_builder_set_fragment,app_control_uri_builder_add_query,app_control_uri_builder_build.
* @passcase				when all the precondition APIs and target api is successfull.
* @failcase				If any of the target api fails.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_uri_add_get_query_p(void)
{
	START_TEST;
	int nRet = APP_CONTROL_URI_ERROR_NONE;
	app_control_uri_query_h hQuery = NULL;

	nRet = app_control_uri_builder_set_scheme(g_hBuilder, "https");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_scheme", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_authority(g_hBuilder,
        "//john.doe@www.example.com:123");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_authority", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_path(g_hBuilder, "/forum/questions/");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_path", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_fragment(g_hBuilder, "top");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_fragment", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "tag", "networking");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "order", "newest");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_build(g_hBuilder, &g_hUri);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_build", AppControlUriGetError(nRet));
	CHECK_HANDLE(g_hUri,"app_control_uri_builder_build");

	nRet = app_control_uri_get_query(g_hUri, &hQuery);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_get_query", AppControlUriGetError(nRet));
	CHECK_HANDLE(hQuery,"app_control_uri_get_query");

	return 0;
}
//& type: auto
//& purpose: retrieve key-value pairs foreach query.
/**
* @testcase 			ITc_application_app_control_uri_query_foreach_p
* @since_tizen			5.5
* @author				SRID(bipin.k)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Retrieves the key-value pairs attributes in the query.
* @scenario			Retrieves the key-value pairs attributes in the query handle.
* @apicovered			app_control_uri_query_foreach,app_control_uri_builder_set_scheme,app_control_uri_builder_set_authority,app_control_uri_builder_set_path
*								app_control_uri_builder_set_fragment,app_control_uri_builder_add_query,app_control_uri_builder_build.
* @passcase				when all the precondition APIs and target api is successfull.
* @failcase				If any of the target api fails.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_uri_query_foreach_p(void)
{
	START_TEST;

	int nRet = APP_CONTROL_URI_ERROR_NONE;
	app_control_uri_query_h hQuery = NULL;
	char *getQueryVal = NULL;
	g_CallbackQueryHit = false;

	nRet = app_control_uri_builder_set_scheme(g_hBuilder, "https");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_scheme", AppControlUriGetError(nRet));

   	nRet = app_control_uri_builder_set_authority(g_hBuilder,
        "//john.doe@www.example.com:123");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_authority", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_path(g_hBuilder, "/forum/questions/");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_path", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_set_fragment(g_hBuilder, "top");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_set_fragment", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_add_query(g_hBuilder, "tag", "networking");
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlUriGetError(nRet));

	nRet = app_control_uri_builder_build(g_hBuilder, &g_hUri);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_builder_build", AppControlUriGetError(nRet));
	CHECK_HANDLE(g_hUri,"app_control_uri_builder_build");

	nRet = app_control_uri_get_query(g_hUri, &hQuery);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_get_query", AppControlUriGetError(nRet));
	CHECK_HANDLE(hQuery,"app_control_uri_get_query");

	nRet = app_control_uri_query_foreach(hQuery, QueryCallback, &getQueryVal);
	PRINT_RESULT(APP_CONTROL_URI_ERROR_NONE, nRet, "app_control_uri_query_foreach", AppControlUriGetError(nRet));


	if(false == g_CallbackQueryHit)
	{
		FPRINTF("[Line : %d][%s] app_control_uri_query_foreach Callback not invoked\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(getQueryVal);
		return 1;
	}

	if(strcmp("networking", getQueryVal))
	{
		FPRINTF("[Line : %d][%s] app control uri query for each :incorrect\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(getQueryVal);
		return 1;
	}

	FREE_MEMORY(getQueryVal);

	return 0;
}
