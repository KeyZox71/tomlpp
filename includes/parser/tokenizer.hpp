/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:31:55 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/04 12:59:09 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node/ANode.hpp"
#include <cstddef>
#include <fstream>
#include <string>
#include "utils.hpp"

namespace toml {
namespace tokenizer {

typedef struct {
	valueType_t kind;
	std::string token;
} token_t;

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

	std::string getNextToken(void);

  protected:
  private:
	std::string _file;
	size_t		_fileIndex;
};

} // namespace tokenizer
} // namespace toml
