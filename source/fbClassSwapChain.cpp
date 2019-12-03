/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassSwapChain.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:44:58 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/03 20:59:42 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vkClassContainer.hpp"

void SwapChain::setupSwapChain(Surface surface)
{
	bool	found = false;

	for (int i = 0; i < surface.khrFormatsCount; ++i)
	{
		if (surface.formats[i].format == VK_FORMAT_B8G8R8A8_UNORM && surface.formats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			sFormat = surface.formats[i];
			found = true;
			break;
		}
	}
	if (!found)
		sFormat = surface.formats[0];
	found = false;
	for (int i = 0; i < surface.khrPresentModesCount; ++i)
	{
		if (surface.presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			sPresentMode = surface.presentModes[i];
			found = true;
			break;
		}
		else if (surface.presentModes[i] == VK_PRESENT_MODE_FIFO_KHR)
		{
			sPresentMode = surface.presentModes[i];
			found = true;
		}
	}
	if (!found)
		sPresentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
	if (surface.capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
	{
		std::cout << "Standart setting\n";
		extent = surface.capabilities.currentExtent;
	}
	else
	{
		extent.width = std::max(surface.capabilities.minImageExtent.width,
		std::min(surface.capabilities.maxImageExtent.width, extent.width));
		extent.height = std::max(surface.capabilities.minImageExtent.height,
		std::min(surface.capabilities.maxImageExtent.height, extent.height));
	}
}

void SwapChain::setupSwapChainCreateInfo(Surface surface)
{
	std::vector<uint32_t> indexArray(2);

	indexArray[0] = device.graphicQueueFamilyIndex;
	indexArray[1] = device.presentQueueFamilyIndex;
	imageCount = surface.capabilities.minImageCount + 1;
	if (surface.capabilities.maxImageCount > 0 && imageCount > surface.capabilities.maxImageCount)
		imageCount = surface.capabilities.maxImageCount;
	sCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	sCreateInfo.surface = surface.self;
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
}

void SwapChain::create()
{
	if ((codeOfError = vkCreateSwapchainKHR(device.self, &sCreateInfo, nullptr, &self)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << codeOfError << std::endl;
		throw std::runtime_error("Failed to creat SwapChain");
	}
	exit(1);
	vkGetSwapchainImagesKHR(device.self, self, &imageCount, nullptr);
	images.resize(imageCount);
	vkGetSwapchainImagesKHR(device.self, self, &imageCount, images.data());
}