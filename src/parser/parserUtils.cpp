/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:40:58 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/11 19:35:52 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cppeleven.hpp"
#include "node/ANode.hpp"
#include "node/default.hpp"
#include "parser/default.hpp"
#include "parser/parser.hpp"
#include "parser/tokenizer.hpp"
#include <sstream>
#include <string>
#include <vector>

using namespace toml;
using namespace parser;

std::vector<std::string> *splitKey(std::string key) {
	std::stringstream		  ss(key);
	std::vector<std::string> *splitedKey = new std::vector<std::string>;
	std::string				  singleKey;

	while (std::getline(ss, singleKey, '.')) {
		splitedKey->push_back(singleKey);
	}
	return splitedKey;
}

void Parser::addToTable(std::string keyTable, parser::keyValue keyVal) {
	if (keyVal.key.empty())
		throw ParseError("Expected a key but got nothing :(");
	std::vector<std::string> *splitedKey = splitKey(keyVal.key);
	if (!keyTable.empty()) {
		std::vector<std::string> *newKeyTable = splitKey(keyTable);
		splitedKey->insert(splitedKey->begin(), newKeyTable->begin(),
						   newKeyTable->end());
		delete newKeyTable;
	}
	ANode	   *actualTable = _finalNode;
	std::string keyToFind;

	for (size_t i = 0; !splitedKey->at(i).empty(); i++) {
		std::string keyToFind = splitedKey->at(i);
		if (i == splitedKey->size())
			break;
		else if (actualTable->type() == TABLE) {
			actualTable = actualTable->getTable();
		} else {
			throw ParseError("key : " + keyTable + "." + keyVal.key +
							 " is already assigned to a " +
							 nodeTypeToStr(actualTable->type()));
		}
	}

	if (!keyToFind.empty()) {
		actualTable->getTable()[keyToFind] = keyVal.content;
	}
	throw ParseError("last key is empty :(");
}
