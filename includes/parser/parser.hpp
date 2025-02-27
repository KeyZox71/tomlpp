/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:46:42 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/27 11:04:05 by adjoly           ###   ########.fr       */
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

void parserError(std::string e) {
	throw std::runtime_error("Parsing error - " + e);
}

class Parser {
  public:
	Parser(tokenizer::Tokenizer tokenizer) : _tokenizer(tokenizer) { log("tomlParser", "", "constructor called"); }
	~Parser(void) { log("tomlParser", "", "destructor called"); }
	ANode parse(void);

  protected:
  private:
	tokenizer::Tokenizer	_tokenizer;

	/**
	 *	@brief	Used to parse a key-value pair
	 */
	ANode	parseKeyValue(void);
	/**
	 *	@brief	Used to parse an table
	 */
	ANode	parseTable(void);
	/**
	 * @brief	Used to parse an array
	 */
	ANode	parseArray(void);

	/**
	 *	@brief				Check if the current token is of the expected type
	 *
	 *	@param	expected	The expected token
	 */
	void	expect(tokenizer::tokenType expected);

};

}; // namespace parser

}; // namespace toml
