/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:45:45 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/10 16:08:31 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.hpp"
#include "Log.hpp"
#include "node/ANode.hpp"
#include "node/Array.hpp"

using namespace toml;
using namespace parser;

parse::parse(std::string name) : _tokenizer(name) {
	log("tomlParser", "", "constructor called");
	std::string token = _tokenizer.getNextToken();
	ANode		node;

	while (!token.empty()) {
		node = _convertToken(token);
		switch (node.type()) {
		case EMPTY:
		case TABLE:
		case ARRAY:
		case BOOL:
		case STRING:
		case INT:
		case FLOAT:
			break;
		}
		token = _tokenizer.getNextToken();
	}
}

parse::~parse(void) { log("tomlParser", "", "destructor called"); }
