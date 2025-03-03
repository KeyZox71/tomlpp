/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:46:42 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/03 11:02:35 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node/ANode.hpp"
#include "node/ValueTemplate.hpp"
#include "parser/tokenizer.hpp"
#include <cstdint>
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
		log("toml", "parser", "constructor called");
	}
	~Parser(void) { log("toml", "parser", "destructor called"); }

	/**
	 *	@brief	Can be used to parse the tokens returned by the tokenizer
	 *
	 *	@return	A pointer to the main table in the AST
	 */
	ANode *parse(void);

  protected:
  private:
	tokenizer::Tokenizer _tokenizer; ///> the tokenizer class
	Table				*_finalNode; ///> the final table that will be returned

	/**
	 *	@brief	Used to parse a key-value pair
	 *
	 *	@return	A pointer to the newly allocted Value (new Value<type>())
	 */
	keyValue parseKeyValue(void);
	/**
	 *	@brief	Used to parse an table
	 *
	 *	@return	A pointer to the newly allocted table (new Table())
	 */
	ANode *parseTable(void);
	/**
	 *	@brief	Used to parse an array
	 *
	 *	@return	A pointer to the newly allocted array (new Array())
	 */
	ANode *parseArray(void);
	/**
	 *	@brief	Used to parse token into value
	 *
	 *	@return	A pointer to the newly allocated value
	 */
	ANode parseValue(void) {}
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
		} catch (std::runtime_error e) {
			throw e;
		}
	}

	/**
	 *	@brief	Check if the current token is of the expected type
	 *
	 *	@param	The expected token
	 */
	void expect(tokenizer::tokenType);
};

}; // namespace parser
}; // namespace toml
