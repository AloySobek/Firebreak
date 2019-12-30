/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassRender.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 17:10:49 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/14 19:42:11 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_RENDER_HPP
# define FB_CLASS_RENDER_HPP

class RenderPass
{
	public:
		VkRenderPass	self = VK_NULL_HANDLE;

		RenderPass();

		VkRenderPass			getSelf();
		VkRenderPassCreateInfo	*getCreateInfo();
		VkAllocationCallbacks	*getAllocation();
		VkAttachmentDescription *getColorAttachmentDescription();
		VkAttachmentReference	*getColorAttachmentReference();
		VkSubpassDescription	*getSubpassDescription();
		VkSubpassDependency		*getSubpassDependency();

		void create(Device &device, int mode = VK_NULL_HANDLE);

	private:
		VkRenderPassCreateInfo	sCreateInfo					= {};
		VkAllocationCallbacks	sAllocation					= {};
		VkAttachmentDescription	sColorAttachment			= {};
		VkAttachmentReference	sColorAttachmentReference	= {};
		VkSubpassDescription	sSubpassDescription			= {};
		VkSubpassDependency		sSubpassDependency			= {};

		int32_t		codeOfError = false;
};

#endif