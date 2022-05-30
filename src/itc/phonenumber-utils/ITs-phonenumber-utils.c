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
#include "ITs-phonenumber-utils-common.h"

bool g_bPhoneIssupportedFeature = false;
bool g_bIsConnected = false;

phone_number_region_e g_nArrNumberRegions[] = {
	PHONE_NUMBER_REGION_ALAND_ISLANDS,
	PHONE_NUMBER_REGION_ALBANIA,
	PHONE_NUMBER_REGION_ALGERIA,
	PHONE_NUMBER_REGION_AMERICAN_SAMOA,
	PHONE_NUMBER_REGION_ANGOLA,
	PHONE_NUMBER_REGION_ANGUILLA,
	PHONE_NUMBER_REGION_ARGENTINA,
	PHONE_NUMBER_REGION_ARMENIA,
	PHONE_NUMBER_REGION_ASCENSION_ISLAND,
	PHONE_NUMBER_REGION_ATIGUA_AND_BARBUDA,
	PHONE_NUMBER_REGION_AUSTRIA,
	PHONE_NUMBER_REGION_BAHAMAS,
	PHONE_NUMBER_REGION_BARBADOS,
	PHONE_NUMBER_REGION_BELARUS,
	PHONE_NUMBER_REGION_BELGIUM,
	PHONE_NUMBER_REGION_BENIN,
	PHONE_NUMBER_REGION_BERMUDA,
	PHONE_NUMBER_REGION_BONAIRE_SINT_EUSTATIUS_AND_SABA,
	PHONE_NUMBER_REGION_BOTSWANA,
	PHONE_NUMBER_REGION_BRAZIL,
	PHONE_NUMBER_REGION_BULGARIA,
	PHONE_NUMBER_REGION_BURKINA_FASO,
	PHONE_NUMBER_REGION_BURUNDI,
	PHONE_NUMBER_REGION_CABO_VERDE,
	PHONE_NUMBER_REGION_CAMEROON,
	PHONE_NUMBER_REGION_CANADA,
	PHONE_NUMBER_REGION_CAYMAN_ISLAND,
	PHONE_NUMBER_REGION_CHILE,
	PHONE_NUMBER_REGION_CHINA,
	PHONE_NUMBER_REGION_COLOMBIA,
	PHONE_NUMBER_REGION_COMOROS,
	PHONE_NUMBER_REGION_CONGO,
	PHONE_NUMBER_REGION_COTE_D_IVOIRE,
	PHONE_NUMBER_REGION_CUBA,
	PHONE_NUMBER_REGION_CURACAO,
	PHONE_NUMBER_REGION_CZECH_REPUBLIC,
	PHONE_NUMBER_REGION_DEMOCRATIC_REPUBLIC_OF_THE_CONGO,
	PHONE_NUMBER_REGION_DOMINICA,
	PHONE_NUMBER_REGION_DOMINICAN_REPUBLIC,
	PHONE_NUMBER_REGION_EGYPT,
	PHONE_NUMBER_REGION_ESTONIA,
	PHONE_NUMBER_REGION_ETHIOPIA,
	PHONE_NUMBER_REGION_FINLAND,
	PHONE_NUMBER_REGION_FRANCE,
	PHONE_NUMBER_REGION_GABON,
	PHONE_NUMBER_REGION_GAMBIA,
	PHONE_NUMBER_REGION_GERMANY,
	PHONE_NUMBER_REGION_GHANA,
	PHONE_NUMBER_REGION_GREECE,
	PHONE_NUMBER_REGION_GREENLAND,
	PHONE_NUMBER_REGION_GRENADA,
	PHONE_NUMBER_REGION_GUAM,
	PHONE_NUMBER_REGION_GUERNSEY,
	PHONE_NUMBER_REGION_GUINEA,
	PHONE_NUMBER_REGION_GUINEA_BISSAU,
	PHONE_NUMBER_REGION_HUNGARY,
	PHONE_NUMBER_REGION_ICELAND,
	PHONE_NUMBER_REGION_INDIA,
	PHONE_NUMBER_REGION_INDONESIA,
	PHONE_NUMBER_REGION_IRELAND,
	PHONE_NUMBER_REGION_ISLAMIC_REPUBLIC_OF_IRAN,
	PHONE_NUMBER_REGION_ISLE_OF_MAN,
	PHONE_NUMBER_REGION_ITALY,
	PHONE_NUMBER_REGION_JAMAICA,
	PHONE_NUMBER_REGION_JAPAN,
	PHONE_NUMBER_REGION_JERSEY,
	PHONE_NUMBER_REGION_JORDAN,
	PHONE_NUMBER_REGION_KAZAKHSTAN,
	PHONE_NUMBER_REGION_KENYA,
	PHONE_NUMBER_REGION_KIRIBATI,
	PHONE_NUMBER_REGION_LATVIA,
	PHONE_NUMBER_REGION_LESOTHO,
	PHONE_NUMBER_REGION_LITHUANIA,
	PHONE_NUMBER_REGION_LUXEMBOURG,
	PHONE_NUMBER_REGION_MADAGASCAR,
	PHONE_NUMBER_REGION_MAURITANIA,
	PHONE_NUMBER_REGION_MAURITIUS,
	PHONE_NUMBER_REGION_MONTSERRAT,
	PHONE_NUMBER_REGION_MOROCCO,
	PHONE_NUMBER_REGION_MOZAMBIQUE,
	PHONE_NUMBER_REGION_NAMIBIA,
	PHONE_NUMBER_REGION_NETHERLANDS,
	PHONE_NUMBER_REGION_NIGERIA,
	PHONE_NUMBER_REGION_NORTHERN_MARIANA_ISLANDS,
	PHONE_NUMBER_REGION_NORWAY,
	PHONE_NUMBER_REGION_PERU,
	PHONE_NUMBER_REGION_POLAND,
	PHONE_NUMBER_REGION_PORTUGAL,
	PHONE_NUMBER_REGION_PUERTO_RICO,
	PHONE_NUMBER_REGION_REPUBLIC_OF_KOREA,
	PHONE_NUMBER_REGION_REPUBLIC_OF_MOLDOVA,
	PHONE_NUMBER_REGION_ROMANIA,
	PHONE_NUMBER_REGION_RUSSIAN_FEDERATION,
	PHONE_NUMBER_REGION_SAINT_HELENA,
	PHONE_NUMBER_REGION_SAINT_KITTS_AND_NEVIS,
	PHONE_NUMBER_REGION_SAINT_LUCIA,
	PHONE_NUMBER_REGION_SAINT_VINCENT_AND_THE_GRENADINES,
	PHONE_NUMBER_REGION_SAO_TOME_AND_PRINCIPE,
	PHONE_NUMBER_REGION_SAUDI_ARABIA,
	PHONE_NUMBER_REGION_SENEGAL,
	PHONE_NUMBER_REGION_SERBIA,
	PHONE_NUMBER_REGION_SIERRA_LEONE,
	PHONE_NUMBER_REGION_SINT_MAARTEN,
	PHONE_NUMBER_REGION_SLOVAKIA,
	PHONE_NUMBER_REGION_SOMALIA,
	PHONE_NUMBER_REGION_SOUTH_AFRICA,
	PHONE_NUMBER_REGION_SPAIN,
	PHONE_NUMBER_REGION_SRI_LANKA,
	PHONE_NUMBER_REGION_SUDAN,
	PHONE_NUMBER_REGION_SVALBARD_AND_JAN_MAYEN,
	PHONE_NUMBER_REGION_SWAZILAND,
	PHONE_NUMBER_REGION_SWEDEN,
	PHONE_NUMBER_REGION_SWITZERLAND,
	PHONE_NUMBER_REGION_TAIWAN_PROVINCE_OF_CHINA,
	PHONE_NUMBER_REGION_THAILAND,
	PHONE_NUMBER_REGION_THE_FORMER_YUGOSLAV_REPUBLIC_OF_MACEDONIA,
	PHONE_NUMBER_REGION_TOGO,
	PHONE_NUMBER_REGION_TRINIDAD_AND_TOBAGO,
	PHONE_NUMBER_REGION_TRISTAN_DA_CUNHA,
	PHONE_NUMBER_REGION_TUNISIA,
	PHONE_NUMBER_REGION_TURKEY,
	PHONE_NUMBER_REGION_TURKS_AND_CAICOS_ISLANDS,
	PHONE_NUMBER_REGION_UGANDA,
	PHONE_NUMBER_REGION_UNITED_KINGDOM,
	PHONE_NUMBER_REGION_UNITED_STATES_OF_AMERICA,
	PHONE_NUMBER_REGION_VENEZUELA,
	PHONE_NUMBER_REGION_VIET_NAM,
	PHONE_NUMBER_REGION_VIRGIN_ISLAND_BRITISH,
	PHONE_NUMBER_REGION_VIRGIN_ISLAND_US,
	PHONE_NUMBER_REGION_WESTERN_SAHARA,
	PHONE_NUMBER_REGION_ZAMBIA,
	PHONE_NUMBER_REGION_ZIMBABWE
};
int g_nRegionSize = sizeof(g_nArrNumberRegions)/sizeof(g_nArrNumberRegions[0]);

phone_number_lang_e g_nArrLanguages[] = {
	PHONE_NUMBER_LANG_AMHARIC,
	PHONE_NUMBER_LANG_ARABIC,
	PHONE_NUMBER_LANG_BELARUSIAN,
	PHONE_NUMBER_LANG_BULGARIAN,
	PHONE_NUMBER_LANG_CHINESE,
	PHONE_NUMBER_LANG_CHINESE_TRADITIONAL,
	PHONE_NUMBER_LANG_CZECH,
	PHONE_NUMBER_LANG_DUTCH,
	PHONE_NUMBER_LANG_ENGLISH,
	PHONE_NUMBER_LANG_FINNISH,
	PHONE_NUMBER_LANG_FRENCH,
	PHONE_NUMBER_LANG_GERMAN,
	PHONE_NUMBER_LANG_GREEK,
	PHONE_NUMBER_LANG_HUNGARIAN,
	PHONE_NUMBER_LANG_INDONESIAN,
	PHONE_NUMBER_LANG_ITALIAN,
	PHONE_NUMBER_LANG_JAPANESE,
	PHONE_NUMBER_LANG_KOREAN,
	PHONE_NUMBER_LANG_NORTHERN_SAMI,
	PHONE_NUMBER_LANG_PERSIAN,
	PHONE_NUMBER_LANG_POLISH,
	PHONE_NUMBER_LANG_PORTUGUESE,
	PHONE_NUMBER_LANG_ROMANIAN,
	PHONE_NUMBER_LANG_RUSSIAN,
	PHONE_NUMBER_LANG_SERBIAN,
	PHONE_NUMBER_LANG_SPANISH,
	PHONE_NUMBER_LANG_SWEDISH,
	PHONE_NUMBER_LANG_THAI,
	PHONE_NUMBER_LANG_TURKISH,
	PHONE_NUMBER_LANG_VIETNAMESE
};
int g_nLanguageSize = sizeof(g_nArrLanguages)/sizeof(g_nArrLanguages[0]);

/** @addtogroup itc-phonenumber-utils
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_phonenumber_utils_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_phonenumber_utils_startup(void)
{
	struct stat stBuff;
	g_bPhoneSupported = false;

	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	g_bPhoneSupported  = TCTCheckSystemInfoFeatureSupported(PHONE_FEATURE, API_NAMESPACE);
	int nRet = phone_number_connect();

	if ( nRet != PHONE_NUMBER_ERROR_NONE )
	{
		g_bIsConnected = false;
		FPRINTF("[Line : %d][%s] phone_number_connect fail in startup error returned : %s \\n", __LINE__, API_NAMESPACE , PhoneNumberUtilsGetError(nRet));
		return;
	}

	g_bIsConnected = true;
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT start-up: ITs_Phonenumber_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
 * @function 		ITs_phonenumber_utils_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_phonenumber_utils_cleanup(void)
{

	int nRet = phone_number_disconnect();
	if ( nRet != PHONE_NUMBER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] phone_number_disconnect fail in cleanup error returned : %s \\n", __LINE__, API_NAMESPACE , PhoneNumberUtilsGetError(nRet));
		return;
	}
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_Phonenumber_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

}

/** @addtogroup itc-phonenumber-utils-testcases
*  @brief 		Integration testcases for module phonenumber-utils
*  @ingroup 	itc-phonenumber-utils
*  @{
*/

//& type: auto
//& purpose: This function gets the formatted number
/**
 * @testcase 				ITc_phone_number_get_formatted_number_p
 * @since_tizen				2.4
 * @author					SRID(m.khalid)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				Gets the formatted number
 * @scenario				Gets the formatted number
 * @apicovered				phone_number_get_formatted_number
 * @passcase				if phone_number_get_formatted_number returns success
 * @failcase				if phone_number_get_formatted_number returns failure
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_phone_number_get_formatted_number_p(void)
{
	START_TEST;

	if(g_bIsConnected == false)
	{
		FPRINTF("[Line : %d][%s] phone_number_get_formatted_number failed ,g_bIsConnected is false\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int nRet = PHONE_NUMBER_ERROR_NONE;
	char *pFormattedNumber = NULL;
	int nIndex;
	for ( nIndex = 0; nIndex < g_nRegionSize; nIndex++ )
	{
		// Target API
		nRet = phone_number_get_formatted_number(PHONE_NUMBER, g_nArrNumberRegions[nIndex], &pFormattedNumber);
		if ( nRet != PHONE_NUMBER_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] phone_number_get_formatted_number failed for region = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, GetRegion(g_nArrNumberRegions[nIndex]), PhoneNumberUtilsGetError(nRet));
			return 1;
		}
		if ( strlen(pFormattedNumber) != 0 )
		{
			FPRINTF("[Line : %d][%s] phone_number_get_formatted_number returned formatted number = %s for region = %s\\n", __LINE__, API_NAMESPACE, pFormattedNumber, GetRegion(g_nArrNumberRegions[nIndex]));
			FREE_MEMORY(pFormattedNumber);
			pFormattedNumber = NULL;
		}
	}

	return 0;
}

//& type: auto
//& purpose: This function gets the location string from number, region and language
/**
 * @testcase 				ITc_phone_number_get_location_from_number_p
 * @since_tizen				2.4
 * @author					SRID(m.khalid)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				Gets the location string from number, region and language
 * @scenario				Gets the location string from number, region and language
 * @apicovered				phone_number_get_location_from_number
 * @passcase				if phone_number_get_location_from_number returns success
 * @failcase				if phone_number_get_location_from_number returns failure
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_phone_number_get_location_from_number_p(void)
{
	START_TEST;

	if(g_bIsConnected == false)
	{
		FPRINTF("[Line : %d][%s] phone_number_get_location_from_number failed ,g_bIsConnected is false\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int nRet = PHONE_NUMBER_ERROR_NONE;
	int nRegionIndex;
	char *pLocation = NULL;

	int nLanguageIndex;
	for ( nLanguageIndex = 0; nLanguageIndex < g_nLanguageSize; nLanguageIndex++ )
	{
		for ( nRegionIndex = 0; nRegionIndex < g_nRegionSize; nRegionIndex++ )
		{
			// Target API
			nRet = phone_number_get_location_from_number(PHONE_NUMBER, g_nArrNumberRegions[nRegionIndex], g_nArrLanguages[nLanguageIndex], &pLocation);
			if ( nRet != PHONE_NUMBER_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] phone_number_get_location_from_number failed for region = %s and language = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, GetRegion(g_nArrNumberRegions[nRegionIndex]), GetLanguage(g_nArrLanguages[nLanguageIndex]), PhoneNumberUtilsGetError(nRet));
				return 1;
			}
			if ( strlen(pLocation) != 0 )
			{
				FPRINTF("[Line : %d][%s] phone_number_get_location_from_number returns location = %s for region = %s and language = %s\\n", __LINE__, API_NAMESPACE, pLocation, GetRegion(g_nArrNumberRegions[nRegionIndex]), GetLanguage(g_nArrLanguages[nLanguageIndex]));
				FREE_MEMORY(pLocation);
				pLocation = NULL;
			}
		}
	}
	return 0;
}

//& type: auto
//& purpose: This function gets the normalized number
/**
 * @testcase                            ITc_phone_number_get_normalized_number_p
 * @since_tizen                         3.0
 * @author                              SRID(nibha.sharma)
 * @reviewer                            SRID(parshant.v)
 * @type                                auto
 * @description                         Gets the normalized number
 * @scenario                            Gets the normalized number
 * @apicovered                          phone_number_get_normalized_number
 * @passcase                            if phone_number_get_normalized_number returns success
 * @failcase                            if phone_number_get_normalized_number returns failure
 * @precondition                        NA
 * @postcondition                       NA
 */
int ITc_phone_number_get_normalized_number_p(void)
{
    START_TEST;

	if(g_bIsConnected == false)
	{
		FPRINTF("[Line : %d][%s] phone_number_get_normalized_number failed ,g_bIsConnected is false\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

    int nRet = PHONE_NUMBER_ERROR_NONE;
    char *pNormalizedNumber = NULL;

    nRet = phone_number_get_normalized_number(PHONE_NUMBER, &pNormalizedNumber);
    FREE_MEMORY(pNormalizedNumber);

    if(g_bPhoneSupported)
    {
       PRINT_RESULT(PHONE_NUMBER_ERROR_NONE, nRet, "phone_number_get_normalized_number", PhoneNumberUtilsGetError(nRet));
    }
    else
    {
       PRINT_RESULT(PHONE_NUMBER_ERROR_NOT_SUPPORTED, nRet, "phone_number_get_normalized_number", PhoneNumberUtilsGetError(nRet));
    }
    return 0;

}

//& type: auto
//& purpose: This function connect and disconnect number
/**
 * @testcase                            ITc_phone_number_connect_disconnect_p
 * @since_tizen                         3.0
 * @author                              SRID(nibha.sharma)
 * @reviewer                            SRID(parshant.v)
 * @type                                auto
 * @description                         This function connect and disconnect number
 * @scenario                           	phone_number_disconnect, phone_number_connect
 * @apicovered                          phone_number_connect and phone_number_disconnect
 * @passcase                            if  phone_number_connect and phone_number_disconnect returns success
 * @failcase                            if  phone_number_connect and phone_number_disconnect returns failure
 * @precondition                        NA
 * @postcondition                       NA
 */
int ITc_phone_number_connect_disconnect_p(void)
{
    START_TEST;

	int nRet = PHONE_NUMBER_ERROR_NONE;

	nRet = phone_number_disconnect();
	PRINT_RESULT(PHONE_NUMBER_ERROR_NONE, nRet, "phone_number_disconnect", PhoneNumberUtilsGetError(nRet));

	nRet = phone_number_connect();
	PRINT_RESULT(PHONE_NUMBER_ERROR_NONE, nRet, "phone_number_connect", PhoneNumberUtilsGetError(nRet));

	return 0;
}

/** @}*/
/** @}*/
