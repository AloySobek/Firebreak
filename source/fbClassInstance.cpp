/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassInstance.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:35:59 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/09 20:47:37 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

Instance::Instance()
{
	sCreateInfo.pApplicationInfo = &sApplicationInfo;
	sApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	sCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
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

VkPhysicalDevice	*Instance::getPhysicalDevices()
{
	if (!calledDevices)
	{
		vkEnumeratePhysicalDevices(self, &availablePhysicalDeviceCount, nullptr);
		pAvailablePhysicalDevices = new VkPhysicalDevice[availablePhysicalDeviceCount];
		vkEnumeratePhysicalDevices(self, &availablePhysicalDeviceCount, pAvailablePhysicalDevices);
		calledDevices = true;
	}
	return (pAvailablePhysicalDevices);
}

VkPhysicalDevice	*Instance::getPhysicalDevices(uint32_t *size)
{
	getPhysicalDevices();
	*size = availablePhysicalDeviceCount;
	return (pAvailablePhysicalDevices);
}

void Instance::setLayers(const char **desiredLayers, uint32_t size)
{
	getAvailableLayers();
	for (int i = 0; i < availableLayersCount; ++i)
		if (isLayerSuitable(pAvailableLayers[i], desiredLayers, size))
			((char **)sCreateInfo.ppEnabledLayerNames)[sCreateInfo.enabledLayerCount++] = pAvailableLayers[i].layerName;
}

void Instance::setExtensions(const char **desiredExtensions, uint32_t size)
{
	getAvailableExtensions();
	for (int i = 0; i < availableExtensionsCount; ++i)
		if (isExtensionSuitable(pAvailableExtensions[i], desiredExtensions, size))
			((char **)sCreateInfo.ppEnabledExtensionNames)[sCreateInfo.enabledExtensionCount++] = pAvailableExtensions[i].extensionName;
}

VkInstance Instance::getSelf(void)
{
	assert(self);
	return (self);
}

VkLayerProperties	*Instance::getAvailableLayers()
{
	if (!calledLayers)
	{
		vkEnumerateInstanceLayerProperties(&availableLayersCount, nullptr);
		pAvailableLayers = new VkLayerProperties[availableLayersCount];
		sCreateInfo.ppEnabledLayerNames = new const char *[availableLayersCount];
		vkEnumerateInstanceLayerProperties(&availableLayersCount, pAvailableLayers);
		calledLayers = true;
	}
	return (pAvailableLayers);
}

VkLayerProperties	*Instance::getAvailableLayers(uint32_t *size)
{
	*size = availableLayersCount;
	return (getAvailableLayers());
}

VkExtensionProperties	*Instance::getAvailableExtensions()
{
	if (!calledExtensions)
	{
		vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, nullptr);
		pAvailableExtensions = new VkExtensionProperties[availableExtensionsCount];
		sCreateInfo.ppEnabledExtensionNames = new const char *[availableExtensionsCount];
		vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, pAvailableExtensions);
		calledExtensions = true;
	}
	return (pAvailableExtensions);
}

VkExtensionProperties	*Instance::getAvailableExtensions(uint32_t *size)
{
	*size = availableExtensionsCount;
	return (getAvailableExtensions());
}

void Instance::create(int mode)
{
	if ((codeOfError = vkCreateInstance(&sCreateInfo, mode ? &sAllocation : nullptr, &self)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << codeOfError << std::endl;
		throw std::runtime_error("Failed to create instance");
	}
}

VkInstance Instance::operator()(void)
{
	return (getSelf());
}

bool Instance::isLayerSuitable(VkLayerProperties sLayer, const char **desiredLayers, uint32_t size)
{
	for (int i = 0; i < size; ++i)
		if (!strcmp(desiredLayers[i], sLayer.layerName))
			return (true);
	return (false);
}

bool Instance::isExtensionSuitable(VkExtensionProperties sExtension, const char **desiredExtensions, uint32_t size)
{
	for (int i = 0; i < size; ++i)
		if (!strcmp(desiredExtensions[i], sExtension.extensionName))
			return (true);
	return (false);
}