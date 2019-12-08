/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassInstance.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:22:46 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/08 14:19:06 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_INSTANCE_HPP
# define FB_CLASS_INSTANCE_HPP

# include "firebreak.hpp"

class Instance
{
	public:
		Instance(const void *pNext);
		Instance(VkInstanceCreateFlags flags = VK_NULL_HANDLE, const void *pNext = nullptr);
		Instance(Instance &anotherInstance) { };

		void setupNext(const void *pNext);
		void setupFlags(VkInstanceCreateFlags flags);
		void setupAppInfo(const char *pAppName = "Firebreak",
							const char *pEngineName = "NoEngine",
								uint32_t appVersion = VK_MAKE_VERSION(1, 0, 0),
									uint32_t engineVersion = VK_MAKE_VERSION(1, 0, 0));
		void setupLayers(std::vector<const char *> &desiredLayers);
		void setupExtensions(std::vector<const char *> &desiredExtensions);

		VkInstance				getSelf();
		VkInstanceCreateFlags	getFlags();
		const void				*getNext();
		const VkApplicationInfo	*getAppInfo();
		VkLayerProperties		*getLayers();
		VkExtensionProperties	*getExtensions();
		uint32_t				getLayersAmount();
		uint32_t				getExtensionsAmount();

		void create();

		VkInstance operator()(void);

		~Instance() { }

	private:
		VkInstance				self				= VK_NULL_HANDLE;
		VkInstanceCreateInfo	sCreateInfo			= {};
		VkApplicationInfo		sApplicationInfo	= {};

		VkLayerProperties	  *pAvailableLayers;
		VkExtensionProperties *pAvailableExtensions;

		const char **ppEnabledLayerNames;
		const char **ppEnabledExtensionNames;

		u_int32_t enabledLayerCount			= 0;
		u_int32_t availableLayersCount		= 0;
		u_int32_t enabledExtensionCount		= 0;
		u_int32_t availableExtensionsCount	= 0;

		bool	calledLayers	 	= false;
		bool	calledExtensions 	= false;
		int32_t	codeOfError			= false;

		bool	isLayerSuitable(VkLayerProperties sLayer, std::vector<const char *> &desiredLayers);
		bool	isExtensionSuitable(VkExtensionProperties sExtension, std::vector<const char *> &desiredExtensions);
};

#endif