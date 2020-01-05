/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firebreak.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:43:53 by vrichese          #+#    #+#             */
/*   Updated: 2019/12/30 16:39:50 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VK_CLASS_CONTAINER_HPP
# define VK_CLASS_CONTAINER_HPP

# define WIDTH	1920
# define HEIGHT	1080
# define SAFEMODE
/*
**	Mode bits
*/
# define FINISH_HIM			0x01
/*
**
*/

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

#ifdef SAFEMODE
	# define THROW_EXCEPTION_IN_CASE_OF_ERROR(x) if (codeOfError != VK_SUCCESS) throw std::runtime_error(x);
#else
	# define THROW_EXCEPTION_IN_CASE_OF_ERROR(x)
#endif

# ifdef SAFEMODE
	#define safeCall(x) try { x(); } catch (const std::exception &error){ std::cerr << error.what() << std::endl; exit(EXIT_FAILURE); }
# else
	#define safeCall(x) x()
# endif

class Surface;
class Instance;
class Device;

# include <vector>
# include <cassert>
# include <fstream>
# include <iostream>
# include <stdexcept>
# include <algorithm>
# include <functional>
# include <vulkan/vulkan.h>
# include <initializer_list>

# include "fbClassDevice.hpp"
# include "fbClassSurface.hpp"
# include "fbClassInstance.hpp"
# include "fbClassRender.hpp"
# include "fbClassBuffer.hpp"
# include "fbClassImage.hpp"
# include "fbClassPipeline.hpp"
# include "fbClassSemaphore.hpp"
# include "fbClassQueue.hpp"
# include "fbClassComputePipeline.hpp"
# include "fbClassShader.hpp"
# include "fbClassCache.hpp"
# include "fbClassCommandPool.hpp"
# include "fbClassBufferView.hpp"
# include "fbClassImageView.hpp"
# include "fbClassDeviceMemory.hpp"
# include "fbClassFence.hpp"

#endif