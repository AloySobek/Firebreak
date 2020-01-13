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

class FbSwapchain
{
	public:
		FbSwapchain(VkAllocationCallbacks allocation) : FbSwapchain({}, allocation);
		FbSwapchain(VkSwapchainCreateInfoKHR info = {}, VkAllocationCallbacks allocation = {});

		VkSwapchainKHR				&getSelf();
		VkSwapchainCreateInfoKHR	&getCreateInfo();
		VkAllocationCallbacks		&getAllocation();
		int32_t						getCodeOfError();

		void	create(FbDevice &device);
		void	destroy(FbDevice &device);

	private:
		VkSwapchainKHR				self;
		VkSwapchainCreateInfoKHR	sCreateInfo;
		VkAllocationCallbacks		sAllocation;

		int32_t	codeOfError;
}

#endif