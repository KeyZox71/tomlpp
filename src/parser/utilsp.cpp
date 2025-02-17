/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsp.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:16:43 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/17 14:31:14 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/utils.hpp"
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <node/ValueTemplate.hpp>
#include <parser/parser.hpp>

using namespace toml;
using namespace parser;

toml::Value<bool> convertBool(std::string token) {
	if (token.compare("true"))
		return toml::Value<bool>(true);
	else if (token.compare("false"))
		return toml::Value<bool>(false);
	return NULL;
}

toml::Value<std::string> convertString(std::string token) {
	size_t i = 0;

	if (tokenizer::checkForTripleQuote(token, i)) {
		while (!tokenizer::checkForTripleQuote(token, i))
			i++;
		return toml::Value<std::string>(token.substr(3, i - 3));
	} else if (token[0] == '"' || token[0] == '\'')
		return toml::Value<std::string>(token.substr(0, token.length() - 2));

	return toml::Value<std::string>(token);
}

toml::Value<int16_t> convertInt(std::string token) {
	int16_t nb = std::atoi(token.c_str());

	return toml::Value<int16_t>(nb);
}

bool isBool(std::string token) {
	if (token.compare("true") || token.compare("false"))
		return true;
	else
		return false;
}

bool isString(std::string token) {
	if (token[0] == '"' || token[0] == '\'')
		return true;
	else
		return false;
}

bool isInt(std::string token) {
	if (std::isdigit(token[0]) || token[0] == '-' || token[0] == '+')
		return true;
	else
		return false;
}
