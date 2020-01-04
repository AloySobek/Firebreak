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

void Queue::retrieve(Device &device)
{
	assert(device.getSelf());
	for (int i = 0; i < sCreateInfo.queueCount; ++i)
		vkGetDeviceQueue(device.getSelf(), sCreateInfo.queueFamilyIndex, i, &selfs[i]);
}