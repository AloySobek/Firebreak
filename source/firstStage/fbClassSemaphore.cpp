/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassSemaphore.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 17:24:04 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/15 17:38:39 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

Semaphore::Semaphore()
{
	sCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
}

VkSemaphore Semaphore::getSelf()
{
	assert(self);
	return (self);
}

VkSemaphoreCreateInfo	*Semaphore::getCreateInfo()
{
	return (&sCreateInfo);
}

VkAllocationCallbacks	*Semaphore::getAllocation()
{
	return (&sAllocation);
}

void Semaphore::create(Device &device, int mode)
{
	if ((codeOfError = vkCreateSemaphore(device.getSelf(), &sCreateInfo, mode ? &sAllocation : nullptr, &self)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << codeOfError << std::endl;
		throw	std::runtime_error("Failed to create semaphore");
	}
}