/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassQueue.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 17:01:28 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/19 17:01:40 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

Queue::Queue() : sCreateInfo({}), codeOfError(false)
{
	sCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
}

VkQueue		&Queue::getSelf(uint32_t index)
{
	assert(index < pSelfs.size());
	return (pSelfs[index]);
}

VkDeviceQueueCreateInfo	&Queue::getCreateInfo()
{
	return (sCreateInfo);
}

int32_t			Queue::getCodeOfError()
{
	VkSubmitInfo	test;

	return (codeOfError);
}

void Queue::retrieve(Device &device)
{
	assert(device.getSelf());
	for (int i = 0; i < sCreateInfo.queueCount; ++i)
		vkGetDeviceQueue(device.getSelf(), sCreateInfo.queueFamilyIndex, i, &pSelfs[i]);
}

void Queue::submitTasks(Device &device, uint32_t index, Fence *pFence)
{
	codeOfError = vkQueueSubmit(pSelfs[index], pSubmitInfo.size(), pSubmitInfo.data(), pFence ? pFence->getSelf() : VK_NULL_HANDLE);
	THROW_EXCEPTION_IN_CASE_OF_ERROR("Failed to submit tasks");
}

void hello(Fence &pFence)
{
	pFence.getSelf();
}

int main(void)
{
	
}
