/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassSurface.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:53:26 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/30 17:05:12 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_SURFACE_HPP
# define FB_CLASS_SURFACE_HPP

# include "firebreak.hpp"

class Surface
{
	public:
		Surface			();
		explicit Surface(std::initializer_list<int> initList);
		Surface			(Surface &anotherSurface);

		VkSurfaceKHR				&getSelf();
		VkSurfaceFormatKHR			&getFormat();
		VkSurfaceCapabilitiesKHR	&getCapabilities();
		int32_t						getCodeOfError();

		~Surface();

	private:
		VkSurfaceKHR				self			= VK_NULL_HANDLE;
		VkSurfaceFormatKHR			sFormat			= {};
		VkSurfaceCapabilitiesKHR	sCapabilities	= {};

		int32_t						codeOfError		= false;
};

class Surface2 : public Surface
{
	public:
		int test;
};

#endif