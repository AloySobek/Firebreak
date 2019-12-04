/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassDevice.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:29:48 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/04 20:52:48 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

Device::Device(const void *pNext)
{
	init();
	sCreateInfo.pNext = pNext;
}

Device::Device(VkDeviceCreateFlags flags, const void *pNext)
{
	init();
	sCreateInfo.flags = flags;
	sCreateInfo.pNext = pNext;
}

void Device::init()
{
	sCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	sCreateInfo.pEnabledFeatures = &sFeatures;
	memset(pIndexArray, -1, VK_QUEUE_PROTECTED_BIT * sizeof(uint32_t));
	memset(pQueues, 0, VK_QUEUE_PROTECTED_BIT);
}

void Device::setupFlags(VkInstanceCreateFlags flags)
{
	sCreateInfo.flags = flags;
}

void Device::setupNext(const void *pNext)
{
	sCreateInfo.pNext = pNext;
}

void Device::setupLayers(std::vector<const char *> &desiredLayers)
{
	getLayers();
	for (int i = 0; i < availableLayersCount; ++i)
		if (isLayerSuitable(pAvailableLayers[i], desiredLayers))
			ppEnabledLayerNames[enabledLayerCount++] = pAvailableLayers[i].layerName;
}

void Device::setupExtensions(std::vector<const char *> &desiredExtensions)
{
	getExtensions();
	for (int i = 0; i < availableExtensionsCount; ++i)
		if (isExtensionSuitable(pAvailableExtensions[i], desiredExtensions))
			ppEnabledExtensionNames[enabledExtensionCount++] = pAvailableExtensions[i].extensionName;
}

VkDevice	Device::getSelf()
{
	assert(self);
	return (self);
}

VkPhysicalDevice	Device::getPhysicalSelf()
{
	assert(physicalSelf);
	return (physicalSelf);
}

VkPhysicalDevice	*Device::getPhysicalDevices(Instance instance)
{
	if (!retrieveDevices)
	{
		vkEnumeratePhysicalDevices(instance(), &availablePhysicalDeviceCount, nullptr);
		pAvailablePhysicalDevices = new VkPhysicalDevice[availablePhysicalDeviceCount];
		vkEnumeratePhysicalDevices(instance(), &availablePhysicalDeviceCount, pAvailablePhysicalDevices);
		retrieveDevices = true;
	}
	return (pAvailablePhysicalDevices);
}

VkPhysicalDeviceFeatures	*Device::getFeatures()
{
	return (&sFeatures);
}

VkPhysicalDeviceProperties	*Device::getProperties()
{
	return (&sProperties);
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

void Device::attachPhysicalDevice(int deviceType)
{
	for (int i = 0; i < availablePhysicalDeviceCount && !physicalSelf; ++i)
		if (isPhysicalDeviceSuitable(pAvailablePhysicalDevices[i], deviceType))
			physicalSelf = pAvailablePhysicalDevices[i];
}

void Device::attachPhysicalDevice(Instance instance, int deviceType)
{
	getPhysicalDevices(instance);
	attachPhysicalDevice(deviceType);
}

bool Device::checkCompatibleWithSurface(Surface surface)
{
	VkBool32 presentQueueFamilySupport = false;

	getQueueFamilies();
	for (int i = 0; i < availableQueuesFamiliesCount; ++i)
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalSelf, i, surface.self, &presentQueueFamilySupport);
		if (presentQueueFamilySupport)
		{
			pIndexArray[VK_QUEUE_PRESENT_BIT] = i;
			break;
		}
	}
	if (!presentQueueFamilySupport)
		return (false);
	return (true);
}

void Device::setupQueue(int type, float priority, int count)
{
	getQueueFamilies();
	for (int i = 0; i < availableQueuesFamiliesCount; ++i)
		if (isQueueFamilySuitable(pAvailableQueuesFamilies[i], type, count) || type == VK_QUEUE_PRESENT_BIT)
		{
			pQueueFamiliesCreateInfo[queueFamiliesCreateInfoCount].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			pQueueFamiliesCreateInfo[queueFamiliesCreateInfoCount].queueCount = count;
			pQueueFamiliesCreateInfo[queueFamiliesCreateInfoCount].pQueuePriorities = &priority;
			pQueueFamiliesCreateInfo[queueFamiliesCreateInfoCount].queueFamilyIndex = i;
			pQueueFamiliesCreateInfo[queueFamiliesCreateInfoCount].pNext = nullptr;
			pQueueFamiliesCreateInfo[queueFamiliesCreateInfoCount].flags = 0;
			if (type != VK_QUEUE_PRESENT_BIT)
				pIndexArray[type] = i;
			++queueFamiliesCreateInfoCount;
			break;
		}
	if (pIndexArray[type] < 0)
		throw std::runtime_error("Failed to setup queue");
}

uint32_t		*Device::requireIndexArray()
{
	uint32_t	*new_array;
	uint32_t	size = 0;

	new_array = new uint32_t[VK_QUEUE_PROTECTED_BIT];
	for (int i = 0; i < VK_QUEUE_PROTECTED_BIT; ++i)
		if (pIndexArray[i] >= 0)
			new_array[size++] = pIndexArray[i];
	new_array[VK_QUEUE_PROTECTED_BIT - 1] = size;
	return (0);
}

VkDevice Device::operator()()
{
	if (!self)
	{
		sCreateInfo.enabledLayerCount		= enabledLayerCount;
		sCreateInfo.ppEnabledLayerNames		= ppEnabledLayerNames;
		sCreateInfo.enabledExtensionCount	= enabledExtensionCount;
		sCreateInfo.ppEnabledExtensionNames	= ppEnabledExtensionNames;
		sCreateInfo.pQueueCreateInfos		= pQueueFamiliesCreateInfo;
		sCreateInfo.queueCreateInfoCount	= queueFamiliesCreateInfoCount;

		if ((codeOfError = vkCreateDevice(physicalSelf, &sCreateInfo, nullptr, &self)) != VK_SUCCESS)
		{
			std::cout << "Code of error: " << codeOfError << std::endl;
			throw std::runtime_error("Failed to create logical device");
		}
		for (int i = 0; i < VK_QUEUE_PROTECTED_BIT; ++i)
			if (pIndexArray[i] >= 0)
				vkGetDeviceQueue(self, pIndexArray[i], 0, &pQueues[i]);
	}
	return (self);
}

bool Device::isPhysicalDeviceSuitable(VkPhysicalDevice testingDevice, uint32_t deviceType)
{
	vkGetPhysicalDeviceFeatures(testingDevice, &sFeatures);
	vkGetPhysicalDeviceProperties(testingDevice, &sProperties);
	return (sProperties.deviceType == deviceType);
}

bool Device::isLayerSuitable(VkLayerProperties sLayer, std::vector<const char *> &desiredLayers)
{
	for (int i = 0; i < desiredLayers.size(); ++i)
		if (!strcmp(desiredLayers[i], sLayer.layerName))
			return (true);
	return (false);
}

bool Device::isExtensionSuitable(VkExtensionProperties sExtension, std::vector<const char *> &desiredExtensions)
{
	for (int i = 0; i < desiredExtensions.size(); ++i)
		if (!strcmp(desiredExtensions[i], sExtension.extensionName))
			return (true);
	return (false);
}

bool Device::isQueueFamilySuitable(VkQueueFamilyProperties queueProperties, uint32_t type, uint32_t count)
{
	if ((queueProperties.queueFlags & type) && queueProperties.queueCount >= count)
		return (true);
	return (false);
}