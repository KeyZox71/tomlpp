/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:31:55 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/21 07:41:53 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node/ANode.hpp"
#include "node/Table.hpp"
#include <cstddef>
#include <fstream>
#include <string>
#include "utils.hpp"

namespace toml {
namespace tokenizer {

typedef enum {
	NL,
	KEY,
	EQUAL,
	TABLE,
	ARRAYTABLE,
	VALUE,
} tokenKind_t;

class Tokenizer {
  public:
	Tokenizer(std::string fileName);
	~Tokenizer(void);

	/**
	 *	@brief	Returns the next token in line in the toml file
	 *
	 *	@return	A string containing the newly read token
	 */
	std::string getNextToken(void);
	/**
	 *	@brief	Returns the last read token
	 *
	 *	@return	A string container the last read token
	 */
	std::string	getLastToken(void);

  protected:
  private:
	std::string _file;
	size_t		_fileIndex;
	std::string _lastToken;
};

} // namespace tokenizer
} // namespace toml
