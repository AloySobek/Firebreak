/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassSurface.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:58:58 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/04 20:56:34 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

Surface::Surface(void *pWindow)
{
	this->pWindow = pWindow;
}

void Surface::setWindow(void *pWindow)
{
	this->pWindow = pWindow;
}

VkSurfaceCapabilitiesKHR	*Surface::getCapabilities(Device device)
{
	if (!calledCapabil)
	{
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device.physicalSelf, self, &sCapabilities);
		calledCapabil = true;
	}
	return (&sCapabilities);
}

VkSurfaceFormatKHR	*Surface::getFormats(Device device)
{
	if (!calledFormats)
	{
		vkGetPhysicalDeviceSurfaceFormatsKHR(device.physicalSelf, self, &khrFormatsCount, nullptr);
		pFormats = (VkSurfaceFormatKHR *)malloc(sizeof(VkSurfaceFormatKHR) * khrFormatsCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device.physicalSelf, self, &khrFormatsCount, pFormats);
		calledFormats = true;
	}
	return (pFormats);
}

VkPresentModeKHR	*Surface::getPresentModes(Device device)
{
	if (!calledPresent)
	{
		vkGetPhysicalDeviceSurfacePresentModesKHR(device.physicalSelf, self, &khrPresentModesCount, nullptr);
		pPresentModes = (VkPresentModeKHR *)malloc(sizeof(VkPresentModeKHR) * khrPresentModesCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device.physicalSelf, self, &khrPresentModesCount, pPresentModes);
		calledPresent = true;
	}
	return (pPresentModes);
}

VkSurfaceKHR	Surface::operator()(Instance &instance)
{
	if (!self)
	{
		if (!pWindow)
			throw std::runtime_error("Failed to create surface, pointer to window has not been provided");
		if ((codeOfError = glfwCreateWindowSurface(instance(), (GLFWwindow *)pWindow, nullptr, &self)) != VK_SUCCESS)
		{
			std::cout << "Code of error: " << codeOfError << std::endl;
			throw std::runtime_error("Failed to create Surface");
		}
	}
	return (self);
}

void Surface::checkSwapChainSupporting(Device device)
{
	getCapabilities(device);
	getPresentModes(device);
	getFormats(device);
	if (!khrFormatsCount || !khrPresentModesCount)
		throw std::runtime_error("Device does not support swap chain");
}

void Surface::setupSwapChain()
{
	bool	found = false;

	for (int i = 0; i < khrFormatsCount && !found; ++i)
	{
		sFormat = pFormats[i];
		if (sFormat.format == VK_FORMAT_B8G8R8A8_UNORM &&
		sFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			found = true;
	}
	if (!found)
		sFormat = pFormats[0];
	found = false;
	for (int i = 0; i < khrPresentModesCount; ++i)
	{
		sPresentMode = pPresentModes[i];
		if (sPresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			found = true;
			break;
		}
		else if (sPresentMode == VK_PRESENT_MODE_FIFO_KHR)
			found = true;
	}
	if (!found)
		sPresentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
	if (sCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
		extent = sCapabilities.currentExtent;
	else
	{
		extent.width = std::max(sCapabilities.minImageExtent.width,
		std::min(sCapabilities.maxImageExtent.width, extent.width));
		extent.height = std::max(sCapabilities.minImageExtent.height,
		std::min(sCapabilities.maxImageExtent.height, extent.height));
	}
}

void Surface::operator()(Device &device)
{
	uint32_t	*indexArray = device.requireIndexArray();
	imageCount = sCapabilities.minImageCount + 1;
	if (sCapabilities.maxImageCount > 0 && imageCount > sCapabilities.maxImageCount)
		imageCount = sCapabilities.maxImageCount;
	sCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	sCreateInfo.surface = self;
	sCreateInfo.clipped = VK_TRUE;
	sCreateInfo.minImageCount = imageCount;
	sCreateInfo.imageFormat = sFormat.format;
	sCreateInfo.imageColorSpace = sFormat.colorSpace;
	sCreateInfo.imageExtent = extent;
	sCreateInfo.imageArrayLayers = 1;
	sCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	sCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
	sCreateInfo.queueFamilyIndexCount = 2;
	sCreateInfo.pQueueFamilyIndices = indexArray.data();
	sCreateInfo.oldSwapchain = VK_NULL_HANDLE;
	sCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	sCreateInfo.presentMode = sPresentMode;
	sCreateInfo.preTransform = surface.capabilities.currentTransform;
	sCreateInfo.flags = 0;
	sCreateInfo.pNext = nullptr;

	if ((codeOfError = vkCreateSwapchainKHR(device.self, &sCreateInfo, nullptr, &self)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << codeOfError << std::endl;
		throw std::runtime_error("Failed to creat SwapChain");
	}
	vkGetSwapchainImagesKHR(device.self, self, &imageCount, nullptr);
	images.resize(imageCount);
	vkGetSwapchainImagesKHR(device.self, self, &imageCount, images.data());
}
