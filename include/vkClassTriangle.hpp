/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vkClassTriangle.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:46:03 by vrichese          #+#    #+#             */
/*   Updated: 2019/12/05 15:51:19 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VK_CLASS_TRIANGLE_HPP
# define VK_CLASS_TRIANGLE_HPP

# include "firebreak.hpp"

class Triangle
{
	public:
		Vulkan		mVulkanObject;
		Window		mWindowObject;
		int			mProgramBuildError;

		Triangle(): mProgramBuildError(0) {}

		void run()
		{
			mVulkanObject.run(mWindowObject.mpWindow);
			mWindowObject.mainLoop(mVulkanObject);
		}
};

#endif