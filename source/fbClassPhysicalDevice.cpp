/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassPhysicalDevice.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:29:48 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/01 20:25:04 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vkClassContainer.hpp"

void PhysicalDevice::getInfo()
{
	vkGetPhysicalDeviceFeatures(self, &sFeatures);
	vkGetPhysicalDeviceProperties(self, &sProperties);
}

void PhysicalDevice::setupLayers()
{
	vkEnumerateDeviceLayerProperties(self, &availableLayersCount, nullptr);
	pAvailableLayers = (VkLayerProperties *)malloc(sizeof(VkLayerProperties) * availableLayersCount);
	ppSelectedLayers.resize(availableLayersCount);
	vkEnumerateDeviceLayerProperties(self, &availableLayersCount, pAvailableLayers);
	for (int i = 0, j = 0; i < availableLayersCount; ++i)
	{
		//if (vkIsLayerSuitable(pAvailablePhysicalDeviceLayers[i]))
		if (0);
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
		//if (vkIsExtensionSuitable(pAvailablePhysicalDeviceExtensions[i]))
		if (1);
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

void PhysicalDevice::init()
{

}