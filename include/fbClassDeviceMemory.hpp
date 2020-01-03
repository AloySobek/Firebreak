/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassDeviceMemory.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 22:25:12 by Rustam            #+#    #+#             */
/*   Updated: 2020/01/01 22:25:12 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_DEVICE_MEMORY_HPP
# define FB_CLASS_DEVICE_MEMORY_HPP

# include "firebreak.hpp"

class DeviceMemory
{
	public:
		DeviceMemory();
		DeviceMemory(std::initializer_list<int> initList);
		DeviceMemory(DeviceMemory &anotherDeviceMemory);

		VkDeviceMemory			&getSelf();
		VkMemoryAllocateInfo	&getAllocateInfo();
		VkAllocationCallbacks	&getAllocation();
		VkDeviceSize			&getSize();

		void allocate(Device &device);
		void map(Device &device, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void **pData);
		void unmap(Device &device);
		void free(Device &device);

	private:
		VkDeviceMemory			self			= VK_NULL_HANDLE;
		VkMemoryAllocateInfo	sAllocateInfo	= {};
		VkAllocationCallbacks	sAllocation		= {};
		VkDeviceSize			sSize			= {};

		int32_t	codeOfError	= false;
};

#endif
