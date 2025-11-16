/*
 * headless_vk_instance_simple.c
 * Uses standard vulkan.h with macros — works perfectly on headless systems.
 */

#include <vulkan/vulkan.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	uint32_t device_count = 0;
	uint32_t i = 0;


	VkApplicationInfo app_info = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = "HeadlessTest",
		.applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0),
		.pEngineName = "NoEngine",
		.engineVersion = VK_MAKE_API_VERSION(0, 1, 0, 0),
		.apiVersion = VK_API_VERSION_1_3
	};

	VkInstanceCreateInfo create_info = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &app_info,
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = NULL,
		.enabledExtensionCount = 0,
		.ppEnabledExtensionNames = NULL
	};

	VkInstance instance;
	VkResult res = vkCreateInstance(&create_info, NULL, &instance);
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

	VkPhysicalDevice* devices = malloc(device_count * sizeof(VkPhysicalDevice));
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
