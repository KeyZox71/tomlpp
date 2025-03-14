/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:46:42 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/14 18:46:47 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "cppeleven.hpp"
#include "node/ANode.hpp"
#include "node/Table.hpp"
#include "node/ValueTemplate.hpp"
#include "node/default.hpp"
#include "parser/tokenizer.hpp"
#include <cstdlib>
#include <node/default.hpp>
#include <sstream>
#include <stdexcept>
#include <string>

namespace toml {
namespace parser {

/**
 *	@brief	Internal function used for throwing error if something can't be
 *			parsed
 */
class ParseError : public std::runtime_error {
  public:
	explicit ParseError(const std::string &message)
		: std::runtime_error("Parse error: " + message) {}
};

struct keyValue {
	std::string key;
	ANode	   *content;
};

/**
 *	@brief	Used to convert string to boolean
 */
static inline bool convertBool(std::string boolean) {
	if (boolean == "true")
		return true;
	else
		return false;
}

/**
 *	@brief	Is used to split a dotted key
 *
 *	@param	The dotted key
 *
 *	@return	A pointer to a vector container every part of the key
 */
static inline std::vector<std::string> *splitKey(std::string key) {
	std::stringstream		  ss(key);
	std::vector<std::string> *splitedKey = new std::vector<std::string>;
	std::string				  singleKey;

	while (std::getline(ss, singleKey, '.')) {
		splitedKey->push_back(singleKey);
	}
	return splitedKey;
}

/**
 *	@brief	Class used to parse the content return by the tokenizer
 *
 *	Get the tokenizer's content and parse into an AST defined in ANode(and it's
 *	derived classes)
 */
class Parser {
  public:
	Parser(tokenizer::Tokenizer &tokenizer) : _tokenizer(tokenizer) {
		_tokenizer.next();
		_finalNode = new Table();
		log("toml", "parser", "constructor called");
	}
	~Parser(void) {
		delete _finalNode;
		log("toml", "parser", "destructor called");
	}

	/**
	 *	@brief	Can be used to parse the tokens returned by the tokenizer
	 *
	 *	@return	A pointer to the main table in the AST
	 */
	ANode *parse(void) {
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

  protected:
  private:
	tokenizer::Tokenizer _tokenizer; ///> the tokenizer class
	ANode				*_finalNode; ///> the final table that will be returned

	/**
	 *	@brief	Used to parse a key-value pair
	 *
	 *	@return	A pointer to the newly allocted Value (new Value<type>())
	 */
	keyValue parseKeyValue(void) {
		expect(tokenizer::KEY);
		keyValue kV;
		kV.key = _tokenizer.peek()->token;
		_tokenizer.next();

		expect(tokenizer::ASSIGNMENT_OPERATOR);
		_tokenizer.next();

		switch (_tokenizer.peek()->type) {
		case (tokenizer::BOOL):
			kV.content = new Value<bool>(parseBool());
			break;
		case (tokenizer::STRING):
			kV.content = new Value<std::string>(_tokenizer.peek()->token);
			break;
		case (tokenizer::NUMBER):
			kV.content = new Value<int32_t>(parseNumber());
			break;
		case (tokenizer::ARRAY_START):
			kV.content = parseArray();
			break;
		default:
			delete _finalNode;
			throw ParseError(
				"Expected a value but found a " +
				tokenizer::tokenTypetoStr(_tokenizer.peek()->type) + " = " +
				_tokenizer.peek()->token);
		}
		return kV;
	}
	/**
	 *	@brief	Used to parse an table
	 *
	 *	@param	The name (or path) of the table that will be parsed
	 */
	void parseTable(std::string &table) {
		while (_tokenizer.peek() != not_nullptr &&
			   _tokenizer.peek()->type != tokenizer::END &&
			   _tokenizer.peek()->type != tokenizer::TABLE_START) {
			keyValue kV = parseKeyValue();
			addToTable(table, kV);
			_tokenizer.next();
			std::cout << *(std::string *)(kV.content)->getValue() << std::endl;
			expect(tokenizer::NEWLINE);
			_tokenizer.next();
		}
		return;
	}
	/**
	 *	@brief	Used to parse an array
	 *
	 *	@return	A pointer to the newly allocted array (new Array())
	 */
	ANode *parseArray(void) {
		std::vector<ANode> *array;

		expect(tokenizer::ARRAY_START);
		array = new std::vector<ANode>;
		while (_tokenizer.peek()->type != tokenizer::END &&
			   _tokenizer.peek()->type != tokenizer::ARRAY_END) {
			try {
				switch (_tokenizer.peek()->type) {
				case (tokenizer::BOOL):
					array->push_back(Value<bool>(parseBool()));
					break;
				case (tokenizer::STRING):
					array->push_back(
						Value<std::string>(_tokenizer.peek()->token));
					break;
				case (tokenizer::NUMBER):
					array->push_back(Value<int32_t>(parseNumber()));
					break;
				default:
					throw ParseError(
						"Expected a value but found a " +
						tokenizer::tokenTypetoStr(_tokenizer.peek()->type) +
						" = " + _tokenizer.peek()->token);
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
	 *	@brief	Used to parse boolean value from the current token
	 *
	 *	@return	The parsed boolean
	 */
	bool parseBool(void) {
		if (_tokenizer.peek()->token == "true")
			return true;
		else
			return false;
	}
	/**
	 *	@brief	Used to parse number value from the current token
	 *
	 *	@note	Throw an error if atoi doen't work
	 *
	 *	@return	A value class with the number in it
	 */
	int32_t parseNumber(void) {
		try {
			if (_tokenizer.peek()->token == "0")
				return 0;
			int32_t nb = std::atoi(_tokenizer.peek()->token.c_str());
			if (nb == 0)
				throw ParseError(
					"Error while parsing number : " + _tokenizer.peek()->token +
					" should be atoi compliant");
			else
				return nb;
		} catch (std::runtime_error &e) {
			throw e;
		}
	}

	/**
	 *	@brief	Can be used to insert a keyValue a specific place in the table
	 *
	 *	@param	The location of the newly added keyvalue
	 *	@param	The keyValue to add
	 */
	void addToTable(std::string keyTable, parser::keyValue keyVal) {
		if (keyVal.key.empty()) {
			delete _finalNode;
			throw ParseError("Expected a key but got nothing :(");
		}

		std::vector<std::string> *splitedKey = splitKey(keyVal.key);
		if (!keyTable.empty()) {
			std::vector<std::string> *newKeyTable = splitKey(keyTable);
			splitedKey->insert(splitedKey->begin(), newKeyTable->begin(),
							   newKeyTable->end());
			delete newKeyTable;
		}

		std::map<std::string, ANode *>	  *actualTable = _finalNode->getTable();
		std::vector<std::string>::iterator it = splitedKey->begin();
		std::string						   keyToFind = *it;


		std::cout << actualTable << std::endl;
		for (size_t i = 0; i < splitedKey->size() - 1; i++) {
			std::string keyToFind = *it;
			if ((*actualTable).find(keyToFind) == actualTable->end()) {
				(*actualTable)[keyToFind] = new Table();
				actualTable = actualTable->at(keyToFind)->getTable();
			} else if (actualTable->find(keyToFind)->second->type() == TABLE) {
				actualTable = actualTable->at(keyToFind)->getTable();
			} else {
				delete _finalNode;
				throw ParseError(
					"key : " + keyTable + "." + keyVal.key +
					" is already assigned to a " +
					nodeTypeToStr(actualTable->at(keyToFind)->type()));
			}
			it++;
		}
		if (!splitedKey->back().empty()) {
			// need to copy deep copy of keyval.content and not assigning - TODO
			if (keyVal.content->type() == STRING)
				(*actualTable)[keyToFind] =  keyVal.content;
			std::cout << keyVal.content << std::endl;
			delete splitedKey;
			return;
		}
		delete splitedKey;
		throw ParseError("last key is empty :(");
	}

	/**
	 *	@brief	Check if the current token is of the expected type
	 *
	 *	@param	The expected token
	 */
	void expect(tokenizer::tokenType expected) {
		if (_tokenizer.peek()->type == expected)
			return;
		delete _finalNode;
		throw ParseError("Expected a " + tokenizer::tokenTypetoStr(expected) +
						 " but got a " +
						 tokenizer::tokenTypetoStr(_tokenizer.peek()->type));
	}

};

}; // namespace parser
}; // namespace toml
