/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassDevice.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:29:48 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/08 14:29:14 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

Device::Device(const void *pNext)
{
	sCreateInfo.pNext = pNext;
	sCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	sCreateInfo.pEnabledFeatures = &sFeatures;
	memset(pQueues, -1, VK_QUEUE_PROTECTED_BIT * sizeof(FbQueue_t));
}

Device::Device(VkDeviceCreateFlags flags, const void *pNext) : Device(pNext)
{
	sCreateInfo.flags = flags;
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

VkPhysicalDevice	*Device::getPhysicalDevices(Instance &instance)
{
	if (!retrieveDevices)
	{
		vkEnumeratePhysicalDevices(instance.getSelf(), &availablePhysicalDeviceCount, nullptr);
		pAvailablePhysicalDevices = new VkPhysicalDevice[availablePhysicalDeviceCount];
		vkEnumeratePhysicalDevices(instance.getSelf(), &availablePhysicalDeviceCount, pAvailablePhysicalDevices);
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

VkPhysicalDeviceMemoryProperties	*Device::getMemoryProperties()
{
	return (&sMemoryProperties);
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

uint32_t Device::getLayersAmount()
{
	return (availableLayersCount);
}

uint32_t Device::getExtensionsAmount()
{
	return (availableExtensionsCount);
}

uint32_t Device::getPhysicalDevicesAmount()
{
	return (availablePhysicalDeviceCount);
}

uint32_t Device::getQueuesFamiliesCount()
{
	return (availableQueuesFamiliesCount);
}

void Device::attachPhysicalDevice(int deviceType)
{
	for (int i = 0; i < availablePhysicalDeviceCount && !physicalSelf; ++i)
		if (isPhysicalDeviceSuitable(pAvailablePhysicalDevices[i], deviceType))
			physicalSelf = pAvailablePhysicalDevices[i];
	if (!physicalSelf)
		throw std::runtime_error("Failed to find physical device");
}

void Device::attachPhysicalDevice(Instance &instance, int deviceType)
{
	getPhysicalDevices(instance);
	attachPhysicalDevice(deviceType);
}

bool Device::checkCompatibleWithSurface(Surface &surface)
{
	VkBool32 presentQueueFamilySupport = false;

	getQueuesFamiliesProperties();
	for (int i = 0; i < availableQueuesFamiliesCount; ++i)
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalSelf, i, surface.self, &presentQueueFamilySupport);
		if (presentQueueFamilySupport)
		{
			pQueues[VK_QUEUE_PRESENT_BIT].index = i;
			break;
		}
	}
	if (!presentQueueFamilySupport)
		return (false);
	return (true);
}

void Device::setupQueue(int type, float priority, int count)
{
	getQueuesFamiliesProperties();
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
				pQueues[type].index = i;
			++queueFamiliesCreateInfoCount;
			break;
		}
	if (pQueues[type].index < 0)
		throw std::runtime_error("Failed to setup queue");
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
}

VkDevice Device::operator()()
{
	return (getSelf());
}

VkPhysicalDevice Device::operator!()
{
	return (getPhysicalSelf());
}

bool Device::isPhysicalDeviceSuitable(VkPhysicalDevice device, uint32_t type)
{
	vkGetPhysicalDeviceFeatures(device, &sFeatures);
	vkGetPhysicalDeviceProperties(device, &sProperties);
	vkGetPhysicalDeviceMemoryProperties(device, &sMemoryProperties);
	vkGetPhysicalDeviceFormatProperties(device, (VkFormat)0, nullptr);
	return (sProperties.deviceType == type);
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