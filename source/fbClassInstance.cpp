/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassInstance.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:35:59 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/25 14:08:13 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

Instance::Instance()
{
	sCreateInfo.sType				= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	sCreateInfo.pApplicationInfo	= &sApplicationInfo;
	sApplicationInfo.sType			= VK_STRUCTURE_TYPE_APPLICATION_INFO;
}

VkInstance	Instance::getSelf(void)
{
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

VkLayerProperties	*Instance::getLayers(uint32_t *size)
{
	if (!pAvailableLayers)
	{
		if ((codeOfError = vkEnumerateInstanceLayerProperties(&availableLayersCount, nullptr)) != VK_SUCCESS)
			throw std::runtime_error("Failed to enumerate instance layer properties");
		pAvailableLayers = new VkLayerProperties[availableLayersCount];
		sCreateInfo.ppEnabledLayerNames = new const char *[availableLayersCount];
		if ((codeOfError = vkEnumerateInstanceLayerProperties(&availableLayersCount, pAvailableLayers)) != VK_SUCCESS)
			throw std::runtime_error("Failed to enumerate instance layer properties");
	}
	size ? *size = availableLayersCount : false;
	return (pAvailableLayers);
}

VkExtensionProperties	*Instance::getExtensions(uint32_t *size)
{
	if (!pAvailableExtensions)
	{
		if ((codeOfError = vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, nullptr)) != VK_SUCCESS)
			throw std::runtime_error("Failed to enumerate instance extension properties");
		pAvailableExtensions = new VkExtensionProperties[availableExtensionsCount];
		sCreateInfo.ppEnabledExtensionNames = new const char *[availableExtensionsCount];
		if ((codeOfError = vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, pAvailableExtensions)) != VK_SUCCESS)
			throw std::runtime_error("Failed to enumerate instance extension properties");
	}
	size ? *size = availableExtensionsCount : false;
	return (pAvailableExtensions);
}

VkPhysicalDevice	*Instance::getPhysicalDevices(uint32_t *size)
{
	if (!pAvailablePhysicalDevices)
	{
		if ((codeOfError = vkEnumeratePhysicalDevices(self, &availablePhysicalDeviceCount, nullptr)) != VK_SUCCESS)
			throw std::runtime_error("Failed to enumerate physical devices");
		pAvailablePhysicalDevices = new VkPhysicalDevice[availablePhysicalDeviceCount];
		if ((codeOfError = vkEnumeratePhysicalDevices(self, &availablePhysicalDeviceCount, pAvailablePhysicalDevices)) != VK_SUCCESS)
			throw std::runtime_error("Failed to enumerate physical devices");
	}
	size ? *size = availablePhysicalDeviceCount : false;
	return (pAvailablePhysicalDevices);
}

int32_t	Instance::getErrorCode()
{
	return (codeOfError);
}

void Instance::create()
{
	if ((codeOfError = vkCreateInstance(&sCreateInfo, sAllocation.pfnAllocation ? &sAllocation : nullptr, &self)) != VK_SUCCESS)
		throw std::runtime_error("Failed to create instance");
	clear();
}

void Instance::clear(uint32_t mode)
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
	if (self && (mode & FINISH_HIM))
	{
		vkDestroyInstance(self, sAllocation.pfnFree ? &sAllocation : nullptr);
		self = VK_NULL_HANDLE;
	}
}

Instance::~Instance()
{
	clear(FINISH_HIM);
}

void Instance2::setLayers(const char **desiredLayers, uint32_t size)
{
	safeCall(getLayers);
	for (int i = 0; i < availableLayersCount; ++i)
		if (isLayerSuitable(pAvailableLayers[i], desiredLayers, size))
			((char **)sCreateInfo.ppEnabledLayerNames)[sCreateInfo.enabledLayerCount++] = pAvailableLayers[i].layerName;
}

void Instance2::setExtensions(const char **desiredExtensions, uint32_t size)
{
	safeCall(getExtensions);
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