/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassImage.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:57:53 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/17 14:22:56 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_IMAGE_HPP
# define FB_CLASS_IMAGE_HPP

# include "firebreak.hpp"

class Image
{
	public:
		VkImage		self = VK_NULL_HANDLE;

		Image() { }
		Image(Image &anotherImage) { }

		VkImage					getSelf();
		VkImageCreateInfo		*getCreateInfo();
		VkAllocationCallbacks	*getAllocationInfo();

		void create(Device &device);

		~Image() { }

	private:
		VkImageCreateInfo		sCreateInfo	= {};
		VkAllocationCallbacks	sAllocation	= {};

		int32_t		codeOfError;
};

#endif