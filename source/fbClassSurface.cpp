/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassSurface.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:58:58 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/02 18:36:26 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vkClassContainer.hpp"

std::vector<VkSurfaceFormatKHR>	Surface::getFormats(PhysicalDevice physicalDevice)
{
	if (!calledFormats)
	{
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice.self, self, &khrFormatsCount, nullptr);
		formats.resize(khrFormatsCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice.self, self, &khrFormatsCount, formats.data());
		calledFormats = true;
	}
	return (formats);
}

std::vector<VkPresentModeKHR>	Surface::getPresentModes(PhysicalDevice physicalDevice)
{
	if (!calledPresent)
	{
		vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice.self, self, &khrPresentModesCount, nullptr);
		presentModes.resize(khrPresentModesCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice.self, self, &khrPresentModesCount , presentModes.data());
		calledPresent = true;
	}
	return (presentModes);
}

void Surface::checkSwapChainSupporting(PhysicalDevice physicalDevice)
{
	getFormats(physicalDevice);
	getPresentModes(physicalDevice);
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice.self, self, &capabilities);

	if (!khrFormatsCount or !khrPresentModesCount)
		throw std::runtime_error("Device does not support swap chain");
}