/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassSurface.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:58:58 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/03 20:59:41 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vkClassContainer.hpp"

Surface::Surface(GLFWwindow *pWindow, Instance instance)
{
	if ((codeOfError = glfwCreateWindowSurface(instance(), pWindow, nullptr, &self)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << codeOfError << std::endl;
		throw std::runtime_error("Failed to create Surface");
	}
}

void Surface::init(GLFWwindow *pWindow, Instance instance)
{
	if ((codeOfError = glfwCreateWindowSurface(instance(), pWindow, nullptr, &self)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << codeOfError << std::endl;
		throw std::runtime_error("Failed to create Surface");
	}
}

std::vector<VkSurfaceFormatKHR>	Surface::getFormats(Device device)
{
	if (!calledFormats)
	{
		vkGetPhysicalDeviceSurfaceFormatsKHR(device.physicalSelf, self, &khrFormatsCount, nullptr);
		formats.resize(khrFormatsCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device.physicalSelf, self, &khrFormatsCount, formats.data());
		calledFormats = true;
	}
	return (formats);
}

std::vector<VkPresentModeKHR>	Surface::getPresentModes(Device device)
{
	if (!calledPresent)
	{
		vkGetPhysicalDeviceSurfacePresentModesKHR(device.physicalSelf, self, &khrPresentModesCount, nullptr);
		presentModes.resize(khrPresentModesCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device.physicalSelf, self, &khrPresentModesCount, presentModes.data());
		calledPresent = true;
	}
	return (presentModes);
}

void Surface::checkSwapChainSupporting(Device device)
{
	getFormats(device);
	getPresentModes(device);
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device.physicalSelf, self, &capabilities);

	if (!khrFormatsCount or !khrPresentModesCount)
		throw std::runtime_error("Device does not support swap chain");
}
