/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassInstance.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:22:46 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/01 20:22:48 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_INSTANCE_HPP
# define FB_CLASS_INSTANCE_HPP

# include "vkClassContainer.hpp"

# define AS_VECTOR		1

class Instance
{
	public:
		VkInstanceCreateInfo	sSelfCreateInfo		= {};
		VkApplicationInfo		sAppCreateInfo		= {};
		VkInstance				self 				= VK_NULL_HANDLE;

		PhysicalDevice	physicalDevice;

		u_int32_t	availableInstanceLayersCount		= 0;
		u_int32_t	selectedInstanceLayersCount			= 0;
		u_int32_t	availableInstanceExtensionsCount	= 0;
		u_int32_t	selectedInstanceExtensionsCount		= 0;
		u_int32_t	availablePhysicalDeviceCount		= 0;

		Instance() { }

		void provideLayersExtensions(std::vector<const char *> layers,
									std::vector<const char *> extensions)
		{
			ppSelectedLayers		= layers;
			ppSelectedExtensions	= extensions;
		}

		void	init(const char *pAppName, const char *pEngineName,
					uint32_t appVersion, uint32_t engineVersion);

		std::vector<VkLayerProperties>		getLayers		();
		std::vector<VkExtensionProperties>	getExtensions	();

		void	findDevice(int deviceType, std::vector<const char *> layers,
								std::vector<const char *> extensions);

		VkInstance	getSelf(void);
		VkInstance	operator()(void);

		~Instance()
		{
			;//vkDestroyInstance(self, nullptr);
		}

	private:
		std::vector<VkExtensionProperties>	pAvailableInstanceExtensions;
		std::vector<VkLayerProperties>		pAvailableInstanceLayers;
		std::vector<const char *>			ppSelectedLayers;
		std::vector<const char *>			ppSelectedExtensions;
		std::vector<VkPhysicalDevice>		pAvailablePhysicalDevices;

		u_int32_t	codeOfError = false;

		u_int32_t	calledLayers		= false;
		u_int32_t	calledExtensions	= false;

		void		setupAppInfo(const char *pAppName, const char *pEngineName,
									uint32_t appVersion, uint32_t engineVersion);
		void		setupLayers();
		bool		isLayerSuitable(VkLayerProperties sLayer);
		void		setupExtensions();
		bool		isExtensionSuitable(VkExtensionProperties sExtension);
		void		setupCreateInfo();
		void		createObj();
		bool		isDeviceSuitable(int deviceType);
		void		error(const char *error_message);
};

#endif