/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassCommandBuffer.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:46:09 by Rustam            #+#    #+#             */
/*   Updated: 2020/01/03 18:26:34 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_COMMAND_BUFFER_HPP
# define FB_CLASS_COMMAND_BUFFER_HPP

#include "firebreak.hpp"

class CommandBuffer
{
	public:
		CommandBuffer();
		explicit CommandBuffer(std::initializer_list<int> initList);
		CommandBuffer(CommandBuffer &anotherCommandBuffer);

		virtual	VkCommandBuffer				&getSelf			();
		virtual	VkCommandBufferAllocateInfo	&getAllocationInfo	();
		virtual VkCommandBufferBeginInfo	&getBeginInfo		();
		virtual int32_t						getCodeOfError		();

		void begin();

		~CommandBuffer();

	private:
		VkCommandBuffer				self;
		VkCommandBufferBeginInfo	sBeginInfo;

		int32_t codeOfError;
};

#endif