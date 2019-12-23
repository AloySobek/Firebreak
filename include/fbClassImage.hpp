/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassImage.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:57:53 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/23 18:42:58 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_IMAGE_HPP
# define FB_CLASS_IMAGE_HPP

# include "firebreak.hpp"

class Image
{
	public:

		Image() { }
		Image(Image &anotherImage) { }

		VkImage					getSelf();
		VkImageCreateInfo		*getCreateInfo();
		VkAllocationCallbacks	*getAllocationInfo();
		VkImageViewCreateInfo	*getImageViewCreateInfo();
		VkImageSubresource		*getImageSubresource(Device &device);
		VkSubresourceLayout		*getImageSubresourceLayout(Device &device);
		VkMemoryRequirements	*getMemoryRequirements(Device &device);

		void create			(Device &device);
		void createView		(Device &device);
		void destroy		(Device &device);
		void destroyView	(Device &device, uint32_t index);
		void destroyViews	(Device &device);

		~Image() { }

	protected:
		VkImage					self					= VK_NULL_HANDLE;
		VkImageCreateInfo		sCreateInfo				= {};
		VkImageSubresource		sImageSubresource		= {};
		VkSubresourceLayout		sImageSubresourceLayout	= {};
		VkImageViewCreateInfo	sImageViewCreateInfo	= {};
		VkMemoryRequirements	sMemoryRequirements		= {};
		VkAllocationCallbacks	sAllocation				= {};

		VkImageView	*pViews = nullptr;

		uint32_t viewCount = 0;

		int32_t codeOfError = false;

		bool	subresourceChecked = false;
};

#endif