/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vkClassContainer.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:43:53 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/23 20:32:46 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VK_CLASS_CONTAINER_HPP
# define VK_CLASS_CONTAINER_HPP

# include <fstream>
# include <iostream>
# include <string>
# include <stdexcept>
# include <functional>
# include <cstdlib>
# include <cstring>
# include <vector>
# include <algorithm>
# include "/usr/local/include/vulkan/vulkan.h"
# include "../include/glfw3.h"

# include "vkClassVulkan.hpp"
# include "vkClassWindow.hpp"
# include "vkClassTriangle.hpp"

# define USER_CHOOSE	0
# define ONE_LAYER_MODE	0
# define ALL_LAYER_OFF	1

#endif