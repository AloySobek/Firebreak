/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassInstance.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:22:46 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/02 18:47:56 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_INSTANCE_HPP
# define FB_CLASS_INSTANCE_HPP

# include "vkClassContainer.hpp"

# define INSTANCE_EASY_MODE 1

class Instance
{
	public:
		VkInstanceCreateInfo	sSelfCreateInfo		= {};
		VkApplicationInfo		sAppCreateInfo		= {};
		VkInstance				self 				= VK_NULL_HANDLE;

		Surface			surface;
		PhysicalDevice	physicalDevice;
		Device			device;
		SwapChain		swapChain;

		u_int32_t	availableInstanceLayersCount		= 0;
		u_int32_t	selectedInstanceLayersCount			= 0;
		u_int32_t	availableInstanceExtensionsCount	= 0;
		u_int32_t	selectedInstanceExtensionsCount		= 0;
		u_int32_t	availablePhysicalDeviceCount		= 0;

		Instance()
		{
			if (INSTANCE_EASY_MODE)
			{
				setupAppInfo("Default", "Default", VK_MAKE_VERSION(1, 0, 0) , VK_MAKE_VERSION(1, 0, 0));
				setupCreateInfo();
				create();
			}
		}

		void	setupAppInfo	(const char *pAppName, const char *pEngineName,
									uint32_t appVersion, uint32_t engineVersion);
		void	setupLayers		(std::vector<const char *> &desiredLayers);
		void	setupExtensions	(std::vector<const char *> &desiredExtensions);
		void	setupCreateInfo	(void);
		void	create			(void);

		std::vector<VkLayerProperties>		getLayers		();
		std::vector<VkExtensionProperties>	getExtensions	();

		VkInstance	getSelf(void);
		VkInstance	operator()(void);

		void	findDevice(int deviceType);

		void	createSurface(GLFWwindow *pWindow);

		~Instance()
		{
			;//vkDestroyInstance(self, nullptr);
		}

	private:
		std::vector<VkExtensionProperties>	pAvailableInstanceExtensions;
		std::vector<VkLayerProperties>		pAvailableInstanceLayers;
		std::vector<VkPhysicalDevice>		pAvailablePhysicalDevices;
		std::vector<const char *>			ppSelectedLayers;
		std::vector<const char *>			ppSelectedExtensions;

		int32_t	codeOfError	= false;

		bool	calledLayers		= false;
		bool	calledExtensions	= false;

		bool		isLayerSuitable		(VkLayerProperties sLayer, std::vector<const char *> &desiredLayers);
		bool		isExtensionSuitable	(VkExtensionProperties sExtension, std::vector<const char *> &desiredExtensions);
		bool		isDeviceSuitable	(int deviceType);

		void		error(const char *error_message);
};

#endif