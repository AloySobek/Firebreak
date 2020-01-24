/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassDevice.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:29:48 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/29 16:23:13 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

FbDevice::FbDevice(VkDeviceCreateInfo info, VkAllocationCallbacks allocation)
	: self(VK_NULL_HANDLE), physicalSelf(VK_NULL_HANDLE), sCreateInfo(info), sAllocation(allocation), codeOfError(false)
{
	sCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
}

void FbDevice::create()
{
	codeOfError = vkCreateDevice(physicalSelf, &sCreateInfo, sAllocation.pfnAllocation ? &sAllocation : nullptr, &self);
	THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to create device");
}

void FbDevice::destroy()
{
	vkDestroyDevice(self, sAllocation.pfnFree ? &sAllocation : nullptr);
	self = VK_NULL_HANDLE;
}

/*
** This border to the next layer of firebreak framework <><><><><><><><><><><><><><><><><>
** This border to the next layer of firebreak framework <><><><><><><><><><><><><><><><><>
** This border to the next layer of firebreak framework <><><><><><><><><><><><><><><><><>
*/

// VkDeviceQueueCreateInfo	*Device2::getDeviceQueueCreateInfo()
// {
// 	return ((VkDeviceQueueCreateInfo *)&sCreateInfo.pQueueCreateInfos[sCreateInfo.queueCreateInfoCount]);
// }

// void	Device2::retrieveQueues()
// {
// 	getQueueFamilyProperties();
// 	for (int i = 0; i < FB_QUEUE_MAX; ++i)
// 		if (pQueues[i].index >= 0)
// 			vkGetDeviceQueue(self, pQueues[i].index, 0, &pQueues[i].self);
// }

// void Device2::clear(int mode)
// {
// 	if (pAvailableLayers)
// 	{
// 		delete[] pAvailableLayers;
// 		availableLayersCount	= 0;
// 		pAvailableLayers		= nullptr;
// 	}
// 	if (pAvailableExtensions)
// 	{
// 		delete[] pAvailableExtensions;
// 		availableExtensionsCount	= 0;
// 		pAvailableExtensions		= nullptr;
// 	}
// 	if (pAvailableQueuesFamilies)
// 	{
// 		delete[] pAvailableQueuesFamilies;
// 		availableQueuesFamiliesCount	= 0;
// 		pAvailableQueuesFamilies		= nullptr;
// 	}
// 	if (self && (mode & FINISH_HIM))
// 		vkDestroyDevice(self, sAllocation.pfnFree ? &sAllocation : nullptr);
// }

// FbQueue	*Device2::getQueues()
// {
// 	return (pQueues);
// }

// void Device2::pushQueue(int32_t type)
// {
// 	if (type >= 0 && type < 5)
// 		pQueues[type].index = sCreateInfo.pQueueCreateInfos[sCreateInfo.queueCreateInfoCount].queueFamilyIndex;
// 	++sCreateInfo.queueCreateInfoCount;
// }

// void Device2::attachPhysicalDevice(Instance &instance, uint32_t type)
// {
// 	VkPhysicalDevice	*devices;
// 	uint32_t			size;

// 	devices = instance.getPhysicalDevices(&size);
// 	for (int i = 0; i < size && !physicalSelf; ++i)
// 	{
// 		vkGetPhysicalDeviceProperties(devices[i], &sProperties);
// 		if (sProperties.deviceType == type)
// 			physicalSelf = devices[i];
// 	}
// 	if (!physicalSelf)
// 		throw std::runtime_error("Failed to find physical device");
// }

// VkPhysicalDeviceFeatures	*Device2::getFeatures()
// {
// 	vkGetPhysicalDeviceFeatures(physicalSelf, &sFeatures);
// 	return (&sFeatures);
// }

// VkPhysicalDeviceProperties	*Device2::getProperties()
// {
// 	vkGetPhysicalDeviceProperties(physicalSelf, &sProperties);
// 	return (&sProperties);
// }

// VkPhysicalDeviceMemoryProperties	*Device2::getMemoryProperties()
// {
// 	vkGetPhysicalDeviceMemoryProperties(physicalSelf, &sMemoryProperties);
// 	return (&sMemoryProperties);
// }

// VkLayerProperties	*Device2::getLayers(uint32_t *size)
// {
// 	if (!pAvailableLayers)
// 	{
// 		vkEnumerateDeviceLayerProperties(physicalSelf, &availableLayersCount, nullptr);
// 		pAvailableLayers				= new VkLayerProperties[availableLayersCount];
// 		sCreateInfo.ppEnabledLayerNames	= new const char *[availableLayersCount];
// 		vkEnumerateDeviceLayerProperties(physicalSelf, &availableLayersCount, pAvailableLayers);
// 	}
// 	size ? *size = availableLayersCount : false;
// 	return (pAvailableLayers);
// }

// VkExtensionProperties	*Device2::getExtensions(uint32_t *size)
// {
// 	if (!pAvailableExtensions)
// 	{
// 		vkEnumerateDeviceExtensionProperties(physicalSelf, nullptr, &availableExtensionsCount, nullptr);
// 		pAvailableExtensions				= new VkExtensionProperties[availableExtensionsCount];
// 		sCreateInfo.ppEnabledExtensionNames	= new const char *[availableExtensionsCount];
// 		vkEnumerateDeviceExtensionProperties(physicalSelf, nullptr, &availableExtensionsCount, pAvailableExtensions);
// 	}
// 	size ? *size = availableExtensionsCount : false;
// 	return (pAvailableExtensions);
// }

// VkQueueFamilyProperties	*Device2::getQueueFamilyProperties(uint32_t *size)
// {
// 	if (!pAvailableQueuesFamilies)
// 	{
// 		vkGetPhysicalDeviceQueueFamilyProperties(physicalSelf, &availableQueuesFamiliesCount, nullptr);
// 		pAvailableQueuesFamilies		= new VkQueueFamilyProperties[availableQueuesFamiliesCount];
// 		sCreateInfo.pQueueCreateInfos	= new VkDeviceQueueCreateInfo[availableQueuesFamiliesCount];
// 		memset((void *)sCreateInfo.pQueueCreateInfos, 0, sizeof(VkDeviceQueueCreateInfo) * availableQueuesFamiliesCount);
// 		vkGetPhysicalDeviceQueueFamilyProperties(physicalSelf, &availableQueuesFamiliesCount, pAvailableQueuesFamilies);
// 	}
// 	size ? *size = availableQueuesFamiliesCount : false;
// 	return (pAvailableQueuesFamilies);
// }

// void Device2::setLayers(const char **desiredLayers, uint32_t size)
// {
// 	getLayers();
// 	for (int i = 0; i < availableLayersCount; ++i)
// 		if (isLayerSuitable(pAvailableLayers[i], desiredLayers, size))
// 			((char **)sCreateInfo.ppEnabledLayerNames)[sCreateInfo.enabledLayerCount++] = pAvailableLayers[i].layerName;
// }

// void Device2::setExtensions(const char **desiredExtensions, uint32_t size)
// {
// 	getExtensions();
// 	for (int i = 0; i < availableExtensionsCount; ++i)
// 		if (isExtensionSuitable(pAvailableExtensions[i], desiredExtensions, size))
// 			((char **)sCreateInfo.ppEnabledExtensionNames)[sCreateInfo.enabledExtensionCount++] = pAvailableExtensions[i].extensionName;
// }

// bool Device2::setPresentQueue(Surface &surface, VkExtent3D minImageTransferGranularity, uint32_t timestampValidBits, uint32_t queueCount, float priority)
// {
// 	VkBool32 presentQueueFamilySupport = false;

// 	getQueueFamilyProperties();
// 	for (int i = 0; i < availableQueuesFamiliesCount; ++i)
// 	{
// 		vkGetPhysicalDeviceSurfaceSupportKHR(physicalSelf, i, surface.getSelf(), &presentQueueFamilySupport);
// 		if (presentQueueFamilySupport)
// 		{
// 			getDeviceQueueCreateInfo()->sType				= VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
// 			getDeviceQueueCreateInfo()->queueCount			= queueCount;
// 			getDeviceQueueCreateInfo()->queueFamilyIndex	= i;
// 			getDeviceQueueCreateInfo()->pQueuePriorities	= &priority;
// 			pushQueue(FB_QUEUE_PRESENT);
// 			break;
// 		}
// 	}
// 	if (!presentQueueFamilySupport)
// 		return (false);
// 	return (true);
// }

// bool Device2::setQueue(uint32_t type, VkExtent3D minImageTransferGranularity, uint32_t timestampValidBits, uint32_t queueCount, float priority)
// {
// 	getQueueFamilyProperties();
// 	for (int i = 0; i < availableQueuesFamiliesCount; ++i)
// 		if (isQueueFamilySuitable(pAvailableQueuesFamilies[i], minImageTransferGranularity, timestampValidBits, queueCount))
// 		{
// 			getDeviceQueueCreateInfo()->sType				= VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
// 			getDeviceQueueCreateInfo()->queueCount			= queueCount;
// 			getDeviceQueueCreateInfo()->queueFamilyIndex	= i;
// 			getDeviceQueueCreateInfo()->pQueuePriorities	= &priority;
// 			pushQueue(type);
// 			break;
// 		}
// 	if (pQueues[type].index < 0)
// 		return (false);
// 	return (true);
// }

// uint32_t		*Device2::requireIndexArray()
// {
// 	uint32_t	*new_array;
// 	uint32_t	size = 0;

// 	new_array = new uint32_t[FB_QUEUE_MAX + 1];
// 	for (int i = 0; i < FB_QUEUE_MAX; ++i)
// 		if (pQueues[i].index >= 0)
// 			new_array[size++] = pQueues[i].index;
// 	new_array[FB_QUEUE_MAX] = size;
// 	return (new_array);
// }

// bool Device2::isQueueFamilySuitable(VkQueueFamilyProperties queueProperties, VkExtent3D minImageTransferGranularity, uint32_t timestampValidBits, uint32_t queueCount)
// {
// 	if (queueProperties.queueCount >= queueCount && queueProperties.minImageTransferGranularity.width >= minImageTransferGranularity.width
// 	&& queueProperties.minImageTransferGranularity.height >= minImageTransferGranularity.height
// 	&& queueProperties.minImageTransferGranularity.depth >= minImageTransferGranularity.depth
// 	&& (queueProperties.timestampValidBits == timestampValidBits || timestampValidBits == 0))
// 		return (true);
// 	return (false);
// }

// bool Device2::isLayerSuitable(VkLayerProperties sLayer, const char **desiredLayers, uint32_t size)
// {
// 	for (int i = 0; i < size; ++i)
// 		if (!strcmp(desiredLayers[i], sLayer.layerName))
// 			return (true);
// 	return (false);
// }

// bool Device2::isExtensionSuitable(VkExtensionProperties sExtension, const char **desiredExtensions, uint32_t size)
// {
// 	for (int i = 0; i < size; ++i)
// 		if (!strcmp(desiredExtensions[i], sExtension.extensionName))
// 			return (true);
// 	return (false);
// }

// bool Device2::isPhysicalDeviceSuitable(VkPhysicalDevice device, uint32_t type)
// {
// 	return (true);
// }