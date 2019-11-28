/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vkVulkanMethods.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:55:17 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/27 14:08:56 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vkClassContainer.hpp"

namespace InstanceLayersExtensions
{
	std::vector<const char *> ppDesiredLayers =
	{
		//"VK_LAYER_LUNARG_api_dump",
		//"VK_LAYER_LUNARG_core_validation",
		//"VK_LAYER_KHRONOS_validation",
		//"VK_LAYER_LUNARG_object_tracker",
		//"VK_LAYER_LUNARG_standard_validation",
		//"VK_LAYER_LUNARG_parameter_validation",
		//"VK_LAYER_GOOGLE_threading",
		//"VK_LAYER_GOOGLE_unique_objects"
	};
	std::vector<const char *> ppDesiredExtensions =
	{
		"VK_KHR_surface",
		"VK_EXT_debug_utils",
		"VK_MVK_macos_surface",
		"VK_EXT_swapchain_colorspace",
		"VK_KHR_get_surface_capabilities2",
		"VK_KHR_get_physical_device_properties2",
		"VK_KHR_device_group_creation",
		"VK_KHR_device_group_creation",
		"VK_KHR_get_physical_device_properties2",
		"VK_KHR_get_surface_capabilities2",
		"VK_KHR_surface",
		"VK_EXT_debug_report",
		"VK_EXT_debug_utils",
		"VK_EXT_swapchain_colorspace",
		"VK_MVK_macos_surface",
		"VK_KHR_16bit_storage",
		"VK_KHR_8bit_storage",
		"VK_KHR_bind_memory2",
		"VK_KHR_dedicated_allocation",
		"VK_KHR_descriptor_update_template",
		"VK_KHR_device_group",
		"VK_KHR_get_memory_requirements2",
		"VK_KHR_image_format_list",
		"VK_KHR_maintenance1",
		"VK_KHR_maintenance2",
		"VK_KHR_maintenance3",
		"VK_KHR_push_descriptor",
		"VK_KHR_relaxed_block_layout",
		"VK_KHR_sampler_mirror_clamp_to_edge",
		"VK_KHR_shader_draw_parameters",
		"VK_KHR_shader_float16_int8",
		"VK_KHR_storage_buffer_storage_class",
		"VK_KHR_swapchain",
		"VK_KHR_swapchain_mutable_format",
		"VK_KHR_uniform_buffer_standard_layout",
		"VK_KHR_variable_pointers",
		"VK_EXT_debug_marker",
		"VK_EXT_host_query_reset",
		"VK_EXT_scalar_block_layout",
		"VK_EXT_shader_viewport_index_layer",
		"VK_EXT_vertex_attribute_divisor",
		"VK_EXTX_portability_subset",
		"VK_AMD_gpu_shader_half_float",
		"VK_AMD_negative_viewport_height",
		"VK_INTEL_shader_integer_functions2",
		"VK_NV_glsl_shader",
	};
};

namespace PhysicalDeviceLayersExtensions
{
	std::vector<const char *> ppDesiredLayers =
	{
	};
	std::vector<const char *> ppDesiredExtensions =
	{
	};
}

void Vulkan::run(GLFWwindow *pWindow)
{
	vkSetupAppInfo();
	vkSetupInstanceLayers();
	vkSetupInstanceExtensions();
	vkSetupInstanceCreateInfo();
	vkCreateInstanceObj();

	vkCreateSurface(pWindow);

	vkChoosePhysicalDeviceObj();
	vkCheckSwapChainSupport();
	vkSetupPhysicalDeviceExtensions();
	vkSetupPhysicalDeviceLayers();
	vkQueryPhysicalDeviceQueue();

	vkSetupDeviceQueueCreateInfo(1.0f);
	vkSetupDeviceCreateInfo();
	vkCreateNewDevice();

	vkSetupSwapChain();
	vkSetupSwapChainCreateInfo();
	vkCreateSwapChain();

	vkCreateNewImageView();

	vkCreateNewRenderPass();
	vkCreateNewGraphicsPipeline();

	vkCreateNewFrameBuffer();

	vkCreateNewCommandPool();

	vkCreateNewCommandBuffers();

	vkCreateNewSemaphore();

	fbCleanUp();
}

void Vulkan::vkSetupAppInfo()
{
	instanceProperties.sAppCreateInfo.sType					= VK_STRUCTURE_TYPE_APPLICATION_INFO;
	instanceProperties.sAppCreateInfo.pApplicationName		= "VulkanLearn";
	instanceProperties.sAppCreateInfo.applicationVersion	= VK_MAKE_VERSION(1, 0, 0);
	instanceProperties.sAppCreateInfo.pEngineName			= "NoEngine";
	instanceProperties.sAppCreateInfo.engineVersion			= VK_MAKE_VERSION(1, 0, 0);
	instanceProperties.sAppCreateInfo.apiVersion			= VK_API_VERSION_1_1;
	instanceProperties.sAppCreateInfo.pNext					= nullptr;
}

void Vulkan::vkSetupInstanceLayers()
{
	vkEnumerateInstanceLayerProperties(&instanceProperties.availableInstanceLayersCount, nullptr);
	instanceProperties.pAvailableInstanceLayers.resize(instanceProperties.availableInstanceLayersCount);
	instanceProperties.ppAvailableInstanceLayersNames.resize(instanceProperties.availableInstanceLayersCount);
	vkEnumerateInstanceLayerProperties(&instanceProperties.availableInstanceLayersCount, instanceProperties.pAvailableInstanceLayers.data());
	for (int i = 0, j = 0; i < instanceProperties.availableInstanceLayersCount; ++i)
	{
		if (vkIsLayerSuitable(instanceProperties.pAvailableInstanceLayers[i]))
		{
			instanceProperties.ppAvailableInstanceLayersNames[j++] = instanceProperties.pAvailableInstanceLayers[i].layerName;
			++instanceProperties.selectedInstanceLayersCount;
		}
	}
}

bool Vulkan::vkIsLayerSuitable(VkLayerProperties sLayer)
{
	for (int i = 0; i < InstanceLayersExtensions::ppDesiredLayers.size(); ++i)
		if (!strcmp(InstanceLayersExtensions::ppDesiredLayers[i], sLayer.layerName))
			return (true);
	for (int i = 0; i < PhysicalDeviceLayersExtensions::ppDesiredLayers.size(); ++i)
		if (!strcmp(PhysicalDeviceLayersExtensions::ppDesiredLayers[i], sLayer.layerName))
			return (true);
	return (false);
}

void Vulkan::vkSetupInstanceExtensions()
{
	vkEnumerateInstanceExtensionProperties(nullptr, &instanceProperties.availableInstanceExtensionsCount, nullptr);
	instanceProperties.pAvailableInstanceExtensions.resize(instanceProperties.availableInstanceExtensionsCount);
	instanceProperties.ppAvailableInstanceExtensionsNames.resize(instanceProperties.availableInstanceExtensionsCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &instanceProperties.availableInstanceExtensionsCount, instanceProperties.pAvailableInstanceExtensions.data());
	for (int i = 0, j = 0; i < instanceProperties.availableInstanceExtensionsCount; ++i)
	{
		if (vkIsExtensionSuitable(instanceProperties.pAvailableInstanceExtensions[i]))
		{
			instanceProperties.ppAvailableInstanceExtensionsNames[j++] = instanceProperties.pAvailableInstanceExtensions[i].extensionName;
			++instanceProperties.selectedInstanceExtensionsCount;
		}
	}
}

bool Vulkan::vkIsExtensionSuitable(VkExtensionProperties sExtension)
{
	for (int i = 0; i < InstanceLayersExtensions::ppDesiredExtensions.size(); ++i)
		if (!strcmp(InstanceLayersExtensions::ppDesiredExtensions[i], sExtension.extensionName))
			return (true);
	for (int i = 0; i < PhysicalDeviceLayersExtensions::ppDesiredExtensions.size(); ++i)
		if (!strcmp(PhysicalDeviceLayersExtensions::ppDesiredExtensions[i], sExtension.extensionName))
			return (true);
	return (false);
}

void Vulkan::vkSetupInstanceCreateInfo()
{
	instanceProperties.sInstanceCreateInfo.sType					= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceProperties.sInstanceCreateInfo.flags					= 0;
	instanceProperties.sInstanceCreateInfo.pNext 					= nullptr;
	instanceProperties.sInstanceCreateInfo.pApplicationInfo			= &instanceProperties.sAppCreateInfo;
	instanceProperties.sInstanceCreateInfo.enabledLayerCount		= instanceProperties.selectedInstanceLayersCount;
	instanceProperties.sInstanceCreateInfo.ppEnabledLayerNames		= instanceProperties.ppAvailableInstanceLayersNames.data();
	instanceProperties.sInstanceCreateInfo.enabledExtensionCount	= instanceProperties.selectedInstanceExtensionsCount;
	instanceProperties.sInstanceCreateInfo.ppEnabledExtensionNames	= instanceProperties.ppAvailableInstanceExtensionsNames.data();
}

void Vulkan::vkCreateInstanceObj()
{
	if ((error = vkCreateInstance(&instanceProperties.sInstanceCreateInfo, nullptr, &instanceProperties.instanceObject)) != VK_SUCCESS)
	{
		std::cout << "Error occured: " << error << std::endl;
		throw std::runtime_error(nullptr);
	}
}

void Vulkan::vkCreateSurface(GLFWwindow *pWindow)
{
	if ((error = glfwCreateWindowSurface(instanceProperties.instanceObject, pWindow, nullptr, &surfaceObj)))
	{
		std::cout << "Code of error: " << error << std::endl;
		throw std::runtime_error("Failed to create window surface");
	}
}

void Vulkan::vkChoosePhysicalDeviceObj()
{
	vkEnumeratePhysicalDevices(instanceProperties.instanceObject, &availablePhysicalDeviceCount, nullptr);
	pAvailablePhysicalDevices = (VkPhysicalDevice *)malloc(sizeof(VkPhysicalDevice) * availablePhysicalDeviceCount);
	vkEnumeratePhysicalDevices(instanceProperties.instanceObject, &availablePhysicalDeviceCount, pAvailablePhysicalDevices);
	for (int i = 0; i < availablePhysicalDeviceCount; ++i)
	{
		if (vkIsDeviceSuitable(pAvailablePhysicalDevices[i]))
		{
			physicalDeviceObj = pAvailablePhysicalDevices[i];
			break;
		}
	}
	if (physicalDeviceObj == VK_NULL_HANDLE)
		throw std::runtime_error("Failed suit GPU");
}

bool Vulkan::vkIsDeviceSuitable(VkPhysicalDevice physicalDevice)
{
	vkGetPhysicalDeviceFeatures		(physicalDevice, &sPhysicalDeviceFeatures);
	vkGetPhysicalDeviceProperties	(physicalDevice, &sPhysicalDeviceProperties);
	return (sPhysicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
}

void Vulkan::vkCheckSwapChainSupport()
{
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDeviceObj, surfaceObj, &capabilities);
	vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDeviceObj, surfaceObj, &khrFormatsCount, nullptr);
	pKHRFormats = (VkSurfaceFormatKHR *)malloc(sizeof(VkSurfaceFormatKHR) * khrFormatsCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDeviceObj, surfaceObj, &khrFormatsCount, pKHRFormats);
	vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDeviceObj, surfaceObj, &khrPresentModesCount, nullptr);
	pKHRPresentModes = (VkPresentModeKHR *)malloc(sizeof(VkPresentModeKHR) * khrPresentModesCount);
	vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDeviceObj, surfaceObj, &khrPresentModesCount , pKHRPresentModes);
	if (!khrFormatsCount or !khrPresentModesCount)
		throw std::runtime_error("Failed to setup swap chain extension");
}

void Vulkan::vkSetupPhysicalDeviceLayers()
{
	vkEnumerateDeviceLayerProperties(physicalDeviceObj, &availablePhysicalDeviceLayersCount, nullptr);
	pAvailablePhysicalDeviceLayers = (VkLayerProperties *)malloc(sizeof(VkLayerProperties) * availablePhysicalDeviceLayersCount);
	ppAvailablePhysicalDeviceLayersNames = (const char **)malloc(sizeof(const char *) * availablePhysicalDeviceLayersCount);
	vkEnumerateDeviceLayerProperties(physicalDeviceObj, &availablePhysicalDeviceLayersCount, pAvailablePhysicalDeviceLayers);
	for (int i = 0, j = 0; i < availablePhysicalDeviceLayersCount; ++i)
	{
		if (vkIsLayerSuitable(pAvailablePhysicalDeviceLayers[i]))
		{
			++selectedPhysicalDeviceLayersCount;
			ppAvailablePhysicalDeviceLayersNames[j++] = pAvailablePhysicalDeviceLayers[i].layerName;
		}
	}
}

void Vulkan::vkSetupPhysicalDeviceExtensions()
{
	vkEnumerateDeviceExtensionProperties(physicalDeviceObj, nullptr, &availablePhysicalDeviceExtensionsCount, nullptr);
	pAvailablePhysicalDeviceExtensions = (VkExtensionProperties *)malloc(sizeof(VkExtensionProperties) * availablePhysicalDeviceExtensionsCount);
	ppAvailablePhysicalDeviceExtensionsNames = (const char **)malloc(sizeof(const char *) * availablePhysicalDeviceExtensionsCount);
	vkEnumerateDeviceExtensionProperties(physicalDeviceObj, nullptr, &availablePhysicalDeviceExtensionsCount, pAvailablePhysicalDeviceExtensions);
	for (int i = 0, j = 0; i < availablePhysicalDeviceExtensionsCount; ++i)
	{
		if (vkIsExtensionSuitable(pAvailablePhysicalDeviceExtensions[i]))
		{
			++selectedPhysicalDeviceExtensionsCount;
			ppAvailablePhysicalDeviceExtensionsNames[j++] = pAvailablePhysicalDeviceExtensions[i].extensionName;
			std::cout << pAvailablePhysicalDeviceExtensions[i].extensionName << "\n";
		}
	}
}

void Vulkan::vkQueryPhysicalDeviceQueue()
{
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDeviceObj, 	&availablePhysicalDeviceQueuesCount, nullptr);
	pAvailablePhysicalDeviceQueuesFamily = (VkQueueFamilyProperties *)malloc(sizeof(VkQueueFamilyProperties) * availablePhysicalDeviceQueuesCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDeviceObj, &availablePhysicalDeviceQueuesCount, pAvailablePhysicalDeviceQueuesFamily);
	for (int i = 0; i < availablePhysicalDeviceQueuesCount and (graphicQueueFamilyIndex < 0 or presentQueueFamilyIndex < 0 or graphicQueueFamilyIndex == presentQueueFamilyIndex); ++i)
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalDeviceObj, i, surfaceObj, &presentQueueFamilySupport);
		if (pAvailablePhysicalDeviceQueuesFamily[i].queueCount > 0)
		{
			if ((pAvailablePhysicalDeviceQueuesFamily[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) and graphicQueueFamilyIndex < 0)
				graphicQueueFamilyIndex = i;
			if (presentQueueFamilySupport)
				presentQueueFamilyIndex = i;
		}
	}
	if (graphicQueueFamilyIndex < 0 or presentQueueFamilyIndex < 0)
		throw std::runtime_error("Failed to find physical queue for gpu");
}

void Vulkan::vkSetupDeviceQueueCreateInfo(float queuePriority)
{
	sDeviceGraphicQueueFamilyCreateInfo.sType				= VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	sDeviceGraphicQueueFamilyCreateInfo.pNext				= nullptr;
	sDeviceGraphicQueueFamilyCreateInfo.flags				= 0;
	sDeviceGraphicQueueFamilyCreateInfo.queueCount			= 1;
	sDeviceGraphicQueueFamilyCreateInfo.queueFamilyIndex	= graphicQueueFamilyIndex;
	sDeviceGraphicQueueFamilyCreateInfo.pQueuePriorities	= &queuePriority;
	++deviceQueueFamilyCreateInfoCount;

	sDevicePresentQeueuFamilyCreateInfo.sType				= VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	sDevicePresentQeueuFamilyCreateInfo.pNext				= nullptr;
	sDevicePresentQeueuFamilyCreateInfo.flags				= 0;
	sDevicePresentQeueuFamilyCreateInfo.queueCount			= 1;
	sDevicePresentQeueuFamilyCreateInfo.queueFamilyIndex	= presentQueueFamilyIndex;
	sDevicePresentQeueuFamilyCreateInfo.pQueuePriorities	= &queuePriority;
	++deviceQueueFamilyCreateInfoCount;

	psDeviceQueueFamilyCreateInfoList = (VkDeviceQueueCreateInfo *)malloc(sizeof(VkDeviceQueueCreateInfo) * deviceQueueFamilyCreateInfoCount);
	psDeviceQueueFamilyCreateInfoList[0] = sDeviceGraphicQueueFamilyCreateInfo;
	psDeviceQueueFamilyCreateInfoList[1] = sDevicePresentQeueuFamilyCreateInfo;
}

void Vulkan::vkSetupDeviceCreateInfo()
{
	sCreateDeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	sCreateDeviceInfo.flags = 0;
	sCreateDeviceInfo.pNext = nullptr;
	sCreateDeviceInfo.pEnabledFeatures = &sPhysicalDeviceFeatures;
	sCreateDeviceInfo.enabledLayerCount = selectedPhysicalDeviceLayersCount;
	sCreateDeviceInfo.ppEnabledLayerNames = ppAvailablePhysicalDeviceLayersNames;
	sCreateDeviceInfo.enabledExtensionCount = selectedPhysicalDeviceExtensionsCount;
	sCreateDeviceInfo.ppEnabledExtensionNames = ppAvailablePhysicalDeviceExtensionsNames;
	sCreateDeviceInfo.pQueueCreateInfos = psDeviceQueueFamilyCreateInfoList;
	sCreateDeviceInfo.queueCreateInfoCount = deviceQueueFamilyCreateInfoCount;
}

void Vulkan::vkCreateNewDevice()
{
	if ((error = vkCreateDevice(physicalDeviceObj, &sCreateDeviceInfo, nullptr, &deviceObj)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << error << std::endl;
		throw std::runtime_error("Failed to create logical device");
	}
	vkGetDeviceQueue(deviceObj, graphicQueueFamilyIndex, 0, &graphicQueueFamily);
	vkGetDeviceQueue(deviceObj, presentQueueFamilyIndex, 0, &presentQueueFamily);
}

void Vulkan::vkSetupSwapChain()
{
	VkSurfaceFormatKHR	surfaceIter = {};
	VkPresentModeKHR	presentIter = {};
	VkBool32			found = false;

	for (int i = 0; i < khrFormatsCount; ++i)
	{
		surfaceIter = pKHRFormats[i];
		if (surfaceIter.format == VK_FORMAT_B8G8R8A8_UNORM and surfaceIter.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			sBestSwapChainFormat = surfaceIter;
			found = true;
			break;
		}
	}
	if (!found)
	{
		std::cout << "Best swap chain format has not been found" << std::endl;
		sBestSwapChainFormat = pKHRFormats[0];
	}
	found = false;
	for (int i = 0; i < khrPresentModesCount; ++i)
	{
		presentIter = pKHRPresentModes[i];
		if (presentIter == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			sBestSwapChainPresentMode = presentIter;
			found = true;
			break;
		}
		else if (presentIter == VK_PRESENT_MODE_FIFO_KHR)
		{
			sBestSwapChainPresentMode = presentIter;
			found = true;
		}
	}
	if (!found)
	{
		std::cout << "Best swap chain present mode has not been found" << std::endl;
		sBestSwapChainPresentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
	}
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
	{
		std::cout << "Standart setting\n";
		sBestSwapChainResolution = capabilities.currentExtent;
	}
	else
	{
		std::cout << "Custom setting\n";
		sBestSwapChainResolution.width = std::max(capabilities.minImageExtent.width,
		std::min(capabilities.maxImageExtent.width, sBestSwapChainResolution.width));
		sBestSwapChainResolution.height = std::max(capabilities.minImageExtent.height,
		std::min(capabilities.maxImageExtent.height, sBestSwapChainResolution.height));
	}
}

void Vulkan::vkSetupSwapChainCreateInfo()
{
	uint32_t	indexArray[2];

	indexArray[0] = graphicQueueFamilyIndex;
	indexArray[1] = presentQueueFamilyIndex;
	imageCount = capabilities.minImageCount + 1;
	if (capabilities.maxImageCount > 0 and imageCount > capabilities.maxImageCount)
	{
		std::cout << "Standart image count has been setup\n";
		imageCount = capabilities.maxImageCount;
	}
	sSwapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	sSwapChainCreateInfo.surface = surfaceObj;
	sSwapChainCreateInfo.flags = 0;
	sSwapChainCreateInfo.pNext = nullptr;
	sSwapChainCreateInfo.clipped = VK_TRUE;
	sSwapChainCreateInfo.minImageCount = imageCount;
	sSwapChainCreateInfo.imageFormat = sBestSwapChainFormat.format;
	sSwapChainCreateInfo.imageColorSpace = sBestSwapChainFormat.colorSpace;
	sSwapChainCreateInfo.imageExtent = sBestSwapChainResolution;
	sSwapChainCreateInfo.imageArrayLayers = 1;
	sSwapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	sSwapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
	sSwapChainCreateInfo.queueFamilyIndexCount = 2;
	sSwapChainCreateInfo.pQueueFamilyIndices = indexArray;
	sSwapChainCreateInfo.oldSwapchain = VK_NULL_HANDLE;
	sSwapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	sSwapChainCreateInfo.presentMode = sBestSwapChainPresentMode;
	sSwapChainCreateInfo.preTransform = capabilities.currentTransform;
}

void Vulkan::vkCreateSwapChain()
{
	if ((error = vkCreateSwapchainKHR(deviceObj, &sSwapChainCreateInfo, nullptr, &swapchainObj)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << error << std::endl;
		throw std::runtime_error("Failed to creat SwapChain");
	}
	vkGetSwapchainImagesKHR(deviceObj, swapchainObj, &imageCount, nullptr);
	pImageObjList = (VkImage *)malloc(sizeof(VkImage) * imageCount);
	vkGetSwapchainImagesKHR(deviceObj, swapchainObj, &imageCount, pImageObjList);
}

VkImageViewCreateInfo Vulkan::vkSetupImageViewCreateInfo(VkImage image)
{
	VkImageViewCreateInfo	sImageViewCreateInfo = {};

	sImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	sImageViewCreateInfo.pNext = nullptr;
	sImageViewCreateInfo.flags = 0;
	sImageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	sImageViewCreateInfo.format = sBestSwapChainFormat.format;
	sImageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
	sImageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
	sImageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
	sImageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
	sImageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	sImageViewCreateInfo.subresourceRange.baseMipLevel = 0;
	sImageViewCreateInfo.subresourceRange.levelCount = 1;
	sImageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
	sImageViewCreateInfo.subresourceRange.layerCount = 1;
	sImageViewCreateInfo.image = image;
	return (sImageViewCreateInfo);
}

void Vulkan::vkCreateNewImageView()
{
	VkImageViewCreateInfo	sImageViewCreateInfo = {};

	pImageViewList = (VkImageView *)malloc(sizeof(VkImageView) * imageCount);
	for (int i = 0; i < imageCount; ++i)
	{
		sImageViewCreateInfo = this->vkSetupImageViewCreateInfo(pImageObjList[i]);
		if ((error = vkCreateImageView(deviceObj, &sImageViewCreateInfo, nullptr, &pImageViewList[i])))
		{
			std::cout << "Code of error: " << error << std::endl;
			throw std::runtime_error("Failed to create image view object");
		}
	}
}

/*
** -----------------------------------------------------------------------------------------------------
*/

void Vulkan::vkCreateNewRenderPass()
{
	VkRenderPassCreateInfo	render				= {};
	VkAttachmentDescription	colorAttachment		= {};
	VkAttachmentReference	colorAttachmentRef	= {};
	VkSubpassDescription	subpass				= {};

	colorAttachment.format			= sBestSwapChainFormat.format;
	colorAttachment.samples			= VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp			= VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp			= VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp	= VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp	= VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout	= VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout		= VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	colorAttachmentRef.attachment	= 0;
	colorAttachmentRef.layout		= VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	subpass.pipelineBindPoint		= VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount	= 1;
	subpass.pColorAttachments		= &colorAttachmentRef;

	render.sType					= VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	render.flags					= 0;
	render.pNext					= nullptr;
	render.attachmentCount			= 1;
	render.pAttachments				= &colorAttachment;
	render.subpassCount				= 1;
	render.pSubpasses				= &subpass;

	VkSubpassDependency dependency = {};

			dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
			dependency.dstSubpass = 0;
			dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			dependency.srcAccessMask = 0;
			dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	render.dependencyCount			= 1;
	render.pDependencies			= &dependency;

	if ((error = vkCreateRenderPass(deviceObj, &render, nullptr, &renderPass)) != VK_SUCCESS)
	{
		std::cout << "Code of error " << error << std::endl;
		throw std::runtime_error("Failed to create render pass");
	}
}

VkShaderModule		Vulkan::vkCreateNewShaderModule(const std::vector<char> &code)
{
	VkShaderModule				shaderModuleObj = {};
	VkShaderModuleCreateInfo	sShaderModuleCreateInfo = {};

	sShaderModuleCreateInfo.sType		= VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	sShaderModuleCreateInfo.flags		= 0;
	sShaderModuleCreateInfo.codeSize	= code.size();
	sShaderModuleCreateInfo.pCode		= reinterpret_cast<const uint32_t *>(code.data());
	sShaderModuleCreateInfo.pNext		= nullptr;

	if ((error = vkCreateShaderModule(deviceObj, &sShaderModuleCreateInfo, nullptr, &shaderModuleObj)) != VK_SUCCESS)
	{
		std::cout << "Code of error" << error << std::endl;
		throw std::runtime_error("Failed to create shader module");
	}
	return (shaderModuleObj);
}

std::vector<char>	Vulkan::vkReadFile(const char *filename)
{
	size_t	fileSize;

	std::ifstream file(filename, std::ios::ate | std::ios::binary);
	if (!file.is_open())
		throw std::runtime_error("Failed to open file!");
	fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);
	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();
	return (buffer);
}

void Vulkan::vkCreateNewGraphicsPipeline()
{
	VkPipelineShaderStageCreateInfo sVertexShaderStageCreateInfo = {};
	VkPipelineShaderStageCreateInfo sFragmentShaderStageCreateInfo = {};

	VkPipelineVertexInputStateCreateInfo sVertexCreateInfo = {};

	VkPipelineInputAssemblyStateCreateInfo sInputAssembly = {};

	VkViewport		viewport = {};

	VkRect2D		scissor = {};

	VkPipelineViewportStateCreateInfo  viewportState = {};

	VkPipelineRasterizationStateCreateInfo rasterizer = {};

	VkPipelineMultisampleStateCreateInfo multisampling = {};

	VkPipelineDepthStencilStateCreateInfo depthStencil = {};

	VkPipelineColorBlendAttachmentState colorBlendAttachment = {};

	VkPipelineColorBlendStateCreateInfo colorBlending = {};

	VkDynamicState dynamicStates[] = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_LINE_WIDTH};

	VkPipelineDynamicStateCreateInfo dynamicState = {};

	VkPipelineLayoutCreateInfo	layoutCreateInfo = {};

	VkShaderModule		vertexModule;
	VkShaderModule		fragmentModule;

	std::vector<char>	vertexCode;
	std::vector<char>	fragmentCode;

	VkGraphicsPipelineCreateInfo	pipeline = {};

	vertexCode = this->vkReadFile("./shader_source/vert.spv");
	fragmentCode = this->vkReadFile("./shader_source/frag.spv");
	vertexModule = this->vkCreateNewShaderModule(vertexCode);
	fragmentModule = this->vkCreateNewShaderModule(fragmentCode);

	sVertexShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	sVertexShaderStageCreateInfo.flags = 0;
	sVertexShaderStageCreateInfo.pNext = nullptr;
	sVertexShaderStageCreateInfo.module = vertexModule;
	sVertexShaderStageCreateInfo.pName = "main";
	sVertexShaderStageCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	sVertexShaderStageCreateInfo.pSpecializationInfo = nullptr;

	sFragmentShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	sFragmentShaderStageCreateInfo.flags = 0;
	sFragmentShaderStageCreateInfo.pNext = nullptr;
	sFragmentShaderStageCreateInfo.module = fragmentModule;
	sFragmentShaderStageCreateInfo.pName = "main";
	sFragmentShaderStageCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	sFragmentShaderStageCreateInfo.pSpecializationInfo = nullptr;

	sVertexCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	sVertexCreateInfo.flags = 0;
	sVertexCreateInfo.pNext = nullptr;
	sVertexCreateInfo.vertexAttributeDescriptionCount = 0;
	sVertexCreateInfo.vertexBindingDescriptionCount = 0;
	sVertexCreateInfo.pVertexAttributeDescriptions = nullptr;
	sVertexCreateInfo.pVertexBindingDescriptions = nullptr;

	sInputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	sInputAssembly.pNext = nullptr;
	sInputAssembly.flags = 0;
	sInputAssembly.primitiveRestartEnable = VK_FALSE;
	sInputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.maxDepth = 1.0f;
	viewport.minDepth = 0.0f;
	viewport.width = (float)sBestSwapChainResolution.width;
	viewport.height = (float)sBestSwapChainResolution.height;

	scissor.offset = {0, 0};
	scissor.extent = sBestSwapChainResolution;

	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.flags = 0;
	viewportState.pNext = nullptr;
	viewportState.pScissors = &scissor;
	viewportState.pViewports = &viewport;
	viewportState.viewportCount = 1;
	viewportState.scissorCount = 1;

	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.flags = 0;
	rasterizer.pNext = nullptr;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;
	rasterizer.depthBiasClamp = 0.0f;
	rasterizer.depthBiasSlopeFactor = 0.0f;
	rasterizer.depthBiasConstantFactor = 0.0f;

	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.flags = 0;
	multisampling.pNext = nullptr;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	multisampling.minSampleShading = 1.0f;
	multisampling.pSampleMask = nullptr;
	multisampling.alphaToCoverageEnable = VK_FALSE;
	multisampling.alphaToOneEnable = VK_FALSE;

	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;
	colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
	colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
	colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.flags = 0;
	colorBlending.pNext = nullptr;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY;
	colorBlending.pAttachments = &colorBlendAttachment;
	colorBlending.attachmentCount = 1;
	colorBlending.blendConstants[0] = 0.0f;
	colorBlending.blendConstants[1] = 0.0f;
	colorBlending.blendConstants[2] = 0.0f;
	colorBlending.blendConstants[3] = 0.0f;

	dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.flags = 0;
	dynamicState.pNext = nullptr;
	dynamicState.dynamicStateCount = 2;
	dynamicState.pDynamicStates = dynamicStates;

	layoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	layoutCreateInfo.flags = 0;
	layoutCreateInfo.pNext = nullptr;
	layoutCreateInfo.setLayoutCount = 0;
	layoutCreateInfo.pSetLayouts = nullptr;
	layoutCreateInfo.pushConstantRangeCount = 0;
	layoutCreateInfo.pPushConstantRanges = nullptr;

	if ((error = vkCreatePipelineLayout(deviceObj, &layoutCreateInfo, nullptr, &layoutObj)) != VK_SUCCESS)
	{
		std::cout << "Code of error" << error << std::endl;
		throw std::runtime_error("Failed to create Pipeline layout");
	}

	VkPipelineShaderStageCreateInfo moduleCreateInfos[2] = {sVertexShaderStageCreateInfo, sFragmentShaderStageCreateInfo};

	pipeline.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipeline.flags = 0;
	pipeline.pNext = nullptr;
	pipeline.stageCount = 2;
	pipeline.pStages = moduleCreateInfos;
	pipeline.pVertexInputState = &sVertexCreateInfo;
	pipeline.pInputAssemblyState = &sInputAssembly;
	pipeline.pViewportState = &viewportState;
	pipeline.pRasterizationState = &rasterizer;
	pipeline.pMultisampleState = &multisampling;
	pipeline.pColorBlendState = &colorBlending;
	pipeline.pDepthStencilState = nullptr;
	pipeline.pDynamicState = &dynamicState;
	pipeline.renderPass = renderPass;
	pipeline.layout = layoutObj;
	pipeline.subpass = 0;
	pipeline.basePipelineHandle = VK_NULL_HANDLE;
	pipeline.basePipelineIndex = -1;
	pipeline.pTessellationState = nullptr;

	if ((error = vkCreateGraphicsPipelines(deviceObj, VK_NULL_HANDLE, 1, &pipeline, nullptr, &pipelineObj)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << error << std::endl;
		throw std::runtime_error("Failed to create pipeline");
	}
}

void Vulkan::vkCreateNewFrameBuffer()
{
	swapChainFrameBuffers.resize(imageCount);

	for (int i = 0; i < imageCount; ++i)
	{
		VkImageView attachments[] = { pImageViewList[i] };
		VkFramebufferCreateInfo	createInfo = {};

		createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.flags = 0;
		createInfo.renderPass = renderPass;
		createInfo.attachmentCount = 1;
		createInfo.pAttachments = attachments;
		createInfo.height = sBestSwapChainResolution.height;
		createInfo.width = sBestSwapChainResolution.width;
		createInfo.layers = 1;

		if ((error = vkCreateFramebuffer(deviceObj, &createInfo, nullptr, &swapChainFrameBuffers[i])) != VK_SUCCESS)
		{
			std::cout << "Code of error: " << error << std::endl;
			throw std::runtime_error("Failed to create on of your buffers");
		}
	}
}

void Vulkan::vkCreateNewCommandPool()
{
	VkCommandPoolCreateInfo		createInfo = {};

	createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.queueFamilyIndex = graphicQueueFamilyIndex;

	if ((error = vkCreateCommandPool(deviceObj, &createInfo, nullptr, &commandPool)))
	{
		std::cout << "Code of error: " << error << std::endl;
		throw std::runtime_error("Failed to create command pool");
	}
}

void Vulkan::vkCreateNewCommandBuffers()
{
	VkCommandBufferAllocateInfo allocInfo = {};

	commandBuffer.resize(swapChainFrameBuffers.size());
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.pNext = nullptr;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = commandPool;
	allocInfo.commandBufferCount = commandBuffer.size();

	if ((error = vkAllocateCommandBuffers(deviceObj, &allocInfo, commandBuffer.data())) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << error << std::endl;
		throw std::runtime_error("Failed to crate command buffers");
	}

	for (int i = 0; i < commandBuffer.size(); ++i)
	{
		VkCommandBufferBeginInfo beginInfo = {};

		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.pNext = nullptr;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		beginInfo.pInheritanceInfo = nullptr;

		if ((error = vkBeginCommandBuffer(commandBuffer[i], &beginInfo)) != VK_SUCCESS)
		{
			std::cout << "Code of error: " << error << std::endl;
			throw std::runtime_error("Failed to create commandBuffer");
		}
		VkRenderPassBeginInfo renderPassInfo = {};

		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.pNext = nullptr;
		renderPassInfo.renderPass = renderPass;
		renderPassInfo.framebuffer = swapChainFrameBuffers[i];
		renderPassInfo.renderArea.offset = {0, 0};
		renderPassInfo.renderArea.extent = sBestSwapChainResolution;

		VkClearValue	clearColor = {0.0f, 0.0f, 0.0f, 1.0f};

		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(commandBuffer[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		vkCmdBindPipeline(commandBuffer[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineObj);
		vkCmdDraw(commandBuffer[i], 3, 1, 0, 0);
		vkCmdEndRenderPass(commandBuffer[i]);

		if ((error = vkEndCommandBuffer(commandBuffer[i])) != VK_SUCCESS)
		{
			std::cout << "Code of error: " << error << std::endl;
			throw std::runtime_error("Failed to end command buffer");
		}
	}
}

void Vulkan::vkCreateNewSemaphore()
{
	VkSemaphoreCreateInfo createInfo = {};

	createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;

	if ((error = vkCreateSemaphore(deviceObj, &createInfo, nullptr, &renderFinishedSemaphore)) != VK_SUCCESS)
	{
		std::cout << "Code fo error1: " << error << std::endl;
		throw std::runtime_error("Failed to create semaphore");
	}

	if ((error = vkCreateSemaphore(deviceObj, &createInfo, nullptr, &imageAvailableSemaphore)) != VK_SUCCESS)
	{
		std::cout << "Code fo error2: " << error << std::endl;
		throw std::runtime_error("Failed to create semaphore");
	}
}

void Vulkan::vkDrawFrame()
{
	uint32_t imageIndex;

	vkAcquireNextImageKHR(deviceObj, swapchainObj, std::numeric_limits<uint64_t>::max(), imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);
	VkSubmitInfo submitInfo = {};

	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.pNext = nullptr;

	VkSemaphore waiteSemaphores[] = {imageAvailableSemaphore};
	VkPipelineStageFlags waiteStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waiteSemaphores;
	submitInfo.pWaitDstStageMask = waiteStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer[imageIndex];

	VkSemaphore signalSemaphore[] = {renderFinishedSemaphore};

	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphore;

	if ((error = vkQueueSubmit(graphicQueueFamily, 1, &submitInfo, VK_NULL_HANDLE)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << error << std::endl;
		throw std::runtime_error("Failed to submit");
	}

	VkPresentInfoKHR present = {};

	present.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	present.pNext = nullptr;
	present.waitSemaphoreCount = 1;
	present.pWaitSemaphores = waiteSemaphores;

	VkSwapchainKHR	swapChains[] = {swapchainObj};

	present.swapchainCount = 1;
	present.pSwapchains = swapChains;
	present.pImageIndices = &imageIndex;
	present.pResults = nullptr;
	vkQueuePresentKHR(presentQueueFamily, &present);
}

void	Vulkan::fbCleanUp()
{
	;//vkDestroyInstance(instanceProperties.instanceObject, nullptr);
}