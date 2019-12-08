/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassRender.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 17:11:52 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/08 13:22:33 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

// VkAttachmentDescription *RenderPass::getColorAttachmentSettings()
// {
// 	return (&sColorAttachment);
// }

void RenderPass::create(Device &device)
{
	sCreateInfo.sType			= VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	sCreateInfo.attachmentCount	= 1;
	sCreateInfo.pAttachments	= &sColorAttachment;
	sCreateInfo.subpassCount	= 1;
	sCreateInfo.pSubpasses		= &sSubpassingRenders;
	sCreateInfo.pNext			= nullptr;
	sCreateInfo.flags			= 0;

	if ((codeOfError = vkCreateRenderPass(device.getSelf(), &sCreateInfo, nullptr, &self)) != VK_SUCCESS)
	{
		std::cout << "Code of error " << codeOfError << std::endl;
		throw std::runtime_error("Failed to create render pass");
	}
}