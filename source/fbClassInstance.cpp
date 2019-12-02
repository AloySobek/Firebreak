/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassInstance.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 13:35:59 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/02 18:09:41 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vkClassContainer.hpp"

void Instance::setupAppInfo(const char *pAppName, const char *pEngineName,
						uint32_t appVersion, uint32_t engineVersion)
{
	sAppCreateInfo.sType				= VK_STRUCTURE_TYPE_APPLICATION_INFO;
	sAppCreateInfo.pApplicationName		= pAppName ? pAppName : "Firebreak";
	sAppCreateInfo.applicationVersion	= appVersion;
	sAppCreateInfo.pEngineName			= pEngineName ? pEngineName : "NoEngine";
	sAppCreateInfo.engineVersion		= engineVersion;
	sAppCreateInfo.apiVersion			= VK_API_VERSION_1_1;
	sAppCreateInfo.pNext				= nullptr;
}

std::vector<VkLayerProperties> Instance::getLayers()
{
	if (!calledLayers)
	{
		vkEnumerateInstanceLayerProperties(&availableInstanceLayersCount, nullptr);
		pAvailableInstanceLayers.resize(availableInstanceLayersCount);
		ppSelectedLayers.resize(availableInstanceLayersCount);
		vkEnumerateInstanceLayerProperties(&availableInstanceLayersCount, pAvailableInstanceLayers.data());
		calledLayers = true;
	}
	return (pAvailableInstanceLayers);
}

std::vector<VkExtensionProperties> Instance::getExtensions()
{
	if (!calledExtensions)
	{
		vkEnumerateInstanceExtensionProperties(nullptr, &availableInstanceExtensionsCount, nullptr);
		pAvailableInstanceExtensions.resize(availableInstanceExtensionsCount);
		ppSelectedExtensions.resize(availableInstanceExtensionsCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &availableInstanceExtensionsCount, pAvailableInstanceExtensions.data());
		calledExtensions = true;
	}
	return (pAvailableInstanceExtensions);
}

void Instance::setupLayers(std::vector<const char *> &desiredLayers)
{
	getLayers();
	for (int i = 0; i < availableInstanceLayersCount; ++i)
		if (isLayerSuitable(pAvailableInstanceLayers[i], desiredLayers))
			ppSelectedLayers[selectedInstanceLayersCount++] = pAvailableInstanceLayers[i].layerName;
	ppSelectedLayers.resize(selectedInstanceLayersCount);
}

bool Instance::isLayerSuitable(VkLayerProperties sLayer, std::vector<const char *> &desiredLayers)
{
	for (int i = 0; i < desiredLayers.size(); ++i)
		if (!strcmp(desiredLayers[i], sLayer.layerName))
			return (true);
	return (false);
}

void Instance::setupExtensions(std::vector<const char *> &desiredExtensions)
{
	getExtensions();
	for (int i = 0; i < availableInstanceExtensionsCount; ++i)
		if (isExtensionSuitable(pAvailableInstanceExtensions[i], desiredExtensions))
			ppSelectedExtensions[selectedInstanceExtensionsCount++] = pAvailableInstanceExtensions[i].extensionName;
	ppSelectedExtensions.resize(selectedInstanceExtensionsCount);
}

bool Instance::isExtensionSuitable(VkExtensionProperties sExtension, std::vector<const char *> &desiredExtensions)
{
	for (int i = 0; i < desiredExtensions.size(); ++i)
		if (!strcmp(desiredExtensions[i], sExtension.extensionName))
			return (true);
	return (false);
}

void Instance::setupCreateInfo()
{
	sSelfCreateInfo.sType					= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	sSelfCreateInfo.pApplicationInfo		= &sAppCreateInfo;
	sSelfCreateInfo.enabledLayerCount		= selectedInstanceLayersCount;
	sSelfCreateInfo.ppEnabledLayerNames		= ppSelectedLayers.data();
	sSelfCreateInfo.enabledExtensionCount	= selectedInstanceExtensionsCount;
	sSelfCreateInfo.ppEnabledExtensionNames	= ppSelectedExtensions.data();
	sSelfCreateInfo.flags					= VK_NULL_HANDLE;
	sSelfCreateInfo.pNext 					= nullptr;
}

void Instance::create()
{
	if ((codeOfError = vkCreateInstance(&sSelfCreateInfo, nullptr, &self)) != VK_SUCCESS)
		error("Failed to create Instance(Vulkan object)");
}

void Instance::findDevice(int deviceType)
{
	vkEnumeratePhysicalDevices(self, &availablePhysicalDeviceCount, nullptr);
	pAvailablePhysicalDevices.resize(availablePhysicalDeviceCount);
	vkEnumeratePhysicalDevices(self, &availablePhysicalDeviceCount, pAvailablePhysicalDevices.data());
	for (int i = 0; i < availablePhysicalDeviceCount; ++i)
	{
		physicalDevice.self = pAvailablePhysicalDevices[i];
		if (isDeviceSuitable(deviceType))
			break;
	}
	if (physicalDevice.sProperties.deviceType != deviceType)
		throw std::runtime_error("Failed suit GPU");
}

bool Instance::isDeviceSuitable(int deviceType)
{
	physicalDevice.getInfo();
	return (physicalDevice.sProperties.deviceType == deviceType);
}

void Instance::createSurface(GLFWwindow *pWindow)
{
	if ((codeOfError = glfwCreateWindowSurface(self, pWindow, nullptr, &surface.self)) != VK_SUCCESS)
		error("Failed to craete window surface");
}

void Instance::error(const char *error_message)
{
	std::cout << "Code of error: " << codeOfError << "\n";
	throw std::runtime_error(error_message);
}

VkInstance Instance::getSelf(void)
{
	assert(self);
	return (self);
}

VkInstance Instance::operator()(void)
{
	assert(self);
	return (self);
}