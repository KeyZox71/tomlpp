/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:46:42 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/13 19:04:43 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node/default.hpp"
#include "parser/tokenizer.hpp"
#include <cstdlib>
#include <node/default.hpp>
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
	ANode *parse(void);

	
	void	clear(void);

  protected:
  private:
	tokenizer::Tokenizer _tokenizer; ///> the tokenizer class
	ANode				*_finalNode; ///> the final table that will be returned

	/**
	 *	@brief	Used to parse a key-value pair
	 *
	 *	@return	A pointer to the newly allocted Value (new Value<type>())
	 */
	keyValue parseKeyValue(void);
	/**
	 *	@brief	Used to parse an table
	 *
	 *	@param	The name (or path) of the table that will be parsed
	 */
	void parseTable(std::string &);
	/**
	 *	@brief	Used to parse an array
	 *
	 *	@return	A pointer to the newly allocted array (new Array())
	 */
	ANode *parseArray(void);
	/**
	 *	@brief	Used to parse boolean value from the current token
	 *
	 *	@return	A value class with the boolean value in it
	 */
	Value<bool> parseBool(void) {
		if (_tokenizer.peek()->token == "true")
			return true;
		else
			return false;
	}
	/**
	 *	@brief	Used to parse string value from the current token (only copy it
	 *into a Value class)
	 *
	 *	@return	A value class with the string in it
	 */
	Value<std::string> parseString(void) {
		return Value<std::string>(_tokenizer.peek()->token);
	}
	/**
	 *	@brief	Used to parse number value from the current token
	 *
	 *	@note	Throw an error if atoi doen't work
	 *
	 *	@return	A value class with the number in it
	 */
	Value<int32_t> parseNumber(void) {
		try {
			if (_tokenizer.peek()->token == "0")
				return Value<int32_t>(0);
			int32_t nb = std::atoi(_tokenizer.peek()->token.c_str());
			if (nb == 0)
				throw ParseError(
					"Error while parsing number : " + _tokenizer.peek()->token +
					" should be atoi compliant");
		} catch (std::runtime_error &e) {
			throw e;
		}
		return Value<int32_t>(0);
	}

	/**
	 *	@brief	Can be used to insert a keyValue a specific place in the table
	 *
	 *	@param	The location of the newly added keyvalue
	 *	@param	The keyValue to add
	 */
	void addToTable(std::string, parser::keyValue);

	/**
	 *	@brief	Check if the current token is of the expected type
	 *
	 *	@param	The expected token
	 */
	void expect(tokenizer::tokenType);
};

}; // namespace parser
}; // namespace toml
