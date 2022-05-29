//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	 http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-phonenumber-utils-common.h"

/** @addtogroup itc-phonenumber-utils
*  @ingroup itc
*  @{
*/

/**
 * @function 		PhoneNumberUtilsGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet: error code returned
 * @return 			error string
 */
char *PhoneNumberUtilsGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case PHONE_NUMBER_ERROR_NONE: 						szErrorVal = "PHONE_NUMBER_ERROR_NONE";							break;
		case PHONE_NUMBER_ERROR_IO_ERROR: 					szErrorVal = "PHONE_NUMBER_ERROR_IO_ERROR";						break;
		case PHONE_NUMBER_ERROR_OUT_OF_MEMORY: 				szErrorVal = "PHONE_NUMBER_ERROR_OUT_OF_MEMORY";				break;
		case PHONE_NUMBER_ERROR_INVALID_PARAMETER: 			szErrorVal = "PHONE_NUMBER_ERROR_INVALID_PARAMETER";			break;
		case PHONE_NUMBER_ERROR_FILE_NO_SPACE_ON_DEVICE: 	szErrorVal = "PHONE_NUMBER_ERROR_FILE_NO_SPACE_ON_DEVICE";		break;
		case PHONE_NUMBER_ERROR_NOT_SUPPORTED: 				szErrorVal = "PHONE_NUMBER_ERROR_NOT_SUPPORTED";				break;
		case PHONE_NUMBER_ERROR_NO_DATA: 					szErrorVal = "PHONE_NUMBER_ERROR_NO_DATA";						break;
		default: 											szErrorVal = "Unknown Error";									break;
	}
	return szErrorVal;
}

/**
 * @function 		GetRegion
 * @description	 	Maps Types of given region code values to string.
 * @parameter		nRet: region code
 * @return 			region code value represented as string
 */
char* GetRegion(int nRet)
{
	char *pszTypeVal = NULL;

	switch ( nRet )
	{
		case PHONE_NUMBER_REGION_ALAND_ISLANDS:								pszTypeVal = "PHONE_NUMBER_REGION_ALAND_ISLANDS";								break;
		case PHONE_NUMBER_REGION_ALBANIA:									pszTypeVal = "PHONE_NUMBER_REGION_ALBANIA";										break;
		case PHONE_NUMBER_REGION_ALGERIA:									pszTypeVal = "PHONE_NUMBER_REGION_ALGERIA";										break;
		case PHONE_NUMBER_REGION_AMERICAN_SAMOA:							pszTypeVal = "PHONE_NUMBER_REGION_AMERICAN_SAMOA";								break;
		case PHONE_NUMBER_REGION_ANGOLA:									pszTypeVal = "PHONE_NUMBER_REGION_ANGOLA";										break;
		case PHONE_NUMBER_REGION_ANGUILLA:									pszTypeVal = "PHONE_NUMBER_REGION_ANGUILLA";									break;
		case PHONE_NUMBER_REGION_ARGENTINA:									pszTypeVal = "PHONE_NUMBER_REGION_ARGENTINA";									break;				
		case PHONE_NUMBER_REGION_ARMENIA:									pszTypeVal = "PHONE_NUMBER_REGION_ARMENIA";										break;
		case PHONE_NUMBER_REGION_ASCENSION_ISLAND:							pszTypeVal = "PHONE_NUMBER_REGION_ASCENSION_ISLAND";							break;
		case PHONE_NUMBER_REGION_ATIGUA_AND_BARBUDA:						pszTypeVal = "PHONE_NUMBER_REGION_ATIGUA_AND_BARBUDA";							break;
		case PHONE_NUMBER_REGION_AUSTRIA:									pszTypeVal = "PHONE_NUMBER_REGION_AUSTRIA";										break;
		case PHONE_NUMBER_REGION_BAHAMAS:									pszTypeVal = "PHONE_NUMBER_REGION_BAHAMAS";										break;
		case PHONE_NUMBER_REGION_BARBADOS:									pszTypeVal = "PHONE_NUMBER_REGION_BARBADOS";									break;
		case PHONE_NUMBER_REGION_BELARUS:									pszTypeVal = "PHONE_NUMBER_REGION_BELARUS";										break;
		case PHONE_NUMBER_REGION_BELGIUM:									pszTypeVal = "PHONE_NUMBER_REGION_BELGIUM";										break;
		case PHONE_NUMBER_REGION_BENIN:										pszTypeVal = "PHONE_NUMBER_REGION_BENIN";										break;
		case PHONE_NUMBER_REGION_BERMUDA:									pszTypeVal = "PHONE_NUMBER_REGION_BERMUDA";										break;
		case PHONE_NUMBER_REGION_BONAIRE_SINT_EUSTATIUS_AND_SABA:			pszTypeVal = "PHONE_NUMBER_REGION_BONAIRE_SINT_EUSTATIUS_AND_SABA";				break;
		case PHONE_NUMBER_REGION_BOTSWANA:									pszTypeVal = "PHONE_NUMBER_REGION_BOTSWANA";									break;
		case PHONE_NUMBER_REGION_BRAZIL:									pszTypeVal = "PHONE_NUMBER_REGION_BRAZIL";										break;
		case PHONE_NUMBER_REGION_BULGARIA:									pszTypeVal = "PHONE_NUMBER_REGION_BULGARIA";									break;
		case PHONE_NUMBER_REGION_BURKINA_FASO:								pszTypeVal = "PHONE_NUMBER_REGION_BURKINA_FASO";								break;
		case PHONE_NUMBER_REGION_BURUNDI:									pszTypeVal = "PHONE_NUMBER_REGION_BURUNDI";										break;
		case PHONE_NUMBER_REGION_CABO_VERDE:								pszTypeVal = "PHONE_NUMBER_REGION_CABO_VERDE";									break;
		case PHONE_NUMBER_REGION_CAMEROON:									pszTypeVal = "PHONE_NUMBER_REGION_CAMEROON";									break;
		case PHONE_NUMBER_REGION_CANADA:									pszTypeVal = "PHONE_NUMBER_REGION_CANADA";										break;
		case PHONE_NUMBER_REGION_CAYMAN_ISLAND:								pszTypeVal = "PHONE_NUMBER_REGION_CAYMAN_ISLAND";								break;
		case PHONE_NUMBER_REGION_CHILE:										pszTypeVal = "PHONE_NUMBER_REGION_CHILE";										break;
		case PHONE_NUMBER_REGION_CHINA:										pszTypeVal = "PHONE_NUMBER_REGION_CHINA";										break;
		case PHONE_NUMBER_REGION_COLOMBIA:									pszTypeVal = "PHONE_NUMBER_REGION_COLOMBIA";									break;
		case PHONE_NUMBER_REGION_COMOROS:									pszTypeVal = "PHONE_NUMBER_REGION_COMOROS";										break;
		case PHONE_NUMBER_REGION_CONGO:										pszTypeVal = "PHONE_NUMBER_REGION_CONGO";										break;
		case PHONE_NUMBER_REGION_COTE_D_IVOIRE:							 	pszTypeVal = "PHONE_NUMBER_REGION_COTE_D_IVOIRE";								break;
		case PHONE_NUMBER_REGION_CUBA:										pszTypeVal = "PHONE_NUMBER_REGION_CUBA";										break;
		case PHONE_NUMBER_REGION_CURACAO:									pszTypeVal = "PHONE_NUMBER_REGION_CURACAO";										break;
		case PHONE_NUMBER_REGION_CZECH_REPUBLIC:							pszTypeVal = "PHONE_NUMBER_REGION_CZECH_REPUBLIC";								break;
		case PHONE_NUMBER_REGION_DEMOCRATIC_REPUBLIC_OF_THE_CONGO:			pszTypeVal = "PHONE_NUMBER_REGION_DEMOCRATIC_REPUBLIC_OF_THE_CONGO";			break;
		case PHONE_NUMBER_REGION_DOMINICA:									pszTypeVal = "PHONE_NUMBER_REGION_DOMINICA";									break;
		case PHONE_NUMBER_REGION_DOMINICAN_REPUBLIC:						pszTypeVal = "PHONE_NUMBER_REGION_DOMINICAN_REPUBLIC";							break;
		case PHONE_NUMBER_REGION_EGYPT:									 	pszTypeVal = "PHONE_NUMBER_REGION_EGYPT";										break;
		case PHONE_NUMBER_REGION_ESTONIA:									pszTypeVal = "PHONE_NUMBER_REGION_ESTONIA";										break;
		case PHONE_NUMBER_REGION_ETHIOPIA:									pszTypeVal = "PHONE_NUMBER_REGION_ETHIOPIA";									break;
		case PHONE_NUMBER_REGION_FINLAND:									pszTypeVal = "PHONE_NUMBER_REGION_FINLAND";										break;
		case PHONE_NUMBER_REGION_FRANCE:									pszTypeVal = "PHONE_NUMBER_REGION_FRANCE";										break;
		case PHONE_NUMBER_REGION_GABON:									 	pszTypeVal = "PHONE_NUMBER_REGION_GABON";										break;
		case PHONE_NUMBER_REGION_GAMBIA:									pszTypeVal = "PHONE_NUMBER_REGION_GAMBIA";										break;
		case PHONE_NUMBER_REGION_GERMANY:									pszTypeVal = "PHONE_NUMBER_REGION_GERMANY";										break;
		case PHONE_NUMBER_REGION_GHANA:									 	pszTypeVal = "PHONE_NUMBER_REGION_GHANA";										break;
		case PHONE_NUMBER_REGION_GREECE:									pszTypeVal = "PHONE_NUMBER_REGION_GREECE";										break;
		case PHONE_NUMBER_REGION_GREENLAND:								 	pszTypeVal = "PHONE_NUMBER_REGION_GREENLAND";									break;
		case PHONE_NUMBER_REGION_GRENADA:									pszTypeVal = "PHONE_NUMBER_REGION_GRENADA";										break;
		case PHONE_NUMBER_REGION_GUAM:										pszTypeVal = "PHONE_NUMBER_REGION_GUAM";										break;
		case PHONE_NUMBER_REGION_GUERNSEY:								 	pszTypeVal = "PHONE_NUMBER_REGION_GUERNSEY";									break;
		case PHONE_NUMBER_REGION_GUINEA:									pszTypeVal = "PHONE_NUMBER_REGION_GUINEA";										break;
		case PHONE_NUMBER_REGION_GUINEA_BISSAU:								pszTypeVal = "PHONE_NUMBER_REGION_GUINEA_BISSAU";								break;
		case PHONE_NUMBER_REGION_HUNGARY:									pszTypeVal = "PHONE_NUMBER_REGION_HUNGARY";										break;
		case PHONE_NUMBER_REGION_ICELAND:									pszTypeVal = "PHONE_NUMBER_REGION_ICELAND";										break;
		case PHONE_NUMBER_REGION_INDIA:										pszTypeVal = "PHONE_NUMBER_REGION_INDIA";										break;
		case PHONE_NUMBER_REGION_INDONESIA:									pszTypeVal = "PHONE_NUMBER_REGION_INDONESIA";									break;
		case PHONE_NUMBER_REGION_IRELAND:									pszTypeVal = "PHONE_NUMBER_REGION_IRELAND";										break;
		case PHONE_NUMBER_REGION_ISLAMIC_REPUBLIC_OF_IRAN:				 	pszTypeVal = "PHONE_NUMBER_REGION_ISLAMIC_REPUBLIC_OF_IRAN";					break;
		case PHONE_NUMBER_REGION_ISLE_OF_MAN:								pszTypeVal = "PHONE_NUMBER_REGION_ISLE_OF_MAN";									break;
		case PHONE_NUMBER_REGION_ITALY:										pszTypeVal = "PHONE_NUMBER_REGION_ITALY";										break;
		case PHONE_NUMBER_REGION_JAMAICA:									pszTypeVal = "PHONE_NUMBER_REGION_JAMAICA";										break;
		case PHONE_NUMBER_REGION_JAPAN:										pszTypeVal = "PHONE_NUMBER_REGION_JAPAN";										break;
		case PHONE_NUMBER_REGION_JERSEY:									pszTypeVal = "PHONE_NUMBER_REGION_JERSEY";										break;
		case PHONE_NUMBER_REGION_JORDAN:									pszTypeVal = "PHONE_NUMBER_REGION_JORDAN";										break;
		case PHONE_NUMBER_REGION_KAZAKHSTAN:							 	pszTypeVal = "PHONE_NUMBER_REGION_KAZAKHSTAN";									break;
		case PHONE_NUMBER_REGION_KENYA:										pszTypeVal = "PHONE_NUMBER_REGION_KENYA";										break;
		case PHONE_NUMBER_REGION_KIRIBATI:								 	pszTypeVal = "PHONE_NUMBER_REGION_KIRIBATI";									break;
		case PHONE_NUMBER_REGION_LATVIA:									pszTypeVal = "PHONE_NUMBER_REGION_LATVIA";										break;
		case PHONE_NUMBER_REGION_LESOTHO:									pszTypeVal = "PHONE_NUMBER_REGION_LESOTHO";										break;
		case PHONE_NUMBER_REGION_LITHUANIA:									pszTypeVal = "PHONE_NUMBER_REGION_LITHUANIA";									break;
		case PHONE_NUMBER_REGION_LUXEMBOURG:							 	pszTypeVal = "PHONE_NUMBER_REGION_LUXEMBOURG";									break;
		case PHONE_NUMBER_REGION_MADAGASCAR:							 	pszTypeVal = "PHONE_NUMBER_REGION_MADAGASCAR";									break;
		case PHONE_NUMBER_REGION_MAURITANIA:							 	pszTypeVal = "PHONE_NUMBER_REGION_MAURITANIA";									break;
		case PHONE_NUMBER_REGION_MAURITIUS:									pszTypeVal = "PHONE_NUMBER_REGION_MAURITIUS";									break;
		case PHONE_NUMBER_REGION_MONTSERRAT:							 	pszTypeVal = "PHONE_NUMBER_REGION_MONTSERRAT";									break;
		case PHONE_NUMBER_REGION_MOROCCO:									pszTypeVal = "PHONE_NUMBER_REGION_MOROCCO";										break;
		case PHONE_NUMBER_REGION_MOZAMBIQUE:							 	pszTypeVal = "PHONE_NUMBER_REGION_MOZAMBIQUE";									break;
		case PHONE_NUMBER_REGION_NAMIBIA:									pszTypeVal = "PHONE_NUMBER_REGION_NAMIBIA";										break;
		case PHONE_NUMBER_REGION_NETHERLANDS:								pszTypeVal = "PHONE_NUMBER_REGION_NETHERLANDS";									break;
		case PHONE_NUMBER_REGION_NIGERIA:									pszTypeVal = "PHONE_NUMBER_REGION_NIGERIA";										break;
		case PHONE_NUMBER_REGION_NORTHERN_MARIANA_ISLANDS:				 	pszTypeVal = "PHONE_NUMBER_REGION_NORTHERN_MARIANA_ISLANDS";					break;
		case PHONE_NUMBER_REGION_NORWAY:									pszTypeVal = "PHONE_NUMBER_REGION_NORWAY";										break;
		case PHONE_NUMBER_REGION_PERU:									 	pszTypeVal = "PHONE_NUMBER_REGION_PERU";										break;
		case PHONE_NUMBER_REGION_POLAND:									pszTypeVal = "PHONE_NUMBER_REGION_POLAND";										break;
		case PHONE_NUMBER_REGION_PORTUGAL:								 	pszTypeVal = "PHONE_NUMBER_REGION_PORTUGAL";									break;
		case PHONE_NUMBER_REGION_PUERTO_RICO:								pszTypeVal = "PHONE_NUMBER_REGION_PUERTO_RICO";									break;
		case PHONE_NUMBER_REGION_REPUBLIC_OF_KOREA:							pszTypeVal = "PHONE_NUMBER_REGION_REPUBLIC_OF_KOREA";							break;
		case PHONE_NUMBER_REGION_REPUBLIC_OF_MOLDOVA:						pszTypeVal = "PHONE_NUMBER_REGION_REPUBLIC_OF_MOLDOVA";							break;
		case PHONE_NUMBER_REGION_ROMANIA:									pszTypeVal = "PHONE_NUMBER_REGION_ROMANIA";										break;
		case PHONE_NUMBER_REGION_RUSSIAN_FEDERATION:					 	pszTypeVal = "PHONE_NUMBER_REGION_RUSSIAN_FEDERATION";							break;
		case PHONE_NUMBER_REGION_SAINT_HELENA:							 	pszTypeVal = "PHONE_NUMBER_REGION_SAINT_HELENA";								break;
		case PHONE_NUMBER_REGION_SAINT_KITTS_AND_NEVIS:						pszTypeVal = "PHONE_NUMBER_REGION_SAINT_KITTS_AND_NEVIS";						break;
		case PHONE_NUMBER_REGION_SAINT_LUCIA:								pszTypeVal = "PHONE_NUMBER_REGION_SAINT_LUCIA";									break;
		case PHONE_NUMBER_REGION_SAINT_VINCENT_AND_THE_GRENADINES:		 	pszTypeVal = "PHONE_NUMBER_REGION_SAINT_VINCENT_AND_THE_GRENADINES";			break;
		case PHONE_NUMBER_REGION_SAO_TOME_AND_PRINCIPE:						pszTypeVal = "PHONE_NUMBER_REGION_SAO_TOME_AND_PRINCIPE";						break;
		case PHONE_NUMBER_REGION_SAUDI_ARABIA:							 	pszTypeVal = "PHONE_NUMBER_REGION_SAUDI_ARABIA";								break;
		case PHONE_NUMBER_REGION_SENEGAL:									pszTypeVal = "PHONE_NUMBER_REGION_SENEGAL";										break;
		case PHONE_NUMBER_REGION_SERBIA:									pszTypeVal = "PHONE_NUMBER_REGION_SERBIA";										break;
		case PHONE_NUMBER_REGION_SIERRA_LEONE:							 	pszTypeVal = "PHONE_NUMBER_REGION_SIERRA_LEONE";								break;
		case PHONE_NUMBER_REGION_SINT_MAARTEN:								pszTypeVal = "PHONE_NUMBER_REGION_SINT_MAARTEN";								break;
		case PHONE_NUMBER_REGION_SLOVAKIA:									pszTypeVal = "PHONE_NUMBER_REGION_SLOVAKIA";									break;
		case PHONE_NUMBER_REGION_SOMALIA:									pszTypeVal = "PHONE_NUMBER_REGION_SOMALIA";										break;
		case PHONE_NUMBER_REGION_SOUTH_AFRICA:								pszTypeVal = "PHONE_NUMBER_REGION_SOUTH_AFRICA";								break;
		case PHONE_NUMBER_REGION_SPAIN:									 	pszTypeVal = "PHONE_NUMBER_REGION_SPAIN";										break;
		case PHONE_NUMBER_REGION_SRI_LANKA:								 	pszTypeVal = "PHONE_NUMBER_REGION_SRI_LANKA";									break;
		case PHONE_NUMBER_REGION_SUDAN:									 	pszTypeVal = "PHONE_NUMBER_REGION_SUDAN";										break;
		case PHONE_NUMBER_REGION_SVALBARD_AND_JAN_MAYEN:					pszTypeVal = "PHONE_NUMBER_REGION_SVALBARD_AND_JAN_MAYEN";						break;
		case PHONE_NUMBER_REGION_SWAZILAND:								 	pszTypeVal = "PHONE_NUMBER_REGION_SWAZILAND";									break;
		case PHONE_NUMBER_REGION_SWEDEN:									pszTypeVal = "PHONE_NUMBER_REGION_SWEDEN";										break;
		case PHONE_NUMBER_REGION_SWITZERLAND:							 	pszTypeVal = "PHONE_NUMBER_REGION_SWITZERLAND";									break;
		case PHONE_NUMBER_REGION_TAIWAN_PROVINCE_OF_CHINA:				 	pszTypeVal = "PHONE_NUMBER_REGION_TAIWAN_PROVINCE_OF_CHINA";					break;
		case PHONE_NUMBER_REGION_THAILAND:									pszTypeVal = "PHONE_NUMBER_REGION_THAILAND";									break;
		case PHONE_NUMBER_REGION_THE_FORMER_YUGOSLAV_REPUBLIC_OF_MACEDONIA: pszTypeVal = "PHONE_NUMBER_REGION_THE_FORMER_YUGOSLAV_REPUBLIC_OF_MACEDONIA";	break;
		case PHONE_NUMBER_REGION_TOGO:										pszTypeVal = "PHONE_NUMBER_REGION_TOGO";										break;
		case PHONE_NUMBER_REGION_TRINIDAD_AND_TOBAGO:		 				pszTypeVal = "PHONE_NUMBER_REGION_TRINIDAD_AND_TOBAGO";							break;
		case PHONE_NUMBER_REGION_TRISTAN_DA_CUNHA:							pszTypeVal = "PHONE_NUMBER_REGION_TRISTAN_DA_CUNHA";							break;
		case PHONE_NUMBER_REGION_TUNISIA:					 				pszTypeVal = "PHONE_NUMBER_REGION_TUNISIA";										break;
		case PHONE_NUMBER_REGION_TURKEY:									pszTypeVal = "PHONE_NUMBER_REGION_TURKEY";										break;
		case PHONE_NUMBER_REGION_TURKS_AND_CAICOS_ISLANDS:					pszTypeVal = "PHONE_NUMBER_REGION_TURKS_AND_CAICOS_ISLANDS";					break;
		case PHONE_NUMBER_REGION_UGANDA:									pszTypeVal = "PHONE_NUMBER_REGION_UGANDA";										break;
		case PHONE_NUMBER_REGION_UNITED_KINGDOM:							pszTypeVal = "PHONE_NUMBER_REGION_UNITED_KINGDOM";								break;
		case PHONE_NUMBER_REGION_UNITED_STATES_OF_AMERICA:					pszTypeVal = "PHONE_NUMBER_REGION_UNITED_STATES_OF_AMERICA";					break;
		case PHONE_NUMBER_REGION_VENEZUELA:				 					pszTypeVal = "PHONE_NUMBER_REGION_VENEZUELA";									break;
		case PHONE_NUMBER_REGION_VIET_NAM:									pszTypeVal = "PHONE_NUMBER_REGION_VIET_NAM";									break;
		case PHONE_NUMBER_REGION_VIRGIN_ISLAND_BRITISH:	 					pszTypeVal = "PHONE_NUMBER_REGION_VIRGIN_ISLAND_BRITISH";						break;
		case PHONE_NUMBER_REGION_VIRGIN_ISLAND_US:							pszTypeVal = "PHONE_NUMBER_REGION_VIRGIN_ISLAND_US";							break;
		case PHONE_NUMBER_REGION_WESTERN_SAHARA:			 				pszTypeVal = "PHONE_NUMBER_REGION_WESTERN_SAHARA";								break;
		case PHONE_NUMBER_REGION_ZAMBIA:									pszTypeVal = "PHONE_NUMBER_REGION_ZAMBIA";										break;
		case PHONE_NUMBER_REGION_ZIMBABWE:									pszTypeVal = "PHONE_NUMBER_REGION_ZIMBABWE";									break;
		default:															pszTypeVal = "Unknown Region";													break;
	}
	return pszTypeVal;
}	

/**
 * @function 		GetLanguage
 * @description	 	Maps Types of given language code values to string.
 * @parameter		nRet: language value
 * @return 			Language code represented as string
 */
char* GetLanguage(int nRet)
{
	char *pszTypeVal = NULL;

	switch ( nRet )
	{
		case PHONE_NUMBER_LANG_AMHARIC:					pszTypeVal = "PHONE_NUMBER_LANG_AMHARIC";					break;
		case PHONE_NUMBER_LANG_ARABIC:					pszTypeVal = "PHONE_NUMBER_LANG_ARABIC";					break;
		case PHONE_NUMBER_LANG_BELARUSIAN:				pszTypeVal = "PHONE_NUMBER_LANG_BELARUSIAN";				break;
		case PHONE_NUMBER_LANG_BULGARIAN:				pszTypeVal = "PHONE_NUMBER_LANG_BULGARIAN";					break;
		case PHONE_NUMBER_LANG_CHINESE:					pszTypeVal = "PHONE_NUMBER_LANG_CHINESE";					break;
		case PHONE_NUMBER_LANG_CHINESE_TRADITIONAL:		pszTypeVal = "PHONE_NUMBER_LANG_CHINESE_TRADITIONAL";		break;
		case PHONE_NUMBER_LANG_CZECH:					pszTypeVal = "PHONE_NUMBER_LANG_CZECH";						break;				
		case PHONE_NUMBER_LANG_DUTCH:					pszTypeVal = "PHONE_NUMBER_LANG_DUTCH";						break;
		case PHONE_NUMBER_LANG_ENGLISH:	 				pszTypeVal = "PHONE_NUMBER_LANG_ENGLISH";					break;
		case PHONE_NUMBER_LANG_FINNISH:					pszTypeVal = "PHONE_NUMBER_LANG_FINNISH";					break;
		case PHONE_NUMBER_LANG_FRENCH:					pszTypeVal = "PHONE_NUMBER_LANG_FRENCH";					break;
		case PHONE_NUMBER_LANG_GERMAN:					pszTypeVal = "PHONE_NUMBER_LANG_GERMAN";					break;
		case PHONE_NUMBER_LANG_GREEK:					pszTypeVal = "PHONE_NUMBER_LANG_GREEK";						break;
		case PHONE_NUMBER_LANG_HUNGARIAN:				pszTypeVal = "PHONE_NUMBER_LANG_HUNGARIAN";					break;
		case PHONE_NUMBER_LANG_INDONESIAN:				pszTypeVal = "PHONE_NUMBER_LANG_INDONESIAN";				break;
		case PHONE_NUMBER_LANG_ITALIAN:					pszTypeVal = "PHONE_NUMBER_LANG_ITALIAN";					break;
		case PHONE_NUMBER_LANG_JAPANESE:				pszTypeVal = "PHONE_NUMBER_LANG_JAPANESE";					break;
		case PHONE_NUMBER_LANG_KOREAN:					pszTypeVal = "PHONE_NUMBER_LANG_KOREAN";					break;				
		case PHONE_NUMBER_LANG_NORTHERN_SAMI:			pszTypeVal = "PHONE_NUMBER_LANG_NORTHERN_SAMI";				break;
		case PHONE_NUMBER_LANG_PERSIAN:	 				pszTypeVal = "PHONE_NUMBER_LANG_PERSIAN";					break;
		case PHONE_NUMBER_LANG_POLISH:					pszTypeVal = "PHONE_NUMBER_LANG_POLISH";					break;
		case PHONE_NUMBER_LANG_PORTUGUESE:				pszTypeVal = "PHONE_NUMBER_LANG_PORTUGUESE";				break;
		case PHONE_NUMBER_LANG_ROMANIAN:				pszTypeVal = "PHONE_NUMBER_LANG_ROMANIAN";					break;
		case PHONE_NUMBER_LANG_RUSSIAN:					pszTypeVal = "PHONE_NUMBER_LANG_RUSSIAN";					break;
		case PHONE_NUMBER_LANG_SERBIAN:					pszTypeVal = "PHONE_NUMBER_LANG_SERBIAN";					break;
		case PHONE_NUMBER_LANG_SPANISH:					pszTypeVal = "PHONE_NUMBER_LANG_SPANISH";					break;
		case PHONE_NUMBER_LANG_SWEDISH:					pszTypeVal = "PHONE_NUMBER_LANG_SWEDISH";					break;				
		case PHONE_NUMBER_LANG_THAI:					pszTypeVal = "PHONE_NUMBER_LANG_THAI";						break;
		case PHONE_NUMBER_LANG_TURKISH:	 				pszTypeVal = "PHONE_NUMBER_LANG_TURKISH";					break;
		case PHONE_NUMBER_LANG_VIETNAMESE:				pszTypeVal = "PHONE_NUMBER_LANG_VIETNAMESE";				break;
		default:										pszTypeVal = "Unknown Language";							break;
	}
	return pszTypeVal;
}

/** @}*/ 
