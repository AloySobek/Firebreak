/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassBuffer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:51:03 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/24 16:09:42 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_BUFFER_HPP
# define FB_CLASS_BUFFER_HPP

#ifdef SAFEMODE
# define THROW_EXCEPTION(x)	if (codeOfError != VK_SUCCESS) throw std::runtime_error(x);
#else
# define THROW_EXCEPTION(x)
#endif

#include "firebreak.hpp"

class Buffer
{
	public:
		Buffer();
		explicit Buffer(std::initializer_list<int> initList);
		Buffer(Buffer &anotherBuffer);

		VkBuffer				getSelf();
		VkBufferCreateInfo		*getCreateInfo();
		VkAllocationCallbacks	*getAllocationInfo();
		VkMemoryRequirements	*getMemoryRequirements();
		VkMemoryAllocateInfo	*getMemoryAllocateInfo();
		VkDeviceMemory			*getDeviceMemory();
		VkMappedMemoryRange		*getMappedMemoryRange();
		void					*getMemoryPtr();
		int32_t					getErrorCode();
		VkDeviceSize			getSizeDeviceMemory(Device &device);

		void create(Device &device);
		void createView(Device &device);
		void allocate(Device &device);
		void bind(Device &device);
		void mapMemory(Device &device, uint32_t offset = 0, uint32_t size = 0);
		void unmapMemory(Device &device);
		void discardDeviceCache(Device &device, uint32_t memoryRangeCount);
		void refreshDeviceCache(Device &device, uint32_t memoryRangeCount);

		~Buffer() { }

	protected:
		VkBuffer				self				= VK_NULL_HANDLE;
		VkBufferCreateInfo		sCreateInfo			= {};
		VkBufferViewCreateInfo	sViewCreateInfo		= {};
		VkAllocationCallbacks	sAllocation			= {};
		VkMemoryRequirements	sMemoryRequirements = {};
		VkMemoryAllocateInfo	sMemoryAllocateInfo	= {};
		VkDeviceMemory			deviceMemory		= nullptr;
		VkDeviceSize			sizeDeviceMemory	= -1;
		VkMappedMemoryRange		sMappedMemoryRange	= {};

		VkBufferView			*pViews				= nullptr;
		void					*pData				= nullptr;

		int32_t	codeOfError = false;
};

#endif