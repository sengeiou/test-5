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
#include "tct_common.h"

#include <app.h>
#include <system_info.h>
#include <SDL.h>
#include <vulkan/vulkan.h>
#include <sys/stat.h>
#include <dlog.h>
#include <dlfcn.h>

static int argc;
static char **argv;

/**
 * @function         setArgument
 * @description      sets global arguments variable
 * @parameter        argc : argument count
 * @parameter        argv : argument vector
 * @return           NA
 */
void setArgument(int _argc, char* _argv[])
{
	argc = _argc;
	argv = _argv;
}

/**
 * @function         initSDLApp
 * @description      initialize SDL application
 * @return           NA
 */
void initSDLApp()
{
	if (SDL_tizen_app_init(argc, argv) == APP_ERROR_NONE) {
		SDL_SetMainReady();
	}
}

/**
 * @testcase        utc_SDL_tizen_app_init_p
 * @since_tizen     4.0
 * @description     testcase for check normal inputs
 */
int utc_SDL_tizen_app_init_p(void)
{
	int ret = SDL_tizen_app_init(argc, argv);
	assert_eq(ret, APP_ERROR_NONE);
	return 0;
}


/**
 * @testcase        utc_SDL_tizen_app_init_p2
 * @since_tizen     7.0
 * @description     testcase for check working although invalid input
                    (argc is 0)
 */
int utc_SDL_tizen_app_init_p2(void)
{
    argc = 0;
    int ret = SDL_tizen_app_init(argc, argv);
    assert_eq(ret, APP_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_SDL_tizen_app_init_p3
 * @since_tizen     7.0
 * @description     testcase for check working although invalid input
                    (argv is NULL)
 */
int utc_SDL_tizen_app_init_p3(void)
{
    argv = NULL;
    int ret = SDL_tizen_app_init(argc, argv);
    assert_eq(ret, APP_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_SDL_tizen_app_init_n
 * @since_tizen     4.0
 * @description     testcase for calling api twice
 */
int utc_SDL_tizen_app_init_n(void)
{
	int ret = SDL_tizen_app_init(argc, argv);
	assert_eq(ret, APP_ERROR_NONE);
	if(ret == APP_ERROR_NONE)
	{
		ret = SDL_tizen_app_init(argc, argv);
	}
	assert_eq(ret, APP_ERROR_ALREADY_RUNNING);
	return 0;
}

void *vulkan_handle;

PFN_vkGetInstanceProcAddr fn_vkGetInstanceProcAddr;
PFN_vkGetDeviceProcAddr fn_vkGetDeviceProcAddr;
PFN_vkEnumerateInstanceLayerProperties fn_vkEnumerateInstanceLayerProperties;
PFN_vkCreateInstance fn_vkCreateInstance;
PFN_vkEnumeratePhysicalDevices fn_vkEnumeratePhysicalDevices;
PFN_vkEnumerateDeviceLayerProperties fn_vkEnumerateDeviceLayerProperties;
PFN_vkEnumerateDeviceExtensionProperties fn_vkEnumerateDeviceExtensionProperties;
PFN_vkGetPhysicalDeviceProperties fn_vkGetPhysicalDeviceProperties;
PFN_vkGetPhysicalDeviceQueueFamilyProperties fn_vkGetPhysicalDeviceQueueFamilyProperties;
PFN_vkGetPhysicalDeviceFeatures fn_vkGetPhysicalDeviceFeatures;

#define VULKAN_FEATURE "tizen.org/feature/vulkan.version.1_0"
#define DEMO_TEXTURE_COUNT 1
#define APP_SHORT_NAME "sdl-utc"
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define ERR_EXIT(err_msg, err_class)                                           \
    do {                                                                       \
        dlog_print(DLOG_INFO, "VULKAN_CTC", err_msg, __LINE__);                \
        exit(1);                                                               \
    } while (0)

#define GET_INSTANCE_PROC_ADDR(inst, entrypoint)                               \
    {                                                                          \
        demo->fp##entrypoint =                                                 \
            (PFN_vk##entrypoint)fn_vkGetInstanceProcAddr(inst, "vk" #entrypoint); \
        if (demo->fp##entrypoint == NULL) {                                    \
            ERR_EXIT("[Line : %d]vkGetInstanceProcAddr failed to find vk" #entrypoint,    \
                     "vkGetInstanceProcAddr Failure");                         \
        }                                                                      \
    }

#define GET_DEVICE_PROC_ADDR(dev, entrypoint)                                  \
    {                                                                          \
        demo->fp##entrypoint =                                                 \
            (PFN_vk##entrypoint)fn_vkGetDeviceProcAddr(dev, "vk" #entrypoint);    \
        if (demo->fp##entrypoint == NULL) {                                    \
            ERR_EXIT("[Line : %d]vkGetDeviceProcAddr failed to find vk" #entrypoint,      \
                     "vkGetDeviceProcAddr Failure");                           \
        }                                                                      \
    }

bool g_bCheckStartup;
int is_supported;
static int validation_error = 0;

typedef struct _SwapchainBuffers {
    VkImage image;
    VkCommandBuffer cmd;
    VkImageView view;
} SwapchainBuffers;

struct texture_object {
    VkSampler sampler;

    VkImage image;
    VkImageLayout imageLayout;

    VkDeviceMemory mem;
    VkImageView view;
    int32_t tex_width, tex_height;
};

struct demo {
    SDL_Window* sdl_window;
    SDL_DisplayMode sdl_mode;

    VkSurfaceKHR surface;
    bool prepared;
    bool use_staging_buffer;

    VkInstance inst;
    VkPhysicalDevice gpu;
    VkDevice device;
    VkQueue queue;
    VkPhysicalDeviceProperties gpu_props;
    VkQueueFamilyProperties *queue_props;
    uint32_t graphics_queue_node_index;

    uint32_t enabled_extension_count;
    uint32_t enabled_layer_count;
    char *extension_names[64];
    char *device_validation_layers[64];

    int width, height;
    VkFormat format;
    VkColorSpaceKHR color_space;

    PFN_vkGetPhysicalDeviceSurfaceSupportKHR
        fpGetPhysicalDeviceSurfaceSupportKHR;
    PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR
        fpGetPhysicalDeviceSurfaceCapabilitiesKHR;
    PFN_vkGetPhysicalDeviceSurfaceFormatsKHR
        fpGetPhysicalDeviceSurfaceFormatsKHR;
    PFN_vkGetPhysicalDeviceSurfacePresentModesKHR
        fpGetPhysicalDeviceSurfacePresentModesKHR;
    PFN_vkCreateSwapchainKHR fpCreateSwapchainKHR;
    PFN_vkDestroySwapchainKHR fpDestroySwapchainKHR;
    PFN_vkGetSwapchainImagesKHR fpGetSwapchainImagesKHR;
    PFN_vkAcquireNextImageKHR fpAcquireNextImageKHR;
    PFN_vkQueuePresentKHR fpQueuePresentKHR;
    uint32_t swapchainImageCount;
    VkSwapchainKHR swapchain;
    SwapchainBuffers *buffers;

    VkCommandPool cmd_pool;

    struct {
        VkFormat format;

        VkImage image;
        VkDeviceMemory mem;
        VkImageView view;
    } depth;

    struct texture_object textures[DEMO_TEXTURE_COUNT];

    struct {
        VkBuffer buf;
        VkDeviceMemory mem;

        VkPipelineVertexInputStateCreateInfo vi;
        VkVertexInputBindingDescription vi_bindings[1];
        VkVertexInputAttributeDescription vi_attrs[2];
    } vertices;

    VkCommandBuffer setup_cmd; // Command Buffer for initialization commands
    VkCommandBuffer draw_cmd;  // Command Buffer for drawing commands
    VkPipelineLayout pipeline_layout;
    VkDescriptorSetLayout desc_layout;
    VkPipelineCache pipelineCache;
    VkRenderPass render_pass;
    VkPipeline pipeline;

    VkShaderModule vert_shader_module;
    VkShaderModule frag_shader_module;

    VkDescriptorPool desc_pool;
    VkDescriptorSet desc_set;

    VkFramebuffer *framebuffers;

    VkPhysicalDeviceMemoryProperties memory_properties;

    int32_t curFrame;
    int32_t frameCount;
    bool validate;
    bool use_break;
    PFN_vkCreateDebugReportCallbackEXT CreateDebugReportCallback;
    PFN_vkDestroyDebugReportCallbackEXT DestroyDebugReportCallback;
    VkDebugReportCallbackEXT msg_callback;
    PFN_vkDebugReportMessageEXT DebugReportMessage;

    float depthStencil;
    float depthIncrement;

    bool quit;
    uint32_t current_buffer;
    uint32_t queue_count;
};

struct demo tcData;

/**
 * @function         printErrMessage
 * @description      called when err is occured
 * @parameter        function : function name which generates error.
 * @parameter        err : error message.
 * @return           NA
 */
void printErrMessage(const char* function, VkResult err)
{
    if(err == VK_SUCCESS) return;
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[ERR] Error occurred : %d, Function:%s\n", err, function);
}

/*
 * @ brief check the using layers
 * @ return  This functions return a value of type VkBool32 that is either true or false.
 */
VkBool32 demo_check_layers(uint32_t check_count, char **check_names, uint32_t layer_count, VkLayerProperties *layers)
{
    uint32_t i, j;
    for (i = 0; i < check_count; i++) {
        VkBool32 found = 0;
        for (j = 0; j < layer_count; j++) {
            if (!strcmp(check_names[i], layers[j].layerName)) {
                found = 1;
                break;
            }
        }
        if (!found) {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Cannot find layer: %s\n", check_names[i]);
            return 0;
        }
    }
    return 1;
}

/*
 * @ brief Debug Report Callback
 * @ param[in] msgFlags indicates the VkDebugReportFlagBitsEXT that triggered this callback.
 * @ param[in] objType is a VkDebugReportObjectTypeEXT specifying the type of object being used or created at the time the event was triggered.
 * @ param[in] srcObject gives the object where the issue was detected. object may be VK_NULL_OBJECT if there is no object associated with the event.
 * @ param[in] location is a component (layer, driver, loader) defined value that indicates the location of the trigger. This is an optional value.
 * @ param[in] msgCode is a layer-defined value indicating what test triggered this callback.
 * @ param[in] pLayerPrefix is the abbreviation of the component making the callback.
 * @ param[in] pMsg is a null-terminated string detailing the trigger conditions.
 * @ param[in] pUserData is the user data given when the DebugReportCallback was created.
 * @ This functions return a value of type VkBool32 that is either true or false.
 */
VKAPI_ATTR VkBool32 VKAPI_CALL
dbgFunc(VkFlags msgFlags, VkDebugReportObjectTypeEXT objType,
        uint64_t srcObject, size_t location, int32_t msgCode,
        const char *pLayerPrefix, const char *pMsg, void *pUserData) {
    char *message = (char *)malloc(strlen(pMsg) + 100);

    assert(message);

    validation_error = 1;

    if (msgFlags & VK_DEBUG_REPORT_ERROR_BIT_EXT) {
        sprintf(message, "ERROR: [%s] Code %d : %s", pLayerPrefix, msgCode,
                pMsg);
    } else if (msgFlags & VK_DEBUG_REPORT_WARNING_BIT_EXT) {
        sprintf(message, "WARNING: [%s] Code %d : %s", pLayerPrefix, msgCode,
                pMsg);
    } else {
        return false;
    }

    printf("%s\n", message);
    fflush(stdout);
    free(message);

    /*
     * false indicates that layer should not bail-out of an
     * API call that had validation failures. This may mean that the
     * app dies inside the driver due to invalid parameter(s).
     * That's what would happen without validation layers, so we'll
     * keep that behavior here.
     */
    return false;
}

/**
 * @function        utc_sdl_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_sdl_startup(void)
{
    struct stat stBuff;
    bool bVulkan;
    int ret = -1;

    if ( stat(ERR_LOG, &stBuff) == 0 )
    {
        remove(ERR_LOG);
    }
    g_bCheckStartup = true;

    ret = system_info_get_platform_bool(VULKAN_FEATURE, &bVulkan);
    if (ret != SYSTEM_INFO_ERROR_NONE) {
        is_supported = 0;
        g_bCheckStartup = false;
        fprintf(stderr, "\\n[Line : %d] system_info_get_platform_bool is failed.\\n", __LINE__);
        return;
    }

    if (!bVulkan) {
        is_supported = 0;
        g_bCheckStartup = false;
        fprintf(stderr, "\\n[Line : %d] Vulkan version.1_0 is not Supported\\n", __LINE__);
        return;
    }

    is_supported = 1;

    vulkan_handle = dlopen("libvulkan.so", RTLD_NOW);
    if (vulkan_handle) {
        fn_vkGetInstanceProcAddr = dlsym(vulkan_handle, "vkGetInstanceProcAddr");
        fn_vkGetDeviceProcAddr = dlsym(vulkan_handle, "vkGetDeviceProcAddr");
        fn_vkEnumerateInstanceLayerProperties = dlsym(vulkan_handle, "vkEnumerateInstanceLayerProperties");
        fn_vkCreateInstance = dlsym(vulkan_handle, "vkCreateInstance");
        fn_vkEnumeratePhysicalDevices = dlsym(vulkan_handle, "vkEnumeratePhysicalDevices");
        fn_vkEnumerateDeviceLayerProperties = dlsym(vulkan_handle, "vkEnumerateDeviceLayerProperties");
        fn_vkEnumerateDeviceExtensionProperties = dlsym(vulkan_handle, "vkEnumerateDeviceExtensionProperties");
        fn_vkGetPhysicalDeviceProperties = dlsym(vulkan_handle, "vkGetPhysicalDeviceProperties");
        fn_vkGetPhysicalDeviceQueueFamilyProperties = dlsym(vulkan_handle, "vkGetPhysicalDeviceQueueFamilyProperties");
        fn_vkGetPhysicalDeviceFeatures = dlsym(vulkan_handle, "vkGetPhysicalDeviceFeatures");
    }

    //Initialize SDL
   if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize! SDL_Error: %s", SDL_GetError());

        return;
    }
    SDL_GetDisplayMode(0, 0, &(tcData.sdl_mode));

    tcData.width = tcData.sdl_mode.w;
    tcData.height = tcData.sdl_mode.h;
    tcData.depthStencil = 1.0;
    tcData.depthIncrement = -0.01f;

    printf("width %d, height %d\n",tcData.sdl_mode.w,tcData.sdl_mode.h);
    tcData.sdl_window =  SDL_CreateWindow( "SDL Vulkan Sample",
                                          0, 0, tcData.sdl_mode.w, tcData.sdl_mode.h,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN);
    if( tcData.sdl_window == NULL ) {
        fprintf(stderr, "[Line : %d] Window could not be create! SDL_Error: %s\\n", __LINE__, SDL_GetError());
        g_bCheckStartup = false;
        return;
    }

    return;
}

/**
 * @function        utc_sdl_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_sdl_cleanup(void)
{
    //Destroy window
    if(g_bCheckStartup)
    {
        SDL_DestroyWindow( tcData.sdl_window );
    }

    if (vulkan_handle)
        dlclose(vulkan_handle);

    //Quit SDL subsystems
//    SDL_Quit();

    return;
}

/*
 * @ brief Initialize Vulkan
 * @ param[in] demo SDL and vulkan data to use application.
 */
void demo_init_vk(struct demo *demo)
{
    /*
     * Initialize Vulkan:
     * 1. Create an instance.
     * 2. Check for extension support.
     * 3. Use validation layers.
     * 4. Set up a message callback.
     * 5. Select a physical device.
     */

    VkResult err;
    uint32_t instance_layer_count = 0;
    uint32_t device_validation_layer_count = 0;
    char **instance_validation_layers = NULL;
    uint32_t i;
    demo->enabled_extension_count = 0;
    demo->enabled_layer_count = 0;

    char *instance_validation_layers_alt1[] = {
        /* Enabling this layer ensures that all official validation layers will going to be keen
            on trying to catch any mistake the application makes in the use of Vulkan. */
        "VK_LAYER_LUNARG_standard_validation"
    };

    /*
       Standard Validation
       This is meta-layer managed by the loader. (name = VK_LAYER_LUNARG_standard_validation)
       specifying this layer name will cause the loader to load the all of the standard validation layers
       (listed below) in the following optimal order:
    */
    char *instance_validation_layers_alt2[] = {
        "VK_LAYER_GOOGLE_threading",     "VK_LAYER_LUNARG_parameter_validation",
        "VK_LAYER_LUNARG_device_limits", "VK_LAYER_LUNARG_object_tracker",
        "VK_LAYER_LUNARG_image",         "VK_LAYER_LUNARG_core_validation",
        "VK_LAYER_LUNARG_swapchain",     "VK_LAYER_GOOGLE_unique_objects"
    };

    /* Look for validation layers */
    VkBool32 validation_found = 0;
    if (demo->validate) {
        /* Returns up to requested number of global layer properties */
        err = fn_vkEnumerateInstanceLayerProperties(&instance_layer_count, NULL);
        printErrMessage(__FUNCTION__, err);

        instance_validation_layers = instance_validation_layers_alt1;
        if (instance_layer_count > 0) {
            VkLayerProperties *instance_layers = malloc(sizeof(VkLayerProperties) * instance_layer_count);
            err = fn_vkEnumerateInstanceLayerProperties(&instance_layer_count, instance_layers);
            printErrMessage(__FUNCTION__, err);

            validation_found = demo_check_layers(ARRAY_SIZE(instance_validation_layers_alt1),
                                instance_validation_layers, instance_layer_count, instance_layers);
            if (validation_found) {
                demo->enabled_layer_count = ARRAY_SIZE(instance_validation_layers_alt1);
                demo->device_validation_layers[0] = "VK_LAYER_LUNARG_standard_validation";
                device_validation_layer_count = 1;
            } else {
                instance_validation_layers = instance_validation_layers_alt2;
                demo->enabled_layer_count = ARRAY_SIZE(instance_validation_layers_alt2);
                validation_found = demo_check_layers(ARRAY_SIZE(instance_validation_layers_alt2),
                                    instance_validation_layers, instance_layer_count, instance_layers);
                device_validation_layer_count = ARRAY_SIZE(instance_validation_layers_alt2);

                for (i = 0; i < device_validation_layer_count; i++)
                    demo->device_validation_layers[i] = instance_validation_layers[i];
            }
            free(instance_layers);
        }

        if (!validation_found) {
            ERR_EXIT("vkEnumerateInstanceLayerProperties failed to find"
                     "required validation layer.\n\n"
                     "Please look at the Getting Started guide for additional "
                     "information.\n",
                     "vkCreateInstance Failure");
        }
    }

    memset(demo->extension_names, 0, sizeof(demo->extension_names));

    /* This function is to query the available instance extensions in SDL with tizen.*/
    SDL_Vulkan_GetInstanceExtensions(demo->sdl_window, &(demo->enabled_extension_count), NULL);
    SDL_Vulkan_GetInstanceExtensions(demo->sdl_window, &(demo->enabled_extension_count), demo->extension_names);

    /* Structure specifying application info */
    const VkApplicationInfo app = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext = NULL,
        .pApplicationName = APP_SHORT_NAME,
        .applicationVersion = 0,
        .pEngineName = APP_SHORT_NAME,
        .engineVersion = 0,
        .apiVersion = VK_API_VERSION_1_0,
    };
    /* Structure specifying parameters of a newly created instance */
    VkInstanceCreateInfo inst_info = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext = NULL,
        .pApplicationInfo = &app,
        /* Structure specifying parameters of a newly created instance */
        .enabledLayerCount = demo->enabled_layer_count,
        .ppEnabledLayerNames = (const char *const *)instance_validation_layers,
        /* the number of global extensions to enable. */
        .enabledExtensionCount = demo->enabled_extension_count,
        .ppEnabledExtensionNames = (const char *const *)demo->extension_names,
    };

    uint32_t gpu_count;

    /*
     * The very first thing you need to do initialize the Vulkan library by creating an instacne.
     * The instance is the connection between your application and the Vulkan library and.
     * creating it involves specifying some details about your application to the driver.
    */
    err = fn_vkCreateInstance(&inst_info, NULL, &demo->inst);
    if (err == VK_ERROR_INCOMPATIBLE_DRIVER) {
        ERR_EXIT("Cannot find a compatible Vulkan installable client driver "
                 "(ICD).\n\nPlease look at the Getting Started guide for "
                 "additional information.\n",
                 "vkCreateInstance Failure");
    } else if (err == VK_ERROR_EXTENSION_NOT_PRESENT) {
        ERR_EXIT("Cannot find a specified extension library"
                 ".\nMake sure your layers path is set appropriately\n",
                 "vkCreateInstance Failure");
    } else if (err) {
        ERR_EXIT("vkCreateInstance failed.\n\nDo you have a compatible Vulkan "
                 "installable client driver (ICD) installed?\nPlease look at "
                 "the Getting Started guide for additional information.\n",
                 "vkCreateInstance Failure");
    }

    /* Enumerates the physical devices accessible to a Vulkan instance */
    err = fn_vkEnumeratePhysicalDevices(demo->inst, &gpu_count, NULL);
    printErrMessage(__FUNCTION__, err);

    if (gpu_count > 0) {
        VkPhysicalDevice *physical_devices = malloc(sizeof(VkPhysicalDevice) * gpu_count);
        if (physical_devices) {
            err = fn_vkEnumeratePhysicalDevices(demo->inst, &gpu_count, physical_devices);
            printErrMessage(__FUNCTION__, err);
            demo->gpu = physical_devices[0];
            free(physical_devices);
        }
    } else {
        ERR_EXIT("vkEnumeratePhysicalDevices reported zero accessible devices."
                 "\n\nDo you have a compatible Vulkan installable client"
                 " driver (ICD) installed?\nPlease look at the Getting Started"
                 " guide for additional information.\n",
                 "vkEnumeratePhysicalDevices Failure");
    }

    if (demo->validate) {
        validation_found = 0;
        demo->enabled_layer_count = 0;
        uint32_t device_layer_count = 0;
        /* Returns properties of available physical device layers */
        err = fn_vkEnumerateDeviceLayerProperties(demo->gpu, &device_layer_count, NULL);
        printErrMessage(__FUNCTION__, err);

        if (device_layer_count > 0) {
            VkLayerProperties *device_layers = malloc(sizeof(VkLayerProperties) * device_layer_count);
            err = fn_vkEnumerateDeviceLayerProperties(demo->gpu, &device_layer_count, device_layers);
            printErrMessage(__FUNCTION__, err);

            validation_found = demo_check_layers(device_validation_layer_count,
                                                demo->device_validation_layers,
                                                device_layer_count,
                                                device_layers);
            demo->enabled_layer_count = device_validation_layer_count;

            free(device_layers);
        }

        if (!validation_found) {
            ERR_EXIT("vkEnumerateDeviceLayerProperties failed to find "
                     "a required validation layer.\n\n"
                     "Please look at the Getting Started guide for additional "
                     "information.\n",
                     "vkCreateDevice Failure");
        }
    }

    uint32_t device_extension_count = 0;
    VkBool32 swapchainExtFound = 0;
    demo->enabled_extension_count = 0;
    memset(demo->extension_names, 0, sizeof(demo->extension_names));

    /* Returns properties of available physical device extensions */
    err = fn_vkEnumerateDeviceExtensionProperties(demo->gpu, NULL, &device_extension_count, NULL);
    printErrMessage(__FUNCTION__, err);

    if (device_extension_count > 0) {
        uint32_t i;
        VkExtensionProperties *device_extensions = malloc(sizeof(VkExtensionProperties) * device_extension_count);
        err = fn_vkEnumerateDeviceExtensionProperties(demo->gpu, NULL, &device_extension_count, device_extensions);
        printErrMessage(__FUNCTION__, err);

        for (i = 0; i < device_extension_count; i++) {
            if (!strcmp(VK_KHR_SWAPCHAIN_EXTENSION_NAME,
                        device_extensions[i].extensionName)) {
                swapchainExtFound = 1;
                demo->extension_names[demo->enabled_extension_count++] =
                VK_KHR_SWAPCHAIN_EXTENSION_NAME;
            }
        }

        free(device_extensions);
    }

    if (!swapchainExtFound) {
        ERR_EXIT("vkEnumerateDeviceExtensionProperties failed to find "
                "the " VK_KHR_SWAPCHAIN_EXTENSION_NAME
                " extension.\n\nDo you have a compatible "
                "Vulkan installable client driver (ICD) installed?\nPlease "
                "look at the Getting Started guide for additional "
                "information.\n",
                "vkCreateInstance Failure");
    }

    if (demo->validate) {
        demo->CreateDebugReportCallback = (PFN_vkCreateDebugReportCallbackEXT)fn_vkGetInstanceProcAddr(demo->inst, "vkCreateDebugReportCallbackEXT");
        demo->DestroyDebugReportCallback = (PFN_vkDestroyDebugReportCallbackEXT)fn_vkGetInstanceProcAddr(demo->inst, "vkDestroyDebugReportCallbackEXT");
        if (!demo->CreateDebugReportCallback)
            ERR_EXIT("GetProcAddr: Unable to find vkCreateDebugReportCallbackEXT\n", "vkGetProcAddr Failure");

        if (!demo->DestroyDebugReportCallback)
            ERR_EXIT("GetProcAddr: Unable to find vkDestroyDebugReportCallbackEXT\n", "vkGetProcAddr Failure");

        demo->DebugReportMessage = (PFN_vkDebugReportMessageEXT)fn_vkGetInstanceProcAddr(demo->inst, "vkDebugReportMessageEXT");
        if (!demo->DebugReportMessage)
            ERR_EXIT("GetProcAddr: Unable to find vkDebugReportMessageEXT\n", "vkGetProcAddr Failure");

        VkDebugReportCallbackCreateInfoEXT dbgCreateInfo;
        dbgCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
        dbgCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
        dbgCreateInfo.pfnCallback = dbgFunc;
        dbgCreateInfo.pUserData = NULL;
        dbgCreateInfo.pNext = NULL;
        err = demo->CreateDebugReportCallback(demo->inst, &dbgCreateInfo, NULL, &demo->msg_callback);
        switch (err) {
        case VK_SUCCESS:
            break;
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            ERR_EXIT("CreateDebugReportCallback: out of host memory\n", "CreateDebugReportCallback Failure");
            break;
        default:
            ERR_EXIT("CreateDebugReportCallback: unknown failure\n", "CreateDebugReportCallback Failure");
            break;
        }
    }

    GET_INSTANCE_PROC_ADDR(demo->inst, GetPhysicalDeviceSurfaceCapabilitiesKHR);
    GET_INSTANCE_PROC_ADDR(demo->inst, GetPhysicalDeviceSurfaceFormatsKHR);
    GET_INSTANCE_PROC_ADDR(demo->inst, GetPhysicalDeviceSurfacePresentModesKHR);
    GET_INSTANCE_PROC_ADDR(demo->inst, GetPhysicalDeviceSurfaceSupportKHR);
    GET_INSTANCE_PROC_ADDR(demo->inst, CreateSwapchainKHR);
    GET_INSTANCE_PROC_ADDR(demo->inst, DestroySwapchainKHR);
    GET_INSTANCE_PROC_ADDR(demo->inst, GetSwapchainImagesKHR);
    GET_INSTANCE_PROC_ADDR(demo->inst, AcquireNextImageKHR);
    GET_INSTANCE_PROC_ADDR(demo->inst, QueuePresentKHR);

    /* Returns properties of a physical device */
    fn_vkGetPhysicalDeviceProperties(demo->gpu, &demo->gpu_props);

    /* Reports properties of the queues of the specified physical device */
    fn_vkGetPhysicalDeviceQueueFamilyProperties(demo->gpu, &demo->queue_count, NULL);

    /* Reports properties of the queues of the specified physical device */
    demo->queue_props = (VkQueueFamilyProperties *)malloc(demo->queue_count * sizeof(VkQueueFamilyProperties));
    fn_vkGetPhysicalDeviceQueueFamilyProperties(demo->gpu, &demo->queue_count, demo->queue_props);

    /* Reports capabilities of a physical device */
    VkPhysicalDeviceFeatures features;
    fn_vkGetPhysicalDeviceFeatures(demo->gpu, &features);
}

/**
 * @testcase        utc_SDL_Vulkan_GetInstanceExtension_p
 * @since_tizen     3.0
 * @description     testcase for check normal inputs
 */
int utc_SDL_Vulkan_GetInstanceExtensions_p(void)
{
    SDL_bool ret;
    if (is_supported) {
        ret = SDL_Vulkan_GetInstanceExtensions(tcData.sdl_window, &(tcData.enabled_extension_count), NULL);
        assert_eq(ret, SDL_TRUE);
    }
    else {
        FPRINTF("Vulkan is not supported.");
        return 0;
    }

   return 0;
}

/**
 * @testcase        utc_SDL_Vulkan_GetInstanceExtension_p2
 * @since_tizen     3.0
 * @description     testcase for check normal inputs
 */
int utc_SDL_Vulkan_GetInstanceExtensions_p2(void)
{
     SDL_bool ret;
    if (is_supported) {
        ret = SDL_Vulkan_GetInstanceExtensions(tcData.sdl_window, &(tcData.enabled_extension_count), NULL);
        assert_eq(ret, SDL_TRUE);
        ret = SDL_Vulkan_GetInstanceExtensions(tcData.sdl_window, &(tcData.enabled_extension_count), tcData.extension_names);
        assert_eq(ret, SDL_TRUE);
    }
    else {
        FPRINTF("Vulkan is not supported.");
        return 0;
    }

   return 0;
}

/**
 * @testcase        utc_SDL_Vulkan_GetInstanceExtension_n
 * @since_tizen     3.0
 * @description     testcase for check invalid input
 *                  (SDL_Window* window : NULL, unsigned int* count : NULL, char** names : NULL)
 */
int utc_SDL_Vulkan_GetInstanceExtensions_n(void)
{
    SDL_bool ret;
    if (is_supported) {
        ret = SDL_Vulkan_GetInstanceExtensions(NULL, NULL, NULL);
        assert_eq(ret, SDL_FALSE);
    }
    else {
        FPRINTF("Vulkan is not supported.");
        return 0;
    }

    return 0;
}

/**
 * @testcase        utc_SDL_Vulkan_GetInstanceExtension_n2
 * @since_tizen     3.0
 * @description     testcase for check invalid input
 *                  (SDL_Window* window : valid, unsigned int* count : NULL, char** names : NULL)
 */
int utc_SDL_Vulkan_GetInstanceExtensions_n2(void)
{
    SDL_bool ret;
    if (is_supported) {
        ret = SDL_Vulkan_GetInstanceExtensions(tcData.sdl_window, NULL, NULL);
        assert_eq(ret, SDL_FALSE);
    }
    else {
        FPRINTF("Vulkan is not supported.");
        return 0;
    }

    return 0;
}

/**
 * @testcase        utc_SDL_Vulkan_GetInstanceExtension_n3
 * @since_tizen     3.0
 * @description     testcase for check invalid input
 *                  (SDL_Window* window : valid, unsigned int* count : NULL, char** names : valid)
 */
int utc_SDL_Vulkan_GetInstanceExtensions_n3(void)
{
    SDL_bool ret;
    if (is_supported) {
        ret = SDL_Vulkan_GetInstanceExtensions(tcData.sdl_window, NULL, tcData.extension_names);
        assert_eq(ret, SDL_FALSE);
    }
    else {
        FPRINTF("Vulkan is not supported.");
        return 0;
    }

    return 0;
}

/**
 * @testcase        utc_SDL_Vulkan_CreateSurface_p
 * @since_tizen     3.0
 * @description     testcase for check normal inputs
 */
int utc_SDL_Vulkan_CreateSurface_p(void)
{
    SDL_bool ret;
    if (is_supported) {
        demo_init_vk(&tcData);
        ret = SDL_Vulkan_CreateSurface(tcData.sdl_window, (SDL_vulkanInstance)tcData.inst, (SDL_vulkanSurface*)&tcData.surface);
        assert_eq(ret, SDL_TRUE);
    }
    else {
        FPRINTF("Vulkan is not supported.");
        return 0;
    }

    return 0;
}

/**
 * @testcase        utc_SDL_Vulkan_CreateSurface_n
 * @since_tizen     3.0
 * @description     testcase for check invalid input
 *                  (SDL_Window* window : NULL, SDL_vulkanInstance instance : NULL, SDL_vulkanSurface* surface : NULL)
 */
int utc_SDL_Vulkan_CreateSurface_n(void)
{
    SDL_bool ret;
    if (is_supported) {
        demo_init_vk(&tcData);
        ret = SDL_Vulkan_CreateSurface(NULL, NULL, NULL);
        assert_eq(ret, SDL_FALSE);
    }
    else {
        FPRINTF("Vulkan is not supported.");
        return 0;
    }

    return 0;
}

/**
 * @testcase        utc_SDL_Vulkan_CreateSurface_n2
 * @since_tizen     3.0
 * @description     testcase for check invalid input
 *                  (SDL_Window* window : valid, SDL_vulkanInstance instance : NULL, SDL_vulkanSurface* surface : NULL)
 */
int utc_SDL_Vulkan_CreateSurface_n2(void)
{
    SDL_bool ret;
    if (is_supported) {
        demo_init_vk(&tcData);
        ret = SDL_Vulkan_CreateSurface(tcData.sdl_window, NULL, NULL);
        assert_eq(ret, SDL_FALSE);
    }
    else {
        FPRINTF("Vulkan is not supported.");
        return 0;
    }

    return 0;
}

/**
 * @testcase        utc_SDL_Vulkan_CreateSurface_n3
 * @since_tizen     3.0
 * @description     testcase for check invalid input
 *                  (SDL_Window* window : valid, SDL_vulkanInstance instance : valid, SDL_vulkanSurface* surface : NULL)
 */
int utc_SDL_Vulkan_CreateSurface_n3(void)
{
    SDL_bool ret;
    if (is_supported) {
        demo_init_vk(&tcData);
        ret = SDL_Vulkan_CreateSurface(tcData.sdl_window, (SDL_vulkanInstance)tcData.inst, NULL);
        assert_eq(ret, SDL_FALSE);
    }
    else {
        FPRINTF("Vulkan is not supported.");
        return 0;
    }

    return 0;
}

/**
 * @testcase        utc_SDL_Vulkan_CreateSurface_n4
 * @since_tizen     3.0
 * @description     testcase for check invalid input
 *                  (SDL_Window* window : valid, SDL_vulkanInstance instance : NULL, SDL_vulkanSurface* surface : valid)
 */
int utc_SDL_Vulkan_CreateSurface_n4(void)
{
    SDL_bool ret;
    if (is_supported) {
        demo_init_vk(&tcData);
        ret = SDL_Vulkan_CreateSurface(tcData.sdl_window, NULL, (SDL_vulkanSurface*)&tcData.surface);
        assert_eq(ret, SDL_FALSE);
    }
    else {
        FPRINTF("Vulkan is not supported.");
        return 0;
    }

    return 0;
}
