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

CommandPool::CommandPool(VkCommandPoolCreateInfo info, VkAllocationCallbacks allocation)
	: self(VK_NULL_HANDLE), sCreateInfo(info), sAllocation(allocation), sCommandBufferAllocateInfo({}), sCommandBufferBeginInfo({})
{
	sCreateInfo.sType						= VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	sCommandBufferAllocateInfo.sType		= VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	sCommandBufferAllocateInfo.commandPool	= self;
}

VkCommandPool	&CommandPool::getSelf()
{
	assert(self);
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

std::vector<VkCommandBuffer> &CommandPool::getCommandBufferGroup(uint32_t group)
{
	assert(group < ppCommandBuffers.size());
	return (ppCommandBuffers[group]);
}

VkCommandBuffer		&CommandPool::getCommandBuffer(uint32_t group, uint32_t index)
{
	assert(group < ppCommandBuffers.size() && index < ppCommandBuffers[ppCommandBuffers.size() - 1].size());
	return (ppCommandBuffers[group][index]);
}

// int32_t		CommandPool::getErrorCode()
// {
// 	vkCmdCopyImage()
// 	return (codeOfError);
// }

// void CommandPool::create(Device &device)
// {
// 	codeOfError = vkCreateCommandPool(device.getSelf(), &sCreateInfo, sAllocation.pfnAllocation ? &sAllocation : nullptr, &self);
// 	THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to create command pool");
// }

// void CommandPool::allocateCommandBuffers(Device &device)
// {
// 	assert(sCommandBufferAllocateInfo.commandBufferCount > 0);
// 	std::vector<VkCommandBuffer> bufferGroup;
// 	bufferGroup.resize(sCommandBufferAllocateInfo.commandBufferCount);
// 	codeOfError = vkAllocateCommandBuffers(device.getSelf(), &sCommandBufferAllocateInfo, bufferGroup.data());
// 	THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to allocate command buffers from command pool");
// 	ppCommandBuffers.push_back(bufferGroup);
// }

// void CommandPool::freeCommandBuffers(Device &device)
// {
// 	vkFreeCommandBuffers(device.getSelf(), self, ppCommandBuffers[ppCommandBuffers.size() - 1].size(), ppCommandBuffers[ppCommandBuffers.size() - 1].data());
// 	ppCommandBuffers[ppCommandBuffers.size() - 1].~vector();
// 	ppCommandBuffers.pop_back();
// }

void CommandPool::beginCommandBuffer(uint32_t index, uint32_t group)
{
	assert(group < ppCommandBuffers.size() && index < ppCommandBuffers[ppCommandBuffers.size() - 1].size());
	codeOfError = vkBeginCommandBuffer(ppCommandBuffers[group][index], &sCommandBufferBeginInfo);
	THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to begin command buffer");
}

void CommandPool::beginCommandBufferGroup(uint32_t group)
{
	assert(group < ppCommandBuffers.size());
	for (VkCommandBuffer &iter : ppCommandBuffers[group])
	{
		codeOfError = vkBeginCommandBuffer(iter, &sCommandBufferBeginInfo);
		THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to begin command buffer");
	}
}

void CommandPool::endCommandBuffer(uint32_t index, uint32_t group)
{
	assert(group < ppCommandBuffers.size() && index < ppCommandBuffers[ppCommandBuffers.size() - 1].size());
	codeOfError = vkEndCommandBuffer(ppCommandBuffers[group][index]);
	THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to end command buffer");
}

void CommandPool::endCommandBufferGroup(uint32_t group)
{
	assert(group < ppCommandBuffers.size());
	for (VkCommandBuffer &iter : ppCommandBuffers[group])
	{
		codeOfError = vkEndCommandBuffer(iter);
		THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to end command buffer");
	}
}

void CommandPool::resetCommandBuffer(VkCommandBufferResetFlags flags, uint32_t index, uint32_t group)
{
	assert(group < ppCommandBuffers.size() && index < ppCommandBuffers[ppCommandBuffers.size() - 1].size());
	codeOfError = vkResetCommandBuffer(ppCommandBuffers[group][index], flags);
	THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to reset command buffer");
}

void CommandPool::resetCommandBufferGroup(VkCommandBufferResetFlags flags, uint32_t group)
{
	assert(group < ppCommandBuffers.size());
	for (VkCommandBuffer &iter : ppCommandBuffers[group])
	{
		codeOfError = vkResetCommandBuffer(iter, flags);
		THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to reset command buffer");
	}
}

void CommandPool::cmdCopy(Buffer &srcBuffer, Buffer &dstBuffer, uint32_t regionCount, VkBufferCopy *pRegions, uint32_t index, uint32_t group)
{
	assert(group < ppCommandBuffers.size() && index < ppCommandBuffers[ppCommandBuffers.size() - 1].size());
	vkCmdCopyBuffer(ppCommandBuffers[group][index], srcBuffer.getSelf(), dstBuffer.getSelf(), regionCount, pRegions);
}

// void CommandPool::reset(Device &device, VkCommandPoolResetFlags flags)
// {
// 	codeOfError = vkResetCommandPool(device.getSelf(), self, flags);
// 	THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to reset command pool");
// }

// void CommandPool::destroy(Device &device)
// {
// 	vkDestroyCommandPool(device.getSelf(), self, sAllocation.pfnFree ? &sAllocation : nullptr);
// 	self = VK_NULL_HANDLE;
// }