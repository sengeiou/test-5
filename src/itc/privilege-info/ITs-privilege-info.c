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
#include "ITs-privilege-info-common.h"

/** @addtogroup itc-privilege-info
*  @ingroup itc
*  @{
*/
//& set: PrivilegeInfo

const static char *pszApiVersion  = "2.3";
const static char *pszPrivilege = "http://tizen.org/privilege/account.read";
const static char *pszMediaPrivilege = "http://tizen.org/privilege/mediastorage";
static char arrPkgTypes[][100] = {"PRVINFO_PACKAGE_TYPE_NATIVE", "PRVINFO_PACKAGE_TYPE_WEB"};
#define PRIVACY_FEATURE "http://tizen.org/feature/security.privacy_privilege"

void ITs_privilege_info_startup(void)
{
	g_bIsPrivilegeInfoInitialized = true;
	g_bIsPrivilegePrivacyFeature = true;
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
        if ( !TCTCheckSystemInfoFeatureSupported(PRIVACY_FEATURE, API_NAMESPACE))
        {
             g_bIsPrivilegePrivacyFeature = false;
        }
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Privilege_Info_p\\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

void ITs_privilege_info_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Privilege_Info_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}


/** @addtogroup itc-privilege-info-testcases
*  @brief 		Integration testcases for module privilege-info
*  @ingroup 	itc-privilege-info
*  @{
*/

//& purpose: Gets the discription of given privilege
//& type: auto
/**
* @testcase 			ITc_privilege_info_get_description_p
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen			2.3
* @description			Gets the discription of given privilege
* @scenario				startup function
* @apicovered			privilege_info_get_description
* @passcase				When privilege_info_get_description api return 0
* @failcase				If privilege_info_get_description api returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_privilege_info_get_description_p(void)
{
	START_TEST;
	char* pszDescription = NULL; 
	int nRetVal = privilege_info_get_description(pszApiVersion, pszPrivilege, &pszDescription);//target api
	PRINT_RESULT_CLEANUP(PRVINFO_ERROR_NONE, nRetVal, "privilege_info_get_description", PrivilegeinfoGetError(nRetVal),FREE_MEMORY(pszDescription));
	FREE_MEMORY(pszDescription);
	return 0;
}

//& purpose: Get the discription of given privilege 
//& type: auto
/**
* @testcase 			ITc_privilege_info_get_description_by_pkgtype_p
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen			2.3
* @description			Get the discription of given privilege 
* @scenario				NA
* @apicovered			get_description_by_pkgtype
* @passcase				if get_description_by_pkgtype return 0
* @failcase				if get_description_by_pkgtype return non zero
* @precondition			NA
* @postcondition		NA
*/
int ITc_privilege_info_get_description_by_pkgtype_p(void)
{
	START_TEST;
	int nEnumSize = 2;
	char* pszDescription = NULL; 
	int nRetVal = 0;
	char *pPkgType = NULL;
	int i = 0;
	for(i = 0; i<nEnumSize ; i++)
	{
		pPkgType = arrPkgTypes[i];
		nRetVal = privilege_info_get_description_by_pkgtype(pPkgType,pszApiVersion,pszPrivilege,&pszDescription);// Target APIs
		PRINT_RESULT_CLEANUP(PRVINFO_ERROR_NONE, nRetVal, "privilege_info_get_description_by_pkgtype", PrivilegeinfoGetError(nRetVal),FREE_MEMORY(pszDescription));
		FREE_MEMORY(pszDescription);
	}
	return 0;
}

//& purpose: Gets the display name of given privilege
//& type: auto
/**
* @testcase 			ITc_privilege_info_get_display_name_p
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen			2.3
* @description			Gets the display name of given privilege
* @scenario				startup function
* @apicovered			privilege_info_get_display_name
* @passcase				When privilege_info_get_display_name api return 0
* @failcase				If privilege_info_get_display_name api returns non zero value
* @precondition			NA
* @postcondition		NA.
*/
int ITc_privilege_info_get_display_name_p(void)
{
	START_TEST;
	char* pszDisplayName = NULL;
	int nRetVal = privilege_info_get_display_name(pszApiVersion, pszPrivilege, &pszDisplayName);//target api
	PRINT_RESULT_CLEANUP(PRVINFO_ERROR_NONE, nRetVal, "privilege_info_get_display_name", PrivilegeinfoGetError(nRetVal),FREE_MEMORY(pszDisplayName));
	FREE_MEMORY(pszDisplayName);
	return 0;
}

//& purpose: Gets the display name of the given privilege.
//& type: auto
/**
* @testcase 			ITc_privilege_info_get_display_name_by_pkgtype_p
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen			2.3
* @description			Gets the display name of the given privilege.
* @scenario				NA
* @apicovered			get_display_name
* @passcase				if get_display_name return 0
* @failcase				if get_display_name return non zero
* @precondition			NA
* @postcondition		NA
*/
int ITc_privilege_info_get_display_name_by_pkgtype_p(void)
{
	START_TEST;
	int nEnumSize = 2;
	int i = 0;
	char* pszDisplayName = NULL;
	char *pPkgType = NULL;
	int nRetVal = 0;
	for(i = 0; i<nEnumSize ; i++)
	{
		pPkgType = arrPkgTypes[i];
		nRetVal = privilege_info_get_display_name_by_pkgtype(pPkgType,pszApiVersion,pszPrivilege,&pszDisplayName);// Target APIs
		PRINT_RESULT_CLEANUP(PRVINFO_ERROR_NONE, nRetVal, "privilege_info_get_display_name_by_pkgtype", PrivilegeinfoGetError(nRetVal),FREE_MEMORY(pszDisplayName));
		FREE_MEMORY(pszDisplayName);
	}
	return 0;
}

//& purpose:  Gets the display name of the privacy group in which the given privilege is included. 
//& type: auto
/**
* @testcase				ITc_privilege_info_get_privacy_display_name_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Gets the display name of the privacy group in which the given privilege is included. 
* @apicovered			privilege_info_get_privacy_display_name
* @passcase				When  privilege_info_get_privacy_display_name API returns 0
* @failcase				If  privilege_info_get_privacy_display_name returns non zero value
* @precondition			Parameter list should have been allocated and buffer parameter should have been set
* @postcondition		NA
*/
int ITc_privilege_info_get_privacy_display_name_p(void)
{
	START_TEST;
	
	char *pPrivacy_name = NULL;
	
	int nRet =  privilege_info_get_privacy_display_name(pszPrivilege, &pPrivacy_name);
        if(!g_bIsPrivilegePrivacyFeature)
        {
           PRINT_RESULT(PRVINFO_ERROR_NOT_SUPPORTED, nRet, " privilege_info_get_privacy_display_name", PrivilegeinfoGetError(nRet));
           return 0;
        }

        PRINT_RESULT(PRVINFO_ERROR_NONE, nRet, " privilege_info_get_privacy_display_name", PrivilegeinfoGetError(nRet));

	if(pPrivacy_name == NULL)
	{
		FPRINTF("[Line : %d][%s] display name of the privacy group is not set\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	FREE_MEMORY(pPrivacy_name);

	return 0;
}

//& purpose:  Gets privilege info list with valid locale and privilege names and frees it.
//& type: auto
/**
* @testcase				ITc_privilege_info_get_free_privilege_info_list_p
* @since				5.5
* @author				SRID(priya.kohli)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @scenario				Gets privilege info list with valid locale and privilege names and frees it.
* @apicovered			privilege_info_get_privilege_info_list, privilege_info_free_privilege_info_list
* @passcase				When privilege_info_get_privilege_info_list & privilege_info_free_privilege_info_list api returns 0
* @failcase				If privilege_info_get_privilege_info_list or privilege_info_free_privilege_info_list api returns non zero value
* @precondition			Parameter list should have been allocated
* @postcondition		Free allocated Parameter list
*/
int ITc_privilege_info_get_free_privilege_info_list_p(void)
{
	START_TEST;

	int nRet = -1;
	int nResult = -1;
	GList* privilege_name_list = NULL;
	GList* privilege_info_list = NULL;
	const char* pszLocale = "ko_KR.UTF8";

	privilege_name_list = g_list_append(privilege_name_list, pszPrivilege);
	privilege_name_list = g_list_append(privilege_name_list, pszMediaPrivilege);

	nRet = privilege_info_get_privilege_info_list(pszLocale, privilege_name_list, &privilege_info_list, &nResult);
	PRINT_RESULT_CLEANUP(PRVINFO_ERROR_NONE, nRet, "privilege_info_get_privilege_info_list", PrivilegeinfoGetError(nRet), g_list_free(privilege_name_list));

	CHECK_HANDLE(privilege_info_list, " privilege_info_get_privilege_info_list");
	PRINT_RESULT_CLEANUP(PRIVILEGE_CONSUMER_RETURN_CODE_SUCCESS, nResult, "privilege_info_get_privilege_info_list", PrivilegeinfoGetError(nRet), g_list_free(privilege_name_list); privilege_info_free_privilege_info_list(privilege_info_list));

	g_list_free(privilege_name_list);

	nRet = privilege_info_free_privilege_info_list(privilege_info_list);
	PRINT_RESULT(PRVINFO_ERROR_NONE, nRet, "privilege_info_free_privilege_info_list", PrivilegeinfoGetError(nRet));

	return 0;
}

/** @} */
/** @} */
