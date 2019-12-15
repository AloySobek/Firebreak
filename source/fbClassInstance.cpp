/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassInstance.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:35:59 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/15 17:19:26 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

Instance::Instance()
{
	sCreateInfo.sType				= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	sCreateInfo.pApplicationInfo	= &sApplicationInfo;
	sApplicationInfo.sType			= VK_STRUCTURE_TYPE_APPLICATION_INFO;
}

VkInstance Instance::getSelf(void)
{
	assert(self);
	return (self);
}

VkInstanceCreateInfo	*Instance::getCreateInfo()
{
	return (&sCreateInfo);
}

VkApplicationInfo	*Instance::getAppInfo()
{
	return (&sApplicationInfo);
}

VkAllocationCallbacks	*Instance::getAllocationInfo()
{
	return (&sAllocation);
}

VkLayerProperties	*Instance::getAvailableLayers(uint32_t *size)
{
	if (!pAvailableLayers)
	{
		vkEnumerateInstanceLayerProperties(&availableLayersCount, nullptr);
		pAvailableLayers = new VkLayerProperties[availableLayersCount];
		sCreateInfo.ppEnabledLayerNames = new const char *[availableLayersCount];
		vkEnumerateInstanceLayerProperties(&availableLayersCount, pAvailableLayers);
	}
	size ? *size = availableLayersCount : false;
	return (pAvailableLayers);
}

VkPhysicalDevice	*Instance::getPhysicalDevices(uint32_t *size)
{
	if (!pAvailablePhysicalDevices)
	{
		vkEnumeratePhysicalDevices(self, &availablePhysicalDeviceCount, nullptr);
		pAvailablePhysicalDevices = new VkPhysicalDevice[availablePhysicalDeviceCount];
		vkEnumeratePhysicalDevices(self, &availablePhysicalDeviceCount, pAvailablePhysicalDevices);
	}
	size ? *size = availablePhysicalDeviceCount : false;
	return (pAvailablePhysicalDevices);
}

VkExtensionProperties	*Instance::getAvailableExtensions(uint32_t *size)
{
	if (!pAvailableExtensions)
	{
		vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, nullptr);
		pAvailableExtensions = new VkExtensionProperties[availableExtensionsCount];
		sCreateInfo.ppEnabledExtensionNames = new const char *[availableExtensionsCount];
		vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, pAvailableExtensions);
	}
	size ? *size = availableExtensionsCount : false;
	return (pAvailableExtensions);
}

void Instance::create(int mode)
{
	if ((codeOfError = vkCreateInstance(&sCreateInfo, mode ? &sAllocation : nullptr, &self)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << codeOfError << std::endl;
		throw std::runtime_error("Failed to create instance");
	}
}

Instance::~Instance()
{
	if (pAvailableLayers)
	{
		delete[] pAvailableLayers;
		availableLayersCount	= 0;
		pAvailableLayers		= nullptr;
	}
	if (pAvailableExtensions)
	{
		delete[] pAvailableExtensions;
		availableExtensionsCount	= 0;
		pAvailableExtensions		= nullptr;
	}
	if (pAvailablePhysicalDevices)
	{
		delete[] pAvailablePhysicalDevices;
		availablePhysicalDeviceCount	= 0;
		pAvailablePhysicalDevices		= nullptr;
	}
}

void Instance2::setLayers(const char **desiredLayers, uint32_t size)
{
	getAvailableLayers();
	for (int i = 0; i < availableLayersCount; ++i)
		if (isLayerSuitable(pAvailableLayers[i], desiredLayers, size))
			((char **)sCreateInfo.ppEnabledLayerNames)[sCreateInfo.enabledLayerCount++] = pAvailableLayers[i].layerName;
}

void Instance2::setExtensions(const char **desiredExtensions, uint32_t size)
{
	getAvailableExtensions();
	for (int i = 0; i < availableExtensionsCount; ++i)
		if (isExtensionSuitable(pAvailableExtensions[i], desiredExtensions, size))
			((char **)sCreateInfo.ppEnabledExtensionNames)[sCreateInfo.enabledExtensionCount++] = pAvailableExtensions[i].extensionName;
}

void Instance2::setAppInfo(const char *pName, uint32_t appVersion, const char *pEngineName, uint32_t engineVersion, uint32_t vulkanVersion)
{
	sApplicationInfo.pApplicationName	= pName;
	sApplicationInfo.applicationVersion	= appVersion;
	sApplicationInfo.pEngineName		= pEngineName;
	sApplicationInfo.engineVersion		= engineVersion;
	sApplicationInfo.apiVersion			= vulkanVersion;
}

bool Instance2::isLayerSuitable(VkLayerProperties sLayer, const char **desiredLayers, uint32_t size)
{
	for (int i = 0; i < size; ++i)
		if (!strcmp(desiredLayers[i], sLayer.layerName))
			return (true);
	return (false);
}

bool Instance2::isExtensionSuitable(VkExtensionProperties sExtension, const char **desiredExtensions, uint32_t size)
{
	for (int i = 0; i < size; ++i)
		if (!strcmp(desiredExtensions[i], sExtension.extensionName))
			return (true);
	return (false);
}