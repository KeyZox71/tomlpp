/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:46:30 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/03 11:07:03 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "parser/parser.hpp"
#include "cppeleven.hpp"
#include "node/ANode.hpp"
#include "node/Array.hpp"
#include "node/Table.hpp"
#include "parser/tokenizer.hpp"
#include <cstdint>
#include <node/default.hpp>
#include <stdexcept>
#include <string>

using namespace toml;
using namespace parser;

ANode *Parser::parse(void) {}

keyValue Parser::parseKeyValue(void) {
	expect(tokenizer::KEY);
	keyValue kV;
	kV.key = _tokenizer.peek()->token;
	_tokenizer.next();

	expect(tokenizer::ASSIGNMENT_OPERATOR);
	_tokenizer.next();

	switch (_tokenizer.peek()->type) {
	case (tokenizer::BOOL):
		kV.content = new Value<bool>(*(bool *)parseBool().getValue());
	case (tokenizer::STRING):
		kV.content =
			new Value<std::string>(*(std::string *)parseString().getValue());
	case (tokenizer::NUMBER):
		kV.content = new Value<int32_t>(*(int32_t *)parseNumber().getValue());
	case (tokenizer::ARRAY_START):
		kV.content = parseArray();
	default:
		throw ParseError("Expected a value but found a " +
						 tokenizer::tokenTypetoStr(_tokenizer.peek()->type) +
						 " = " + _tokenizer.peek()->token);
	}
	return kV;
}

ANode *Parser::parseTable(void) {
	Table *table;

	while (_tokenizer.peek()->type != tokenizer::END &&
		   _tokenizer.peek()->type != tokenizer::TABLE_START) {
		
	}
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
			break;
		expect(tokenizer::COMMA);
		_tokenizer.next();
	}
	if (_tokenizer.peek()->type == tokenizer::ARRAY_END) {
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
