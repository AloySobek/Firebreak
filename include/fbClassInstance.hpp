/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassInstance.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:22:46 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/03 20:59:51 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_INSTANCE_HPP
# define FB_CLASS_INSTANCE_HPP

# include "vkClassContainer.hpp"

# define INSTANCE_EASY_MODE 1

class Instance
{
	public:
		VkInstance self = VK_NULL_HANDLE;

		u_int32_t	enabledLayerCount		 = 0;
		u_int32_t	availableLayersCount	 = 0;
		u_int32_t	enabledExtensionCount	 = 0;
		u_int32_t	availableExtensionsCount = 0;
		VkLayerProperties		*pAvailableLayers;
		VkExtensionProperties	*pAvailableExtensions;
		const char				**ppEnabledLayerNames;
		const char				**ppEnabledExtensionNames;
		Instance(const char *pAppName = "Firebreak",
					const char *pEngineName = "NoEngine",
						uint32_t appVersion = VK_MAKE_VERSION(1, 0, 0),
							uint32_t engineVersion = VK_MAKE_VERSION(1, 0, 0));
		void setupNext(const void *pNext);
		void setupFlags(VkInstanceCreateFlags flags);
		void setupAppInfo(const char *pAppName = "Firebreak",
							const char *pEngineName = "NoEngine",
								uint32_t appVersion = VK_MAKE_VERSION(1, 0, 0),
									uint32_t engineVersion = VK_MAKE_VERSION(1, 0, 0));
		void setupLayers(std::vector<const char *> &desiredLayers);
		void setupExtensions(std::vector<const char *> &desiredExtensions);
		void create(void);
		VkLayerProperties	*getLayers();
		VkExtensionProperties	*getExtensions();
		VkInstance	getSelf(void);
		VkInstance	operator()(void);

		SwapChain swapChain;

	private:
		VkInstanceCreateInfo	sCreateInfo			= {};
		VkApplicationInfo		sApplicationInfo	= {};
		bool	calledLayers	 	= false;
		bool	calledExtensions 	= false;
		int32_t	codeOfError			= false;
		bool	isLayerSuitable(VkLayerProperties sLayer, std::vector<const char *> &desiredLayers);
		bool	isExtensionSuitable(VkExtensionProperties sExtension, std::vector<const char *> &desiredExtensions);
};

#endif