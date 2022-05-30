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
#include "CTs-vulkan-common.h"
struct instance_demo {
    SDL_Window* sdl_window;
    SDL_DisplayMode sdl_mode;

    VkInstance inst;
    VkPhysicalDevice gpu;
    VkDevice device;

    uint32_t enabled_extension_count;
    uint32_t enabled_layer_count;
    char *extension_names[64];

    int width, height;

    float depthStencil;
    float depthIncrement;
};

static struct instance_demo instance_demo;

/** @addtogroup ctc-vulkan
* @ingroup		ctc
* @{
*/

//& set: Vulkan


/**
 * @function 		CTs_vulkan_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void CTs_vulkan_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}
	g_bCheckStarup = true;

    //Initialize SDL
    SDL_GetDisplayMode(0, 0, &(instance_demo.sdl_mode));

    instance_demo.width = instance_demo.sdl_mode.w;
    instance_demo.height = instance_demo.sdl_mode.h;
    instance_demo.depthStencil = 1.0;
    instance_demo.depthIncrement = -0.01f;

    printf("width %d, height %d\n",instance_demo.sdl_mode.w,instance_demo.sdl_mode.h);
    instance_demo.sdl_window =  SDL_CreateWindow( "SDL Vulkan Sample",
                                          0, 0, instance_demo.sdl_mode.w, instance_demo.sdl_mode.h,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN);
    if( instance_demo.sdl_window == NULL ) {
//        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        FPRINTF("[Line : %d][%s] Window could not be create! SDL_Error: %s\\n", __LINE__, API_NAMESPACE, SDL_GetError());
        g_bCheckStarup = false;
		return;
    }

	return;
}


/**
 * @function 		CTs_vulkan_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void CTs_vulkan_cleanup(void)
{
	//Destroy window
	if(g_bCheckStarup)
	{
		SDL_DestroyWindow( instance_demo.sdl_window );
	}

    //Quit SDL subsystems
//    SDL_Quit();

	return;
}


/** @addtogroup	ctc-vulkan-testcases
* @brief 		Integration testcases for module vulkan
* @ingroup		ctc-vulkan
* @{
*/


//& purpose: vulkan initialize.
//&type: auto
/**
* @testcase			CTc_vulkan_create_instance_p
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer         SRID(a.pandia1)
* @type 			auto
* @scenario			vulkan initialize
* @apicovered		vkCreateInstance
* @passcase			Covered api should return zero success value
* @failcase			Covered api returns negative nRetor value 
* @precondition		NA
* @postcondition	NA
*/
int CTc_vulkan_create_instance_p(void)
{
	START_TEST;

	VkResult nRet;
    char **instance_validation_layers = NULL;
    //uint32_t i;
    instance_demo.enabled_extension_count = 0;
    instance_demo.enabled_layer_count = 0;

   /* Look for instance extensions */
    memset(instance_demo.extension_names, 0, sizeof(instance_demo.extension_names));

    SDL_Vulkan_GetInstanceExtensions(instance_demo.sdl_window, &(instance_demo.enabled_extension_count), NULL);
    SDL_Vulkan_GetInstanceExtensions(instance_demo.sdl_window, &(instance_demo.enabled_extension_count), instance_demo.extension_names);
    const VkApplicationInfo app = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext = NULL,
        .pApplicationName = APP_SHORT_NAME,
        .applicationVersion = 0,
        .pEngineName = APP_SHORT_NAME,
        .engineVersion = 0,
        .apiVersion = VK_API_VERSION_1_0,
    };
     VkInstanceCreateInfo inst_info = {
         .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
         .pNext = NULL,
         .pApplicationInfo = &app,
         .enabledLayerCount = instance_demo.enabled_layer_count,
         .ppEnabledLayerNames = (const char *const *)instance_validation_layers,
         .enabledExtensionCount = instance_demo.enabled_extension_count,
         .ppEnabledExtensionNames = (const char *const *)instance_demo.extension_names,
     };

    uint32_t gpu_count;

     nRet = vkCreateInstance(&inst_info, NULL, &instance_demo.inst);
	 if (nRet == VK_ERROR_INCOMPATIBLE_DRIVER) {
		 FPRINTF("[Line : %d][%s] Cannot find a compatible Vulkan installable client driver (ICD).\n\nPlease look at the Getting Started guide for additional information. vkCreateInstance Failure\\n", __LINE__, API_NAMESPACE);
		 return 1;
     } else if (nRet == VK_ERROR_EXTENSION_NOT_PRESENT) {
		 FPRINTF("[Line : %d][%s] Cannot find a specified extension library. Make sure your layers path is set appropriately. vkCreateInstance Failure\\n", __LINE__, API_NAMESPACE);
		 return 1;
     } else {
		 FPRINTF("[Line : %d][%s] vkCreateInstance failed.\n\nDo you have a compatible Vulkan installable client driver (ICD) installed?\nPlease look at the Getting Started guide for additional information. vkCreateInstance Failure %s\\n", __LINE__, API_NAMESPACE, VulkanGetError(nRet));
		 return 1;
     }
	return 0;
}

/** @} */
/** @} */
