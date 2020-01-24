/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassSwapchain.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 19:28:48 by Rustam            #+#    #+#             */
/*   Updated: 2020/01/24 18:16:02 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

// FbSwapchain::FbSwapchain(VkSwapchainCreateInfoKHR info, VkAllocationCallbacks allocation)
// 	: self(VK_NULL_HANDLE), sCreateInfo{info}, sAllocation{allocation}, codeOfError{false}
// {
// 	sCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
// }

// void FbSwapchain::create(FbDevice &device)
// {
// 	codeOfError = vkCreateSwapchainKHR(device.getSelf(), &sCreateInfo, sAllocation.pfnAllocation ? &sAllocation : nullptr, &self);
// 	THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to create swapchain object");
// }

// void FbSwapchain::destroy(FbDevice &device)
// {
// 	vkDestroySwapchainKHR(device.getSelf(), self, sAllocation.pfnFree ? &sAllocation : nullptr);
// 	self = VK_NULL_HANDLE;
// }