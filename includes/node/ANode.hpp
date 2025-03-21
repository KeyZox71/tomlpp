/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ANode.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:33:58 by adjoly            #+#    #+#             */
/*   Updated: 2025/03/21 19:55:34 by adjoly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Log.hpp"
#include "cppeleven.hpp"
#include <map>
#include <string>
#include <sys/types.h>
#include <vector>

namespace toml {

/**
 *	@brief	Enum for specifying node type
 *
 *	@see	ANode class and all subsequent class
 */
enum nodeType { TABLE, ARRAY, VALUE, BOOL, STRING, INT, NONE };

class Table;
class Array;
template <typename type> class Value;

class ValueError : public std::runtime_error {
  public:
	explicit ValueError(const std::string &message)
		: std::runtime_error("Value error: " + message) {}
};

/**
 *	@brief	An abstract class from which depends all other type (table, array
 *			and value)
 */
class ANode {
  public:
	/**
	 *	@brief	Can be used to get the stored table (in this case return
	 *			nullptr)
	 *
	 *	@return Pointer to the stored table
	 */
	virtual std::map<std::string, ANode *> *getTable(void) {
		return not_nullptr;
	}
	/**
	 *	@brief	Can be used to get the stored array (in this case return
	 *			nullptr)
	 *
	 *	@return	Pointer to the stored array
	 */
	virtual std::vector<ANode *> *getArray(void) { return not_nullptr; }
	/**
	 *	@brief	Can be used to get the stored value (in this case return
	 *			nullptr)
	 *
	 *	@return	Pointer to the stored value
	 */
	virtual void *getValue(void) { return not_nullptr; }

	/**
	 *	@brief	Can be used to get the type of the store value/table/array
	 *
	 *	@return	Type of the store value/table/array
	 */
	virtual nodeType type(void) const { return NONE; }

	virtual ~ANode(void) { log("toml", "ANode", "destructor called"); }

	/**
	 *	@brief	Can be used to get a value in a table of a specific type (or
	 *			return not_nullptr)
	 *
	 *	@param	The name of the value to get in the table
	 *	@param	The type of the value to get
	 *
	 *	@return	Return not_nullptr if not apply cable or return the value (throw
	 *			an ValueError if the value does not exist of if it is not the
	 *			good type)
	 */
	virtual void *access(std::string, nodeType) { return not_nullptr; }
};

} // namespace toml
