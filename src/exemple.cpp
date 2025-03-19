/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exemple.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:39:49 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/19 14:49:34 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node/ANode.hpp"
#include "tomlpp.hpp"

using namespace toml;

int	main(int, char **av) {
	Toml	file(av[1]);

	try {
		file.parse();
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	ANode *node = file.getParsedFile();

	std::map<std::string, ANode *> table = (*(*node->getTable())["test"]->getTable());

	std::cout << table.begin()->first << std::endl;
	
	delete node;
}
