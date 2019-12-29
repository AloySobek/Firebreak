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
		CommandPool() { }
		CommandPool(CommandPool &anotherCommandPool) { }

		VkCommandPool			&getSelf();
		VkCommandPoolCreateInfo	&getCreateInfo();
		VkAllocationCallbacks	&getAllocaiton();
		int32_t 				getErrorCode();

	private:
		VkCommandPool			self		= VK_NULL_HANDLE;
		VkCommandPoolCreateInfo	sCreateInfo	= {};
		VkAllocationCallbacks	sAllocation	= {};

		int32_t					codeOfError = false;
};

#endif