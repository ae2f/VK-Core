#include <vulkan/vulkan_core.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

VkResult s_vkres = VK_SUCCESS;

static VkApplicationInfo	s_vkapp;
static VkInstanceCreateInfo	s_vkcreat;
static VkInstance		s_vulkan;

static VkPhysicalDevice*		sp_vkphydev;
#define vkphydev			(*sp_vkphydev)

static uint32_t				s_vkphydevcount = 0;
static VkPhysicalDeviceMemoryProperties	s_vkphydevmemprops;

static VkDevice			s_vkdev;
static VkDeviceCreateInfo	s_vkdevcreat;
static VkQueue			s_vkqueue;

static uint32_t find_queue_family(VkPhysicalDevice phydev) {
        uint32_t queueFamilyCount = 0;

        union {
                void*   v;
                VkQueueFamilyProperties* p;
        } queueFamilies; 
        uint32_t queueFamilyIndex = UINT32_MAX;

        vkGetPhysicalDeviceQueueFamilyProperties(
                        phydev
                        , &queueFamilyCount
                        , NULL
                        );
 
                        
        queueFamilies.v = malloc((size_t)(queueFamilyCount * sizeof(VkQueueFamilyProperties)));

        vkGetPhysicalDeviceQueueFamilyProperties(
                        phydev
                        , &queueFamilyCount
                        , queueFamilies.p
                        );

	{
		uint32_t i = queueFamilyCount;
		while (i--) {
			if (queueFamilies.p[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				queueFamilyIndex = i;
				break;
			}
		}
	}
	free(queueFamilies.v);
	return queueFamilyIndex;
}

static void Test_VkInit(void) {
	uint32_t queueFamilyIndex;
	float queuePriority;
	VkDeviceQueueCreateInfo queueCreateInfo;
	const char* instanceExtensions[] = {
		"VK_KHR_surface",
		"VK_EXT_headless_surface"
	};

	s_vkdev = VK_NULL_HANDLE;
	s_vulkan = 0;
	s_vkphydevcount = 0;
	sp_vkphydev = NULL;

	memset(&s_vkphydevmemprops, 0, sizeof(s_vkphydevmemprops));
	memset(&s_vkdevcreat, 0, sizeof(s_vkdevcreat));
	memset(&s_vkcreat, 0, sizeof(s_vkcreat));

	s_vkapp.apiVersion = VK_MAKE_VERSION(1, 0, 0);
	s_vkapp.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	s_vkapp.pApplicationName = "ae2f_vktest";
	s_vkapp.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	s_vkapp.pNext = NULL;
	s_vkapp.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	s_vkapp.pEngineName = "ae2f_vktest_engine";

	s_vkcreat.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	s_vkcreat.enabledExtensionCount = sizeof(instanceExtensions) / sizeof(instanceExtensions[0]);
	s_vkcreat.enabledLayerCount = 0;
	s_vkcreat.ppEnabledExtensionNames = instanceExtensions;
	s_vkcreat.ppEnabledLayerNames = 0;
	s_vkcreat.flags = 0;
	s_vkcreat.pApplicationInfo = &s_vkapp;

	s_vkres = vkCreateInstance(&s_vkcreat, 0, &s_vulkan);
	printf("vkCreateInstance result: %d\n", s_vkres);
	assert(vkres == VK_SUCCESS && "vkCreateInstance has failed");
	assert(s_vulkan);


	s_vkres = vkEnumeratePhysicalDevices(
			s_vulkan
			, &s_vkphydevcount
			, NULL
			);

	assert(vkres == VK_SUCCESS);
	assert(vkphydevcount && "vkphydevcount must be greater than 0.");

	printf("Number of Physical Device available: %u\n", s_vkphydevcount);

	sp_vkphydev = malloc((size_t)(sizeof(VkPhysicalDevice) * s_vkphydevcount));
	assert(p_vkphydev);

	s_vkres = vkEnumeratePhysicalDevices(
			s_vulkan
			, &s_vkphydevcount
			, sp_vkphydev
			);

	assert(vkres == VK_SUCCESS || vkres == VK_INCOMPLETE && "vkEnumeratePhysicalDevices has failed.");
	assert(vkphydev && "vkphydev is no initialised");

	s_vkdevcreat.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	/** Find a queue family */
	queueFamilyIndex = find_queue_family(vkphydev);
	assert(queueFamilyIndex != UINT32_MAX && "No suitable queue family found");

	/* Initialize VkDeviceQueueCreateInfo */
	queuePriority = 1.0f;
	memset(&queueCreateInfo, 0, sizeof(queueCreateInfo));

	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
	queueCreateInfo.queueCount = 1;
	queueCreateInfo.pQueuePriorities = &queuePriority;

	/* Initialize VkDeviceCreateInfo */
	s_vkdevcreat.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	s_vkdevcreat.queueCreateInfoCount = 1;
	s_vkdevcreat.pQueueCreateInfos = &queueCreateInfo;
	s_vkdevcreat.enabledExtensionCount = 0;
	s_vkdevcreat.ppEnabledExtensionNames = NULL;
	s_vkdevcreat.enabledLayerCount = 0;
	s_vkdevcreat.ppEnabledLayerNames = NULL;
	s_vkdevcreat.flags = 0;

	s_vkres = vkCreateDevice(
			vkphydev
			, &s_vkdevcreat
			, 0
			, &s_vkdev
			);

	vkGetDeviceQueue(
			s_vkdev
			, queueFamilyIndex
			, 0
			, &s_vkqueue
			);

	assert(vkres == VK_SUCCESS && "vkCreateDevice has failed.");
	assert(vkdev == VK_NULL_HANDLE && "vkdev is not initialised");

	vkGetPhysicalDeviceMemoryProperties(
			vkphydev
			, &s_vkphydevmemprops
			);

	puts("Test_VkInit has done.");
}

static void Test_VkEnd(void) {
	if(s_vkdev)	vkDestroyDevice(s_vkdev, 0);
	if(s_vulkan)	vkDestroyInstance(s_vulkan, 0);
	free(sp_vkphydev);
}
