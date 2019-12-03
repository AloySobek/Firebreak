/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassDevice.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:29:48 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/03 20:59:39 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vkClassContainer.hpp"

Device::Device()
{
	sCreateInfo.sType					= VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	sCreateInfo.pEnabledFeatures		= &sFeatures;
	sCreateInfo.flags					= VK_NULL_HANDLE;
	sCreateInfo.pNext					= nullptr;
}

void Device::setupFlags(VkInstanceCreateFlags flags)
{
	sCreateInfo.flags = flags;
}

void Device::setupNext(const void *pNext)
{
	sCreateInfo.pNext = pNext;
}

void Device::retrievePhysicalDevices(VkInstance instance)
{
	if (!retrieveDevices)
	{
		vkEnumeratePhysicalDevices(instance, &availablePhysicalDeviceCount, nullptr);
		pAvailablePhysicalDevices = new VkPhysicalDevice[availablePhysicalDeviceCount];
		vkEnumeratePhysicalDevices(instance, &availablePhysicalDeviceCount, pAvailablePhysicalDevices);
		retrieveDevices = true;
	}
}

void Device::attachPhysicalDevice(int deviceType)
{
	for (int i = 0; i < availablePhysicalDeviceCount && !physicalSelf; ++i)
		if (isPhysicalDeviceSuitable(pAvailablePhysicalDevices[i], deviceType))
			std::cout << sProperties.deviceName << std::endl;
}

bool Device::isPhysicalDeviceSuitable(VkPhysicalDevice testingDevice, int deviceType)
{
	vkGetPhysicalDeviceFeatures(testingDevice, &sFeatures);
	vkGetPhysicalDeviceProperties(testingDevice, &sProperties);
	return (sProperties.deviceType == deviceType);
}

VkLayerProperties	*Device::getLayers()
{
	if (!calledLayers)
	{
		vkEnumerateDeviceLayerProperties(physicalSelf, &availableLayersCount, nullptr);
		pAvailableLayers = new VkLayerProperties[availableLayersCount];
		ppEnabledLayerNames = new const char *[availableLayersCount];
		vkEnumerateDeviceLayerProperties(physicalSelf, &availableLayersCount, pAvailableLayers);
		calledLayers = true;
	}
	return (pAvailableLayers);
}

void Device::setupLayers(std::vector<const char *> &desiredLayers)
{
	getLayers();
	for (int i = 0; i < availableLayersCount; ++i)
		if (isLayerSuitable(pAvailableLayers[i], desiredLayers))
			ppEnabledLayerNames[enabledLayerCount++] = pAvailableLayers[i].layerName;
}

bool Device::isLayerSuitable(VkLayerProperties sLayer, std::vector<const char *> &desiredLayers)
{
	for (int i = 0; i < desiredLayers.size(); ++i)
		if (!strcmp(desiredLayers[i], sLayer.layerName))
			return (true);
	return (false);
}

VkExtensionProperties	*Device::getExtensions()
{
	if (!calledExtensions)
	{
		vkEnumerateDeviceExtensionProperties(physicalSelf, nullptr, &availableExtensionsCount, nullptr);
		pAvailableExtensions = new VkExtensionProperties[availableExtensionsCount];
		ppEnabledExtensionNames = new const char *[availableExtensionsCount];
		vkEnumerateDeviceExtensionProperties(physicalSelf, nullptr, &availableExtensionsCount, pAvailableExtensions);
		calledExtensions = true;
	}
	return (pAvailableExtensions);
}

void Device::setupExtensions(std::vector<const char *> &desiredExtensions)
{
	getExtensions();
	for (int i = 0; i < availableExtensionsCount; ++i)
		if (isExtensionSuitable(pAvailableExtensions[i], desiredExtensions))
			ppEnabledExtensionNames[enabledExtensionCount++] = pAvailableExtensions[i].extensionName;
}

bool Device::isExtensionSuitable(VkExtensionProperties sExtension, std::vector<const char *> &desiredExtensions)
{
	for (int i = 0; i < desiredExtensions.size(); ++i)
		if (!strcmp(desiredExtensions[i], sExtension.extensionName))
			return (true);
	return (false);
}

VkDevice Device::getSelf()
{
	return (self);
}

VkDevice Device::operator()()
{
	return (self);
}

VkQueueFamilyProperties	*Device::getQueueFamilies()
{
	if (!calledQeueue)
	{
		vkGetPhysicalDeviceQueueFamilyProperties(physicalSelf, &availableQueuesFamiliesCount, nullptr);
		pAvailableQueuesFamilies = new VkQueueFamilyProperties[availableQueuesFamiliesCount];
		vkGetPhysicalDeviceQueueFamilyProperties(physicalSelf, &availableQueuesFamiliesCount, pAvailableQueuesFamilies);
		calledQeueue = true;
	}
	return (pAvailableQueuesFamilies);
}

void Device::checkCompatibleWithSurface(Surface surface)
{
	VkBool32 presentQueueFamilySupport = false;

	getQueueFamilies();
	for (int i = 0; i < availableQueuesFamiliesCount && presentQueueFamilyIndex < 0; ++i)
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalSelf, i, surface.self, &presentQueueFamilySupport);
		if (presentQueueFamilySupport)
			presentQueueFamilyIndex = i;
	}
	if (presentQueueFamilyIndex < 0)
		throw std::runtime_error("Device not compatible with surface");
	setupQueueFamilyCreateInfo(1.0f, 1, presentQueueFamilyIndex);
}

void Device::setupQueue(int type)
{
	getQueueFamilies();
	for (int i = 0; i < availableQueuesFamiliesCount; ++i)
		if (pAvailableQueuesFamilies[i].queueCount > 0)
			if ((pAvailableQueuesFamilies[i].queueFlags & type) && type == VK_QUEUE_GRAPHICS_BIT)
			{
				graphicQueueFamilyIndex = i;
				if (i != presentQueueFamilyIndex)
					break;
			}
	if (graphicQueueFamilyIndex < 0)
		throw std::runtime_error("Failed to find physical queue for gpu");
	setupQueueFamilyCreateInfo(1.0f, 1, graphicQueueFamilyIndex);
}

void Device::setupQueueFamilyCreateInfo(float queuePriority, int queueCount, int queueIndex)
{
	pQueueFamilies[queueFamilyCreateInfoCount].sType			= VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	pQueueFamilies[queueFamilyCreateInfoCount].queueCount		= queueCount;
	pQueueFamilies[queueFamilyCreateInfoCount].queueFamilyIndex	= queueIndex;
	pQueueFamilies[queueFamilyCreateInfoCount].pQueuePriorities	= &queuePriority;
	pQueueFamilies[queueFamilyCreateInfoCount].pNext			= nullptr;
	pQueueFamilies[queueFamilyCreateInfoCount++].flags			= 0;
}

void Device::create()
{
	sCreateInfo.enabledLayerCount		= enabledLayerCount;
	sCreateInfo.ppEnabledLayerNames		= ppEnabledLayerNames;
	sCreateInfo.enabledExtensionCount	= enabledExtensionCount;
	sCreateInfo.ppEnabledExtensionNames	= ppEnabledExtensionNames;
	sCreateInfo.pQueueCreateInfos		= pQueueFamilies;
	sCreateInfo.queueCreateInfoCount	= queueFamilyCreateInfoCount;

	if ((codeOfError = vkCreateDevice(physicalSelf, &sCreateInfo, nullptr, &self)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << codeOfError << std::endl;
		throw std::runtime_error("Failed to create logical device");
	}
}

void Device::retrieveAllQueus()
{
	vkGetDeviceQueue(self, graphicQueueFamilyIndex, 0, &graphicQueueFamily);
	vkGetDeviceQueue(self, presentQueueFamilyIndex, 0, &presentQueueFamily);
}