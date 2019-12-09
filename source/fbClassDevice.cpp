/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassDevice.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:29:48 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/09 16:14:03 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

Device::Device()
{
	sCreateInfo.sType				= VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	sCreateInfo.pEnabledFeatures	= &sFeatures;
	sCreateInfo.pQueueCreateInfos	= pQueueFamiliesCreateInfos;
	memset(pQueues, -1, VK_QUEUE_PROTECTED_BIT * sizeof(FbQueue_t));
}

void Device::setLayers(const char **desiredLayers, uint32_t size)
{
	getAvailableLayers();
	for (int i = 0; i < availableLayersCount; ++i)
		if (isLayerSuitable(pAvailableLayers[i], desiredLayers, size))
			((char **)sCreateInfo.ppEnabledLayerNames)[sCreateInfo.enabledLayerCount++] = pAvailableLayers[i].layerName;
}

void Device::setExtensions(const char **desiredExtensions, uint32_t size)
{
	getAvailableExtensions();
	for (int i = 0; i < availableExtensionsCount; ++i)
		if (isExtensionSuitable(pAvailableExtensions[i], desiredExtensions, size))
			((char **)sCreateInfo.ppEnabledExtensionNames)[sCreateInfo.enabledExtensionCount++] = pAvailableExtensions[i].extensionName;
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

VkPhysicalDeviceFeatures	*Device::getFeatures()
{
	return (&sFeatures);
}

VkPhysicalDeviceProperties	*Device::getProperties()
{
	return (&sProperties);
}

VkPhysicalDeviceMemoryProperties	*Device::getMemoryProperties()
{
	return (&sMemoryProperties);
}

VkLayerProperties	*Device::getAvailableLayers()
{
	if (!calledLayers)
	{
		vkEnumerateDeviceLayerProperties(physicalSelf, &availableLayersCount, nullptr);
		pAvailableLayers = new VkLayerProperties[availableLayersCount];
		sCreateInfo.ppEnabledLayerNames = new const char *[availableLayersCount];
		vkEnumerateDeviceLayerProperties(physicalSelf, &availableLayersCount, pAvailableLayers);
		calledLayers = true;
	}
	return (pAvailableLayers);
}

VkExtensionProperties	*Device::getAvailableExtensions()
{
	if (!calledExtensions)
	{
		vkEnumerateDeviceExtensionProperties(physicalSelf, nullptr, &availableExtensionsCount, nullptr);
		pAvailableExtensions = new VkExtensionProperties[availableExtensionsCount];
		sCreateInfo.ppEnabledExtensionNames = new const char *[availableExtensionsCount];
		vkEnumerateDeviceExtensionProperties(physicalSelf, nullptr, &availableExtensionsCount, pAvailableExtensions);
		calledExtensions = true;
	}
	return (pAvailableExtensions);
}

VkQueueFamilyProperties	*Device::getQueuesFamiliesProperties()
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

FbQueue_t	*Device::getQueuesFamilies()
{
	if (!getQueue)
	{
		for (int i = 0; i < VK_QUEUE_PROTECTED_BIT; ++i)
			if (pQueues[i].index >= 0)
				vkGetDeviceQueue(self, pQueues[i].index, 0, &pQueues[i].self);
		getQueue = true;
	}
	return (pQueues);
}

void Device::attachPhysicalDevice(int type, VkPhysicalDevice *pPhysicalDevices, uint32_t size)
{
	for (int i = 0; i < size && !physicalSelf; ++i)
		if (isPhysicalDeviceSuitable(pPhysicalDevices[i], type))
			physicalSelf = pPhysicalDevices[i];
	if (!physicalSelf)
		throw std::runtime_error("Failed to find physical device");
}

bool Device::setQueue(Surface &surface, VkQueueFamilyProperties properties, float priority)
{
	VkBool32 presentQueueFamilySupport = false;

	getQueuesFamiliesProperties();
	for (int i = 0; i < availableQueuesFamiliesCount; ++i)
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalSelf, i, surface.getSelf(), &presentQueueFamilySupport);
		if (presentQueueFamilySupport)
		{
			fillQueueCreateInfo(properties, priority, i);
			pQueues[properties.queueFlags].index = i;
			break;
		}
	}
	if (pQueues[properties.queueFlags].index)
		return (false);
	return (true);
}

bool Device::setQueue(VkQueueFamilyProperties properties, float priority)
{
	getQueuesFamiliesProperties();
	for (int i = 0; i < availableQueuesFamiliesCount; ++i)
		if (isQueueFamilySuitable(pAvailableQueuesFamilies[i], properties))
		{
			fillQueueCreateInfo(properties, priority, i);
			pQueues[properties.queueFlags].index = i;
			break;
		}
	if (pQueues[properties.queueFlags].index < 0)
		return (false);
	return (true);
}

uint32_t		*Device::requireIndexArray()
{
	uint32_t	*new_array;
	uint32_t	size = 0;

	new_array = new uint32_t[VK_QUEUE_PROTECTED_BIT];
	for (int i = 0; i < VK_QUEUE_PROTECTED_BIT; ++i)
		if (pQueues[i].index >= 0)
			new_array[size++] = pQueues[i].index;
	new_array[VK_QUEUE_PROTECTED_BIT - 1] = size;
	return (new_array);
}

void Device::create()
{
	assert(physicalSelf);
	if ((codeOfError = vkCreateDevice(physicalSelf, &sCreateInfo, nullptr, &self)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << codeOfError << std::endl;
		throw std::runtime_error("Failed to create logical device");
	}
	getQueuesFamilies();
}

VkDevice Device::operator()()
{
	return (getSelf());
}

VkPhysicalDevice Device::operator!()
{
	return (getPhysicalSelf());
}

bool Device::isLayerSuitable(VkLayerProperties sLayer, const char **desiredLayers, uint32_t size)
{
	for (int i = 0; i < size; ++i)
		if (!strcmp(desiredLayers[i], sLayer.layerName))
			return (true);
	return (false);
}

bool Device::isExtensionSuitable(VkExtensionProperties sExtension, const char **desiredExtensions, uint32_t size)
{
	for (int i = 0; i < size; ++i)
		if (!strcmp(desiredExtensions[i], sExtension.extensionName))
			return (true);
	return (false);
}

bool Device::isPhysicalDeviceSuitable(VkPhysicalDevice device, uint32_t type)
{
	vkGetPhysicalDeviceFeatures(device, &sFeatures);
	vkGetPhysicalDeviceProperties(device, &sProperties);
	vkGetPhysicalDeviceMemoryProperties(device, &sMemoryProperties);
	return (sProperties.deviceType == type);
}

bool Device::isQueueFamilySuitable(VkQueueFamilyProperties queueProperties, VkQueueFamilyProperties properties)
{
	if ((queueProperties.queueFlags & properties.queueFlags) && queueProperties.queueCount >= properties.queueCount)
		return (true);
	return (false);
}

void Device::fillQueueCreateInfo(VkQueueFamilyProperties properties, float priority, int index)
{
	pQueueFamiliesCreateInfos[queueFamiliesCreateInfoCount].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	pQueueFamiliesCreateInfos[queueFamiliesCreateInfoCount].pQueuePriorities = &priority;
	pQueueFamiliesCreateInfos[queueFamiliesCreateInfoCount].queueFamilyIndex = index;
	pQueueFamiliesCreateInfos[queueFamiliesCreateInfoCount].queueCount = properties.queueCount;
	pQueueFamiliesCreateInfos[queueFamiliesCreateInfoCount].pNext = nullptr;
	pQueueFamiliesCreateInfos[queueFamiliesCreateInfoCount].flags = 0;
	++queueFamiliesCreateInfoCount;
	sCreateInfo.queueCreateInfoCount = queueFamiliesCreateInfoCount;
}