/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassQueue.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 17:01:23 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/20 17:13:05 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_QUEUE_HPP
# define FB_CLASS_QUEUE_HPP

# include "firebreak.hpp"

class Queue
{
	public:
		Queue();
		Queue(Queue &anotherQueue);

		VkQueue						getSelf							();
		VkCommandPool				getCommandPool					();
		VkDeviceQueueCreateInfo		*getCreateInfo					();
		VkCommandPoolCreateInfo		*getCommandPoolCreateInfo		();
		VkAllocationCallbacks		*getAllocation					();
		VkCommandBufferAllocateInfo	*getCommandBufferAllocateInfo	();
		VkCommandBufferBeginInfo	*getCommandBufferBeginInfo		();
		VkBufferCopy				*getBufferCopy					();
		VkSubmitInfo				*getSubmitInfo					();
		VkCommandBuffer				getCommandBuffer				(uint32_t index);

		void retrive				(Device &device);
		void createCommandPool		(Device &device);
		void allocateCommandBuffers	(Device &device);
		void freeCommandBuffers		(Device &device);
		void destroyCommandPool		(Device &device);
		void beginCommandBuffer		(uint32_t bufferIndex);
		void cmdCopyBuffer			(uint32_t bufferIndex, VkBuffer src, VkBuffer dst, uint32_t regionCount);
		void endCommandBuffer		(uint32_t bufferIndex);
		void resetCommandBuffer		(uint32_t bufferIndex, VkCommandBufferResetFlags flags);
		void resetCommandPool		(Device &device, VkCommandPoolResetFlags flags);
		void submitTasks			();

	private:
		VkQueue						self						= VK_NULL_HANDLE;
		VkCommandPool				commandPool					= VK_NULL_HANDLE;
		VkDeviceQueueCreateInfo		sCreateInfo					= {};
		VkCommandPoolCreateInfo		sCommandPoolCreateInfo		= {};
		VkAllocationCallbacks		sAllocation					= {};
		VkCommandBufferAllocateInfo	sCommandBuffersAllocateInfo	= {};
		VkCommandBufferBeginInfo	sCommandBufferBeginInfo		= {};
		VkBufferCopy				sBufferCopy					= {};
		VkSubmitInfo				sSubmitInfo					= {};
};

#endif