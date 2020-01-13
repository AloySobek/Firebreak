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

/*
**
*/

#ifdef SAFEMODE
	# define THROW_EXCEPTION_IN_CASE_OF_ERROR(x) if (codeOfError != VK_SUCCESS) throw std::runtime_error(x);
	# define SAFECALL(x) try { x(); } catch (const std::exception &error){ std::cerr << error.what() << std::endl; exit(EXIT_FAILURE); }
#else
	# define THROW_EXCEPTION_IN_CASE_OF_ERROR
	# define SAFECALL(x) x()
#endif

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

# include "fbClassInstance.hpp"
# include "fbClassDevice.hpp"
# include "fbClassImage.hpp"
# include "fbClassBuffer.hpp"
# include "fbClassSurface.hpp"
# include "fbClassRender.hpp"
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