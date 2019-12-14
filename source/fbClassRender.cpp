/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassRender.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 17:11:52 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/14 20:57:35 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

RenderPass::RenderPass()
{
	sCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
}

VkRenderPass			RenderPass::getSelf()
{
	assert(self);
	return (self);
}

VkRenderPassCreateInfo	*RenderPass::getCreateInfo()
{
	return (&sCreateInfo);
}

VkAttachmentDescription *RenderPass::getColorAttachmentDescription()
{
	return (&sColorAttachment);
}

VkAttachmentReference	*RenderPass::getColorAttachmentReference()
{
	return (&sColorAttachmentReference);
}

VkSubpassDescription	*RenderPass::getSubpassDescription()
{
	return (&sSubpassDescription);
}

VkSubpassDependency		*RenderPass::getSubpassDependency()
{
	return (&sSubpassDependency);
}

void RenderPass::create(Device &device, int mode)
{
	if ((codeOfError = vkCreateRenderPass(device.getSelf(), &sCreateInfo, mode ? &sAllocation : nullptr, &self)) != VK_SUCCESS)
	{
		std::cout << "Code of error " << codeOfError << std::endl;
		throw std::runtime_error("Failed to create render pass");
	}
}