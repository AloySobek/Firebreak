/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassPhysicalDevice.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:29:48 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/02 18:38:34 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vkClassContainer.hpp"

void PhysicalDevice::getInfo()
{
	vkGetPhysicalDeviceFeatures(self, &sFeatures);
	vkGetPhysicalDeviceProperties(self, &sProperties);
}

std::vector<VkLayerProperties>	PhysicalDevice::getLayers()
{
	if (!calledLayers)
	{
		vkEnumerateDeviceLayerProperties(self, &availableLayersCount, nullptr);
		pAvailableLayers.resize(availableLayersCount);
		ppSelectedLayers.resize(availableLayersCount);
		vkEnumerateDeviceLayerProperties(self, &availableLayersCount, pAvailableLayers.data());
		calledLayers = true;
	}
	return (pAvailableLayers);
}

std::vector<VkExtensionProperties> PhysicalDevice::getExtensions()
{
	if (!calledExtensions)
	{
		vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, nullptr);
		pAvailableExtensions.resize(availableExtensionsCount);
		ppSelectedExtensions.resize(availableExtensionsCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, pAvailableExtensions.data());
		calledExtensions = true;
	}
	return (pAvailableExtensions);
}

void PhysicalDevice::setupLayers(std::vector<const char *> &desiredLayers)
{
	getLayers();
	for (int i = 0; i < availableLayersCount; ++i)
		if (isLayerSuitable(pAvailableLayers[i], desiredLayers))
			ppSelectedLayers[selectedLayersCount++] = pAvailableLayers[i].layerName;
	ppSelectedLayers.resize(selectedLayersCount);
}

bool PhysicalDevice::isLayerSuitable(VkLayerProperties sLayer, std::vector<const char *> &desiredLayers)
{
	for (int i = 0; i < desiredLayers.size(); ++i)
		if (!strcmp(desiredLayers[i], sLayer.layerName))
			return (true);
	return (false);
}

void PhysicalDevice::setupExtensions(std::vector<const char *> &desiredExtensions)
{
	getExtensions();
	for (int i = 0; i < availableExtensionsCount; ++i)
		if (isExtensionSuitable(pAvailableExtensions[i], desiredExtensions))
			ppSelectedExtensions[selectedExtensionsCount++] = pAvailableExtensions[i].extensionName;
	ppSelectedExtensions.resize(selectedExtensionsCount);
}

bool PhysicalDevice::isExtensionSuitable(VkExtensionProperties sExtension, std::vector<const char *> &desiredExtensions)
{
	for (int i = 0; i < desiredExtensions.size(); ++i)
		if (!strcmp(desiredExtensions[i], sExtension.extensionName))
			return (true);
	return (false);
}

std::vector<VkQueueFamilyProperties> PhysicalDevice::getQueueFamilies()
{
	if (!calledQeueueFamilies)
	{
		vkGetPhysicalDeviceQueueFamilyProperties(self, &availableQueuesFamilies, nullptr);
		pAvailableQueuesFamilies.resize(availableQueuesFamilies);
		vkGetPhysicalDeviceQueueFamilyProperties(self, &availableQueuesFamilies, pAvailableQueuesFamilies.data());
		calledQeueueFamilies = true;
	}
	return (pAvailableQueuesFamilies);
}

void PhysicalDevice::checkSurfaceSupportAndSetupPresentQueue(Surface surface)
{
	VkBool32 presentQueueFamilySupport = false;

	getQueueFamilies();
	for (int i = 0; i < pAvailableQueuesFamilies.size(); ++i)
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(self, i, surface.self, &presentQueueFamilySupport);
		if (presentQueueFamilySupport)
		{
			presentQueueFamilyIndex = i;
			break;
		}
	}
	if (!presentQueueFamilySupport)
		throw std::runtime_error("Device not compatible with surface");
}

void PhysicalDevice::setupQueue(int type)
{
	getQueueFamilies();
	for (int i = 0; i < pAvailableQueuesFamilies.size(); ++i)
		if (pAvailableQueuesFamilies[i].queueCount > 0)
			if (pAvailableQueuesFamilies[i].queueFlags & type && type == VK_QUEUE_GRAPHICS_BIT)
				graphicQueueFamilyIndex = i;
	if (graphicQueueFamilyIndex < 0)
		throw std::runtime_error("Failed to find physical queue for gpu");
}