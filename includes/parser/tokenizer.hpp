/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:31:55 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/25 11:43:08 by adjoly           ###   ########.fr       */
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

struct token {
	std::string token;
	tokenType	type;
};

class Tokenizer {
  public:
	Tokenizer(std::string &input)
		: _input(input), _index(0), _currentToken((token){"", ERR}) {}
	~Tokenizer(void){}

	/**
	 *	@brief	Returns the next token in line in the toml file
	 *
	 *	@return	A struct containing the string of the token(which can be empty) and it's type
	 */
	void	next(void);
	/**
	 *	@brief	Returns the read token
	 *
	 *	@return	The a struct with a string and the type of the read token
	 */
	token	*peek(void);

  protected:
  private:
	std::string _input;
	size_t		_index;
	token		_currentToken;
};

} // namespace tokenizer
} // namespace toml
