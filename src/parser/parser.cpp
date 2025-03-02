/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:46:30 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/01 11:11:19 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "parser/parser.hpp"
#include "cppeleven.hpp"
#include "node/ANode.hpp"
#include "node/Array.hpp"
#include "parser/tokenizer.hpp"
#include <node/default.hpp>
#include <stdexcept>

using namespace toml;
using namespace parser;

ANode *Parser::parse(void) {}

ANode *Parser::parseKeyValue(void) { expect(tokenizer::KEY); }

ANode *Parser::parseTable(void) {

}

ANode *Parser::parseArray(void) {
	std::vector<ANode> *array;

	expect(tokenizer::ARRAY_START);
	array = new std::vector<ANode>;
	while (_tokenizer.peek()->type != tokenizer::END &&
		   _tokenizer.peek()->type != tokenizer::ARRAY_END) {
		try {
			switch (_tokenizer.peek()->type) {
			case (tokenizer::BOOL):
				array->push_back(parseBool());
			case (tokenizer::STRING):
				array->push_back(parseString());
			case (tokenizer::NUMBER):
				array->push_back(parseNumber());
			default:
				throw ParseError(
					"Expected a value but found a " +
					tokenizer::tokenTypetoStr(_tokenizer.peek()->type) + " = " +
					_tokenizer.peek()->token);
			};
		} catch (std::runtime_error e) {
			throw e;
		}
		_tokenizer.next();
		if (_tokenizer.peek()->type == tokenizer::ARRAY_END)
			break ;
		expect(tokenizer::COMMA);
		_tokenizer.next();
	}
	if (_tokenizer.peek()->type != tokenizer::END) {
		return new Array(array);
	}
	throw ParseError("Expected a " +
					 tokenizer::tokenTypetoStr(tokenizer::ARRAY_END) +
					 " but ended up to end of file");
}

void Parser::expect(tokenizer::tokenType expected) {
	if (_tokenizer.peek()->type == expected)
		return;
	throw ParseError("Expected a " + tokenizer::tokenTypetoStr(expected) +
					 " but got a " +
					 tokenizer::tokenTypetoStr(_tokenizer.peek()->type) +
					 " = " + _tokenizer.peek()->token);
}
