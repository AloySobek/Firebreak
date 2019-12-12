/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassImage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:57:46 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/12 18:07:42 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

VkImage	Image::getSelf()
{
	assert(self);
	return (self);
}

VkImageCreateInfo	*Image::getCreateInfo()
{
	return (&sCreateInfo);
}

VkAllocationCallbacks	*Image::getAllocationInfo()
{
	return (&sAllocation);
}

void	Image::create(Device &device, int mode)
{
	if ((codeOfError = vkCreateImage(device.getSelf(), &sCreateInfo, mode ? &sAllocation : nullptr, &self)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << codeOfError << std::endl;
		throw std::runtime_error("Failed to create image");
	}
}