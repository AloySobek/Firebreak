/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassBuffer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:50:56 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/09 20:59:30 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

VkBufferCreateInfo	*Buffer::getCreateInfo()
{
	return (&sCreateInfo);
}

VkAllocationCallbacks	*Buffer::getAllocationInfo()
{
	return (&sAllocation);
}

void Buffer::create(Device &device, int mode)
{
	if ((codeOfError = vkCreateBuffer(device.getSelf(), &sCreateInfo, mode ? &sAllocation : nullptr, &self)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << codeOfError << "\n";
		throw std::runtime_error("Failed to create buffer object");
	}
}