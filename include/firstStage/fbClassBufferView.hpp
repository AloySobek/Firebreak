/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassBufferView.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 16:24:25 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/30 16:40:01 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_BUFFER_VIEW_HPP
# define FB_CLASS_BUFFER_VIEW_HPP

#include "firebreak.hpp"

class BufferView
{
	public:
		BufferView			();
		explicit BufferView	(std::initializer_list<int> initList);
		BufferView			(BufferView &anotherView);

		VkBufferView			&getSelf();
		VkBufferViewCreateInfo	&getCreateInfo();
		VkAllocationCallbacks	&getAllocation();

		void create	(Device &device);
		void destroy(Device &device);

	private:
		VkBufferView			self		= VK_NULL_HANDLE;
		VkBufferViewCreateInfo	sCreateInfo	= {};
		VkAllocationCallbacks	sAllocation	= {};
};

#endif