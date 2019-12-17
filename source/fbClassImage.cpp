/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassImage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:57:46 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/17 14:23:19 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

VkImage	Image::getSelf()
{
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

void	Image::create(Device &device)
{
	if ((codeOfError = vkCreateImage(device.getSelf(), &sCreateInfo, sAllocation.pfnAllocation ? &sAllocation : nullptr, &self)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << codeOfError << std::endl;
		throw std::runtime_error("Failed to create image");
	}
}