/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tomlpp.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:35:34 by adjoly            #+#    #+#             */
/*   Updated: 2025/01/25 15:23:55 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/toml.hpp"
#include <fstream>
#include <iostream>
#include <string>

toml	*toml::parse(std::string fileName) {
	std::ifstream	file(fileName.c_str());

	if (!file.is_open()) {
		std::cerr << "Error opening file" << std::endl;
		return new toml;
	}
	std::string	s;
	std::getline(file, s);

	file.close();
}
