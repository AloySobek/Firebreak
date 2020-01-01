/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassImageView.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 16:33:46 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/30 16:39:54 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_IMAGE_VIEW_HPP
# define FB_CLASS_IMAGE_VIEW_HPP

#include "firebreak.hpp"

class ImageView
{
	public:
		ImageView			();
		explicit ImageView	(std::initializer_list<int> initList);
		ImageView			(ImageView &anotherImageView);

		VkImageView				&getSelf();
		VkImageViewCreateInfo	&getCreateInfo();
		VkAllocationCallbacks	&getAllocation();

		void create();
		void destroy();

	private:
		VkImageView				self		= VK_NULL_HANDLE;
		VkImageViewCreateInfo	sCreateInfo = {};
		VkAllocationCallbacks	sAllocation	= {};
};

#endif