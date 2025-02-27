/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:42:13 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/27 11:16:50 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/tokenizer.hpp"
#include "cppeleven.hpp"
#include <cctype>
#include <stdexcept>
#include <string>

using namespace toml;
using namespace tokenizer;


void Tokenizer::next(void) {
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
			_currentToken =
				(token){_input.substr(strStart, _index - strStart - 1), STRING};
			return;
		}

		if (isalpha(c)) {
			size_t keyStart = _index - 1;
			while (_index < _input.size() && isalpha(_input[_index])) {
				_index++;
			}
			std::string endValue = _input.substr(keyStart, _index - keyStart);
			if (endValue == "true" || endValue == "false") {
				_currentToken = (token){endValue, BOOL};
				return;
			}
			_currentToken = (token){endValue, KEY};
			return;
		}

		switch (c) {
		case '{':
			_currentToken = (token){"{", TABLE_START};
			return;
		case '}':
			_currentToken = (token){"}", TABLE_END};
			return;
		case '[':
			_currentToken = (token){"[", ARRAY_START};
			return;
		case ']':
			_currentToken = (token){"]", ARRAY_END};
			return;
		case '=':
			_currentToken = (token){"=", ASSIGNMENT_OPERATOR};
			return;
		case '\n':
			_currentToken = (token){"NEW", NEWLINE};
			return;
		default:
			tokenizerError("unrecognized token : " + std::string(1, c));
		}
	}
	_currentToken = (token){"", END};
	return;
}

token *Tokenizer::peek(void) {
	if (_currentToken.type != ERR && _currentToken.type != END) {
		return &_currentToken;
	}
	return not_nullptr;
}
