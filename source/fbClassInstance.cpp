/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassInstance.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:35:59 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/08 19:14:40 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

Instance::Instance(const void *pNext)
{
	sCreateInfo.pNext = pNext;
	sCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	sCreateInfo.pApplicationInfo = nullptr;
}

Instance::Instance(VkInstanceCreateFlags flags, const void *pNext) : Instance(pNext)
{
	sCreateInfo.flags = flags;
}

void	Instance::setupAppInfo(const char *pAppName, const char *pEngineName, uint32_t appVersion, uint32_t engineVersion)
{
	sApplicationInfo.sType				= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	sApplicationInfo.pNext				= nullptr;
	sApplicationInfo.pApplicationName	= pAppName;
	sApplicationInfo.pEngineName		= pEngineName;
	sApplicationInfo.engineVersion		= engineVersion;
	sApplicationInfo.apiVersion			= appVersion;
}

void	Instance::setupFlags(VkInstanceCreateFlags flags)
{
	sCreateInfo.flags = flags;
}

void	Instance::setupNext(const void *pNext)
{
	sCreateInfo.pNext = pNext;
}

void Instance::setupLayers(std::vector<const char *> &desiredLayers)
{
	getLayers();
	for (int i = 0; i < availableLayersCount; ++i)
		if (isLayerSuitable(pAvailableLayers[i], desiredLayers))
			ppEnabledLayerNames[enabledLayerCount++] = pAvailableLayers[i].layerName;
}

void Instance::setupExtensions(std::vector<const char *> &desiredExtensions)
{
	getExtensions();
	for (int i = 0; i < availableExtensionsCount; ++i)
		if (isExtensionSuitable(pAvailableExtensions[i], desiredExtensions))
			ppEnabledExtensionNames[enabledExtensionCount++] = pAvailableExtensions[i].extensionName;
}

VkInstance Instance::getSelf(void)
{
	assert(self);
	return (self);
}

VkInstanceCreateFlags	Instance::getFlags()
{
	return (sCreateInfo.flags);
}

const void	*Instance::getNext()
{
	return (sCreateInfo.pNext);
}

const VkApplicationInfo	*Instance::getAppInfo()
{
	return (sCreateInfo.pApplicationInfo);
}

VkLayerProperties	*Instance::getLayers()
{
	if (!calledLayers)
	{
		vkEnumerateInstanceLayerProperties(&availableLayersCount, nullptr);
		pAvailableLayers = new VkLayerProperties[availableLayersCount];
		ppEnabledLayerNames = new const char *[availableExtensionsCount];
		vkEnumerateInstanceLayerProperties(&availableLayersCount, pAvailableLayers);
		calledLayers = true;
	}
	return (pAvailableLayers);
}

VkExtensionProperties	*Instance::getExtensions()
{
	if (!calledExtensions)
	{
		vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, nullptr);
		pAvailableExtensions = new VkExtensionProperties[availableExtensionsCount];
		ppEnabledExtensionNames = new const char *[availableExtensionsCount];
		vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, pAvailableExtensions);
		calledExtensions = true;
	}
	return (pAvailableExtensions);
}

uint32_t	Instance::getLayersAmount()
{
	return (availableLayersCount);
}

uint32_t	Instance::getExtensionsAmount()
{
	return (availableExtensionsCount);
}

void Instance::create()
{
	sCreateInfo.enabledLayerCount		= enabledLayerCount;
	sCreateInfo.ppEnabledLayerNames		= ppEnabledLayerNames;
	sCreateInfo.enabledExtensionCount	= enabledExtensionCount;
	sCreateInfo.ppEnabledExtensionNames	= ppEnabledExtensionNames;
	if ((codeOfError = vkCreateInstance(&sCreateInfo, nullptr, &self)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << codeOfError << std::endl;
		throw std::runtime_error("Failed to create instance");
	}
}

VkInstance Instance::operator()(void)
{
	if (!self)
		create();
	return (self);
}

bool Instance::isLayerSuitable(VkLayerProperties sLayer, std::vector<const char *> &desiredLayers)
{
	for (int i = 0; i < desiredLayers.size(); ++i)
		if (!strcmp(desiredLayers[i], sLayer.layerName))
			return (true);
	return (false);
}

bool Instance::isExtensionSuitable(VkExtensionProperties sExtension, std::vector<const char *> &desiredExtensions)
{
	for (int i = 0; i < desiredExtensions.size(); ++i)
		if (!strcmp(desiredExtensions[i], sExtension.extensionName))
			return (true);
	return (false);
}