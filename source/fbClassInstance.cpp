/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassInstance.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:35:59 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/29 15:55:17 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

Instance::Instance() : self(VK_NULL_HANDLE), sCreateInfo({}), sAllocation({}), codeOfError(false)
{
	sCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
}

VkInstance				&Instance::getSelf(void)
{
	return (self);
}

VkInstanceCreateInfo	&Instance::getCreateInfo()
{
	return (sCreateInfo);
}

VkAllocationCallbacks	&Instance::getAllocation()
{
	return (sAllocation);
}

int32_t	Instance::getErrorCode()
{
	return (codeOfError);
}

void Instance::create()
{
	codeOfError = vkCreateInstance(&sCreateInfo, sAllocation.pfnAllocation ? &sAllocation : nullptr, &self);
	THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to create instance");
}

void Instance::destroy()
{
	vkDestroyInstance(self, sAllocation.pfnFree ? &sAllocation : nullptr);
	self = VK_NULL_HANDLE;
}

Instance::~Instance()
{
	destroy();
}

/*
** This border to the next layer of firebreak framework <><><><><><><><><><><><><><><><><>
** This border to the next layer of firebreak framework <><><><><><><><><><><><><><><><><>
** This border to the next layer of firebreak framework <><><><><><><><><><><><><><><><><>
*/

Instance2::Instance2() : Instance()
{
	;
}

Instance2::Instance2(VkInstanceCreateInfo &sCreateInfo) : Instance(sCreateInfo)
{
	;
}

VkInstance		&Instance2::getSelf()
{
	assert(self);
	return (self);
}

VkLayerProperties	*Instance2::getLayers(uint32_t *size)
{
	if (!pAvailableLayers)
	{
		codeOfError = vkEnumerateInstanceLayerProperties(&availableLayersCount, nullptr);
		THROW_EXCEPTION("Failed to enumerate instance layer properties");
		pAvailableLayers = new VkLayerProperties[availableLayersCount];
		sCreateInfo.ppEnabledLayerNames	= new const char *[availableLayersCount];
		codeOfError = vkEnumerateInstanceLayerProperties(&availableLayersCount, pAvailableLayers);
		THROW_EXCEPTION("Failed to enumerate instance layer properties");
	}
	size ? *size = availableLayersCount : false;
	return (pAvailableLayers);
}

VkExtensionProperties	*Instance2::getExtensions(uint32_t *size)
{
	if (!pAvailableExtensions)
	{
		codeOfError = vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, nullptr);
		THROW_EXCEPTION("Failed to enumerate instance extension properties");
		pAvailableExtensions = new VkExtensionProperties[availableExtensionsCount];
		sCreateInfo.ppEnabledExtensionNames = new const char *[availableExtensionsCount];
		codeOfError = vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, pAvailableExtensions);
		THROW_EXCEPTION("Failed to enumerate instance extension properties");
	}
	size ? *size = availableExtensionsCount : false;
	return (pAvailableExtensions);
}

VkPhysicalDevice	*Instance2::getPhysicalDevices(uint32_t *size)
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

void Instance2::setLayers(const char **desiredLayers, uint32_t size)
{
	safeCall(getLayers);
	for (int i = 0; i < availableLayersCount; ++i)
		for (int j = 0; j < size; ++j)
			if (!strcmp(desiredLayers[i], pAvailableLayers[i].))

		if (isLayerSuitable(pAvailableLayers[i], desiredLayers, size))
			((char **)sCreateInfo.ppEnabledLayerNames)[sCreateInfo.enabledLayerCount++] = pAvailableLayers[i].layerName;
}

void Instance2::setExtensions(const char **desiredExtensions, uint32_t size)
{
	safeCall(getExtensions);
	for (int i = 0; i < availableExtensionsCount; ++i)
		for (int j = 0; j < size; ++j)
			if (!strcmp(desiredExtensions[i], pAvailableExtensions[i].extensionName))
				((char **)sCreateInfo.ppEnabledExtensionNames)[sCreateInfo.enabledExtensionCount++]
					= pAvailableExtensions[i].extensionName;
}

void Instance2::setAppInfo(const char *pName, uint32_t appVersion, const char *pEngineName, uint32_t engineVersion, uint32_t vulkanVersion)
{
	sApplicationInfo.pApplicationName	= pName;
	sApplicationInfo.applicationVersion	= appVersion;
	sApplicationInfo.pEngineName		= pEngineName;
	sApplicationInfo.engineVersion		= engineVersion;
	sApplicationInfo.apiVersion			= vulkanVersion;
	sCreateInfo.pApplicationInfo		= &sApplicationInfo;
}

bool Instance2::isLayerSuitable(VkLayerProperties sLayer, const char **desiredLayers, uint32_t size)
{
	for (int i = 0; i < size; ++i)
		if (!strcmp(desiredLayers[i], sLayer.layerName))
			return (true);
	return (false);
}