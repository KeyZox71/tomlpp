/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:45:45 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/21 18:04:01 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.hpp"
#include "Log.hpp"
#include "node/ANode.hpp"
#include "node/ValueTemplate.hpp"
#include "node/Array.hpp"
#include "parser/utils.hpp"
#include <stdexcept>

using namespace toml;
using namespace parser;

parse::parse(std::string name) : _tokenizer(name) {
	log("tomlParser", "", "constructor called");
	std::string token = _tokenizer.getNextToken();
	ANode		node;

	while (!token.empty()) {
		if (isTable(token)) {

		}
		token = _tokenizer.getNextToken();
	}
}

parse::~parse(void) { log("tomlParser", "", "destructor called"); }

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
