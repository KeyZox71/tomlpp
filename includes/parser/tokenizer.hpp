/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:31:55 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/27 12:30:28 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "cppeleven.hpp"
#include "node/Table.hpp"
#include <cstddef>
#include <fstream>
#include <string>

namespace toml {
namespace tokenizer {

/**
 * @brief	Enum for specifying the token type
 *
 * @see		Tokenizer class
 */
enum tokenType {
	KEY,
	VALUE,
	TABLE_START,
	TABLE_END,
	ARRAY_START,
	ARRAY_END,
	ASSIGNMENT_OPERATOR,
	STRING,
	NUMBER,
	BOOL,
	NEWLINE,
	COMMA,
	END,
	ERR
};

/**
 *	@brief	Struct for the tokenizer to return a token with it's type
 *
 *	@see	Tokenizer class
 */
struct token {
	std::string token;
	tokenType	type;
};

/**
 *	@brief	Class that tokenize a plain text toml file
 *
 *			next() to scan for the next token and peek() to get the read token,
 *			returns (token){"", END} if a end of file and return
 *			(token){"", ERR} if didn't initialize with next()
 *
 *	@note	Throw an error if a token is invalid
 */
class Tokenizer {
  public:
	Tokenizer(std::string &input)
		: _input(input), _index(0), _currentToken((token){"", ERR}) { log("toml", "tokenizer", "constructor called");}
	~Tokenizer(void) {}

	/**
	 *	@brief	Scan the _input for the next token
	 */
	void next(void);
	/**
	 *	@brief	Returns the read token
	 *
	 *	@return	A struct with a string and the type of the read token
	 */
	token *peek(void);

  protected:
  private:
	std::string _input;		   ///< The file input in plain text
	size_t		_index;		   ///< The index which we are in the file
	token		_currentToken; ///< The last read token

	/**
	 *	@brief	Internal function used to throw error in the tokenizer
	 */
	void tokenizerError(std::string e) {
		throw std::runtime_error("Token error - " + e);
	}
};

} // namespace tokenizer
} // namespace toml
