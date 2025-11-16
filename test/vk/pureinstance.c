/*
 * headless_vk_instance_simple.c
 * Uses standard vulkan.h with macros — works perfectly on headless systems.
 */

#if 1
#include <vulkan/vulkan.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	uint32_t device_count = 0;
	uint32_t i = 0;

	VkPhysicalDevice* devices;


	VkApplicationInfo app_info;

	VkInstanceCreateInfo create_info;
	VkInstance instance;

	VkResult res; 

	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pApplicationName = "HeadlessTest";
	app_info.applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
	app_info.pEngineName = "NoEngine";
	app_info.engineVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
	app_info.apiVersion = VK_API_VERSION_1_3;

	create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	create_info.pApplicationInfo = &app_info;
	create_info.enabledLayerCount = 0;
	create_info.ppEnabledLayerNames = NULL;
	create_info.enabledExtensionCount = 0;
	create_info.ppEnabledExtensionNames = NULL;

	res = vkCreateInstance(&create_info, NULL, &instance);



	if (res != VK_SUCCESS) {
		fprintf(stderr, "Failed to create instance: %d\n", res);
		return EXIT_FAILURE;
	}
	printf("Vulkan instance created (headless OK).\n");

	vkEnumeratePhysicalDevices(instance, &device_count, NULL);
	if (device_count == 0) {
		fprintf(stderr, "No physical devices found.\n");
		vkDestroyInstance(instance, NULL);
		return EXIT_FAILURE;
	}

	printf("Found %u physical device(s).\n", device_count);

	devices = malloc((size_t)(device_count * sizeof(VkPhysicalDevice)));
	vkEnumeratePhysicalDevices(instance, &device_count, devices);

	for (i = 0; i < device_count; ++i) {
		VkPhysicalDeviceProperties props;
		vkGetPhysicalDeviceProperties(devices[i], &props);
		printf("  [%u] %s\n", i, props.deviceName);
	}
	free(devices);

	vkDestroyInstance(instance, NULL);
	printf("Instance destroyed.\n");

	return EXIT_SUCCESS;
}
#else
int main(void) {
	return 0;
}
#endif
