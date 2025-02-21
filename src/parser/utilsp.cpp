/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsp.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:16:43 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/21 18:04:08 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node/ANode.hpp"
#include "parser/tokenizer.hpp"
#include "parser/utils.hpp"
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <node/ValueTemplate.hpp>
#include <parser/parser.hpp>
#include <stdexcept>

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

	if (tokenizer::checkForTripleQuote(token, i))
		return toml::Value<std::string>(token.substr(3, token.length() - 3));
	else if (token[0] == '"' || token[0] == '\'')
		return toml::Value<std::string>(token.substr(0, token.length() - 2));

	return toml::Value<std::string>(token);
}

toml::Value<int16_t> convertInt(std::string token) {
	int16_t nb = std::atoi(token.c_str());

	return toml::Value<int16_t>(nb);
}

toml::Table convertTable(tokenizer::Tokenizer tokenizer) {
	std::string token = tokenizer.getNextToken();
	std::map<std::string, ANode>	map;

	while (!token.empty() || isTable(token)) {
		
		token = tokenizer.getNextToken();
	}
	return toml::Table(map);
}

ANode convertValue(std::string token) {
	if (isBool(token))
		return convertBool(token);
	else if (isInt(token))
		return convertInt(token);
	else if (isString(token))
		return convertString(token);
	else if (token[0] == '\n')
		throw(std::runtime_error("Please specify a value after ="));
	else if (token[0] == '=')
		throw(std::runtime_error("= present after ="));
	else
		throw(std::runtime_error("No value present")); 
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

bool isTable(std::string token) {
	if (token[0] == '[' && token[token.length()] == ']')
		return true;
	else
		return false;
}

bool isTableArray(std::string token) {
	if (token[0] == '[' && token[token.length()] == ']')
		throw std::runtime_error("Array of table are not yet supported : " +
								 token);
	else
		return false;
}
