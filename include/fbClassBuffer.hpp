/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassBuffer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:51:03 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/14 20:57:00 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_BUFFER_HPP
# define FB_CLASS_BUFFER_HPP

#include "firebreak.hpp"

class Buffer
{
	public:
		Buffer();
		Buffer(Buffer &anotherBuffer);

		VkBuffer				getSelf();
		VkBufferCreateInfo		*getCreateInfo();
		VkAllocationCallbacks	*getAllocationInfo();
		VkMemoryRequirements	*getMemoryRequirements();
		VkMemoryAllocateInfo	*getMemoryAllocaionInfo();

		void create(Device &device, int mode = VK_NULL_HANDLE);
		void allocate(Device &device, int mode = VK_NULL_HANDLE);

		~Buffer() { }

	private:
		VkBuffer				self				= VK_NULL_HANDLE;
		VkBufferCreateInfo		sCreateInfo			= {};
		VkAllocationCallbacks	sAllocation			= {};
		VkMemoryRequirements	sMemoryRequirements = {};
		VkMemoryAllocateInfo	sMemoryAllocation	= {};

		VkDeviceMemory			deviceMemory		= nullptr;

		int32_t	codeOfError = false;
};

#endif