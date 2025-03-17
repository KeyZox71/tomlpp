/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tomlpp.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:57:22 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/17 11:39:37 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node/ANode.hpp"
#include "parser/default.hpp"
#include "node/default.hpp"
#include "parser/parser.hpp"
#include "parser/tokenizer.hpp"
#include <sstream>
#include <string>

namespace toml {


/**
 *	@brief	Class that can be used to parse a toml file
 */
class Toml {
  public:
	/**
	 * @brief	constructor that takes a filename and parse it
	 *
	 * @param	The name of the file that will be parsed by this class
	 */
	Toml(std::string filePath) : _filePath(filePath) {
		log("toml", "Toml", "filePath constructor called");
		
		std::ifstream input(filePath.c_str());
		std::stringstream buf;
		std::string s;

		buf << input.rdbuf();
		s = buf.str();
		_tokenizer = new tokenizer::Tokenizer(s);
		_parser = new parser::Parser(*_tokenizer);
		_ast = _parser->parse();
		delete _tokenizer;
	}
	
	~Toml(void) {
		log("toml", "Toml", "destructor called");

		delete _parser;
	}
	/**
	 *	@brief	function that can be used to get the parsed file
	 *
	 *	@return	the final node (a Table) of the parsed file
	 */
	ANode	*getParsedFile(void) {
		return _ast;
	}

  protected:
  private:
	tokenizer::Tokenizer *_tokenizer; ///> a pointer to the tokenizer class
	parser::Parser		 *_parser; ///> a pointer to the parser class

	ANode	*_ast; ///> the abstract syntax tree

	std::string	_filePath; ///> the filepath that will be parsed
};

} // namespace toml
