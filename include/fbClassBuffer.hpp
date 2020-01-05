/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassBuffer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:51:03 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/30 16:40:06 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_BUFFER_HPP
# define FB_CLASS_BUFFER_HPP

#include "firebreak.hpp"

class Buffer
{
	public:
		Buffer ();

		VkBuffer				&getSelf();
		VkBufferCreateInfo		&getCreateInfo();
		VkAllocationCallbacks	&getAllocation();
		int32_t					getErrorCode();

		void create	(Device &device);
		void bind	(Device &device, DeviceMemory &deviceMemory, VkDeviceSize offset);
		void destroy(Device &device);

		~Buffer();

	protected:
		VkBuffer				self				= VK_NULL_HANDLE;
		VkBufferCreateInfo		sCreateInfo			= {};
		VkAllocationCallbacks	sAllocation			= {};
		VkDeviceSize			size				= VK_WHOLE_SIZE;
		VkDeviceSize			offset				= 0;

		int32_t	codeOfError = false;
};

#endif