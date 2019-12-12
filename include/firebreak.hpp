/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firebreak.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:43:53 by vrichese          #+#    #+#             */
/*   Updated: 2019/12/12 17:58:03 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VK_CLASS_CONTAINER_HPP
# define VK_CLASS_CONTAINER_HPP

# define WIDTH	1920
# define HEIGHT	1080

# define APPLE	1
# define WIN32	2
# define WIN64	3
# define UNIX	4

#ifdef __APPLE__
# define OS APPLE
#elif __WIN32__
# define OS WIN32
#elif __WIN64__
# define OS WIN64
#elif __unix__
# define OS UNIX
#endif

#ifdef NDEBUG
	const bool validationLayers = false;
#else
	const bool validationLayers = true;

#endif

class Surface;
class Instance;
class Device;

# include <fstream>
# include <iostream>
# include <stdexcept>
# include <functional>
# include <vector>
# include <algorithm>
# include <cassert>
# include "/usr/local/include/vulkan/vulkan.h"
# include "/Users/vrichese/Workspace/Rus42/MyProjects/WanderingStar/include/glfw3.h"

# include "fbClassSurface.hpp"
# include "fbClassDevice.hpp"
# include "fbClassInstance.hpp"
# include "fbClassRender.hpp"
# include "fbClassBuffer.hpp"
# include "fbClassImage.hpp"

#endif