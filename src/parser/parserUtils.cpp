/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:40:58 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/11 13:46:44 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cppeleven.hpp"
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

void parser::Parser::addToTable(std::string keyTable, parser::keyValue keyVal) {
	if (keyVal.key.empty())
		throw ParseError("Expected a key but got nothing :(");
	std::vector<std::string> *splitedKey = splitKey(keyVal.key);
	if (!keyTable.empty()) {
		std::vector<std::string> *newKeyTable = splitKey(keyTable);
		splitedKey->insert(splitedKey->begin(), newKeyTable->begin(),
						   newKeyTable->end());
		delete newKeyTable;
	}
	std::map<std::string, ANode> &actualTable = _finalNode->getTable();
	std::string					  keyToFind;

	for (size_t i = 0; !splitedKey->at(i).empty(); i++) {
		std::string							   keyToFind = splitedKey->at(i);
		std::map<std::string, ANode>::iterator test =
			actualTable.find(keyToFind);
	}
}
