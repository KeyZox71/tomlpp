/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:40:58 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/12 10:06:04 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cppeleven.hpp"
#include "node/ANode.hpp"
#include "node/default.hpp"
#include "parser/default.hpp"
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
	std::map<std::string, ANode> &actualTable = *_finalNode->getTable();
	std::string					  keyToFind;

	for (size_t i = 0; !splitedKey->at(i).empty(); i++) {
		std::string keyToFind = splitedKey->at(i);
		if (i == splitedKey->size())
			break;
		else if (actualTable[keyToFind].type() == TABLE) {
			actualTable = *(actualTable[keyToFind].getTable());
		} else {
			throw ParseError("key : " + keyTable + "." + keyVal.key +
							 " is already assigned to a " +
							 nodeTypeToStr(actualTable[keyToFind].type()));
		}
	}

	if (!keyToFind.empty()) {
		actualTable[keyToFind] = *keyVal.content;
	}
	throw ParseError("last key is empty :(");
}
