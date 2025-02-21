/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:32:45 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/21 07:37:19 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node/ANode.hpp"
#include "node/ValueTemplate.hpp"
#include "parser/tokenizer.hpp"
#include <string>

namespace toml {
namespace tokenizer {

bool		checkForTripleQuote(std::string, size_t &);
std::string getStr(std::string, size_t &);
std::string getQuotedString(std::string, size_t &);
std::string getTableString(std::string, size_t &);

} // namespace tokenizer

namespace parser {

toml::Table				 convertTable(tokenizer::Tokenizer);
toml::Value<bool>		 convertBool(std::string);
toml::Value<std::string> convertString(std::string);
toml::Value<int16_t>	 convertInt(std::string);

bool isTable(std::string);
bool isBool(std::string);
bool isString(std::string);
bool isInt(std::string);

} // namespace parser
} // namespace toml
