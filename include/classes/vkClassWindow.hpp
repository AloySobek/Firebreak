/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vkClassWindow.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:50:43 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/23 20:37:14 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VK_CLASS_WINDOW_HPP
# define VK_CLASS_WINDOW_HPP

# include "vkClassContainer.hpp"

class Window
{
	public:
		int mWidth;
		int	mHeight;
		GLFWwindow *mpWindow;

		Window() : mWidth(1920), mHeight(1080)
		{
			glfwInit();
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			mpWindow = glfwCreateWindow(mWidth, mHeight, "Vulkan", nullptr, nullptr);
		}

		void mainLoop(Vulkan vulkan)
		{
			while (!glfwWindowShouldClose(mpWindow))
			{
				glfwPollEvents();
				vulkan.vkDrawFrame();
			}
		}
};

#endif