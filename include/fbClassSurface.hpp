/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassSurface.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:53:26 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/02 17:07:35 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_SURFACE_HPP
# define FB_CLASS_SURFACE_HPP

# include "vkClassContainer.hpp"

class Surface
{
	public:
		VkSurfaceKHR	self = VK_NULL_HANDLE;

		VkSurfaceCapabilitiesKHR		capabilities;

		uint32_t		khrFormatsCount			= 0;
		uint32_t		khrPresentModesCount	= 0;

		Surface()
		{
			;
		}

		std::vector<VkSurfaceFormatKHR>	getFormats		(PhysicalDevice physicalDevice);
		std::vector<VkPresentModeKHR>	getPresentModes	(PhysicalDevice physicalDevice);

		void	checkSwapChainSupporting(PhysicalDevice physicalDevice);

		friend class Instance;
		friend class SwapChain;

		~Surface()
		{
			;
		}

	private:
		std::vector<VkSurfaceFormatKHR>	formats;
		std::vector<VkPresentModeKHR>	presentModes;

		bool calledFormats = false;
		bool calledPresent = false;
};

#endif