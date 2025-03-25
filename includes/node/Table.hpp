/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Table.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:42:10 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/25 13:41:03 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Log.hpp"
#include "cppeleven.hpp"
#include "default.hpp"
#include "node/ANode.hpp"
#include <functional>
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
	Table(void) {
		log("toml", "table", "default constructor called");
		_map = new std::map<std::string, ANode *>;
	}
	Table(std::map<std::string, ANode *> *map) {
		log("toml", "table", "map constructor called");
		_map = map;
	}
	~Table(void) {
		std::map<std::string, ANode *>::iterator it;
		for (it = _map->begin(); it != _map->end(); it++) {
			delete it->second;
		}
		delete _map;
		log("toml", "table", "destructor called");
	}

	/**
	 *	@brief	Can be used to get the table stored
	 *
	 *	@return	A pointer to a map containing the stored table
	 */
	std::map<std::string, ANode *> *getTable(void) { return _map; }
	/**
	 *	@brief	Can be used to get type (always returns TABLE)
	 *
	 *	@return Always returns TABLE
	 */
	nodeType type(void) const { return TABLE; }

	/**
	 *	@brief	Can be used to get a value in a table of a specific type (or
	 *			return not_nullptr)
	 *
	 *	@param	The name of the value to get in the table
	 *	@param	The type of the value to get
	 *
	 *	@return	Return not_nullptr if not apply cable or return the value
	 */
	void *access(std::string what, nodeType type, bool &found) {
		std::map<std::string, ANode *>::iterator valIt = _map->find(what);
		if (valIt != _map->end()) {
			found = true;
			if (valIt->second->type() == type) {
				if (type == toml::TABLE)
					return valIt->second->getTable();
				if (type == toml::ARRAY)
					return valIt->second->getArray();
				else
					return valIt->second->getValue();
			} else {
				return not_nullptr;
			}
		} else {
			found = false;
			return not_nullptr;
		}
	}

	/**
	 *	@brief	Can be used to get a iterator in a table of a specific type (or
	 *			return not_nullptr)
	 *
	 *	@param	The name of the value to get in the table
	 *	@param	The type of the value to get
	 *	@param	An error boolean that tell you if the value was found or not
	 *
	 *	@return	Return not_nullptr if not apply cable or return an iterator to
	 *			the node
	 */
	std::map<std::string, ANode *>::iterator accessIt(std::string what, nodeType type,
													   bool &found) {
		std::map<std::string, ANode *>::iterator it = _map->find(what);
		if (it != _map->end()) {
			found = true;
			if (it->second->type() == type) {
				return it;
			} else {
				return _map->end();
			}
		} else {
			found = false;
			return _map->end();
		}
	}

  protected:
  private:
	std::map<std::string, ANode *> *_map; ///< Map of the stored table
};

} // namespace toml
