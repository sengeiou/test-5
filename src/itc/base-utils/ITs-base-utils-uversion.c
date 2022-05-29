

#include "ITs-base-utils-common.h"


static const i18n_uversion_info version_info_1 = {
	57, 1, 0, 0
};

static const i18n_uversion_info version_info_2 = {
	234, 55, 12, 56
};


static const char *version_info_1_string = "57.1";
static const char *version_info_2_string = "234.55.12.56";



/**
 * @function        ITs_base_utils_uversion_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */

void ITs_base_utils_uversion_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		int nRet = remove(ERR_LOG);
		PRINT_RESULT_NORETURN(0, nRet, "ITs_base_utils_uversion_startup -remove", "Remove failed for ERR_LOG");
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_base_utils_uversion\\n", __LINE__, API_NAMESPACE);
#endif
	g_bBaseUtilsInitFlag = true;
	return;
}


/**
 * @function        ITs_base_utils_uversion_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */

void ITs_base_utils_uversion_cleanup(void)
{

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_base_utils_uversion\\n", __LINE__, API_NAMESPACE);
#endif
	g_bBaseUtilsInitFlag = false;
	return;

}


//& type: auto
//& purpose: Check whether the result of i18n_uversion_get_version will be equal to currently used ICU version.
/**
* @testcase		ITc_base_utils_i18n_uversion_get_version_p
* @since_tizen 		3.0
* @author            	SRID(maneesha.k)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @scenario		Calls i18n_uversion_get_version to check whether the result will be equal to
*	 	        currently used ICU version.
* @apitarget		i18n_uversion_get_version
* @apicovered		i18n_uversion_get_version
* @passcase		When i18n_uversion_get_version is successful
* @failcase		If target i18n_uversion_get_version fails or any precondition and postcondition api fails.
* @precondition			NA
* @postcondition		NA
*/


int ITc_base_utils_i18n_uversion_get_version_p(void)
{
	START_TEST;

	i18n_uversion_info uDestinationString;

	int nRetVal = i18n_uversion_get_version(uDestinationString);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_uversion_get_version", BaseUtilsGetError(nRetVal));

	return 0;
}


//& type: auto
//& purpose: Check whether the array with ICU version informations will be formatted properly.
/**
* @testcase		ITc_base_utils_i18n_uversion_to_string_p
* @since_tizen 		3.0
* @author            	SRID(maneesha.k)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @scenario		Calls i18n_uversion_to_string to check whether the array with ICU version
*		        informations will be formatted properly.
* @apitarget		i18n_uversion_to_string
* @apicovered		i18n_uversion_to_string
* @passcase		When i18n_uversion_to_string is successful
* @failcase		If target i18n_uversion_to_string fails or any precondition and postcondition api fails
* @precondition			NA
* @postcondition		NA
*/



int ITc_base_utils_i18n_uversion_to_string_p(void)
{
	START_TEST;

	char uDestinationString[I18N_UVERSION_MAX_VERSION_STRING_LENGTH];

	int nRetVal = i18n_uversion_to_string(version_info_1, uDestinationString);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_uversion_to_string", BaseUtilsGetError(nRetVal));

	if(strlen(version_info_1_string) != strlen(uDestinationString))
	{
		FPRINTF("\\n[Line : %d][%s]  Version Information 1 Length = %d, does not match the Returned Version Info Length = %d \n", __LINE__, API_NAMESPACE, strlen(version_info_1_string), strlen(uDestinationString));

		return 1;
	}

	if(memcmp(uDestinationString, version_info_1_string, sizeof(char) * strlen(uDestinationString)) != 0)
	{
		FPRINTF("\\n[Line : %d][%s]  Version Information 1 text = %s, does not match the Returned Version Info text = %s \n", __LINE__, API_NAMESPACE, version_info_1_string, uDestinationString);

		return 1;

	}

	nRetVal = i18n_uversion_to_string(version_info_2, uDestinationString);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_uversion_to_string", BaseUtilsGetError(nRetVal));

	if(strlen(version_info_2_string) != strlen(uDestinationString))
	{
		FPRINTF("\\n[Line : %d][%s] Version Information 2 Length = %d, does not match the Returned Version Info Length = %d \n", __LINE__, API_NAMESPACE, strlen(version_info_2_string), strlen(uDestinationString));

		return 1;
	}

	if(memcmp(uDestinationString, version_info_2_string, sizeof(char) * strlen(uDestinationString)) != 0)
	{
		FPRINTF("\\n[Line : %d][%s] Version Information 2 text = %s, does not match the Returned Version Info text = %s \n", __LINE__, API_NAMESPACE, version_info_2_string, uDestinationString);

		return 1;

	}

	return 0;
}


//& type: auto
//& purpose: Check whether the string with dotted-decimal version information will be parsed properly.
/**
* @testcase		ITc_base_utils_i18n_uversion_from_string_p
* @since_tizen 		3.0
* @author            	SRID(maneesha.k)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @scenario		Calls i18n_uversion_from_string to check whether the string with dotted-decimal
*              		version information will be parsed properly.
* @apitarget		i18n_uversion_from_string
* @apicovered		i18n_uversion_from_string
* @passcase		When i18n_uversion_from_string is successful
* @failcase		If target i18n_uversion_from_string fails or any precondition and postcondition api fails
* @precondition			NA
* @postcondition		NA
*/




int ITc_base_utils_i18n_uversion_from_string_p(void)
{
	START_TEST;

	i18n_uversion_info uDestinationString;

	int nRetVal = i18n_uversion_from_string(version_info_1_string, uDestinationString);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_uversion_from_string", BaseUtilsGetError(nRetVal));

	if(memcmp(uDestinationString, version_info_1, sizeof(uDestinationString)) != 0)
	{
		FPRINTF("\\n[Line : %d][%s] Version Information 1 text = %s, does not match the Returned Version Info text = %s \n", __LINE__, API_NAMESPACE, version_info_1, uDestinationString);
		return 1;

	}
	nRetVal = i18n_uversion_from_string(version_info_2_string, uDestinationString);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_uversion_from_string", BaseUtilsGetError(nRetVal));
	if(memcmp(uDestinationString, version_info_2, sizeof(uDestinationString)) != 0)
	{
		FPRINTF("\\n[Line : %d][%s] Version Information 2 text = %s, does not match the Returned Version Info text = %s \n", __LINE__, API_NAMESPACE, version_info_2, uDestinationString);
		return 1;

	}
	return 0;
}


//& type: auto
//& purpose: Check whether the Unicode string with dotted-decimal version information will be parsed properly.
/**
* @testcase		ITc_base_utils_i18n_uversion_from_ustring_p
* @since_tizen 		3.0
* @author            	SRID(maneesha.k)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @scenario		Calls i18n_uversion_from_ustring to check whether the Unicode string with
*             		dotted-decimal version information will be parsed properly.
* @apitarget		i18n_uversion_from_ustring
* @apicovered		i18n_uversion_from_ustring
* @passcase		When i18n_uversion_from_ustring is successful
* @failcase		If target i18n_uversion_from_ustring fails or any precondition and postcondition api fails
* @precondition			NA
* @postcondition		NA
*/




int ITc_base_utils_i18n_uversion_from_ustring_p(void)
{
	START_TEST;

	i18n_uversion_info uDestinationString;
	i18n_uchar uVersionString[I18N_UVERSION_MAX_VERSION_STRING_LENGTH];

	i18n_uchar *pRet = i18n_ustring_copy_ua(uVersionString, version_info_1_string);
	if ( pRet == NULL || i18n_ustring_get_length(uVersionString) <= 0)
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRetVal = i18n_uversion_from_ustring(uVersionString, uDestinationString);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_uversion_from_ustring", BaseUtilsGetError(nRetVal));

	if(memcmp(uDestinationString, version_info_1, sizeof(uDestinationString)) != 0)
	{
		FPRINTF("\\n[Line : %d][%s] Version Information 1 text, does not match the Returned Version Info text\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	pRet = i18n_ustring_copy_ua(uVersionString, version_info_2_string);
	if ( pRet == NULL || i18n_ustring_get_length(uVersionString) <= 0)
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = i18n_uversion_from_ustring(uVersionString, uDestinationString);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_uversion_from_ustring", BaseUtilsGetError(nRetVal));

	if(memcmp(uDestinationString, version_info_2, sizeof(uDestinationString)) != 0)
	{
		FPRINTF("\\n[Line : %d][%s] Version Information 2 text = %s, does not match the Returned Version Info text = %s \n", __LINE__, API_NAMESPACE, version_info_2_string, uDestinationString);
		return 1;
	}
	return 0;
}
