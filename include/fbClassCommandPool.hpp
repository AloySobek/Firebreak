/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassCommandPool.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 16:33:41 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/29 16:37:29 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_COMMAND_POOL_HPP
# define FB_CLASS_COMMAND_POOL_HPP

# include "firebreak.hpp"

class CommandPool
{
	public:
		CommandPool			();

		VkCommandPool					&getSelf();
		VkCommandPoolCreateInfo			&getCreateInfo();
		VkAllocationCallbacks			&getAllocation();
		VkCommandBufferAllocateInfo		&getCommandBufferAllocateInfo();
		std::vector<VkCommandBuffer>	&getCommandBuffer(uint32_t group = 0);
		int32_t 						getErrorCode();

		void create					(Device &device);
		void allocateCommandBuffers	(Device &device);
		void freeCommandBuffers		(Device &device);
		void destroy				(Device &device);

		~CommandPool();

	private:
		VkCommandPool				self						= VK_NULL_HANDLE;
		VkCommandPoolCreateInfo		sCreateInfo					= {};
		VkAllocationCallbacks		sAllocation					= {};
		VkCommandBufferAllocateInfo	sCommandBufferAllocateInfo	= {};

		std::vector<std::vector<VkCommandBuffer>>	ppCommandBuffers;

		int32_t	codeOfError	= false;
};

#endif