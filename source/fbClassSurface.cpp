/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassSurface.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:58:58 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/08 16:23:49 by Rustam           ###   ########.fr       */
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

void Surface::setFlags(VkSwapchainCreateFlagsKHR flags)
{
	sSwapchainCreateInfo.flags = flags;
}

void Surface::setNext(const void *pNext)
{
	sSwapchainCreateInfo.pNext = pNext;
}

void Surface::setClipped(VkBool32 clipped)
{
	sSwapchainCreateInfo.clipped = clipped;
}

void Surface::setImageCount(uint32_t imagesCount)
{
	this->imagesCount = imagesCount;
	if (sCapabilities.maxImageCount > 0 &&
	this->imagesCount > sCapabilities.maxImageCount)
		this->imagesCount = sCapabilities.maxImageCount;
}

void Surface::setImageArrayLayers(uint32_t imageLayers)
{
	sSwapchainCreateInfo.imageArrayLayers = imageLayers;
}

void Surface::setImageUsage(int32_t imageUsage)
{
	sSwapchainCreateInfo.imageUsage = imageUsage;
}

void Surface::setOldSwapChain(VkSwapchainKHR oldSwapchain)
{
	sSwapchainCreateInfo.oldSwapchain = oldSwapchain;
}

void Surface::setCompositeAlpha(VkCompositeAlphaFlagBitsKHR composite)
{
	sSwapchainCreateInfo.compositeAlpha = composite;
}

bool Surface::setupFormat(VkFormat format, VkColorSpaceKHR colorSpace)
{
	for (int i = 0; i < khrFormatsCount; ++i)
	{
		sFormat = pFormats[i];
		if (sFormat.format == format &&
		sFormat.colorSpace == colorSpace)
			return (true);
	}
	sFormat = pFormats[0];
	return (false);
}

bool Surface::setupPresentMode(VkPresentModeKHR presentMode)
{
	for (int i = 0; i < khrPresentModesCount; ++i)
	{
		sPresentMode = pPresentModes[i];
		if (sPresentMode == presentMode)
			return (true);
	}
	sPresentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
	return (false);
}

bool Surface::setupExtent()
{
	if (sCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
		extent = sCapabilities.currentExtent;
	else
	{
		extent.width = std::max(sCapabilities.minImageExtent.width,
		std::min(sCapabilities.maxImageExtent.width, extent.width));
		extent.height = std::max(sCapabilities.minImageExtent.height,
		std::min(sCapabilities.maxImageExtent.height, extent.height));
		return (true);
	}
	return (false);
}

VkSurfaceCapabilitiesKHR	*Surface::getCapabilities(Device &device)
{
	if (!calledCapabil)
	{
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(!device, self, &sCapabilities);
		calledCapabil = true;
	}
	return (&sCapabilities);
}

VkSurfaceCapabilitiesKHR	*Surface::getCapabilities()
{
	return (&sCapabilities);
}

VkSurfaceFormatKHR	*Surface::getFormats(Device &device)
{
	if (!calledFormats)
	{
		vkGetPhysicalDeviceSurfaceFormatsKHR(!device, self, &khrFormatsCount, nullptr);
		pFormats = (VkSurfaceFormatKHR *)malloc(sizeof(VkSurfaceFormatKHR) * khrFormatsCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(!device, self, &khrFormatsCount, pFormats);
		calledFormats = true;
	}
	return (pFormats);
}

VkSurfaceFormatKHR	*Surface::getFormat()
{
	return (&sFormat);
}

VkPresentModeKHR	*Surface::getPresentModes(Device &device)
{
	if (!calledPresent)
	{
		vkGetPhysicalDeviceSurfacePresentModesKHR(!device, self, &khrPresentModesCount, nullptr);
		pPresentModes = (VkPresentModeKHR *)malloc(sizeof(VkPresentModeKHR) * khrPresentModesCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(!device, self, &khrPresentModesCount, pPresentModes);
		calledPresent = true;
	}
	return (pPresentModes);
}

VkPresentModeKHR	*Surface::getPresentMode()
{
	return (&sPresentMode);
}

VkImage	*Surface::getImages(Device &device)
{
	if (!calledImages)
	{
		vkGetSwapchainImagesKHR(device.getSelf(), swapchain, &imagesCount, nullptr);
		pImages = (VkImage *)malloc(sizeof(VkImage) * imagesCount);
		vkGetSwapchainImagesKHR(device.getSelf(), swapchain, &imagesCount, pImages);
		calledImages = true;
	}
	return (pImages);
}

void Surface::checkSwapChainSupporting(Device &device)
{
	getCapabilities(device);
	getPresentModes(device);
	getFormats(device);
	if (!khrFormatsCount || !khrPresentModesCount)
		throw std::runtime_error("Device does not support swap chain");
}

void Surface::create(Instance &instance)
{
	assert(pWindow);
	if ((codeOfError = glfwCreateWindowSurface(instance(), (GLFWwindow *)pWindow, nullptr, &self)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << codeOfError << std::endl;
		throw std::runtime_error("Failed to create window surface");
	}
}

void Surface::create(Instance &instance, void *pWindow)
{
	this->pWindow = pWindow;
	create(instance);
}

void	Surface::createSwapchain(Device &device)
{
	imagesCount = sCapabilities.minImageCount + 1;
	if (sCapabilities.maxImageCount > 0 && imagesCount > sCapabilities.maxImageCount)
		imagesCount = sCapabilities.maxImageCount;
	sSwapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	sSwapchainCreateInfo.surface = self;
	sSwapchainCreateInfo.imageExtent = extent;
	sSwapchainCreateInfo.imageFormat = sFormat.format;
	sSwapchainCreateInfo.presentMode = sPresentMode;
	sSwapchainCreateInfo.preTransform = sCapabilities.currentTransform;
	sSwapchainCreateInfo.imageColorSpace = sFormat.colorSpace;
	if (device.pQueues[VK_QUEUE_GRAPHICS_BIT].index != device.pQueues[VK_QUEUE_PRESENT_BIT].index)
	{
		sSwapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		sSwapchainCreateInfo.pQueueFamilyIndices = device.requireIndexArray();
		sSwapchainCreateInfo.queueFamilyIndexCount = sSwapchainCreateInfo.pQueueFamilyIndices[VK_QUEUE_PROTECTED_BIT - 1];
	}
	else
		sSwapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	if ((codeOfError = vkCreateSwapchainKHR(device.getSelf(), &sSwapchainCreateInfo, nullptr, &swapchain)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << codeOfError << std::endl;
		throw std::runtime_error("Failed to creat SwapChain");
	}
}

void	Surface::operator()(Instance &instance)
{
	create(instance);
}

void	Surface::operator()(Instance &instance, void *pWindow)
{
	create(instance, pWindow);
}


void	Surface::operator()(Device &device)
{
	createSwapchain(device);
}

void	Surface::setupImageView(Device &device)
{
	VkImageViewCreateInfo	sImageViewCreateInfo = {};

	pImageViewList = new VkImageView[imagesCount];
	for (int i = 0; i < imagesCount; ++i)
	{
		sImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		sImageViewCreateInfo.image = pImages[i];
		sImageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		sImageViewCreateInfo.format = sFormat.format;
		sImageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		sImageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		sImageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		sImageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		sImageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		sImageViewCreateInfo.subresourceRange.baseMipLevel = 0;
		sImageViewCreateInfo.subresourceRange.levelCount = 1;
		sImageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
		sImageViewCreateInfo.subresourceRange.layerCount = 1;
		sImageViewCreateInfo.pNext = nullptr;
		sImageViewCreateInfo.flags = 0;

		if ((codeOfError = vkCreateImageView(device.getSelf(), &sImageViewCreateInfo, nullptr, &pImageViewList[i])))
		{
			std::cout << "Code of error: " << codeOfError << std::endl;
			throw std::runtime_error("Failed to create image view object");
		}
	}
}
