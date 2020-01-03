/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassImage.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:57:53 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/30 15:20:07 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_IMAGE_HPP
# define FB_CLASS_IMAGE_HPP

# include "firebreak.hpp"

class Image
{
	public:
		Image();
		explicit Image(std::initializer_list<int> list);
		Image(Image &anotherImage);

		VkImage							&getSelf();
		VkImageCreateInfo				&getCreateInfo();
		VkAllocationCallbacks			&getAllocation();
		int32_t							getCodeOfError();

		void create	(Device &device);
		void bind	(Device &device, DeviceMemory &deviceMemory, VkDeviceSize offset);
		void destroy(Device &device);

		~Image() { }

	protected:
		VkImage					self					= VK_NULL_HANDLE;
		VkImageCreateInfo		sCreateInfo				= {};
		VkAllocationCallbacks	sAllocation				= {};

		int32_t codeOfError = false;
};

#endif