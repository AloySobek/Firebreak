/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vkClassTriangle.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:46:03 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/23 19:55:30 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VK_CLASS_TRIANGLE_HPP
# define VK_CLASS_TRIANGLE_HPP

# include "vkClassContainer.hpp"

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