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
#include "ITs-media-vision-common.h"

//& set: MediaVision

/** @addtogroup itc-media-vision
*  @ingroup itc
*  @{
*/
/**
* @function			movement_detected_cb
* @description		Called when transform is finished just before returning the output.
* @parameter[IN]	The error code of
* @parameter[IN]	Media packet handle	
* @parameter[IN]	The user data passed from the for each function			
* @return			NA
*/
void movement_detected_cb(mv_surveillance_event_trigger_h event_trigger,mv_source_h source,int video_stream_id,mv_surveillance_result_h event_result,void *user_data)
{
	int number_of_movement_regions = 0;
	int nRet = mv_surveillance_get_result_value(event_result,MV_SURVEILLANCE_MOVEMENT_NUMBER_OF_REGIONS,&number_of_movement_regions);
	if(nRet == MEDIA_VISION_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, "mv_surveillance_get_result_value");
	}
	else
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "mv_surveillance_get_result_value", MediaVisionGetError(nRet), nRet);
    }		
	FPRINTF("\nNumber of movement regions is %d \n", number_of_movement_regions);
	
	mv_rectangle_s *movement_regions = malloc(sizeof(mv_rectangle_s) * number_of_movement_regions);
	//target api
	nRet = mv_surveillance_get_result_value(event_result,MV_SURVEILLANCE_MOVEMENT_REGIONS,movement_regions);
	if( nRet == MEDIA_VISION_ERROR_NONE )
    {
		FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, "mv_surveillance_get_result_value");
		FREE_MEMORY(movement_regions);
    }
	else 
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "mv_surveillance_get_result_value",  MediaVisionGetError(nRet), nRet);
		FREE_MEMORY(movement_regions);
	}
}

/**
 * @function 		ITs_media_vision_surveillance_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_vision_surveillance_startup(void)
{
    struct stat stBuff;
    if ( stat(ERR_LOG, &stBuff) == 0 )
    {
        remove(ERR_LOG);
    }
	
	g_bIsFaceRecognitionFeatureSupported = TCTCheckSystemInfoFeatureSupported(FACERECOGFEATURE, API_NAMESPACE);
	g_bIsImageRecognitionFeatureSupported = TCTCheckSystemInfoFeatureSupported(IMAGERECOGFEATURE, API_NAMESPACE);
	
    return;
}


/**
 * @function 		ITs_media_vision_surveillance_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_vision_surveillance_cleanup(void)
{
    return;
}

/**
 * @testcase 				ITc_mv_surveillance_event_trigger_create_destroy_p
 * @author            		SRID(manu.tiwari)
 * @reviewer         		SRID(parshant.v)
 * @type 				    auto
 * @since_tizen 			3.0
 * @description				To Create surveillance event trigger handle
 * @scenario				Call mv_surveillance_event_trigger_create,mv_surveillance_event_trigger_destroy
 * @apicovered				mv_surveillance_event_trigger_create, mv_surveillance_event_trigger_destroy
 * @passcase				If mv_surveillance_event_trigger_create and mv_surveillance_event_trigger_destroy returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To Create surveillance event trigger handle
int ITc_mv_surveillance_event_trigger_create_destroy_p(void)
{
    START_TEST_SURVEILLANCE;
	int nRet = -1;
    mv_surveillance_event_trigger_h handle = NULL;
	static const char *EVENT_TYPES_NAMES[] = 
    {
		MV_SURVEILLANCE_EVENT_TYPE_MOVEMENT_DETECTED,
		MV_SURVEILLANCE_EVENT_TYPE_PERSON_APPEARED_DISAPPEARED,
		MV_SURVEILLANCE_EVENT_TYPE_PERSON_RECOGNIZED
    };

	int enum_size = sizeof(EVENT_TYPES_NAMES)/sizeof(EVENT_TYPES_NAMES[0]);
	int enum_counter = 0;
	for ( enum_counter=0; enum_counter< enum_size; enum_counter++)
	{   
			//target api
			nRet = mv_surveillance_event_trigger_create(EVENT_TYPES_NAMES[enum_counter], &handle);
			PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_event_trigger_create", MediaVisionGetError(nRet));
			CHECK_HANDLE(handle,"mv_surveillance_event_trigger_create");
			//target api
			nRet = mv_surveillance_event_trigger_destroy(handle);
			PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_event_trigger_destroy", MediaVisionGetError(nRet));
	}
	return 0;
}

/**
 * @testcase 				ITc_mv_surveillance_get_event_trigger_type_p
 * @author            		SRID(manu.tiwari)
 * @reviewer         		SRID(parshant.v)
 * @type 				    auto
 * @since_tizen 			3.0
 * @description				Gets the surveillance event trigger type as character string
 * @scenario				Call mv_surveillance_event_trigger_create,mv_surveillance_get_event_trigger_type,mv_surveillance_event_trigger_destroy
 * @apicovered				mv_surveillance_event_trigger_create,mv_surveillance_get_event_trigger_type,mv_surveillance_event_trigger_destroy
 * @passcase				If mv_surveillance_get_event_trigger_type returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: Gets the surveillance event trigger type as character string
int ITc_mv_surveillance_get_event_trigger_type_p(void)
{
	START_TEST_SURVEILLANCE;
	
	int nRet = -1;
	mv_surveillance_event_trigger_h handle = NULL;
	char *event_type = NULL;
	
	nRet = mv_surveillance_event_trigger_create(MV_SURVEILLANCE_EVENT_TYPE_MOVEMENT_DETECTED, &handle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_event_trigger_create", MediaVisionGetError(nRet));
	CHECK_HANDLE(handle,"mv_surveillance_event_trigger_create");
	//target api
	nRet = mv_surveillance_get_event_trigger_type(handle,&event_type);
	PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_get_event_trigger_type", MediaVisionGetError(nRet), FREE_MEMORY(event_type));

	if (strncmp(event_type,MV_SURVEILLANCE_EVENT_TYPE_MOVEMENT_DETECTED,MAX_EVENT_TYPE_LEN) != 0)
	{
		FPRINTF("event_type != MV_SURVEILLANCE_EVENT_TYPE_MOVEMENT_DETECTED \\n");
		nRet = mv_surveillance_event_trigger_destroy(handle);
		PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_event_trigger_destroy", MediaVisionGetError(nRet));
		free(event_type);
		return 1;
	}
	nRet = mv_surveillance_event_trigger_destroy(handle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_event_trigger_destroy", MediaVisionGetError(nRet));
	free(event_type);
	
	return 0;
}

/**
 * @testcase 				ITc_mv_surveillance_set_get_event_trigger_roi_p
 * @author            		SRID(manu.tiwari)
 * @reviewer         		SRID(parshant.v)
 * @type 				    auto
 * @since_tizen 			3.0
 * @description				Sets and Gets ROI (Region Of Interest) to the event trigger
 * @scenario				Call mv_surveillance_event_trigger_create,mv_surveillance_set_event_trigger_roi,mv_surveillance_get_event_trigger_roi,mv_surveillance_event_trigger_destroy
 * @apicovered				mv_surveillance_set_event_trigger_roi,mv_surveillance_get_event_trigger_roi
 * @passcase				If api returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: Sets and Gets ROI (Region Of Interest) to the event trigger
int ITc_mv_surveillance_set_get_event_trigger_roi_p(void)
{
	START_TEST_SURVEILLANCE;

	int nRet = -1;
	mv_surveillance_event_trigger_h handle = NULL;
	const int nRoiPoints = 5;
	int nGetRoiPoints = 0;
	int xRoi = 5, yRoi = 4, i = 0;
	mv_point_s* nGetRoi = NULL;

	nRet = mv_surveillance_event_trigger_create(MV_SURVEILLANCE_EVENT_TYPE_MOVEMENT_DETECTED, &handle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_event_trigger_create", MediaVisionGetError(nRet));
	CHECK_HANDLE(handle,"mv_surveillance_event_trigger_create");

	mv_point_s* nRoi = (mv_point_s*) malloc(sizeof(mv_point_s) * nRoiPoints);
	for (; i < nRoiPoints; ++i) 
	{
		nRoi[i].x = xRoi;
		nRoi[i].y = yRoi;
	}
	//target api
	nRet = mv_surveillance_set_event_trigger_roi(handle,nRoiPoints,nRoi);
	PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_set_event_trigger_roi", MediaVisionGetError(nRet), FREE_MEMORY(nRoi));

	//target api
	nRet = mv_surveillance_get_event_trigger_roi(handle,&nGetRoiPoints,&nGetRoi);
	PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_get_event_trigger_roi", MediaVisionGetError(nRet), FREE_MEMORY(nGetRoi);FREE_MEMORY(nRoi));

	if(nRoiPoints != nGetRoiPoints)
	{
		FPRINTF("[Line : %d][%s] Values of set get not matched!!!\\n", __LINE__, API_NAMESPACE);
		nRet = mv_surveillance_event_trigger_destroy(handle);
		PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_event_trigger_destroy", MediaVisionGetError(nRet),FREE_MEMORY(nGetRoi);FREE_MEMORY(nRoi));
		FREE_MEMORY(nGetRoi);
		FREE_MEMORY(nRoi);
		return 1;
	}
	nRet = mv_surveillance_event_trigger_destroy(handle);
	PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_event_trigger_destroy", MediaVisionGetError(nRet),FREE_MEMORY(nGetRoi);FREE_MEMORY(nRoi));
	
	FREE_MEMORY(nGetRoi);
	FREE_MEMORY(nRoi);
	

	return 0;
}
/**
 * @testcase 				ITc_mv_surveillance_push_source_p
 * @author            		SRID(manu.tiwari)
 * @reviewer         		SRID(parshant.v)
 * @type 				    auto
 * @since_tizen 			3.0
 * @description				Pushes source to the surveillance system to detect events
 * @scenario				Call mv_surveillance_push_source
 * @apicovered				mv_surveillance_push_source
 * @passcase				If mv_surveillance_push_source returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: Pushes source to the surveillance system to detect events
int ITc_mv_surveillance_push_source_p(void)
{
	START_TEST_SURVEILLANCE;
	
	int video_stream_id = 0;
	mv_source_h source1;
	mv_surveillance_event_trigger_h handle = NULL;
	
	char pszFilePath[PATHLEN] = {0,};
	if ( false == MediaVisionAppendToAppDataPath(PATHPFX, pszFilePath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int nRet = mv_surveillance_event_trigger_create(MV_SURVEILLANCE_EVENT_TYPE_MOVEMENT_DETECTED, &handle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_event_trigger_create", MediaVisionGetError(nRet));
	CHECK_HANDLE(handle,"mv_surveillance_event_trigger_create");
	
	nRet = mv_surveillance_subscribe_event_trigger(handle,video_stream_id,NULL,movement_detected_cb,NULL);
	PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_subscribe_event_trigger", MediaVisionGetError(nRet), mv_surveillance_event_trigger_destroy(handle));
	
	nRet = mv_create_source(&source1);
	PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet), mv_surveillance_event_trigger_destroy(handle));
	
	nRet = image_load(pszFilePath, source1);
	PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "image_load", MediaVisionGetError(nRet), mv_surveillance_event_trigger_destroy(handle); mv_destroy_source(source1));
	//target api
	nRet = mv_surveillance_push_source(source1, video_stream_id);
	PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_push_source", MediaVisionGetError(nRet), mv_surveillance_event_trigger_destroy(handle);mv_destroy_source(source1));

	nRet = mv_destroy_source(source1);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_destroy_source", MediaVisionGetError(nRet));
	nRet = mv_surveillance_unsubscribe_event_trigger(handle,video_stream_id);
	PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_unsubscribe_event_trigger", MediaVisionGetError(nRet), mv_surveillance_event_trigger_destroy(handle));

	nRet = mv_surveillance_event_trigger_destroy(handle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_event_trigger_destroy", MediaVisionGetError(nRet));

	return 0;
}
/**
 * @testcase 				ITc_mv_surveillance_subscribe_unsubscribe_event_get_result_value_p
 * @author            		SRID(manu.tiwari)
 * @reviewer         		SRID(parshant.v)
 * @type 				    auto
 * @since_tizen 			3.0
 * @description				Gets result value
 * @scenario				Call mv_surveillance_get_result_value
 * @apicovered				mv_surveillance_get_result_value
 * @passcase				If mv_surveillance_get_result_value returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: Gets result value
int ITc_mv_surveillance_subscribe_unsubscribe_event_get_result_value_p(void)
{
	START_TEST_SURVEILLANCE;
	
	mv_surveillance_event_trigger_h handle = NULL;
	char *event_type = NULL;
	int video_stream_id = 2;
	
	int nRet = mv_surveillance_event_trigger_create(MV_SURVEILLANCE_EVENT_TYPE_MOVEMENT_DETECTED, &handle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_event_trigger_create", MediaVisionGetError(nRet));
	CHECK_HANDLE(handle,"mv_surveillance_event_trigger_create");

	nRet = mv_surveillance_get_event_trigger_type(handle,&event_type);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_get_event_trigger_type", MediaVisionGetError(nRet));

	if (strncmp(event_type,MV_SURVEILLANCE_EVENT_TYPE_MOVEMENT_DETECTED,MAX_EVENT_TYPE_LEN) == 0)
	{
		//traget api
		nRet = mv_surveillance_subscribe_event_trigger(handle,video_stream_id,NULL,movement_detected_cb,NULL);
		PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_subscribe_event_trigger", MediaVisionGetError(nRet), mv_surveillance_event_trigger_destroy(handle));
	}
	nRet = mv_surveillance_unsubscribe_event_trigger(handle,video_stream_id);
	PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_unsubscribe_event_trigger", MediaVisionGetError(nRet), mv_surveillance_event_trigger_destroy(handle));

	nRet = mv_surveillance_event_trigger_destroy(handle);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_event_trigger_destroy", MediaVisionGetError(nRet));
	
	return 0;
}
/**
* @function			foreach_event_result_value_name_cb
* @description		Called when transform is finished just before returning the output.
* @parameter[IN]	The error code of
* @parameter[IN]	Media packet handle	
* @parameter[IN]	The user data passed from the for each function			
* @return			NA
*/
bool foreach_event_result_value_name_cb(const char *value_name, void *user_data)
{
	g_bforeach_event_result_value_nameCompletedCallback = true;

	if (NULL == value_name) 
	{
		return true;
	}
	return true;
}
/**
* @function			foreach_event_type_cb
* @description		Called when transform is finished just before returning the output.
* @parameter[IN]	The error code of
* @parameter[IN]	Media packet handle	
* @parameter[IN]	The user data passed from the for each function			
* @return			NA
*/
bool foreach_event_type_cb(const char *event_type, void *user_data)
{
	g_bforeach_event_typeCompletedCallback = true;

	if (NULL == event_type) 
	{
		return true;
	}

	g_bforeach_event_result_value_nameCompletedCallback = false;
	//target api
	const int nRet = mv_surveillance_foreach_event_result_name(event_type, foreach_event_result_value_name_cb, user_data);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillance_foreach_event_result_name", MediaVisionGetError(nRet));
	if ( !g_bforeach_event_result_value_nameCompletedCallback )
	{
		return false;
	}

	return true;
}
/**
 * @testcase 				ITc_mv_surveillance_foreach_supported_event_type_p
 * @author            		SRID(manu.tiwari)
 * @reviewer         		SRID(parshant.v)
 * @type 				    auto
 * @since_tizen 			3.0
 * @description				Gets result value
 * @scenario				Call mv_surveillance_get_result_value
 * @apicovered				mv_surveillance_get_result_value
 * @passcase				If mv_surveillance_get_result_value returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: Gets result value
int ITc_mv_surveillance_foreach_supported_event_type_p(void)
{
    START_TEST_SURVEILLANCE;
	
	g_bforeach_event_typeCompletedCallback = false;
	const int nRet = mv_surveillance_foreach_supported_event_type(foreach_event_type_cb, NULL);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_surveillanc_foreach_supported_event_type", MediaVisionGetError(nRet));
	if ( !g_bforeach_event_typeCompletedCallback )
	{
		FPRINTF("[Line : %d][%s] foreach_event_type_cb failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	else
	{
		#if DEBUG
		FPRINTF("[Line : %d][%s] mv_surveillance_foreach_supported_event_type is successful\\n", __LINE__, API_NAMESPACE);
		#endif
	}
	return 0;
}
/** @} */
/** @} */
