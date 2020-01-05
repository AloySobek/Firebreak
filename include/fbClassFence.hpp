/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassFence.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 14:32:14 by Rustam            #+#    #+#             */
/*   Updated: 2020/01/05 14:35:16 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_FENCE_HPP
# define FB_CLASS_FENCE_HPP

# include "firebreak.hpp"

class Fence
{
	public:
		Fence();

		VkFence		&getSelf();

		~Fence();

	private:
		VkFence	self;
};

#endif