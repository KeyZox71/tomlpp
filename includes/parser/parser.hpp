/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:46:42 by adjoly            #+#    #+#             */
/*   Updated: 2025/07/15 20:50:19 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "cppeleven.hpp"
#include "node/ANode.hpp"
#include "node/Table.hpp"
#include "node/ValueTemplate.hpp"
#include "node/default.hpp"
#include "parser/tokenizer.hpp"
#include <cmath>
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

/**
 *	@brief	struc that can be used to store a pair key value
 */
struct keyValue {
	std::string key;
	ANode *		content;
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

	while (std::getline(ss, singleKey, '.'))
		splitedKey->push_back(singleKey);
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
		nextToken();
		_finalNode = new Table();
		log("toml", "parser", "constructor called");
	}
	~Parser(void) { log("toml", "parser", "destructor called"); }

	/**
	 *	@brief	Can be used to parse the tokens returned by the tokenizer
	 *
	 *	@return	A pointer to the main table in the AST
	 */
	ANode *parse(void) {
		try {
			std::string actualTable = "";
			if (_tokenizer.peek()->type == tokenizer::KEY ||
				_tokenizer.peek()->type == tokenizer::NUMBER) {
				parseTable(actualTable);
			}
			while (_tokenizer.peek()->type != tokenizer::END) {
				expect(tokenizer::TABLE_START);
				nextToken();
				expect(tokenizer::KEY);
				actualTable = _tokenizer.peek()->token;
				nextToken();
				expect(tokenizer::TABLE_END);
				nextToken();
				expect(tokenizer::NEWLINE);
				while (_tokenizer.peek()->type == tokenizer::NEWLINE) {
					nextToken();
				}
				parseTable(actualTable);
			}
		} catch (const ParseError &e) {
			throw e;
		} catch (const tokenizer::TokenizerError &e) {
			delete _finalNode;
			throw e;
		}
		return _finalNode;
	}

  protected:
  private:
	tokenizer::Tokenizer _tokenizer; ///> the tokenizer class
	ANode *				 _finalNode; ///> the final table that will be returned

	/**
	 *	@brief	Used to parse a key-value pair
	 *
	 *	@return	A pointer to the newly allocted Value (new Value<type>())
	 */
	keyValue parseKeyValue(void) {
		std::vector<tokenizer::tokenType> expectedTypes;
		expectedTypes.push_back(tokenizer::NUMBER);
		expectedTypes.push_back(tokenizer::KEY);
		multiExpect(expectedTypes);

		keyValue kV;
		kV.key = _tokenizer.peek()->token;
		nextToken();

		expect(tokenizer::ASSIGNMENT_OPERATOR);
		nextToken();

		switch (_tokenizer.peek()->type) {
		case (tokenizer::BOOL):
			kV.content = new Value<bool>(new bool(parseBool()));
			break;
		case (tokenizer::STRING):
			kV.content = new Value<std::string>(
				new std::string(_tokenizer.peek()->token));
			break;
		case (tokenizer::NUMBER):
			kV.content = new Value<int32_t>(new int32_t(parseNumber()));
			break;
		case (tokenizer::ARRAY_START):
			kV.content = parseArray();
			break;
		default:
			delete _finalNode;
			throw ParseError(
				"Expected a value but found a " +
				tokenizer::tokenTypetoStr(_tokenizer.peek()->type));
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
			nextToken();
			expect(tokenizer::NEWLINE);
			while (_tokenizer.peek()->type == tokenizer::NEWLINE) {
				nextToken();
			}
		}
		return;
	}
	/**
	 *	@brief	Used to parse an array
	 *
	 *	@return	A pointer to the newly allocted array (new Array())
	 */
	ANode *parseArray(void) {
		std::vector<ANode *> *array;

		expect(tokenizer::ARRAY_START);
		nextToken();
		array = new std::vector<ANode *>;
		while (_tokenizer.peek()->type != tokenizer::END &&
			   _tokenizer.peek()->type != tokenizer::ARRAY_END) {
			try {
				switch (_tokenizer.peek()->type) {
				case (tokenizer::BOOL):
					log("toml", "parser", "pushed back in to array a bool");
					array->push_back(new Value<bool>(new bool(parseBool())));
					break;
				case (tokenizer::STRING):
					log("toml", "parser", "pushed back in to array a string");
					array->push_back(new Value<std::string>(
						new std::string(_tokenizer.peek()->token)));
					break;
				case (tokenizer::NUMBER):
					log("toml", "parser", "pushed back in to array a int");
					array->push_back(
						new Value<int32_t>(new int32_t(parseNumber())));
					break;
				default:
					// delete _finalNode;
					throw ParseError(
						"Expected a value but found a " +
						tokenizer::tokenTypetoStr(_tokenizer.peek()->type) +
						" = " + _tokenizer.peek()->token);
				};
			} catch (const ParseError &e) {
				if (!array->empty()) {
					for (std::vector<ANode *>::iterator it = array->begin();
						 it != array->end(); it++)
						delete *it;
				}
				delete array;
				delete _finalNode;
				throw e;
			}
			try {
				nextToken();
			} catch (const tokenizer::TokenizerError &e) {
				if (!array->empty()) {
					for (std::vector<ANode *>::iterator it = array->begin();
						 it != array->end(); it++)
						delete *it;
				}
				delete array;
				throw e;
			}
			if (_tokenizer.peek()->type == tokenizer::ARRAY_END)
				break;
			try {
				expect(tokenizer::COMMA);
				nextToken();
			} catch (const ParseError &e) {
				if (!array->empty()) {
					for (std::vector<ANode *>::iterator it = array->begin();
						 it != array->end(); it++)
						delete *it;
				}
				delete array;
				throw e;
			}
		}
		if (_tokenizer.peek()->type == tokenizer::ARRAY_END) {
			return new Array(array);
		}
		if (!array->empty()) {
			for (std::vector<ANode *>::iterator it = array->begin();
				 it != array->end(); it++)
				delete *it;
		}
		delete array;
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
		} catch (const ParseError&e) {
			throw e;
		}
	}

	/**
	 *	@brief	Can be used to insert a keyValue a specific place in the
	 *table
	 *
	 *	@param	The location of the newly added keyvalue
	 *	@param	The keyValue to add
	 */
	void addToTable(std::string keyTable, parser::keyValue keyVal) {
		if (keyVal.key.empty()) {
			delete _finalNode;
			throw ParseError("Expected a key but got nothing :(");
		}

		std::vector<std::string> *tableKey;

		if (keyTable.empty()) {
			tableKey = splitKey(keyVal.key);
		} else {
			tableKey = splitKey(keyTable);
			std::vector<std::string> *valKey = splitKey(keyVal.key);
			tableKey->insert(tableKey->end(), valKey->begin(), valKey->end());
			delete valKey;
		}

		std::map<std::string, ANode *> *   actualTable = _finalNode->getTable();
		std::vector<std::string>::iterator it = tableKey->begin();
		std::string						   keyToFind = *it;

		for (size_t i = 0; i < tableKey->size() - 1; i++) {
			std::string keyToFind = *it;
			if ((*actualTable).find(keyToFind) == actualTable->end()) {
				(*actualTable)[keyToFind] = new Table();
				actualTable = actualTable->at(keyToFind)->getTable();
				log("toml", "parser", "creating table : " + keyToFind);
			} else if (actualTable->find(keyToFind)->second->type() == TABLE) {
				actualTable = actualTable->at(keyToFind)->getTable();
				log("toml", "parser", "going to table : " + keyToFind);
			} else {
				delete _finalNode;
				throw ParseError(
					"key : " + keyTable + "." + keyVal.key +
					" is already assigned to a " +
					nodeTypeToStr(actualTable->at(keyToFind)->type()));
			}
			it++;
		}
		keyToFind = *it;
		if (!tableKey->back().empty()) {
			log("toml", "parser", "adding to table : " + keyToFind);
			switch (keyVal.content->type()) {
			case STRING:
				(*actualTable)[keyToFind] =
					new Value<std::string>(new std::string(
						*(std::string *)(keyVal.content->getValue())));
				delete keyVal.content;
				break;
			case INT:
				(*actualTable)[keyToFind] = new Value<int32_t>(
					new int32_t(*(int32_t *)keyVal.content->getValue()));
				delete keyVal.content;
				break;
			case BOOL:
				(*actualTable)[keyToFind] = new Value<bool>(
					new bool(*(bool *)keyVal.content->getValue()));
				delete keyVal.content;
				break;
			case ARRAY: {
				ANode *newVec = ((Array *)keyVal.content)->clone();
				(*actualTable)[keyToFind] = newVec;
				delete keyVal.content;
				break;
			}
			default:
				throw ParseError("value type not recognized");
			};
			delete tableKey;
			return;
		}
		delete tableKey;
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

	/**
	 *	@brief	Check if the current token is one of the expected type
	 *
	 *	@param	a vector of the expected tokens
	 */
	void multiExpect(std::vector<tokenizer::tokenType> expected) {
		if (expected.size() == 1) {
			if (_tokenizer.peek()->type == *expected.begin()) {
				delete _finalNode;
				throw ParseError(
					"Expected a " +
					tokenizer::tokenTypetoStr(*expected.begin()) +
					" but got a " +
					tokenizer::tokenTypetoStr(_tokenizer.peek()->type));
			}
		} else {
			for (std::vector<tokenizer::tokenType>::iterator it =
					 expected.begin();
				 it != expected.end(); it++) {
				if (_tokenizer.peek()->type == *it) {
					return;
				}
			}
		}
		std::ostringstream oss;
		oss << "Expected one of the following tokens: ";
		for (size_t i = 0; i < expected.size(); ++i) {
			oss << tokenizer::tokenTypetoStr(expected[i]);
			if (i < expected.size() - 1) {
				oss << ", ";
			}
		}
		delete _finalNode;
		oss << " but got a "
			<< tokenizer::tokenTypetoStr(_tokenizer.peek()->type);
		throw ParseError(oss.str());
	}

	/**
	 *	@brief	Internal function used to throw cleanly an error on
	 *tokenizer error
	 */
	void nextToken(void) {
		try {
			_tokenizer.next();
		} catch (const tokenizer::TokenizerError &e) {
			// delete _finalNode;
			throw e;
		}
	}
};

}; // namespace parser
}; // namespace toml
