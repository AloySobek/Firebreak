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

FbInstance::FbInstance(VkInstanceCreateInfo info, VkAllocationCallbacks allocation)
	: self{VK_NULL_HANDLE}, sCreateInfo{info}, sAllocation{allocation}, codeOfError{false}
{
	sCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
}

void FbInstance::create()
{
	codeOfError = vkCreateInstance(&sCreateInfo, sAllocation.pfnAllocation ? &sAllocation : nullptr, &self);
	THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to create instance");
}

void FbInstance::destroy()
{
	vkDestroyInstance(self, sAllocation.pfnFree ? &sAllocation : nullptr);
	self = VK_NULL_HANDLE;
}

/*
** This border to the next layer of firebreak framework <><><><><><><><><><><><><><><><><>
** This border to the next layer of firebreak framework <><><><><><><><><><><><><><><><><>
** This border to the next layer of firebreak framework <><><><><><><><><><><><><><><><><>
*/

FbInstance2::FbInstance2(std::vector<char *> &extensions, std::vector<char *> &layers) : FbInstance()
{
	if (&layers != &namesStub)
	{
		SAFECALL(getLayers);
		setLayers(layers);
	}
	if (&extensions != &namesStub)
	{
		SAFECALL(getExtensions);
		setExtensions(extensions);
	}
}

std::vector<VkLayerProperties>	&FbInstance2::getLayers()
{
	if (!availableLayers.size())
	{
		uint32_t	count{0};

		codeOfError = vkEnumerateInstanceLayerProperties(&count, nullptr);
		THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to enumerate instance layer properties");
		availableLayers.resize(count);
		codeOfError = vkEnumerateInstanceLayerProperties(&count, availableLayers.data());
		THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to enumerate instance layer properties");
	}
	return (availableLayers);
}

std::vector<VkExtensionProperties>	&FbInstance2::getExtensions(const char *pLayerName)
{
	if (!availableExtensions.size())
	{
		uint32_t	count{0};

		codeOfError = vkEnumerateInstanceExtensionProperties(pLayerName, &count, nullptr);
		THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to enumerate instance extension properties");
		availableExtensions.resize(count);
		codeOfError = vkEnumerateInstanceExtensionProperties(nullptr, &count, availableExtensions.data());
		THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to enumerate instance extension properties");
	}
	return (availableExtensions);
}

std::vector<VkPhysicalDevice>	&FbInstance2::getPhysicalDevices()
{
	if (!availablePhysicalDevices.size())
	{
		uint32_t	count{0};

		codeOfError = vkEnumeratePhysicalDevices(self, &count, nullptr);
		THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to enumerate physical devices");
		availablePhysicalDevices.resize(count);
		codeOfError = vkEnumeratePhysicalDevices(self, &count, availablePhysicalDevices.data());
		THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to enumerate phsyical devices");
	}
	return (availablePhysicalDevices);
}

void FbInstance2::setAppInfo(const char *pName, uint32_t appVersion, const char *pEngineName,
								uint32_t engineVersion, uint32_t vulkanVersion, void *pNext)
{
	sApplicationInfo =
	{
		VK_STRUCTURE_TYPE_APPLICATION_INFO,
		pNext,
		pName,
		appVersion,
		pEngineName,
		engineVersion,
		vulkanVersion
	};
	sCreateInfo.pApplicationInfo = &sApplicationInfo;
}

void FbInstance2::setLayers(std::vector<char *> &desiredLayers)
{
	SAFECALL(getLayers);
	for (int i = 0; i < availableLayers.size(); ++i)
		if (isLayerSuitable(availableLayers[i], desiredLayers, size))
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

void FbInstance2::setAppInfo(const char *pName, uint32_t appVersion, const char *pEngineName, uint32_t engineVersion, uint32_t vulkanVersion)
{

}

bool Instance2::isLayerSuitable(VkLayerProperties sLayer, const char **desiredLayers, uint32_t size)
{
	for (int i = 0; i < size; ++i)
		if (!strcmp(desiredLayers[i], sLayer.layerName))
			return (true);
	return (false);
}