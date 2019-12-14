/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassBuffer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:50:56 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/14 20:59:01 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

Buffer::Buffer()
{
	sCreateInfo.sType		= VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	sMemoryAllocation.sType	= VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
}

VkBuffer	Buffer::getSelf()
{
	assert(self);
	return (self);
}

VkBufferCreateInfo	*Buffer::getCreateInfo()
{
	return (&sCreateInfo);
}

VkAllocationCallbacks	*Buffer::getAllocationInfo()
{
	return (&sAllocation);
}

VkMemoryRequirements	*Buffer::getMemoryRequirements()
{
	return (&sMemoryRequirements);
}

VkMemoryAllocateInfo	*Buffer::getMemoryAllocaionInfo()
{
	return (&sMemoryAllocation);
}

void Buffer::create(Device &device, int mode)
{
	if ((codeOfError = vkCreateBuffer(device.getSelf(), &sCreateInfo, mode ? &sAllocation : nullptr, &self)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << codeOfError << "\n";
		throw std::runtime_error("Failed to create buffer object");
	}
	vkGetBufferMemoryRequirements(device.getSelf(), self, &sMemoryRequirements);
}

void Buffer::allocate(Device &device, int mode)
{
	if ((codeOfError = vkAllocateMemory(device.getSelf(), &sMemoryAllocation, mode ? &sAllocation : nullptr, &deviceMemory)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << codeOfError << std::endl;
		throw std::runtime_error("Failed to allocate memory");
	}
}