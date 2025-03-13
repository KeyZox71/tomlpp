/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:46:30 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/13 20:36:33 by adjoly           ###   ########.fr       */
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
	throw ParseError("Expected a " + tokenizer::tokenTypetoStr(expected) +
					 " but got a " +
					 tokenizer::tokenTypetoStr(_tokenizer.peek()->type) +
					 " = " + _tokenizer.peek()->token);
}

void	clearArray(std::vector<ANode> *value) {
	delete value;
}

void	clearTable(std::map<std::string, ANode *> *table) {
	std::map<std::string, ANode *>::iterator it;
	for (it = table->begin(); it != table->end(); it++) {
		
	}
	delete table;
}

void	Parser::clear(void) {
	if (_finalNode->type() == TABLE) {
		std::map<std::string, ANode *> *table =  _finalNode->getTable();
		std::map<std::string, ANode *>::iterator it;

		for (it = table->begin(); it != table->end(); it++) {
			switch (it->second->type()) {
				case TABLE:
					clearTable(it->second->getTable());
					break;
				case ARRAY:
					clearArray(it->second->getArray());
					break;
				case BOOL:
				case INT:
				case STRING:
					delete it->second;
					break;
				default:
					break;
			};
		}

	}
}
