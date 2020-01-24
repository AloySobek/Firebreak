/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassBuffer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:50:56 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/30 16:33:32 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

Buffer::Buffer()
{
	sCreateInfo.sType			= VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
}

VkBuffer				&Buffer::getSelf()
{
	return (self);
}

VkBufferCreateInfo		&Buffer::getCreateInfo()
{
	return (sCreateInfo);
}

VkAllocationCallbacks	&Buffer::getAllocation()
{
	return (sAllocation);
}

// VkMemoryRequirements	&Buffer::getMemoryRequirements()
// {
// 	return (sMemoryRequirements);
// }

// VkMemoryAllocateInfo	*Buffer::getMemoryAllocateInfo()
// {
// 	return (&sMemoryAllocateInfo);
// }

// VkDeviceMemory	*Buffer::getDeviceMemory()
// {
// 	return (&deviceMemory);
// }

// VkMappedMemoryRange	*Buffer::getMappedMemoryRange()
// {
// 	return (&sMappedMemoryRange);
// }

// void	*Buffer::getMemoryPtr()
// {
// 	return (pData);
// }

// int32_t		Buffer::getErrorCode()
// {
// 	return (codeOfError);
// }

// VkDeviceSize	Buffer::getSizeDeviceMemory(Device &device)
// {
// 	if (sizeDeviceMemory == -1)
// 		vkGetDeviceMemoryCommitment(device.getSelf(), deviceMemory, &sizeDeviceMemory);
// 	return (sizeDeviceMemory);
// }

// void Buffer::create(Device &device)
// {
// 	codeOfError = vkCreateBuffer(device.getSelf(), &sCreateInfo, sAllocation.pfnAllocation ? &sAllocation : nullptr, &self);
// 	THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to create buffer object");
// 	vkGetBufferMemoryRequirements(device.getSelf(), self, &sMemoryRequirements);
// }

// void Buffer::allocate(Device &device)
// {
// 	codeOfError = vkAllocateMemory(device.getSelf(), &sMemoryAllocateInfo, sAllocation.pfnAllocation ? &sAllocation : nullptr, &deviceMemory);
// 	THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to allocate memory");
// }

// void Buffer::bind(Device &device)
// {
// 	codeOfError = vkBindBufferMemory(device.getSelf(), self, deviceMemory, 0);
// 	THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to bind memory");
// }

// void Buffer::mapMemory(Device &device, uint32_t offset, uint32_t size)
// {
// 	if (!pData)
// 	{
// 		codeOfError = vkMapMemory(device.getSelf(), deviceMemory, 0, size ? size : sCreateInfo.size, 0, &this->pData);
// 		THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to map memory");
// 	}
// }

// void Buffer::unmapMemory(Device &device)
// {
// 	vkUnmapMemory(device.getSelf(), deviceMemory);
// 	pData = nullptr;
// }

// void Buffer::discardDeviceCache(Device &device, uint32_t memoryRangeCount)
// {
// 	codeOfError = vkFlushMappedMemoryRanges(device.getSelf(), memoryRangeCount, &sMappedMemoryRange);
// 	THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to discard device cache");
// }

// void Buffer::refreshDeviceCache(Device &device, uint32_t memoryRangeCount)
// {
// 	codeOfError = vkInvalidateMappedMemoryRanges(device.getSelf(), memoryRangeCount, &sMappedMemoryRange);
// 	THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to refresh device cache");
// }