/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:13:44 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/03 19:52:52 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/utils.hpp"
#include <string>

bool checkForTripleQuote(std::string str, size_t &index) {
	if (!str[index] || !str[index + 1] || !str[index + 2])
		return false;
	else if (str[index] == '\'' && str[index + 1] == '\'' &&
			 str[index + 2] == '\'')
		return true;
	else if (str[index] == '"' && str[index + 1] == '"' &&
			 str[index + 2] == '"')
		return true;
	else
		return false;
}

bool checkDoubleQ(char c) {
	if (c == '"')
		return true;
	else
		return false;
}

bool checkForDoubleBracket(std::string str, size_t &index, char bracketType) {
	if (!str[index] || !str[index + 1])
		return false;
	else if (str[index] == bracketType && str[index + 1] == bracketType)
		return true;
	else
		return false;
}

std::string getStr(std::string &_file, size_t &index) {
	size_t start = index;

	while (_file[index] && !isspace(_file[index])) {
		index++;
	}
	return _file.substr(start, index - start);
}

std::string getQuotedString(std::string _file, size_t &index) {
	size_t start = index;
	bool   multiLine = checkForTripleQuote(_file, index);
	bool   doubleQuote = checkDoubleQ(_file[index]);

	if (multiLine)
		index += 3;
	else
		index++;
	while (_file[index]) {
		if (multiLine && checkForTripleQuote(_file, index) &&
			doubleQuote == checkDoubleQ(_file[index])) {
			index += 3;
			break;
		} else if (!multiLine && doubleQuote == checkDoubleQ(_file[index]) &&
				   (_file[index] == '\'' || _file[index] == '"')) {
			index++;
			break;
		} else if (!multiLine && _file[index] == '\n') {
			index++;
			break;
		}
		index++;
	}
	return _file.substr(start, index - start);
}

std::string getTableString(std::string _file, size_t &index) {
	size_t start = index;
	bool   tableArray = checkForDoubleBracket(_file, index, '[');

	if (tableArray)
		index += 2;
	else
		index++;
	while (_file[index]) {
		if (tableArray && checkForDoubleBracket(_file, index, ']')) {
			index += 2;
			break;
		} else if (_file[index] == ']') {
			index++;
			break;
		} else if (_file[index] == '\n') {
			index++;
			break;
		}
		index++;
	}
	return _file.substr(start, index - start);
}
