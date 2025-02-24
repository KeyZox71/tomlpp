/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:31:55 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/24 19:21:42 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node/ANode.hpp"
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
	END
};

struct token {
	std::string token;
	tokenType	type;
};

class Tokenizer {
  public:
	Tokenizer(std::string &input)
		: _input(input), _index(0), _currentToken((token){"", END}) {}
	~Tokenizer(void);

	/**
	 *	@brief	Returns the next token in line in the toml file
	 *
	 *	@return	A struct containing the string of the token(which can be empty) and it's type
	 */
	token next(void);
	/**
	 *	@brief	Returns the read token
	 *
	 *	@return	A string that contains the read token
	 */
	std::string peek(void);

  protected:
  private:
	std::string _input;
	size_t		_index;
	token		_currentToken;
};

} // namespace tokenizer
} // namespace toml
