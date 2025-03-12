/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:46:30 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/12 09:08:27 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.hpp"
#include "cppeleven.hpp"
#include "node/ANode.hpp"
#include "node/Array.hpp"
#include "node/Table.hpp"
#include "parser/tokenizer.hpp"
#include <node/default.hpp>
#include <stdexcept>
#include <string>

using namespace toml;
using namespace parser;

ANode *Parser::parse(void) {
	std::string actualTable = "";
	if (_tokenizer.peek()->type == tokenizer::KEY) {
		parseTable(actualTable);
	}
	while (_tokenizer.peek()->type != tokenizer::END) {
		expect(tokenizer::TABLE_START);
		_tokenizer.next();
		expect(tokenizer::KEY);
		actualTable = _tokenizer.peek()->token;
		_tokenizer.next();
		expect(tokenizer::TABLE_END);
		_tokenizer.next();
		parseTable(actualTable);
	}
	return _finalNode;
}

void Parser::expect(tokenizer::tokenType expected) {
	if (_tokenizer.peek()->type == expected)
		return;
	throw ParseError("Expected a " + tokenizer::tokenTypetoStr(expected) +
					 " but got a " +
					 tokenizer::tokenTypetoStr(_tokenizer.peek()->type) +
					 " = " + _tokenizer.peek()->token);
}
