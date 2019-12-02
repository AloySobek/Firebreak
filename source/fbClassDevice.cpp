/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassDevice.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:32:38 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/02 18:50:55 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vkClassContainer.hpp"

void Device::attachWithPhysicalDevice(PhysicalDevice &device)
{
	physicalDevice = device;
}

void Device::setupQueueFamilyCreateInfo(float queuePriority, int queueCount, int queueIndex)
{
	queuesFamilies.resize(queueFamilyCreateInfoCount + 1);
	queuesFamilies[queueFamilyCreateInfoCount].sType			= VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queuesFamilies[queueFamilyCreateInfoCount].queueCount		= queueCount;
	queuesFamilies[queueFamilyCreateInfoCount].queueFamilyIndex	= queueIndex;
	queuesFamilies[queueFamilyCreateInfoCount].pQueuePriorities	= &queuePriority;
	queuesFamilies[queueFamilyCreateInfoCount].pNext			= nullptr;
	queuesFamilies[queueFamilyCreateInfoCount++].flags			= 0;
}

void Device::setupCreateInfo()
{
	sCreateInfo.sType					= VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	sCreateInfo.pEnabledFeatures		= &physicalDevice.sFeatures;
	sCreateInfo.enabledLayerCount		= physicalDevice.selectedLayersCount;
	sCreateInfo.ppEnabledLayerNames		= physicalDevice.ppSelectedLayers.data();
	sCreateInfo.enabledExtensionCount	= physicalDevice.selectedExtensionsCount;
	sCreateInfo.ppEnabledExtensionNames	= physicalDevice.ppSelectedExtensions.data();
	sCreateInfo.pQueueCreateInfos		= queuesFamilies.data();
	sCreateInfo.queueCreateInfoCount	= queueFamilyCreateInfoCount;
	sCreateInfo.flags					= 0;
	sCreateInfo.pNext					= nullptr;
}

void Device::create()
{
	if ((codeOfError = vkCreateDevice(physicalDevice.self, &sCreateInfo, nullptr, &self)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << codeOfError << std::endl;
		throw std::runtime_error("Failed to create logical device");
	}
}

void Device::retrieveAllQueus()
{
	vkGetDeviceQueue(self, physicalDevice.graphicQueueFamilyIndex, 0, &graphicQueue);
	vkGetDeviceQueue(self, physicalDevice.presentQueueFamilyIndex, 0, &presentQueue);
}