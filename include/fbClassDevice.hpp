/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassDevice.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:33:37 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/02 18:47:45 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_DEVICE_HPP
# define FB_CLASS_DEVICE_HPP

# include "vkClassContainer.hpp"

class Device
{
	public:
		VkDevice			self		= VK_NULL_HANDLE;
		VkDeviceCreateInfo	sCreateInfo	= {};

		PhysicalDevice	physicalDevice;
		VkQueue			graphicQueue;
		VkQueue			presentQueue;

		uint32_t	queueFamilyCreateInfoCount	= 0;

		Device() { }

		void	setupQueueFamilyCreateInfo(float queuePriority, int queueCount, int queueIndex);
		void	setupCreateInfo();
		void	attachWithPhysicalDevice(PhysicalDevice	&device);
		void	create();
		void	retrieveAllQueus();

		~Device() { }

	private:
		std::vector<VkDeviceQueueCreateInfo>	queuesFamilies;

		int32_t	codeOfError = false;
};

#endif