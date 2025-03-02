/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Table.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:42:10 by adjoly            #+#    #+#             */
/*   Updated: 2025/02/28 09:04:27 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ANode.hpp"
#include "Log.hpp"
#include "parser/tokenizer.hpp"
#include <map>

namespace toml {

/**
 *	@brief	Class for toml table
 *
 *	Stored a map the key is a string and the value is a ANode (which can be of
 *	any type possible in toml)
 */
class Table : public ANode {
  public:
	Table(std::map<std::string, ANode> *map) {
		log("toml", "table", "constructor called");
		_map = map;
	}
	~Table(void) {
		delete _map;
		log("toml", "table", "destructor called"); }

	/**
	 *	@brief	Can be used to get the table stored
	 *
	 *	@return	A pointer to a map containing the stored table
	 */
	std::map<std::string, ANode> *getTable(void) { return _map; }
	/**
	 *	@brief	Can be used to get type (always returns TABLE)
	 *
	 *	@return Always returns TABLE
	 */
	nodeType type(void) const { return TABLE; }

  protected:
  private:
	std::map<std::string, ANode> *_map; ///< Map of the stored table
};

} // namespace toml
