/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassSurface.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:58:58 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/23 18:04:14 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

// Surface::Surface()
// {
// 	sSwapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
// }

// VkSurfaceKHR	Surface::getSelf()
// {
// 	return (self);
// }

// VkSwapchainKHR	Surface::getSwapchainSelf()
// {
// 	return (swapchain);
// }

// VkSwapchainCreateInfoKHR	*Surface::getSwapchainCreateInfo()
// {
// 	return (&sSwapchainCreateInfo);
// }

// VkImageViewCreateInfo	*Surface::getImageViewCreateInfo()
// {
// 	return (&sImageViewCreateInfo);
// }

// VkSurfaceFormatKHR	*Surface::getFormats(Device2 &device, uint32_t *size)
// {
// 	if (!pFormats)
// 	{
// 		vkGetPhysicalDeviceSurfaceFormatsKHR(device.getPhysicalSelf(), self, &khrFormatsCount, nullptr);
// 		pFormats = new VkSurfaceFormatKHR[khrFormatsCount];
// 		vkGetPhysicalDeviceSurfaceFormatsKHR(device.getPhysicalSelf(), self, &khrFormatsCount, pFormats);
// 	}
// 	size ? *size = khrFormatsCount : false;
// 	return (pFormats);
// }

// VkPresentModeKHR	*Surface::getPresentModes(Device2 &device, uint32_t *size)
// {
// 	if (!pPresentModes)
// 	{
// 		vkGetPhysicalDeviceSurfacePresentModesKHR(device.getPhysicalSelf(), self, &khrPresentModesCount, nullptr);
// 		pPresentModes = new VkPresentModeKHR[khrPresentModesCount];
// 		vkGetPhysicalDeviceSurfacePresentModesKHR(device.getPhysicalSelf(), self, &khrPresentModesCount, pPresentModes);
// 	}
// 	size ? *size = khrPresentModesCount : false;
// 	return (pPresentModes);
// }

// VkSurfaceCapabilitiesKHR	*Surface::getCapabilities(Device2 &device)
// {
// 	if (!capabilities)
// 	{
// 		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device.getPhysicalSelf(), self, &sCapabilities);
// 		capabilities = true;
// 	}
// 	return (&sCapabilities);
// }

// VkSurfaceFormatKHR	*Surface::getFormat()
// {
// 	return (&sFormat);
// }

// VkPresentModeKHR	*Surface::getPresentMode()
// {
// 	return (&sPresentMode);
// }

// VkExtent2D			*Surface::getExtent()
// {
// 	return (&sExtent);
// }

// VkImage	*Surface::getImages(Device2 &device, uint32_t *size)
// {
// 	if (!pImages)
// 	{
// 		vkGetSwapchainImagesKHR(device.getSelf(), swapchain, &imagesCount, nullptr);
// 		pImages		= new VkImage[imagesCount];
// 		pImageViews	= new VkImageView[imagesCount];
// 		vkGetSwapchainImagesKHR(device.getSelf(), swapchain, &imagesCount, pImages);
// 	}
// 	size ? *size = imagesCount : false;
// 	return (pImages);
// }

// VkImageView	*Surface::getImageViews()
// {
// 	return (pImageViews);
// }

// uint32_t	*Surface::getImagesCount()
// {
// 	return (&imagesCount);
// }

// void Surface::provideSurface(VkSurfaceKHR &surface)
// {
// 	self = surface;
// }

// void	Surface::createSwapchain(Device2 &device)
// {
// 	if ((codeOfError = vkCreateSwapchainKHR(device.getSelf(), &sSwapchainCreateInfo, sAllocation.pfnAllocation ? &sAllocation : nullptr, &swapchain)) != VK_SUCCESS)
// 	{
// 		std::cout << "Code of error: " << codeOfError << std::endl;
// 		throw std::runtime_error("Failed to creat SwapChain");
// 	}
// }

// void	Surface::createImageView(Device2 &device)
// {
// 	if ((codeOfError = vkCreateImageView(device.getSelf(), &sImageViewCreateInfo, nullptr, &pImageViews[imageViewsCount++])))
// 	{
// 		std::cout << "Code of error: " << codeOfError << std::endl;
// 		throw std::runtime_error("Failed to create image view object");
// 	}
// }
