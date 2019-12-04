/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   appExample.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:42:52 by vrichese          #+#    #+#             */
/*   Updated: 2019/12/04 20:22:28 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

int main(void)
{
	Triangle	app;

	try
	{
		app.run();
	}
	catch (const std::exception &error)
	{
		std::cerr << error.what() << std::endl;
		return EXIT_FAILURE;
	}
	return (0);
}