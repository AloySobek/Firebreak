/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassImage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:57:46 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/23 18:37:53 by Rustam           ###   ########.fr       */
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

VkImageViewCreateInfo	*Image::getImageViewCreateInfo()
{
	return (&sImageViewCreateInfo);
}

VkImageSubresource	*Image::getImageSubresource(Device &device)
{
	if (!subresourceChecked)
	{
		vkGetImageSubresourceLayout(device.getSelf(), self, &sImageSubresource, &sImageSubresourceLayout);
		subresourceChecked = true;
	}
	return (&sImageSubresource);
}

VkSubresourceLayout	*Image::getImageSubresourceLayout(Device &device)
{
	if (subresourceChecked)
	{
		vkGetImageSubresourceLayout(device.getSelf(), self, &sImageSubresource, &sImageSubresourceLayout);
		subresourceChecked = true;
	}
	return (&sImageSubresourceLayout);
}

void	Image::create(Device &device)
{
	codeOfError = vkCreateImage(device.getSelf(), &sCreateInfo, sAllocation.pfnAllocation ? &sAllocation : nullptr, &self);
	THROW_EXCEPTION("Failed to create iamge");
}

void	Image::createView(Device &device)
{
	codeOfError = vkCreateImageView(device.getSelf(), &sImageViewCreateInfo, sAllocation.pfnAllocation ? & sAllocation : nullptr, &pViews[viewCount++]);
	THROW_EXCEPTION("Failed to create image view");
}