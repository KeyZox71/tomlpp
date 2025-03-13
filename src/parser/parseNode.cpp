/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseNode.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:10:47 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/13 20:54:50 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/default.hpp"

using namespace toml;
using namespace parser;

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
		break;
	case (tokenizer::STRING):
		kV.content =
			new Value<std::string>(*(std::string *)parseString().getValue());
		break;
	case (tokenizer::NUMBER):
		kV.content = new Value<int32_t>(*(int32_t *)parseNumber().getValue());
		break;
	case (tokenizer::ARRAY_START):
		kV.content = parseArray();
		break;
	default:
		delete _finalNode;
		throw ParseError("Expected a value but found a " +
						 tokenizer::tokenTypetoStr(_tokenizer.peek()->type) +
						 " = " + _tokenizer.peek()->token);
	}
	return kV;
}

void	Parser::parseTable(std::string &table) {
	while (_tokenizer.peek()->type != tokenizer::END &&
		   _tokenizer.peek()->type != tokenizer::TABLE_START) {
		keyValue kV = parseKeyValue();
		addToTable(table, kV);
		_tokenizer.next();
		expect(tokenizer::NEWLINE);
		_tokenizer.next();
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
				break;
			case (tokenizer::STRING):
				array->push_back(parseString());
				break;
			case (tokenizer::NUMBER):
				array->push_back(parseNumber());
				break;
			default:
				throw ParseError(
					"Expected a value but found a " +
					tokenizer::tokenTypetoStr(_tokenizer.peek()->type) + " = " +
					_tokenizer.peek()->token);
			};
		} catch (std::runtime_error &e) {
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
	delete _finalNode;
	throw ParseError("Expected a " +
					 tokenizer::tokenTypetoStr(tokenizer::ARRAY_END) +
					 " but ended up to end of file");
}

/**
 *	@brief	convert a string to a boolean
 *
 *	@param	A string containing the boolean
 *
 *	@return The boolean :D
 */
bool	convertBool(std::string	boolean) {
	if (boolean == "true")
		return true;
	else
		return false;
}
