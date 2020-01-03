/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassCommandPool.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 21:48:55 by Rustam            #+#    #+#             */
/*   Updated: 2020/01/01 21:48:55 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

CommandPool::CommandPool() : self(VK_NULL_HANDLE), sCreateInfo({}), sAllocation({})
{
	sCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
}

VkCommandPool	&CommandPool::getSelf()
{
	return (self);
}

VkCommandPoolCreateInfo	&CommandPool::getCreateInfo()
{
	return (sCreateInfo);
}

VkAllocationCallbacks	&CommandPool::getAllocation()
{
	return (sAllocation);
}

int32_t		CommandPool::getErrorCode()
{
	return (codeOfError);
}

void CommandPool::create(Device &device)
{
	codeOfError = vkCreateCommandPool(device.getSelf(), &sCreateInfo, sAllocation.pfnAllocation ? &sAllocation : nullptr, &self);
	THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to create command pool");
}

void CommandPool::allocateCommandBuffers(Device &device)
{
	pCommandBuffers.resize(sCommandBufferAllocateInfo.commandBufferCount);
	codeOfError = vkAllocateCommandBuffers(device.getSelf(), &sCommandBufferAllocateInfo, pCommandBuffers.data());
}

void CommandPool::destroy(Device &device)
{
	vkDestroyCommandPool(device.getSelf(), self, sAllocation.pfnFree ? &sAllocation : nullptr);
	self = VK_NULL_HANDLE;
}