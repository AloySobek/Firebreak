/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassRender.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 17:10:49 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/08 13:22:10 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_RENDER_HPP
# define FB_CLASS_RENDER_HPP

class RenderPass
{
	public:
		VkRenderPass	self = VK_NULL_HANDLE;

		VkAttachmentDescription *getColorAttachmentSettings();
		VkAttachmentReference	*getColorAttachmentReferenceSettings();

		void create(Device &device);

	private:
		VkRenderPassCreateInfo	sCreateInfo					= {};
		VkAttachmentDescription	sColorAttachment			= {};
		VkAttachmentReference	sColorAttachmentReference	= {};
		VkSubpassDescription	sSubpassingRenders			= {};
		VkSubpassDependency		sDependency					= {};

		int32_t		codeOfError = false;
};

#endif