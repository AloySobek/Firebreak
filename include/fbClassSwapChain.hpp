/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassSwapChain.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:45:17 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/02 18:48:12 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_SWAP_CHAIN_HPP
# define FB_CLASS_SWAP_CHAIN_HPP

# include "vkClassContainer.hpp"

class	SwapChain
{
	public:
		SwapChain() {}
		VkSwapchainKHR				self			= VK_NULL_HANDLE;
		VkSwapchainCreateInfoKHR	sCreateInfo		= {};
		VkSurfaceFormatKHR			sFormat			= {};
		VkPresentModeKHR			sPresentMode	= {};
		VkExtent2D					extent			= {WIDTH, HEIGHT};

		uint32_t					imageCount		= 0;

		std::vector<VkImage>		images;

		Device			device;
		Surface			surface;

		void	setupSwapChain();
		void	setupSwapChainCreateInfo();
		void	create();

		~SwapChain() { }

	private:
		int32_t codeOfError = false;
};

#endif