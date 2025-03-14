/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:31:55 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/14 16:18:59 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "cppeleven.hpp"
#include "node/Table.hpp"
#include <cstddef>
#include <fstream>
#include <map>
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

static inline std::string tokenTypetoStr(tokenType type) {
	static std::map<tokenType, std::string> tokenTypeName;
	if (tokenTypeName.empty()) {
		tokenTypeName[KEY] = "key";
		tokenTypeName[VALUE] = "value";
		tokenTypeName[TABLE_START] = "[";
		tokenTypeName[TABLE_END] = "]";
		tokenTypeName[ARRAY_START] = "{";
		tokenTypeName[ARRAY_END] = "}";
		tokenTypeName[ASSIGNMENT_OPERATOR] = "=";
		tokenTypeName[STRING] = "string";
		tokenTypeName[NUMBER] = "number";
		tokenTypeName[BOOL] = "boolean";
		tokenTypeName[NEWLINE] = "newline";
		tokenTypeName[COMMA] = ",";
		tokenTypeName[END] = "end of file";
	}
	return tokenTypeName.at(type);
}

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
		: _input(input), _index(0), _currentToken((token){"", ERR}) {
		log("toml", "tokenizer", "constructor called");
	}
	~Tokenizer(void) {}

	/**
	 *	@brief	Scan the _input for the next token
	 */
	void next(void) {
		while (_index < _input.size()) {
			char c = _input[_index];
			_index++;

			if (std::isspace(c) && c != '\n')
				continue;

			if (c == '#' && _index < _input.size() && _input[_index] != '\n') {
				size_t commentEnd = _input.find('\n', _index);
				if (commentEnd != _input.npos) {
					_index = commentEnd + 1;
				} else {
					_index = _input.size();
				}
				continue;
			}

			if (std::isdigit(c)) {
				size_t nbStart = _index;
				while (_index < _input.size() && isdigit(_input[_index])) {
					_index++;
				}
				_currentToken = (token){
					_input.substr(nbStart - 1, _index - nbStart + 1), NUMBER};
				return;
			}

			if (c == '"') {
				size_t strStart = _index;
				bool   escape = false;
				while (_index < _input.size() && _input[_index] != '"' &&
					   _input[_index] != '\n') {
					escape = !escape && _input[_index] == '\\';
					_index++;
				}
				if (_index == _input.size())
					tokenizerError("unexpected token in string : " +
								   std::string(_input[_index], 1));
				_index++;
				_currentToken = (token){
					_input.substr(strStart, _index - strStart - 1), STRING};
				return;
			}

			if (isalpha(c)) {
				size_t keyStart = _index - 1;
				while (_index < _input.size() &&
					   (isalpha(_input[_index]) || _input[_index] == '.')) {
					_index++;
				}
				std::string endValue =
					_input.substr(keyStart, _index - keyStart);
				if (endValue == "true" || endValue == "false") {
					_currentToken = (token){endValue, BOOL};
					return;
				}
				_currentToken = (token){endValue, KEY};
				return;
			}

			switch (c) {
			case '{':
				_currentToken = (token){"", TABLE_START};
				return;
			case '}':
				_currentToken = (token){"", TABLE_END};
				return;
			case '[':
				_currentToken = (token){"", ARRAY_START};
				return;
			case ']':
				_currentToken = (token){"", ARRAY_END};
				return;
			case '=':
				_currentToken = (token){"", ASSIGNMENT_OPERATOR};
				return;
			case '\n':
				_currentToken = (token){"", NEWLINE};
				return;
			case ',':
				_currentToken = (token){"", COMMA};
				return;
			default:
				tokenizerError("unrecognized token : " + std::string(1, c));
			}
		}
		_currentToken = (token){"", END};
		return;
	}
	/**
	 *	@brief	Returns the read token
	 *
	 *	@return	A struct with a string and the type of the read token
	 */
	token *peek(void) {
		if (_currentToken.type != ERR && _currentToken.type != END) {
			return &_currentToken;
		}
		return not_nullptr;
	}

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
