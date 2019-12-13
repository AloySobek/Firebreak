/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassBuffer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:51:03 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/12 17:55:37 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_BUFFER_HPP
# define FB_CLASS_BUFFER_HPP

#include "firebreak.hpp"

class Buffer
{
	public:
		VkBuffer	self;

		Buffer();
		Buffer(Buffer &anotherBuffer);

		VkBufferCreateInfo		*getCreateInfo();
		VkAllocationCallbacks	*getAllocationInfo();

		void create(Device &device, int mode = VK_NULL_HANDLE);

		~Buffer() { }

	private:
		VkBufferCreateInfo		sCreateInfo = {};
		VkAllocationCallbacks	sAllocation = {};

		int32_t	codeOfError = false;
};

#endif