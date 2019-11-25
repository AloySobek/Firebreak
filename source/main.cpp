/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:42:52 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/23 18:36:41 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vkClassContainer.hpp"

int main(void)
{
	Triangle	app;

	try
	{
		app.run();
	}
	catch (const std::exception &error)
	{
		std::cout << "ERROR\n";
		std::cerr << error.what() << std::endl;
		return EXIT_FAILURE;
	}
	return (0);
}