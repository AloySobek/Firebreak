/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassSurface.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:27:43 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/01 19:28:51 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vkClassContainer.hpp"

void Vulkan::vkCreateSurface(GLFWwindow *pWindow)
{
	if ((error = glfwCreateWindowSurface(instance(), pWindow, nullptr, &surfaceObj)))
	{
		std::cout << "Code of error: " << error << std::endl;
		throw std::runtime_error("Failed to create window surface");
	}
}

void Vulkan::vkSetupSwapChain()
{
	VkSurfaceFormatKHR	surfaceIter = {};
	VkPresentModeKHR	presentIter = {};
	VkBool32			found = false;

	for (int i = 0; i < khrFormatsCount; ++i)
	{
		surfaceIter = pKHRFormats[i];
		if (surfaceIter.format == VK_FORMAT_B8G8R8A8_UNORM and surfaceIter.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			sBestSwapChainFormat = surfaceIter;
			found = true;
			break;
		}
	}
	if (!found)
	{
		std::cout << "Best swap chain format has not been found" << std::endl;
		sBestSwapChainFormat = pKHRFormats[0];
	}
	found = false;
	for (int i = 0; i < khrPresentModesCount; ++i)
	{
		presentIter = pKHRPresentModes[i];
		if (presentIter == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			sBestSwapChainPresentMode = presentIter;
			found = true;
			break;
		}
		else if (presentIter == VK_PRESENT_MODE_FIFO_KHR)
		{
			sBestSwapChainPresentMode = presentIter;
			found = true;
		}
	}
	if (!found)
	{
		std::cout << "Best swap chain present mode has not been found" << std::endl;
		sBestSwapChainPresentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
	}
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
	{
		std::cout << "Standart setting\n";
		sBestSwapChainResolution = capabilities.currentExtent;
	}
	else
	{
		std::cout << "Custom setting\n";
		sBestSwapChainResolution.width = std::max(capabilities.minImageExtent.width,
		std::min(capabilities.maxImageExtent.width, sBestSwapChainResolution.width));
		sBestSwapChainResolution.height = std::max(capabilities.minImageExtent.height,
		std::min(capabilities.maxImageExtent.height, sBestSwapChainResolution.height));
	}
}

void Vulkan::vkSetupSwapChainCreateInfo()
{
	uint32_t	indexArray[2];

	indexArray[0] = graphicQueueFamilyIndex;
	indexArray[1] = presentQueueFamilyIndex;
	imageCount = capabilities.minImageCount + 1;
	if (capabilities.maxImageCount > 0 and imageCount > capabilities.maxImageCount)
	{
		std::cout << "Standart image count has been setup\n";
		imageCount = capabilities.maxImageCount;
	}
	sSwapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	sSwapChainCreateInfo.surface = surfaceObj;
	sSwapChainCreateInfo.flags = 0;
	sSwapChainCreateInfo.pNext = nullptr;
	sSwapChainCreateInfo.clipped = VK_TRUE;
	sSwapChainCreateInfo.minImageCount = imageCount;
	sSwapChainCreateInfo.imageFormat = sBestSwapChainFormat.format;
	sSwapChainCreateInfo.imageColorSpace = sBestSwapChainFormat.colorSpace;
	sSwapChainCreateInfo.imageExtent = sBestSwapChainResolution;
	sSwapChainCreateInfo.imageArrayLayers = 1;
	sSwapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	sSwapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
	sSwapChainCreateInfo.queueFamilyIndexCount = 2;
	sSwapChainCreateInfo.pQueueFamilyIndices = indexArray;
	sSwapChainCreateInfo.oldSwapchain = VK_NULL_HANDLE;
	sSwapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	sSwapChainCreateInfo.presentMode = sBestSwapChainPresentMode;
	sSwapChainCreateInfo.preTransform = capabilities.currentTransform;
}

void Vulkan::vkCreateSwapChain()
{
	if ((error = vkCreateSwapchainKHR(deviceObj, &sSwapChainCreateInfo, nullptr, &swapchainObj)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << error << std::endl;
		throw std::runtime_error("Failed to creat SwapChain");
	}
	vkGetSwapchainImagesKHR(deviceObj, swapchainObj, &imageCount, nullptr);
	pImageObjList = (VkImage *)malloc(sizeof(VkImage) * imageCount);
	vkGetSwapchainImagesKHR(deviceObj, swapchainObj, &imageCount, pImageObjList);
}