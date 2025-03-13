/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:46:30 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/13 20:42:01 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.hpp"
#include "node/ANode.hpp"
#include "parser/tokenizer.hpp"

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
	delete _finalNode;
	throw ParseError("Expected a " + tokenizer::tokenTypetoStr(expected) +
					 " but got a " +
					 tokenizer::tokenTypetoStr(_tokenizer.peek()->type) +
					 " = " + _tokenizer.peek()->token);
}
