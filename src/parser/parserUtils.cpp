/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:40:58 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/07 15:14:45 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cppeleven.hpp"
#include "parser/default.hpp"
#include "parser/tokenizer.hpp"
#include <sstream>
#include <string>
#include <vector>

using namespace toml;
using namespace parser;

std::vector<std::string> *splitKey(tokenizer::token key) {
	if (key.type == tokenizer::KEY) {
		std::stringstream		 ss(key.token);
		std::vector<std::string> splitedKey;
		std::string				 singleKey;

		while (std::getline(ss, singleKey, '.')) {
			splitedKey.push_back(singleKey);
		}

	} else {
		return not_nullptr;
	}
}
