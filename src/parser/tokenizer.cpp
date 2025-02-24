/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:42:13 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/24 18:13:07 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/tokenizer.hpp"
#include <cctype>
#include <stdexcept>
#include <string>

using namespace toml;
using namespace tokenizer;

void tokenizerError(std::string e) {
	throw std::runtime_error("Token error - " + e);
}

token Tokenizer::next(void) {
	while (_index < _input.size()) {
		char c = _input[_index];
		_index++;

		if (std::isspace(c))
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
			return (token){_input.substr(nbStart, _index - nbStart), NUMBER};
		}

		if (c == '"') {
			size_t strStart = _index;
			bool   escape = false;
			while (_index < _input.size() && _input[_index] != '"' &&
				   _input[_index] != '\n') {
				if (_input[_index] == '"' && !escape) {
					_index++;
					return (token){_input.substr(strStart, _index - strStart - 1), STRING};
				}
				escape = !escape && _input[_index] == '\\';
				_index++;
			}
			tokenizerError("unexpected token in string : " + std::string(_input[_index], 1));
		}

		if (isalpha(c)) {
			size_t	keyStart = _index;
			while (_index < _input.size() && isgraph(_input[_index])) {
				_index++;
			}
			std::string endValue = _input.substr(keyStart, _index - keyStart);
			if (endValue == "true" || endValue == "false") {
				return (token){endValue, BOOL};
			}
			return (token){endValue, KEY};
		}

		switch (c) {
		case '{':
			return (token){"", TABLE_START};
		case '}':
			return (token){"", TABLE_END};
		case '[':
			return (token){"", ARRAY_START};
		case ']':
			return (token){"", ARRAY_END};
		case '=':
			return (token){"", ASSIGNMENT_OPERATOR};
		case '\n':
			return (token){"", NEWLINE};
		default:
			tokenizerError("unexpected token : " + std::string(1, c));
		}
	}
}
