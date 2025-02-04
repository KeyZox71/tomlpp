/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:42:13 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/04 12:42:14 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/tokenizer.hpp"
#include "Log.hpp"
#include "parser/utils.hpp"
#include <cctype>
#include <cstddef>
#include <cwctype>
#include <fstream>
#include <sstream>
#include <string>

using namespace toml;
using namespace tokenizer;

Tokenizer::Tokenizer(std::string fileName) : _fileIndex(0) {
	std::ifstream fileStream;
	try {
		fileStream.open(fileName.c_str());

		if (!fileStream.is_open()) {
			throw fileName;
		}
	} catch (std::string fileName) {
		logWarning("tomlpp", "File open", "error opening " + fileName);
		return;
	}

	std::stringstream ss;

	ss << fileStream.rdbuf();
	_file = ss.str();
	fileStream.close();
}

std::string Tokenizer::getNextToken(void) {
	std::string token;

	while (_fileIndex < _file.length()) {
		if (_file[_fileIndex] == '\n' || _file[_fileIndex] == '=')
			return _file.substr(_fileIndex++, 1);
		else if (_file[_fileIndex] == '[')
			return getTableString(_file, _fileIndex);
		else if (isalnum(_file[_fileIndex]))
			return getStr(_file, _fileIndex);
		else if (_file[_fileIndex] == '"' || _file[_fileIndex] == '\'')
			return getQuotedString(_file, _fileIndex);
		_fileIndex++;
	}
	return token;
}

Tokenizer::~Tokenizer(void) {}
