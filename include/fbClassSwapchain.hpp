/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassSwapchain.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 16:41:17 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/30 16:45:53 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_SWAPCHAIN_HPP
# define FB_CLASS_SWAPCHAIN_HPP

#include "firebreak.hpp"

class Swapchain
{
	public:
		Swapchain			();
		explicit Swapchain	(std::initializer_list<int> initList);
		Swapchain			(Swapchain &anotherSwapchain);

		VkSwapchainKHR				&getSelf();
		VkSwapchainCreateInfoKHR	&getCreateInfo();
		VkAllocationCallbacks		&getAllocation();

		void	create();
		void	destroy();

	private:
		VkSwapchainKHR				self		= VK_NULL_HANDLE;
		VkSwapchainCreateInfoKHR	sCreateInfo	= {};
		VkAllocationCallbacks		sAllocation = {};
}

#endif