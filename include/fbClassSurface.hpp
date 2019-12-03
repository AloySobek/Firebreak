/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassSurface.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:53:26 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/03 20:59:47 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_SURFACE_HPP
# define FB_CLASS_SURFACE_HPP

# include "vkClassContainer.hpp"

class Surface
{
	public:
		VkSurfaceKHR self = VK_NULL_HANDLE;
		VkSurfaceCapabilitiesKHR capabilities;
		uint32_t khrFormatsCount	  = 0;
		uint32_t khrPresentModesCount = 0;
		std::vector<VkSurfaceFormatKHR>	formats;
		std::vector<VkPresentModeKHR>	presentModes;

		Surface() { }
		Surface(GLFWwindow *pWindow, Instance instance);
		void init(GLFWwindow *pWindow, Instance instance);

		std::vector<VkSurfaceFormatKHR>	getFormats		(Device device);
		std::vector<VkPresentModeKHR>	getPresentModes	(Device device);

		void	checkSwapChainSupporting(Device device);

		~Surface() { }

	private:
		bool calledFormats = false;
		bool calledPresent = false;
		int32_t codeOfError= false;
};

#endif