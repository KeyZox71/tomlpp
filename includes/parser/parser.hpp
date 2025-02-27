/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:46:42 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/27 12:31:15 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node/ValueTemplate.hpp"
#include "parser/tokenizer.hpp"
#include <node/default.hpp>
#include <stdexcept>
#include <string>

namespace toml {
namespace parser {

/**
 *	@brief	Class used to parse the content return by the tokenizer
 *
 *	Get the tokenizer's content and parse into an AST defined in ANode(and it's
 *	derived classes)
 */
class Parser {
  public:
	Parser(tokenizer::Tokenizer tokenizer) : _tokenizer(tokenizer) {
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

	/**
	 *	@brief	Used to parse a key-value pair
	 */
	ANode parseKeyValue(void);
	/**
	 *	@brief	Used to parse an table
	 */
	ANode parseTable(void);
	/**
	 * @brief	Used to parse an array
	 */
	ANode parseArray(void);

	/**
	 *	@brief				Check if the current token is of the expected type
	 *
	 *	@param	expected	The expected token
	 */
	void expect(tokenizer::tokenType expected);

	/**
	 *	@brief	Internal function used for throwing error if something can't be parsed
	 */
	void parserError(std::string e) {
		throw std::runtime_error("Parsing error - " + e);
	}
};

}; // namespace parser
}; // namespace toml
